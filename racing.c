#include <stdio.h>
#define INF 2147483647
/*140
5
100 30 100 40 50 60
5 10 4 11 7*/
int max_dist;
int N;
int arr[110] = {0,};
int time[110] = {0,};
int visited[110] = {0, };
int process_dist[110] = {0,};
int path[110] = {0,};
int cnt = 0;
int result[110] = {0,};
struct QUE{
    int from;
};
struct QUE que[100 * 100 * 10];
int wp, rp;
void push(int from){
    que[wp].from = from;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

void InputData(void){
    scanf(" %d", &max_dist);
    scanf(" %d", &N);
    for(int i =0; i <= N; i++){
        scanf(" %d", &arr[i]);
    }
    for(int i = 1; i <= N; i++){
        scanf(" %d", &time[i]);
    }

    // initialize
    for(int i = 0; i <= N; i++){
        for(int j = i; j <= N+1; j++){
            process_dist[i] += arr[j];
        }
    }
}

int BFS(void){
    wp = rp = 0;
    visited[0] = 0;
    push(0);
    while(!empty()){
        struct QUE cur = deque();
        for(int i = cur.from + 1; i <= N+1; i++){
            // 정비소까지 갈 수 있는지 판별하기 : 현재 장소 - 나머지 거리
            if(process_dist[cur.from] - process_dist[i] <= max_dist){
                int new_value = visited[cur.from] + time[i];
                if(visited[i] >= new_value){
                    visited[i] = new_value;
                    path[i] = cur.from;
                    push(i);
                }
            }
        }
    }
    return visited[N+1];
}

void print_map(int num){
    if(path[num] == 0) return;
    print_map(path[num]);
    result[cnt] = path[num];
    cnt++;
}
int main(void){
    InputData();
    for(int i = 0; i <= N+1; i++){
        visited[i] = INF;
    }
    if(process_dist[0] <= max_dist){
        printf("%d\n", 0);
        printf("%d\n", 0);
    }
    else{
        int time = BFS();
        printf("%d\n", time);
        print_map(N+1);
        printf("%d\n", cnt);
        for(int i = 0; i < cnt; i++){
            printf("%d ", result[i]);
        }
    }
    return 0;
}