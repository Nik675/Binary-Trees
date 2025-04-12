#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node {

  T data;
  shared_ptr<Node<T>> left ;
  shared_ptr<Node<T>> right ;

  Node(const T& value) : data(value), 
                         left(nullptr), 
                         right(nullptr) {}
};

template <typename T>

class BTree {

public:
  BTree() : root(nullptr) {}

  void insert(const T& item) {

    root = insert(item, root);

  }

  void preOrder() {

    preOrder(root);
    cout << endl;

  }

  void inOrder() {

    inOrder(root);
    cout << endl;

  }

  void postOrder() {

    postOrder(root);
    cout << endl;

  }

  int nodeCount() {

    return nodeCount(root);

  }

  int leavesCount() {

    return leavesCount(root);

  }

private:
  shared_ptr<Node<T>> root;

  shared_ptr<Node<T>> insert(const T& item, shared_ptr<Node<T>> ptr) 
  {
    if (!ptr) {

      return make_shared<Node<T>>(item);

    }
    if (item < ptr->data) {
      ptr->left = insert(item, ptr->left);

    } else {

      ptr->right = insert(item, ptr->right);
    }
    return ptr;
  }

  void preOrder(shared_ptr<Node<T>> ptr) 
  {
    if (ptr) {

      cout << ptr->data << " ";
      preOrder(ptr->left);
      preOrder(ptr->right);
      
    }
  }

  void inOrder(shared_ptr<Node<T>> ptr) {
    if (ptr) {
      inOrder(ptr->left);
      cout << ptr->data << " ";
      inOrder(ptr->right);
    }
  }

  void postOrder(shared_ptr<Node<T>> ptr) {
    if (ptr) {
      postOrder(ptr->left);
      postOrder(ptr->right);
      cout << ptr->data << " ";
    }
  }

  int nodeCount(shared_ptr<Node<T>> ptr) {
    if (!ptr) {
      return 0;
    }
    return 1 + nodeCount(ptr->left) + nodeCount(ptr->right);
  }

  int leavesCount(shared_ptr<Node<T>> ptr) {
    if (!ptr) {
      return 0;
    }
    if (!ptr->left && !ptr->right) {
      return 1;
    }
    return leavesCount(ptr->left) + leavesCount(ptr->right);
  }
};