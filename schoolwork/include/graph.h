#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100 
#define INFINITY_INT 65535

typedef char VertexType;
typedef int EdgeType;

/* ==============================================
   1. 邻接矩阵 (Adjacency Matrix) 结构定义
   ============================================== */
typedef struct {
    VertexType vexs[MAX_VEX];      // 顶点表
    EdgeType arc[MAX_VEX][MAX_VEX];// 邻接矩阵，可看作边表
    int numVertexes, numEdges;     // 图中当前的顶点数和边数
} MGraph;

/* ==============================================
   2. 邻接表 (Adjacency List) 结构定义
   ============================================== */
// 边表结点
typedef struct EdgeNode {
    int adjvex;              // 邻接点域，存储该顶点对应的下标
    EdgeType weight;         // 用于存储权值，对于非网图可以不需要
    struct EdgeNode *next;   // 链域，指向下一个邻接点
} EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    VertexType data;         // 顶点域，存储顶点信息
    EdgeNode *firstedge;     // 边表头指针
} VertexNode, AdjList[MAX_VEX];

// 邻接表图结构
typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
} ALGraph;

/* ==============================================
   函数声明 (核心算法：创建图)
   ============================================== */

// 创建无向网图（使用邻接矩阵）
void CreateMGraph(MGraph *G);

// 创建无向网图（使用邻接表）
void CreateALGraph(ALGraph *G);

#endif