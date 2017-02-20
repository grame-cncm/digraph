//
//  tests.cpp
//  graphlib
//
//  Created by Yann Orlarey on 06/02/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include "tests.hpp"

using namespace digraph;

void test0(ostream& ss)
{

    digraph<char> g;
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    ss << "g = " << g;
}

string res0() 
{
    return "g = Graph {A->B, B-1->C, C->A, D->B, D->C, D-1->E, E->D, E->F, F->G, G-1->F, H->E, H->G, H-1->H}";
}

bool check0()
{
    stringstream ss;
    test0(ss);
    bool ok = (0 == ss.str().compare(res0()));
    if (ok) {
        cout << "test0 OK " << ss.str() << endl;
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
    g.add('A','B');
    g.add('B','C');
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E');
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F');

    g.add('H','G');
    g.add('H','E');
    g.add('H','H');

    ss << "Tarjan partition of g = ";
    Tarjan<char> tarj(g);
    for (const auto& cycle : tarj.partition()) {
        ss << "group{ ";
        for (const auto& n : cycle) {
            ss << n << " ";
        }
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
        cout << "test1 OK " << ss.str() << endl;
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
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    ss << "dag of g = " << graph2dag(g);
}

string res2() 
{
    return "dag of g = Graph {Graph {A->B, B-1->C, C->A}, Graph {D-1->E, E->D}->Graph {A->B, B-1->C, C->A}, Graph {D-1->E, E->D}->Graph {F->G, G-1->F}, Graph {F->G, G-1->F}, Graph {H-1->H}->Graph {D-1->E, E->D}, Graph {H-1->H}->Graph {F->G, G-1->F}}";
}

bool check2()
{
    stringstream ss;
    test2(ss);
    bool ok = (0 == ss.str().compare(res2()));
    if (ok) {
        cout << "test2 OK " << ss.str() << endl;
    } else {
        cout << "test2 FAIL " << endl;
        cout << "We got     " << ss.str() << endl;
        cout << "instead of " << res2() << endl;
    }
    return ok;
}

void test3()
{
    digraph<char> g;
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    digraph<digraph<char>> gg;
    gg.add(g,g,10);
    cout << "test3 digraph " << gg << endl;
}

void test4()
{

    digraph<char> k;
    k.add('A','B');
    k.add('C','B');
    k.add('D','B');
    k.add('A','E');
    k.add('B','E');
    cout << "test4, graph k      : " << k << endl;
}

void test5()
{
    std::cout << "test 5" << std::endl;
    digraph<char> g;
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    digraph<char> h(g);
    digraph<char> k(h);

    cout << "test5 k = " << k << endl;
}


void test6(ostream& cout)
{

    digraph<char> g;
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    auto h1 = cut(g, 64);	// cut vectorsize connections
    auto h2 = graph2dag(h1);	// find cycles
    auto h3 = mapnodes<digraph<char>,digraph<char>>(h2, [](const digraph<char>& g)->digraph<char> { return cut(g,1); });
/*  cout << "test6: g = " << g << endl;
    cout << "     : h1= " << h1 << endl;
    cout << "     : h2= " << h2 << endl;
*/    cout << "test6: h3= " << h3;
}


string res6() 
{
    return "test6: h3= Graph {Graph {D, E->D}->Graph {F->G, G}, Graph {D, E->D}->Graph {A->B, B, C->A}, Graph {F->G, G}, Graph {A->B, B, C->A}, Graph {H}->Graph {D, E->D}, Graph {H}->Graph {F->G, G}}";
}

bool check6()
{
    stringstream ss;
    test6(ss);
    bool ok = (0 == ss.str().compare(res6()));
    if (ok) {
        cout << "test6 OK \"" << ss.str() <<'"' << endl;
    } else {
        cout << "test6 FAIL " << endl;
        cout << "We got     \"" << ss.str() <<'"' << endl;
        cout << "instead of \"" << res6() <<'"' << endl;
    }
    return ok;
}


void test7()
{

    digraph<char> g;
    g.add('A','B');
    g.add('B','C',1);
    g.add('C','A');

    g.add('D','B');
    g.add('D','C');
    g.add('D','E',1);
    g.add('E','D');
    g.add('E','F');

    g.add('F','G');
    g.add('G','F',1);

    g.add('H','G');
    g.add('H','E');
    g.add('H','H',1);

    auto h = graph2dag(g);		// on fait un dag dont les noeuds sont les cycles du graphe g
    auto p = parallelize(h);	//
    auto s = serialize(h);	//

    cout << "test7:        g = " << g << endl;
    cout << "number of cycles: " << cycles(g) << endl;
    cout << "0-cycles        : " << cycles(cut(g,1)) << endl;
    cout << "graph2dag(g)    = " << h << endl;
    cout << "parallelize(h)  = " << p << endl;
    cout << "serialize(h)    = " << s << endl;
}

