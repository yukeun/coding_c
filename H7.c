#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXH (12)
#define MAXW (6)
char map[MAXH+2][MAXW+2];
int visited[MAXH+2][MAXW+2] = {0,};
int pop_visit[MAXH+2][MAXW+2] = {0,};
struct QUE{
    int h;
    int w;
    char a;
};
struct QUE que[100 * 100 * 100 + 10];
int wp, rp;
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

void push(int h, int w, char a){
    que[wp].h = h;
    que[wp].w = w;
    que[wp].a = a;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

void InputData(void){
    for (int i=1; i<=MAXH; i++){
        scanf("%s", &map[i][1]);
    }
}

void print_map(void){
    for(int h=1; h <= MAXH; h++){
        for(int w=1; w<= MAXW; w++){
            printf("%c",map[h][w]);
        }
        printf("\n");
    }
}

int BFS(int h, int w, char a){
    // 정확한 시작지점을 모르므로 여기서 visited를 초기화 하면 안된다.
    wp = rp = 0;                // 큐 포인터 초기화
    push(h,w,a);
    visited[h][w] = 1;
    int cnt = 1;
    while(!empty()){
        if (cnt >= 4) {
            //printf("count is over!\n");
            return 1;
        }
        struct QUE cur = deque();
        //printf("deque!\n");
        // 일단 유효범위 안에 들어와야한다.
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];
            //printf("test\n");
            if(next_h >= 1 && next_h <= MAXH && next_w >= 1 && next_w <= MAXW && visited[next_h][next_w] == 0){
                // 아직 방문안했고 유효범위 안에 들어올 경우,
                if(map[next_h][next_w] == cur.a){
                    push(next_h,next_w,cur.a);
                    visited[next_h][next_w] = 1;
                    cnt++;
                }
            }
        }
    }
    return 0;           // 4개 이상이 아닐 경우에는 0을 리턴한다.
    // 0을 리턴하게 되면, 뭐 어떻게 해야하는건데? => 
}
void POP(int h, int w, char a){
    wp = rp =0;
    push(h,w,a);
    pop_visit[h][w] = 1;
    map[h][w] = '.';
    while(!empty()){
        struct QUE cur = deque();
        //유효범위 판별하기
        //printf("pop pop pop\n");
        for(int i = 0; i < 4; i++){
            int next_h = cur.h + dh[i];
            int next_w = cur.w + dw[i];

            if(next_h >= 1 && next_h <= MAXH && next_w >= 1 && next_w <= MAXW && pop_visit[next_h][next_w] == 0){
                //printf("temp %c\n", cur.a);
                if(map[next_h][next_w] == cur.a){
                    //printf("temp %c\n", cur.a);
                    map[next_h][next_w] = '.';
                    pop_visit[next_h][next_w] = 1;
                    push(next_h, next_w, cur.a);
                }
            }
        }
    }
    printf("====== After pop! =======\n\n");
    print_map();
}

void drop_block(int h,int w){
    // 일단 좌표를 받아와야 한다. 재귀를 하려면
    // 근데 이 좌표가 뭐지?
    // 0. 종료조건을 선언해줘야 한다.
    // 현재 좌표보다 한 칸 위가 .이 있거나, 
    if (map[h-1][w] == '.' || (h-1) < 1) return;
    // 1. 재귀조건
    if (map[h-1][w] != '.'){
        map[h][w] = map[h-1][w]; // 한 칸 밑으로 내린다.
        map[h-1][w] = '.';
        drop_block(h-1,w);
    }

}

int Solve(void){
    int drop_cnt = 0;
    int flag = 0;
    while(!flag){
        // 일단 새로 좌표를 잡아서 시작하는 이상 visited 및  pos_visit을 활성화시켜줘야 한다.
        //memset(visited, 0, sizeof(visited));
        memset(pop_visit, 0, sizeof(pop_visit));
        for(int h=1; h<=MAXH; h++){
            for(int w=1; w<=MAXW; w++){
                if(map[h][w] !='.'){
                    memset(visited, 0, sizeof(visited));
                    int state = BFS(h,w,map[h][w]);
                    if (state){
                        //printf("Hello Pop!!\n");
                        POP(h,w,map[h][w]);
                        flag = 1;
                        state = 0;
                    }
                    // map을 터뜨린다.
                }
            }
        }
        if (flag){
            // 터진게 있다면 내려야 한다.
            for(int h=1;h<=MAXH;h++){
                for(int w=1; w<=MAXW;w++){
                    if(pop_visit[h][w] != 1) continue;
                    drop_block(h,w);
                }
            }
            memset(pop_visit, 0, sizeof(pop_visit));
            drop_cnt++;
            flag = 0;
            printf("====== After drop =======\n\n");
            print_map();
        }
        else{
            return drop_cnt;
        } 
        // 전체 맵을 돌면서 4개 이상인 것을 한번씩 터뜨렸을 때, 이제 내리는 단계가 있어야한다.
        
    }
    return drop_cnt;
    
}

int main(void){
    int T, t, ans = -1;
    scanf("%d", &T);
    for (t=1; t<=T; t++){
        InputData();//입력받는 부분
        //print_map();
        ans = Solve();
        //여기서부터 작성
        //print_map();

        printf("%d\n", ans);//출력하는 부분
    }
    return 0;
}