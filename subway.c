#include <stdio.h>
#define MAXN (100)
#define INF (1<<30)
int N, M;//지하철역수, 목적역
int S[MAXN+2][MAXN+2];//[s][e]=시간
int visited[MAXN+2] ={0,};
int path[MAXN+2] = {0,};
int min_time = 1000000000;
// M은 목적역이다.

int que[100 * 100 * 100 + 10];
int wp, rp;

void push(int before){
    que[wp++] = before;
}
int deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

void PRT(int m){
    if(m == 1) return;
    PRT(path[m]);
    printf("%d ", path[m]);
}
void BFS(void){
    // 시작역은 정해져 있엉??? 1번역이 숙소
    wp = rp = 0;
    for(int i = 0; i < MAXN + 2; i++){
        visited[i] = INF;
    }
    push(1);
    visited[1] = 0;
    path[1] = 0;
    while(!empty()){
        int cur = deque();
        for(int next=2; next <= N; next++){
            int time = visited[cur] + S[cur][next];
            if(visited[next] > time){
                push(next);
                visited[next] = time;
                path[next] = cur;
            }
        }
    }
    printf("%d\n", visited[M]);
    PRT(M);
    printf("%d",M);
}
// ㅇ이미 그래프가 만들어져 있다.

void InputData(void){
	scanf("%d %d", &N, &M);
	for (int s=1; s<=N; s++){
		for (int e=1; e<=N; e++){
			scanf("%d", &S[s][e]);
		}
	}
}

int main(void){
	InputData();//입력
    BFS();
	//여기서부터 작성
	return 0;
}