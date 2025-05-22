#ifndef V1_5VECT_H
#define V1_5VECT_H

#include "lib.h"

extern std::chrono::duration<double> pushlaikas; // generavimo laikas
extern std::chrono::duration<double> generationTime; // generavimo laikas
extern std::chrono::duration<double> readTime; // skaitymo laikas
extern std::chrono::duration<double> sortTime; // skirstymo laikas
extern std::chrono::duration<double> writeTime; // rasymo laikas
extern std::chrono::duration<double> rusiavimoLaikas; // rusiavimo laikas

// V1.5vect.h
#pragma once
#include <initializer_list>
#include <stdexcept> // for std::out_of_range

template <typename T>
class Vector {
private:
    T* data; // duomenu masyvas
    size_t size; // masyvo dydis
    size_t capacity; // talpa

public:
    Vector() : data(nullptr), size(0), capacity(0) {} // konstruktorius;

    ~Vector() {};

    //index operator
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    //back function
    T& back() {
        return data[size - 1];
    }

    const T& back() const {
        return data[size - 1];
    }

    //empty function
    bool empty() const {
        return size == 0;
    }

    //clear function
    void clear() {
        size = 0;
    }

    // begin, end function
    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* end() const {
        return data + size;
    }

    static size_t count;

    // push_back funkcija
    void push_back(const T& value) {
        if (size == capacity) {
            count++;
            size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }

        data[size++] = value;
    }

    //pop_back
    void pop_back() {
        if (size == 0) return;
        --size;
    }

    void resize(size_t newSize) {
        if (newSize < size) {
            size = newSize;
        } else if (newSize > size) {
            if (newSize > capacity) {
                size_t new_capacity = newSize;
                T* new_data = new T[new_capacity];

                for (size_t i = 0; i < size; ++i) {
                    new_data[i] = data[i];
                }

                delete[] data;
                data = new_data;
                capacity = new_capacity;
            }

            for (size_t i = size; i < newSize; ++i) {
                data[i] = T();
            }

            size = newSize;
        }
    }

    // getteriai
    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }

    static size_t getCount() {
        return count;
    }

    Vector(std::initializer_list<T> init) : data(nullptr), size(0), capacity(0) {
        size = init.size();
        capacity = size;
        data = new T[capacity];
        size_t i = 0;
        for (const auto& elem : init) {
            data[i++] = elem;
        }
    }
};

// Static count variable definition
template<typename T>
size_t Vector<T>::count = 0;

// operator==
template <typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.getSize() != rhs.getSize()) return false;
    for (size_t i = 0; i < lhs.getSize(); ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

// Additional functions (correctly added outside the class)

// at()
template <typename T>
T& at(Vector<T>& vec, size_t index) {
    if (index >= vec.getSize()) throw std::out_of_range("Index out of range");
    return vec[index];
}

template <typename T>
const T& at(const Vector<T>& vec, size_t index) {
    if (index >= vec.getSize()) throw std::out_of_range("Index out of range");
    return vec[index];
}

// front()
template <typename T>
T& front(Vector<T>& vec) {
    return vec[0];
}

template <typename T>
const T& front(const Vector<T>& vec) {
    return vec[0];
}

// data pointer accessors
template <typename T>
T* get_data(Vector<T>& vec) {
    return vec.begin();
}

template <typename T>
const T* get_data(const Vector<T>& vec) {
    return vec.begin();
}

// operator!=
template <typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

// operator<
template <typename T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    size_t minSize = lhs.getSize() < rhs.getSize() ? lhs.getSize() : rhs.getSize();
    for (size_t i = 0; i < minSize; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (lhs[i] > rhs[i]) return false;
    }
    return lhs.getSize() < rhs.getSize();
}

// operator<=
template <typename T>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}

// operator>
template <typename T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

// operator>=
template <typename T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}

// swap
template <typename T>
void swap(Vector<T>& a, Vector<T>& b) {
    using std::swap;
    swap(a, b);
}

