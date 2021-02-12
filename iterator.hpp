#pragma once    //instead of ifdef and so on

#include <iostream>

template <typename pair_type, typename node_type>
class iterator {
    node_type* current;
    node_type* next(node_type* cur);
    
    public:
    using difference_type = std::ptrdiff_t; // pointer arithmetic
    using reference = pair_type&;
    using pointer = pair_type*;

    node_type* left_most(node_type* other);

    // default ctor and dtor
    iterator() = default;
    ~iterator() noexcept = default;

    // custom ctor
    explicit iterator(node_type* other):
    current{other} {}

    // deleting copy semantics
    iterator(const iterator& it) = delete;
    iterator& operator=(const iterator& it) = delete;

    // move semantics
    explicit iterator(const iterator&& it) noexcept:
    current{std::move(it.current)} {
        it.current = nullptr;
    }
    iterator& operator=(iterator&& it) noexcept {
        delete current;
        current = it.current;
        it.current = nullptr;
        return *this;
    }

    // operators overloading
    reference operator*() const noexcept{
        return current->get_data();
    }

    pointer operator->() const noexcept{
        return &(*(*this));
    }

    // pre increment
    iterator& operator++() const{
        current = next(current);
        return *this;
    }

    // post increment
    iterator operator++(int) const{
        iterator update{*this};
        ++(*update);
        return update;
    } 

    friend bool operator==(const iterator& lhs, const iterator& rhs) noexcept{
        return lhs.current == rhs.current;
    }

    friend bool operator!=(const iterator& lhs, const iterator& rhs) noexcept{
        return !(lhs.current == rhs.current);
    }
};

template <typename pair_type, typename node_type>
node_type* iterator<pair_type,node_type>::left_most(node_type* other) {
    node_type* first_node = other;
    while(other->get_left()) {
        first_node = other->get_left();
    }

    return first_node;
}

template <typename pair_type, typename node_type>
node_type* iterator<pair_type,node_type>::next(node_type* cur) {
    auto next_one {cur};
    if(cur->get_right()) {
        next_one = left_most(cur->get_right());
    }
    else if(cur->get_parent()){
        auto parent {cur->get_parent()};
        while(parent) {
            if(parent->get_left() == cur){
                break;
            }
            else {
                cur = parent;
                parent = parent->get_parent();
            }
        }

        next_one = parent; 
    }

    return next_one;
}

