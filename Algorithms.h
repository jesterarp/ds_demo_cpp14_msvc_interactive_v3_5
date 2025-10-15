// Algorithms.h
// C++14 utilities: merge sort, quick sort, timing, searches
// DO-178B/C: strict single-return-per-function

#pragma once
#include <vector>
#include <chrono>
#include <functional>
#include <random>
#include <algorithm>
#include <iostream>
#include <cstddef>

namespace algo
{
    template <typename F>
    long long time_ms(F f)
    {
        long long result = 0;
        auto start = std::chrono::high_resolution_clock::now();
        f();
        auto end = std::chrono::high_resolution_clock::now();
        result = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        return result;
    }

    inline std::vector<int> make_random_ints(std::size_t n, int lo, int hi, unsigned seed = 12345u)
    {
        std::vector<int> v;
        v.reserve(n);
        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> dist(lo, hi);
        std::size_t i = 0;
        while (i < n)
        {
            v.push_back(dist(rng));
            ++i;
        }
        return v;
    }

    inline void merge(std::vector<int> &a, int l, int m, int r, std::vector<int> &tmp)
    {
        int i = l;
        int j = m + 1;
        int k = l;
        while (i <= m && j <= r)
        {
            if (a[i] <= a[j]) { tmp[k] = a[i]; ++k; ++i; }
            else { tmp[k] = a[j]; ++k; ++j; }
        }
        while (i <= m) { tmp[k] = a[i]; ++k; ++i; }
        while (j <= r) { tmp[k] = a[j]; ++k; ++j; }
        int t = l;
        while (t <= r) { a[t] = tmp[t]; ++t; }
    }

    inline void merge_sort_impl(std::vector<int> &a, int l, int r, std::vector<int> &tmp)
    {
        bool doWork = (l < r);
        if (doWork)
        {
            int m = l + (r - l) / 2;
            merge_sort_impl(a, l, m, tmp);
            merge_sort_impl(a, m + 1, r, tmp);
            merge(a, l, m, r, tmp);
        }
    }

    inline void merge_sort(std::vector<int> &a)
    {
        bool doWork = !a.empty();
        if (doWork)
        {
            std::vector<int> tmp(a.size());
            merge_sort_impl(a, 0, static_cast<int>(a.size()) - 1, tmp);
        }
    }

    inline int partition(std::vector<int> &a, int l, int r)
    {
        int result = 0;
        int pivot = a[r];
        int i = l - 1;
        int j = l;
        while (j < r)
        {
            if (a[j] <= pivot)
            {
                ++i;
                std::swap(a[i], a[j]);
            }
            ++j;
        }
        std::swap(a[i + 1], a[r]);
        result = i + 1;
        return result;
    }

    inline void quick_sort_impl(std::vector<int> &a, int l, int r)
    {
        bool doWork = (l < r);
        if (doWork)
        {
            int p = partition(a, l, r);
            quick_sort_impl(a, l, p - 1);
            quick_sort_impl(a, p + 1, r);
        }
    }

    inline void quick_sort(std::vector<int> &a)
    {
        bool doWork = !a.empty();
        if (doWork)
        {
            quick_sort_impl(a, 0, static_cast<int>(a.size()) - 1);
        }
    }

    inline int linear_search(const std::vector<int> &a, int key, bool trace = false)
    {
        int index = -1;
        std::size_t i = 0;
        while (i < a.size() && index == -1)
        {
            if (trace) { std::cout << "check a[" << i << "]=" << a[i] << "\n"; }
            if (a[i] == key) { index = static_cast<int>(i); }
            ++i;
        }
        return index;
    }

    inline int binary_search_trace(const std::vector<int> &a, int key, bool trace = false)
    {
        int result = -1;
        int lo = 0;
        int hi = static_cast<int>(a.size()) - 1;
        while (lo <= hi && result == -1)
        {
            int mid = lo + (hi - lo) / 2;
            if (trace) { std::cout << "lo=" << lo << " mid=" << mid << " hi=" << hi << " a[mid]=" << a[mid] << "\n"; }
            if (a[mid] == key) { result = mid; }
            else if (a[mid] < key) { lo = mid + 1; }
            else { hi = mid - 1; }
        }
        return result;
    }
}
