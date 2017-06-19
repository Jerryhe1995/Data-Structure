#include <fstream>
#include <iostream>
#include <algorithm>
#include "freqtable.h"

int main(int argc, char **argv) {
     FreqTable test;
    test.insert("6");
    test.insert("3");
    test.insert("8");
    test.insert("2");
    test.insert("4");
    test.insert("7");
    test.insert("9");
    test.insert("3");
     test.insert("2");
    test.insert("10");
    test.insert("11");
    test.insert("8");
    test.insert("13");
    test.insert("3");
    test.insert("4");
    test.insert("6");

    test.erase("6");
    test.erase("1");
    test.erase("3");
    std::cout<<"check";
    test.erase("9");
    test.erase("8");
    test.erase("4");
    test.erase("6");
    test.erase("6");
    std::cout <<  "test size "<<test.size() <<std::endl;
    // this program expects 1 command line argument
    if (argc != 2) {
        std::cout << "Usage: ./main <filename>\n";
        std::cout << "\t<filename> path to an input text file\n";
        return 0;
    }

    // create the frequency table
    FreqTable mytree;

    // open the text file and read its contents
    // insert every word into the tree
    std::ifstream in_file(argv[1]);
    for(std::string w ; in_file >> w ; ) {
        // only keep alphanumeric characters
        // (uses fancy lambda functions from C++ 11)
        w.erase(std::remove_if(w.begin(), w.end(), [](char c) {return !std::isalnum(c);}), w.end());
        // ignore empty words
        if (w.size() == 0) continue;
        // insert word into the three
        mytree.insert(w.c_str());
        // you can use std::cout at this point to inspect the words when your program runs
        // std::cout << w << std::endl;
    }

    // print the frequency 
    std::cout << "Before :\n";
    mytree.print_all();
    std::cout<<"size is "<< "   "<< mytree.size() << std::endl;
    mytree.erase("ai");
    std::cout<<"size is "<< "   "<< mytree.size() << std::endl;
    mytree.erase("1");
    std::cout<<"size is "<< "   "<< mytree.size()<<"begin" << std::endl;
    
    
     
    
    mytree.erase("with");
    mytree.erase("with");
    mytree.erase("with");
    
    mytree.erase("way");
    
    mytree.erase("way");
    mytree.erase("way");
    std::cout<<"size is "<< "   "<< mytree.size() <<"contains way" <<mytree.contains("way")<< std::endl;
    std::cout << "end :\n";


    
    // here you can add more code to test all of your methods
    // TODO

    return 0;
}