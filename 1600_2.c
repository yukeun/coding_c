#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int K = 0;
int W = 0;
int H = 0;
int visited[200 + 10][200 + 10] = {0,};
int visited2[200 + 10][200 + 10][31] = {0, };  // 수정: visited2 배열에 K에 대한 차원 추가
int map[200 + 10][200 + 10] = {0,};

int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};
int hh[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int hw[] = {-2, -1, 1, 2, -2, -1, 1, 2};

struct QUE {
    int h_cnt;
    int h;
    int w;
    int cnt;
};

struct QUE que[100 * 100 * 100 * 10 + 10];
int wp, rp;

void push(int h_cnt, int h, int w, int cnt) {
    que[wp].h_cnt = h_cnt;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].cnt = cnt;
    wp++;
}

struct QUE deque(void) {
    return que[rp++];
}

int empty(void) {
    return wp == rp;
}

void InputData(void) {
    scanf(" %d", &K);
    scanf(" %d", &W);
    scanf(" %d", &H);
    for (int h = 1; h <= H; h++) {
        for (int w = 1; w <= W; w++) {
            scanf(" %d", &map[h][w]);
        }
    }
}

int BFS(void) {
    memset(visited, 0, sizeof(visited));
    memset(visited2, 0, sizeof(visited2));
    wp = rp = 0;
    push(0, 1, 1, 0);
    visited[1][1] = 1;
    while (!empty()) {
        struct QUE cur = deque();
        for (int i = 0; i < 8; i++) {  // 말처럼 이동하는 경우를 위해 8로 수정
            int next_h, next_w;
            if (i < 4) {
                next_h = cur.h + dh[i];
                next_w = cur.w + dw[i];
            } else {
                next_h = cur.h + hh[i];
                next_w = cur.w + hw[i];
            }
            // 말 이동횟수를 다 쓰지 않은 경우
            if (cur.h_cnt < K && next_h >= 1 && next_h <= H && next_w >= 1 && next_w <= W) {
                if (next_h == H && next_w == W) return cur.cnt + 1;
                if (map[next_h][next_w] == 0 && visited[next_h][next_w] == 0 && visited2[next_h][next_w][cur.h_cnt + 1] == 0) {
                    push(cur.h_cnt + 1, next_h, next_w, cur.cnt + 1);
                    visited2[next_h][next_w][cur.h_cnt + 1] = 1;
                }
            }
            if (next_h >= 1 && next_h <= H && next_w >= 1 && next_w <= W) {
                if (next_h == H && next_w == W) return cur.cnt + 1;
                if (map[next_h][next_w] == 1) continue;
                if (map[next_h][next_w] == 0 && visited[next_h][next_w] == 0 && visited2[next_h][next_w][cur.h_cnt] == 0) {
                    push(cur.h_cnt, next_h, next_w, cur.cnt + 1);
                    visited[next_h][next_w] = 1;
                    visited2[next_h][next_w][cur.h_cnt] = 1;
                }
            }
        }
    }
    return -1;
}

int main(void) {
    InputData();
    int result = BFS();
    printf("%d\n", result);
    return 0;
}
