#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include <math.h>
#include <queue>
using std::queue;

#define MAXNODE 100 // 树节点最多数

BiTreeNode* globalPre;
BiTreeNode* globalHead;

void treeDemo()
{
    ElemType preOrderList[] = { 'A', 'B', 'D', 'E', 'C', 'F', 'G','H', 'I' };
    ElemType levelOrderList[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G' };

    ElemType inOrderList[] = {'D', 'B', 'E', 'A', 'F', 'C', 'G', 'H', 'I'};
    BiTree root = createTreePreAndIn(preOrderList, 0, 5,
                                     inOrderList, 0, 5);
    BiTree rootLevel = createTreeLevelAndIn(levelOrderList, 0, 6, inOrderList, 0, 6);

    BSTree bstRoot = NULL;

    preTraverse(root);
    printf("\n");
    inTraverse(root);
    printf("\n");
    printf("%d \n", getTreeNode(root));
    int balance =  0;
    isBalanceTree(root, balance);
    printf("balance: %d \n", balance);
    printf("leaf: %d \n", getLeafNum(root));
    printf("one degree: %d \n", getOneDegreeNum(root));
    BiTreeNode* xNode = getXNode(root, 'G');
    if(xNode){
        printf("%c \n", xNode->data);
    } else {
        printf("not found");
    }
    BiTreeNode* node = NULL;
    getXNodeRef(root, 'M', node);
    if(!node) {
        printf("not found\n");
    } else {
        printf("%c \n", node->data);
    }
    printf("height: %d \n", getHeight(root));
    int xHeight = -1;
    xHeight = getXnodeHeight(root, 'M');
    printf("xHeihgt: %d\n", xHeight);
    //exchangeTree(root);
    preTraverse(root);
    printf("\n");

    /*
        BiTreeNode* pre = (BiTreeNode*)malloc(sizeof(BiTreeNode));
        pre->data = 'X';
        pre->rchild = NULL;
        pre->lchild = NULL;
        BiTreeNode* head = pre;
        linkLeafNode(pre, root);
    */

    /*
        globalPre = (BiTreeNode*)malloc(sizeof(BiTreeNode));
        globalHead = globalPre;
        globalPre->lchild = NULL;
        globalPre->rchild = NULL;

        linkLeaf2DoubleLinkList(root);
        BiTreeNode* pCurrent = globalHead->rchild;
        while(pCurrent!=NULL) {
            printf("%c ", pCurrent->data);
            pCurrent = pCurrent->rchild;
        }
        printf("\n");
        pCurrent = globalPre;
        while(pCurrent!=globalHead) {
            printf("%c ", pCurrent->data);
            pCurrent = pCurrent->lchild;
        }
    */
    // printf("expression: %.2f", expressionCalculate(root));
    // printf("level traverse: ");
    printf("is complete: %d \n", isCompleteTree(root));
    printf("maxWidth: %d \n", getMaxWidth(root));

    int dataBST[] = {6, 8, 2, 1, 4, 3};
    bstCreate(bstRoot, dataBST, 6);
    // bstDelete(bstRoot, 2);
    inTraverse(bstRoot);
    printf("\nx depth: %d \n", getXlevel(bstRoot, 3, 1));
    BSTree T1 = NULL, T2 = NULL;
    splitBST(3, bstRoot, T1, T2);
    inTraverse(T1);
    printf("\n");
    inTraverse(T2);
}

void preTraverse(BiTree root)
{
     if(root == NULL) return;
     printf("%c ", root->data);
     preTraverse(root->lchild);
     preTraverse(root->rchild);
}

void inTraverse(BiTree root)
{
    if(root == NULL) return;
    inTraverse(root->lchild);
    printf("%c ", root->data);
    inTraverse(root->rchild);

}

void inTraverse(BSTree T)
{
    if(T) {
        inTraverse(T->lchild);
        printf("%d ", T->data);
        inTraverse(T->rchild);
    }
}

BiTree createTreePreAndIn(ElemType preOrderList[], int preStartIndex, int preEndIndex,
                        ElemType inOrderList[], int inStartIndex, int inEndIndex)
{
    if(preStartIndex > preEndIndex) {
        return NULL;
    }
    BiTreeNode* root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    root->data = preOrderList[preStartIndex]; // 先序序列第一个位置

    int rIndex;
    for(rIndex = inStartIndex; rIndex <= inEndIndex; rIndex++) {
        if(inOrderList[rIndex] == root->data) break;
    }

    // 创建左子树
    int leftLength = rIndex - inStartIndex; // 计算左子树长度，pre按照 root left right 顺序排列，因此计算出长度直接可以进行划分
    root->lchild = createTreePreAndIn(preOrderList, preStartIndex + 1, preStartIndex + leftLength,
                       inOrderList, inStartIndex, rIndex - 1);
    root->rchild = createTreePreAndIn(preOrderList,preStartIndex+leftLength+1, preEndIndex,
                                      inOrderList, rIndex+1, inEndIndex);
}

BiTree createTreeLevelAndIn(ElemType levelOrderList[], int levelStartIndex, int levelEndIndex,
                            ElemType inOrderList[], int inStartIndex, int inEndIndex)
{
    if(levelStartIndex > levelEndIndex) return NULL;
    BiTreeNode* root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    root->data = levelOrderList[levelStartIndex];

    int rIndex; // root 节点在中序遍历序列中的位置
    for(rIndex = inStartIndex; rIndex < inEndIndex; rIndex++) {
        if(inOrderList[rIndex] == root->data) break;
    }

    ElemType leftLevelOrderList[MAXNODE];
    int leftLevelOrderLength = 0;
    // 层序遍历左子树
    for(int i = levelStartIndex + 1; i <= levelEndIndex; i++) {
        for(int j = inStartIndex; j < rIndex; j++) {
            if(levelOrderList[i] == inOrderList[j]) { // 成功匹配上，说明当前节点是左子树
                leftLevelOrderList[leftLevelOrderLength++] = levelOrderList[i];
            }
        }
    }

    ElemType rightLevelOrderList[MAXNODE];
    int rightLevelOrderLength = 0;
    // 层序遍历右子树
    for(int i = levelStartIndex + 1; i <= levelEndIndex; i++) {
        for(int j = rIndex + 1; j <= inEndIndex; j++) {
            if(levelOrderList[i] == inOrderList[j]) { // 成功匹配上，说明当前节点是左子树
                rightLevelOrderList[rightLevelOrderLength++] = levelOrderList[i];
            }
        }
    }
    root->lchild = createTreeLevelAndIn(leftLevelOrderList, 0, leftLevelOrderLength - 1,
                                        inOrderList, inStartIndex, rIndex - 1);
    root->rchild = createTreeLevelAndIn(rightLevelOrderList, 0, rightLevelOrderLength - 1,
                                        inOrderList, rIndex + 1, inEndIndex);
}

int getTreeNode(BiTree root)
{
    if(root) {
        return 1 + getTreeNode(root->lchild) + getTreeNode(root->rchild);
    } else {
        return 0;
    }
}

// 判断是否平衡二叉树
int isBalanceTree(BiTree root, int& balance)
{
    int bl = 0, br = 0, hl = 0, hr = 0, h = 0, balanceRoot = 0;
    if(root) { // 树空一定会出去
        hl = isBalanceTree(root->lchild, bl);
        hr = isBalanceTree(root->rchild, br);
        if(abs(hl - hr) < 2) {
            balanceRoot = 1;
        }

        balance = balanceRoot && bl && br;
        h = ( hl > hr ? hl : hr ) + 1;
        return h;
    } else {
        balance = 1;
        return 0;
    }
}

// 求二叉树中叶子节点的个数
int getLeafNum(BiTree root)
{
    if(!root) return 0;
    if(!root->lchild && !root->rchild)
        return 1 + getLeafNum(root->lchild) + getLeafNum(root->rchild);
    return getLeafNum(root->lchild) + getLeafNum(root->rchild);
}

// 查找二叉树中度为 1 的节点数
int getOneDegreeNum(BiTree root)
{
    if(!root) return 0;
    if(root->lchild && !root->rchild || !root->lchild && root->rchild) return 1 + getOneDegreeNum(root->lchild) + getOneDegreeNum(root->rchild);
    return getOneDegreeNum(root->lchild) + getOneDegreeNum(root->rchild);
}

// 查找二叉树中为x的节点
BiTreeNode* getXNode(BiTree root, ElemType x)
{
    if(!root) return NULL;
    if(root->data == x) return root;

    BiTreeNode* lnode = getXNode(root->lchild, x);
    if(lnode) return lnode;
    BiTreeNode* rnode = getXNode(root->rchild, x);
    if(rnode) return rnode;
}
// 引用的方式查找 x 节点
void getXNodeRef(BiTree root, ElemType x, BiTreeNode* & node)
{
    if(!root){
        return ;
    }
    if(root->data == x) {
        node = root;
        return;
    }
    getXNodeRef(root->lchild, x, node);
    getXNodeRef(root->rchild, x, node);
}

// 求二叉树的高度
int getHeight(BiTree root)
{
    if(!root) return 0;
    int lh = getHeight(root->lchild);
    int rh = getHeight(root->rchild);

    return lh > rh ? lh : rh + 1;
}

// 求二叉树中值为x节点作为根的深度
void getXnodeHeightRef(BiTree root, ElemType x, int& xHeight)
{
    if(!root) return ;
    if(root->data == x) {
        xHeight = getHeight(root);
        return ;
    }
    getXnodeHeightRef(root->lchild, x, xHeight);
    getXnodeHeightRef(root->rchild, x, xHeight);
}

// 二叉树中节点x作为根的高度
int getXnodeHeight(BiTree root, ElemType x)
{
    if(!root) return 0;
    if(root->data == x) return getHeight(root);
    int lh = getXnodeHeight(root->lchild, x);
    int rh = getXnodeHeight(root->rchild, x);
    return lh > rh ? lh : rh;
}

// 交换一颗二叉树
void exchangeTree(BiTree root)
{
    if(!root) return;
    BiTreeNode* t = root->lchild;
    root->lchild = root->rchild;
    root->rchild = t;
    exchangeTree(root->lchild);
    exchangeTree(root->rchild);
}

int isSameTree(BiTree root1, BiTree root2)
{
    if(!root1 && !root2) {
        return 1; // 两棵树都是空相似
    } else if((!root1 && root2) || (root1 && !root2)) {
        return 0; // 一棵树为空另外一棵树不为空，不相似
    } else {
        return isSameTree(root1->lchild, root2->lchild)
        && isSameTree(root1->rchild, root2->rchild); // 两棵树都不为空，当前节点相似，判断字树是否相似
    }
}

void linkLeafNode(BiTreeNode*& pre, BiTree root)
{
    if(root) {
        if(!root->lchild && !root->rchild) { // 当前节点是一个叶子节点
            root->lchild = pre;
            pre->rchild = root;
            pre = root;
        }
    } else { // 如果用先序遍历的方式会导致，叶子节点连接前序，然后往叶子节点遍历
        linkLeafNode(pre, root->lchild);
        linkLeafNode(pre, root->rchild);
    }
}

// 使用头插法插入到链表中
void linkLeaf2DoubleLinkList(BiTree root)
{
    if(root) {
        if(!root->lchild && !root->rchild) { // 叶子节点
            globalPre->rchild = root;
            root->lchild = globalPre;
            globalPre = root;
        } else {
            linkLeaf2DoubleLinkList(root->lchild);
            linkLeaf2DoubleLinkList(root->rchild);
        }
    }
}

float calOp(char type, float x, float y)
{
    switch(type){
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    default:
        break;
    }
}

// 后序遍历(左子树求值,右子树求值，根求值)表达式求值
float expressionCalculate(BiTree root)
{
    if(!root->lchild && !root->rchild) {
        return root->data - '0';
    } else {
        float leftResult = expressionCalculate(root->lchild);
        float rightResult = expressionCalculate(root->rchild);
        return calOp(root->data, leftResult, rightResult);
    }
}

// 判断是否完全二叉树(实节点之前不能有空节点== 出现空节点之后都是空节点)
int isCompleteTree(BiTree root)
{
    queue<BiTreeNode*> treeQueue;
    if(root) treeQueue.push(root);
    int flag = 0;
    while(!treeQueue.empty()) {
        BiTreeNode* t = treeQueue.front();
        treeQueue.pop();
        if(!t) break;
        treeQueue.push(t->lchild);
        treeQueue.push(t->rchild);
    }
    while(!treeQueue.empty()) {
        BiTreeNode* t = treeQueue.front();
        treeQueue.pop();
        if(t) return 0;
    }
    return 1;
}

// 获取树最大宽度
int getMaxWidth(BiTree T)
{
    queue<BiTreeNode*>treeQueue;
    if(T) {
        treeQueue.push(T);
    } else {
       return 0;
    }
    BiTreeNode* last = T;
    int layerWidth = 0, maxWidth = 1;
    while(!treeQueue.empty()) {
        BiTreeNode* t = treeQueue.front();
        treeQueue.pop();
        layerWidth++;

        if(t->lchild) treeQueue.push(t->lchild);
        if(t->rchild) treeQueue.push(t->rchild);

        if(t == last) { // 当前层已经全部出来，队列里全是下一层的
            last = treeQueue.back();
            maxWidth = maxWidth > layerWidth ? maxWidth : layerWidth;
            layerWidth = 0;
        }
    }
    return maxWidth;
}

void bstCreate(BSTree &T, int data[], int n)
{
    for(int i=0; i < n; i++) {
        bsTreeCreateInsert(T, data[i]);
    }
    inTraverse(T);
    printf("\n");
}

// 创建一棵二叉排序树
int bsTreeCreateInsert(BSTree &T, int data)
{
    if(!T) {
        T = (BSTNode*)malloc(sizeof(BSTNode));
        T->data = data;
        T->lchild = NULL;
        T->rchild = NULL;
        return 0;
    } else {
        if(data < T -> data) {
            return bsTreeCreateInsert(T->lchild, data);
        } else if(data > T->data) {
            return bsTreeCreateInsert(T->rchild, data);
        } else {
            return -1; // 出现相等节点插入失败
        }
    }
}

// 删除BST的某个节点
int bstDelete(BSTree &T, int data)
{
    if(T) {
        if(data > T->data) {
            bstDelete(T->rchild, data);
        } else if(data < T->data) {
            bstDelete(T->lchild, data);
        } else {
            // 叶子节点 单叶子节点 双叶子节点
            if(!T->lchild && !T->rchild) {
                free(T);
                T = NULL;
            } else if(T->lchild) { // else 不可能同时左右孩子都是NULL
                BSTNode* t = T;
                T = T->lchild;
                free(t);
            } else if(T->rchild) {
                BSTNode* t = T;
                T = T->rchild;
                free(t);
            } else {
                BSTNode* p = T->lchild;
                while(p->rchild != NULL) p = p->rchild;

                // 另外一种删除方式，不用进行交换，直接将左子树作为根节点
                // 右子树接到 左子树最右边节点的右边
                /*
                    p->rchild = T->rchild;
                    BSTNode* t = T;
                    T = T->lchild; // 左子树作为根节点
                    free(t);
                */
                p->data = p->data ^ T->data;
                T->data = p->data ^ T->data;
                p->data = p->data ^ T->data;
                bstDelete(T->lchild, p->data);
            }
        }
    }
}
// 求节点 x 所在层数
int getXlevel(BSTree T, int x, int depth)
{
    if(T) {
        if(T->data == x) {
            return depth;
        } else if(x < T->data) {
            return getXlevel(T->lchild, x, depth+1);
        } else {
            return getXlevel(T->rchild, x, depth+1);
        }
    }
    return -1;
}

// 查找二叉树中所有小于key的关键字

// 计算查找成功的ASL(不会将NULL节点计算进比较节点)

// BST插入，只用插入根节点
void insertSubTree(BSTree &root, BSTree sub)
{
    if(root) {
        if(sub->data < root->data) {
            insertSubTree(root->lchild, sub);
        } else if(sub->data > root->data) {
            insertSubTree(root->rchild, sub);
        }
    } else {
        root = sub;
    }
}

// 二叉排序树分解成两棵树
void splitBST(int key, BSTree &T, BSTree &T1, BSTree &T2)
{
    if(T) {
        if( key == T->data) {
            insertSubTree(T1, T1->lchild);
            insertSubTree(T2, T2->rchild);
            free(T);
            T = NULL;
        } else if(key < T->data) {
            BSTNode* lchild = T-> lchild;
            T->lchild = NULL;
            insertSubTree(T2, T);
            splitBST(key, lchild, T1, T2);
        } else { // key > T-> data
            BSTNode* rchild = T->rchild;
            T->rchild = NULL;
            insertSubTree(T1, T);
            splitBST(key, rchild, T1, T2);
        }
    }
}


