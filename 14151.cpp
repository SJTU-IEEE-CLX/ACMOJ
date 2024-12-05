#include <iostream>
#include <vector>
using namespace std;
class outOfBound{};


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

bool is_valid_sequence(int n, const vector<int>& sequence) {
    seqStack<int> stack;
    int current = 1;
    for (int num : sequence) {
        while (current <= num) {
            stack.push(current++);
        }
        if (stack.top() == num) {
            stack.pop();
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> sequence(n);
        for (int i = 0; i < n; ++i) {
            cin >> sequence[i];
        }
        if (is_valid_sequence(n, sequence)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}