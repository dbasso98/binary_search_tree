#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <utility>
#include <exception>
#include <chrono>
#include "node.hpp"
#include "iterator.hpp"

#define COUNT 10  

/** \class bst bst.hpp "include/node.hpp include/iterator.hpp"
 *  
 * Custom Binary Search Tree Template class.
 * Every instance of the bst class is a hierarchical (ordered) data structure.
 */
template<typename key_type, typename value_type, typename comparison=std::less<key_type>>
class bst {

    /** using declaration for pair_type. Represents a pair type of key and associated value. */
    using pair_type = std::pair<const key_type, value_type>;
    /** using declaration for pair_type. Represents a node type of a pair of key and associated value. */
    using node_type = node<pair_type>;
    /** using declaration for pair_type. Represents a constant iterator class, defined by a pair type and node type. */
    using const_iterator = Iterator<const pair_type, node_type>;
    /** using declaration for pair_type. Represents an iterator class, defined by a pair type and node type. */
    using iterator = Iterator<pair_type, node_type>;

    /** \brief head
     * 
     * Root of the tree as \private head */
    std::unique_ptr<node_type> head;

    /** \brief size
     * 
     * Size of the tree as \private _size .*/
    std::size_t _size;

    /**  \brief compare two nodes
     * 
     * Compare two nodes, as \private comp.*/
    comparison comp;

    /** \brief internal insert
     * 
     * Private function to insert node. \p x passed as r-value, of typename O. */
    template<typename O>
    std::pair<iterator, bool> _insert(O&& x);

    /** \brief internal find
     * 
     * Private function for finding a node based on key. \p x passed as r-value, of typename T. */
    template<typename T>
    node_type* _find(T&& x) const noexcept;

    /** \brief internal print2D
     * 
     * Private function for printing tree in 2D */
    void _print2D(node_type *root, int space) const noexcept;


    /** \brief repopulate the tree
     * 
     * Function to properly repopulate tree. \p child passed, pointer to a node type. 
     * Used after erasing a node in the tree.*/
    void repopulate(node_type* child);

    /** \brief recursive insert for balance
     * 
     * Auxiliary function for balance tree, recursive. The vector that holds the tree nodes, gets to be divided by the median. 
     * Each splitted vector gets its' median inserted into the new, balanced tree. 
     * Process repeated for each section divided by the median.
     * Process stops when median doesn't hold anymore a positive value.*/
    void insert_balanced_node(std::vector<pair_type> vec);


    public:

    /** \brief Default iterator Constructor */
    bst() = default;
    /** \brief Default iterator Destructor */
    ~bst() noexcept = default;

    /** \brief 
     * 
     * Move constructor */
    explicit bst(bst&& other) noexcept = default;
    /** \brief 
     * 
     * Move assignment */
	bst& operator=(bst&& other) noexcept = default;

    /** \brief 
     * 
     * Deep-copy constructor */
    explicit bst(const bst& other):
    _size{other._size}, comp{other.comp} {
        if(other.head)
            head.reset(new node_type{*(other.head.get())});
    }

    /** \brief 
     * 
     * Deep-copy assignment */
    bst& operator=(const bst& x) {
        auto tmp {x}; // copy ctor
        *this = std::move(tmp); // move assignment
        return *this;    
    }

    /** \brief delete tree
     * 
     * Function to clear the contents of the tree by setting head to null-pointer. */
    void clear() {
        head.reset(nullptr);
        _size = 0;
    }
    
    /** \brief pretty print
     * 
     * Function for a 2D design of the existing tree */
    void print2D() const noexcept {  
        _print2D(head.get(), 0);  
    } 

    /** \brief begin of for loop with iterator
     * 
     * Return an iterator to the left-most node (which, likely, is not the root node).
     * The returning value is obtained using the fucntion leftiest(),
     * which finds the leaf node placed at the very far left*/
    iterator begin() noexcept{
        return iterator{head.get()->leftiest()};
    }

