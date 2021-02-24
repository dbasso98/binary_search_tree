#pragma once //instead of ifdef and so on

#include <iostream>

/** Custom Forward Iterator Template class for members of the binary search tree concept.
 * Every instance of the Iterator class is a pointer to a Node type.
 * Mainly used to tarverse the tree in order.
 */
template <typename pair_type, typename node_type>
class Iterator {

    /** \brief Pointer to current node 
     * 
     * Pointer to a node class, private to the user, \private current. */
    node_type *current;
    
    public:
    /** \subsection Default Iterator members. */
    using difference_type = std::ptrdiff_t; // pointer arithmetic
    using reference = pair_type &;
    using pointer = pair_type *;
    using iterator_category = std::forward_iterator_tag;

    /** \brief Next node
     * 
     * Declaration of function that returns pointer to the node that is successive to the current one, 
     * which is passed as a pointer \p cur . */
    node_type *next(node_type *cur) const noexcept;

    /** \brief Default iterator Constructor and Destructor */
    Iterator() = default;
    ~Iterator() noexcept = default;

    /** \brief Custom iterator Constructor
     * 
     * Creates an iterator by receiving a pointer to node type as \p other . */
    explicit Iterator(node_type *other) : current{other} {}

    /**
     * Operator overloading. Operator * to return contents of the current Iterator instance */
    reference operator*() const noexcept
    {
        return current->get_data();
    }

    /**
     * Operator overloading. Operator -> to return #TODO */
    pointer operator->() const noexcept
    {
        return &(*(*this));
    }

    /**
     * Operator overloading. Operator ++ as pre-increment. */
    Iterator &operator++() 
    {
        current = next(current);
        return *this;
    }

    /**
     * Operator overloading. Operator ++ as post-increment with \p int . */
    Iterator operator++(int) 
    {
        auto update(*this);
        ++(*update);
        return update;
    }

    friend bool operator==(const Iterator &lhs, const Iterator &rhs) noexcept
    {
        return lhs.current == rhs.current;
    }

    friend bool operator!=(const Iterator &lhs, const Iterator &rhs) noexcept
    {
        return !(lhs == rhs);
    }
};

/** Definition of Function that returns the pointer to the Node that is successive to the current one, 
     * passed as a pointer to a Node \p cur */
template <typename pair_type, typename node_type>
node_type* Iterator<pair_type, node_type>::next(node_type *cur) const noexcept
{
    auto next_one{cur};
    if (cur->get_right()) {
        next_one = cur->get_right()->leftiest();
    }
    else {
        auto parent{cur->get_parent()};
        while (parent) {
            if (parent->get_left() == cur) {
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
