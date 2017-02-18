#ifndef GRAPHMTX_H
#define GRAPHMTX_H
#include<Graph.h>
#include<iostream>
#include<stdlib.h>
using namespace std;

template <class T,class E>
class Graphmtx
{

public:
    E maxWeight;
    /** Default constructor */
    Graphmtx(int sz=DefaultVertices)
    {
        maxVertices=sz;
        numVertices=0;
        numEdges=0;
        VerticesList =new T[maxVertices];
        Edge =(E **)new E *[maxVertices];
        //��ʼ���ڽӾ���
        for(int i=0; i<maxVertices; i++)
            Edge[i]=new E[maxVertices];
        for(int i=0; i<maxVertices; i++)
            for(int j=0; j<maxVertices; j++)
                Edge[i][j]=i==j?0:maxWeight;
    }
    /** Default destructor */
    ~Graphmtx()
    {
        delete []VerticesList;
        delete Edge;
    }
    //��ǰ������
    int NumberOfvertices()
    {
        return numVertices;
    }
    //���ص�ǰ����
    int NumberOfEdges()
    {
        return numEdges;
    }
//��ȡ�����ֵ
    T getValue(int i)
    {
        return i>=0&&i<numVertices?VerticesList[i]:NULL;
    }
    //��ȡ���ϵ�Ȩֵ
    E getWeight(int v1,int v2)
    {
        return -1!=v1&&-1!=v2?Edge[v1][v2]:0;
    }
    //��ȡ����v�ĵ�һ���ڽӶ���
    int getFirstNeighbor(int v)
    {
        if(-1!=v)
        {
            for(int col=0; col<numVertices; col++)
                if(Edge[v][col]>0&&Edge[v][col]<maxWeight)
                    return col;
        }
        return -1;
    }
    //��ȡv���ڽӶ���w����һ�ڽӶ���
    int getNextNeighbor(int v,int w)
    {
        if(-1!=v&&-1!=w)
            for(int col=w+1; col<maxVertices; col++)
                if(Edge[v][col]>0&&Edge[v][col]<maxWeight)
                    return col;
        return -1;
    }
    //���붥��
    bool insertVertex(const T &vertex)
    {
        if(numVertices==maxVertices)
            return false;
        VerticesList[numVertices++]=vertex;
        return true;
    }
    //�����
    bool insertEdge(int v1,int v2,const E cost)
    {
        if(v1>-1&&v1<numVertices&&v2>-1&&v2<numVertices&&Edge[v1][v2]==maxWeight)
        {
            Edge[v1][v2]=Edge[v2][v1]=cost;
            numEdges++;
            return true;
        }
        return false;
    }
    //ɾ������v�Լ�������֮�����ı�
    bool removeVertex(int v)
    {
        //v����ͼ�в�ɾ��
        if(v<0||v>numVertices)
            return false;
        //ֻʣ��һ�����㣬��ɾ��
        if(1==numVertices)
        {
            return false;
        }
        VerticesList[v]=VerticesList[numVertices-1];
        //��ȥ��v������ı�
        for(int i=0; i<numVertices; i++)
            if(Edge[v][i]>0&&Edge[v][i]<maxWeight)
                numEdges--;
        //�����һ�����
        for(int i=0; i<numVertices; i++)
            Edge[i][v]=Edge[i][numVertices-1];
        numVertices--;
        //�����һ�����v��
        for(int i=0; i<numVertices; i++)
            Edge[v][i]=Edge[numVertices-1][i];
        return true;
    }
    //ɾ����(v1,v2)
    bool removeEdge(int v1,int v2)
    {

        if(v1>-1&&v1<numVertices&&v2>-1&&v2<numVertices&&Edge[v1][v2]>0&&Edge[v1][v2]<maxWeight)
        {
            Edge[v1][v2]=Edge[v2][v1]=maxWeight;
            numEdges--;
            return true;
        }
        return false;

    }
    template <class V,class W>
    friend istream& operator >>(istream & in,Graphmtx<V,W> &G);
    template <class V,class W>
    friend ostream& operator<<(ostream &out,Graphmtx<V,W> &G);
private:
    //���Ķ�����
    int maxVertices;
    //��ǰ����
    int numEdges;
    //��ǰ������
    int numVertices;
    //�����
    T *VerticesList;
    //�ڽӾ���
    E **Edge;
    //����������ͼ�е�λ��
    int getVertexPos(T vertex)
    {
        for(int i=0; i<numVertices; i++)
        {
            if(VerticesList[i]==vertex)
                return i;
        }
        return -1;
    }
};

#endif // GRAPHMTX_H
