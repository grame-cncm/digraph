#pragma once

#include <cstdio>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <set>
#include <stack>

template <typename A>
class arrow_traits
{
};

template <>
struct arrow_traits<int> {
    static int  combine(int x, int y) { return (x < y) ? x : y; }
    static int  empty() { return INT32_MAX; }
    static bool isEmpty(int d) { return d == INT32_MAX; }
    static int  mindist(int d) { return d; }
};

using multidep = std::map<std::string, int>;

template <>
struct arrow_traits<multidep> {
    static multidep combine(const multidep& X, const multidep& Y)
    {
        multidep M;
        auto     itx = X.begin();
        auto     ity = Y.begin();
        while ((itx != X.end()) && (ity != Y.end())) {
            if (itx->first < ity->first) {
                M[itx->first] = itx->second;
            } else if (itx->first > ity->first) {
                M[ity->first] = ity->second;
            } else {
                M[ity->first] = std::min(itx->second, ity->second);
            }
            itx++;
            ity++;
        }
        while (itx != X.end()) {
            M[itx->first] = itx->second;
            itx++;
        }
        while (ity != Y.end()) {
            M[ity->first] = ity->second;
            ity++;
        }
        return M;
    }

    static multidep empty() { return {}; }
    static bool     isEmpty(const multidep& m) { return m.size() == 0; }
    static int      mindist(const multidep& m)
    {
        // TODO: use a cache instead of recompute the value
        int md = INT32_MAX;
        for (const auto& e : m) {
            if (e.second < md) md = e.second;
        }
        return md;
    }
};
