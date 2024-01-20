#ifndef H_TREE
#define H_TREE

#include <memory>

template<typename Value>
class BinaryTreeNode {
    private:
        Value val;
        std::shared_ptr<BinaryTreeNode<Value>> leftChild;
        std::shared_ptr<BinaryTreeNode<Value>> rightChild;
        bool leaf;
    public:
        // leaf-constructor
        BinaryTreeNode(const Value& valInit) : 
                val(valInit), leftChild(), rightChild(), leaf(true) {}

        // non-leaf-constructor
        BinaryTreeNode(const std::shared_ptr<BinaryTreeNode<Value>>& leftChInit, const std::shared_ptr<BinaryTreeNode<Value>>& rightChInit) : 
                val(), leftChild(leftChInit), rightChild(rightChInit), leaf(false) {};

        // methods
        Value getValue() const { return val; }
        std::shared_ptr<BinaryTreeNode<Value>> getLeft() const { return leftChild; }
        std::shared_ptr<BinaryTreeNode<Value>> getRight() const { return rightChild; }
        bool isLeaf() const { return leaf; }
};

#endif