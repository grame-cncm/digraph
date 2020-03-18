/*******************************************************************************
********************************************************************************

    schedule : ordered set of elements

    Created by Yann Orlarey on 17/03/2020.
    Copyright © 2017 Grame. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once

#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "digraph.hh"
#include "digraphop.hh"

/**
 * @brief a schedule S is an ordered set of elements of type N
 *
 * @tparam N
 */
template <typename N>
class schedule
{
   private:
    std::vector<N>   fElements;  // ordered set of elements
    std::map<N, int> fOrder;  // order of each element (starting at 1, 0 indicates not in schedule)

   public:
    // append a new element to a schedule
    schedule& append(const N& n)
    {
        if (fOrder[n] > 0) {
            std::cerr << "WARNING, already scheduled" << std::endl;
        } else {
            fElements.push_back(n);
            fOrder[n] = fElements.size();
        }
        return *this;
    }

    // number of elements in the schedule
    int size() { return fElements.size(); }

    // the vector of elements (for iterations)
    const std::vector<N>& elements() const { return fElements; }

    // the order of an element in the schedule (starting from 1)
    int order(const N& n) const
    {
        auto it = fOrder.find(n);
        return (it == fOrder.end()) ? 0 : it->second;
    }
};

template <typename N>
inline std::ostream& operator<<(std::ostream& file, const schedule<N>& g)
{
    std::string sep = "";

    file << "Schedule {";
    for (const N& n : g.elements()) {
        file << sep << g.order(n) << ":" << n;
        sep = ", ";
    }
    return file << "}";
}

// Deep-first scheduling

template <typename N>
inline schedule<N> dfschedule(const digraph<N>& G)
{
    schedule<N> S;
    std::set<N> V;  // set of visited nodes

    //    std::function<void(const N&)> dfvisit = [&dfvisit, &G, &S, &V](const N& n) {
    std::function<void(const N&)> dfvisit = [&](const N& n) {
        if (V.find(n) == V.end()) {
            V.insert(n);
            for (const auto& p : G.connections(n)) { dfvisit(p.first); }
            S.append(n);
        }
    };

    for (const auto& n : roots(G)) dfvisit(n);

    return S;
}

// Breadth-first scheduling

template <typename N>
inline schedule<N> bfschedule(const digraph<N>& G)
{
    std::vector<std::vector<N>> P = parallelize(G);
    schedule<N>                 S;

    for (unsigned int i = 0; i < P.size(); i++) {
        for (const N& n : P[i]) S.append(n);
    }
    return S;
}

// compute the distance of a graph scheduling

template <typename N>
inline int schedulingcost(const digraph<N>& G, const schedule<N>& S)
{
    int cost = 0;
    for (const N& n : G.nodes()) {
        int o = S.order(n);
        for (const auto& c : G.connections(n)) {
            assert(o > S.order(c.first));
            cost += (o - S.order(c.first));
        }
    }
    return cost;
}
