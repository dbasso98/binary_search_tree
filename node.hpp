#ifndef NODE_HPP // include guard
#define NODE_HPP // or shall we use #pragma once (simpler and also can improve computational speed)

#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move and std::pair

template <typename pair_type>
class node{
    
    public:

    node* parent_node;                  // pointer to parent node
    std::unique_ptr<node> left_child;   // unique pointer to left child
    std::unique_ptr<node> right_child;  // unique pointer to right child
    pair_type data;                     // data contained in the node

    // default constructor and destructor
    node()  = default;
    ~node() noexcept = default;

    // custom constructors

    // create a node giving only the parent node and the value we want to store
    // basically is a copy ctor
    node(node* parent = nullptr, const pair_type& d):                   
    parent_node{parent}, left_child{nullptr},
    right_child{nullptr}, data{d} {}

    // create a node giving only the parent node
    explicit node(node* parent = nullptr):
    parent_node{parent}, left_child{nullptr},
    right_child{nullptr}, data{} {}

    // move ctor
    node(node* parent = nullptr, const pair_type&& d):
    parent{parent}, left_child{nullptr},
    right_child{nullptr}, data{std::move(d)} {}

}

#endif