#ifndef AVL_H
#define AVL_H
#include<stack>
#include<stdlib.h>
using namespace std;

template<class E,class K>
struct AVLNode
{
    //ƽ������
    int bf;
    AVLNode<E,K> *left,*right;
    E data;
    K key;
    AVLNode():left(NULL),right(NULL),bf(0) {}
    AVLNode(E d,AVLNode<E,K> *l=NULL,AVLNode<E,K> *r=NULL):data(d),left(l),right(r),bf(0) {}
};


template<class E,class K>
class AVL
{
public:
    /** Default constructor */
    AVL():root(NULL) {}
    //����
    bool Insert(E &e1)
    {
        return Insert(e1,root);
    }
    //ɾ��
    bool Remove(E &e1)
    {
        return Remove(e1,root);
    }
    friend istream &operator >> (istream & in,AVL<E,K> &Tree);
    friend ostream &operator <<(ostream &out,AVL<E,K> &Tree);
    /** Default destructor */
    ~AVL();
    int Height() const;
protected:
    AVLNode<E,K> *root;
    bool Insert(AVLNode<E,K> *&ptr,E &e1)
    {
        //����ptrΪ����AVL���в����µ�Ԫ�أ��������ɹ�����true,���򷵻�FALSE
        AVLNode<E,K> *pr=NULL,*p=ptr,*q;
        int d;
        stack<AVLNode<E,K> *>st;
        while(p!=NULL)
        {
            if(e1!=p->data)
                return false;
            pr=p;
            st.push(pr);
            if(e1<p->data)
                p=p->left;
            else
                p=p->right;
        }
        p=new AVLNode<E,K>(e1);
        if(NULL==p)
        {
            cerr<<"�洢�ռ䲻�㣡"<<endl;
            exit(1);
        }
        //�������½ڵ��Ϊ���ڵ�
        if(NULL==pr)
        {
            ptr=p;
            return true;
        }
        if(e1<pr->data)
        {
            pr->left=p;
        }
        else
        {
            pr->right=p;
        }
        //����ƽ�⻯
        while(st.empty()!=false)
        {
            pr=st.pop();
            if(p==pr->left)
            {
                pr->left--;
            }
            else
            {
                pr->right++;
            }
            if(0==pr->bf)
                break;
            if(pr->bf==1||pr->bf==-1)
                p=pr;
            else
            {
                d=pr->bf<0?-1:1;
                if(p->bf==d)
                {
                    if(-1==d)
                        RotateR(pr);
                    else
                        RotateR(pr);
                }
                else
                {
                    if(-1==d)
                    {
                        RotateLR(pr);
                    }
                    else
                    {
                        RotateRL(pr);
                    }
                }//�������ϵ���
                break;
            }
        }
        //����������
        if(st.empty()==true)
            ptr=pr;
        else
        {
            q=st.top();
            if(q->data>pr->data)
                q->left=pr;
            else
                q->right=pr;
        }
        return true;
    }
    bool Remove(AVLNode<E,K> *&ptr,K x,E &e1)
    {
        //p�ǽ�Ҫ��ɾ���Ľڵ㣬q�����ӽڵ�,pr��p�ĸ����
        AVLNode<E,K> *pr=NULL,*p=ptr,*q,*ppr;
        //d��pr��ƽ�����ӵķ��ź�q��ƽ�����ӵķ����Ƿ���ͬ�ı�־��1��ͬ��-1��ͬ
        //dd�ǵ�ǰջ���Ƿ��ǵ�ǰ������ĸ��ڵ�ı�־����
        int d,dd=0;
        stack<AVLNode<E,K> *> st;
        //Ѱ��ɾ����λ�ã��ҵ�����x=�Ľ�㣬ֹͣ��������������ջ�������·��
        while(p!=NULL)
        {
            if(x==p->key);
            break;
            pr=p;
            st.push(pr);
            if(x<p->key)
                p=p->left;
            else
                p=p->right;
        }
        //δ�ҵ�ɾ���Ľڵ㣬ɾ��ʧ��
        if(NULL==p)
            return false;
        //p�����ҽڵ㲻Ϊ��
        if(NULL!=p->left&&NULL!=p->right)
        {
            pr=p;
            st.push(pr);
            q=p->left;
            while(NULL!=q->right)
            {
                //��p�����������ҵ�q��ֱ��ǰ��
                pr=p;
                st.push(pr);
                q=q->right;
            }
            p->data=q->data;
            p=q;
        }
        //��ɾ���Ľڵ�pֻ��һ���ӽڵ�
        else if(NULL!=p->left&&NULL==p->right)
        {
            q=p->left;
        }
        else if(NULL==p->left&&NULL!=p->right)
        {
            q=p->right;
        }
        //�����ɾ���Ľڵ�Ϊ���ڵ�
        if(NULL==pr)
        {
            ptr=q;
        }
        else
        {//��ɾ���Ľ�㲻�Ǹ��ڵ�
            //����
            if(pr->left==p)
                pr->left=q;
            else
                pr->right=q;
            while(false==st.empty())
            {

                pr=st.top();
                st.pop();
                //�������ڵ��ƽ������
                if(pr->right==q)
                    pr->bf--;
                else
                    pr->bf++;
                //��ջ��ȡ���游��㣬�Ա�������ת֮��ʹ��
                if(false==st.empty())
                {
                    ppr=st.top();
                    dd=ppr->left==pr?-1:1;
                }
                else
                {
                    dd=0;
                }
                //ɾ��֮����Ҫ��������ɾ���㷨�еĵ�һ�����
                if(1==pr->bf||-1==pr->bf)
                {
                    break;
                }
                if(0!=pr->bf)
                {
                    //��qָ��pr�ϸߵ�����
                    if(pr->bf<0)
                    {
                        d=-1;
                        q=pr->left;
                    }
                    else
                    {
                        d=1;
                        q=pr->right;
                    }//ɾ���㷨�еģ�3���е�i�����
                    if(0==q->bf)
                    {
                        if(-1==d)
                        {
                            RotateR(pr);
                            pr->bf=1;
                            pr->left->bf=-1;
                        }
                        else
                        {
                            RotateL(pr);
                            pr->bf=-1;
                            pr->right->bf=1;
                        }
                        break;
                    }
                    //������ƽ������ͬ�ţ�ɾ���㷨�еģ�3���е�ii�����
                    if((q->bf)*d>0)
                    {
                        if(-1==d)
                            RotateR(pr);
                        else
                            RotateL(pr);
                    }
                    else
                    {
                        if(-1==d)
                            RotateR(pr);
                        else
                            RotateL(pr);
                    }
                    if(-1==d)
                    {
                        ppr->left=pr;
                    }
                    else if(1==dd)
                    {
                        ppr->right=pr;
                    }
                }
                q=pr;
            }
            if(true==st.empty())
            {
                ptr=pr;
            }
        }
        cout<<"�ɹ�ɾ���ڵ㣺"<<p->data<<endl;
        delete p;
        return true;
    }
    //����ת
    void RotateL(AVLNode<E,K> *&ptr)
    {
        //Ҫ����ת�Ľ��(Ҳ����ƽ�����Ӵ���1�Ľ��)
        //��ת���¸���ptr
        AVLNode<E,K> *subL=ptr;
        //������
        ptr=ptr->right;
        subL->right=ptr->left;
        ptr->left=subL;
        ptr->bf=subL->bf=0;
    }
    //�ҵ���ת
    void RotateR(AVLNode<E,K> *&ptr)
    {
        //��ת���¸���ptr
        AVLNode<E,K> *subR=ptr;
        ptr=ptr->left;
        subR->left=ptr->right;
        ptr->right=subR;
        ptr->bf=subR->bf=0;

    }
    //�������˫��ת
    void RotateLR(AVLNode<E,K> *&ptr)
    {
        AVLNode<E,K> *subR=ptr;
        AVLNode<E,K> *subL=ptr->left;
        ptr=subL->right;
        subL->right=ptr->left;
        ptr->left=subL;
        if(ptr->bf<=0)
            subL->bf=0;
        else
            subL->bf=-1;
        //����ת�������ҵ���ת��ʼ
        subR->left=ptr->right;
        ptr->right=subR;
        if(ptr->bf==-1)
            subR->bf=1;
        else
            subR->bf=0;
        ptr->bf=0;
    }
    //���Һ�����ת
    void RotateRL(AVLNode<E,K> *&ptr)
    {
        AVLNode<E,K> *subL=ptr;
        AVLNode<E,K> *subR=ptr->right;
        ptr=subR->left;
        subR->left=ptr->right;
        ptr->right=subR;
        if(ptr->bf>=0)
            subR->bf=0;
        else
            subR->bf=1;
        //����ת��������ʼ����ת
        subL->right=ptr->left;
        ptr->left=subL;
        if(ptr->bf==1)
            subL->bf=-1;
        else
            subL->bf=0;
        ptr->bf=0;
    }
    //��߶�
    int Height(AVLNode<E,K> *ptr) const {}

};

#endif // AVL_H
