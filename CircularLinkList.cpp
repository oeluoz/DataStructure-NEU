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

// ɾ���ڵ�p��ֱ��ǰ��
void deleteNodePre(LinkNode* p)
{
    LinkNode* pCurrent = p->next;
    LinkNode* pPre = p;
    while(pCurrent->next != p) {
        pPre = pCurrent;
        pCurrent = pCurrent->next;
    }
    // ɾ������
    pPre->next = pCurrent->next;
    free(pCurrent);
    displayCircularListNoneHead(p);
}

// ��������ͷ��������
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
// �ڵ����ӷ�����ת
void reverseCircularList(LinkList L)
{
    // 1 -> 2 -> 3 -> 4
    // 1 <- 2 <- 3 <- 4
    LinkNode* pCurrent = L->next;
    L->next = L; // �������ʼ��ʱ��ָ��NULL��ѭ������ָ֮����
    while(pCurrent != L) {
        // ͷ�巨����ڵ�
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;
        t->next = L->next;
        L->next = t;
    }
    displayCircularList(L);
}

// ���������� k ����λ(����ͷ���)
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

// ��ĸ�����ַ�
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

// ��ȡi�Žڵ�ǰ���ڵ�
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

// i �Žڵ㵽 m �Žڵ㹹������ѭ������
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

// ������ѭ��������ϲ���һ��ѭ��������(��С�¼����Ӷ�)
void mergeCircularList(LinkList La, int m, LinkList Lb, int n)
{
    LinkNode* pCurrentA = La -> next;
    LinkNode* pCurrentB = Lb -> next;
    // �ӽ�С��һ���������ҵ�β�ڵ㣬���뵽����һ�������ͷ���
    if(m < n) {
        while(pCurrentA->next != La) {
            pCurrentA = pCurrentA->next;
        }
        // ��Ҫɾ��ͷ�ڵ�
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

// ����βָ��ָ���ѭ��������
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
// Ϊ�˺ϲ����ӿ��٣����õ�ѭ�������βָ��
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
