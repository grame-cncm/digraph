//
//  tests.cpp
//  graphlib
//
//  Created by Yann Orlarey on 06/02/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include "tests.hh"

#include "dglib/digraph.hh"
#include "dglib/digraphop.hh"
#include "dglib/schedule.hh"

void test0(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 1)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 1)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 1)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 1);

    ss << "g = " << g;
}

std::string res0()
{
    return "g = Graph {A-0->B, B-1->C, C-0->A, D-0->B, D-0->C, D-1->E, E-0->D, E-0->F, F-0->G, "
           "G-1->F, H-0->E, "
           "H-0->G, H-1->H}";
}

bool check0()
{
    std::stringstream ss;
    test0(ss);
    bool ok = (0 == ss.str().compare(res0()));
    if (ok) {
        std::cout << "test0 OK " << std::endl;
    } else {
        std::cout << "test0 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res0() << std::endl;
    }
    return ok;
}

void test1(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 0)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 0)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 0)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 0);

    ss << "Tarjan partition of g = ";
    Tarjan<char> tarj(g);
    for (const auto& cycle : tarj.partition()) {
        ss << "group{ ";
        for (const auto& n : cycle) { ss << n << " "; }
        ss << "} ";
    }
}

std::string res1()
{
    return "Tarjan partition of g = group{ A B C } group{ D E } group{ F G } group{ H } ";
}

bool check1()
{
    std::stringstream ss;
    test1(ss);
    bool ok = (0 == ss.str().compare(res1()));
    if (ok) {
        std::cout << "test1 OK " << std::endl;
    } else {
        std::cout << "test1 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res1() << std::endl;
    }
    return ok;
}

void test2(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 1)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 1)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 1)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 1);

    ss << "dag of g = " << graph2dag(g);
}

std::string res2()
{
    return "dag of g = Graph {Graph {H-1->H}-0->Graph {F-0->G, G-1->F}, Graph {H-1->H}-0->Graph "
           "{D-1->E, "
           "E-0->D}, Graph {F-0->G, G-1->F}, Graph {D-1->E, E-0->D}-0->Graph {F-0->G, G-1->F}, "
           "Graph {D-1->E, E-0->D}-0->Graph {A-0->B, B-1->C, C-0->A}, Graph {A-0->B, B-1->C, "
           "C-0->A}}";
}

bool check2()
{
    std::stringstream ss;
    test2(ss);
    bool ok = (0 == ss.str().compare(res2()));
    if (ok) {
        std::cout << "test2 OK " << std::endl;
    } else {
        std::cout << "test2 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res2() << std::endl;
    }
    return ok;
}

void test3(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 1)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 1)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 1)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 1);

    auto h1 = cut(g, 64);     // cut vectorsize connections
    auto h2 = graph2dag(h1);  // find cycles
    auto h3 = mapnodes<digraph<char>, digraph<char>>(
        h2, [](const digraph<char>& gr) -> digraph<char> { return cut(gr, 1); });
    ss << "test3: h3= " << h3;
}

std::string res3()
{
    return "test3: h3= Graph {Graph {A-0->B, B, C-0->A}, Graph {D, E-0->D}-0->Graph {A-0->B, B, "
           "C-0->A}, Graph {D, E-0->D}-0->Graph {F-0->G, G}, Graph {H}-0->Graph {D, E-0->D}, Graph "
           "{H}-0->Graph {F-0->G, G}, Graph {F-0->G, G}}";
}

bool check3()
{
    std::stringstream ss;
    test3(ss);
    bool ok = (0 == ss.str().compare(res3()));
    if (ok) {
        std::cout << "test3 OK " << std::endl;
    } else {
        std::cout << "test3 FAIL " << std::endl;
        std::cout << "We got     \"" << ss.str() << '"' << std::endl;
        std::cout << "instead of \"" << res3() << '"' << std::endl;
    }
    return ok;
}