    /** \brief const begin of for loop with iterator
     * 
     * Return a const iterator to the left-most node (which, likely, is not the root node).
     * The returning value is obtained using the fucntion leftiest(),
     * which finds the leaf node placed at the very far left*/
    const_iterator begin() const noexcept {
        return const_iterator{head.get()->leftiest()};
    }

    /** \brief const begin of for loop with iterator
     * 
     * Return a const iterator to the left-most node (which, likely, is not the root node).
     * The returning value is obtained using the fucntion leftiest(),
     * which finds the leaf node placed at the very far left*/
    const_iterator cbegin() const noexcept {
        return const_iterator{head.get()->leftiest()};
    }

    /** \brief end of for loop with iterator
     * 
     * Returns an iterator to one-past the last element. 
     * Basically an iterator initialized to a nullptr*/
    iterator end() noexcept {
        return iterator{nullptr};
    }

    /** \brief const end of for loop with iterator
     * 
     * Returns a const iterator to one-past the last element.
     * Basically a const_iterator initialized to a nullptr*/
    const_iterator end() const noexcept {
        return const_iterator{nullptr};
    }

    /** \brief const end of for loop with iterator
     * 
     * Returns a const iterator to one-past the last element.
     * Basically a const_iterator initialized to a nullptr*/
    const_iterator cend() const noexcept{
        return const_iterator{nullptr};
    }

    /** \brief find element in tree
     * 
     * Find a given key, \p x passed as l-value. 
     * If the key is present, returns an iterator to the proper node; if not
     * the function _find() returns a nullptr, so same result as end().
     */
    iterator find(const key_type& x) noexcept{
        return iterator{_find(x)}; 
    }

    /** \brief const find element in tree by key
     * 
     * Find a given key, \p x passed as l-value. 
     * If the key is present, returns a const_iterator to the proper node; if not
     * the function _find() returns a nullptr, so same result as cend().
     */
    const_iterator find(const key_type& x) const noexcept{
        return const_iterator{_find(x)};
    }

    /** \brief insert node by pair
     * 
     * Function to insert node based on \p x , as const l-value reference pair type. 
     * The function returns a pair of an iterator (pointing to the node) and a bool. 
     * The bool is true if a new node has been allocated, false otherwise.
     */
    std::pair<iterator, bool> insert(const pair_type& x) {
        return _insert(x);
    }
    
    /** \brief const insert node by pair
     * 
     * Function to insert node based on \p x , as r-value reference pair type. 
     * The function returns a pair of an iterator (pointing to the node) and a bool. 
     * The bool is true if a new node has been allocated, false otherwise.
     */
    std::pair<iterator, bool> insert(pair_type&& x) {
        return _insert(std::move(x));
    }

    /** \brief emplace element
     * 
     * Inserts a new element into the container constructed in-place with the given args 
     * if there is no element with the key in the container.
     */
    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args) {
        return insert(std::make_pair(std::forward<Types>(args)...));
    }

    /** \brief erase element from tree
     * 
     * Function that removes the element (if one exists) with the key equivalent to key. 
     * When element found, deleted. After erase, tree repopulated.
     * Takes const \p x , l-value reference of type key. */
    void erase(const key_type& x);

    /** \brief balance tree
     * 
     * Function to balance the tree.*/
    void balance();
    
    /** \brief depth of tree
     * 
     * Returns depth of the tree. */
    std::size_t size() const noexcept{
        return this->_size;
    }

    /** \brief put-to
     * 
     * Put-to operator, takes instance of ostream, and \p x as l-value reference to bst type. 
     */
    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) {
        os << "Depth of the tree is: " << x.size() << "\n";
        for(const auto& el : x) {
            os << "[ key=" << el.first <<" , value=" << el.second << " ] ";
        }
        os << std::endl;
        return os;
    }

    /** \brief subscripting l-value 
     * 
     * Subscripting operator, takes \p x as l-value reference, of type key.
     * Returns a reference to the value that is mapped to a key equivalent to x, 
     * performing an insertion if such key does not already exist.
     * Takes advantage of the already defined insert() function.
     */
    value_type& operator[](const key_type& x){
        iterator it = find(x);
        if(it != iterator{nullptr})
            return it->second;

        return insert(pair_type{x,{}}).first->second;
    }
    
    /** \brief subscripting r-value
     * 
     * Subscripting operator, takes \p x as r-value reference, of type key.
     * Returns a reference to the value that is mapped to a key equivalent to x, 
     * performing an insertion if such key does not already exist.
     * Takes advantage of the already defined insert() function.
     */
    value_type& operator[](key_type&& x){
        iterator it = find(std::move(x));
        if(it != iterator{nullptr})
            return it->second;

        return insert(pair_type{std::move(x),{}}).first->second;
    } 
};


