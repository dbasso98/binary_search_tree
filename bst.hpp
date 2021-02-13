#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <utility>
#include "node.hpp"
#include "iterator.hpp"

template<typename key_type, typename value_type, typename comparison=std::less<key_type>>
class bst {
    // using declaration
    using pair_type = std::pair<const key_type, value_type>;
    using node_type = node<pair_type>;
    using const_iterator = Iterator<const pair_type, node_type>;
    using iterator = Iterator<pair_type, node_type>;

    // private member variables
    std::unique_ptr<node_type> head;
    std::size_t _size;
    comparison comp;

    // private member functions
    template<typename O>
    std::pair<Iterator<O,node<O>>, bool> _insert(O&& x);

    public:
    // default ctor and dtor
    bst() = default;
    ~bst() noexcept = default;

    // move semantics
    bst(bst&& other) noexcept = default;
	bst& operator=(bst&& other) noexcept = default;

    // deep copy semantics
    bst(const bst& other):
    _size{other._size}, comp{other.comp} {
        if(other.head)
            head.reset(other.head.get());
    }

    bst& operator=(const bst& x) {
        clear();
        auto tmp = x; // copy ctor
        *this = std::move(tmp); // move assignment
        return *this;    
    }
    
    // small member functions
    void clear() {
        head.reset(nullptr);
        _size = 0;
    }

    iterator begin() noexcept{
        return iterator{head.get()->leftiest()};
    }
    const_iterator begin() const noexcept {
        return const_iterator{head.get()->leftiest()};
    }
    const_iterator cbegin() const noexcept {
        return const_iterator{head.get()->leftiest()};
    }

    iterator end() noexcept {
        return iterator{nullptr};
    }
    const_iterator end() const noexcept {
        return const_iterator{nullptr};
    }
    const_iterator cend() const noexcept{
        return const_iterator{nullptr};
    }

    // operators overload

    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) {
        os << "Size of the tree is:" << x._size << "\n";
        for(const auto& el : x) {
            os << "[ key=" << el.first <<" , value=" << el.second << " ] ";
        }
        os << std::endl;
        return os;
    }

    //
    std::pair<iterator, bool> insert(const pair_type& x) {
        return _insert(x);
    }
    std::pair<iterator, bool> insert(pair_type&& x) {
        return _insert(std::move(x));
    }
    
};


template<typename key_type, typename value_type, typename comparison>
template<typename O>
std::pair<Iterator<O,node<O>>, bool> bst<key_type, value_type, comparison>::_insert(O&& x){
    //std::cout << "forwarding insert" << std::endl;
    auto _node = new node<O>{std::forward<O>(x)};
    auto tmp = head.get();
    bool added = false;
    if (!tmp) { // if tmp == nullptr
        // our list is empty
        head.reset(_node);
        added = true;
        ++_size;
        std::cout << "root insert" << std::endl;
        return std::make_pair(Iterator<O,node<O>>{_node},added);
    }

    else {
        auto parent {tmp};
        int flag {0};
        // checking if we have to go left or right
        while(tmp) {
            // go right
            if(comp(tmp->get_data().first, _node->get_data().first)) {
                parent = tmp;
                tmp = tmp->get_right();
                flag = 0;
            }
            // go left
            else if(comp(_node->get_data().first, tmp->get_data().first)){
                parent = tmp;
                tmp = tmp->get_left();
                flag = 1;
            }
            // this means that we have found that there already is a node
            // with same key w.r.t. the one we wanted to insert
            else {  
                added = false;
                flag = -1;
                tmp = nullptr;
            }  
        }
        // after having found the correct position, we can add the node to the tree
        auto final_node = new node<O>{_node->get_data(),parent};
        switch(flag) {
            case 0:
                parent->right_child.reset(final_node);
                if(!parent->get_left())
                    ++_size;
                std::cout << "right insert" << std::endl;
                break;
            case 1:
                parent->left_child.reset(final_node);
                if(!parent->get_right())
                    ++_size;
                std::cout << "left insert" << std::endl;
                break;
            default:
                std::cout << "node was already present" << std::endl;
                break;
        }
    }

    return std::make_pair(Iterator<O,node<O>>{_node},added);
}