void test4(std::ostream& ss)
{
    digraph<char> g1, g2, g3;
    g1.add('A', 'A', 2);
    g1.add('A', 'D', 1);
    g1.add('A', 'B', 0);

    g2.add('A', 'B', 2);
    g2.add('B', 'B', 1);
    g2.add('A', 'C', 0);

    g3.add(g1).add(g2);

    ss << "test4: g3.add(g1).add(g2) = " << g3;
    // std::cout << "test4: g1= " << g1 << std::endl;
    // std::cout << "test4: g2= " << g2 << std::endl;
    // std::cout << "test4: g3= " << g3 << std::endl;
}

std::string res4()
{
    return "test4: g3.add(g1).add(g2) = Graph {A-2->A, A-0->B, A-0->C, A-1->D, B-1->B, C, D}";
};

bool check4()
{
    std::stringstream ss;
    test4(ss);
    bool ok = (0 == ss.str().compare(res4()));
    if (ok) {
        std::cout << "test4 OK " << std::endl;
    } else {
        std::cout << "test4 FAIL " << std::endl;
        std::cout << "We got     \"" << ss.str() << '"' << std::endl;
        std::cout << "instead of \"" << res4() << '"' << std::endl;
    }
    return ok;
}

// Test separation of graphs
void test5(std::ostream& ss)
{
    digraph<char> g1, g2, g3;

    g1.add('A', 'Z', 0);
    g1.add('A', 'B', 0);
    g1.add('B', 'C', 0);
    g1.add('C', 'A', 1);

    g1.add('Z', 'W', 0);
    g1.add('W', 'Z', 1);

    g1.add('A', 'Z', 0);
    g1.add('W', 'C', 1);

    splitgraph<char>(
        g1, [](const char& c) { return c < 'K'; }, g2, g3);

    ss << "test5: g1 = " << g1 << "; g2 = " << g2 << "; g3 = " << g3;
}

std::string res5()
{
    return "test5: g1 = Graph {A-0->B, A-0->Z, B-0->C, C-1->A, W-1->C, W-1->Z, Z-0->W}; g2 = Graph "
           "{A-0->B, "
           "B-0->C, C-1->A}; g3 = Graph {W-1->Z, Z-0->W}";
};

bool check5()
{
    std::stringstream ss;
    test5(ss);
    bool ok = (0 == ss.str().compare(res5()));
    if (ok) {
        std::cout << "test5 OK " << std::endl;
    } else {
        std::cout << "test5 FAIL " << std::endl;
        std::cout << "We got     \"" << ss.str() << '"' << std::endl;
        std::cout << "instead of \"" << res5() << '"' << std::endl;
    }
    return ok;
}

void test7(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 1)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 1)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 1)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 1);

    auto h  = graph2dag(g);     // on fait un dag dont les noeuds sont les cycles du graphe g
    auto p  = parallelize(h);   //
    auto rp = rparallelize(h);  //
    auto s  = serialize(h);     //

    ss << "test7:        g = " << g << "; ";
    ss << "number of cycles: " << cycles(g) << "; ";
    ss << "0-cycles        : " << cycles(cut(g, 1)) << "; ";
    ss << "graph2dag(g)    = " << h << "; ";
    ss << "parallelize(h)  = " << p << "; ";
    ss << "rparallelize(h)  = " << rp << "; ";
    ss << "serialize(h)    = " << s << "; ";

    dotfile(ss, g);
}

