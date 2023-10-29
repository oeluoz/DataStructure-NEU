#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
#include <stack>
#include <queue>
#include <vector>

using std::stack;
using std::queue;
using std::vector;

int getLeastSameParent(int T[], int i, int j) {
    while (i!=j) {
        if(i>j) {
            i/=2;
        } else {
            j/=2;
        }
    }
    printf("parent node: %d \n", T[i]);
}
// 后序遍历二叉树非递归算法
void postTraverseNoneRe(BiTree T) {
    // 左子树 右子树 根节点
    stack<BiTreeNode*> stk;
    BiTreeNode* pTop = T;
    BiTreeNode* r = NULL;
    while(!stk.empty() || pTop) {
        if(pTop) { // 当前节点是非空节点
            stk.push(pTop);
            pTop = pTop->lchild;
        } else {
            pTop = stk.top();
            // 第一次回到根节点
            if(pTop->rchild && pTop->rchild != r) {
                pTop = pTop->rchild;
            } else {
                // 第二次回到根节点
                stk.pop();
                printf("%d ", pTop->data);
                r = pTop;
                pTop = NULL; // 当前子树已经访问完
            }
        }
    }
}
// 二叉树从下到上，从右到左的层序遍历
void getReverseLayer(BiTree T) {
    queue<BiTreeNode*> tq;
    stack<BiTreeNode*> ts;
    tq.push(T);
    while (!tq.empty()) {
        BiTreeNode* t = tq.front();
        tq.pop();
        ts.push(t);
        if(t->lchild) {
            tq.push(t->lchild);
        }
        if(t->rchild) {
            tq.push(t->rchild);
        }
    }
    while(!ts.empty()) {
        BiTreeNode *t = ts.top();
        ts.pop();
        printf("%c ", t->data);
    }
    printf("\n");
}

// 非递归算法求二叉树的高度
int getHeightNoneRe(BiTree T) {
    // 层序遍历记录层数，后序遍历
    int treeHeight = 0;
    queue<BiTreeNode*> tq;
    if(!T) return 0;
    tq.push(T);
    BiTreeNode* layerLast = T;
    while(!tq.empty()) {
        BiTreeNode *t = tq.front();
        tq.pop();
        if(t->lchild) tq.push(t->lchild);
        if(t->rchild) tq.push(t->rchild);

        // 需要找到下一层第一个节点
        if(t == layerLast) {
            treeHeight++;
            layerLast = tq.back();
        }
    }
    return treeHeight;
}
// 计算双分支节点数量
int getDoubleDegree(BiTree T) {
    int cnt=0;
    queue<BiTreeNode*>tq;
    if(!T) return 0;
    tq.push(T);
    while(!tq.empty()) {
        BiTreeNode *t = tq.front();
        tq.pop();
        if(t->lchild && t->rchild) cnt++;
        if(t->lchild) tq.push(t->lchild);
        if(t->rchild) tq.push(t->rchild);
    }
    return cnt;
}
// 交换左右两棵子树
void exchangeSubTree(BiTree T) {
    if(T) {
        exchangeSubTree(T->lchild);
        exchangeSubTree(T->rchild);
        BiTreeNode *t = T->rchild;
        T->rchild = T->lchild;
        T->lchild = t;
    }
}

// 求先序遍历第 k 个节点
char preTraverseK(BiTree T, int &current, int k) {
    if(T) {
        if(current < k) {
            current++;
            char result = preTraverseK(T->lchild, current, k);
            if(result != '#') return result; // 不在左子树，结果一定在右子树
            return preTraverseK(T->rchild, current, k);
        } else {
            printf("%c ", T->data);
            return T->data;
        }
    }
    return '#';
}

