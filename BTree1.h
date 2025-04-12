#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

template <typename T>
struct TreeNode
{
    T data;
    shared_ptr<TreeNode<T>> leftChild;
    shared_ptr<TreeNode<T>> rightChild;

    TreeNode(const T &val) : data(val), leftChild(nullptr), rightChild(nullptr) {}
};

template <typename T>
class BTree
{
public:
    BTree() : rootNode(nullptr) {}

    void insert(const T &data)
    {
        rootNode = addNode(data, rootNode);
    }

    shared_ptr<TreeNode<T>> find(const T &data) const
    {
        return findNode(data, rootNode);
    }

    shared_ptr<TreeNode<T>> findRightMostNode(shared_ptr<TreeNode<T>> node) const
    {
        while (node && node->rightChild)
        {
            node = node->rightChild;
        }
        return node;
    }

    shared_ptr<TreeNode<T>> findParent(shared_ptr<TreeNode<T>> child) const
    {
        return findParentNode(rootNode, child);
    }

    void remove(const T &data)
    {
        rootNode = removeNode(data, rootNode);
    }

    void inOrder() const
    {
        traverseInOrder(rootNode);
        cout << endl;
    }

private:
    shared_ptr<TreeNode<T>> rootNode;

    shared_ptr<TreeNode<T>> addNode(const T &data, shared_ptr<TreeNode<T>> currentNode)
    {
        if (!currentNode)
        {
            return make_shared<TreeNode<T>>(data);
        }
        if (data < currentNode->data)
        {
            currentNode->leftChild = addNode(data, currentNode->leftChild);
        }
        else
        {
            currentNode->rightChild = addNode(data, currentNode->rightChild);
        }
        return currentNode;
    }

    shared_ptr<TreeNode<T>> findNode(const T &data, shared_ptr<TreeNode<T>> node) const
    {
        if (!node || node->data == data)
        {
            return node;
        }
        if (data < node->data)
        {
            return findNode(data, node->leftChild);
        }
        return findNode(data, node->rightChild);
    }

    shared_ptr<TreeNode<T>> findParentNode(shared_ptr<TreeNode<T>> parent, shared_ptr<TreeNode<T>> child) const
    {
        if (!parent || parent->leftChild == child || parent->rightChild == child)
        {
            return parent;
        }
        if (child->data < parent->data)
        {
            return findParentNode(parent->leftChild, child);
        }
        return findParentNode(parent->rightChild, child);
    }

    shared_ptr<TreeNode<T>> removeNode(const T &data, shared_ptr<TreeNode<T>> node)
    {
        if (!node)
        {
            return nullptr;
        }
        if (data < node->data)
        {
            node->leftChild = removeNode(data, node->leftChild);
        }
        else if (data > node->data)
        {
            node->rightChild = removeNode(data, node->rightChild);
        }
        else
        {
            if (!node->leftChild)
            {
                return node->rightChild;
            }
            if (!node->rightChild)
            {
                return node->leftChild;
            }
            auto rightMost = findRightMostNode(node->leftChild);
            node->data = rightMost->data;
            node->leftChild = removeNode(rightMost->data, node->leftChild);
        }
        return node;
    }

    void traverseInOrder(shared_ptr<TreeNode<T>> node) const
    {
        if (node)
        {
            traverseInOrder(node->leftChild);
            cout << node->data << " ";
            traverseInOrder(node->rightChild);
        }
    }
};