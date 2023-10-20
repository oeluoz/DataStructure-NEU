#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"
#include "CircularLinkList.h"

void circularLinkListDemo()
{
    int data[6] = {4, 5, 6, 7, 8, 9};
    int data2[3] = {1, 2, 3};
    LinkNode* L = NULL;
    LinkNode* Lb = NULL;

    LinkNode* LNoneHead = NULL;
    createCircularList(L, 6, data);
    createCircularList(Lb, 3, data2);
    // createCircularListNoneHead(LNoneHead, data, 6);
    // displayCircularListNoneHead(LNoneHead);

    // displayCircularList(L);
    // reverseCircularList(L);
    // leftMove(LNoneHead, 7);
    // deleteNodePre(LNoneHead->next->next);
    // dividedToThree(L);
    // reverseFromItoM(L, 3, 6);
    // mergeCircularList(Lb, 3, L, 6);
    createCircularListTail(L, 6, data);
    createCircularListTail(Lb, 3, data2);
    //displayCircularListTail(L);
    mergeCircularListTai(L, Lb);
}

void createCircularList(LinkList &L, int length, int* data)
{
    L = (LinkNode*)malloc(sizeof(LinkNode));
    L->next = L;
    LinkNode* pTail = L;
    for(int i = 0; i < length; i++)
    {
        LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
        t->data = data[i];
        t->next = pTail->next;
        pTail->next = t;
        pTail = t;
    }
}

// 删除节点p的直接前驱
void deleteNodePre(LinkNode* p)
{
    LinkNode* pCurrent = p->next;
    LinkNode* pPre = p;
    while(pCurrent->next != p) {
        pPre = pCurrent;
        pCurrent = pCurrent->next;
    }
    // 删除操作
    pPre->next = pCurrent->next;
    free(pCurrent);
    displayCircularListNoneHead(p);
}

// 创建不带头结点的链表
void createCircularListNoneHead(LinkList &L, int* data, int length)
{
    LinkNode* pTail = (LinkNode*)malloc(sizeof(LinkNode));
    pTail->data = data[0];
    pTail->next = pTail;
    L = pTail;

    for(int i = 1; i < length; i++) {
        LinkNode* t = (LinkNode*) malloc(sizeof(LinkNode));
        t->data = data[i];
        t->next = pTail->next;
        pTail->next = t;
        pTail = t;
    }
}
// 节点链接方向逆转
void reverseCircularList(LinkList L)
{
    // 1 -> 2 -> 3 -> 4
    // 1 <- 2 <- 3 <- 4
    LinkNode* pCurrent = L->next;
    L->next = L; // 单链表初始的时候指向NULL，循环链表之指向本身
    while(pCurrent != L) {
        // 头插法插入节点
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;
        t->next = L->next;
        L->next = t;
    }
    displayCircularList(L);
}

// 单链表左移 k 个单位(不带头结点)
int leftMove(LinkList &L, int k)
{
    if(!L) return 0;
    LinkNode* pCurrent = L;

    for(int i=0; i < k; i++) {
        pCurrent = pCurrent->next;
    }
    L = pCurrent;
    displayCircularListNoneHead(L);
}

void insertAlp(LinkNode* pNode, LinkList L)
{
    pNode->next = L->next;
    L->next = pNode;
}

// 字母数字字符
void dividedToThree(LinkList L)
{
    LinkNode* pCurrent = L->next;
    LinkList LNumber = (LinkList)malloc(sizeof(LinkNode));
    LNumber->next = LNumber;

    LinkList LAlpha = (LinkList)malloc(sizeof(LinkNode));
    LAlpha->next = LAlpha;

    LinkList LOther = (LinkList)malloc(sizeof(LinkNode));
    LOther->next = LOther;

    while(pCurrent != L)
    {
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;

        if(t->data >= '0' && t->data<='9') {
            insertAlp(t, LNumber);
        } else if((t->data >='A' && t->data <='Z') ||
                  (t->data >='a' && t->data<='z')) {
            insertAlp(t, LAlpha);
        } else {
            insertAlp(t, LOther);
        }
    }

    displayCircularList(LNumber);
    displayCircularList(LAlpha);
    displayCircularList(LOther);
}

