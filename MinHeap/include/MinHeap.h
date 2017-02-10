#ifndef MINHEAP_H
#define MINHEAP_H
#include<PQueue.h>

//最小堆 继承了最小优先权队列
template<class T>
class MinHeap:public PQueue<T>
{
public:
    /** Default constructor */
    MinHeap(int sz=DefaultSize)
    {
        maxHeapsize=DefaultSize<sz?sz:DefaultSize;
        heap=new T[maxHeapsize];
        if(NULL==heap)
        {
            cerr<<"堆存储空间分配失败！"<<endl;
            exit(1);
        }
        currentSize=0;
    }
    MinHeap(T arra[],int n)
    {
        maxHeapsize=DefaultSize<n?n:DefaultSize;
        heap=new T[maxHeapsize];
        if(NULL=heap)
        {
            cerr<<"堆存储空间分配失败！"<<endl;
            exit(1);
        }
        //复制堆数组，建立当前大小
        for(int i=0; i<n; i++)
            heap[i]=arra[i];
        currentSize=n;
        //找最初调整位置
        int currentPosition=(currentSize-2)/2;
        while(currentPosition>=0)
        {
            //局部自上向下调整
            shiftDown(currentPosition,currentSize-1);
            //换下一个分支节调整
            currentPosition--;
        }
    }
    /** Default destructor */
    ~MinHeap()
    {
        delete []heap;
    }

    bool Insert(const T &x)
    {
        if(currentSize==maxHeapsize)
        {
            cerr<<"Heap Full"<<endl;
            return false;
        }
        heap[currentSize]=x;
        shiftUp(currentSize);
        currentSize++;
        return true;
    }
    bool RemoveMin(T &x)
    {
        if(!currentSize)
        {

            cerr<<"Heap empty!"<<endl;
            return false;
        }
        x=heap[0];
        heap[0]=heap[currentSize-1];
        currentSize--;
        shiftDown(0,currentSize-1);
        return true;
    }
//判断是否为空
    bool IsEmpty()const
    {
        return currentSize==0?true:false;
    }
    bool IsFull()const
    {
        return currentSize==0?true:false;
    }
    void MakeEmpty()
    {
        currentSize=0;
    }
    int GetSize()
    {
        return currentSize;
    }
private:
    //存放最小堆中元素的数组；
    T *heap;
    int currentSize;
    int maxHeapsize;
    void shiftDown(int start,int m)
    {
        //从节点start开始m为止，自上向下，如果子女的值小于父节点的值
        //则关键码小的上浮，继续向下比较，就可以将一个局部调整为最小堆
        int i=start;
        int j=2*i+1;//j是i的做子女的位置
        T temp=heap[i];
        while(j<m)
        {
            if(j<m&&heap[j]>heap[j+1])
                //让j指向两子女中较小者
                j++;
            if(temp<=heap[j])
                break;
            else
            {
                heap[i]=heap[j];
                i=j;
                j=2*j+1;
            }
        }
        heap[i]=temp;
    }
    void shiftUp(int start)
    {
        //从节点start开始到节点0为止，自下向上比较，如果子女的值小于父节点的值】
        //则互相交换，将集合从新调整为最小堆
        int j=start;
        int i=(j-1)/2;
        T temp=heap[j];
        while(j>0)
        {
            //父节点的值小，则不调整
            if(heap[i]<=temp)
                break;
            //父节点的值大，则调整
            else
            {
                heap[j]=heap[i];
                j=i;
                i=(i-1)/2;
            }
        }
        heap[j]=temp;
    }
};

#endif // MINHEAP_H
