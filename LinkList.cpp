#include "LinkList.h"

//TODO: 多次重复创建会出现内存错误，顺序执行
// 不存在并发加锁问题

int linkListDemo()
{
    int data[6] = {6, 5, 4, 3, 2, 1};
    int dataA[8] = {1, 2, 3, 4, 5};
    int dataB[8] = {4, 5, 7};
    int dataC[8] = {1, 5, 6, 3, 3, 2, 1};

    LinkList L, La, Lb, Lc;
    // createLinkList(L, data, 5);
    createLinkListTail(L, data, 6);
    createLinkListTail(La, dataA, 4);
    createLinkListTail(Lb, dataB, 3);
    createLinkListTail(Lc, dataC, 7);

    /*
    LinkNode *p = L->next;
    while(p->next!=NULL) p = p->next;
    p->next = Lb->next;
    p = La->next;
    while(p->next!=NULL) p = p->next;
    p->next = Lb->next;
    */

    //displayList(L);
    //displayList(La);
    //displayList(La);
    // printf("%d\n", indexOf(L, 6));
    // insertAt(L, 7, 99);
    // lastOfM(L, 6);
    // printf("same: %d \n", isSame(L, 4));
    // removeSame(L);
    // lowerThanX(L, 1);
    // removeSameList(La, Lb);
    // removeSameListPre(La, Lb);
    // removeSameListThree(L, La, Lb);
    // mergeListTwice(La, Lb);
    // mergeListOnce(La, Lb, Lc);
    //removeBetween(L, 4, 6);
    // bubbleSortList(L);
    // sortListInsert( L );
    // adjustList(Lc, 3);
    // int result = isSubLinkList(La, Lb);
    // printf("result: %d", result);
    // printf("%d ", getCommonNode(L, La)->data);
    listConvert(La);
}

// 头插法创建带头结点的链表
int createLinkList(LinkList& L, int* dataArr, int length)
{
    L = (LinkNode*) malloc(sizeof(LinkNode));
    L -> next = NULL;

    for(int i = 0; i < length; i++) {
        LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
        node->data = dataArr[i];

        node->next = L->next;
        L->next = node;
    }
}

void createLinkListTail(LinkList& L, int* dataArr, int n)
{
    L = (LinkList) malloc(sizeof(LinkList));
    L->data = -1;
    L -> next = NULL;
    LinkList tail = L;
    for(int i=0; i < n; i++) {
        LinkList t = (LinkList)malloc(sizeof(LinkList));
        t ->data = dataArr[i];
        t->next = NULL;
        tail->next = t;
        tail = t;
    }
}

int listMaxRecur(LinkNode* head, LinkList remain)
{   // 1 2 3 4 5
    if(remain == NULL) return head->data;
    int maxNum = listMaxRecur(remain, remain->next);
    return head->data > maxNum ? head->data : maxNum;
}
int nodeNum(LinkList& L)
{
    if(L == NULL) return 0;
    return 1 + nodeNum(L->next);
}
float nodeMean(LinkList& head, LinkList& L)
{
    if(L == NULL) return 0;
    return head->data + nodeMean(L, L->next);
}
int indexOf(LinkList& L, int n)
{
    if(L==NULL) return -1;
    if(n==0 && L) return L->data;
    return indexOf(L->next, --n);
}

void insertAt(LinkList& L, int index, int e)
{
    if(index < 1) {
        printf("Out Range!");
        return ;
    }
    LinkList  current = L;
    int i = 0;
    while((i<index-1) && current) {
        current = current->next;
    }
    if(!current) {
        printf("Out Range!\n");
        return ;
    }
    LinkList node = (LinkList)malloc(sizeof(LinkList));
    node->data = e;
    LinkList t = current->next;
    current->next = node;
    node->next = t;
}

int lastOfM(LinkList& L, int m)
{
    LinkNode* current = L;
    int cnt = 0;
    while(current->next != NULL) { // 最小只能是倒数第一个
        if(cnt == m) {
            break;
        }
        current = current -> next;
        cnt++;
    }
    current = current->next; // 指向第 m+1 个节点
    LinkNode* preNode = L->next;
    while(current != NULL) {
        preNode = preNode->next;
        current = current->next;
    }
    printf("pre: %d \n", preNode->data);
}

