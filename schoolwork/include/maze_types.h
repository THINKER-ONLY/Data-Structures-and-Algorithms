#ifndef MAZE_TYPES_H
#define MAZE_TYPES_H

// 在这里定义迷宫问题专属的 Pos 结构体
typedef struct {
    int x;
    int y;
    int dir;
} Pos;

// 在这里将我们本次应用所需的元素类型 ElementType 定义为 Pos
typedef Pos ElementType;

#endif // MAZE_TYPES_H