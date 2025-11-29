/*
 * bitree.h
 * * 定义二叉链表（BiTree）的结构和相关操作的声明。
 */

#ifndef BITREE_H
#define BITREE_H

#include <stdio.h>  // 包含标准输入输出
#include <stdlib.h> // 包含内存分配(malloc)和退出(exit)

// --- 1. 结构体定义 ---

typedef char TElemType;

/**
 * 二叉链表节点结构
 */
typedef struct BiTNode {
    TElemType data;                 // 数据域
    struct BiTNode *lchild, *rchild; // 左、右孩子指针
} BiTNode, *BiTree;


// --- 2. 核心算法 (函数声明/原型) ---

/**
 * 访问节点（辅助函数）
 * 在 bitree.c 中实现
 */
void Visit(TElemType data);

/**
 * 按前序遍历的顺序创建二叉树。
 * T 是一个指向 BiTree 的指针 (即 BiTNode**)。
 */
void CreateBiTree(BiTree *T);

/**
 * 3.1 前序遍历 (DLR)
 */
void PreOrderTraverse(BiTree T);

/**
 * 3.2 中序遍历 (LDR)
 */
void InOrderTraverse(BiTree T);

/**
 * 3.3 后序遍历 (LRD)
 */
void PostOrderTraverse(BiTree T);


#endif // BITREE_H