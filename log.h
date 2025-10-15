// Log.h — MSVC v143 / C++14 / DO-178 single-return
#pragma once
#include <iostream>
#include <ostream>

namespace logsys
{
    // Initialize logging: creates .\Logs\demo_YYYYMMDD_HHMMSS.txt
    // Redirects std::cout to a tee that writes to console and log file.
    void init();

    // Restore std::cout and close the log file.
    void close();

    // (Optional) return a reference to std::cout (already tee’d)
    inline std::ostream& stream() { return std::cout; }
}
