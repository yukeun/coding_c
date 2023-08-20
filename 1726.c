#include <stdio.h>
int M, N;
int str_h, str_w, str_dir;
int dst_h, dst_w, dst_dir;
int map[110][110] = {0,};
int visited[110][110][5] = {0,};

struct QUE{
    int state;
    int dir;
    int h;
    int w;
    int cnt;
};
struct QUE que[100 * 100 * 100];
int wp, rp;

void push(int state, int dir, int h, int w, int cnt){
    que[wp].state =state; que[wp].dir = dir; que[wp].h =h; que[wp].w = w; que[wp].cnt = cnt;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

int left_direction(int dir){
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
int right_direction(int dir){
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
int BFS(void){
    int dh[] = {0, 0, 1, -1};
    int dw[] = {1, -1, 0, 0};
    int left, right;
    wp = rp = 0;
    visited[str_h][str_w][str_dir] = 1;
    push(0, str_dir, str_h, str_w, 0);
    while(!empty()){
        struct QUE cur = deque();
        // 종료조건
        if(cur.h == dst_h && cur.w == dst_w && cur.dir == dst_dir) return cur.cnt;
        if(cur.state == 0){
            left = left_direction(cur.dir);
            right = right_direction(cur.dir);
            if(visited[cur.h][cur.w][left] == 0) 
            push(1, cur.dir, cur.h, cur.w, cur.cnt);
            if(visited[cur.h][cur.w][left] == 0) {
                push(1, left, cur.h, cur.w, cur.cnt + 1);
                visited[cur.h][cur.w][left] = 1;
            }
            if(visited[cur.h][cur.w][right] == 0){
                push(1, right, cur.h, cur.w, cur.cnt + 1);
                visited[cur.h][cur.w][right] = 1;
            }
            
            
        }
        else if(cur.state == 1){
            // 이동할 차례
            for(int k = 1; k <= 3; k++){
                int next_h = cur.h + dh[cur.dir-1] * k;
                int next_w = cur.w + dw[cur.dir-1] * k;
                if(next_h >= 1 && next_h <= M && next_w >= 1 && next_w <= N){
                    if(map[next_h][next_w] == 1){
                        //printf("break! next_h : %d, next_W : %d, k : %d\n", next_h, next_w, k);
                        break;
                    }
                    if(visited[next_h][next_w][cur.dir] == 1){
                        //printf("continue ! next_h : %d, next_w : %d\n", next_h, next_w);
                        continue;
                    } 
                    push(0, cur.dir, next_h, next_w, cur.cnt + 1);
                    //printf("push ! next_h : %d, next_w : %d, cur.cnt + 1 : %d, dir : %d\n", next_h, next_w, cur.cnt+1, cur.dir);
                }
            }
        }
    }
    return -1;
}

void InputData(void){
    scanf(" %d %d", &M, &N);
    for(int h = 1; h <= M; h++){
        for(int w = 1; w <= N; w++){
            scanf(" %d", &map[h][w]);
        }
    }
    scanf(" %d %d %d", &str_h, &str_w, &str_dir);
    scanf(" %d %d %d", &dst_h, &dst_w, &dst_dir);
}

void print_map(void){
    for(int h = 1; h <= M; h++){
        for(int w = 1; w <= N; w++){
            printf("%d", map[h][w]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(void){
    InputData();
    //print_map();
    int result = BFS();
    printf("%d\n", result);
    return 0;
}