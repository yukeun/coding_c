#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN (100)
#define INF (1<<30)

int L; // 정비를 받지 않고 갈 수 있는 최대 거리
int N; // 정비소 개수
int dist[MAXN + 2]; // 정비소 사이 거리
int time[MAXN + 2]; // 정비 시간
int graph[MAXN + 2][MAXN + 2]; // 그래프
int visited[MAXN + 2]; // 방문 여부 및 정비 시간 기록
int path[MAXN + 2]; // 경로 기록
int total_time = INF; // 최소 총 정비 시간
int total_cnt = 0; // 방문하는 정비소 개수

struct QUE {
    int before;
    int cnt;
};

struct QUE que[MAXN * MAXN * MAXN + 10];
int wp, rp = 0;

void push(int place, int cnt) {
    que[wp].before = place;
    que[wp].cnt = cnt;
    wp++;
}

struct QUE deque(void) {
    return que[rp++];
}

int empty(void) {
    return wp == rp;
}

int abs(int a) {
    return (a > 0 ? a : -a);
}

void InputData(void) {
    scanf("%d", &L);
    scanf("%d", &N);
    for (int i = 1; i <= N + 1; i++) {
        scanf("%d", &dist[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &time[i]);
    }
}

void init_graph(void) {
    for (int h = 0; h <= N + 1; h++) {
        int start = dist[h];
        for (int w = 0; w <= N + 1; w++) {
            int end = dist[w];
            graph[h][w] = abs(end - start);
            graph[w][h] = abs(end - start);
        }
    }
}

void BFS(void) {
    wp = rp = 0;
    for (int i = 0; i < MAXN + 2; i++) {
        visited[i] = INF;
    }
    push(0, 0);
    visited[0] = 0;
    path[0] = 0;
    
    while (!empty()) {
        struct QUE cur = deque();
        
        if (cur.before == N + 1) {
            if (total_time > visited[N + 1]) {
                total_cnt = cur.cnt;
                total_time = visited[N + 1];
            }
        }
        
        for (int next = cur.before + 1; next <= N + 1; next++) {
            if (graph[cur.before][next] > L)
                continue;
            else {
                int New_time = visited[cur.before] + time[next];
                if (visited[next] <= New_time)
                    continue;
                visited[next] = New_time;
                path[next] = cur.before;
                push(next, cur.cnt + 1);
            }
        }
    }
}

void PrintResult(void) {
    if (total_time == INF) {
        printf("0\n");
        return;
    }
    
    printf("%d\n", total_time);
    printf("%d\n", total_cnt);
    for (int i = 1; i <= N + 1; i++) {
        if (path[i] != 0) {
            printf("%d ", path[i]);
        }
    }
}

int main(void) {
    InputData();
    init_graph();
    BFS();
    PrintResult();
    
    return 0;
}
