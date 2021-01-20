#pragma once

#include <cstdio>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

template <typename N, typename M>
inline std::ostream& operator<<(std::ostream& file, const std::pair<N, M>& V);

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::vector<N>& V);

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::set<N>& S);

template <typename N, typename A>
inline std::ostream& operator<<(std::ostream& file, const std::map<N, A>& S);

//===========================================================
//===========================================================
// file << std::pair : print a std::pair on a stream
//===========================================================
//===========================================================

template <typename N, typename M>
inline std::ostream& operator<<(std::ostream& file, const std::pair<N, M>& V)
{
    return file << "std::pair{" << V.first << ", " << V.second << "}";
}

//===========================================================
//===========================================================
// file << std::vector : print a std::vector on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::vector<N>& V)
{
    std::string sep = "";

    file << "std::vector{";
    for (const N& e : V) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

//===========================================================
//===========================================================
// file << std::set : print a std::set on a stream
//===========================================================
//===========================================================

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const std::set<N>& S)
{
    std::string sep = "";

    file << "std::set{";
    for (const N& e : S) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

//===========================================================
//===========================================================
// file << std::map : print a std::map on a stream
//===========================================================
//===========================================================

template <typename N, typename A>
inline std::ostream& operator<<(std::ostream& file, const std::map<N, A>& S)
{
    std::string sep = "";

    file << "std::map{";
    for (const std::pair<N, A>& e : S) {
        file << sep << e;
        sep = ", ";
    }
    return file << "}";
}

template <typename A>
class arrow_traits
{
    static int         combine(int x, int y);
    static int         empty();
    static bool        isEmpty(int d);
    static int         mindist(int d);
    static std::string label(int d);
};

template <>
struct arrow_traits<int> {
    static int         combine(int x, int y) { return (x < y) ? x : y; }
    static int         empty() { return INT32_MAX; }
    static bool        isEmpty(int d) { return d == INT32_MAX; }
    static int         mindist(int d) { return d; }
    static std::string label(int d) { return std::to_string(d); }
};

using multidep = std::pair<std::map<std::string, int>, int>;

inline multidep mdep(std::string s) { return {{{s, 0}}, 0}; }
inline multidep mdep(std::string s, int d) { return {{{s, d}}, d}; }

template <>
struct arrow_traits<multidep> {
    static std::string label(const multidep& M)
    {
        std::stringstream sn;
        std::string       sep = "";
        for (const auto& d : M.first) {
            sn << sep << d.first << ":" << d.second;
            sep = " ";
        }
        return sn.str();
    }
    static multidep combine(const multidep& X, const multidep& Y)
    {
        // std::cerr << "combine " << label(X) << " + " << label(Y) << std::endl;
        multidep M;
        auto     itx = X.first.begin();
        auto     ity = Y.first.begin();
        while ((itx != X.first.end()) && (ity != Y.first.end())) {
            if (itx->first < ity->first) {
                M.first[itx->first] = itx->second;
                itx++;
            } else if (ity->first < itx->first) {
                M.first[ity->first] = ity->second;
                ity++;
            } else {
                M.first[ity->first] = std::min(itx->second, ity->second);
                itx++;
                ity++;
            }
        }
        while (itx != X.first.end()) {
            M.first[itx->first] = itx->second;
            itx++;
        }
        while (ity != Y.first.end()) {
            M.first[ity->first] = ity->second;
            ity++;
        }
        M.second = std::min(X.second, Y.second);
        // std::cerr << "combine " << label(X) << " + " << label(Y) << " = " << label(M) <<
        // std::endl;
        return M;
    }

    static multidep empty() { return {{}, INT32_MAX}; }
    static bool     isEmpty(const multidep& M) { return M.first.size() == 0; }
    static int      mindist(const multidep& M) { return M.second; }
};
