#include "graph.h"

/* * 算法实现1: 创建邻接矩阵图
 * 思路：
 * 1. 输入顶点数和边数。
 * 2. 初始化顶点表。
 * 3. 初始化矩阵（对角线为0，其余为无穷大）。
 * 4. 循环输入每条边的两个顶点及权值，修改矩阵对应位置。
 */
void CreateMGraph(MGraph *G) {
    int i, j, k, w;
    
    printf("--- 开始创建邻接矩阵图 ---\n");
    printf("请输入顶点数和边数 (空格分隔): ");
    scanf("%d %d", &G->numVertexes, &G->numEdges);
    // 吸收可能存在的换行符，防止影响后续字符输入
    getchar(); 

    // 1. 建立顶点表
    for(i = 0; i < G->numVertexes; i++) {
        printf("请输入第%d个顶点的值: ", i + 1);
        scanf("%c", &G->vexs[i]);
        getchar(); // 吃掉回车
    }

    // 2. 初始化邻接矩阵
    for(i = 0; i < G->numVertexes; i++) {
        for(j = 0; j < G->numVertexes; j++) {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = INFINITY_INT;
        }
    }

    // 3. 建立边表
    for(k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi, vj)的下标i, 下标j 和 权值w (空格分隔): ");
        scanf("%d %d %d", &i, &j, &w);

        // 注意：这里假设用户输入的是数组下标。
        // 如果用户输入的是顶点字符，需要增加一个LocateVex函数来查找下标。
        
        G->arc[i][j] = w;
        G->arc[j][i] = w; // 因为是无向图，矩阵是对称的
    }
    printf("邻接矩阵图创建成功！\n\n");
}

/* * 算法实现2: 创建邻接表图
 * 思路：
 * 1. 输入顶点数和边数。
 * 2. 初始化顶点表，将所有 firstedge 置空。
 * 3. 循环输入边，使用头插法建立链表。
 */
void CreateALGraph(ALGraph *G) {
    int i, j, k;
    int w;
    EdgeNode *e;

    printf("--- 开始创建邻接表图 ---\n");
    printf("请输入顶点数和边数 (空格分隔): ");
    scanf("%d %d", &G->numVertexes, &G->numEdges);
    getchar();

    // 1. 建立顶点表
    for(i = 0; i < G->numVertexes; i++) {
        printf("请输入第%d个顶点的值: ", i + 1);
        scanf("%c", &G->adjList[i].data);
        G->adjList[i].firstedge = NULL; // 初始化为空链表
        getchar(); // 吃掉回车
    }

    // 2. 建立边表 (头插法)
    for(k = 0; k < G->numEdges; k++) {
        printf("请输入边(vi, vj)的下标i, 下标j 和 权值w (空格分隔): ");
        scanf("%d %d %d", &i, &j, &w);

        // 生成一个新的边结点 e
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = j;     // 邻接点是 j
        e->weight = w;
        e->next = G->adjList[i].firstedge; // 将 e 指向当前顶点 i 的头结点
        G->adjList[i].firstedge = e;       // 将顶点 i 的头结点指向 e (头插法完成)

        // 因为是无向图，还需要生成一个结点由 j 指向 i
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex = i;     // 邻接点是 i
        e->weight = w;
        e->next = G->adjList[j].firstedge;
        G->adjList[j].firstedge = e;
    }
    printf("邻接表图创建成功！\n\n");
}