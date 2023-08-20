#include <stdio.h>
int R;
int C;
char map[55][55] = {0,};
int visited_1[55][55] = {0,};
int visited_2[55][55] = {0,};
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

struct QUE{
    int status;                         // status 0 : flood, 1 : biber
    int h;
    int w;
    int cnt;
};
struct QUE que[100 * 100 * 10];
int wp, rp;

void push(int status, int h, int w, int cnt){
    que[wp].status = status;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].cnt = cnt;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}
//KAKTUS
void InputData(void){
    scanf(" %d %d", &R, &C);
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            scanf(" %c", &map[i][j]);
        }
    }
}

int BFS(void){
    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];
            if(next_h >= 1 && next_h <= R && next_w >= 1 && next_w <= C){
                //1. state확인
                if (cur.status == 0){
                    // 홍수이면
                    if(map[next_h][next_w] == 'X' || visited_1[next_h][next_w] == 1 || map[next_h][next_w] == '*' || map[next_h][next_w] == 'D') continue;
                    visited_1[next_h][next_w] = 1;
                    push(0,next_h,next_w, cur.cnt + 1);
                    map[next_h][next_w] = '*';
                }
                else if(cur.status == 1){
                    if(map[next_h][next_w] == 'D') return cur.cnt + 1;
                    if(map[next_h][next_w] == 'X' || visited_2[next_h][next_w] == 1 || map[next_h][next_w] == '*') continue;
                    visited_2[next_h][next_w] = 1;
                    map[cur.h][cur.w] = '.';
                    push(1,next_h,next_w, cur.cnt + 1);
               }
            }
            //print_map();
        }
    }
    return -1;
}

void Search_map(void){
    wp = rp = 0;
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            if(map[i][j] == '*'){
                push(0,i,j,0);
                visited_1[i][j] = 1;
            }
        }
    }
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            if(map[i][j] == 'S'){
                push(1,i,j,0);
                visited_2[i][j] = 1;
                map[i][j] = '.';
            }
        }
    }
}



void print_map(void){
    for(int i = 1; i <= R; i++){
        for(int j = 1; j <= C; j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// 홍수를 먼저 담자



int main(void){
    InputData();
    //print_map();
    Search_map();
    int result = BFS();
    if(result == -1) printf("KAKTUS\n");
    else printf("%d\n", result);
    return 0;
}