#pragma once

#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move and std::pair

template <typename pair_type>
class node{

    node* leftmost(node* other) noexcept {
        auto first_node {other};
        if(first_node) {
            while (first_node->get_left()) {
                first_node = first_node->get_left();
            }
        }

        return first_node;
    }
    
    public:

    node* parent_node;                  // pointer to parent node
    std::unique_ptr<node> left_child;   // unique pointer to left child
    std::unique_ptr<node> right_child;  // unique pointer to right child
    pair_type data;                     // data contained in the node

    // default constructor and destructor
    node() = default;
    ~node() noexcept = default;

    // custom constructors

    // create a node giving only the parent node and the value we want to store
    node(const pair_type& d, node* parent = nullptr):                   
    parent_node{parent}, data{d} {
        left_child.reset();
        right_child.reset();
    }

    // create a node giving only the parent node
    explicit node(node* parent = nullptr):
    parent_node{parent}, data{} {
        left_child.reset();
        right_child.reset();
    }

    node(const pair_type&& d, node* parent = nullptr):
    parent_node{parent}, data{std::move(d)} {
        left_child.reset();
        right_child.reset();
    }

    // deep copy semantic
    explicit node(const std::unique_ptr<node>& other):
    data{other->data} {
        if(other->parent_node) {
            parent_node = new node{other->parent_node};
        }
        if(other->right_child) {
            right_child.reset(new node{other->right_child});
            right_child->parent_node = this;
        }
        if(other->left_child) {
            left_child.reset(new node{other->left_child});
            left_child->parent_node = this;
        }
    }

    node& operator=(const node& x) {
        left_child.reset();
        right_child.reset();
        auto tmp = x; // copy ctor
        *this = std::move(tmp); // move assignment
        return *this;    
    }

    // some useful functions
    node* get_left() noexcept{
        return left_child.get();
    }

    node* get_right() noexcept{
        return right_child.get();
    }

    node* get_parent() noexcept{
        return parent_node;
    }

    pair_type& get_data() noexcept{
        return data;
    }

    const pair_type& get_data() const noexcept{
        return data;
    }

    node* leftiest() noexcept {
		return leftmost(this);
	}

	const node* leftiest() const noexcept {
		return leftmost(this);
	}

};
