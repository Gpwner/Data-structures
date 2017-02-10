#ifndef MINHEAP_H
#define MINHEAP_H
#include<PQueue.h>

//��С�� �̳�����С����Ȩ����
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
            cerr<<"�Ѵ洢�ռ����ʧ�ܣ�"<<endl;
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
            cerr<<"�Ѵ洢�ռ����ʧ�ܣ�"<<endl;
            exit(1);
        }
        //���ƶ����飬������ǰ��С
        for(int i=0; i<n; i++)
            heap[i]=arra[i];
        currentSize=n;
        //���������λ��
        int currentPosition=(currentSize-2)/2;
        while(currentPosition>=0)
        {
            //�ֲ��������µ���
            shiftDown(currentPosition,currentSize-1);
            //����һ����֧�ڵ���
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
//�ж��Ƿ�Ϊ��
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
    //�����С����Ԫ�ص����飻
    T *heap;
    int currentSize;
    int maxHeapsize;
    void shiftDown(int start,int m)
    {
        //�ӽڵ�start��ʼmΪֹ���������£������Ů��ֵС�ڸ��ڵ��ֵ
        //��ؼ���С���ϸ����������±Ƚϣ��Ϳ��Խ�һ���ֲ�����Ϊ��С��
        int i=start;
        int j=2*i+1;//j��i������Ů��λ��
        T temp=heap[i];
        while(j<m)
        {
            if(j<m&&heap[j]>heap[j+1])
                //��jָ������Ů�н�С��
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
        //�ӽڵ�start��ʼ���ڵ�0Ϊֹ���������ϱȽϣ������Ů��ֵС�ڸ��ڵ��ֵ��
        //���ཻ���������ϴ��µ���Ϊ��С��
        int j=start;
        int i=(j-1)/2;
        T temp=heap[j];
        while(j>0)
        {
            //���ڵ��ֵС���򲻵���
            if(heap[i]<=temp)
                break;
            //���ڵ��ֵ�������
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
