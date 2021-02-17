// g++ vector_array_impl.cpp -o vector_array_impl.out -std=c++11

// ./vector_array_impl.out
// capacity: 2 size: 1
// capacity: 2 size: 2
// capacity: 4 size: 3
// expected front 100, front 100
// capacity: 4 size: 2
// expect [0] 100, [0] 100
// expect [1] 200, [1] 200
// capacity: 4 size: 1
// capacity: 2 size: 0
// capacity: 2 size: 1

#include <iostream>

using namespace std;

class Vector
{
 public:
    Vector();
    virtual ~Vector();

    void    push_back(int val);
    void    pop_back();
    int     front();
    int     at(int idx);
    int     size();
    int     capacity();

 private:
    void    resize();
    int*    m_array;
    int     m_index;
    int     m_capacity;
};

Vector::Vector()
{
    // initialize array as 4 elements at the initial state
    // then exponentially increase if needed
    m_array = new int[2];
    m_index = -1;
    m_capacity = 2;
}

Vector::~Vector()
{
    delete [] m_array;
    m_index = -1;
    m_capacity = 0;
}

void Vector::resize()
{
    int size = m_index + 1;
    if (size * 2 == m_capacity)
    {
        return;
    }

    int* tmp = new int[size * 2];
    m_capacity = size * 2;
    for (int i = 0; i <= m_index; i++)
    {
        tmp[i] = m_array[i];
    }

    delete [] m_array;
    m_array = tmp;

    return;
}

void Vector::push_back(int val)
{
    int size = m_index + 1;
    if (size * 2 > m_capacity)
    {
        resize();
    }

    m_index ++;
    m_array[m_index] = val;

    return;
}

void Vector::pop_back()
{
    int size = m_index + 1;
    if (size * 2 < m_capacity)
    {
        resize();
    }

    m_index --;
}

int Vector::front()
{
    return m_array[0];
}

int Vector::at(int idx)
{
    return m_array[idx];
}

int Vector::size()
{
    return m_index + 1;
}

int Vector::capacity()
{
    return m_capacity;
}

int main()
{
    Vector my_vector;

    my_vector.push_back(100);
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
    my_vector.push_back(200);
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
    my_vector.push_back(300);
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;

    cout << "expected front 100, front " << my_vector.front() << endl;

    my_vector.pop_back(); // pop the last element
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
    cout << "expect [0] 100, [0] " << my_vector.at(0) << endl;
    cout << "expect [1] 200, [1] " << my_vector.at(1) << endl;
    my_vector.pop_back();
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
    my_vector.pop_back();
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
    my_vector.push_back(400);
    cout << "capacity: " << my_vector.capacity() << " size: " << my_vector.size() << endl;
}
