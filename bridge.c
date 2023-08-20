#include <stdio.h>
#include <string.h>
#define MAXN 100
#define INF (1<<30)
int N = 0;
int map[MAXN+10][MAXN+10] = {0,};
int visited[MAXN+10][MAXN+10] = {0,};
int visited2[MAXN+10][MAXN+10] = {0,};
int map2[MAXN+10][MAXN+10] = {0,};
int min_cost = INF;
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

큐 형식을 아래와 같은걸로 바꿔줘

struct QUE{
    int h;
    int w;
    int cost;
    int from;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

void push(int h, int w, int cost, int from){
    que[wp].h = h;
    que[wp].w = w;
    que[wp].cost = cost;
    que[wp].from = from;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}

void InputData(void){
    scanf(" %d", &N);
    for(int h = 0; h < N;h++){
        for(int w= 0; w < N; w++){
            scanf(" %d", &map[h][w]);
        }
    }
}

void BFS(int h, int w, int num){
    visited[h][w] = 1;
    map2[h][w] = num;
    wp = rp = 0;
    push(h, w, 0, 0);

    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];
            if(next_h >= 0 && next_h < N && next_w >=0 && next_w < N){
                if(map[next_h][next_w] == 1 && visited[next_h][next_w] == 0){
                    push(next_h, next_w, 0, 0);
                    visited[next_h][next_w] = 1;
                    map2[next_h][next_w] = num;
                }
                else if(map[next_h][next_w] == 0){
                    map[cur.h][cur.w] = 9;
                    visited[next_h][next_w] = 1;
                }
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
                if(map2[next_h][next_w] == cur.from && map2[cur.h][cur.w] != 0){               // 같은 대륙에 도착했을 경우
                    continue;
                }
                else if(map2[next_h][next_w] == cur.from && map2[cur.h][cur.w] == 0){
                    visited2[cur.h][cur.w] = 0;
                    continue;
                }
                if(map2[next_h][next_w] != 0 && map2[next_h][next_w] != cur.from){                      // 어차피 도착지점은 이미 visited처리됨
                    if(cur.cost < min_cost) min_cost = cur.cost;
                    continue;
                }
                if (map2[next_h][next_w] == 0 && visited2[next_h][next_w] == 0){
                    push(next_h,next_w, cur.cost + 1, cur.from);
                    visited2[next_h][next_w];
                }
            }
        }
    }
}

void Search_map(void){
    int num = 2;
    for(int h = 0; h < N; h++){
        for(int w = 0; w < N; w++){
            if (map[h][w] == 1 && visited[h][w] == 0){
                BFS(h,w,num);
                num++;
            }
        }
    }
    memset(visited, 0, sizeof(visited));
}

void Search_map2(void){
    wp = rp = 0;
    for(int h = 0; h < N; h++){
        for(int w = 0; w < N; w++){
            if (map[h][w] == 9){
                push(h,w,0,map2[h][w]);
                visited2[h][w] = 1;
            }
        }
    }
    BFS2();
}

void print_map(void){
    printf("\n");
    for(int h = 0; h < N; h++){
        for(int w = 0; w < N; w++){
            printf("%d ", map[h][w]);
        }
        printf("\n");
    }
    printf("\n");

    for(int h = 0; h < N; h++){
        for(int w = 0; w < N; w++){
            printf("%d ", map2[h][w]);
        }
        printf("\n");
    }
}


int main(void){
    InputData();
    Search_map();
    Search_map2();
    //print_map();
    printf("%d\n", min_cost);
    return 0;
}