// 获取i号节点前驱节点
LinkNode* getPre(LinkList L, int i)
{
    int cnt = 1;
    LinkNode* pPre = L;
    LinkNode* pCurrent = L->next;
    while(cnt < i) {
        pPre = pCurrent;
        pCurrent = pCurrent->next;
        cnt++;
    }
    return pPre;
}

// i 号节点到 m 号节点构成逆置循环链表
void reverseFromItoM(LinkList L, int i, int m)
{
    LinkNode* pPreI = getPre(L, i);
    LinkNode* pPreM = getPre(L, m);

    displayCircularList(L);
    LinkNode* LNew = (LinkNode*)malloc(sizeof(LinkNode));
    LNew->next = LNew;


    LinkNode* pCurrent = pPreI->next;
    LinkNode* pLast = pPreM->next;

    pPreI->next = pPreM->next->next;

    pLast->next = NULL;

    while(pCurrent)
    {
        LinkNode* t = pCurrent;
        pCurrent = pCurrent -> next;
        t -> next = LNew -> next;
        LNew -> next = t;
    }
    displayCircularList(L);
    displayCircularList(LNew);

}

// 将两个循环单链表合并成一个循环单链表(最小事件复杂度)
void mergeCircularList(LinkList La, int m, LinkList Lb, int n)
{
    LinkNode* pCurrentA = La -> next;
    LinkNode* pCurrentB = Lb -> next;
    // 从较小的一条链表中找到尾节点，插入到另外一条链表的头结点
    if(m < n) {
        while(pCurrentA->next != La) {
            pCurrentA = pCurrentA->next;
        }
        // 需要删除头节点
        LinkNode* t = pCurrentA->next;
        pCurrentA->next = Lb->next;
        Lb->next = t->next;
        free(t);
        displayCircularList(Lb);
    } else {
        while(pCurrentB->next != Lb ) {
            pCurrentB = pCurrentB -> next;
        }
        LinkNode* t = pCurrentB->next;
        pCurrentB->next = La->next;
        La->next = t->next;
        free(t);
        displayCircularList(La);
    }

}

// 创建尾指针指向的循环单链表
void createCircularListTail(LinkList &L, int n, int* data)
{
    L = (LinkNode*)malloc(sizeof(LinkNode));
    L->next = L;
    for(int i=0; i < n; i++) {
        LinkNode* t = (LinkNode*)malloc(sizeof(LinkNode));
        t->data = data[i];

        t->next = L->next;
        L->next = t;
        L = t;
    }
}
// 为了合并更加快速，设置单循环链表的尾指针
void mergeCircularListTai(LinkList& La, LinkList& Lb)
{
    LinkNode* pHeadLa = La->next;
    LinkNode* pHeadLb = Lb->next;
    La->next = pHeadLb->next;
    Lb->next = pHeadLa;
    free(pHeadLb);
    La = Lb;
    Lb = NULL;
    displayCircularListTail(La);
}
void displayCircularListTail(LinkList L)
{
    LinkNode* pHead = L->next;
    LinkNode* pCurrent = pHead->next;

    while(pCurrent != pHead) {
        printf("%d ", pCurrent->data);
        pCurrent = pCurrent->next;
    }
    printf("\n");
}

void displayCircularList(LinkList L)
{
    LinkNode* pCurrent = L->next;
    while(pCurrent != L) {
        printf(" %d ", pCurrent->data);
        pCurrent = pCurrent->next;
    }
    printf("\n");
}
void displayCircularListNoneHead(LinkList L)
{
    LinkNode* pCurrent = L;
    int isHead = 1;
    while(isHead || pCurrent != L) {
        printf("=>%d ", pCurrent->data);
        pCurrent = pCurrent->next;
        isHead = 0;
    }
    printf("\n");
}
