#include "Graph.h"


void graphDemo() {
    printf("This is graph demo\n");
    // Ĭ�ϻ���ǰֵ������ + 1
    enum { Mon = 1, Tue, Wed=100, Thu, Fri };
    createMGraph();
}

// �����ڽӾ���洢��ͼ
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

