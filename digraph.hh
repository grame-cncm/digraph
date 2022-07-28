/*******************************************************************************
********************************************************************************

    digraph : directed graph

    Created by Yann Orlarey on 31/01/2017.
    Copyright © 2017 Grame. All rights reserved.

 *******************************************************************************
 ******************************************************************************/

#pragma once

#include <cstdio>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stack>

//===========================================================
// digraph : a directed graph, a set of nodes f type N and a
// set of connections between these nodes. Connections have an
// associated value, by defaut 0. This value is used in Faust
// to represent the time dependency between computations.
//===========================================================

template <typename N>
class digraph {
    using TDestinations = std::map<N, std::set<int>>;

    //--------------------------------------------------------------------------
    // Real/internal structure of a graph. A graph is a set of nodes
    // and a set of connections between theses nodes. These connections
    // have integer values attached.
    class internalgraph {
       private:
        std::set<N>                fNodes;        // {n1,n2,...}
        std::map<N, TDestinations> fConnections;  // {(ni -d-> nj),...}

       public:
#if 0
        internalgraph() { std::cout << "create internalgraph " << this << std::endl; }
        ~internalgraph() { std::cout << "delete internalgraph " << this << std::endl; }
#endif
        // Add the node n to the graph
        void add(N n)
        {
            fNodes.insert(n);
            (void)fConnections[n];  // make sure we have an empty set of connections for n
        }

        // Add the nodes n1 and n2 and the connection (n1 -d-> n2) to the graph.
        // Multiple connections are allowed. But multiple connections with the same value
        // are only counted once.
        void add(const N& n1, const N& n2, int d = 0)
        {
            add(n1);
            add(n2);
            fConnections[n1][n2].insert(d);
        }

        // returns the set of nodes of the graph
        const std::set<N>& nodes() const
        {
            return fNodes;
        }

        // Returns the destinations of node n in the graph
        const TDestinations& destinations(const N& n) const
        {
            return fConnections.at(n);
        }

        // Tests if two nodes are connected. Returns in d the
        // smallest connection value.
        bool areConnected(const N& n1, const N& n2, int& d) const
        {
            const TDestinations& dst = fConnections.at(n1);
            auto                 q   = dst.find(n2);
            if (q != dst.end()) {
                // search for the smallest connection value
                d = INT_MAX;
                for (int v : q->second) {
                    if (v < d) {
                        d = v;
                    }
                }
                return true;
            } else {
                return false;
            }
        }

        // tests if two nodes are connected
        bool areConnected(const N& n1, const N& n2) const
        {
            const TDestinations& dst = fConnections.at(n1);
            return dst.find(n2) != dst.end();
        }
    };

    std::shared_ptr<internalgraph> fContent = std::make_shared<internalgraph>();

   public:
    // Add the node n to the graph
    digraph& add(N n)
    {
        fContent->add(n);
        return *this;
    }

    // Add the graph g to the graph.
    digraph& add(const digraph& g)
    {
        for (auto& n : g.nodes()) {
            add(n);
            for (auto& c : g.connections(n)) {
                add(n, c.first, c.second);
            }
        }
        return *this;
    }

    // Add the nodes n1 and n2 and the connection (n1 -d-> n2) to the graph.
    digraph& add(const N& n1, const N& n2, int d = 0)
    {
        fContent->add(n1, n2, d);
        return *this;
    }

    // returns the set of nodes of the graph
    const std::set<N>& nodes() const
    {
        return fContent->nodes();
    }
    //
    const TDestinations& destinations(const N& n) const
    {
        return fContent->destinations(n);
    }

    bool areConnected(const N& n1, const N& n2, int& d) const
    {
        return fContent->areConnected(n1, n2, d);
    }
    bool areConnected(const N& n1, const N& n2) const
    {
        return fContent->areConnected(n1, n2);
    }

    // compare graphs for maps and other containers

    friend bool operator<(const digraph& p1, const digraph& p2)
    {
        return p1.fContent < p2.fContent;
    }
    friend bool operator==(const digraph& p1, const digraph& p2)
    {
        return p1.fContent == p2.fContent;
    }
};
