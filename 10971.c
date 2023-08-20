/*

첫째 줄에 도시의 수 N이 주어진다. (2 ≤ N ≤ 10) 다음 N개의 줄에는 비용 행렬이 주어진다. 
각 행렬의 성분은 1,000,000 이하의 양의 정수이며, 갈 수 없는 경우는 0이 주어진다. 
W[i][j]는 도시 i에서 j로 가기 위한 비용을 나타낸다.

항상 순회할 수 있는 경우만 입력으로 주어진다.

출력
첫째 줄에 외판원의 순회에 필요한 최소 비용을 출력한다.

4
0 10 15 20
5 0 9 10
6 13 0 12
8 8 9 0
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 10
int N = 0;
int map[MAXN + 10][MAXN + 10] = {0,};
int visited[MAXN + 10] = {0,};              // 방문도시 표시
int total_sum = (1<<30);

void InputData(void){
    scanf(" %d", &N);
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            scanf(" %d", &map[i][j]);
        }
    } 
}

void DFS(int index, int from, int cost_sum, int start){
    //0. 가지치기
    if (cost_sum >= total_sum) return;

    //1. 종료조건
    if(index == N-1){
        if(map[from][start] == 0) return;
        if(cost_sum + map[from][start] < total_sum){
            total_sum = cost_sum + map[from][start];
            return;
        }
    }

    //2. 재귀조건
    if(index == 0) visited[from] = 1;

    for(int i = 1; i <= N; i++){
        if (map[from][i] == 0 || visited[i] == 1) continue;
        if (i == from) continue;
        visited[i] = 1;
        DFS(index+1, i, cost_sum + map[from][i], start);
        visited[i] = 0;
    }
}

int main(void){
    InputData();
    for(int i = 1; i <= N; i++){
        DFS(0, i, 0, i);
    }
    printf("%d\n", total_sum);
    return 0;
}