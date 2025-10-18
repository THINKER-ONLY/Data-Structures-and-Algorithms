#include <stdio.h>
#include <stdlib.h>
#include "maze_types.h"
#include "sqstack.h"

#define TRUE 1
#define FALSE 0

#define MAZE_ROWS 10
#define MAZE_COLS 10

Status MazePath(int maze[MAZE_ROWS][MAZE_COLS], Pos start, Pos end, SqStack *S)
{
    Pos currentPos;
    SqStack_Push(S, start);
    maze[start.x][start.y] = 2;
    while (!SqStack_IsEmpty(S))
    {
        SqStack_GetTop(S, &currentPos);
        if (currentPos.x == end.x && currentPos.y == end.y) return OK;
        int next_x, next_y;
        int find_next_step = FALSE;
        for (int direction=currentPos.dir + 1; direction<4; direction++)
        {
            S->base[S->top-1].dir = direction;
            if (direction == 0) { next_x = currentPos.x; next_y = currentPos.y + 1; }
            else if (direction == 1) { next_x = currentPos.x + 1; next_y = currentPos.y; }
            else if (direction == 2) { next_x = currentPos.x; next_y = currentPos.y - 1; }
            else { next_x = currentPos.x - 1; next_y = currentPos.y; }
            if (maze[next_x][next_y] == 0)
            {
                Pos nextPos = {next_x, next_y, -1};
                SqStack_Push(S, nextPos);
                maze[next_x][next_y] = 2;
                find_next_step = TRUE;
                break;
            }
        }
        if (!find_next_step) SqStack_Pop(S, &currentPos);
    }
    return ERROR;
}

void PrintPath(const SqStack S)
{
    printf("\nPath found as follows (total %d steps):\n", S.top);
    for(int i=0; i<S.top; i++)
    {
        printf("(%d,%d) ", S.base[i].x, S.base[i].y);
    }
    printf("\n");
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
    
    Pos start = {1, 1, -1};
    Pos end = {8, 8, -1};

    SqStack pathStack;
    SqStack_Init(&pathStack);

    printf("Starting to solve the maze...\n");

    if (MazePath(maze, start, end, &pathStack) == OK) {
        PrintPath(pathStack);
    } else {
        printf("No path found from entrance to exit.\n");
    }

    SqStack_Destroy(&pathStack);
    
    return 0;
}