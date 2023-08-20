#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (500)
int N;
int grids[MAXN+10][MAXN+10];
int visited[MAXN+10][MAXN+10];
int maxh = -1;

struct QUE{
    int h;
    int w;
    int height;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;
void push(int h, int w, int height){
    visited[h][w] = 1;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].height = height;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
};
int empty(void){
    return wp == rp;
}
int abs(int a){
    return (a >= 0 ? a : -a);
}

void print_map(void){
    for(int h = 0; h < N; h++){
        for(int w=0; w < N; w++){
            printf("%d ", grids[h][w]);
        }
        printf("\n");
    }
}

void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            scanf("%d", &grids[i][j]);
            if (maxh < grids[i][j]) maxh = grids[i][j];
        }
    }
}

int BFS(int h, int w, int mid){
    int dh[] = {-1, 1, 0, 0};       // 사방 탐색을 하기 위함
    int dw[] = {0, 0, -1, 1};       // 사방 탐색을 하기 위함

    //visited는 새로운 mid를 가지고 할떄마다 업데이트해주면 되니까 BFS밖에서 선언해줘야 한다.
    // 해당 h와 w를 가지고 push한 이후에 BFS 탐색을 진행한다.
    //memset(visited, 0, sizeof(visited));        // visited 초기화
    wp = rp = 0;                                  // 큐 포인터 초기화
    push(h,w, grids[h][w]);
    int cnt = 1;                                    // 처음에 푸쉬될때부터 한 칸을 차지하므로 이렇게 처리해준다.
    while(!empty()){
        if (cnt >= ((N * N + 1) / 2)){
            // 반절이상 차지한 경우에는 mid를 갱신해줘야 하므로 while 문을 탈출해야한다.
            return 1;               // 반 절이상 나왔을 경우, 1을 리턴하도록 한다.
        }
        struct QUE pos = deque();
        for(int i = 0; i < 4; i++){
            int next_h = pos.h + dh[i];
            int next_w = pos.w + dw[i];
            // 유효 범위 안에 들어오는 지 확인하기
            if(next_h >= 0 && next_h < N && next_w >= 0 && next_w < N && visited[next_h][next_w] == 0){
                // 유효 범위 안에 들어왔을 경우, 탐색을 진행한다.
                // case 1 높이차가 mid 보다 높을 경우 
                if(abs(grids[next_h][next_w] - pos.height) > mid) continue;
                push(next_h, next_w, grids[next_h][next_w]);
                cnt++;
            }
        }
    }
    return 0;
}

int Binary_Search(int start, int end){
    // 이진탐색을 시작한다
    // 좀 더 효율적인 탐색을 위해서 right의 경우에는 grids에서 가장 높은 높이를 탐색한다.
    int left = start;
    int right = end - start;
    int result = end;                   // 처음에 D는 end로 설정해준다.
    int flag = 0;
    memset(visited,0,sizeof(visited));      // visited 배열 초기화
    while(left <= right){
        int mid = (left + right) / 2;
         // 전체 맵 한 바퀴 돌기
        for(int h = 0; h < N; h++){
            for(int w = 0; w < N; w++){
                // 가지치기 해줘야겠구나
                if (visited[h][w] == 1) continue;
                int temp = BFS(h,w,mid);
                if(temp){
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }
        if (flag){
            // flag면 mid값 갱신해야하는데, mid값을 더 줄이는 방향으로
            right = mid - 1;
            result = mid;
            flag = 0;
        }
        else{
            // flag == 0일 경우 해당 mid값으로 모든 좌표를 다 BFS 돌려도 반절이상 차지하지못함
            // mid를 키워야 한다.
            left = mid + 1;
        }
        memset(visited, 0, sizeof(visited));            // visited 배열 초기화해주기
    }
    return result;
    
}

int main(void){
    int ans = -1;

    InputData();// 입력받는 부분
    // 여기서부터 작성
    ans = Binary_Search(0, maxh);
    printf("%d\n", ans);// 출력하는 부분
    return 0;
}