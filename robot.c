#include <stdio.h>
int M, N;
int map[110][110] = {0,};
int str_h, str_w, str_dir;
int dst_h, dst_w, dst_dir;
int visited[110][110][5] = {0,};
int dh[] = {0, 0, 0, 1, -1};
int dw[] = {0, 1, -1, 0, 0};
int min = (1<<30);
struct QUE{
    int state;
    int dir;
    int h;
    int w;
    int cnt;
};
struct QUE que[100 * 100 * 100 + 10];
int wp, rp;
void push(int state, int dir, int h, int w, int cnt){
    que[wp].state = state;
    que[wp].dir = dir;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].cnt = cnt;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

void InputData(void){
    scanf(" %d %d", &M, &N);
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            scanf(" %d", &map[i][j]);
        }
    }
    scanf(" %d %d %d", &str_h, &str_w, &str_dir);
    scanf(" %d %d %d", &dst_h, &dst_w, &dst_dir);
}

void print_map(void){
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}
int left_dir(int dir){
    int left;
    switch(dir){
        case 1:
            left = 4; break;
        case 2:
            left = 3; break;
        case 3:
            left = 1; break;
        default:
            left = 2;
    }
    return left;
}

int right_dir(int dir){
    int right;
    switch(dir){
        case 1:
            right = 3; break;
        case 2:
            right = 4; break;
        case 3:
            right = 2; break;
        default:
            right = 1;
    }
    return right;
}
int back_dir(int dir){
    int back;
    switch(dir){
        case 1:
            back = 2; break;
        case 2:
            back = 1; break;
        case 3:
            back = 4; break;
        default:
            back = 3;
    }
    return back;
}

int BFS(void){
    wp = rp = 0;
    visited[str_h][str_w][str_dir] = 1;
    push(1, str_dir, str_h, str_w, 0);
    while(!empty()){
        struct QUE cur = deque();
        //1. 종료조건
        if (cur.h == dst_h && cur.w == dst_w && cur.dir == dst_dir) return cur.cnt;
        if(cur.state == 1){
            int go = cur.dir;
            int left = left_dir(cur.dir);
            int right = right_dir(cur.dir);
            int back = back_dir(cur.dir);
            for(int k = 1; k <= 3; k++){
                int next_h = cur.h + dh[cur.dir] * k;
                int next_w = cur.w + dw[cur.dir] * k;
                if(next_h >= 1 && next_h <= M && next_w >= 1 && next_w <= N){
                    if(map[next_h][next_w] == 1) break;
                    if(map[next_h][next_w] == 0 && visited[next_h][next_w][cur.dir] == 0){
                        push(1, cur.dir, next_h, next_w, cur.cnt + 1);
                        //printf("next_h : %d next_w : %d, cur.dir = %d, cur.cnt + 1 : %d\n",next_h, next_w, cur.dir, cur.cnt + 1);
                        visited[next_h][next_w][cur.dir] = 1;
                    }
                }
            }
            push(2, left, cur.h, cur.w, cur.cnt+1);
            push(2, right, cur.h, cur.w, cur.cnt + 1);
            push(2, back, cur.h, cur.w, cur.cnt + 2);
            visited[cur.h][cur.w][left] = 1;
            visited[cur.h][cur.w][right] = 1;
            visited[cur.h][cur.w][back] = 1;
        }
        else if(cur.state == 2){
            for(int k = 1; k <= 3; k++){
                int next_h = cur.h + dh[cur.dir] * k;
                int next_w = cur.w + dw[cur.dir] * k;
                if(next_h >= 1 && next_h <= M && next_w >= 1 && next_w <= N){
                    if(map[next_h][next_w] == 1) break;
                    if(map[next_h][next_w] == 0 && visited[next_h][next_w][cur.dir] == 0){
                        push(1, cur.dir, next_h, next_w, cur.cnt + 1);
                        //printf("next_h : %d next_w : %d, cur.dir = %d, cur.cnt + 1 : %d\n",next_h, next_w, cur.dir, cur.cnt + 1);
                        visited[next_h][next_w][cur.dir] = 1;
                    }
                }
            }
        }
    }
    return -1;
}

int main(void){
    InputData();
    //print_map();
    int result = BFS();
    printf("%d\n", result);
    return 0;
}