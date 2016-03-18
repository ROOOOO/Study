#ifndef yaimp_cpp_3_super_calc_h
#define yaimp_cpp_3_super_calc_h
#include <vector>
using namespace std;
enum Operations {
    VAL, PLS, SUB, USUB, MUL, DIV, PTR
};
template <typename T>
class Cell {
    Operations op;
    T val;
    const Cell<T> *l;
    const Cell<T> *r;
    public:
    static vector<Cell<T>* > to_remove;
    Cell():op(), l(), r() {};
    Cell(Cell<T> &obj):op(obj.op), val(obj.val), l(obj.l), r(obj.r) {};
    Cell(const T& value): op(VAL), val(value), l(), r() {};
    Cell(const Cell<T>& obj, Operations unary) : op(unary), l(&obj), r() {};
    Cell(const Cell<T>& obj1, const Cell<T>& obj2, Operations op) : op(op), l(&obj1), r(&obj2) {};
    Cell& operator=(const T& value){
        val = value;
        op = VAL;
        return *this;
    };
    Cell& operator=(const Cell<T>& obj){
        op = PTR;
        l = &obj;
#ifndef yaimp_cpp_3_super_calc_h
#define yaimp_cpp_3_super_calc_h
#include <vector>
        using namespace std;
        enum Operations {
            VAL, PLS, SUB, USUB, MUL, DIV, PTR
        };
        template <typename T>
        class Cell {
            Operations op;
            T val;
            const Cell<T> *l;
            const Cell<T> *r;
            public:
            static vector<Cell<T>* > to_remove;
            Cell():op(), l(), r() {};
            Cell(Cell<T> &obj):op(obj.op), val(obj.val), l(obj.l), r(obj.r) {};
            Cell(const T& value): op(VAL), val(value), l(), r() {};
            Cell(const Cell<T>& obj, Operations unary) : op(unary), l(&obj), r() {};
            Cell(const Cell<T>& obj1, const Cell<T>& obj2, Operations op) : op(op), l(&obj1), r(&obj2) {};
            Cell& operator=(const T& value){
                val = value;
                op = VAL;
                return *this;
            };
            Cell& operator=(const Cell<T>& obj){
                op = PTR;
                l = &obj;
                return *this;
            };
            operator T() const{
                if(op==VAL) return val;
                else if(op==PLS) return (T)*l + (T)*r;
                else if(op==SUB) return (T)*l - (T)*r;
                else if(op==MUL) return (T)*l * (T)*r;
                else if(op==DIV) return (T)*l / (T)*r;
                else if(op==USUB) return -(T)*l;
                else return (T)*l;
            };
            Cell<T>& operator*=(Cell<T> &obj){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                r = &obj;
                op = MUL;
                return *this;
            };
            Cell<T>& operator*=(const T& value){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                to_remove.push_back(new Cell<T>(value));
                r = to_remove.back();
                op = MUL;
                return *this;
            };
            Cell<T>& operator/=(Cell<T> &obj){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                r = &obj;
                op = DIV;
                return *this;
            };
            Cell<T>& operator/=(const T& value){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                to_remove.push_back(new Cell<T>(value));
                r = to_remove.back();
                op = DIV;
                return *this;
            };
            Cell<T>& operator+=(Cell<T> &obj){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                r = &obj;
                op = PLS;
                return *this;
            };
            Cell<T>& operator+=(const T& value){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                to_remove.push_back(new Cell<T>(value));
                r = to_remove.back();
                op = PLS;
                return *this;
            };
            Cell<T>& operator-=(Cell<T> &obj){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                r = &obj;
                op = SUB;
                return *this;
            };
            Cell<T>& operator-=(const T& value){
                to_remove.push_back(new Cell<T>(*this));
                l = to_remove.back();
                to_remove.push_back(new Cell<T>(value));
                r = to_remove.back();
                op = SUB;
                return *this;
            };
            const Cell<T>& operator-() const{
                to_remove.push_back(new Cell<T>(*this, USUB));
                return *to_remove.back();
            };
            friend const Cell<T>& operator+(const Cell<T>& obj1, const Cell<T> &obj2){
                Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, PLS));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator+(const Cell<T> &obj, const T &val){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                return obj + *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator*(const Cell<T> &obj1, const Cell<T> &obj2){
                Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, MUL));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator*(const Cell<T> &obj, const T &val){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(obj, *v, MUL));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator*(const T &val, const Cell<T> &obj){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, MUL));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator/(const Cell<T> &obj1, const Cell<T> &obj2){
                Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, DIV));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator/(const Cell<T> &obj, const T &val){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(obj, *v, DIV));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator/(const T &val, const Cell<T> &obj){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, DIV));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator+(const T &val, const Cell<T> &obj){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, PLS));
                return *Cell<T>::to_remove.back();
            };
            friend const Cell<T>& operator-(const Cell<T> &obj1, const Cell<T> &obj2){
                Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, SUB));
                return *Cell<T>::to_remove.back();
            }
            friend const Cell<T>& operator-(const Cell<T> &obj1, const T &obj2){
                Cell<T>::to_remove.push_back(new Cell<T>(obj2));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(obj1, *v, SUB));
                return *Cell<T>::to_remove.back();
            }
            friend const Cell<T>& operator-(const T &val, const Cell<T> &obj){
                Cell<T>::to_remove.push_back(new Cell<T>(val));
                Cell<T> *v = Cell<T>::to_remove.back();
                Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, SUB));
                return *Cell<T>::to_remove.back();
            }
        };
        template <typename T>
        vector<Cell<T> *> Cell<T>::to_remove;
        template <class T>
        class SuperCalc {
            Cell<T> **table;
            int m, n;
            public:
            SuperCalc(int m, int n){
                this->m = m;
                this->n = n;
                table = new Cell<T>*[m];
                for (int i = 0; i<m; i++) table[i] = new Cell<T>[n];
            };
            ~SuperCalc(){
                for (Cell<T>*x: Cell<T>::to_remove) delete x;
                for (int i = 0; i<m; i++) delete[] table[i] ;
                delete [] table;
            };
            Cell<T>& operator() (int i, int j){return table[i][j];};
        };
