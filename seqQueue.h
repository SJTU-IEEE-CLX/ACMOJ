#ifndef SEQQUEUE_H_INCLUDED
#define SEQQUEUE_H_INCLUDED
 class illegalSize
 {
 };
// class outOfBound
// {
// };
template <class elemType>
class seqQueue
{
private:
    elemType *array;
    int maxSize;
    int Front, Rear;
    void doubleSpace(); // 扩展队队列元素的存储空间为原来的2倍
public:
    seqQueue(int size = 10);         // 初始化队列元素的存储空间
    bool isEmpty();                  // 判断队空否，空返回true，否则为false
    bool isFull();                   // 判断队满否，满返回true，否则为false
    elemType front();                // 读取队首元素的值，队首不变
    void enQueue(const elemType &x); // 将x进队，成为新的队尾
    void deQueue();                  // 将队首元素出队
    ~seqQueue();                     // 释放队列元素所占据的动态数组
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) // 初始化队列元素的存储空间
{
    array = new elemType[size]; // 申请实际的队列存储空间
    if (!array)
        throw illegalSize();
    maxSize = size;
    Front = Rear = 0;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty() // 判断队空否，空返回true，否则为false
{
    return Front == Rear;
}

template <class elemType>
bool seqQueue<elemType>::isFull() // 判断队满否，满返回true，否则为false
{
    return (Rear + 1) % maxSize == Front;
}

template <class elemType>
elemType seqQueue<elemType>::front() // 读取队首元素的值，队首不变
{
    if (isEmpty())
        throw outOfBound();
    return array[Front];
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x) // 将x进队，成为新的队尾
{
    if (isFull())
        doubleSpace();
    array[Rear] = x;
    Rear = (Rear + 1) % maxSize;
}
template <class elemType>
void seqQueue<elemType>::deQueue() // 将队首元素出队
{
    if (isEmpty())
        throw outOfBound();
    Front = (Front + 1) % maxSize;
}

template <class elemType>
seqQueue<elemType>::~seqQueue() // 释放队列元素所占据的动态数组
{
    delete[] array;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace() // 扩展队队列元素的存储空间为原来的2倍
{
    elemType *tmp = array;
    array = new elemType[2 * maxSize];
    if (!array)
        throw illegalSize();
    for (int i = 1; i < maxSize; i++)
        array[i] = tmp[(Front + i) % maxSize];
    Front = 0;
    Rear = maxSize - 1;
    maxSize *= 2;
    delete[] tmp;
}

#endif