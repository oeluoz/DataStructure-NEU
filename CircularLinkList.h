#ifndef CIRCULARLINKLIST_H_INCLUDED
#define CIRCULARLINKLIST_H_INCLUDED


void circularLinkListDemo();
void createCircularList(LinkList &L, int length, int* data);
void displayCircularList(LinkList L);
void reverseCircularList(LinkList L);
int leftMove(LinkList &L, int k);
void displayCircularListNoneHead(LinkList L);
void createCircularListNoneHead(LinkList &L, int* data, int length);
void deleteNodePre(LinkNode* p);
void dividedToThree(LinkList L);
void insertAlp(LinkNode* pNode, LinkList L);
void dividedToThree(LinkList L);
void reverseFromItoM(LinkList L, int i, int m);
LinkNode* getPre(LinkList L, int i);
void mergeCircularList(LinkList La, int m, LinkList Lb, int n);
void createCircularListTail(LinkList &L, int n, int* data);
void displayCircularListTail(LinkList L);
void mergeCircularListTai(LinkList& La, LinkList& Lb);

#endif // CIRCULARLINKLIST_H_INCLUDED
