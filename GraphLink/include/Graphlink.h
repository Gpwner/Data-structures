#ifndef GRAPHLINK_H
#define GRAPHLINK_H
#include<stdlib.h>
#include<iostream>
using namespace std;
const int Defaultsize=30;
template <class T,class E>
struct Edge
{
    //边结点的定义
    int dest;
    //边上的权值
    E cost;
    //下一条边链指针
    Edge<T,E> *link;
    //构造函数
    Edge() {}
    //带参数构造函数
    Edge(int num,E weight):dest(num),cost(weight),link(NULL) {}
    bool operator !=(Edge<T,E> &R) const
    {
        return dest!=R.dest?true:false;
    }
};
template<class T,class E>
struct Vertex
{
    //顶点的名字
    T data;
    //边链表的头指针
    Edge<T,E> *adj;
};
template<class T,class E>
class Graphlink
{
    template <class V,class W>
    friend istream& operator >>(istream & in,Graphlink<V,W> &G);
    template <class V,class W>
    friend ostream& operator<<(ostream &out,Graphlink<V,W> &G);
public:
    /** Default constructor 创建顶点列表，并初始化NULL*/
    Graphlink(int sz=Defaultsize):maxVertices(sz),numVertices(0),numEdges(0)
    {
        Nodetable=new Vertex<T,E>[maxVertices];
        if(NULL==Nodetable)
        {
            cerr<<"存储分配错误"<<endl;
            exit(1);
        }
        for(int i=0; i<maxVertices; i++)
        {
            Nodetable[i].adj=NULL;
        }
    }
    /** Default destructor */
    ~Graphlink()
    {
        for(int i=0; i<maxVertices; i++)
        {
            Edge<T,E> *p=Nodetable[i].adj;
            while(NULL!=p)
            {
                Nodetable[i].adj=p->link;
                delete p;
                p=Nodetable[i].adj;
            }
        }
        delete []Nodetable;
    }
    //获取顶点表中第i个位置的顶点
    T getValue(int i)
    {
        return i>=0&&i<numVertices?Nodetable[i].data:NULL;
    }
    //获取边上的权值
    E getWeight(int v1,int v2)
    {
        if(-1!=v1&&-1!=v2)
        {
            Edge<T,E> *p=Nodetable[v1].adj;
            while(NULL!=p&&v2!=p->dest)
                p=p->link;
            if(NULL!=p)
                return p->cost;
        }
        return 0;
    }
    //插入一个顶点
    bool insertVertex(const T &vertex)
    {
        if(numVertices==maxVertices)
            return false;
        Nodetable[numVertices].data=vertex;
        numVertices++;
        return true;
    }
    //删除一个顶点
    bool removeVertex(int v)
    {
        if(1==numVertices||v<0||v>=numVertices)
            return false;
        Edge<T,E> *p,*s,*t;
        int k;
        while(NULL!=Nodetable[v].adj)
        {
            p=Nodetable[v].adj;
            k=p->dest;
            s=Nodetable[k].adj;
            t=NULL;
            //处理边结点
            while(NULL!=s&&v!=s->dest)
            {
                t=s;
                s=s->link;
            }
            if(NULL!=s)
            {
                if(NULL==t)
                    Nodetable[k].adj=s->link;
                else
                    t->link=s->link;
                delete s;
            }
            Nodetable[v].adj=p->link;
            delete p;
            numEdges--;
        }
        //用最后一个顶点填补被删除的顶点的位置
        numVertices--;
        Nodetable[v].data=Nodetable[v].data;
        p=Nodetable[v].adj=Nodetable[numVertices].adj;
        while(NULL!=p)
        {
            s=Nodetable[p->dest].adj;
            while(NULL!=s)
            {
                if(s->dest==numVertices)
                {
                    s->dest=v;
                    break;
                }
                else
                {
                    s=s->link;
                }
            }
        }
        return true;
    }
    //插入一条边
    bool insertEdge(int v1,int v2,E weight)
    {
        if(v1>=0&&v1<numVertices&&v2>=0&&v2<numVertices)
        {
            Edge<T,E> *q,*p=Nodetable[v1].adj;
            while(NULL!=p&&NULL!=v2)
                p=p->link;
            if(NULL!=p)
            {
                return false;
            }
            p=new Edge<T,E>();
            q=new Edge<T,E>();
            p->dest=v2;
            p->cost=weight;
            p->link=Nodetable[v1].adj;
            Nodetable[v1].adj=p;
            q->dest=v1;
            q->cost=weight;
            q->link=Nodetable[v2].adj;
            Nodetable[v2].adj=q;
            numEdges++;
            return true;
        }
        return false;
    }
    //删除一条边
    bool removeEdge(int v1,int v2)
    {
        if(-1==v1&&-1==v2)
        {
            Edge<T,E> *p=Nodetable[v1].adj,*q=NULL,*s=p;
            //在v1的边链表中查找被删的边
            while(NULL!=p&&p->dest!=v2)
            {
                q=p;
                p=p->link;
            }
            if(NULL!=p)
            {
                //改结点是不是边链表的首结点
                if(s==p)
                    Nodetable[v1].adj=p->link;
                else
                    q->link=p->link;
                delete p;
            }
            else
                return false;
            p=Nodetable[v2].adj;
            q=NULL;
            s=p;
            while(p->dest!=v1)
            {
                q=p;
                p=p->link;
            }
            if(p==s)
                Nodetable[v2].adj=p->link;
            else
                q->link=p->link;
            delete p;
            return true;
        }
        return false;
    }
    //获取邻接顶点
    int GetFirstNeighbor(int v)
    {
        if(-1!=v)
        {
            Edge<T,E> *p=Nodetable[v].adj;
            if(NULL!=p)
                return p->dest;
        }
        return -1;
    }
    //获取顶点v的邻接顶点的下一邻接顶点
    int getNextNeighbor(int v,int w)
    {
        if(-1!=v)
        {
            Edge<T,E> *p=Nodetable[v].adj;
            while(NULL!=p&&w!=p->dest)
            {
                p=p->link;
            }
            if(NULL!=p&&NULL!=p->link)
                return p->link->dest;
        }
        return -1;
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
private:
    //最大的顶点树
    int maxVertices;
    //当前边数
    int numEdges;
    //当前顶点树
    int numVertices;
    //顶点表
    Vertex<T,E> *Nodetable;
    //给出顶点在图中的位置
    int getVertexPos(const T Vertex)
    {
        for(int i=0; i<numVertices; i++)
            if(Nodetable[i].data==Vertex)
                return i;
        return -1;
    }
};

#endif // GRAPHLINK_H
