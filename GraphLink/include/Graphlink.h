#ifndef GRAPHLINK_H
#define GRAPHLINK_H
#include<stdlib.h>
#include<iostream>
using namespace std;
const int Defaultsize=30;
template <class T,class E>
struct Edge
{
    //�߽��Ķ���
    int dest;
    //���ϵ�Ȩֵ
    E cost;
    //��һ������ָ��
    Edge<T,E> *link;
    //���캯��
    Edge() {}
    //���������캯��
    Edge(int num,E weight):dest(num),cost(weight),link(NULL) {}
    bool operator !=(Edge<T,E> &R) const
    {
        return dest!=R.dest?true:false;
    }
};
template<class T,class E>
struct Vertex
{
    //���������
    T data;
    //�������ͷָ��
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
    /** Default constructor ���������б�����ʼ��NULL*/
    Graphlink(int sz=Defaultsize):maxVertices(sz),numVertices(0),numEdges(0)
    {
        Nodetable=new Vertex<T,E>[maxVertices];
        if(NULL==Nodetable)
        {
            cerr<<"�洢�������"<<endl;
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
    //��ȡ������е�i��λ�õĶ���
    T getValue(int i)
    {
        return i>=0&&i<numVertices?Nodetable[i].data:NULL;
    }
    //��ȡ���ϵ�Ȩֵ
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
    //����һ������
    bool insertVertex(const T &vertex)
    {
        if(numVertices==maxVertices)
            return false;
        Nodetable[numVertices].data=vertex;
        numVertices++;
        return true;
    }
    //ɾ��һ������
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
            //����߽��
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
        //�����һ���������ɾ���Ķ����λ��
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
    //����һ����
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
    //ɾ��һ����
    bool removeEdge(int v1,int v2)
    {
        if(-1==v1&&-1==v2)
        {
            Edge<T,E> *p=Nodetable[v1].adj,*q=NULL,*s=p;
            //��v1�ı������в��ұ�ɾ�ı�
            while(NULL!=p&&p->dest!=v2)
            {
                q=p;
                p=p->link;
            }
            if(NULL!=p)
            {
                //�Ľ���ǲ��Ǳ�������׽��
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
    //��ȡ�ڽӶ���
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
    //��ȡ����v���ڽӶ������һ�ڽӶ���
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
private:
    //���Ķ�����
    int maxVertices;
    //��ǰ����
    int numEdges;
    //��ǰ������
    int numVertices;
    //�����
    Vertex<T,E> *Nodetable;
    //����������ͼ�е�λ��
    int getVertexPos(const T Vertex)
    {
        for(int i=0; i<numVertices; i++)
            if(Nodetable[i].data==Vertex)
                return i;
        return -1;
    }
};

#endif // GRAPHLINK_H
