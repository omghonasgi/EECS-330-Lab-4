#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>
#include "MyVector_o797g056.h"

template <typename DataType>
class MyQueue : private MyVector<DataType>
{  
  private:
    size_t dataStart, dataEnd;

    // changes the size of the array to newSize
    void resize(size_t newSize)
    {
        if (newSize > this->theCapacity) {
            this->reserve(newSize * 2); 
        }
        this->theSize = newSize;
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity)
    {
        if(newCapacity < this->theCapacity){
            return;
        }
        
        DataType *tmp = new DataType[newCapacity];
        
        for (size_t i = 0; i < this->theSize; ++i) {
            tmp[i] = std::move(this->data[(dataStart + i) % this->theCapacity]);
        }
        
        delete[] this->data;  // Delete old array
        this->data = tmp;
        this->theCapacity = newCapacity;
        dataStart = 0;
        dataEnd = this->theSize > 0 ? this->theSize - 1 : 0;
    }

  public:
    // default constructor
    explicit MyQueue(size_t initSize = 0)
        : MyVector<DataType>(initSize) {
        dataStart = 0;
        dataEnd = this->theSize > 0 ? this->theSize - 1 : 0;
    }

    // copy constructor
    MyQueue(const MyQueue & rhs)
        : MyVector<DataType>(rhs) {
        dataStart = rhs.dataStart;
        dataEnd = rhs.dataEnd;
    }

    // move constructor
    MyQueue(MyQueue && rhs)
        : MyVector<DataType>(std::move(rhs)) {
        dataStart = rhs.dataStart;
        dataEnd = rhs.dataEnd;
        
        // Reset rhs state after move
        rhs.dataStart = 0;
        rhs.dataEnd = 0;
    }

    // destructor
    ~MyQueue() {
        // Base class destructor will be called automatically
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs) 
    {
        if (this != &rhs) {
            MyVector<DataType>::operator=(rhs);
            dataStart = rhs.dataStart;
            dataEnd = rhs.dataEnd;
        }
        return *this;
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs) 
    {
        if (this != &rhs) {
            MyVector<DataType>::operator=(std::move(rhs));
            dataStart = rhs.dataStart;
            dataEnd = rhs.dataEnd;
            
            // Reset rhs state after move
            rhs.dataStart = 0;
            rhs.dataEnd = 0;
        }
        return *this;
    }

    // insert x into the queue
    void enqueue(const DataType & x) 
    {
        if (this->empty()) {
            this->resize(1);
            dataStart = 0;
            dataEnd = 0;
            this->data[0] = x;
        } else {
            this->resize(this->theSize + 1);
            dataEnd = (dataEnd + 1) % this->theCapacity;
            this->data[dataEnd] = x;
        }
    }

    // insert x into the queue
    void enqueue(DataType && x) 
    {
        if (this->empty()) {
            this->resize(1);
            dataStart = 0;
            dataEnd = 0;
            this->data[0] = std::move(x);
        } else {
            this->resize(this->theSize + 1);
            dataEnd = (dataEnd + 1) % this->theCapacity;
            this->data[dataEnd] = std::move(x);
        }
    }

    // remove the first element from the queue
    void dequeue(void) 
    {
        if (!this->empty()) {
            dataStart = (dataStart + 1) % this->theCapacity;
            --this->theSize;
            
            if (this->empty()) {
                dataStart = 0;
                dataEnd = 0;
            }
        }
    }

    // access the first element of the queue
    const DataType & front(void) const
    {
        return this->data[dataStart];
    }

    // check if the queue is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const 
    {
        return this->theSize == 0;
    }

    // access the size of the queue
    size_t size() const 
    {
        return this->theSize;
    }

    // access the capacity of the queue
    size_t capacity(void) const 
    {
        return this->theCapacity;
    }
};

#endif // __MYQUEUE_H__