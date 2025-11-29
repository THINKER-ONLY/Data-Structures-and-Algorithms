/*
 * bitree.c
 *
 * 实现 bitree.h 中声明的二叉树操作。
 */

#include "bitree.h" // 包含我们自己的头文件

// --- 2. 核心算法 (函数实现) ---

/**
 * 访问节点（辅助函数）
 * 简单地打印节点的数据
 */
void Visit(TElemType data) {
    printf("%c ", data);
}

/**
 * 按前序遍历的顺序创建二叉树。
 */
void CreateBiTree(BiTree *T) {
    TElemType ch;
    
    // 使用 " %c" 来读取字符，前面的空格可以跳过任何空白符（如换行符）
    if (scanf(" %c", &ch) != 1) { 
        *T = NULL;
        return;
    }

    if (ch == '#') {
        *T = NULL; // 空节点
    } else {
        // 创建根节点
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (*T == NULL) {
            fprintf(stderr, "内存分配失败！\n");
            exit(1); // 退出程序
        }
        (*T)->data = ch; // 设置数据
        
        // 递归创建左子树
        CreateBiTree(&(*T)->lchild);
        
        // 递归创建右子树
        CreateBiTree(&(*T)->rchild);
    }
}

/**
 * 3.1 前序遍历 (DLR) (函数实现)
 */
void PreOrderTraverse(BiTree T) {
    if (T) {
        Visit(T->data);              // 访问根节点
        PreOrderTraverse(T->lchild); // 递归遍历左子树
        PreOrderTraverse(T->rchild); // 递归遍历右子树
    }
}

/**
 * 3.2 中序遍历 (LDR) (函数实现)
 */
void InOrderTraverse(BiTree T) {
    if (T) {
        InOrderTraverse(T->lchild); // 递归遍历左子树
        Visit(T->data);             // 访问根节点
        InOrderTraverse(T->rchild); // 递归遍历右子树
    }
}

/**
 * 3.3 后序遍历 (LRD) (函数实现)
 */
void PostOrderTraverse(BiTree T) {
    if (T) {
        PostOrderTraverse(T->lchild); // 递归遍历左子树
        PostOrderTraverse(T->rchild); // 递归遍历右子树
        Visit(T->data);               // 访问根节点
    }
}


/**
 * 主函数 - 用于测试
 */
int main() {
    BiTree T = NULL; // 初始化一个空树

    printf("请按前序遍历顺序输入二叉树（#表示空节点，例如: A B D # # E # # C # F # #）：\n");
    
    // 调用本文件中实现的函数
    CreateBiTree(&T);

    printf("\n--- 遍历结果 ---\n");

    printf("前序遍历: ");
    PreOrderTraverse(T);
    printf("\n");

    printf("中序遍历: ");
    InOrderTraverse(T);
    printf("\n");

    printf("后序遍历: ");
    PostOrderTraverse(T);
    printf("\n");

    // 可以在这里添加释放树内存的函数
    // ...

    return 0;
}