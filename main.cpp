// main.cpp — v3.7 menu-driven (C++14 / MSVC v143 / DO-178 single-return)
#include "Algorithms.h"
#include "BinarySearchTree.h"
#include "DoublyLinkedList.h"
#include "Log.h"
#include "PerfLog.h"
#include "SinglyLinkedList.h"

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

// ---------- small helpers ----------
static void pause_line()
{
    std::cout << "Press Enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);
}

static int read_int(const char* prompt)
{
    int value = 0;
    bool ok = false;
    while (!ok)
    {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line))
        {
            // EOF or stream error: fall back to 0
            ok = true;
        }
        else
        {
            std::istringstream iss(line);
            if (iss >> value)
            {
                ok = true;
            }
            else
            {
                std::cout << "Invalid number. Try again.\n";
            }
        }
    }
    return value;
}

static int read_menu_choice(int minOpt, int maxOpt)
{
    int choice = minOpt;
    bool ok = false;
    while (!ok)
    {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line))
        {
            ok = true; // treat as exit on stream end
            choice = minOpt;
        }
        else
        {
            std::istringstream iss(line);
            int c = 0;
            if ((iss >> c) && c >= minOpt && c <= maxOpt)
            {
                choice = c;
                ok = true;
            }
            else
            {
                std::cout << "Please enter a number between " << minOpt << " and " << maxOpt << ".\n";
            }
        }
    }
    return choice;
}

// ---------- Singly Linked List menu ----------
static void menu_sll()
{
    SinglyLinkedList<int> list;
    bool running = true;
    while (running)
    {
        std::cout << "\n=== Singly Linked List ===\n"
                     "1) Push Front\n"
                     "2) Push Back\n"
                     "3) Insert After\n"
                     "4) Pop Front\n"
                     "5) Sort (in-place merge)\n"
                     "6) Print\n"
                     "0) Return to Main Menu\n";
        const int choice = read_menu_choice(0, 6);

        if (choice == 1)
        {
            const int x = read_int("Value: ");
            list.push_front(x);
            list.print(std::cout);
            pause_line();
        }
        else if (choice == 2)
        {
            const int x = read_int("Value: ");
            list.push_back(x);
            list.print(std::cout);
            pause_line();
        }
        else if (choice == 3)
        {
            const int x = read_int("Insert after (existing value): ");
            const int y = read_int("New value: ");
            if (!list.insert_after(x, y))
            {
                std::cout << "Value " << x << " not found.\n";
            }
            list.print(std::cout);
            pause_line();
        }
        else if (choice == 4)
        {
            if (!list.pop_front())
            {
                std::cout << "(empty)\n";
            }
            list.print(std::cout);
            pause_line();
        }
        else if (choice == 5)
        {
            list.sort();
            list.print(std::cout);
            pause_line();
        }
        else if (choice == 6)
        {
            list.print(std::cout);
            pause_line();
        }
        else /* 0 */
        {
            running = false;
        }
    }
}

// ---------- Doubly Linked List menu ----------
static void menu_dll()
{
    DoublyLinkedList<int> list;
    bool running = true;
    while (running)
    {
        std::cout << "\n=== Doubly Linked List ===\n"
                     "1) Push Back\n"
                     "2) Insert Before\n"
                     "3) Erase\n"
                     "4) Sort (in-place merge)\n"
                     "5) Print Forward\n"
                     "6) Print Backward\n"
                     "0) Return to Main Menu\n";
        const int choice = read_menu_choice(0, 6);

        if (choice == 1)
        {
            const int x = read_int("Value: ");
            list.push_back(x);
            list.print_forward(std::cout);
            list.print_backward(std::cout);
            pause_line();
        }
        else if (choice == 2)
        {
            const int x = read_int("Insert before (existing value): ");
            const int y = read_int("New value: ");
            if (!list.insert_before(x, y))
            {
                std::cout << "Value " << x << " not found.\n";
            }
            list.print_forward(std::cout);
            list.print_backward(std::cout);
            pause_line();
        }
        else if (choice == 3)
        {
            const int x = read_int("Erase value: ");
            if (!list.erase(x))
            {
                std::cout << "Value " << x << " not found.\n";
            }
            list.print_forward(std::cout);
            list.print_backward(std::cout);
            pause_line();
        }
        else if (choice == 4)
        {
            list.sort();
            list.print_forward(std::cout);
            list.print_backward(std::cout);
            pause_line();
        }
        else if (choice == 5)
        {
            list.print_forward(std::cout);
            pause_line();
        }
        else if (choice == 6)
        {
            list.print_backward(std::cout);
            pause_line();
        }
        else /* 0 */
        {
            running = false;
        }
    }
}

