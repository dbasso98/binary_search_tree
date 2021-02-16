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
    bst<int,int,std::less<int>> tree {};

    try{
    //tree.erase(8);
    
    auto a = std::make_pair(8,0);
    auto b = std::make_pair(3,0);
    auto c = std::make_pair(10,0);
    auto d = std::make_pair(1,0);
    auto e = std::make_pair(6,0);

    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
    tree.insert(d);
    tree.insert(e);
    tree.emplace(14,0);
    tree.emplace(4,0);
    tree.emplace(7,0);
    tree.emplace(13,0);

    /*
    for (int i {-5}; i < 15; ++i){
        auto a = std::make_pair(i,i);
        tree.insert(a);
    }
    */
    

    //tree.emplace(12,3);

    tree.find(2);

    //tree.print2D();
    //std::cout << tree << std::endl;

    tree.erase(8);
    tree.print2D();

    //tree.clear();

    //std::cout << tree[3] << std::endl;

    auto tree2 {tree};
    std::cout << tree2 << std::endl;

    tree2.erase(3);

    tree2.print2D();
    tree.print2D();

    }
    catch(std::logic_error& e){
        std::cout << "Standard exception: " << e.what() << std::endl;
    };

    return 0;
}
