//
//  tests.cpp
//  graphlib
//
//  Created by Yann Orlarey on 06/02/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include "tests.hh"

void test0(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C', 1)
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E', 1)
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F', 1)
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H', 1);

    ss << "g = " << g;
}

string res0()
{
    return "g = Graph {A->B, B-1->C, C->A, D->B, D->C, D-1->E, E->D, E->F, F->G, G-1->F, H->E, "
           "H->G, H-1->H}";
}

bool check0()
{
    stringstream ss;
    test0(ss);
    bool ok = (0 == ss.str().compare(res0()));
    if (ok) {
        cout << "test0 OK " << endl;
    } else {
        cout << "test0 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res0() << endl;
    }
    return ok;
}

void test1(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C')
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E')
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F')
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H');

    ss << "Tarjan partition of g = ";
    Tarjan<char> tarj(g);
    for (const auto& cycle : tarj.partition()) {
        ss << "group{ ";
        for (const auto& n : cycle) { ss << n << " "; }
        ss << "} ";
    }
}

string res1()
{
    return "Tarjan partition of g = group{ A B C } group{ D E } group{ F G } group{ H } ";
}

bool check1()
{
    stringstream ss;
    test1(ss);
    bool ok = (0 == ss.str().compare(res1()));
    if (ok) {
        cout << "test1 OK " << endl;
    } else {
        cout << "test1 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res1() << endl;
    }
    return ok;
}

void test2(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C', 1)
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E', 1)
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F', 1)
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H', 1);

    ss << "dag of g = " << graph2dag(g);
}

string res2()
{
    return "dag of g = Graph {Graph {A->B, B-1->C, C->A}, Graph {D-1->E, E->D}->Graph {A->B, "
           "B-1->C, C->A}, Graph {D-1->E, E->D}->Graph {F->G, G-1->F}, Graph {F->G, G-1->F}, Graph "
           "{H-1->H}->Graph {D-1->E, E->D}, Graph {H-1->H}->Graph {F->G, G-1->F}}";
}

bool check2()
{
    stringstream ss;
    test2(ss);
    bool ok = (0 == ss.str().compare(res2()));
    if (ok) {
        cout << "test2 OK " << endl;
    } else {
        cout << "test2 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res2() << endl;
    }
    return ok;
}

void test3(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C', 1)
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E', 1)
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F', 1)
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H', 1);

    auto h1 = cut(g, 64);     // cut vectorsize connections
    auto h2 = graph2dag(h1);  // find cycles
    auto h3 = mapnodes<digraph<char>, digraph<char>>(
        h2, [](const digraph<char>& gr) -> digraph<char> { return cut(gr, 1); });
    ss << "test3: h3= " << h3;
}

string res3()
{
    return "test3: h3= Graph {Graph {D, E->D}->Graph {F->G, G}, Graph {D, E->D}->Graph {A->B, B, "
           "C->A}, Graph {F->G, G}, Graph {A->B, B, C->A}, Graph {H}->Graph {D, E->D}, Graph "
           "{H}->Graph {F->G, G}}";
}

bool check3()
{
    stringstream ss;
    test3(ss);
    bool ok = (0 == ss.str().compare(res3()));
    if (ok) {
        cout << "test3 OK " << endl;
    } else {
        cout << "test3 FAIL " << endl;
        cout << "We got     \"" << ss.str() << '"' << endl;
        cout << "instead of \"" << res3() << '"' << endl;
    }
    return ok;
}

void test4(ostream& ss)
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
    // cout << "test4: g1= " << g1 << endl;
    // cout << "test4: g2= " << g2 << endl;
    // cout << "test4: g3= " << g3 << endl;
}

string res4()
{
    return "test4: g3.add(g1).add(g2) = Graph {A-2->A, A->B, A->C, A-1->D, B-1->B, C, D}";
};

