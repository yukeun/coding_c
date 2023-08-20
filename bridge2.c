#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100

int board[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1 , 0, -1, 0 };

int n;
int minBridge = INT_MAX;
int flag = 1;

// DFS를 사용하여 섬들을 구분하는 함수
void dfs(int x, int y) {
    visited[x][y] = true;
    board[x][y] = flag;

    int dir;
    for (dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 배열 범위를 벗어나는 경우 건너뜀
        if (nx < 0 || ny < 0 || nx >= n || ny >= n)
            continue;

        // 주변에 섬이 있고 방문하지 않은 경우 재귀 호출
        if (board[nx][ny] == 1 && !visited[nx][ny]) {
            dfs(nx, ny);
        }
    }
}

// BFS를 사용하여 최단 다리 길이를 구하는 함수
void bfs(int start) {
    int queue[MAX_SIZE * MAX_SIZE][2];
    int front = 0, rear = 0;

    // 시작 섬을 큐에 넣고 방문 표시
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == start) {
                queue[rear][0] = i;
                queue[rear][1] = j;
                rear++;
                visited[i][j] = true;
            }
        }
    }

    int dist = 0;
    while (front != rear) {
        int size = rear - front;
        while (size--) {
            int curX = queue[front][0];
            int curY = queue[front][1];
            front++;

            int dir;
            for (dir = 0; dir < 4; dir++) {
                int nx = curX + dx[dir];
                int ny = curY + dy[dir];

                // 배열 범위를 벗어나는 경우 건너뜀
                if (nx < 0 || ny < 0 || nx >= n || ny >= n)
                    continue;

                // 다른 섬에 도착한 경우 최소 다리 길이를 업데이트하고 종료
                if (board[nx][ny] && board[nx][ny] != start) {
                    minBridge = (minBridge > dist) ? dist : minBridge;
                    return;
                }

                // 바다인 경우 큐에 넣고 방문 표시
                if (board[nx][ny] == 0 && !visited[nx][ny]) {
                    queue[rear][0] = nx;
                    queue[rear][1] = ny;
                    rear++;
                    visited[nx][ny] = true;
                }
            }
        }
        dist++;
    }
}

int main(void) {
    scanf("%d", &n);

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &board[i][j]);
        }
    }

    // 섬들을 구분하는 DFS 호출
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == 1 && !visited[i][j]) {
                dfs(i, j);
                flag++;
            }
        }
    }

    // 각 섬에서 BFS 호출하여 최단 다리 길이를 구함
    for (i = 1; i < flag; i++) {
        // visited 배열 초기화
        for (j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                visited[j][k] = false;
            }
        }
        bfs(i);
    }

    printf("%d\n", minBridge);

    return 0;
}
