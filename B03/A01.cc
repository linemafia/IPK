#include <iostream>
#include <list>

//a)
void reverseList(std::list<int>& list) {
    std::list<int>::iterator itRight, itLeft;
    itLeft = list.begin();
    itRight = list.end(); itRight --;
    while (itLeft != itRight) {
        std::swap(*itLeft, *itRight);
        itLeft++; 
        if (itLeft == itRight) return;
        itRight --;
    }
 }

 //b)
void zigzag(std::list<int>& list) {
    std::list<int> sortedList(list);
    sortedList.sort();
    std::list<int>::iterator itListNow, itSortedLeft, itSortedRight;
    itListNow = list.begin();
    itSortedLeft = sortedList.begin();
    itSortedRight = sortedList.end(); itSortedRight --;
    while (itListNow != list.end()) {
        *itListNow = *itSortedLeft;
        itListNow ++;
        itSortedLeft ++;
        if (itListNow == list.end()) {
            return;
        }
        *itListNow = *itSortedRight;
        itListNow ++;
        itSortedRight --;
    }
}

// str of a list
std::string strList(std::list<int>& list) {
    if (list.size() == 0) {
        return "[]";
    }
    std::list<int>::iterator itList = list.begin();
    std::string strOut = "[" + std::to_string(*itList);
    itList ++;
    for (; itList != list.end(); itList ++) {
        strOut += ", " + std::to_string(*itList); 
    }
    strOut += "]";
    return strOut;
}


//testing
void test(int testNumber, unsigned int n) {
    std::list<int> list;
    for (unsigned int i = 1; i <= n; i ++)
        list.push_back(i);
    std::cout << "Test " << testNumber << " : list = " << strList(list) << std::endl;
    reverseList(list);
    std::cout << "  reverseList : " << strList(list) << std::endl;
    zigzag(list);
    std::cout << "  zigzag : " + strList(list) << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

int main() {
    test(0, 0);
    test(1, 5);
    test(2, 6);
    
    std::cout << "Now you can enter one Test-list" << std::endl;
    std::cout << "Enter the length of your list: " << std::endl;
    unsigned int n; std::cin >> n;
    std::cout << "Now enter " << n << " numbers: " << std::endl;
    std::list<int> list(n);
    for (std::list<int>::iterator it = list.begin(); it != list.end(); it ++) {
        std::cin >> *it;
    }
    reverseList(list);
    std::cout << "  reverseList : " << strList(list) << std::endl;
    zigzag(list);
    std::cout << "  zigzag : " + strList(list) << std::endl;
    std::cout << std::endl;
}