std::string res7()
{
    return "test7:        g = Graph {A-0->B, B-1->C, C-0->A, D-0->B, D-0->C, D-1->E, E-0->D, "
           "E-0->F, F-0->G, G-1->F, H-0->E, H-0->G, H-1->H}; number of cycles: 4; 0-cycles        "
           ": 0; graph2dag(g)    = Graph {Graph {F-0->G, G-1->F}, Graph {A-0->B, B-1->C, C-0->A}, "
           "Graph {H-1->H}-0->Graph {F-0->G, G-1->F}, Graph {H-1->H}-0->Graph {D-1->E, E-0->D}, "
           "Graph {D-1->E, E-0->D}-0->Graph {F-0->G, G-1->F}, Graph {D-1->E, E-0->D}-0->Graph "
           "{A-0->B, B-1->C, C-0->A}}; parallelize(h)  = std::vector{std::vector{Graph {F-0->G, "
           "G-1->F}, Graph {A-0->B, B-1->C, C-0->A}}, std::vector{Graph {D-1->E, E-0->D}}, "
           "std::vector{Graph {H-1->H}}}; rparallelize(h)  = std::vector{std::vector{Graph "
           "{H-1->H}}, std::vector{Graph {D-1->E, E-0->D}}, std::vector{Graph {F-0->G, G-1->F}, "
           "Graph {A-0->B, B-1->C, C-0->A}}}; serialize(h)    = std::vector{Graph {F-0->G, "
           "G-1->F}, Graph {A-0->B, B-1->C, C-0->A}, Graph {D-1->E, E-0->D}, Graph {H-1->H}}; "
           "digraph mygraph {"
           "\n\t\"A\"->\"B\" [label=\"0\"];"
           "\n\t\"B\"->\"C\" [label=\"1\"];"
           "\n\t\"C\"->\"A\" [label=\"0\"];"
           "\n\t\"D\"->\"B\" [label=\"0\"];"
           "\n\t\"D\"->\"C\" [label=\"0\"];"
           "\n\t\"D\"->\"E\" [label=\"1\"];"
           "\n\t\"E\"->\"D\" [label=\"0\"];"
           "\n\t\"E\"->\"F\" [label=\"0\"];"
           "\n\t\"F\"->\"G\" [label=\"0\"];"
           "\n\t\"G\"->\"F\" [label=\"1\"];"
           "\n\t\"H\"->\"E\" [label=\"0\"];"
           "\n\t\"H\"->\"G\" [label=\"0\"];"
           "\n\t\"H\"->\"H\" [label=\"1\"];"
           "\n}\n";
}

bool check7()
{
    std::stringstream ss;
    test7(ss);
    bool ok = (0 == ss.str().compare(res7()));
    if (ok) {
        std::cout << "test7 OK " << std::endl;
    } else {
        std::cout << "test7 FAIL " << std::endl;
        std::cout << "We got     \"" << ss.str() << '"' << std::endl;
        std::cout << "instead of \"" << res7() << '"' << std::endl;
    }
    return ok;
}

void test8(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 0)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 0)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 0)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 0);

    std::set<char> S{'C', 'F'};
    digraph<char>  r = subgraph(g, S);
    ss << "Subgraph(" << g << ", " << S << ") = " << r;
}

std::string res8()
{
    return "Subgraph(Graph {A-0->B, B-0->C, C-0->A, D-0->B, D-0->C, D-0->E, E-0->D, E-0->F, "
           "F-0->G, G-0->F, H-0->E, H-0->G, H-0->H}, std::set{C, F}) = Graph {A-0->B, B-0->C, "
           "C-0->A, F-0->G, G-0->F}";
}

bool check8()
{
    std::stringstream ss;
    test8(ss);
    bool ok = (0 == ss.str().compare(res8()));
    if (ok) {
        std::cout << "test8 OK " << std::endl;
    } else {
        std::cout << "test8 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res8() << std::endl;
    }
    return ok;
}

void test9(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 0)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 0)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 0)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 0);

    std::set<char> S{'H'};
    digraph<char>  r = subgraph(g, S);
    ss << "Subgraph(" << g << ", " << S << ") = " << r;
}

std::string res9()
{
    return "Subgraph(Graph {A-0->B, B-0->C, C-0->A, D-0->B, D-0->C, D-0->E, E-0->D, E-0->F, "
           "F-0->G, G-0->F, H-0->E, H-0->G, H-0->H}, std::set{H}) = Graph {A-0->B, B-0->C, C-0->A, "
           "D-0->B, D-0->C, D-0->E, E-0->D, E-0->F, F-0->G, G-0->F, H-0->E, H-0->G, H-0->H}";
}