bool check4()
{
    stringstream ss;
    test4(ss);
    bool ok = (0 == ss.str().compare(res4()));
    if (ok) {
        cout << "test4 OK " << endl;
    } else {
        cout << "test4 FAIL " << endl;
        cout << "We got     \"" << ss.str() << '"' << endl;
        cout << "instead of \"" << res3() << '"' << endl;
    }
    return ok;
}

// Test separation of graphs
void test5(ostream& ss)
{
    digraph<char> g1, g2, g3;

    g1.add('A', 'Z');
    g1.add('A', 'B');
    g1.add('B', 'C');
    g1.add('C', 'A', 1);

    g1.add('Z', 'W');
    g1.add('W', 'Z', 1);

    g1.add('A', 'Z');
    g1.add('W', 'C', 1);

    splitgraph<char>(
        g1, [](const char& c) { return c < 'K'; }, g2, g3);

    ss << "test5: g1 = " << g1 << "; g2 = " << g2 << "; g3 = " << g3;
}

string res5()
{
    return "test5: g1 = Graph {A->B, A->Z, B->C, C-1->A, W-1->C, W-1->Z, Z->W}; g2 = Graph {A->B, "
           "B->C, C-1->A}; g3 = Graph {W-1->Z, Z->W}";
};

bool check5()
{
    stringstream ss;
    test5(ss);
    bool ok = (0 == ss.str().compare(res5()));
    if (ok) {
        cout << "test5 OK " << endl;
    } else {
        cout << "test5 FAIL " << endl;
        cout << "We got     \"" << ss.str() << '"' << endl;
        cout << "instead of \"" << res5() << '"' << endl;
    }
    return ok;
}

