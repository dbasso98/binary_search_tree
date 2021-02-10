//DSSC 2020/2021 AP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>  // std::unique_ptr
#include <utility> // std::move


enum class Method { push_left, push_right };

template <typename key_type, typename value_type, typename comparison = std::less<key_type>> 
class bst{
    using pair_type = std::pair<key_type,value_type>;

    struct node{
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;
    pair_type data;
    key_type key = std::get<0>(data);
    value_type value = std::get<1>(data);
    

    explicit node(const pair_type& x): data{x}, left(nullptr), right(nullptr) {};
    node(const pair_type &x, node* p1, node* p2):left{p1}, right{p2}, data{x} {} //raw pointer here? 21:00 linkedlist vid

    explicit node(key_type&& x): key{std::move(x)}, value{std::move(0)}, left(nullptr), right(nullptr) {}; //r-value
    node(key_type &&x, node *p1, node *p2) : left{p1}, right{p2}, key{std::move(x)} {};

    explicit node(const key_type &x): key{x}, value{0}, left(nullptr), right(nullptr) {}; //l-value
    
    };

    std::unique_ptr<node> head;
    std::size_t _size;



    // TODO comparison template
    // template <typename node>
    // node smaller_node(const node& a,const node& b) {
    //     //TODO IF
    //   std::less<a.property.first>
    // return 
    // }
    void push_left(const pair_type& x);
    void push_right(const pair_type& x);

    template <typename O> void push_left(O &&x) {
    auto _node = new node{std::forward<O>(x)};
    auto tmp = head.get();
    if (!tmp) { // if tmp == nullptr
      // our list is empty
      head.reset(_node);
      return;
    }

    while (tmp->left) // while tmp->next.get() != nullptr
      tmp = tmp->left.get();

    tmp->left.reset(_node);

    }

    template <typename O> void push_right(O &&x) {
    auto _node = new node{std::forward<O>(x)};
    auto tmp = head.get();
    if (!tmp) { // if tmp == nullptr
      // our list is empty
      head.reset(_node);
      return;
    }
    }

    template <typename O>
    void _insert(O&& x, const Method m);

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

  void insert(const key_type &x, const Method m) { _insert(x, m); }
  void insert(key_type&& x, const Method m) { _insert(std::move(x), m); }


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
void bst<key_type, value_type, comparison>::_insert(O&& x, const Method m){
  std::cout << "forwarding insert" << std::endl;
  switch(m){
  case Method::push_left:
    push_left(std::forward<O>(x)); 
    break;
  case Method::push_right:
    push_right(std::forward<O>(x));
    break;
  default:
    std::cerr << "unknown method" << std::endl;
    break;
    
  };
  ++_size;

}

int main() {
  bst<int,int,bool> bst1{};
  
  int a = 8;
  int b = 3;
  bst1.insert(a, Method::push_left);
  bst1.insert(b, Method::push_left);
  //std::cout << bst1 << std::endl;

}