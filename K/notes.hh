// !!! NEGATIVES: -7 % 3 = -1
// git -> lecture_04.pdf

// g++ -Wall -o helloworld helloworld.cc

// Exceptions:
namespace std {
    class logic_error;
        class domain_error;
        class invalid_argument;
        class length_error;
        class out_of_range;
    class runtime_error;
        class range_error;
        class overflow_error;
        class underflow_error;
}

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <exception>

#pragma once // damit mehrfach importierte Header nicht kollidieren

int main(int argc, char** argv) {}

// const, virtual, override!!!
class A {
    virtual float f() const {
        return 0;
    }
};
class B : public A {
    virtual float f() const override {
        return 1;
    }
};


typedef int Integer;
using Int = int;


//-----------------------------------------------------

// Typecasting:
//    static: 
        double d = static_cast<double>(5);
//    dynamic: 
        A* ptrA;
        A* a = dynamic_cast<A*>(ptrA);

// STL Algorithm:
    #include <algorithm>
    void STL_alg() {
        std::vector<int> v;
        std::sort(v.begin(), v.end());
        std::find(v.begin(), v.end(), 57);
    }

// Files:
    #include <fstream>
    void files() {
    //- std::ofstream - output
        std::ofstream oFile("filename.txt");
        oFile << "Opened";
        oFile.close();
    //- std::ifstream - input
        std::ifstream iFile("filename.txt");
        std::string line;
        while (std::getline(iFile, line)) {
            std::cout << line << std::endl;
        }
        iFile.close();
    //- std::fstream - I/O
    }

// Smart Pointer:
    #include <memory>
    void pointer() {
        { // std::unique_ptr<Class> 
        std::unique_ptr<A> ptr(new A());
        ptr.reset();
        ptr.reset(new A());
        }
        { // std::shared_ptr<Class>;
        std::shared_ptr<A> ptr(new A());
        ptr = std::make_shared<A>(/*a, b, c*/);
        int n = ptr.use_count();
        }
        { // weak_ptr -- are not counted, cannot be used to access the object
        std::weak_ptr<A> wp;
        std::shared_ptr<A> sp = wp.lock(); // is counted again :)
        }
    }

// Class, operator overloading:
    class Q {
    private:
        static int gcd(int a, int b) {/*...*/}
    public:
        int n, m;
        Q(int _n, int _m) : n(0), m(1) {
            if (_m == 0)
                throw std::logic_error("Division by zero");
            int d = gcd(_n, _m); n = _n / d; m = _m / d;
            if (m < 0) { m = -m; n = -n;
            }
        }
        Q operator* (const Q& other) const {
            return Q(n * other.n, m * other.m);
        }
        Q& operator= (const Q& other) {
            n = other.n; m = other.m;
            return *this;
        }
        friend std::ostream& operator<< (std::ostream& s, const Q& obj) {
            s << obj.n << "/" << obj.m;
            return s;
        }
    };

// Array:
    #include <array>
    std::array<int, 3> v{1,2,3};
    // length - known at the compile-time!!! 

// Vector:
    #include <vector>
    void vector() {
        std::vector<int> v;
        v.push_back(1);
        v.pop_back(); // void
        v.resize(1); // now v.size() = 1;
    }

// List:
    #include <list>
    ??? - Zettel

// Map: 
    // unordered_map: <unordered_map>
    #include <map>
    void dict() {
        std::map<int, std::string, std::less<int>> name;
        name[1] = "name";
        name.insert({2, "two"});
        if (name.count(3))
            name.erase(3);
        name[3] = "three";
        for (std::pair<const int, std::string>& pair : address) {
            std::cout << pair.first << " : " << pair.second << std::endl;
        }
    }

// Pair:
    #include <utility>
    void pairs() {
        std::pair<int, double> p = std::make_pair(0, 1.0);
        p.first = 1;
        p.second = 0.0;
    }
// Tuple:
    #include <tuple>
    void tuples() { 
        std::tuple<int, double, std::string> t(1, 2.0, "3");
        std::get<2>(t) = "three";
    }
