#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

// typedef int ElemType;
typedef struct LinkNode {
    int data;
    struct LinkNode* next;
}LinkNode, *LinkList;

int linkListDemo();
int createLinkList(LinkList& L, int* dataArr, int length);
void displayList(LinkList& L);
void createLinkListTail(LinkList& L, int* dataArr, int n);
int listMaxRecur(LinkNode* head, LinkList remain);
int nodeNum(LinkList& L);
float nodeMean(LinkList& node, LinkList& L);
int indexOf(LinkList& L, int n);
void insertAt(LinkList& L, int index, int e);
int lastOfM(LinkList& L, int m);
int isSame(LinkList& L, int n);
void removeSame(LinkList& L);
int lowerThanX(LinkList& L, int x);
void removeSameList(LinkList& La, LinkList& Lb);
void removeSameListPre(LinkList& La, LinkList& Lb);
void removeSameListThree(LinkList La, LinkList Lb, LinkList Lc);
void mergeListTwice(LinkList La, LinkList Lb);
void mergeListOnce(LinkList& La, LinkList &Lb, LinkList &Lc);
void removeBetween(LinkList L, int minElem, int maxElem);
void bubbleSortList(LinkList L);
void sortListInsert(LinkList L);
void adjustList(LinkList L, int x);
int isSubList(LinkList La, LinkList Lb);
int isSubLinkList(LinkList La, LinkList Lb);
int getListLength(LinkList L);
LinkNode* getCommonNode(LinkList La, LinkList Lb);
void listConvert(LinkList L);
#endif // LINKLIST_H_INCLUDED
