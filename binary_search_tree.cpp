#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"
#include "bst.hpp"

int main() {
    bst<int,int,std::less<int>> tree {};
    
    auto a = std::make_pair(8,0);
    auto b = std::make_pair(3,1);
    auto c = std::make_pair(9,1);
    auto d = std::make_pair(190,900);

    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
    tree.insert(d);

    /*
    for (int i {-5}; i < 15; ++i){
        auto a = std::make_pair(i,i);
        tree.insert(a);
    }
    */
    

    tree.emplace(12,3);

    tree.find(3);

    tree.erase(3);

    //tree.clear();



    //std::cout << tree[3] << std::endl;
    std::cout << tree << std::endl;


    return 0;
}
