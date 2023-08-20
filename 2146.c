/*
10
1 1 1 0 0 0 0 1 1 1
1 1 1 1 0 0 0 0 1 1
1 0 1 1 0 0 0 0 1 1
0 0 1 1 1 0 0 0 0 1
0 0 0 1 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 0 0 0 0
0 0 0 0 1 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 102

int N;
int map1[MAXN][MAXN] = {0,};
int map2[MAXN][MAXN] = {0,};            // 대륙을 구분하는
int visited[MAXN][MAXN] = {0,};
int dh[] = {-1, 1, 0 , 0};
int dw[] = {0 , 0, -1, 1};
int min_distance = 10010;

void inputdata(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf(" %d", &map1[i][j]);
        }
    }
}
void print_map(void){
    for(int i = 0; i < N ; i++){
        for(int j = 0; j < N; j++){
            printf("%d", map1[i][j]);
        }
        printf("\n");
    }
}

struct QUE{
    int h;
    int w;
    int from;
    int cnt;
};
struct QUE que[100 * 100 * 100 * 10];
int wp, rp;

void push(int h, int w, int from, int cnt){
    que[wp].h = h;
    que[wp].w = w;
    que[wp].from = from;
    que[wp].cnt = cnt;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}

void BFS1(int i, int j, int from){
    wp = rp = 0;
    push(i, j, from, 0);
    map2[i][j] = from;
    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];

            // 사방탐색
            if(next_h >= 0 && next_h < N && next_w >= 0 && next_w < N){
                if(map1[next_h][next_w] == 0 && map1[cur.h][cur.w] == 1){
                    map1[cur.h][cur.w] = 7;
                }
                if(map1[next_h][next_w] == 0 || map2[next_h][next_w] != 0) continue;
                if(map1[next_h][next_w] == 1 && map2[next_h][next_w] == 0){
                    map2[next_h][next_w] = cur.from;
                    push(next_h, next_w, cur.from, 0);
                }
                // 테두리 부분 표시하기(바다랑 인접한 육지를 표시하기)
            }
        }
    }
}

void BFS2(void){
    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];
            if(next_h >= 0 && next_h < N && next_w >= 0 && next_w < N){
                if(map2[next_h][next_w] != 0 && map2[next_h][next_w] != cur.from){
                    if(min_distance > cur.cnt) min_distance = cur.cnt;
                    visited[next_h][next_w] = 1;
                    continue;
                }
                if(map2[next_h][next_w] != 0 && map2[next_h][next_w] == cur.from) continue;
                if(map2[next_h][next_w] == 0 && visited[next_h][next_w] == 0){
                    visited[next_h][next_w] = 1;
                    push(next_h, next_w, cur.from, cur.cnt + 1);
                }
            }
        }
    }
}

void searching(void){
    int start_num = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if (map1[i][j] == 1 && map2[i][j] == 0){
                BFS1(i, j, start_num);
                start_num++;
            }
        }
    }
    for(int k = 1; k < start_num; k++){
        // 대륙별로 다리 건설 시작하기
        memset(visited, 0, sizeof(visited));
        wp = rp = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if (map2[i][j] == k && map1[i][j] == 7){
                    push(i, j ,k, 0);
                    visited[i][j] = 1;
                }
            }
        }
        BFS2();
    }
}



int main(void){
    inputdata();
    searching();
    printf("%d\n", min_distance);
    return 0;
}