#pragma once //instead of ifdef and so on

#include <iostream>

template <typename pair_type, typename node_type>
class Iterator
{
    node_type *current;

public:
    using difference_type = std::ptrdiff_t; // pointer arithmetic
    using reference = pair_type &;
    using pointer = pair_type *;

    node_type *left_most(node_type *other) const noexcept;
    node_type *next(node_type *cur) const noexcept;

    // default ctor and dtor
    Iterator() = default;
    ~Iterator() noexcept = default;

    // custom ctor
    explicit Iterator(node_type *other) : current{other} {}

    // deleting copy semantics
    Iterator(const Iterator &it) = delete;
    Iterator &operator=(const Iterator &it) = delete;

    // move semantics
    explicit Iterator(Iterator &&it) noexcept : current{std::move(it.current)}
    {
        it.current = nullptr;
    }
    Iterator &operator=(Iterator &&it) noexcept
    {
        delete current;
        current = it.current;
        it.current = nullptr;
        return *this;
    }

    // operators overloading
    reference operator*() const noexcept
    {
        return current->get_data();
    }

    pointer operator->() const noexcept
    {
        return &(*(*this));
    }

    // pre increment
    Iterator &operator++() 
    {
        current = next(current);
        return *this;
    }

    // post increment
    Iterator operator++(int) 
    {
        Iterator update{*this};
        ++(*update);
        return update;
    }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) noexcept
    {
        return lhs.current == rhs.current;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) noexcept
    {
        return !(lhs.current == rhs.current);
    }
};

template <typename pair_type, typename node_type>
node_type* Iterator<pair_type, node_type>::left_most(node_type *other) const noexcept
{
    node_type *first_node = other;
    while (first_node->get_left())
    {
        first_node = first_node->get_left();
    }

    return first_node;
}

template <typename pair_type, typename node_type>
node_type* Iterator<pair_type, node_type>::next(node_type *cur) const noexcept
{
    auto next_one{cur};
    if (cur->get_right())
    {
        next_one = left_most(cur->get_right());
    }
    else if (cur->get_parent())
    {
        auto parent{cur->get_parent()};
        while (parent)
        {
            if (parent->get_left() == cur)
            {
                break;
            }
            else
            {
                cur = parent;
                parent = parent->get_parent();
            }
        }

        next_one = parent;
    }

    return next_one;
}
