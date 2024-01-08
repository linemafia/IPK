# include <array>
# include <iostream>

template <typename Number, unsigned int N, unsigned int M>
class Matrix {
    private:
        std::array<std::array<Number, M>, N> valArr;
    public:
        // e)

        // constructor for std::vector<std::vector>, std::array<std::array> 
        template<typename Container>
        Matrix(const Container& valCont) : valArr() {
            unsigned int i = 0;
            for (const auto & line : valCont) {
                unsigned int j = 0;
                for (const Number& val : line) {
                    valArr[i][j] = val;
                    j ++;
                }
                i ++;
            }
        }


        // a)

        // Default-Konstruktor : erzeugt eine 0-Matrix
        Matrix() : valArr() {}

        // die Matrix auf der Konsole ausgibt
        void print() const {
            for (const std::array<Number, M>& line : valArr) {
                for (const Number& val : line)
                    std::cout << val << " ";
                std::cout << std::endl;
            }
        }

        // die Lese- und Schreibzugriff auf die Elemente erlaubt 
        //!! Das heißt mat.get(0,3) = 7; soll möglich sein.
        Number& get(const unsigned int &i, const unsigned int &j) {
            return valArr[i][j];
        }

        // b)

        // die Matrix in transponiert2 zurückgibt.
        Matrix<Number, M, N> transpose() const {
            Matrix<Number, M, N> result;
            for (unsigned int i = 0; i < N; i ++)
                for (unsigned int j = 0; j < M; j ++)
                    result.get(j, i) = valArr[i][j];
            return result;
        }

        // c)

        // eine Matrix gleicher Größe bekommt und eine Matrix zurück gibt, 
        // deren Elemente jeweils die Summe der Elemente an der gleichen Stelle sind.
        Matrix<Number, N, M> add(Matrix<Number, N, M>& other) const {
            Matrix<Number, N, M> result;
            for (unsigned int i = 0; i < N; i ++) 
                for (unsigned int j = 0; j < M; j ++)
                    result.get(i, j) = valArr[i][j] + other.get(i, j);
            return result;
        }

        // eine Matrix gleicher Größe bekommt und eine Matrix zurück gibt, 
        // deren Elemente jeweils die Differenz der Elemente an der gleichen Stelle sind.
        Matrix<Number, N, M> subtract(Matrix<Number, N, M>& other) const {
            Matrix<Number, N, M> result;
            for (unsigned int i = 0; i < N; i ++) 
                for (unsigned int j = 0; j < M; j ++)
                    result.get(i, j) = valArr[i][j] - other.get(i, j);
            return result;
        }

        // d)

        // die Matrix-Multiplikation4 durchführt
        template<unsigned int K>
        Matrix<Number, N, K> multiply(Matrix<Number, M, K>& other) const {
            Matrix<Number, N, K> result;
            for (unsigned int i = 0; i < N; i ++)
                for (unsigned int t = 0; t < K; t ++)
                    for (unsigned int j = 0; j < M; j ++)
                        result.get(i, t) += valArr[i][j] * other.get(j, t);
            return result;
        }
};