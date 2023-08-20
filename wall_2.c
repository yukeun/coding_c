#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1010

int H, W;
char map[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE][2];
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

typedef struct {
    int state;
    int h;
    int w;
    int cost;
} Point;

Point queue[MAX_SIZE * MAX_SIZE * 2];
int front, rear;

void push(int state, int h, int w, int cost) {
    queue[rear].state = state;
    queue[rear].h = h;
    queue[rear].w = w;
    queue[rear].cost = cost;
    rear++;
}

Point deque() {
    return queue[front++];
}

bool empty() {
    return front == rear;
}

void InputData() {
    scanf("%d %d", &H, &W);
    for (int h = 0; h < H; h++) {
        scanf("%s", map[h]);
    }
}

int BFS() {
    front = rear = 0;
    push(0, 0, 0, 1);
    visited[0][0][0] = 1;

    while (!empty()) {
        Point cur = deque();

        if (cur.h == H - 1 && cur.w == W - 1) {
            return cur.cost;
        }

        for (int i = 0; i < 4; i++) {
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];

            if (next_h >= 0 && next_h < H && next_w >= 0 && next_w < W) {
                if (cur.state == 0) {
                    if (map[next_h][next_w] == '1' && !visited[next_h][next_w][1]) {
                        push(1, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w][1] = 1;
                    }
                    else if (map[next_h][next_w] == '0' && !visited[next_h][next_w][0]) {
                        push(0, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w][0] = 1;
                    }
                }
                else if (cur.state == 1) {
                    if (map[next_h][next_w] == '0' && !visited[next_h][next_w][1]) {
                        push(1, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w][1] = 1;
                    }
                }
            }
        }
    }

    return -1;
}

int main() {
    InputData();
    int result = BFS();
    printf("%d\n", result);

    return 0;
}
