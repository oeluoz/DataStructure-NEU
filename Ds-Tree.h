#ifndef DS_TREE_H
#define DS_TREE_H
#include "Tree.h"

void getReverseLayer(BiTree T);
int getHeightNoneRe(BiTree T);
int getDoubleDegree(BiTree T);
char preTraverseK(BiTree T, int &current, int k);
void kthNode(BiTree T, int k);
int getXParant(BiTree T, char x);
void postTraverseNoneRe(BiTree T);
#endif