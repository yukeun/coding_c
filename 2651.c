#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647

int dist;
int N;                  // 1 <= N <= 100
int array[100 + 2] = {0,};
int time[100 + 2] = {0,};
int diff_dist[100 + 2] = {0,};
int visited[100 + 2] = {0,};
int way[100 + 2] = {0,};
struct QUE{
    int from;
    int cnt;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

void push(int from, int cnt){
    que[wp].from = from;
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
    scanf(" %d", &dist);
    scanf(" %d", &N);
    for(int i = 1; i <= N + 1; i++){
        scanf(" %d", &array[i]);
    }
    for(int i = 1; i <= N; i++){
        scanf(" %d", &time[i]);
    }
}

int BFS(void){
    wp = rp = 0;
    for(int i = 0; i <= 101; i++){
        visited[i] = INF;
    }
    visited[0] = 0;
    push(0, 0);

    while(!empty()){
        struct QUE pos = deque();
        for(int next = pos.from + 1; next <= N+1; next++){
            // 가지치기
            if((diff_dist[next] - diff_dist[pos.from]) > dist) continue;
            int temp_time = visited[pos.from] + time[next];
            if(visited[next] >= temp_time){
                visited[next] = temp_time;
                //printf("visited[%d] : %d\n", next, temp_time);
                push(next, pos.cnt + 1);
                way[next] = pos.from;
            }
        }
    }
    return que[--rp].cnt;
}

void print_way(int dst, int cnt){
    // 1. 종료조건
    if(cnt == 1) return;
    print_way(way[dst], cnt-1);
    printf("%d ", way[dst]);
}

void make_graph(void){
    int sum = 0;
    for(int i = 0; i <= N + 1; i++){
        for(int j = 0; j <= i; j++){
            sum += array[j];
        }
        diff_dist[i] = sum;
        sum = 0;
        //printf("%d ", diff_dist[i]);
    }
    //printf("\n");
}

int main(void){
    InputData();
    make_graph();
    if ((diff_dist[N+1] - diff_dist[0]) <= dist){
        printf("%d\n", 0);
        printf("%d\n", 0);
    }
    else{
        int cnt = BFS();
        printf("%d\n", visited[N+1]);
        printf("%d\n", cnt - 1);
        print_way(N+1, cnt);
    }

    return 0;
}