#pragma once    //instead of ifdef and so on

#include <iostream>

template <typename pair_type, typename node_type>
class iterator {
    node_type* current;
    node_type* left_most(node_type* other);
    
    public:
    using difference_type = std::ptrdiff_t; // pointer arithmetic
    using reference = pair_type&;
    using pointer = pair_type*;

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
        return current->data;
    }

    pointer operator->() const noexcept{
        return &(*(*this));
    }

    // pre increment
    iterator& operator++() const{
        current = left_most(current);
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
    
}
