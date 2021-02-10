//DSSC 2020/2021 

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>  // std::unique_ptr
#include <utility> // std::move


template <typename key_type, typename value_type, typename comparison = std::less<key_type>> 
class bst{
    using pair_type = std::pair<key_type,value_type>;

    struct node{
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    pair_type data;
    
    //key_type key = std::get<0>(data);
    //value_type value = std::get<1>(data);
 

    explicit node(const pair_type &x): data{x}, left(nullptr), right(nullptr) {};
    node(const pair_type &x, node* p1, node* p2):left{p1}, right{p2}, data{x} {} //raw pointer here? 21:00 linkedlist vid

    explicit node(pair_type&& x): data{std::move(x)}, left(nullptr), right(nullptr) {}; //r-value
    node(pair_type &&x, node *p1, node *p2) : left{p1}, right{p2}, data{std::move(x)} {};

    //explicit node(const key_type &x): key{x}, value{0}, left(nullptr), right(nullptr) {}; //l-value
    
    };

    std::unique_ptr<node> head;
    std::size_t _size;
    comparison comp;


    // TODO comparison template
    // template <typename node>
    // node smaller_node(const node& a,const node& b) {
    //     //TODO IF
    //   std::less<a.property.first>
    // return 
    // }

    template <typename O> void push(O &&x) {
    auto _node = new node{std::forward<O>(x)};
    auto tmp = head.get();
    if (!tmp) { // if tmp == nullptr
      // our list is empty
      head.reset(_node);
      return;
    }
    }
    
    // if(comparison(std::get<0>(x),tmp->std::get<0>(data))){
    //   while (tmp->left) // while tmp->next.get() != nullptr
    //     tmp = tmp->left.get();     
    // }
    
    // if(comparison(std::get<0>(x),tmp->std::get<0>(data)))
    //     tmp->left.reset(_node);
    // else
    //     tmp->right.reset(_node);

    // }

    template <typename O>
    void _insert(O&& x);

//     while (tmp->next ) // while tmp->next.get() != nullptr
//       tmp = tmp->next.get();

//     tmp->next.reset(_node);
//   }

public:
  // constructors
  bst() = default; // default ctor      
  
  bst(bst&&) = default;
  bst& operator=(bst&&) = default;

  bst(const bst& x): _size{x._size} {
    
    if(x.head)
      head.reset(new node{x.head});

    // auto tmp = x.head.get();
    // while(tmp){
    //   insert(tmp->value, Method::push_back);
    // tmp = tmp->next.get();
    // }
  }

  void insert(const pair_type &x) { _insert(x); }
  void insert(pair_type&& x) { _insert(std::move(x)); }


//   friend std::ostream &operator<<(std::ostream &os, const bst &x) {
//     os << "[" << x._size << "] ";
//     for (const auto &el : x)
//       os << x << " ";

//     os << std::endl;
//     return os;
//   }

  
  ~bst() noexcept = default; //default dtor
  


};



template <typename key_type, typename value_type, typename comparison>
template <typename O>
void bst<key_type, value_type, comparison>::_insert(O&& x){
  std::cout << "forwarding insert" << std::endl;
    push(std::forward<O>(x)); 
  ++_size;
}

int main() {
  bst<int,int,bool> bst1{};
  
  auto p1 = std::make_pair(8, 0);
 
  bst1.insert(p1);
  //bst1.insert(b);
  //std::cout << bst1 << std::endl;

}