// assign
template <typename T>
void assign(Vector<T>& vec, std::initializer_list<T> list) {
    vec.clear();
    for (const auto& item : list) {
        vec.push_back(item);
    }
}

// find
template <typename T>
T* find(Vector<T>& vec, const T& value) {
    for (T* it = vec.begin(); it != vec.end(); ++it) {
        if (*it == value) return it;
    }
    return vec.end();
}



class Zmogus{
    protected:
        string name; // vardas
        string surn; // pavarde
    public:
        Zmogus() : name(""), surn("") {} // konstruktorius
        virtual ~Zmogus(){}

        void setName(const string& Name) {
            name = Name;
        }

        void setSurn(const string& Surn) {
            surn = Surn;
        }

        string getName() const {
            return name;
        }

        string getSurn() const {
            return surn;
        }
        virtual void test() = 0;
};




class Student : public Zmogus {
    private:
        Vector<int> nd; // nd rezultatai 
        int egz; // egzaminu rez
        double vid; // galutinis vidurkis

    public:

        void test(){}

        Student() : egz(0), vid(0) {} // konstruktorius

        ~Student(){} // destruktorius

        // copy constructor dada
        Student(const Student& other)
        : Zmogus(other), nd(other.nd), egz(other.egz), vid(other.vid){}

        // copy assignment operator
        Student& operator=(const Student& other){
            if(this != &other) {
                name = other.name;
                surn = other.surn;
                nd = other.nd;
                egz = other.egz;
                vid = other.vid;
            }
            return *this;
        }

       // move constructor
        Student(Student&& other)
            : Zmogus(std::move(other)),
            nd(std::move(other.nd)),
            egz(std::move(other.egz)),
            vid(std::move(other.vid))
        {
            other.egz = 0;
            other.vid = 0.0;
            other.name = ""; 
            other.surn = ""; 
            other.nd.clear();
        }

        // move assignment operator
        Student& operator=(Student&& other) {
            if (this != &other) {
                name = std::move(other.name);
                surn = std::move(other.surn);
                nd = std::move(other.nd);
                egz = std::move(other.egz);
                vid = std::move(other.vid);

                other.egz = 0;
                other.vid = 0.0;
                other.name = ""; 
                other.surn = ""; 
                other.nd.clear();
            }
            return *this;
        }

        //seteriai
        void setVid(double Vid) {
            vid = Vid;
        }

        void setEgz(int Egz) {
            egz = Egz;
        }

        void setNd(const Vector<int>& Nd) {
            nd = Nd;
        }


        //geteriai
        double getVid() const {
            return vid;
        }

        int getEgz() const {
            return egz;
        }

        Vector<int>& getNd(){
            return nd;
        }

        friend istream& operator>>(std::istream& in, Student& s) {
            string name, surname;
            Vector<int> nd;
            int temp, egz;

            in >> name >> surname;
            s.setName(name);
            s.setSurn(surname);

            while (in >> temp) {
                nd.push_back(temp);
            }

            if (!nd.empty()) {
                egz = nd.back();
                nd.pop_back();  // Remove last element, which is egz
                s.setEgz(egz);
                s.setNd(nd);
            }

            in.clear();  // Clear stream state if end of line or error
            return in;
        }

        // isvesties operatorius 
        friend ostream& operator<<(ostream& os, const Student& s){
            os << left << setw(20) << s.name << setw(16) << s.surn << s.vid << endl;
            return os;
        }

};

extern Vector<Student> BadStudents;
extern Vector<Student> GoodStudents;

void skaitom(int pasirinkimas, string A[], string B[]);
void vidurkis();
void mediana();
void spausdinam(char a);
void generuojam(string b, int n);
void pushTestas(int n);
void rusiuojam2(); // skaidymas per puse
void rusiuojam1(); // skaidymas is vieno konteinerio i du
bool compareByName(const Student& a, const Student& b);
bool compareBySurname(const Student& a, const Student& b);
bool compareByVid(const Student& a, const Student& b);
void testas();

#endif