// 第 k 个节点问题，统一返回值用void， 通过引用接收数据
// 这类问题会出现找到了结果由于原来进行了左右两个方向的遍历
// 出现重复访问和重复赋值的情况产生
void getKthNode(BiTree T, int k, int &index, int &result) {
    if(T) {
        if(index < k) {
            index++;
            getKthNode(T->lchild, k, index, result);
            if(index < k) {
                getKthNode(T->rchild, k, index, result);
            }
        } else {
            result = T->data;
        }
    }
}

void kthNode(BiTree T, int k) {
    int index = 1, result = -1;
    getKthNode(T, k, index, result);
    printf("kthNode %c \n", result);
}

// 删除 x 为根的子树
void deleteTree(BiTree &T) {
    if(T) {
        deleteTree(T->lchild);
        deleteTree(T->rchild);
        free(T);
        T = NULL;
    }
}
void findAndDelete(BiTree &T, char x) {
    if(T) {
        if(T->data == x) {
            deleteTree(T->lchild);
            deleteTree(T->rchild);
        } else {
            findAndDelete(T->lchild, x);
            findAndDelete(T->rchild, x);
        }
    }
}
// 二叉树中查找值为 x 的节点，打印 x 的所有祖先
int getXParant(BiTree T, char x) {
    // 后遍历非递归，栈中所有节点为其祖先
    stack<BiTreeNode*> ts;
    BiTreeNode* pTop = T;
    BiTreeNode* r = NULL;
    while (!ts.empty() || pTop) {
        if(pTop) {
            ts.push(pTop);
            pTop = pTop->lchild;
        } else { // 栈中弹出一个节点
            pTop = ts.top();
            if(pTop->rchild && pTop->rchild != r) { // 开始到右子树执行先序遍历
                pTop = pTop->rchild;
            } else {
                // 右子树回到根节点
                ts.pop();
                r = pTop;
                if(pTop->data == x) { //栈中存放的是其父节点
                    stack<char> tq;
                    while(!ts.empty()) {
                        tq.push(ts.top()->data);
                        ts.pop();
                    }
                    while(!tq.empty()) {
                        printf("%c ", tq.top());
                        tq.pop();
                    }
                    return 1;
                }
                pTop = NULL; // 继续向上回溯一层
            }
        }
    }
    return 0;
}
#define MAX_SIZE 100
// 寻找两个节点最近公共节点
BiTreeNode *getAncestor(BiTreeNode *T, BiTreeNode* p, BiTreeNode *q) {
    // 后续遍历找到节点，将所有的根节点保存下来
    BiTreeNode *pTop = T;
    BiTreeNode *r = NULL;
    stack<BiTreeNode*> stk;
    int pSize = 0, qSize = 0;
    BiTreeNode *pRoot[MAX_SIZE], *qRoot[MAX_SIZE];
    while(pTop || stk.empty()) {
        if(pTop) {
            stk.push(pTop);
            pTop = pTop->lchild;
        } else {
            pTop = stk.top();
            if(pTop->rchild && pTop->rchild != r) {
                pTop = pTop->rchild;
            } else {
                stk.pop();
                r = pTop;
                if(pTop->data == p->data) {
                    // 保存 p 的所有父节点
                    while(!stk.empty()) {
                        pRoot[pSize++] = stk.top();
                        stk.pop();
                    }
                    for(int i = pSize-1; i >= 0; i++) {
                        stk.push(pRoot[i]);
                    }
                }
                if(pTop->data == q->data) {
                    while(!stk.empty()) {
                        qRoot[qSize++] = stk.top();
                        stk.pop();
                        for(int i = qSize-1; i >= 0; i--) {
                            stk.push(qRoot[i]);
                        }
                    }
                }
                pTop = NULL;
            }
        }
    }
    // 进行匹配
    for(int i = 0; i < pSize; i++) {
        BiTreeNode* pPnode = pRoot[i];
        for(int j = 0; j < qSize; j++) {
            BiTreeNode *pQnode = qRoot[j];
            if(pPnode == pQnode) {
                return pPnode;
            }
        }
    }       
}