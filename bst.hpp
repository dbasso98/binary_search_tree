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

    void repopulate(node_type* child);

    template<typename T>
    node_type* _find(T&& x) noexcept;

    void _print2D(node_type *root, int space) const noexcept;

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
        this->clear();
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

    iterator find(const key_type& x) noexcept{
        return iterator{_find(x)};
        
    }
    const_iterator find(const key_type& x) const noexcept{
        return const_iterator{_find(x)};
    }

    std::pair<iterator, bool> insert(const pair_type& x) {
        return _insert(x);
    }
    
    std::pair<iterator, bool> insert(pair_type&& x) {
        return _insert(std::move(x));
    }

    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args) {
        return insert(std::make_pair(std::forward<Types>(args)...));
    }

    void erase(const key_type& x);
    
    std::size_t size() const noexcept{
        return this->_size;
    }

    // operators overload

    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) {
        os << "Depth of the tree is: " << x.size() << "\n";
        for(const auto& el : x) {
            os << "[ key=" << el.first <<" , value=" << el.second << " ] ";
        }
        os << std::endl;
        return os;
    }

    value_type& operator[](const key_type& x){
        iterator it = find(x);
        if(it != iterator{nullptr})
            return it->second;

        return insert(pair_type{x,{}}).first->second;
    }
 
    value_type& operator[](key_type&& x){
        iterator it = find(std::move(x));
        if(it != iterator{nullptr})
            return it->second;

        return insert(pair_type{std::move(x),{}}).first->second;
    }
    
    void print2D() noexcept {  
        _print2D(head.get(), 0);  
    }  
    
};


template<typename key_type, typename value_type, typename comparison>
template<typename O>
std::pair<Iterator<O,node<O>>, bool> bst<key_type, value_type, comparison>::_insert(O&& x){
    auto start = std::chrono::high_resolution_clock::now(); 
    auto _node = new node<O>{std::forward<O>(x)};
    auto tmp = head.get();
    bool added = false;
    if (!tmp) { // if tmp == nullptr
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
node<std::pair<const key_type, value_type>>* bst<key_type, value_type, comparison>::_find(T&& x) noexcept{

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
    std::cout << "Node with key = "<< x  << "is not present" << std::endl;
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);  
    std::cout << "Time taken by find: " << duration.count() << " microseconds" << std::endl; 
    return end().current;
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
                //save the children before erasing the father
                auto rightChild = new node_type{nullptr};
                auto leftChild = new node_type{nullptr};
                if(tmp->get_right())
                    rightChild = new node_type{tmp->right_child};
                if(tmp->get_left())
                    leftChild = new node_type{tmp->left_child};

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
                    this->clear();
                }

                tmp->parent_node = nullptr;
                tmp->left_child.reset();
                tmp->right_child.reset();
                tmp = nullptr;

                //insert all the "sub-tree" that starts from temp in order to keep the correct structure of bst
                if(rightChild)
                    repopulate(rightChild);
                if(leftChild)
                    repopulate(leftChild);
                
                std::cout << "Erased node with key = "<< x << std::endl;
            } 
        }
        if(!isPresent){
            std::cout << "Node with key = "<< x << "not found" <<std::endl;
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