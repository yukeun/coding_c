#include <stdio.h>
#include <stdlib.h>

int N;
int grids[500+10][500+10];
int D = 1000001;               // 트랙터의 최소 성능 => 맵 탐색해서 가장 높은 높이로 초기설정
int visited[500+10][500+10] = {0,};
int target = 0;
int min_power = 1000001;

int abs(int a){
    return (a >= 0? a : -a);
}

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
};

void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            scanf("%d", &grids[i][j]);
        }
    }
    target = ((double)(N*N)/2 + 0.7);
    printf("target : %d\n", target);
}
void print_map(void){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%d", grids[i][j]);
        }
        printf("\n");
    }
}

int BFS(int mid){
    int dh[] = {-1, 1, 0, 0};
    int dw[] = {0, 0, -1, 1};
    int count = 1;
    printf("test\n");
    while(!empty()){
        struct QUE value = deque();
        //printf("deque!!\n");
        //printf("value.h : %d, value.w : %d, value.height : %d\n", value.h, value.w, value.height);
        if(count>=target) return count;
        for(int i = 0; i < 4; i++){
            // 유효범위 안에 들어오는가
            if(value.h+dh[i] >=0 && value.h+dh[i]<N && value.w+dw[i]>=0 && value.w+dw[i]<N){
                // 이동하려는 곳이 현재 있는 곳 보다 높을 때
                //
                if(abs(grids[value.h+dh[i]][value.w+dw[i]] - value.height) > mid) continue;
                else{
                        push(value.h+dh[i],value.w+dw[i], grids[value.h+dh[i]][value.w+dw[i]]);
                        printf("value.h : %d, value.w : %d, value.height : %d\n", value.h+dh[i], value.w+dw[i], grids[value.h+dh[i]][value.w+dw[i]]);
                        printf("push again!!\n");
                        count++;
                    }
                }
            }
        }
        return count;
    }
    

void Binary_search(void){
    int flag = 0;
    int start = 0;
    int end = D;
    int mid = 0;
    printf("start : %d, end : %d\n", start, end);
    int result = 0;
    while(start<=end){
        printf("hello\n");
        mid = (start + end) / 2;            // m 바꿈
        D = mid;
        printf("mid : %d\n", mid);
        flag=0;// 
        memset(visited, 0, sizeof(visited));
        // 반복문 초기값 넣어줌
        for(int i = 0; i < N; i++){
            if(flag==1){
                printf("Hi Again there~!\n");
                    break;
            }
            for(int j = 0; j < N; j++){
                if(flag==1) {
                    printf("Hi there~!\n");
                    break;
                }
                if(visited[i][j]) continue;             // 한번 방문한 곳인지.
                else{
                   // printf("Test!!!!\n");
                    wp = rp = 0;
                    push(i, j, grids[i][j]);
                    printf("i : %d, j : %d, grids[%d][%d] : %d\n",i,j,i,j,grids[i][j]);
                    int state = BFS(mid);
                    printf("state : %d\n",state);
                    if (state){
                        // 반 이상을 이동할 수 있을 때,
                        flag =1;
                        end = mid -1;
                        printf("end :  %d\n", end);
                        printf("Move to the first!\n");
                        break;
                    }
                    else{
                        continue;
                    }
                    
                }
            }
        }
        //start=mid+1;
    }
    printf("why?\n");
    printf("start :%d, mid : %d, end :%d\n",start ,mid, end);
    return;
    
}

    
int main(void){
    int ans = -1;
    InputData();// 입력받는 부분
    print_map();
    //Binary_search();
    // 여기서부터 작성
    printf("D : %d\n",D);
    //printf("%d\n", ans);// 출력하는 부분
    return 0;
}