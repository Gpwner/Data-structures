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
        //初始化邻接矩阵
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
    //当前定点数
    int NumberOfvertices()
    {
        return numVertices;
    }
    //返回当前边数
    int NumberOfEdges()
    {
        return numEdges;
    }
//获取顶点的值
    T getValue(int i)
    {
        return i>=0&&i<numVertices?VerticesList[i]:NULL;
    }
    //获取边上的权值
    E getWeight(int v1,int v2)
    {
        return -1!=v1&&-1!=v2?Edge[v1][v2]:0;
    }
    //获取顶点v的第一个邻接顶点
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
    //获取v的邻接顶点w的下一邻接顶点
    int getNextNeighbor(int v,int w)
    {
        if(-1!=v&&-1!=w)
            for(int col=w+1; col<maxVertices; col++)
                if(Edge[v][col]>0&&Edge[v][col]<maxWeight)
                    return col;
        return -1;
    }
    //插入顶点
    bool insertVertex(const T &vertex)
    {
        if(numVertices==maxVertices)
            return false;
        VerticesList[numVertices++]=vertex;
        return true;
    }
    //插入边
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
    //删除顶点v以及所有与之关联的边
    bool removeVertex(int v)
    {
        //v不在图中不删除
        if(v<0||v>numVertices)
            return false;
        //只剩下一个顶点，不删除
        if(1==numVertices)
        {
            return false;
        }
        VerticesList[v]=VerticesList[numVertices-1];
        //减去与v相关联的边
        for(int i=0; i<numVertices; i++)
            if(Edge[v][i]>0&&Edge[v][i]<maxWeight)
                numEdges--;
        //用最后一列填补第
        for(int i=0; i<numVertices; i++)
            Edge[i][v]=Edge[i][numVertices-1];
        numVertices--;
        //用最后一行填补第v行
        for(int i=0; i<numVertices; i++)
            Edge[v][i]=Edge[numVertices-1][i];
        return true;
    }
    //删除边(v1,v2)
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
    //最大的顶点树
    int maxVertices;
    //当前边数
    int numEdges;
    //当前顶点树
    int numVertices;
    //顶点表
    T *VerticesList;
    //邻接矩阵
    E **Edge;
    //给出顶点在图中的位置
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
