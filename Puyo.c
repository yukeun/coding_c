#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map[100+10][100+10] = {0,};
int visited[100+10][100+10] = {0,};
int is_boom[100 + 10][100 + 10] = {0,};
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};
int flag = 0;
int total_cnt = 0;
struct QUE{
    int h;
    int w;
    char a;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

void push(int h, int w, char a){
    que[wp].h = h;
    que[wp].w = w;
    que[wp].a = a;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}

void inputdata(void){
    for(int i = 0; i < 12; i++){
        scanf("%s", &map[i][0]);
        /*for(int j = 0; j < 6; j++){
            scanf(" %s", &map[i][j]);
        }*/
    }
}

int BFS(int h, int w){
    char target = map[h][w];
    int cnt = 1;
    wp = rp = 0;
    push(h,w,map[h][w]);
    visited[h][w] = 1;
    // 초기화
    while(!empty()){
        struct QUE pos = deque();
        for(int i = 0; i < 4; i++){
            int next_h = pos.h + dh[i];
            int next_w = pos.w + dw[i];
            if(next_h >= 0 && next_h < 12 && next_w >= 0 && next_w < 6 && visited[next_h][next_w] == 0){
                // 사방탐색을 시작한다.
                if(map[next_h][next_w] == '.' || map[next_h][next_w] != target) continue;
                push(next_h,next_w,map[pos.h][pos.w]);
                visited[next_h][next_w] = 1;
                cnt++;
            }
        }
    }
    if (cnt >= 4) return 1;
    else return 0;
}

void BOOM(int h, int w){
    char target = map[h][w];
    wp = rp = 0;
    push(h, w, map[h][w]);
    map[h][w] = '.';
    is_boom[h][w] = 1;
    while(!empty()){
        struct QUE pos = deque();
        //printf("Deque!\n");
        for(int i = 0; i < 4; i++){
            int next_h = pos.h + dh[i];
            int next_w = pos.w + dw[i];
            if(next_h >= 0 && next_h < 12 && next_w >= 0 && next_w < 6 && is_boom[next_h][next_w] == 0){
                // 사방탐색을 시작한다.
                if(map[next_h][next_w] == '.' || map[next_h][next_w] != target) continue;
                map[next_h][next_w] = '.';
                push(next_h,next_w,map[pos.h][pos.w]);
                is_boom[next_h][next_w] = 1;
            }
        }
    }
}

void down(int h, int w){
    // 종료조건 설정
    if(map[h-1][w] == '.' || (h-1) < 0) return;

    // 재귀 조건
    //위에 걸 내리고 아래걸 올려서 위에것에서 재귀해야한다.
    map[h][w] = map[h-1][w];
    map[h-1][w] = '.';
    down(h-1,w);
}

int Solve(void){
    while(!flag){
        memset(visited, 0, sizeof(visited));                // visited 배열을 초기화해줘야한다.
        for(int i = 0; i < 12; i++){
            for(int j = 0; j < 6; j++){
                if (map[i][j] != '.' && visited[i][j] == 0){
                    int whether = BFS(i,j);
                    if(whether){
                        BOOM(i, j);
                        flag = 1;
                    }
                }
            }
        }
        if (flag){
            total_cnt++;
            // 폭발한거 내려야함
            for(int i = 0; i < 12; i++){
                for(int j = 0; j < 6; j++){
                    if (is_boom[i][j] == 1){
                        down(i,j);
                    }
                }
            }
            flag = 0;
            memset(is_boom, 0, sizeof(is_boom));
            //print_map();
        }
        else{
                printf("%d\n", total_cnt);
                return 0;
        }
    }  
    // 한번 떨어졌당
}



void print_map(void){
    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 6; j++){
            printf("%c",map[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    inputdata();
    Solve();
    return 0;
}