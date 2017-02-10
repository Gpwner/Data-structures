#ifndef PQUEUE_H
#define PQUEUE_H

#include<assert.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

const int DefaultSize=50;
template <class T>
class PQueue
{
public:
    /** Default constructor */
    PQueue(int sz=DefaultSize):maxSize(sz),num(0)
    {
        //创建队列空间
        pqelements=new T[maxSize];
        //断言，动态存储分配是否成功
        assert(NULL!=pqelements);
    }
    /** Default destructor */
    ~PQueue()
    {
        delete [] pqelements;
    }

    bool Insert(const T & x)
    {
        if(num==maxSize)
            return false;
        pqelements[num++]=x;
        Adjust();
    }
    bool RemoveMin(T & x)
    {
        if(0==num)
        {
            return false;
        }
        x=pqelements[0];
        for(int i=1; i<num; i++)
        {
            pqelements[i-1]=pqelements[i];
        }
        num--;
        return true;
    }
    bool GetFront(T &x) const
    {
        if(0==num)
        {
            return false;
        }
        else
        {
            x=pqelements[0];
            return true;
        }
    }
    void MakeEmpty()
    {
        num=0;
    }
    bool IsEmpty()const
    {
        return num==0?true:false;
    }
    bool IsFull() const
    {
        return num==maxSize?true:false;
    }
    int getSize() const
    {
        return num;
    }
protected:
    T * pqelements;
    int num;
    int maxSize;
    void Adjust()
    {
        //将队尾元素按其优先权调整到适当的位置，保持所有元素优先权从小到大有序
        T temp=pqelements[num-1];
        for(int j=num-2; j>0; j--)
        {
            if(pqelements[j]<=temp)
                break;
            else
                pqelements[j+1]=pqelements[j];
            pqelements[j]=temp;
        }
    }
};

#endif // PQUEUE_H
