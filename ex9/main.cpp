#include <iostream>

using namespace std;

const int DEFAULT_VECTOR_SIZE = 16;



// Simple STL Vector implementation
template <typename T>
class Vector
{
public:
    Vector (int capacity=DEFAULT_VECTOR_SIZE);
    Vector (const Vector&);
    ~Vector () {
        delete [] m_container;
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            /// TODO
        }
        return *this;
    }


    Vector operator+(const Vector& other);
    T& operator[](const int& index) {
        return m_container[index];
    };

    void push(T& item);
    T pop();

    void insertAt(); // TODO
    void removeAt(); // TODO




    friend std::ostream& operator<<(std::ostream& stream /*cout*/, const Vector& vector) {
        stream << "[ ";
        for (int i = 0; i < vector.m_size; ++i) {
            stream << vector.m_container[i] << ", ";
            /// cout << vector.m_container[i]
        }
        stream << " ]";
            /* stream << vector[i]; */
        return stream;
    };


private:
    /* func */

private:
   /* data */ 
   T* m_container;

   int m_size, // current number of items
       m_capacity;  // max number of elements
};

template <typename T>
Vector<T>::Vector(int capacity)
    : m_capacity(capacity), m_size(0) {

    m_container = new T[m_capacity];
}

template <typename T>
void Vector<T>::push(T& item) {
    if (m_size >= m_capacity) {
        // TODO resize
        return;
    }

    m_container[m_size++] = item;
}

template <typename T>
T Vector<T>::pop() {
    return m_container[--m_size];
}



int main()
{
    Vector<int> arr1(10); // int[10] arr;
    Vector<int> arr2; // int[10] arr;
    int x = 2;
    // size == 0; capacity == 10
    arr1.push(x); // [1]
    x = 5;
    arr1.push(x); // [1, 2]

    // Vector<int> arr3 = arr1 + arr2;


    // size == 2
    // size1 + size2
    
    cout << arr1 << " this is the End..." << arr1[1] << endl; // ( cout << arr1 ) << "this is the End..." << 1 << endl;

    // cout << "this is the End" << 1 << endl
    // cout << 1 << endl
    // cout << endl

    /// writing to file for example
    // arr << filename;

    arr1.pop();

    // cout << arr << endl;

    return 0;
}
