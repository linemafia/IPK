#include "huffman.hh"
#include <string>
#include <map>

// a)
std::map<char, int> countCharacterFrequency(const std::string & text) {
    std::map<char, int> frequency;
    for (const char ch : text)
        if (frequency.count(ch) == 0)
            frequency[ch] = 1;
        else
            frequency[ch]++;
    return frequency;
}
// end a)

// c)
template<typename T>
bool isWeightGreater(const std::pair<int, T>& left, const std::pair<int, T> right) {
    return left.first > right.first;
}
// end c)

// h)
// returns "is the left pair smaller?"
// 101 < 111 < 0001 < 0010 < 0101
bool sortByCode(const std::pair<char, BitVector>& left, const std::pair<char, BitVector>& right) {
    return left.second < right.second;
    /*
    unsigned int leftSize = left.second.size();
    unsigned int rightSze = right.second.size();

    // different lengths
    if (leftSize != rightSize)
        return leftSize < rightSize;

    // search for the first different bit
    BitVector::iterator itLeft, itRight;
    itLeft = left.second.begin();
    itRight = right.second.begin();
    itEnd = left.second.end();
    while ((itLeft != itEnd) && (*itLift == *itRight)) {
        itLeft ++;
        itRight ++;
    }
    // all bits are the same
    if (itLeft == itEnd)
        return false;

    return *itLeft < *itRight;   
    */
}
// end h)

// i_1)
std::string boolVectorToString(const BitVector& vec) {
    std::string code(vec.size(), '0');
    std::string::iterator itStr = code.begin();
    std::string::iterator itStrEnd = code.end();
    BitVector::iterator itVec = vec.begin();
    while (itStr != itStrEnd) {
        if (*itVec)
            *itStr = '1';
        itStr ++; itVec ++;
    }
    return code;
}
// end i_1)