void test7(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C', 1)
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E', 1)
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F', 1)
        .add('H', 'G')
        .add('H', 'E')
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

string res7()
{
    return "test7:        g = Graph {A->B, B-1->C, C->A, D->B, D->C, D-1->E, E->D, E->F, F->G, "
           "G-1->F, H->E, H->G, H-1->H}; number of cycles: 4; 0-cycles        : 0; graph2dag(g)    "
           "= Graph {Graph {A->B, B-1->C, C->A}, Graph {D-1->E, E->D}->Graph {A->B, B-1->C, C->A}, "
           "Graph {D-1->E, E->D}->Graph {F->G, G-1->F}, Graph {F->G, G-1->F}, Graph "
           "{H-1->H}->Graph {D-1->E, E->D}, Graph {H-1->H}->Graph {F->G, G-1->F}}; parallelize(h)  "
           "= vector {vector {Graph {A->B, B-1->C, C->A}, Graph {F->G, G-1->F}}, vector {Graph "
           "{D-1->E, E->D}}, vector {Graph {H-1->H}}}; rparallelize(h)  = vector {vector {Graph "
           "{H-1->H}}, vector {Graph {D-1->E, E->D}}, vector {Graph {A->B, B-1->C, C->A}, Graph "
           "{F->G, G-1->F}}}; serialize(h)    = vector {Graph {A->B, B-1->C, C->A}, Graph {F->G, "
           "G-1->F}, Graph {D-1->E, E->D}, Graph {H-1->H}}; digraph mygraph {"
           "\n\t\"A\"->\"B\";"
           "\n\t\"B\"->\"C\" [label=\"1\"];"
           "\n\t\"C\"->\"A\";"
           "\n\t\"D\"->\"B\";"
           "\n\t\"D\"->\"C\";"
           "\n\t\"D\"->\"E\" [label=\"1\"];"
           "\n\t\"E\"->\"D\";"
           "\n\t\"E\"->\"F\";"
           "\n\t\"F\"->\"G\";"
           "\n\t\"G\"->\"F\" [label=\"1\"];"
           "\n\t\"H\"->\"E\";"
           "\n\t\"H\"->\"G\";"
           "\n\t\"H\"->\"H\" [label=\"1\"];"
           "\n}\n";
}

bool check7()
{
    stringstream ss;
    test7(ss);
    bool ok = (0 == ss.str().compare(res7()));
    if (ok) {
        cout << "test7 OK " << endl;
    } else {
        cout << "test7 FAIL " << endl;
        cout << "We got     \"" << ss.str() << '"' << endl;
        cout << "instead of \"" << res7() << '"' << endl;
    }
    return ok;
}

void test8(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C')
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E')
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F')
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H');

    set<char>     S{'C', 'F'};
    digraph<char> r = subgraph(g, S);
    ss << "Subgraph(" << g << ", " << S << ") = " << r;
}

string res8()
{
    return "Subgraph(Graph {A->B, B->C, C->A, D->B, D->C, D->E, E->D, E->F, F->G, G->F, H->E, "
           "H->G, H->H}, set {C, F}) = Graph {A->B, B->C, C->A, F->G, G->F}";
}

bool check8()
{
    stringstream ss;
    test8(ss);
    bool ok = (0 == ss.str().compare(res8()));
    if (ok) {
        cout << "test8 OK " << endl;
    } else {
        cout << "test8 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res8() << endl;
    }
    return ok;
}

void test9(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B')
        .add('B', 'C')
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E')
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F')
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H');

    set<char>     S{'H'};
    digraph<char> r = subgraph(g, S);
    ss << "Subgraph(" << g << ", " << S << ") = " << r;
}

string res9()
{
    return "Subgraph(Graph {A->B, B->C, C->A, D->B, D->C, D->E, E->D, E->F, F->G, G->F, H->E, "
           "H->G, H->H}, set {H}) = Graph {A->B, B->C, C->A, D->B, D->C, D->E, E->D, E->F, F->G, "
           "G->F, H->E, H->G, H->H}";
}

bool check9()
{
    stringstream ss;
    test9(ss);
    bool ok = (0 == ss.str().compare(res9()));
    if (ok) {
        cout << "test9 OK " << endl;
    } else {
        cout << "test9 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res9() << endl;
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
    g.add('A', 'B')
        .add('B', 'C', 1)
        .add('C', 'A')
        .add('D', 'B')
        .add('D', 'C')
        .add('D', 'E', 1)
        .add('E', 'D')
        .add('E', 'F')
        .add('F', 'G')
        .add('G', 'F', 1)
        .add('H', 'G')
        .add('H', 'E')
        .add('H', 'H', 1);

    digraph<char> r = reverse(reverse(g));
    if (equiv(g, r)) {
        cout << "test10 OK " << endl;
        return true;
    } else {
        cout << "test10 FAIL " << endl;
        cout << "We got      " << r << endl;
        cout << "Instead of  " << g << endl;
        return false;
    }
}

void test11(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B').add('B', 'C', 3).add('C', 'D').add('D', 'E');
    g.add('A', 'I').add('I', 'J', 4).add('J', 'E', 5);

    digraph<char> r = chain(g, false);
    ss << "chain(" << g << ", false) = " << r;
}

string res11()
{
    return "chain(Graph {A->B, A->I, B-3->C, C->D, D->E, E, I-4->J, J-5->E}, false) = Graph {A, "
           "B-3->C, "
           "C->D, D, E, I-4->J, J}";
}

bool check11()
{
    stringstream ss;
    test11(ss);
    bool ok = (0 == ss.str().compare(res11()));
    if (ok) {
        cout << "test11 OK " << endl;
    } else {
        cout << "test11 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res9() << endl;
    }
    return ok;
}

//=====================================================================

void test12(ostream& ss)
{
    digraph<char> g;
    g.add('A', 'B').add('B', 'C', 3).add('C', 'D').add('D', 'E');
    g.add('A', 'I').add('I', 'J', 4).add('J', 'E', 5);

    digraph<char> r = chain(g, true);
    ss << "chain(" << g << ", true) = " << r;
}

string res12()
{
    return "chain(Graph {A->B, A->I, B-3->C, C->D, D->E, E, I-4->J, J-5->E}, true) = Graph "
           "{B-3->C, C->D, D, I-4->J, J}";
}

bool check12()
{
    stringstream ss;
    test12(ss);
    bool ok = (0 == ss.str().compare(res12()));
    if (ok) {
        cout << "test12 OK " << endl;
    } else {
        cout << "test12 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res12() << endl;
    }
    return ok;
}

//=====================================================================

void test13(ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B').add('B', 'C').add('C', 'D').add('B', 'G');
    h.add('E', 'F').add('F', 'G').add('G', 'H');  //.add('F', 'C');

    ss << "graph h   : " << h << endl;
    ss << "roots(h)  : " << roots(h) << endl;
    ss << "leafs(h)  : " << leaves(h) << endl;
    ss << dfschedule(h) << ", cost: " << schedulingcost(h, dfschedule(h)) << endl;
    ss << bfschedule(h) << ", cost: " << schedulingcost(h, bfschedule(h)) << endl;
}

string res13()
{
    return "graph h   : Graph {A->B, B->C, B->G, C->D, D, E->F, F->G, G->H, H}\n"
           "roots(h)  : vector {A, E}\n"
           "leafs(h)  : vector {D, H}\n"
           "Schedule {1:D, 2:C, 3:H, 4:G, 5:B, 6:A, 7:F, 8:E}, cost: 11\n"
           "Schedule {1:D, 2:H, 3:C, 4:G, 5:B, 6:F, 7:A, 8:E}, cost: 13\n";
}

bool check13()
{
    stringstream ss;
    test13(ss);
    bool ok = (0 == ss.str().compare(res13()));
    if (ok) {
        cout << "test13 OK " << endl;
    } else {
        cout << "test13 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res13() << endl;
    }
    return ok;
}

//=====================================================================

void test14(ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B').add('B', 'C').add('C', 'D').add('B', 'G', 1).add('C', 'B', 1);
    h.add('E', 'F').add('F', 'G').add('G', 'H').add('G', 'F', 2);

    ss << "graph h   : " << h << endl;
    ss << dfcyclesschedule(h) << ", cost: " << schedulingcost(h, dfcyclesschedule(h)) << endl;
}

string res14()
{
    return "graph h   : Graph {A->B, B->C, B-1->G, C-1->B, C->D, D, E->F, F->G, G-2->F, G->H, H}\n"
           "Schedule {1:H, 2:G, 3:F, 4:E, 5:D, 6:C, 7:B, 8:A}, cost: 17\n";
}

bool check14()
{
    stringstream ss;
    test14(ss);
    bool ok = (0 == ss.str().compare(res14()));
    if (ok) {
        cout << "test14 OK " << endl;
    } else {
        cout << "test14 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res14() << endl;
    }
    return ok;
}

//=====================================================================

void test15(ostream& ss)
{
    // roots and leaves
    digraph<char> h;
    h.add('A', 'B').add('B', 'C').add('C', 'D').add('B', 'G', 1).add('C', 'B', 1);
    h.add('E', 'F').add('F', 'G').add('G', 'H').add('G', 'F', 2);

    ss << "graph h   : " << h << endl;
    ss << bfcyclesschedule(h) << ", cost: " << schedulingcost(h, bfcyclesschedule(h)) << endl;
}

string res15()
{
    return "graph h   : Graph {A->B, B->C, B-1->G, C-1->B, C->D, D, E->F, F->G, G-2->F, G->H, H}\n"
           "Schedule {1:D, 2:H, 3:G, 4:F, 5:C, 6:B, 7:E, 8:A}, cost: 17\n";
}

bool check15()
{
    stringstream ss;
    test15(ss);
    bool ok = (0 == ss.str().compare(res15()));
    if (ok) {
        cout << "test15 OK " << endl;
    } else {
        cout << "test15 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res15() << endl;
    }
    return ok;
}
