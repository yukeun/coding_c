#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int K = 0;
int W = 0;
int H = 0;
int visited[210][210][31];
int map[210][210];

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
struct QUE que[100 * 100 * 100 * 10];
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
    scanf("%d", &K);
    scanf("%d", &W);
    scanf("%d", &H);
    for (int h = 1; h <= H; h++) {
        for (int w = 1; w <= W; w++) {
            scanf("%d", &map[h][w]);
        }
    }
}

int BFS(void) {
    memset(visited, 0, sizeof(visited));
    wp = rp = 0;
    push(0, 1, 1, 0);
    visited[1][1][0] = 1;
    while (!empty()) {
        struct QUE cur = deque();

        for (int i = 0; i < 12; i++) {
            if (i >= 4) {
                int horse_h = cur.h + hh[i - 4];
                int horse_w = cur.w + hw[i - 4];
                if (cur.h_cnt < K && horse_h >= 1 && horse_h <= H && horse_w >= 1 && horse_w <= W) {
                    if (horse_h == H && horse_w == W) return cur.cnt + 1;
                    if (map[horse_h][horse_w] == 0 && visited[horse_h][horse_w][cur.h_cnt + 1] == 0) {
                        push(cur.h_cnt + 1, horse_h, horse_w, cur.cnt + 1);
                        visited[horse_h][horse_w][cur.h_cnt + 1] = 1;
                    }
                }
            } 
            else {
                int next_h = cur.h + dh[i];
                int next_w = cur.w + dw[i];
                if (next_h >= 1 && next_h <= H && next_w >= 1 && next_w <= W) {
                    if (next_h == H && next_w == W) return cur.cnt + 1;
                    if (map[next_h][next_w] == 1) continue;
                    if (map[next_h][next_w] == 0 && visited[next_h][next_w][cur.h_cnt] == 0) {
                        push(cur.h_cnt, next_h, next_w, cur.cnt + 1);
                        visited[next_h][next_w][cur.h_cnt] = 1;
                    }
                }
            }
        }
    }
    if(W == 1 && H == 1) return 0;
    else return -1;
}

int main(void) {
    InputData();
    int result = BFS();
    printf("%d\n", result);
    return 0;
}
