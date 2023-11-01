#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

typedef  char ElemType;

typedef struct BiTreeNode {
    ElemType data;
    struct BiTreeNode* lchild, *rchild;
}BiTreeNode, *BiTree;

typedef struct BSTNode {
    int data;
    BSTNode* lchild;
    BSTNode* rchild;
}BSTNode, *BSTree;

typedef struct BiThreadTreeNode {
    ElemType data;
    int ltag;
    int rtag;
    BiThreadTreeNode* lchild;
    BiThreadTreeNode* rchild;
}BiThreadTreeNode, *BiThreadTree;


void treeDemo();

void preTraverse(BiTree root);
BiTree createTreePreAndIn(ElemType preOrderList[], int preStartIndex, int preEndIndex,
                        ElemType inOrderList[], int inStartIndex, int inEndIndex);
void inTraverse(BiTree root);
void inTraverse(BSTree T);
BiTree createTreeLevelAndIn(ElemType levelOrderList[], int levelStartIndex, int levelEndIndex,
                            ElemType inOrderList[], int inStartIndex, int inEndIndex);
int getTreeNode(BiTree root);
int isBalanceTree(BiTree root, int& balance);
int getLeafNum(BiTree root);
int getOneDegreeNum(BiTree root);
BiTreeNode* getXNode(BiTree root, ElemType x);
void getXNodeRef(BiTree root, ElemType x, BiTreeNode* & node);
int getHeight(BiTree root);
void getXnodeHeightRef(BiTree root, ElemType x, int& xHeight);
int getXnodeHeight(BiTree root, ElemType x);
void exchangeTree(BiTree root);
void linkLeafNode(BiTreeNode*& pre, BiTree root);
void linkLeaf2DoubleLinkList(BiTree root);
float expressionCalculate(BiTree root);
int isCompleteTree(BiTree root);
int getMaxWidth(BiTree T);
int bsTreeCreateInsert(BSTree &T, int data);
void bstCreate(BSTree &T, int data[], int n);
int bstDelete(BSTree &T, int data);
int getXlevel(BSTree T, int x, int depth);
void insertSubTree(BSTree &root, BSTree sub);
void splitBST(int key, BSTree &T, BSTree &T1, BSTree &T2);
void freeTree(BSTree&T);
void removeLowerThanK(BSTree &T, int k);
void findAllLowerThanK(BSTree T, int k);
void getBiggerThanValue(BSTree T, int value, int &preValue);

void getBiggerThanValueGlobal(BSTree T, int value);


BiThreadTree createTreePreAndInThread(ElemType preOrderList[], int preStartIndex, int preEndIndex,
                        ElemType inOrderList[], int inStartIndex, int inEndIndex);

void preOrderThreading(BiThreadTree T, BiThreadTreeNode *&pre);
void createPreThreading(BiThreadTree T);
void preOrderThreadTraversing(BiThreadTree T);
void preTraverseThread(BiThreadTree T);

void inTraverseThread(BiThreadTree T);
void inOrderThreading(BiThreadTree T, BiThreadTreeNode *&pre);
void createInThreading(BiThreadTree T);
BiThreadTreeNode* getFirstNodeIn(BiThreadTree T);
BiThreadTreeNode* getNext(BiThreadTreeNode* pCurrent);
void inOrderThreadTraversing(BiThreadTree T);

#endif // TREE_H_INCLUDED
