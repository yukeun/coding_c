#include <stdio.h>

int N;
int K; //(0<=K<=100)
int map[110][110] = {0,};
int L;  // snake's direction point
int time[10010];
char dir[110];
int dh[] = {0, 0, 0, 1, -1};        //동서남북
int dw[] = {0, 1, -1, 0, 0};

struct QUE{
    int dir;
    int h;
    int w;
    int time;
};
struct QUE que[100 * 100 * 100];
int wp, rp;


void InputData(void){
    scanf(" %d", &N);
    scanf(" %d", &K);
    for(int i = 1; i <= K; i++){
        int h, w;
        scanf(" %d %d", &h, &w);
        map[h][w] = 1;
    }
    scanf(" %d", &L);
    for(int i =  0; i < L; i++){
        scanf(" %d %c",  &time[i], &dir[i]);
    }
}
void print_map(void){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
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
int BFS(int direct, int h, int w, int timer){
    int time_idx = 0;
    wp = rp = 0;
    que[wp].dir = direct;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].time = timer;
    while(1){
        //printf("pop\n");
        // 1. 방향전환 조건
        int direction = que[wp].dir;
        int cur_time = que[wp].time;
        int next_h = que[wp].h + dh[direction];
        int next_w = que[wp].w + dw[direction];
        //printf("next_h :%d next_w : %d\n",next_h, next_w);
        if(que[wp].time == time[time_idx]){
            if(dir[time_idx] == 'L'){
                direction = left_direction(que[wp].dir);
            }
            else direction = right_direction(que[wp].dir);
            next_h = que[wp].h + dh[direction];
            next_w = que[wp].w + dw[direction];
            time_idx++;
        }
        
        //2. 종료조건
        if (next_h < 1 || next_h > N || next_w < 1 || next_w > N) return que[wp].time + 1;
        if (map[next_h][next_w] == 2) return que[wp].time + 1;

        // BFS설정
        if (map[next_h][next_w] == 1){
            // 사과를 발견했을 떄
            map[next_h][next_w] = 2;
            que[++wp].dir = direction;
            que[wp].h = next_h;
            que[wp].w = next_w;
            que[wp].time = cur_time + 1;
        }
        else{
            map[next_h][next_w] = 2;
            map[que[rp].h][que[rp].w] = 0;
            //printf("next_h :%d next_w : %d\n",next_h, next_w);
            que[++wp].dir = direction;
            que[wp].h = next_h;
            que[wp].w = next_w;
            que[wp].time = cur_time + 1;
            rp++;
        }
        //print_map();
    }
    return -1;
}

int main(void){
    InputData();
    //print_map();
    int result = BFS(1, 1, 1, 0);
    printf("%d\n", result);
    return 0;
}