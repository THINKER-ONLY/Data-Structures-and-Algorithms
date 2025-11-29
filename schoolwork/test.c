#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. 二叉树基础结构 ---
// (来自 btree.cpp 或 btree.h 的基础定义)
typedef char TElemType;

typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// --- 2. 辅助队列结构 (用于层序遍历) ---
#define MAX_QUEUE_SIZE 50
typedef struct {
    BiTree data[MAX_QUEUE_SIZE]; // 队列，存放指向树节点的指针
    int front;
    int rear;
} Queue;

void InitQueue(Queue *q) {
    q->front = q->rear = 0;
}

int IsEmpty(Queue q) {
    return q.front == q.rear;
}

void Enqueue(Queue *q, BiTree node) {
    // 假设队列空间足够
    q->data[q->rear] = node;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
}

BiTree Dequeue(Queue *q) {
    BiTree node = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return node;
}

// --- 3. 核心算法：重建二叉树 ---

/**
 * 辅助函数：在中序序列中查找根节点的位置
 */
int findInOrderIndex(char in[], int in_start, int in_end, char root_val) {
    for (int i = in_start; i <= in_end; i++) {
        if (in[i] == root_val) {
            return i;
        }
    }
    return -1; // 未找到
}

/**
 * 递归函数：根据后序和中序序列构建二叉树
 * post: 后序遍历数组
 * in:   中序遍历数组
 * [post_start, post_end]: 当前处理的后序序列范围
 * [in_start, in_end]:   当前处理的中序序列范围
 */
BiTree BuildTreeFromPostIn(char post[], char in[], 
                           int post_start, int post_end, 
                           int in_start, int in_end) {
    // 1. 基本情况（空树）
    if (post_start > post_end || in_start > in_end) {
        return NULL;
    }

    // 2. 后序序列的最后一个元素是根
    char root_val = post[post_end];
    BiTree root = (BiTree)malloc(sizeof(BiTNode));
    root->data = root_val;

    // 3. 在中序序列中找到根的位置
    int in_root_index = findInOrderIndex(in, in_start, in_end, root_val);
    
    // 4. 计算左子树的节点数量
    int left_subtree_size = in_root_index - in_start;

    // 5. 递归构建左子树
    // 左子树的后序范围: [post_start, post_start + left_subtree_size - 1]
    // 左子树的中序范围: [in_start, in_root_index - 1]
    root->lchild = BuildTreeFromPostIn(
        post, in,
        post_start, post_start + left_subtree_size - 1,
        in_start, in_root_index - 1
    );

    // 6. 递归构建右子树
    // 右子树的后序范围: [post_start + left_subtree_size, post_end - 1]
    // 右子树的中序范围: [in_root_index + 1, in_end]
    root->rchild = BuildTreeFromPostIn(
        post, in,
        post_start + left_subtree_size, post_end - 1,
        in_root_index + 1, in_end
    );

    // 7. 返回创建的根节点
    return root;
}

// --- 4. 核心算法：层序遍历 ---
/**
 * 使用队列进行层序遍历（广度优先搜索）
 */
void LevelOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }

    Queue q;
    InitQueue(&q);
    Enqueue(&q, T); // 根节点入队

    while (!IsEmpty(q)) {
        BiTree current = Dequeue(&q); // 节点出队
        printf("%c", current->data);  // 访问（打印）节点数据

        // 如果有左孩子，左孩子入队
        if (current->lchild != NULL) {
            Enqueue(&q, current->lchild);
        }
        // 如果有右孩子，右孩子入队
        if (current->rchild != NULL) {
            Enqueue(&q, current->rchild);
        }
    }
}


// --- 5. 主函数 (用于测试) ---
int main() {
    // 已知序列
    char post[] = "GDBEFCA";
    char in[]   = "DGBAECF";
    int n = strlen(post);

    // 1. 通过后序和中序重建二叉树
    //    初始调用时，范围是整个数组 (0 到 n-1)
    BiTree T = BuildTreeFromPostIn(post, in, 0, n - 1, 0, n - 1);

    // 2. 输出层序遍历结果
    printf("二叉树的层序表示法为：");
    LevelOrderTraverse(T);
    printf("\n");

    // 可以在此处添加释放树内存的代码（非本题要求）
    // ...

    return 0;
}