/*6 4
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1

첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 
단, 2 ≤ M,N ≤ 1,000 이다. 
둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 
즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 
하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 
정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다.

토마토가 하나 이상 있는 경우만 입력으로 주어진다.

출력
여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 
만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 
토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1001
int M;          // M은 가로 칸의 수
int N;          // N은 세로 칸의 수
char map[MAXN+10][MAXN+10] = {0,};
int map1[MAXN+10][MAXN+10] = {0,};

struct QUE{
    int h;
    int w;
    int day;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;
void push(int h, int w, int day){
    que[wp].h = h;
    que[wp].w = w;
    que[wp].day = day;
    wp++;
}

struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}

void InputData(void){
    scanf("%d", &M);
    scanf("%d", &N);
    // printf("pass\n");
    //printf("M : %d, N : %d\n", M, N);
    // 초기화
    memset(map, 0, sizeof(map));
    memset(map1, 0 ,sizeof(map1));
    wp = rp = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf(" %s", &map[i][j]);
            map1[i][j] = (int)(map[i][j] - '0');
            if (map1[i][j] == 1){
                // 익은 토마토가 발견된다면, que에 푸쉬한다.
                push(i,j,0);
            }
        }   
    }
    return;
}

void print_map(void){
    printf("\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            printf("%d ", map1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int BFS(void){
    int dh[] = {-1, 1, 0, 0};
    int dw[] = {0, 0, -1, 1};                 // 사방 탐색

    while(!empty()){
        struct QUE cur = deque();
        for(int i = 0; i < 4; i++)
        {
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];
            if (next_h >= 0 && next_h < N && next_w >= 0 && next_w < M){
                // 사각 범위 안에 들어온다면 사방탐색 시작
                if (map1[next_h][next_w] != 0) continue;
                map1[next_h][next_w] = 1;
                push(next_h, next_w, cur.day + 1);
            }
        }
    }
    if (que[--rp].day == 0){
        // 토마토가 모두 익어있는 상태
        return 0;
    }
    else que[--rp].day;
}

int search_map(void){
    for(int h = 0; h < N; h++){
        for(int w = 0; w < M; w++){
            if (map1[h][w] == 0) return -1;
        }
    }
    return 0;
}

int main(void){
    InputData();
    //print_map();
    int time = BFS();
    int result = search_map();
    if (result == 0){
        printf("%d\n", time);
    }
    else{
        printf("%d\n", result);
    }
    //print_map();
    return 0;
}