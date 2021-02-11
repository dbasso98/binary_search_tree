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
    using iterator = iterator<pair_type, node_type>;
    using const_iterator = iterator<const pair_type, node_type>;

    // private member variables
    std::unique_ptr<node_type> head;
    std::size_t _size;
    comparison comp;

    // private member functions

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
            head.reset(new node_type{other.head})
    }

    bst& operator=(const bst& x) {
        head.reset();
        auto tmp = x; // copy ctor
        *this = std::move(tmp); // move assignment
        return *this;    
    }
    
    
    // small member functions
    void clear() {
        head.reset(nulltpr);
        _size = 0;
    }

    iterator begin() noexcept{
        return iterator{left_most(head.get())};
    }
    const_iterator begin() const noexcept {
        return const_iterator{left_most(head.get())};
    }
    const_iterator cbegin() const noexcept {
        return const_iterator{left_most(head.get())};
    }

    iterator end() noexcept {
        return iterator{nullptr};
    }
    const_iterator end() const noexcept {
        return const_iterator{nullptr};
    }
    const_iterator cend() const noexcept{
        return const_iterator{nullptr}
    }

    // operators overload
    
};