bool check9()
{
    std::stringstream ss;
    test9(ss);
    bool ok = (0 == ss.str().compare(res9()));
    if (ok) {
        std::cout << "test9 OK " << std::endl;
    } else {
        std::cout << "test9 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res9() << std::endl;
    }
    return ok;
}

template <typename N>
bool equiv(const digraph<N>& g, const digraph<N>& h)
{
    if (g.nodes() != h.nodes()) {
        return false;
    } else {
        for (const auto& n : g.nodes()) {
            if (g.connections(n) != h.connections(n)) return false;
        }
        return true;
    }
}

bool check10()
{
    digraph<char> g;
    g.add('A', 'B', 0)
        .add('B', 'C', 1)
        .add('C', 'A', 0)
        .add('D', 'B', 0)
        .add('D', 'C', 0)
        .add('D', 'E', 1)
        .add('E', 'D', 0)
        .add('E', 'F', 0)
        .add('F', 'G', 0)
        .add('G', 'F', 1)
        .add('H', 'G', 0)
        .add('H', 'E', 0)
        .add('H', 'H', 1);

    digraph<char> r = reverse(reverse(g));
    if (equiv(g, r)) {
        std::cout << "test10 OK " << std::endl;
        return true;
    } else {
        std::cout << "test10 FAIL " << std::endl;
        std::cout << "We got      " << r << std::endl;
        std::cout << "Instead of  " << g << std::endl;
        return false;
    }
}

void test11(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0).add('B', 'C', 3).add('C', 'D', 0).add('D', 'E', 0);
    g.add('A', 'I', 0).add('I', 'J', 4).add('J', 'E', 5);

    digraph<char> r = chain(g, false);
    ss << "chain(" << g << ", false) = " << r;
}

std::string res11()
{
    return "chain(Graph {A-0->B, A-0->I, B-3->C, C-0->D, D-0->E, E, I-4->J, J-5->E}, false) = "
           "Graph {A, "
           "B-3->C, "
           "C-0->D, D, E, I-4->J, J}";
}

bool check11()
{
    std::stringstream ss;
    test11(ss);
    bool ok = (0 == ss.str().compare(res11()));
    if (ok) {
        std::cout << "test11 OK " << std::endl;
    } else {
        std::cout << "test11 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res9() << std::endl;
    }
    return ok;
}

//=====================================================================

void test12(std::ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B', 0).add('B', 'C', 3).add('C', 'D', 0).add('D', 'E', 0);
    g.add('A', 'I', 0).add('I', 'J', 4).add('J', 'E', 5);

    digraph<char> r = chain(g, true);
    ss << "chain(" << g << ", true) = " << r;
}

std::string res12()
{
    return "chain(Graph {A-0->B, A-0->I, B-3->C, C-0->D, D-0->E, E, I-4->J, J-5->E}, true) = Graph "
           "{B-3->C, C-0->D, D, I-4->J, J}";
}

bool check12()
{
    std::stringstream ss;
    test12(ss);
    bool ok = (0 == ss.str().compare(res12()));
    if (ok) {
        std::cout << "test12 OK " << std::endl;
    } else {
        std::cout << "test12 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res12() << std::endl;
    }
    return ok;
}

//=====================================================================

void test13(std::ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B', 0).add('B', 'C', 0).add('C', 'D', 0).add('B', 'G', 0);
    h.add('E', 'F', 0).add('F', 'G', 0).add('G', 'H', 0);  //.add('F', 'C', 0);

    ss << "graph h   : " << h << std::endl;
    ss << "roots(h)  : " << roots(h) << std::endl;
    ss << "leafs(h)  : " << leaves(h) << std::endl;
    ss << dfschedule(h) << ", cost: " << schedulingcost(h, dfschedule(h)) << std::endl;
    ss << bfschedule(h) << ", cost: " << schedulingcost(h, bfschedule(h)) << std::endl;
}

