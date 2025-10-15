// PerfLog.h — append human-readable tables to Logs/perf_summary.txt
#pragma once
#include <string>

namespace perflog
{
    // Append a header like: "Sorting Performance (N=50000)"
    void append_header(const std::string& title);

    // Append one row to the table
    void append_row(const std::string& name, long long ms);

    // Append a horizontal rule
    void append_rule();
}
