#include "stdio.h"
#include "malloc.h"

typedef struct BiTNode{
    char data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

typedef struct LinkNode{
    BiTNode *data;
    LinkNode *next;
}LinkNode,*LinkStack;

typedef struct LinkQueue{
    LinkNode *front,*rear;
}LinkQueue,*LiQueue;

void InitQueue(LiQueue &Q){
    LinkNode *n = (LinkNode *)malloc(sizeof(LinkNode));
    n->next=NULL;
    Q = (LiQueue)malloc(sizeof(LinkQueue));
    Q->front=n;
    Q->rear=n;
}

int IsQueueEmpty(LiQueue Q){
    if(Q->front==Q->rear){
        return 1;
    }else{
        return 0;
    }
}

void ClearQueue(LiQueue &Q){
    while(!IsQueueEmpty(Q)){
        LinkNode *p = Q->front;
        Q->front = p->next;
        free(p);
    }
}

void EnQueue(LiQueue &Q,LinkNode *&p){
    Q->rear->next=p;
    Q->rear = p;
}

void DeQueue(LiQueue &Q,LinkNode *&p){
    p=Q->front->next;
    Q->front=p;
}

int IsEmpty(LinkStack S){
    if(S->next!=NULL)
        return 0;
    else
        return 1;
}

void InitStack(LinkStack &S){
    S->next=NULL;
}

void Push(LinkStack &S,BiTNode *p){
    LinkNode *li = (LinkNode *)malloc(sizeof(LinkNode));
    li->data=p;
    li->next=S->next;
    S->next=li;
}

void Pop(LinkStack &S,BiTNode *&p){
    if(!IsEmpty(S)){
        LinkNode *li = S->next;
        p=li->data;
        S->next = li->next;
        free(li);
    }
}

void InitBiTree(BiTree &T){
    BiTNode *A = (BiTNode *)malloc(sizeof(BiTNode));
    A->data = 'A';
    BiTNode *B = (BiTNode *)malloc(sizeof(BiTNode));
    B->data = 'B';
    A->lchild = B;
    BiTNode *C = (BiTNode *)malloc(sizeof(BiTNode));
    C->data = 'C';
    A->rchild = C;
    BiTNode *D = (BiTNode *)malloc(sizeof(BiTNode));
    D->data = 'D';
    D->lchild = NULL;
    D->rchild = NULL;
    B->lchild = D;
    BiTNode *E = (BiTNode *)malloc(sizeof(BiTNode));
    E->data = 'E';
    E->lchild = NULL;
    E->rchild = NULL;
    B->rchild = E;
    BiTNode *F = (BiTNode *)malloc(sizeof(BiTNode));
    F->data = 'F';
    F->lchild = NULL;
    F->rchild = NULL;
    C->lchild = F;
    BiTNode *G = (BiTNode *)malloc(sizeof(BiTNode));
    G->data = 'G';
    G->lchild = NULL;
    G->rchild = NULL;
    C->rchild = G;
    T = A;
}

void visit(BiTNode *p){
    if(p!=NULL){
        printf("%c\t",p->data);
    }
}

//递归遍历
//先序遍历
void PreOrder(BiTree T){
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
//中序遍历
void InOrder(BiTree T){
    if(T!=NULL){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}
//后序遍历
void PostOrder(BiTree T){
    if(T!=NULL){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

//非递归算法
//先序遍历
void PreOrderByStack(LinkStack &S,BiTree T){
    BiTNode *p = T;
    InitStack(S);
    while (p!=NULL || !IsEmpty(S)){
        visit(p);
        if(p->lchild!=NULL){
            Push(S,p);
            p = p->lchild;
        }
        else
        {
            if(p->rchild!=NULL){
                p = p->rchild;
            } else {
                Pop(S,p);
                p = p->rchild;
            }
        }
    }

}
//中序遍历
void InOrderByStack(LinkStack &S,BiTree T){
    BiTNode *p = T;
    InitStack(S);
    while(p!=NULL || !IsEmpty(S)){
        if(p!=NULL){
            Push(S,p);
            p = p->lchild;
        } else {
            Pop(S,p);
            visit(p);
            p=p->rchild;
        }
    }
}
//后序遍历
void PostOrderByStack(LinkStack &S,BiTree T){
    InitStack(S);
    BiTNode *p = T;
    BiTNode *pre = NULL;
    int flag = 0;
    while(!flag || !IsEmpty(S)){
        if(p!=NULL && !flag) {
            Push(S,p);
            p = p->lchild;
        }
        else{
            flag=0;
            Pop(S,p);
            if(p->rchild!=NULL&&pre!=p->rchild){ //有右孩子或者右孩子没有遍历过
                Push(S,p);
                p=p->rchild;
            } else { //没有右孩子或者右孩子已经遍历过
                visit(p);
                pre=p;
                flag=1;
            }
        }
    }
}
//层次遍历（使用队列来实现）
void LevelOrder(LiQueue &Q,BiTree T){
    InitQueue(Q);
    BiTNode *p = T;
    LinkNode *n = (LinkNode *)malloc(sizeof(LinkNode));
    n->data = p;
    EnQueue(Q,n);
    while(!IsQueueEmpty(Q)){
        DeQueue(Q,n);
        visit(n->data);
        if(n->data->lchild!=NULL){
            LinkNode *l = (LinkNode *)malloc(sizeof(LinkNode));
            l->data = n->data->lchild;
            EnQueue(Q,l);
        }
        if(n->data->rchild!=NULL){
            LinkNode *r = (LinkNode *)malloc(sizeof(LinkNode));
            r->data = n->data->rchild;
            EnQueue(Q,r);
        }
    }
}

void PrintSequence(){
    BiTree T;
    InitBiTree(T);

    LinkStack S;
    //PostOrderByStack(S,T);

    LiQueue Q;
    LevelOrder(Q,T);
    /*
    PreOrder(T);
    printf("\n");
    InOrder(T);
    printf("\n");
    PostOrder(T);
    printf("\n");
    */
}

int main(){
    PrintSequence();
}