template<typename key_type, typename value_type, typename comparison>
template<typename O>
std::pair<typename bst<key_type, value_type, comparison>::iterator, bool> bst<key_type, value_type, comparison>::_insert(O&& x){
    auto start = std::chrono::high_resolution_clock::now(); 
    auto _node = new node<O>{std::forward<O>(x)};
    auto tmp = head.get();
    bool added = false;
    if (!tmp) {
        // our list is empty
        head.reset(_node);
        added = true;
        std::cout << "root insert" << std::endl;
        auto stop = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
  
        std::cout << "Time taken by insert: " << duration.count() << " microseconds" << std::endl; 

        return std::make_pair(Iterator<O,node<O>>{_node},added);
    }

    else {
        auto parent {tmp};
        int flag {0};
        // checking if we have to go left or right
        while(tmp) {
            // go right
            if(comp(tmp->get_data().first, x.first)) {
                parent = tmp;
                tmp = tmp->get_right();
                flag = 0;
            }
            // go left
            else if(comp(x.first, tmp->get_data().first)){
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
                if(!parent->get_left()){
                    ++_size;
                }
                std::cout << "right insert" << std::endl;
                break;
            case 1:
                parent->left_child.reset(final_node);
                if(!parent->get_right()){
                    ++_size;
                }
                std::cout << "left insert" << std::endl;
                break;
            default:
                std::cout << "node was already present" << std::endl;
                break;
        }
    }
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start); 
  
    std::cout << "Time taken by insert: " << duration.count() << " microseconds" << std::endl; 

    return std::make_pair(Iterator<O,node<O>>{_node},added);
}


template<typename key_type, typename value_type, typename comparison>
template<typename T>
node<std::pair<const key_type, value_type>>* bst<key_type, value_type, comparison>::_find(T&& x) const noexcept{

    auto start = std::chrono::high_resolution_clock::now(); 
    auto tmp {head.get()};
    // checking if we have to go left or right
    while(tmp) {
        // go right
        if(comp(tmp->get_data().first, x)) {
            tmp = tmp->get_right();
        }
        // go left
        else if(comp(x, tmp->get_data().first)){
            tmp = tmp->get_left();
        }
        // this means that we have found that there already is a node
        // with same key w.r.t. the one we wanted to insert
        else {
            std::cout << "Found node with key = "<< x << std::endl;  

            auto stop = std::chrono::high_resolution_clock::now(); 
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
            std::cout << "Time taken by find: " << duration.count() << " microseconds" << std::endl; 

            return tmp;
        }  
    }
    std::cout << "Node with key = "<< x  << " is not present" << std::endl;
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Time taken by find: " << duration.count() << " microseconds" << std::endl; 
    return nullptr;
}


template<typename key_type, typename value_type, typename comparison>
void bst<key_type, value_type, comparison>::repopulate(node_type* child){
    if(child->get_left()){
        repopulate(child->get_left());
    }
    if(child->get_right()){
        repopulate(child->get_right());
    }
    const pair_type i = child->get_data();
    std::cout << "Repopulating node with key: "<<i.first<< " value: "<<i.second<< std::endl;

    emplace(i.first, i.second);
}


