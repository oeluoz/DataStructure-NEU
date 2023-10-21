#include <stdio.h>
#include "Tree.h"
#include <stack>
using std::stack;

int main(int argc, char const *argv[])
{
    
    return 0;
}
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