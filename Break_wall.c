#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int H = 0;
int W = 0;
char map[1000 + 10][1000 + 10] = {0,};
int map2[1000 + 10][1000 + 10] = {0, };
int visited[1000 + 10][1000 + 10] = {0,};
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

struct QUE{
    int state;              // 벽을 부쉈는지 안 부쉈는지
    int h;
    int w;
    long long cost;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

void push(int state, int h, int w, long long cost){
    que[wp].state = state;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].cost = cost;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}

void InputData(void){
    scanf(" %d", &H);
    scanf(" %d", &W);
    for(int h = 1; h <= H; h++){
        for(int w =1; w <= W; w++){
            scanf(" %c", &map[h][w]);
        }
    }
    for(int h =1; h <= H; h++){
        for(int w = 1; w <= W; w++){
            map2[h][w] = (map[h][w] - '0');
        }
    }
    printf("\n");
    for(int i = 1; i <= H; i++){
        for(int j = 1; j <= W; j++){
            printf("%d", map2[i][j]);
        }
        printf("\n");
    }
}

long long BFS(void){
    memset(visited, 0, sizeof(visited));
    wp = rp = 0;
    push(0,1,1,1);
    visited[1][1] = 1;

    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];

            if(next_h >= 1 && next_h <= H && next_w >= 1 && next_w <= W){
                if(visited[next_h][next_w] == 1) continue;
                if(next_h == H && next_w == W){
                    return cur.cost + 1;
                }
                if (cur.state == 0){
                    if(map2[next_h][next_w] == 1){
                        push(1, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w] = 1;
                    }
                    else if (map2[next_h][next_w] == 0){
                        push(0, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w] = 1;
                    }
                }
                else if(cur.state == 1){
                    if (map2[next_h][next_w] == 1) continue;
                    else{
                        push(1, next_h, next_w, cur.cost + 1);
                        visited[next_h][next_w] = 1;
                    }
                }
            }
        }
    }
    return -1;
}



int main(void){
    InputData();
    long long result = BFS();
    printf("%lld\n", result);
    return 0;
}