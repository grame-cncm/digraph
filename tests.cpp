//
//  tests.cpp
//  graphlib
//
//  Created by Yann Orlarey on 06/02/2017.
//  Copyright © 2017 Yann Orlarey. All rights reserved.
//

#include "tests.hpp"

using namespace digraph;

void test0()
{

    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

    cout << "test0 : g = " << g << endl;
}

void test1()
{
    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C');
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E');
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F');

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H');

    cout << "teste1: g = " << g << endl;

    Tarjan<char> tarj(g);
    for (const auto& cycle : tarj.partition()) {
        cout << "group{ ";
        for (const auto& n : cycle) {
            cout << n << " ";
        }
        cout << "}" << endl;
    }

    cout << "number of cycles " << tarj.cycles() << endl;

}

void test2()
{
    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

    //digraph<supernode<char>*> sg = supergraph(g);
    digraph<digraph<char>> sg(graph2dag(g));
    cout << "test2 : graph g      : " << g << endl;
    cout << "test2 : super dag sg : " << sg << endl;
}

void test3()
{
    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

    digraph<digraph<char>> gg;
    gg.connect(g,g,10);
    cout << "test3 digraph " << gg << endl;
}

void test4()
{

    digraph<char> k;
    k.connect('A','B');
    k.connect('C','B');
    k.connect('D','B');
    k.connect('A','E');
    k.connect('B','E');
    cout << "test4, graph k      : " << k << endl;
}

void test5()
{
    std::cout << "test 5" << std::endl;
    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

    digraph<char> h(g);
    digraph<char> k(h);

    cout << "test5 k = " << k << endl;
}


void test6()
{

    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

    auto h1 = cut(g, 64);	// cut vectorsize connections
    auto h2 = graph2dag(h1);	// find cycles
    auto h3 = mapnodes<digraph<char>,digraph<char>>(h2, [](const digraph<char>& g)->digraph<char> { return cut(g,1); });
    cout << "test6: g = " << g << endl;
    cout << "     : h1= " << h1 << endl;
    cout << "     : h2= " << h2 << endl;
    cout << "     : h3= " << h3 << endl;
}



void test7()
{

    digraph<char> g;
    g.connect('A','B');
    g.connect('B','C',1);
    g.connect('C','A');

    g.connect('D','B');
    g.connect('D','C');
    g.connect('D','E',1);
    g.connect('E','D');
    g.connect('E','F');

    g.connect('F','G');
    g.connect('G','F',1);

    g.connect('H','G');
    g.connect('H','E');
    g.connect('H','H',1);

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

