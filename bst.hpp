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

    template<typename T>
    const_iterator _find(T&& x) const noexcept{
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
                return const_iterator{tmp};
            }  
        }
        return end();
    }

    template<typename T>
    iterator _find(T&& x) noexcept{
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
                return iterator{tmp};
            }  
        }
        return end();
    }

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
        return _find(x);
        
    }
    const_iterator find(const key_type& x) const noexcept{
        return _find(x);
    }

    /*
    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args);
    */

    template< class... Types >
    std::pair<iterator,bool> emplace(Types&&... args) {
        return insert(std::make_pair(std::forward<Types>(args)...));
    }

    std::pair<iterator, bool> insert(const pair_type& x) {
        return _insert(x);
    }
    
    std::pair<iterator, bool> insert(pair_type&& x) {
        return _insert(std::move(x));
    }

    void repopulate(node_type* child){
        if(child->get_left()){
            repopulate(child->get_left());
        }
        if(child->get_right()){
            repopulate(child->get_right());
        }
        auto info{child->get_data()};
        _insert(info);
        //child = nullptr;
    }
    void erase(const key_type& x){
        auto tmp {head.get()};
        if(tmp){
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
                //save the children before erasing the father
                auto rightChild{tmp->get_right()};
                auto leftChild{tmp->get_left()};
                //erase
                auto to_delete = std::move(tmp);
                //to_delete = nullptr;
                tmp = nullptr;
                //free(tmp);
                free(to_delete);
                //delete to_delete;
                //insert all the "sub-tree" that starts from temp in order to keep the right structure of bst
                if(rightChild)
                    repopulate(rightChild);
                if(leftChild)
                    repopulate(leftChild);
                } 
            }
        }
    }
    
    std::size_t size() const noexcept{
        return this->_size;
    }
    // operators overload

    friend
    std::ostream& operator<<(std::ostream& os, const bst& x) {
        os << "Size of the tree is: " << x.size() << "\n";
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