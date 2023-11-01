#include "Graph.h"


void graphDemo() {
    printf("This is graph demo\n");
    // 默认会在前值基础上 + 1
    enum { Mon = 1, Tue, Wed=100, Thu, Fri };
    createMGraph();
}

// 创建邻接矩阵存储的图
void createMGraph() {
    MatrixGraph mg;

    FILE *fpVset = fopen("C:\\Users\\Leo\\Desktop\\NEU\\DS\\vSet.txt", "r");
    int vertexNum = 0;
    int vertexId;
    if(fpVset) {
        while(!feof(fpVset)) {
            fscanf(fpVset, "%d", &vertexId);
            mg.vertex[vertexId] = vertexId;
            vertexNum++;
        }
        mg.vertexNum = vertexNum;
        fclose(fpVset);
    }
    for( int i = 1; i <= mg.vertexNum; i++) {
        printf("%d ", mg.vertex[i]);
    }
}

