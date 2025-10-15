// PerfLog.cpp — MSVC v143 / C++14
#include "PerfLog.h"
#include <fstream>
#include <sstream>
#include <iomanip>

namespace
{
    static const char* kPerfFile = "Logs/perf_summary.txt";

    static std::string pad(const std::string& s, std::size_t w)
    {
        std::string out = s;
        if (out.size() < w) { out.append(w - out.size(), ' '); }
        return out;
    }
}

namespace perflog
{
    void append_header(const std::string& title)
    {
        std::ofstream f(kPerfFile, std::ios::out | std::ios::app);
        if (f.is_open())
        {
            f << "\n" << title << "\n";
            f << "+---------------+-----------+\n";
            f << "| " << pad("Algorithm", 13) << " | " << pad("Time (ms)", 9) << " |\n";
            f << "+---------------+-----------+\n";
        }
    }

    void append_row(const std::string& name, long long ms)
    {
        std::ofstream f(kPerfFile, std::ios::out | std::ios::app);
        if (f.is_open())
        {
            std::ostringstream oss;
            oss << ms;
            f << "| " << pad(name, 13) << " | " << pad(oss.str(), 9) << " |\n";
        }
    }

    void append_rule()
    {
        std::ofstream f(kPerfFile, std::ios::out | std::ios::app);
        if (f.is_open())
        {
            f << "+---------------+-----------+\n";
        }
    }
}
