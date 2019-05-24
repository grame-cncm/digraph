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

void test3(ostream& cout)
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
        h2, [](const digraph<char>& g) -> digraph<char> { return cut(g, 1); });
    cout << "test3: h3= " << h3;
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

void test7()
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

    auto h = graph2dag(g);    // on fait un dag dont les noeuds sont les cycles du graphe g
    auto p = parallelize(h);  //
    auto s = serialize(h);    //

    cout << "test7:        g = " << g << endl;
    cout << "number of cycles: " << cycles(g) << endl;
    cout << "0-cycles        : " << cycles(cut(g, 1)) << endl;
    cout << "graph2dag(g)    = " << h << endl;
    cout << "parallelize(h)  = " << p << endl;
    cout << "serialize(h)    = " << s << endl;

    dotfile(cout, g);
}
