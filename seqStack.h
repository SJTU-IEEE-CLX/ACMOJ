#ifndef SEQSTACK_H
#define SEQSTACK_H
#include <iostream>
using namespace std;

#ifndef ERROR_HANDLING
#define ERROR_HANDLING
class outOfBound{};

#endif

template <class T>
class seqStack
{
    private:
        T *array;
        int m_top;
        int max_size;
        void double_space();
    public:
        seqStack(int init_size = 100);
        int isEmpty() { return (m_top == -1); };
        int isFull() { return (m_top == max_size - 1); };
        T top();
        void push(const T& e);
        void pop();
        ~seqStack() { delete[] array; };
};

template <class T>
void seqStack<T>::double_space() {
    int new_max_size = 2 * max_size;
    T *new_array = new T[new_max_size];
    for (int i = 0; i < m_top + 1; ++i) {
        new_array[i] = array[i];
    }
    delete[] array;
    array = new_array;
    max_size = new_max_size;
}

template <class T>
seqStack<T>::seqStack(int init_size) {
    array = new T[init_size];
    max_size = init_size;
    m_top = -1;
}

template <class T>
T seqStack<T>::top() {
    if (isEmpty()) {
        throw outOfBound();        
    }
    return array[m_top];
}

template <class T>
void seqStack<T>::push(const T& e) {
    if (isFull()) {
        double_space();
    }
    m_top++;
    array[m_top] = e;
}

template <class T>
void seqStack<T>::pop() {
    if (isEmpty()) {
        throw outOfBound();
    }
    m_top--;
}

#endif //SEQSTACK_H