// head 之后的 i 个节点
void getIthNode(int ith, LinkNode*head , LinkNode* &preIthNode, LinkNode* &pIthNode)
{
    LinkNode* pre = NULL;
    LinkNode* current = head;
    int cnt = 0;
    while((cnt < ith) && (current!=NULL)) {
        pre = current;
        current = current->next;
        cnt++;
    }
    preIthNode = pre;
    pIthNode = current;
}
void operateList(int j, int len, LinkList& La, LinkList& Lb)
{
    // La j
}

// 前 n/2 与 后 n/2 字符是否相同
int isSame(LinkList& L, int n)
{
    LinkNode* current = L->next;
    LinkNode* pre = L->next;
    LinkNode* post = L->next;
    // 2, 2, 1, 2, 2
    // 1 2 1
    int middle = n/2;
    int cnt = 0;
    while(cnt <= middle-1) {
        current = current->next;
        cnt++;
    }

    post = current->next;
    while(post) {
        if(pre->data != post->data) return 0;
        pre = pre->next;
        post = post->next;
    }
    return 1;
}
// 递增单链表中删除相同的多余元素
void removeSame(LinkList& L)
{
    LinkNode* current = L->next;
    while(current && current->next) {
        if(current->data == current->next->data) { // 前后不相等
            LinkNode* t = current->next;
            current->next = current->next->next;
            free(t);
        } else {
            current = current->next;
        }
    }

}

// 非递减单链表，比x小的节点数量
int lowerThanX(LinkList& L, int x)
{   // 1 2 2 2 4 6
    int cnt = 0;
    LinkNode* current = L->next;
    LinkNode* pre = L;
    while(current && current->data<x) {
        if(current == L || current->data != pre->data) {
            cnt++;
        }
        pre = current;
        current = current->next;
    }
    printf("lower than x: %d\n", cnt);
    return cnt;
}

// 删除递增链表La中Lb相同的内容
void removeSameList(LinkList& La, LinkList& Lb)
{
    // headA -> 1 -> 1
    // headB -> 1
    LinkNode* pLa = La;
    LinkNode* pLb = Lb->next;
    while(pLa && pLb && pLa->next) {
        if(pLa->next->data == pLb->data) { // 删除
            LinkNode* t = pLa->next;
            pLa->next = t->next;
            printf("aaa\n");
            free(t);
        } else if(pLa->next->data < pLb->data) {
            pLa = pLa->next;
        } else {
            pLb = pLb->next;
        }
    }
    printf("delete same: ");
    displayList(La);
}

// 优化版本，使用一个变量记录前驱，退化成普通的线性表
// 去重操作
void removeSameListPre(LinkList& La, LinkList& Lb)
{
    LinkNode* pre = La;
    LinkNode* pLa = La -> next;
    LinkNode* pLb = Lb -> next;
    while(pLa && pLb) {
        if(pLa->data == pLb->data) {
            // 删除
            LinkNode* t = pLa;
            pre->next = pLa->next;
            pLa = pre->next;
            // pLb 不能向后移，因为还有可能有相同的元素在pLa中
            free(t);
        } else if(pLa->data < pLb->data) {
            pre = pLa;
            pLa = pLa->next;
        } else {
            pLb = pLb->next;
        }
    }
}

// La 中删除同时出现在 Lb 和 Lc 中的元素
void removeSameListThree(LinkList La, LinkList Lb, LinkList Lc)
{
    // 1, 2, 3, 4, 5, 6
    // 1, 2, 3, 4
    // 1, 2, 3, 4

    LinkNode* pLa = La->next;
    LinkNode* pLb = Lb->next;
    LinkNode* pLc = Lc->next;

    LinkNode* pre = La;
    while(pLa&&pLb&&pLc) {
        if(pLb->data == pLc->data) { // 开始在La中查找
            while(pLa->data < pLb->data) {
                pre = pLa;
                pLa = pLa->next;
            }
            if(pLa->data == pLb->data) { //删除
                LinkNode* t = pLa;
                pre->next = t->next;
                pLa = pre->next;
                free(t);
            }
            pLb = pLb->next;
            pLc = pLc->next;
        } else if(pLb->data < pLc->data) {
            pLb = pLb->next;
        } else {
            pLc = pLc->next;
        }
    }
    displayList(La);
}

