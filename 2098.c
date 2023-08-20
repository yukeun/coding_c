#include <stdio.h>
#include <stdio.h>
#define INF (1<<30)

int N;
int map[20][20] = {0,};
int min_cnt = INF;
int visited[20] = {0,};
void InputData(void){
    scanf(" %d", &N);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            scanf(" %d", &map[i][j]);
        }
    }
}

void DFS(int idx, int from, int sum, int start){
    //1. 가지치기
    if (sum >= min_cnt) return;
    //2. 종료조건
    if (idx == N){
        if(map[from][start] == 0 || visited[start] ==1) return;
        int temp_sum = 0;
        temp_sum = sum + map[from][start];
        if(temp_sum < min_cnt) min_cnt = temp_sum;
        return;
    }

    //3. 재귀조건
    for(int i = 1; i <= N; i++){
        if (map[from][i] == 0 || visited[i] == 1) continue;
        visited[i] = 1;
        DFS(idx+1, i, sum + map[from][i], start);
        visited[i] = 0;
    }
}

int main(void){
    InputData();
    DFS(1,1,0,1);
    printf("%d\n", min_cnt);
    return 0;
}