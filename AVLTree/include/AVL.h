#ifndef AVL_H
#define AVL_H
#include<stack>
#include<stdlib.h>
using namespace std;

template<class E,class K>
struct AVLNode
{
    //平衡因子
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
    //插入
    bool Insert(E &e1)
    {
        return Insert(e1,root);
    }
    //删除
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
        //在以ptr为根的AVL树中插入新的元素，如果插入成功返回true,否则返回FALSE
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
            cerr<<"存储空间不足！"<<endl;
            exit(1);
        }
        //空树，新节点成为根节点
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
        //重新平衡化
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
                }//不再向上调整
                break;
            }
        }
        //调整到树根
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
        //p是将要被删除的节点，q是其子节点,pr是p的父结点
        AVLNode<E,K> *pr=NULL,*p=ptr,*q,*ppr;
        //d是pr的平衡因子的符号和q的平衡因子的符号是否相同的标志，1相同，-1不同
        //dd是当前栈顶是否是当前考查结点的父节点的标志，是
        int d,dd=0;
        stack<AVLNode<E,K> *> st;
        //寻找删除的位置，找到等于x=的结点，停止搜索，否则利用栈记忆查找路径
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
        //未找到删除的节点，删除失败
        if(NULL==p)
            return false;
        //p的左右节点不为空
        if(NULL!=p->left&&NULL!=p->right)
        {
            pr=p;
            st.push(pr);
            q=p->left;
            while(NULL!=q->right)
            {
                //在p的左子树中找到q的直接前驱
                pr=p;
                st.push(pr);
                q=q->right;
            }
            p->data=q->data;
            p=q;
        }
        //被删除的节点p只有一个子节点
        else if(NULL!=p->left&&NULL==p->right)
        {
            q=p->left;
        }
        else if(NULL==p->left&&NULL!=p->right)
        {
            q=p->right;
        }
        //如果被删除的节点为根节点
        if(NULL==pr)
        {
            ptr=q;
        }
        else
        {//被删除的结点不是根节点
            //链接
            if(pr->left==p)
                pr->left=q;
            else
                pr->right=q;
            while(false==st.empty())
            {

                pr=st.top();
                st.pop();
                //调整父节点的平衡因子
                if(pr->right==q)
                    pr->bf--;
                else
                    pr->bf++;
                //从栈中取出祖父结点，以备下面旋转之后使用
                if(false==st.empty())
                {
                    ppr=st.top();
                    dd=ppr->left==pr?-1:1;
                }
                else
                {
                    dd=0;
                }
                //删除之后不需要调整，如删除算法中的第一种情况
                if(1==pr->bf||-1==pr->bf)
                {
                    break;
                }
                if(0!=pr->bf)
                {
                    //用q指向pr较高的子树
                    if(pr->bf<0)
                    {
                        d=-1;
                        q=pr->left;
                    }
                    else
                    {
                        d=1;
                        q=pr->right;
                    }//删除算法中的（3）中的i种情况
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
                    //两结点的平衡因子同号，删除算法中的（3）中的ii种情况
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
        cout<<"成功删除节点："<<p->data<<endl;
        delete p;
        return true;
    }
    //左单旋转
    void RotateL(AVLNode<E,K> *&ptr)
    {
        //要左旋转的结点(也就是平衡因子大于1的结点)
        //旋转后新根在ptr
        AVLNode<E,K> *subL=ptr;
        //右子树
        ptr=ptr->right;
        subL->right=ptr->left;
        ptr->left=subL;
        ptr->bf=subL->bf=0;
    }
    //右单旋转
    void RotateR(AVLNode<E,K> *&ptr)
    {
        //旋转后新根在ptr
        AVLNode<E,K> *subR=ptr;
        ptr=ptr->left;
        subR->left=ptr->right;
        ptr->right=subR;
        ptr->bf=subR->bf=0;

    }
    //先左后右双旋转
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
        //左单旋转结束，右单旋转开始
        subR->left=ptr->right;
        ptr->right=subR;
        if(ptr->bf==-1)
            subR->bf=1;
        else
            subR->bf=0;
        ptr->bf=0;
    }
    //先右后左旋转
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
        //右旋转结束，开始左旋转
        subL->right=ptr->left;
        ptr->left=subL;
        if(ptr->bf==1)
            subL->bf=-1;
        else
            subL->bf=0;
        ptr->bf=0;
    }
    //求高度
    int Height(AVLNode<E,K> *ptr) const {}

};

#endif // AVL_H
