/*

2https://de.wikipedia.org/wiki/Matrix_(Mathematik)#Transponierte_Matrix
3https://de.wikipedia.org/wiki/Matrix_(Mathematik)#Matrizenaddition
4https://de.wikipedia.org/wiki/Matrix_(Mathematik)#Matrizenmultiplikation
Seite
*/
# include <array>
# include <iostream>

template <typename Number, unsigned int N, unsigned int M>
class Matrix {
    private:
        std::array<std::array<Number, M>, N> valArr;
    public:
        // e) 
        /*
        (5 Bonus- Punkte) Schreiben Sie einen weiteren Konstruktor, der (über einen Template-
        Parameter) einen verschachtelten Container annimmt, und mit dessen Inhalt die Matrix
        füllt. Vor allem soll somit die Initialisierung durch ein std::array<std::array> und einen
        std::vector<std::vector> möglich sein.
        Tipp: Durch zwei verschachtelte Range-Based-For-Loops und das Keyword auto können Sie
        problemlos über einen Container unbekannten Typs iterieren.
        1falls noch nicht bekannt: für diese Aufgabe reicht es größtenteils, sich diese als N ×M große Tabelle von Zahlen
        vorzustellen */
        template<typename Container>
        Matrix(Container valCont) : valArr(valCont) {}


        // a)

        // Default-Konstruktor : erzeugt eine 0-Matrix
        Matrix() : valArr() {}

        // die Matrix auf der Konsole ausgibt
        void print() const {
            for (std::array<Number, M>& line : valArr) {
                for (Number& val : valArr)
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
            Matrix<Number, M, N> result(M, N);
            for (unsigned int i = 0; i < N; i ++)
                for (unsigned int j = 0; j < M; j ++)
                    result.valArr[j][i] = valArr[i][j];
            return result;
        }

        // c)

        // eine Matrix gleicher Größe bekommt und eine Matrix zurück gibt, 
        // deren Elemente jeweils die Summe der Elemente an der gleichen Stelle sind.
        Matrix<Number, N, M> add(const Matrix<Number, N, M>& other) const {
            Matrix<Number, N, M> result(N, M);
            for (unsigned int i = 0; i < N; i ++) 
                for (unsigned int j = 0; j < M; j ++)
                    result.valArr[i][j] = valArr[i][j] + other.valArr[i][j];
            return result;
        }

        // eine Matrix gleicher Größe bekommt und eine Matrix zurück gibt, 
        // deren Elemente jeweils die Differenz der Elemente an der gleichen Stelle sind.
        Matrix<Number, N, M> subtract(const Matrix<Number, N, M>& other) const {
            Matrix<Number, N, M> result(N, M);
            for (unsigned int i = 0; i < N; i ++) 
                for (unsigned int j = 0; j < M; j ++)
                    result.valArr[i][j] = valArr[i][j] - other.valArr[i][j];
            return result;
        }

        // d)

        // die Matrix-Multiplikation4 durchführt
        template<unsigned int K>
        Matrix<Number, N, K> multiply(const Matrix<Number, M, K>& other) const {
            Matrix<Number, N, K> result;
            for (unsigned int i = 0; i < N; i ++)
                for (unsigned int t = 0; t < K; t ++)
                    for (unsigned int j = 0; j < M; j ++)
                        result.valArr[i][t] += valArr[i][j] * other.valArr[j][t];
            return result;
        }




};


/*
            if (N != other.N || M != other.M) {
                std::err << "Err: .add two matrices of different sizes" << std::endl;
                return Matrix<Number>();
            }
*/