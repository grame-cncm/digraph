//
//  main.cpp
//  graphlib
//
//  Created by Yann Orlarey on 31/01/2017.
//  Copyright © 2017-2019 GRAME. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <list>
#include "tests.hh"

using namespace std;

int main(int, const char**)
{
    cout << "Tests digraph library\n";

    bool r = true;
    r &= check0();
    r &= check1();
    r &= check2();
    r &= check3();
    r &= check4();
    r &= check5();
    r &= check7();
    r &= check8();
    r &= check9();
    r &= check10();
    r &= check11();
    r &= check12();

    // test11(std::cout);

    // // Faust test
    // digraph<char> g;
    // g.add('A', 'B').add('B', 'C', 3).add('C', 'A');  // cycle 1
    // g.add('U', 'V').add('V', 'W', 4).add('W', 'U');  // cycle 2

    // g.add('A', 'U', 2).add('B', 'V', 3).add('C', 'W', 1);

    // cout << "graph    : " << g << endl;
    // cout << "digraph  : " << graph2dag(g) << endl;
    // cout << "digraph2 : " << graph2dag2(g) << endl;

    // std::ofstream outfile("foo.dot");

    // dotfile(outfile, g, true);

    // outfile.close();
}
