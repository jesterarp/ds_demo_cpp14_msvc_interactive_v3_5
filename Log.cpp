// Log.cpp — MSVC v143 / C++14 / DO-178 single-return
#include "Log.h"
#include <iostream>
#include <streambuf>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#  include <direct.h>   // _mkdir
#endif

namespace
{
    // Streambuf that mirrors output to two destinations (console + file)
    class TeeBuf : public std::streambuf
    {
    public:
        TeeBuf(std::streambuf* a, std::streambuf* b)
            : m_a(a), m_b(b)
        {
        }

    protected:
        virtual int overflow(int ch) /*override*/
        {
            int result = 0;
            int wa = 0;
            int wb = 0;

            if (ch == traits_type::eof())
            {
                wa = (m_a ? m_a->sputc(traits_type::to_char_type(ch)) : 0);
                wb = (m_b ? m_b->sputc(traits_type::to_char_type(ch)) : 0);
                result = traits_type::eof(); // but this path is rarely used
            }
            else
            {
                const char c = static_cast<char>(ch);
                wa = (m_a ? m_a->sputc(c) : 0);
                wb = (m_b ? m_b->sputc(c) : 0);
                result = (wa == traits_type::eof() || wb == traits_type::eof())
                         ? traits_type::eof()
                         : ch;
            }
            return result;
        }

        virtual std::streamsize xsputn(const char* s, std::streamsize n) /*override*/
        {
            std::streamsize result = 0;
            std::streamsize wa = 0;
            std::streamsize wb = 0;

            if (m_a) { wa = m_a->sputn(s, n); }
            if (m_b) { wb = m_b->sputn(s, n); }
            result = (wa < n || wb < n) ? (wa < wb ? wa : wb) : n;
            return result;
        }

        virtual int sync() /*override*/
        {
            int result = 0;
            int sa = 0;
            int sb = 0;

            if (m_a) { sa = m_a->pubsync(); }
            if (m_b) { sb = m_b->pubsync(); }
            result = (sa != 0 || sb != 0) ? -1 : 0;
            return result;
        }

    private:
        std::streambuf* m_a; // typically std::cout.rdbuf()
        std::streambuf* m_b; // file.rdbuf()
    };

    std::ofstream   g_logFile;
    TeeBuf*         g_teeBuf = 0;
    std::streambuf* g_oldCoutBuf = 0;

    static std::string make_timestamp_filename()
    {
        std::string name;
        std::time_t t = std::time(0);
        std::tm tmv;
#if defined(_WIN32)
        localtime_s(&tmv, &t);
#else
        tmv = *std::localtime(&t);
#endif
        char buf[64] = {0};
        if (std::strftime(buf, sizeof(buf), "demo_%Y%m%d_%H%M%S.txt", &tmv) != 0)
        {
            name.assign(buf);
        }
        else
        {
            name.assign("demo.txt");
        }
        return name;
    }

    static void ensure_logs_dir()
    {
#ifdef _WIN32
        // _mkdir returns 0 on success or if already exists (errno=EEXIST) – we ignore errors
        (void)_mkdir("Logs");
#endif
    }
}

namespace logsys
{
    void init()
    {
        ensure_logs_dir();

        const std::string fileName = std::string("Logs/") + make_timestamp_filename();
        g_logFile.open(fileName.c_str(), std::ios::out | std::ios::trunc);
        if (!g_logFile.is_open())
        {
            // If we cannot open, do not alter cout. Still honor single-return.
        }
        else
        {
            g_oldCoutBuf = std::cout.rdbuf();
            g_teeBuf = new TeeBuf(g_oldCoutBuf, g_logFile.rdbuf());
            std::cout.rdbuf(g_teeBuf);
        }
    }

    void close()
    {
        if (g_oldCoutBuf != 0)
        {
            std::cout.rdbuf(g_oldCoutBuf);
            g_oldCoutBuf = 0;
        }
        if (g_teeBuf != 0)
        {
            delete g_teeBuf;
            g_teeBuf = 0;
        }
        if (g_logFile.is_open())
        {
            g_logFile.flush();
            g_logFile.close();
        }
    }
}