// 归并两条递增的链表(先全部放到一条链表再删除重复节点)
void mergeListTwice(LinkList La, LinkList Lb)
{
    // { 1, 3, 3, 4, 5, 7 }
    // { 1, 2, 3, 4, 8 }
    LinkNode* pLa = La->next;
    LinkNode* pre = La;
    LinkNode* pLb = Lb->next;
    while(pLa && pLb) {
        if(pLa->data < pLb->data) {
            pre = pLa;
            pLa = pLa->next;
        }else if(pLa->data == pLb->data) {
            pLb = pLb->next;
        } else {
            // pLb 节点插入 pLa 中
            LinkNode* t = pLb;
            pLb = pLb->next;
            t->next = pLa;
            pre->next = t;
        }
    }
    if(pLa == NULL && pLb) {
        pre->next = pLb;
    }
    pLa = La -> next;
    pre = La;
    displayList(La);
    while(pLa) {
        // 1 2 3 3 4 5 7 8
        if(pre!=La && pre->data == pLa->data) {
            LinkNode* t = pLa;
            pre->next = pLa->next;
            pLa = pre->next;
            free(t);
        } else {
            pre = pLa;
            pLa = pLa->next;
        }
    }
    displayList(La);
}

// 两个链表尾插法插入到Lc中中
void insertNode(LinkNode* &tail, LinkNode* pNode)
{
    if(tail->data == pNode->data) {
        free(pNode);
    } else {
        pNode->next = tail->next;
        tail->next = pNode;
        tail = tail->next;
    }
}
void mergeListOnce(LinkList& La, LinkList &Lb, LinkList &Lc)
{
    LinkNode* pLa = La->next;
    LinkNode* pLb = Lb->next;
    if(!Lb) printf("NULL");
    free(Lb);
    Lc = La;
    Lc->next = NULL;
    LinkNode* tail = Lc;
    while(pLa && pLb) {
        if(pLa->data < pLb->data) {
            LinkNode* t = pLa;
            pLa = pLa->next;
            insertNode(tail, t);
        } else {
            LinkNode* t = pLb;
            pLb = pLb->next;
            insertNode(tail, t);
        }
    }
    while(pLa) {
        LinkNode* t = pLa;
        pLa = pLa->next;
        insertNode(tail, pLa);
    }
    while(pLb) {
        LinkNode* t = pLb;
        pLb=pLb->next;
        insertNode(tail, t);
    }
    displayList(Lc);
}

// 删除链表中 (min, max) 之间的元素
void removeBetween(LinkList L, int minElem, int maxElem)
{
    LinkNode* pre = L;
    LinkNode* pL = L->next;
    while(pL) {
        if(pL->data > minElem && pL->data < maxElem) {
            LinkNode* t = pL;
            pre->next = pL->next;
            pL = pL->next;
            free(t);
        } else {
            pre = pL;
            pL = pL->next;
        }
    }
    displayList(L);
}

// 链表使用冒泡排序
void bubbleSortList(LinkList L)
{
    LinkNode* pre = L;
    LinkNode* pL = L->next;
    LinkNode* pLoop = L->next;
    LinkNode* pLast = NULL;
    while(pLoop) {
        LinkNode* pre = L;
        LinkNode* pL = L->next;
        while(pL) {
            if(pre!=L && (pre->data < pL->data)) {
                pre->data ^= pL->data;
                pL->data ^= pre->data;
                pre->data ^= pL->data;
            }
            pre = pL;
            pL = pL->next;
        }
        pLoop = pLoop->next;
    }
    displayList(L);
}

// 将链表原地排序
void sortListInsert(LinkList L)
{
    displayList(L);
    LinkNode* pL = L->next;
    L->next = NULL;
    L->data = -1;
    while(pL) {
        LinkNode* t = pL;
        pL = pL->next;
        LinkNode* pre = L;
        LinkNode* pCurrent = L->next;
        while(pCurrent && pCurrent->data < t->data) {
            pre = pCurrent;
            pCurrent = pCurrent ->next;
        }
        if(pCurrent && pCurrent->data == t->data) {
            free(t);
        } else {
            t->next = pre->next;
            pre->next = t;
        }
    }
    displayList(L);
}