// ---------- BST menu ----------
static void menu_bst()
{
    BinarySearchTree<char> bst;
    bool running = true;
    while (running)
    {
        std::cout << "\n=== Binary Search Tree ===\n"
                     "1) Insert Node\n"
                     "2) Search Node\n"
                     "3) Display ASCII Tree\n"
                     "4) Autorun Preset (F B G A D I C E H)\n"
                     "0) Return to Main Menu\n";
        const int choice = read_menu_choice(0, 4);

        if (choice == 1)
        {
            std::cout << "Value (single character): ";
            std::string line;
            char x = 0;
            if (std::getline(std::cin, line) && !line.empty())
            {
                x = line[0];
            }
            bst.insert(x, true);
            pause_line();
        }
        else if (choice == 2)
        {
            std::cout << "Search for (single character): ";
            std::string line;
            char x = 0;
            if (std::getline(std::cin, line) && !line.empty())
            {
                x = line[0];
            }
            const bool f = bst.search(x, true);
            std::cout << (f ? "found\n" : "not found\n");
            pause_line();
        }
        else if (choice == 3)
        {
            bst.print_ascii(std::cout);
            pause_line();
        }
        else if (choice == 4)
        {
            std::cout << "Loading preset sequence: F B G A D I C E H\n\n";
            const char seq[] = {'F', 'B', 'G', 'A', 'D', 'I', 'C', 'E', 'H'};
            std::size_t i = 0;
            while (i < sizeof(seq) / sizeof(seq[0]))
            {
                bst.insert(seq[i], true);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                ++i;
            }
            std::cout << "Search path trace for 'E':\n";
            const bool f = bst.search('E', true);
            std::cout << (f ? "found\n" : "not found\n");
            pause_line();
        }
        else /* 0 */
        {
            running = false;
        }
    }
}

// ---------- Performance routines (unchanged core; table + perf log) ----------
static void sorting_perf()
{
    using namespace algo;
    const std::size_t N = 50000;
    std::cout << "Generating " << N << " ints...\n";
    std::vector<int> base = make_random_ints(N, -1000000, 1000000, 42u);

    std::vector<int> v1 = base;
    std::vector<int> v2 = base;
    std::vector<int> v3 = base;

    const long long t1 = time_ms([&] { merge_sort(v1); });
    const long long t2 = time_ms([&] { quick_sort(v2); });
    const long long t3 = time_ms([&] { std::sort(v3.begin(), v3.end()); });

    std::cout << "\n+---------------+-----------+\n";
    std::cout << "| Algorithm     | Time (ms) |\n";
    std::cout << "+---------------+-----------+\n";
    std::cout << "| Merge Sort    | " << t1 << "\n";
    std::cout << "| Quick Sort    | " << t2 << "\n";
    std::cout << "| std::sort     | " << t3 << "\n";
    std::cout << "+---------------+-----------+\n\n";

    perflog::append_header("Sorting Performance (N=50000)");
    perflog::append_row("Merge Sort", t1);
    perflog::append_row("Quick Sort", t2);
    perflog::append_row("std::sort", t3);
    perflog::append_rule();

    pause_line();
}

static void searching_perf()
{
    using namespace algo;
    const std::size_t N = 50000;
    std::vector<int> v = make_random_ints(N, -1000000, 1000000, 777u);
    std::sort(v.begin(), v.end());
    const int key = v[N / 2];

    const long long tl = time_ms(
        [&]
        {
            int i = 0;
            while (i < 100)
            {
                (void) linear_search(v, key, false);
                ++i;
            }
        });
    const long long tb = time_ms(
        [&]
        {
            int i = 0;
            while (i < 100)
            {
                (void) binary_search_trace(v, key, false);
                ++i;
            }
        });

    std::cout << "\n+----------------------+-----------+\n";
    std::cout << "| Search (100x)        | Time (ms) |\n";
    std::cout << "+----------------------+-----------+\n";
    std::cout << "| Linear Search        | " << tl << "\n";
    std::cout << "| Binary Search        | " << tb << "\n";
    std::cout << "+----------------------+-----------+\n\n";

    perflog::append_header("Searching Performance (100x)");
    perflog::append_row("Linear Search", tl);
    perflog::append_row("Binary Search", tb);
    perflog::append_rule();

    std::cout << "Trace demo for key=" << key << ":\n";
    (void) binary_search_trace(v, key, true);

    pause_line();
}

// ---------- Program entry ----------
int main()
{
    logsys::init();

    bool running = true;
    while (running)
    {
        std::cout << "\n=== Data Structures & Algorithms Demo (v3.7) ===\n"
                     "1) Singly Linked List\n"
                     "2) Doubly Linked List\n"
                     "3) Binary Search Tree\n"
                     "4) Sorting Performance\n"
                     "5) Searching Performance\n"
                     "0) Exit\n";
        const int choice = read_menu_choice(0, 5);

        if (choice == 1)
        {
            menu_sll();
        }
        else if (choice == 2)
        {
            menu_dll();
        }
        else if (choice == 3)
        {
            menu_bst();
        }
        else if (choice == 4)
        {
            sorting_perf();
        }
        else if (choice == 5)
        {
            searching_perf();
        }
        else /* 0 */
        {
            running = false;
        }
    }

    logsys::close();
    return 0;
}
