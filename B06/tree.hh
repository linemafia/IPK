template<typename Value>
 class BimaryTreeNode {
    private:
        Value val;
        std::shared_ptr<Node> leftChild;
        std::shared_ptr<Node> rightChild;
        bool leaf;
    public:
        // leaf-constructor
        BimaryTreeNode(const Value& valInit) : val(valInit), leaf(true) {}

        // non-leaf-constructor
        BimaryTreeNode(const std::shared_ptr<Value>& leftChInit, const std::shared_ptr<Value>& rightChInit) : 
                leftChild(leftChInit), rightChild(rightChInit) {};

        // methods
        Value getValue() const { return val; }
        std::shared_ptr<BimaryTreeNode<Value>> getLeft() const { return leftChild; }
        std::shared_ptr<BimaryTreeNode<Value>> getRight() const { return rightChild; }
        bool isLeaf() const { return leaf; }
};