#endif
        return *this;
    };
    operator T() const{
        if(op==VAL) return val;
        else if(op==PLS) return (T)*l + (T)*r;
        else if(op==SUB) return (T)*l - (T)*r;
        else if(op==MUL) return (T)*l * (T)*r;
        else if(op==DIV) return (T)*l / (T)*r;
        else if(op==USUB) return -(T)*l;
        else return (T)*l;
    };
    Cell<T>& operator*=(Cell<T> &obj){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        r = &obj;
        op = MUL;
        return *this;
    };
    Cell<T>& operator*=(const T& value){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        to_remove.push_back(new Cell<T>(value));
        r = to_remove.back();
        op = MUL;
        return *this;
    };
    Cell<T>& operator/=(Cell<T> &obj){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        r = &obj;
        op = DIV;
        return *this;
    };
    Cell<T>& operator/=(const T& value){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        to_remove.push_back(new Cell<T>(value));
        r = to_remove.back();
        op = DIV;
        return *this;
    };
    Cell<T>& operator+=(Cell<T> &obj){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        r = &obj;
        op = PLS;
        return *this;
    };
    Cell<T>& operator+=(const T& value){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        to_remove.push_back(new Cell<T>(value));
        r = to_remove.back();
        op = PLS;
        return *this;
    };
    Cell<T>& operator-=(Cell<T> &obj){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        r = &obj;
        op = SUB;
        return *this;
    };
    Cell<T>& operator-=(const T& value){
        to_remove.push_back(new Cell<T>(*this));
        l = to_remove.back();
        to_remove.push_back(new Cell<T>(value));
        r = to_remove.back();
        op = SUB;
        return *this;
    };
    const Cell<T>& operator-() const{
        to_remove.push_back(new Cell<T>(*this, USUB));
        return *to_remove.back();
    };
    friend const Cell<T>& operator+(const Cell<T>& obj1, const Cell<T> &obj2){
        Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, PLS));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator+(const Cell<T> &obj, const T &val){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        return obj + *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator*(const Cell<T> &obj1, const Cell<T> &obj2){
        Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, MUL));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator*(const Cell<T> &obj, const T &val){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(obj, *v, MUL));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator*(const T &val, const Cell<T> &obj){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, MUL));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator/(const Cell<T> &obj1, const Cell<T> &obj2){
        Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, DIV));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator/(const Cell<T> &obj, const T &val){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(obj, *v, DIV));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator/(const T &val, const Cell<T> &obj){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, DIV));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator+(const T &val, const Cell<T> &obj){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, PLS));
        return *Cell<T>::to_remove.back();
    };
    friend const Cell<T>& operator-(const Cell<T> &obj1, const Cell<T> &obj2){
        Cell<T>::to_remove.push_back(new Cell<T>(obj1, obj2, SUB));
        return *Cell<T>::to_remove.back();
    }
    friend const Cell<T>& operator-(const Cell<T> &obj1, const T &obj2){
        Cell<T>::to_remove.push_back(new Cell<T>(obj2));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(obj1, *v, SUB));
        return *Cell<T>::to_remove.back();
    }
    friend const Cell<T>& operator-(const T &val, const Cell<T> &obj){
        Cell<T>::to_remove.push_back(new Cell<T>(val));
        Cell<T> *v = Cell<T>::to_remove.back();
        Cell<T>::to_remove.push_back(new Cell<T>(*v, obj, SUB));
        return *Cell<T>::to_remove.back();
    }
};
template <typename T>
vector<Cell<T> *> Cell<T>::to_remove;
template <class T>
class SuperCalc {
    Cell<T> **table;
    int m, n;
    public:
    SuperCalc(int m, int n){
        this->m = m;
        this->n = n;
        table = new Cell<T>*[m];
        for (int i = 0; i<m; i++) table[i] = new Cell<T>[n];
    };
    ~SuperCalc(){
        for (Cell<T>*x: Cell<T>::to_remove) delete x;
        for (int i = 0; i<m; i++) delete[] table[i] ;
        delete [] table;
    };
    Cell<T>& operator() (int i, int j){return table[i][j];};
};
#endif