#include <iostream>

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

int calcPost(char* str){
    int op,op1,op2;
    int tmp,i;
    seqStack<int> s;
    i = 0;

    while (str[i]!='@'){
        if (str[i] == '.'){
            i++;
            continue;
        }
        if(str[i] >= '0' && str[i] <= '9'){
            {
                tmp = str[i] - '0';
                while (str[i+1] != '.'){
                    tmp = tmp * 10 + str[i+1] - '0';
                    i++;
                }
                s.push(tmp);
            }
        }
        else{
            op2 = s.top();
            s.pop();
            op1 = s.top();
            s.pop();
            switch(str[i]){
                case '+': s.push(op1 + op2); break;
                case '-': s.push(op1 - op2); break;
                case '*': s.push(op1 * op2); break;
                case '/': s.push(op1 / op2); break;
            }
        }i++;
    }
        op = s.top();
        s.pop();
        return op;
}

int main() {
    char str[10000];
    cin.getline(str,10000);
    cout << calcPost(str) << endl;
    return 0;
}