template<typename key_type, typename value_type, typename comparison>
void bst<key_type, value_type, comparison>::erase(const key_type& x){
    auto start = std::chrono::high_resolution_clock::now();
    auto tmp {head.get()};
    if(tmp){
        bool isPresent{false};
        while(tmp) {
            // go right
            if(comp(tmp->get_data().first, x)) {
                tmp = tmp->get_right();
            }
            // go left
            else if(comp(x, tmp->get_data().first)){
                tmp = tmp->get_left();
            }
            // this means that we have found that there already is a node
            // with same key w.r.t. the one we wanted to erase
            else {
                isPresent = true;
                bool hasRight{false};
                bool hasLeft{false};
                //save the children before erasing the father
                auto rightChild = new node_type{nullptr};
                auto leftChild = new node_type{nullptr};
                if(tmp->get_right()){
                     rightChild = new node_type{*(tmp->get_right())};
                     hasRight = true;
                }

                if(tmp->get_left()){
                     leftChild = new node_type{*(tmp->get_left())};
                     hasLeft = true;
                }

                //erase
                if(tmp != head.get()) {
                    if(tmp->get_parent()->get_left() == tmp) {
                        tmp->parent_node->left_child.release();
                    }
                    if(tmp->get_parent()->get_right() == tmp) {
                        tmp->parent_node->right_child.release();
                    }
                }
                else {
                    std::cout << "deleting root node" << std::endl;
                    clear();
                }

                tmp->parent_node = nullptr;
                tmp->left_child.reset();
                tmp->right_child.reset();
                tmp = nullptr;

                //insert all the "sub-tree" that starts from temp in order to keep the correct structure of bst
                if(hasRight)
                    repopulate(rightChild);
                if(hasLeft)
                    repopulate(leftChild);
                
                std::cout << "Erased node with key = "<< x << std::endl;
            } 
        }
        if(!isPresent){
            std::cout << "Node with key = "<< x << " not found" <<std::endl;
        }
        auto stop = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
        std::cout << "Time taken by erase: " << duration.count() << " microseconds" << std::endl; 
    }
    else{
        throw std::logic_error{"In function erase(): there is not a root node"};
    }
}


template<typename key_type, typename value_type, typename comparison>
void bst<key_type, value_type, comparison>::balance(){
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<pair_type> v{};

    for(iterator it = begin(); it != end(); ++it){
        v.push_back(*it);
    }
    clear();
    insert_balanced_node(v);
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Time taken by balance: " << duration.count() << " microseconds" << std::endl;
}



template<typename key_type, typename value_type, typename comparison>
void bst<key_type, value_type, comparison>:: insert_balanced_node(std::vector<pair_type> vec){
    
    if(vec.size() > 0){
        std::size_t const median = vec.size()/2;
        emplace(vec[median].first, vec[median].second);
        if(median > 0){
            std::vector<pair_type> split_left(vec.begin(), vec.begin() + median);
            std::vector<pair_type> split_right(vec.begin() + median + 1, vec.end());
            insert_balanced_node(split_left);
            insert_balanced_node(split_right);
        }
    }
    else{
        return;
    }    
}
 

template<typename key_type, typename value_type, typename comparison>
void bst<key_type, value_type, comparison>::_print2D(node_type *root, int space) const noexcept{   
    if (root == NULL)  
        return;  

    // Increase distance between levels  
    space += COUNT;  

    // Process right child first  
    _print2D(root->get_right(), space);  

    // Print current node after space  
    // count  
    std::cout<<std::endl;  
    for (int i = COUNT; i < space; i++)  
        std::cout<<" ";  
    std::cout<< root->get_data().first <<"\n";  

    // Process left child  
    _print2D(root->get_left(), space);  
}  
