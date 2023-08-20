// 백준 3190번 문제인데 뭐가 틀린거야?? 틀린부분 알려줘
#include <stdio.h>
int N;                  // 2< =N <= 100, 보드의 크기
int K;                  // 사과의 갯수
int L;                  // 뱀의 방향전환 횟수
int map[110][110] = {0,};
int map2[110][110] = {0,};
int time[110] = {0,};
char direction[110] = {0,};
int dh[] = {0,1,0,-1};
int dw[] = {1,0,-1,0};

void InputData(void){
    scanf(" %d", &N);
    scanf(" %d", &K);
    for(int i = 0; i < K; i++){
        int h, w;
        scanf(" %d %d", &h, &w);
        map[h][w] = 1;
    }
    scanf(" %d", &L);
    for(int i = 0; i < L; i++){
        scanf("%d %c", &time[i], &direction[i]);
    }
    
}
void print_map(void){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%d", map2[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_map1(void){
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
struct QUE{
    int h;
    int w;
};
struct QUE snake[100 * 100 * 100 * 10] = {0,};
int wp, rp;
int Solve(void){
    wp = rp = 0;
    snake[wp].h = snake[wp].w = 1;
    int timer = 0;
    int i = 0;
    int idx = 0;
    char cur_direct = 'D';
    while(1){
        printf("current time : %d\n", timer);
        printf("current direct : %c\n", cur_direct);
        //printf("i : %d\n", i % 4);
        int next_h, next_w;
        if(cur_direct == 'D'){
            next_h = snake[wp].h + dh[(i)% 4];
            next_w = snake[wp].w + dw[(i) % 4];
        }
        else{
            next_h = snake[wp].h + dh[(i+2) % 4];
            next_w = snake[wp].w + dw[(i+2) % 4];
        }
        
        if(timer == time[idx]){
            i++;
            if(direction[idx] == 'L'){
                next_h = snake[wp].h + dh[(i+2) % 4];
                next_w = snake[wp].w + dw[(i+2) % 4];  
                cur_direct = 'L';
            }
            else{
                next_h = snake[wp].h + dh[(i)% 4];
                next_w = snake[wp].w + dw[(i) % 4];
                cur_direct = 'D';
            }
            idx++;
        }
        // 종료조건 설정해주기
        if (next_h < 1 || next_h > N || next_w < 1 || next_w > N) return timer + 1;
        if(map2[next_h][next_w] == 2) return timer + 1;
        if (map[next_h][next_w] == 1){
            map[next_h][next_w] = 0;
            snake[++wp].h = next_h;
            snake[wp].w = next_w;
            map2[snake[wp].h][snake[wp].w]= 2;
            map2[snake[rp].h][snake[rp].w] = 2;
        }
        else{
            snake[++wp].h = next_h;
            snake[wp].w = next_w;
            map2[snake[wp].h][snake[wp].w]= 2;
            map2[snake[rp].h][snake[rp].w]= 0;
            rp++;
        }
        print_map();
        timer++;
    }
}
int main(void){
    InputData();
    print_map1();
    int result = Solve();
    printf("%d\n", result);
    return 0;
}