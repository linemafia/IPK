#ifndef HH_HUFFMAN
#define HH_HUFFMAN

#include "tree.hh"

#include <iostream>
#include <vector>
#include <map>
#include <memory> // for std::shared_ptr
#include <queue> // for std::priority_queue
#include <algorithm>

#include <fstream> // for huffman_main.cc !!!

// b)
using HuffmanNode = BinaryTreeNode<char>;
using HuffmanPointer = std::shared_ptr<HuffmanNode>;
using WeightedHuffmanPointer = std::pair<int, HuffmanPointer>;
using BitVector = std::vector<bool>; // 1 => right; 0 => left
using CodeMap = std::map<char, BitVector>;
// end b)

// e_2)
using HuffmanCompareFunktion = std::function<bool(WeightedHuffmanPointer, WeightedHuffmanPointer)>;
// end e_2)

// funktions:

// a)
std::map<char, int> countCharacterFrequency(const std::string & text);
// end a)

// c)
template<typename T>
bool isWeightGreater(const std::pair<int, T>& left, const std::pair<int, T> right);
// end c)

// h)
// returns "is the left pair smaller?"
// 101 < 111 < 0001 < 0010 < 0101
bool sortByCode(const std::pair<char, BitVector>& left, const std::pair<char, BitVector>& right);
// end h)

// i_1)
std::string boolVectorToString(const BitVector& vec);
// end i_1)


// Funktion with a template -> in .hh
// c)
template<typename T>
bool isWeightGreater(const std::pair<int, T>& left, const std::pair<int, T> right) {
    return left.first > right.first;
}
// end c)

class Huffman {
    public:
        // g)
        Huffman(const std::string& text) : root(buildHuffmanTree(text)), codeMap() {
            generateHuffmanCodes();
        }
        // end g)

        // i_2)
        // "r: 0110"
        // sorted!!!
        void printHuffmanCodes() {
            std::vector<std::pair<char, BitVector>> sortedCodes(codeMap.begin(), codeMap.end());
            std::sort(sortedCodes.begin(), sortedCodes.end(), sortByCode);
            for (const std::pair<char, BitVector>& charVecPair : sortedCodes) {
                std::cout << charVecPair.first << ": " << boolVectorToString(charVecPair.second) << std::endl;
            }
        }
        void print() { // in huffman_main.cc
            printHuffmanCodes();
        }
        // end i_2)

        // j)
        void encode(const std::string& text, BitVector& vecOut) {
            for (const char ch : text) {
                const BitVector charCode = codeMap[ch];
                for (bool bit : charCode)
                    vecOut.push_back(bit);
            }
        }
        // end j)

        // k)
        std::string decode(const BitVector& vecCoded) const {
            std::string strOut;
            HuffmanPointer nowNodePtr = root;
            for (const bool bitNow : vecCoded) {
                if (bitNow) 
                    nowNodePtr = nowNodePtr -> getRight();
                else
                    nowNodePtr = nowNodePtr -> getLeft();
                if (nowNodePtr -> isLeaf()) {
                    strOut.push_back(nowNodePtr -> getValue());
                    nowNodePtr = root;
                }
            }
            return strOut;
        }
        // end k)
        
    private:
        // d)
        HuffmanPointer root;
        CodeMap codeMap;
        // end d)

        // e_1)
        HuffmanPointer buildHuffmanTree(const std::string& text) const {
            std::map<char, int> frequency = countCharacterFrequency(text);
            std::priority_queue<WeightedHuffmanPointer, std::vector<WeightedHuffmanPointer>, HuffmanCompareFunktion> queue(isWeightGreater<HuffmanPointer>);
            
            // create Nodes <int, HuffmanPointer>
            for (const std::pair<const char, int>& charFreq : frequency) {
                HuffmanPointer nodePtr = std::make_shared<HuffmanNode>(charFreq.first);
                int weight = (int) charFreq.second;
                queue.push(std::make_pair(weight, nodePtr));
            }

            unsigned int numberOfIterations = queue.size() - 1; // every iteration: -1 element in queue. in the end: onle root in queue
            for (unsigned int iteration = 0; iteration < numberOfIterations; iteration ++) {
                // get the two least frequent nodes: <int, ptr>
                WeightedHuffmanPointer nodePtr1 = queue.top();
                queue.pop();
                WeightedHuffmanPointer nodePtr2 = queue.top();
                queue.pop();
                
                // push a new <int, prt> in the queue 
                HuffmanPointer newNodePtr = std::make_shared<HuffmanNode>(nodePtr1.second, nodePtr2.second);
                int newWeight = nodePtr1.first + nodePtr2.first;
                queue.push(std::make_pair(newWeight, newNodePtr));
            }
            return queue.top().second; // the root
        }
        // end e_1)

        // f)
        void generateHuffmanCodes() {
            if (!root)
                return;
            BitVector way;
            recursiveGenerateHuffmanCodes(root, way);
        }

        void recursiveGenerateHuffmanCodes(const HuffmanPointer& nowPtr, BitVector& way) {
            if (nowPtr -> isLeaf()) {
                codeMap[nowPtr -> getValue()] = way;
                return;
            }
            // go to the left child
            way.push_back(false);
            recursiveGenerateHuffmanCodes(nowPtr -> getLeft(), way);

            // go to the right child
            *(way.end() - 1) = true;
            recursiveGenerateHuffmanCodes(nowPtr -> getRight(), way);
            way.pop_back();
            return;
        }
        // end f)
};

#endif