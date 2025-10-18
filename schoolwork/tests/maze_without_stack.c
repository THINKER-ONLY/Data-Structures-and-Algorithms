#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAZE_ROWS 10
#define MAZE_COLS 10

typedef int Status;

typedef struct {
    int x;   
    int y;  
} Pos;

int findPath(int maze[MAZE_ROWS][MAZE_COLS], Pos currentPos,Pos end, Pos path[], int step)
{
    if (currentPos.x < 0 || currentPos.x >= MAZE_ROWS ||
        currentPos.y < 0 || currentPos.y >= MAZE_COLS ||
        maze[currentPos.x][currentPos.y] != 0)
    {
        return FALSE;
    }
    
    path[step] = currentPos;
    maze[currentPos.x][currentPos.y] = 2; 

    if (currentPos.x == end.x && currentPos.y == end.y) return TRUE;

    if (findPath((maze, (Pos){currentPos.x, currentPos.y + 1}, end, path, step + 1)) return TRUE;
    
    // b. 尝试向南
    if (findPath((maze, (Pos){currentPos.x + 1, currentPos.y}, end, path, step + 1)) return TRUE;
    
    // c. 尝试向西
    if (findPath((maze, (Pos){currentPos.x, currentPos.y - 1}, end, path, step + 1)) return TRUE;
    
    // d. 尝试向北
    if (findPath((maze, (Pos){currentPos.x - 1, currentPos.y}, end, path, step + 1)) return TRUE;

    maze[currentPos.x][currentPos.y] = 0; 
    return FALSE;
}

int main() 
{
    int maze[MAZE_ROWS][MAZE_COLS] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,0,1,0,1},
        {1,0,0,1,0,0,0,1,0,1},
        {1,0,0,0,0,1,1,0,0,1},
        {1,0,1,1,1,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,1},
        {1,0,1,1,1,0,1,1,0,1},
        {1,1,1,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    
    Pos start = {1, 1};
    Pos end = {8, 8};

    Pos foundPath[MAZE_ROWS * MAZE_COLS];

    printf("开始使用递归求解迷宫...\n");

    if (findPath(maze, start, end, foundPath, 0)) {
        printf("找到的路径如下:\n");

        for(int i = 0; i < MAZE_ROWS * MAZE_COLS; ++i) {
            printf("(%d,%d) ", foundPath[i].x, foundPath[i].y);
            if (foundPath[i].x == end.x && foundPath[i].y == end.y) {
                break;
            }
        }
        printf("\n");
    } else {
        printf("未找到从入口到出口的路径。\n");
    }

    return 0;
}