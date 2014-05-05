//
//  main.cpp
//  Test
//
//  Created by Philip Kubiak on 4/26/14.
//  Copyright (c) 2014 Philip Kubiak. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int SIZE = 100;
int main()
{

    // insert code here...
    string id[SIZE],name[SIZE];
    int index=0;
    ifstream infile;
    infile.open("/Users/kubiak/cpp_hw/idprsnel.dat");
    if (!infile) // check input file
        cerr << "Can't open input file\n";
    else{
        for (string line; getline(infile, line);){
            id[index] = line.substr(0,9);
            name[index] = line.substr(9,31);
            index++;
        }
        for (int i=0; i<SIZE;i++){
            cout << "ID " << i << ": " << id[i] << endl;
            cout << "Name " << i << ": " << name[i] << endl;
        }
        int* p = &index;
        cout << p << endl;
    }
    return 0;
}