std::string res13()
{
    return "graph h   : Graph {A-0->B, B-0->C, B-0->G, C-0->D, D, E-0->F, F-0->G, G-0->H, H}\n"
           "roots(h)  : std::vector{A, E}\n"
           "leafs(h)  : std::vector{D, H}\n"
           "Schedule {1:D, 2:C, 3:H, 4:G, 5:B, 6:A, 7:F, 8:E}, cost: 11\n"
           "Schedule {1:D, 2:H, 3:C, 4:G, 5:B, 6:F, 7:A, 8:E}, cost: 13\n";
}

bool check13()
{
    std::stringstream ss;
    test13(ss);
    bool ok = (0 == ss.str().compare(res13()));
    if (ok) {
        std::cout << "test13 OK " << std::endl;
    } else {
        std::cout << "test13 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res13() << std::endl;
    }
    return ok;
}

//=====================================================================

void test14(std::ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B', 0).add('B', 'C', 0).add('C', 'D', 0).add('B', 'G', 1).add('C', 'B', 1);
    h.add('E', 'F', 0).add('F', 'G', 0).add('G', 'H', 0).add('G', 'F', 2);

    ss << "graph h   : " << h << std::endl;
    ss << dfcyclesschedule(h) << ", cost: " << schedulingcost(h, dfcyclesschedule(h)) << std::endl;
}

std::string res14()
{
    return "graph h   : Graph {A-0->B, B-0->C, B-1->G, C-1->B, C-0->D, D, E-0->F, F-0->G, G-2->F, "
           "G-0->H, H}\n"
           "Schedule {1:H, 2:G, 3:F, 4:D, 5:C, 6:B, 7:A, 8:E}, cost: 17\n";
}

bool check14()
{
    std::stringstream ss;
    test14(ss);
    bool ok = (0 == ss.str().compare(res14()));
    if (ok) {
        std::cout << "test14 OK " << std::endl;
    } else {
        std::cout << "test14 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res14() << std::endl;
    }
    return ok;
}

//=====================================================================

void test15(std::ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B', 0).add('B', 'C', 0).add('C', 'D', 0).add('B', 'G', 1).add('C', 'B', 1);
    h.add('D', 'U', 0).add('U', 'D', 1);
    h.add('E', 'F', 0).add('F', 'G', 0).add('G', 'H', 0).add('G', 'F', 2);

    ss << "graph h   : " << h << std::endl;
    ss << "deep-first    : " << dfcyclesschedule(h)
       << ", cost: " << schedulingcost(h, dfcyclesschedule(h)) << std::endl;
    ss << "breadth-first : " << bfcyclesschedule(h)
       << ", cost: " << schedulingcost(h, bfcyclesschedule(h)) << std::endl;
}

std::string res15()
{
    return "graph h   : Graph {A-0->B, B-0->C, B-1->G, C-1->B, C-0->D, D-0->U, E-0->F, F-0->G, "
           "G-2->F, G-0->H, "
           "H, U-1->D}\n"
           "deep-first    : Schedule {1:U, 2:D, 3:H, 4:G, 5:F, 6:C, 7:B, 8:A, 9:E}, cost: 20\n"
           "breadth-first : Schedule {1:H, 2:U, 3:D, 4:G, 5:F, 6:C, 7:B, 8:E, 9:A}, cost: 18\n";
}

bool check15()
{
    std::stringstream ss;
    test15(ss);
    bool ok = (0 == ss.str().compare(res15()));
    if (ok) {
        std::cout << "test15 OK " << std::endl;
    } else {
        std::cout << "test15 FAIL " << std::endl;
        std::cout << "We got     " << ss.str() << std::endl;
        std::cout << "instead of " << res15() << std::endl;
    }
    return ok;
}
