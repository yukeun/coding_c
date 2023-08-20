#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 1000
#define INF 1e9

int N = 0;
int M = 0;
int start = 0;
int end = 0;
int str[100000 + 10] = {0,};
int dst[100000 + 10] = {0,};
int cost[100000 + 10] = {0,};
int graph[MAXN + 10][MAXN + 10] = {0,};
int visited[MAXN + 10] = {0,};

struct QUE{
    int from;
};

struct QUE que[100 * 100 * 100 + 10] = {0,};
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
    scanf("%d", &N);           // N: 도시 개수
    scanf("%d", &M);           // M: 버스의 개수
    for(int i = 1; i <= M; i++){
        scanf("%d", &str[i]);
        scanf("%d", &dst[i]);
        scanf("%d", &cost[i]);
    }
    scanf("%d", &start);
    scanf("%d", &end);
}

void init_map(void){
    memset(graph, -1, sizeof(graph));

    for(int i = 1; i <= M; i++){
        int u = str[i];
        int v = dst[i];
        int w = cost[i];

        // 같은 경로에 대해 비용이 작은 버스만을 저장
        if(graph[u][v] == -1 || graph[u][v] > w)
            graph[u][v] = w;
    }
}

int BFS(void){
    // que 및 visited 초기화
    wp = rp = 0;
    for(int i = 1; i <= N; i++){
        visited[i] = INF;
    }

    push(start);
    visited[start] = 0;         // 초기 비용: 0

    while(!empty()){
        struct QUE cur = deque();
        for(int next = 1; next <= N; next++){
            if(graph[cur.from][next] == -1) continue;
            int time = visited[cur.from] + graph[cur.from][next];
            if (visited[next] > time){
                push(next);
                visited[next] = time;
            }
        }
    }

    return visited[end];
}

int main(void){
    InputData();
    init_map();
    int result = BFS();
    printf("%d\n", result);
    return 0;
}
