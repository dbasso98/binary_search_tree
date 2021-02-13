#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"
#include "bst.hpp"

int main() {
    auto a = std::make_pair(8,0);
    auto b = std::make_pair(3,1);
    auto c = std::make_pair(9,1);
    auto d = std::make_pair(1,900);

    bst<int,int,std::less<int>> tree {};
    tree.insert(a);
    tree.insert(b);
    tree.insert(c);
    tree.insert(d);

    std::cout << tree << std::endl;

    return 0;
}
