// like a pair but a triplet
template <typename T1, typename T2, typename T3>
class Triplet {
    private:
        T1 firstVal;
        T2 secondVal;
        T3 thirdVal;
    public:
        Triplet(const T1& initFirst, const T2& initSecond, const T3& initThird) 
            : firstVal(initFirst), secondVal(initSecond), thirdVal(initThird) {}
        
        T1 first() const {
            return firstVal;
        }
        T2 second() const {
            return secondVal;
        }
        T3 third() const {
            return thirdVal;
        }
        
        void setFirst(const T1& newFirst) {
            firstVal = newFirst;
        }
        void setSecond(const T2& newSecond) {
            secondVal = newSecond;
        }
        void setThird(const T3& newThird) {
            thirdVal = newThird;
        }
};