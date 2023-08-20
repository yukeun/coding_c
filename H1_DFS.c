#include <stdio.h>
#define MAXN (100)
int L;//정비를 받지 않고 갈수있는 최대거리
int N;//정비소 개수
int dist[MAXN+10];//정비소사이거리
int time[MAXN+10];//정비시간
int used[MAXN+10] = {0,};
int visited[10000+ 10][MAXN + 10] = {0,};
int temp[MAXN + 10] = {0,};
int sum_time = 100000000;
int total_cnt = 0;
int dist_sum[MAXN + 10] = {0,};
void InputData(void){
    scanf("%d", &L);
    scanf("%d", &N);
    for (int i=1; i<=N+1; i++){
        scanf("%d", &dist[i]);
    }
    for (int i=1; i<=N; i++){
        scanf("%d", &time[i]);
    }
    for(int i=1; i<=N+1;i++){
        dist_sum[i] += dist_sum[i-1] + dist[i];
        // printf("dist_sum[%d] : %d\n", i, dist_sum[i]);
        // 누적거리 : dist_sum;
    }
}
 
void DFS(int before, int cnt, int sum){
    //before : 어느 별에서 왔니
    // cnt : 이동횟수
    // sum : 정비시간 누적 합
    // 0. 가지치기
     
    if(sum >= sum_time){
        //printf("Fail! sum : %d\n", sum);
        return;}
    //1. 종료조건
    if(before >= N+1){
        // 도착지를 만났을 경우
        if(sum < sum_time){
            sum_time = sum;
            total_cnt = cnt;
            //printf("test");
            for(int i = 1; i <= total_cnt; i++)
            {
                visited[sum_time][i] = temp[i];
                //printf("%d ",temp[i]);
            }
            return;
        }
    }
    else if(dist_sum[N+1] - dist_sum[before] <= L){
        // 정비소를 전혀 방문하지 않아도 되는 경우 : 이동할 수 있는거리 <= 최대거
        sum_time = sum;
        total_cnt = cnt;
        for(int i = 1; i <= total_cnt; i++)
            {
                visited[sum_time][i] = temp[i];
                //printf("%d ",temp[i]);
            }
        return;
    }
    // 정비소 전혀 방문안해도되는 경우
     
    //2. 재귀조건
    // 먼저 어디서 왔는지를 알아야겠지?
    used[before] = 1;
    for(int i = before; i <= N+1;i++){
        // 지나 온길 가면 안되고,,,
        // 그리고 가려는 곳과 현재 있는 곳 까지의 거리차가 L 이하여야 한다.
        if(used[i] == 0 && ((dist_sum[i] - dist_sum[before]) < L)){
            //printf("i : %d, cnt+1:%d, time[%d]:%d\n",i,cnt+1,i,time[i]);
            temp[cnt+1] = i;
            DFS(i,cnt+1,sum + time[i]);
            temp[cnt+1] = 0;
             
        }   
    }
    used[before] = 0;
}
 
 
 
int main(void){
     
    InputData();//입력 받는 부분
 
    //여기서부터 작성
    DFS(0,0,0);
    if(sum_time == 0){
        printf("%d\n", sum_time);
    }
    else{
        printf("%d\n", sum_time);
        printf("%d\n", total_cnt);
        for(int i = 1; i <= total_cnt; i++){
            printf("%d ", visited[sum_time][i]);
        }
    }
     
    return 0;
}