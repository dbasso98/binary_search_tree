#pragma once

#include <iostream>
#include <memory> // std::unique_ptr
#include <utility> // std::move and std::pair


/** Template class for members of the binary search tree concept.
 * Every element of the binary search tree is a node. 
 * Each node stores a pair of a key and the associated value.
 */
template <typename pair_type>
class node{
    /** \brief Node content
     * 
     * Pair type, containing a key and associated value, stored in var \private  data. */
    pair_type data;  

    /** \brief Pointer to far left node
     * 
     *Private function that returns the node on the far left side of the tree, 
     * used as the begin of the iterator.
     */    
    node* _leftmost(node* other) const noexcept {
        auto first_node {other};
        if(first_node) {
            while (first_node->get_left()) {
                first_node = first_node->get_left();
            }
        }

        return first_node;
    }

    public:
    /** \brief Parent node
     * 
     * Pointer to the node that has the current node as one of its' childs.
     * Widely used in the insert function in order to find the correct place for a new node.
    */
    node* parent_node; 

    /** \brief Left child
     * 
     * Unique pointer to the node that is left from the current, 
     * a node with a smaller key from the current node.
     */
    std::unique_ptr<node> left_child;   

    /** \brief Right child 
     * 
     * Unique pointer to the node that is right from the current, 
     * a node with a bigger key from the current node.
     */
    std::unique_ptr<node> right_child; 

    /** \brief Default node Constructor and Destructor 
     * 
    */
    node() = default;
    ~node() noexcept = default;

    /** \brief Custom node Constructor
     * 
     * Creates a node receiving an l-value reference to the content we want to store in it,as \p d , 
     * and parent node as \p parent with default value as nullptr.
     */
    node(const pair_type& d, node* parent = nullptr):                   
    data{d}, parent_node{parent} {
        left_child.reset();
        right_child.reset();
    }

    /** \brief Custom Node Constructor
     *  
     * Creates a node receiving an r-value reference to the content we want to store in it,as \p d , 
     * and parent node as \p parent with default value as nullptr.
     */
    node(const pair_type&& d, node* parent = nullptr):
    data{std::move(d)}, parent_node{parent} {
        left_child.reset();
        right_child.reset();
    }

    /** \brief Custom Node Constructor
     * 
     * Creates a node receiving a parent node as \p parent with default value as nullptr.
     */
    explicit node(node* parent = nullptr):
    data{}, parent_node{parent}{ 
        left_child.reset();
        right_child.reset();
    }

    /** \brief Move semantics
     * 
     * Implementing both move constructor and move assignment
     * using default compiler generated ones.
     */
    explicit node(node&& other) noexcept = default;
	node& operator=(node&& other) noexcept = default;

    
    /** \brief Deep copy semantics
     * 
     * Managing the resources from the lowest level, to achieve a deep copy of the bst itself.
     */
    explicit node(const node& other):
    data{other.data}, parent_node{nullptr} { 
        if(other.parent_node) {
            parent_node = new node{other.parent_node};
        }
        if(other.right_child) {
            right_child.reset(new node{*(other.right_child.get())});
            right_child->parent_node = this;
        }
        if(other.left_child) {
            left_child.reset(new node{*(other.left_child.get())});
            left_child->parent_node = this;
        }
    }
    
    /** \brief Copy assignment
     * 
     */
    node& operator=(const node& x) {
        left_child.reset();
        right_child.reset();
        auto tmp {x}; // copy ctor
        *this = std::move(tmp); //move assignment
        return *this;    
    }

    /** \subsection Getter functions of node class*/

    /** \returns pointer to left child*/
    node* get_left() noexcept{
        return left_child.get();
    }

    /** \returns pointer to right child*/
    node* get_right() noexcept{
        return right_child.get();
    }

    /** \returns pointer to parent*/
    node* get_parent() noexcept{
        return parent_node;
    }

    /** \returns by reference, contents of node, as data */
    pair_type& get_data() noexcept{
        return data;
    }

    /** \returns by const reference, contents of node, as data */
    const pair_type& get_data() const noexcept{
        return data;
    }

    /** \returns pointer to  leftmost node */
    node* leftiest() noexcept {
		return _leftmost(this);
	}

    /** \returns const leftmost node */
	const node* leftiest() const noexcept {
		return _leftmost(this);
	}

};
