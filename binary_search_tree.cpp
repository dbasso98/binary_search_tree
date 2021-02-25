#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <exception>
#include "node.hpp"
#include "iterator.hpp"
#include "bst.hpp"

int main() {

    try {
        bst<int,int,std::less<int>> tree {};

        // creating pairs and inserting them in a tree
        auto a = std::make_pair(8,0);
        auto b = std::make_pair(3,20);
        auto c = std::make_pair(10,10);
        auto d = std::make_pair(1,-5);
        auto e = std::make_pair(6,8);

        // test insert
        std::cout << "Testing insert() function" << std::endl;
        tree.insert(a);
        tree.insert(b);
        tree.insert(c);
        tree.insert(d);
        tree.insert(e);

        // test emplace
        std::cout << "Testing emplace() function" << std::endl;    
        tree.emplace(14,2000);
        tree.emplace(4,0);
        tree.emplace(7,-30);
        tree.emplace(13,9);

        // test find function for existing key value and not
        std::cout << "Testing find() function" << std::endl;    
        tree.find(2);
        tree.find(14);

        // test erase function for existing key value and not
        std::cout << "Testing erase() function" << std::endl;
        tree.erase(8);
        tree.erase(-2);

        // test balance function
        std::cout << "Testing balance() function" << std::endl;
        tree.balance();

        // test put to operator and then 2D printing of the tree
        std::cout << "Testing put to operator and print2D() function" << std::endl;
        std::cout << tree << std::endl;
        tree.print2D();

        // test deep copy constructor
        std::cout << "Testing deep copy constructor" << std::endl;
        auto tree2 {tree};

        // test subscripting operator
        std::cout << "Testing subscripting operator" << std::endl;
        auto var {3};
        std::cout << tree2[var] << std::endl;
        std::cout << tree2[-2] << std::endl;

        // test if deep copy is actually working
        std::cout << "Printing original tree" << std::endl;
        tree.print2D();
        std::cout << "Printing modified tree constructed through deep copy (tree2)" << std::endl;
        tree2.print2D();

        // test deep copy assignment
        std::cout << "Testing copy assignment" << std::endl;
        bst<int,int,std::less<int>> tree3 {};
        tree3 = tree2;
        tree3.erase(10);
        std::cout << "Printing tree2" << std::endl;
        tree2.print2D();
        std::cout << "Printing tree3" << std::endl;
        tree3.print2D();
        

        // test move constructor
        std::cout << "Testing move constructor" << std::endl;
        auto tree4 {std::move(tree2)};
        std::cout << "Printing tree2" << std::endl;
        tree2.print2D();
        std::cout << "Printing tree4, created moving tree2" << std::endl;
        tree4.print2D();

        // test move assignment
        std::cout << "Testing move assignment" << std::endl;
        bst<int,int,std::less<int>> tree5 {};
        tree5 = std::move(tree4);
        std::cout << "Printing tree5, created moving tree4" << std::endl;
        tree5.print2D();
        

        // test clear function
        std::cout << "Testing clear() function" << std::endl;
        tree.clear();
        tree2.clear();
        tree3.clear();
        tree4.clear();
        tree5.clear();
    }

    catch(std::logic_error& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    };

    return 0;
}

