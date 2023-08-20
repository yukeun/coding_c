#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN (100)
#define INF (1<<30)

int L;//정비를 받지 않고 갈수있는 최대거리
int N;//정비소 개수
int dist[MAXN+10] = {0,};//정비소사이거리
int time[MAXN+10] = {0,};//정비시간
int graph[MAXN+10][MAXN+10] = {0,};
int visited[MAXN + 10] = {0,};
int path[MAXN + 10] = {0,};
int total_time = INF;
int diff[MAXN + 10] = {0,};
int total_cnt = 0;

int static compare(const void* first, const void* second){
    int a = (*(int *)first);
    int b= (*(int *)second);
    if(a > b) return 1;
    else return -1;
}
struct QUE{
    int before;
    int cnt;
};

struct QUE que[MAXN * MAXN * MAXN + 10];
int wp, rp = 0;

void push(int place, int cnt){
    que[wp].before = place;
    que[wp].cnt = cnt;
    wp++;
};
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

int abs(int a){
    return (a > 0 ? a : -a);
}

void InputData(void){
    scanf("%d", &L);
    scanf("%d", &N);
    for (int i=1; i<=N+1; i++){
        scanf("%d", &dist[i]);
    }
    for (int i=1; i<=N; i++){
        scanf("%d", &time[i]);
    }
}

void init_diff(void){
    for(int h = 0; h <= N+1; h++){
        for(int w= 0; w <= h; w++){
            diff[h] += dist[w];
        }
        //printf("diff[%d] = %d\n",h, diff[h]);
    }
}

// 구조체 까지 만들었구요
void init_graph(void){
    for(int h = 0; h <= N+1; h++){
        int start = dist[h];         // 첫 시작 점이죠;
        for(int w = 0; w <= N+1; w++){
            int end = dist[w];      // 정비소까지의 거리이죠
            graph[h][w] = abs(diff[w] - diff[h]);
            graph[w][h] = abs(diff[w] - diff[h]);
            // 그래프에는 현재 위치에서 다음 위치까지의 거리 차가 적혀 있다.
            //e.g., (0,2) 같은 경우, 0(출발지)에서 도착지까지의 거리차가 적혀있따
            // e.g., (2,3) 같은 경우 2번 정비소에서 3번 정비소 까지의 거리가 적혀있다. 
        }
    }
}

void print_graph(void){
    for(int h = 0; h <= N + 1; h++){
        for(int w= 0; w <= N+1; w++){
            printf("%d ", graph[h][w]);
        }
        printf("\n");
    }
}

void BFS(void){
    // 어차피 출발지는 0으로 정해져있다. 그러므로 BFS 안에서 큐 및 visited 초기화가 가능하다/
    wp = rp =0;
    for(int i = 0; i < MAXN+10;i++){
        visited[i] = INF;
    }
    push(0, 0);        // 0번 출발지부터 고려하자
    visited[0] = 0;
    path[0] = 0;
    //
    while(!empty()){
        
        struct QUE cur = deque();
        //printf("deque\n");
        if (cur.before == N+1){
            if (total_time > visited[N+1]){
                total_cnt = cur.cnt-1;
                total_time = visited[N+1];
            }
        }
        for(int next = cur.before+1; next <= N+1; next++){
            // 재 방문은 필요 없어영
            //printf("hello\n");
            if (graph[cur.before][next] > L) continue;
            else{
                // 사정 거리 안에 들어왔음
                int New_time = visited[cur.before] + time[next];            // 정비시간
                //printf("new_time : %d\n",New_time);
                if (visited[next] <= New_time) continue;
                visited[next] = New_time;
                //printf("visited[%d] = %d\n",next, visited[next]);
                path[next] = cur.before;
                push(next,cur.cnt+1);
            }
        }
    }
}

void PRT(int m, int index){
    if (m == 0){
        total_cnt = index-1;
        printf("%d\n",total_cnt);
        return;
    }
    PRT(path[m], index+1);
    if(path[m] == 0) return;
    else{
        printf("%d ", path[m]);
    }
}


int main(void){
    InputData();//입력 받는 부분
    init_diff();
    init_graph();
    //print_graph();
    //여기서부터 작성
    BFS();
    if (total_time == 0){
        printf("%d\n", 0);
    }
    else{
        printf("%d\n",total_time);
        //printf("%d\n", total_cnt);
        PRT(N+1,0);
    }
    


    return 0;
}