// 将所有小于x元素放在前面，大于x元素放在后面
void adjustList(LinkList L, int x)
{
    // 1, 5, 6, 3, 2, 1
    LinkNode* pCurrent = L->next;
    LinkNode* dummyNode = (LinkNode*)malloc(sizeof(LinkNode));
    LinkNode *preDummy, *pTail;
    dummyNode->next = NULL;
    L->next = dummyNode;
    preDummy = L;
    pTail = dummyNode;
    while(pCurrent) {
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;

        if(t->data < x) { // 插入到前面
            t->next = L->next;
            L->next = t;
            if(preDummy == L) preDummy = t;
        } else if(t->data > x) { // 插入到后面
            t->next = pTail->next;
            pTail->next = t;
            pTail = t;
        } else {
            t->next = preDummy->next;
            preDummy->next = t;
            preDummy = t;
        }
    }
    preDummy->next = dummyNode->next;
    free(dummyNode);
    displayList(L);
}
int isSubList(LinkList La, LinkList Lb)
{
    // 1 2 3 4 5 6 7 8
    // 3 4 5 6
    LinkNode* pLa = La->next;
    LinkNode* pLb = Lb->next;

    LinkNode* pMove = Lb->next;
    while(pLa) {
        if(pLa->data == pLb->data) { // 匹配到第一个节点
            pMove = pLa;
            // 循环匹配
            while(pLb) {
                if(pLb && pMove && pMove->data == pLb->data) {
                    pLb = pLb->next;
                    pMove = pMove->next;
                } else {
                    break;
                }
            }
        }
        if(!pLb) {
            return 1;
        } else {
            pLb = Lb->next;
        }
        pLa = pLa->next;
    }
    return 0;
}

// 另外一种写法
int isSubLinkList(LinkList La, LinkList Lb)
{
    LinkNode* pStartPosition = La->next;
    LinkNode* pMoveLa = pStartPosition;
    LinkNode* pMoveLb = Lb->next;

    while(pMoveLa && pMoveLb) {
        if(pMoveLa->data == pMoveLb->data) {
            pMoveLa = pMoveLa->next;
            pMoveLb = pMoveLb->next;
        } else {
            pStartPosition = pStartPosition->next;
            pMoveLa = pStartPosition;
            pMoveLb = Lb->next;
        }
    }
    if(!pMoveLb) return 1;
    return 0;
}

// 获取两条链表的公共节点
LinkNode* getCommonNode(LinkList La, LinkList Lb)
{
    int lengthA = getListLength(La);
    int lengthB = getListLength(Lb);

    LinkNode* pLa = La->next;
    LinkNode* pLb = Lb->next;

    // 移动长链
    if(lengthA > lengthB) { // La 前进
        for(int i=0; i < lengthA - lengthB; i++)
            pLa = pLa->next;
    } else {
        for(int i=0; i < lengthB - lengthA; i++)
            pLb = pLb->next;
    }
    while(pLa) {
        if(pLa == pLb) {
            return pLa;
        }
        pLa = pLa->next;
        pLb = pLb->next;
    }
    return NULL;
}

int getListLength(LinkList L)
{
    int length = 0;
    LinkNode* pLa = L->next;
    while(pLa) {
        pLa = pLa->next;
        length++;
    }
    return length;
}

//  L1 L2...Ln -> L1 Ln L2
void listConvert(LinkList L)
{
    // 1 2 3 4 5
    int length = getListLength(L) / 2;
    LinkNode* pCurrent = L -> next;
    for(int i = 0; i < length-1; i++) {
        pCurrent = pCurrent->next;
    }
    LinkNode* head = pCurrent;
    pCurrent = pCurrent->next;
    head->next = NULL;


    while(pCurrent) {
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;

        t->next = head->next;
        head->next = t;
    }


    pCurrent = L->next;
    L->next = NULL;
    LinkNode* tail = L;

    head = head->next;
    for(int i=0; i < length; i++) {
        LinkNode* t = pCurrent;
        pCurrent = pCurrent->next;
        t->next = tail->next;
        tail->next = t;
        tail = t;

        t = head;
        head = head->next;
        t->next = tail->next;
        tail->next = t;
        tail = t;

    }

    if(head) {
        head->next = tail->next;
        tail->next = head;
    }
    displayList(L);
}

void displayList(LinkList& L)
{
    LinkNode* current = L->next;
    while(current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
