//
//  tests.cpp
//  graphlib
//
//  Created by Yann Orlarey on 06/02/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include "mtests.hh"
#include "arrow.hh"

bool mcheck(const std::string& testname, const std::string& testvalue,
            const std::string& expectedvalue)
{
    bool ok = (0 == expectedvalue.compare(testvalue));
    if (ok) {
        std::cout << testname << " SUCCEDED " << std::endl;
    } else {
        std::cout << testname << " FAILED " << std::endl;
        std::cout << "We got     [[" << testvalue << "]]" << std::endl;
        std::cout << "instead of [[" << expectedvalue << "]]" << std::endl;
    }
    return ok;
}

std::string mtest0()
{
    digraph<char, multidep> g;
    g.add('A', 'B', mdep("M"))
        .add('B', 'C', mdep("M", 1))
        .add('C', 'A', mdep("M"))
        .add('D', 'B', mdep("M"))
        .add('D', 'C', mdep("M"))
        .add('D', 'E', mdep("M", 1))
        .add('E', 'D', mdep("M"))
        .add('E', 'F', mdep("M"))
        .add('F', 'G', mdep("M"))
        .add('G', 'F', mdep("M", 1))
        .add('H', 'G', mdep("M"))
        .add('H', 'E', mdep("M"))
        .add('H', 'H', mdep("M", 1));

    std::stringstream ss;
    ss << "g = " << g;
    return ss.str();
}

std::string mres0()
{
    return "g = Graph {A-std::pair{std::map{std::pair{M, 0}}, 0}->B, "
           "B-std::pair{std::map{std::pair{M, 1}}, 1}->C, C-std::pair{std::map{std::pair{M, 0}}, "
           "0}->A, D-std::pair{std::map{std::pair{M, 0}}, 0}->B, D-std::pair{std::map{std::pair{M, "
           "0}}, 0}->C, D-std::pair{std::map{std::pair{M, 1}}, 1}->E, "
           "E-std::pair{std::map{std::pair{M, 0}}, 0}->D, E-std::pair{std::map{std::pair{M, 0}}, "
           "0}->F, F-std::pair{std::map{std::pair{M, 0}}, 0}->G, G-std::pair{std::map{std::pair{M, "
           "1}}, 1}->F, H-std::pair{std::map{std::pair{M, 0}}, 0}->E, "
           "H-std::pair{std::map{std::pair{M, 0}}, 0}->G, H-std::pair{std::map{std::pair{M, 1}}, "
           "1}->H}";
}

bool mcheck0() { return mcheck("mtest0", mtest0(), mres0()); }

//===================================================================================

std::string mtest1()
{
    digraph<char, multidep> g;
    g.add('A', 'B', mdep("M"))
        .add('B', 'C', mdep("M"))
        .add('C', 'A', mdep("M"))
        .add('D', 'B', mdep("M"))
        .add('D', 'C', mdep("M"))
        .add('D', 'E', mdep("M"))
        .add('E', 'D', mdep("M"))
        .add('E', 'F', mdep("M"))
        .add('F', 'G', mdep("M"))
        .add('G', 'F', mdep("M"))
        .add('H', 'G', mdep("M"))
        .add('H', 'E', mdep("M"))
        .add('H', 'H', mdep("M"));

    std::stringstream ss;
    ss << "Tarjan partition of g = ";
    Tarjan<char, multidep> tarj(g);
    for (const auto& cycle : tarj.partition()) {
        ss << "group{ ";
        for (const auto& n : cycle) { ss << n << " "; }
        ss << "} ";
    }
    return ss.str();
}

std::string mres1()
{
    return "Tarjan partition of g = group{ A B C } group{ D E } group{ F G } group{ H } ";
}

bool mcheck1() { return mcheck("mtest1", mtest1(), mres1()); }

//===================================================================================

std::string mtest2()
{
    digraph<char, multidep> g;
    g.add('A', 'B', mdep("M", 2))
        .add('A', 'B', mdep("M", 1))
        .add('A', 'B', mdep("N", 0))
        .add('B', 'C', mdep("M"))
        .add('C', 'A', mdep("M"))
        .add('D', 'B', mdep("M"))
        .add('D', 'C', mdep("M"))
        .add('D', 'E', mdep("M"))
        .add('E', 'D', mdep("M"))
        .add('E', 'F', mdep("M"))
        .add('F', 'G', mdep("M"))
        .add('G', 'F', mdep("M"))
        .add('H', 'G', mdep("M"))
        .add('H', 'E', mdep("M"))
        .add('H', 'H', mdep("M"));

    std::stringstream ss;
    ss << "g = " << g;
    return ss.str();
}

std::string mres2()
{
    return "g = Graph {A-std::pair{std::map{std::pair{M, 1}, std::pair{N, 0}}, 0}->B, "
           "B-std::pair{std::map{std::pair{M, 0}}, 0}->C, C-std::pair{std::map{std::pair{M, 0}}, "
           "0}->A, D-std::pair{std::map{std::pair{M, 0}}, 0}->B, D-std::pair{std::map{std::pair{M, "
           "0}}, 0}->C, D-std::pair{std::map{std::pair{M, 0}}, 0}->E, "
           "E-std::pair{std::map{std::pair{M, 0}}, 0}->D, E-std::pair{std::map{std::pair{M, 0}}, "
           "0}->F, F-std::pair{std::map{std::pair{M, 0}}, 0}->G, G-std::pair{std::map{std::pair{M, "
           "0}}, 0}->F, H-std::pair{std::map{std::pair{M, 0}}, 0}->E, "
           "H-std::pair{std::map{std::pair{M, 0}}, 0}->G, H-std::pair{std::map{std::pair{M, 0}}, "
           "0}->H}";
}

bool mcheck2() { return mcheck("mtest2", mtest2(), mres2()); }

//===================================================================================

std::string mtest3()
{
    digraph<char, multidep> g;
    g.add('A', 'B', mdep("Y", 1))
        .add('A', 'B', mdep("Y", 2))
        .add('B', 'C', mdep("Q"))
        .add('C', 'A', mdep("X"))
        .add('D', 'B', mdep("M"))
        .add('D', 'C', mdep("M", 2))
        .add('D', 'E', mdep("M"))
        .add('E', 'D', mdep("N", 1));

    std::stringstream ss;
    ss << "g = " << g;
    return ss.str();
}

std::string mres3() { return "g = "; }

bool mcheck3() { return mcheck("mtest3", mtest3(), mres3()); }
