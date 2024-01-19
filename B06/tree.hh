#ifndef H_TREE
#define H_TREE

#include <memory>

template<typename Value>
class BinaryTreeNode {
    private:
        Value val;
        std::shared_ptr<BinaryTreeNode> leftChild;
        std::shared_ptr<BinaryTreeNode> rightChild;
        bool leaf;
    public:
        // leaf-constructor
        BinaryTreeNode(const Value& valInit) : val(valInit), leaf(true) {}

        // non-leaf-constructor
        BinaryTreeNode(const std::shared_ptr<Value>& leftChInit, const std::shared_ptr<Value>& rightChInit) : 
                leftChild(leftChInit), rightChild(rightChInit), val() {};

        // methods
        Value getValue() const { return val; }
        std::shared_ptr<BinaryTreeNode<Value>> getLeft() const { return leftChild; }
        std::shared_ptr<BinaryTreeNode<Value>> getRight() const { return rightChild; }
        bool isLeaf() const { return leaf; }
};

#endif