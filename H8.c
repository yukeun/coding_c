#include <stdio.h>
#include <string.h>
#define MAXN (50)
int N, M, K;//철도역수, 철도수, 추가로 연결시킬수있는 철도수
int S[MAXN + 10];
int E[MAXN + 10];
int visited[MAXN + 10] = {0,};
int graph[MAXN+10][MAXN+10] = {0,};
int coordinate[3][3] = {0,};
int total_cnt = 0;
struct QUE{
    int before;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

void push(int before){
    visited[before] = 1;
    que[wp].before = before;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}

void InputData(void) {
    scanf("%d %d %d", &N, &M, &K);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &S[i], &E[i]);
    }
}
void init_graph(void){
    for(int i = 0; i < M; i++){
        int start = S[i];
        int end = E[i];
        graph[start][end] = 1;
        graph[end][start] = 1;
    }
}
void print_graph(void){
    for(int h = 1; h <= N; h++){
        for(int w=1; w <= N; w++){
            printf("%d", graph[h][w]);
        }
        printf("\n");
    }
}

void BFS(int before){
    // 시작점은 1부터 시작인가? 아닌데, 
    // 처음에 빈 곳을 탐색한 후에, 그곳에 1넣어버리면 되자너~~~
    memset(visited, 0, sizeof(visited));        // visited 초기화
    wp = rp = 0;
    push(before);
    // visited 갱신했고요
    int cnt = 1;
    while(!empty()){
        struct QUE cur = deque();
        if(total_cnt < cnt){
            total_cnt = cnt;
        }
        for(int next = 1; next <= N; next++){
            if (cur.before == next) continue;
            if (visited[next] == 1) continue;
            if (graph[cur.before][next] == 1){
                push(next);
                cnt++;
            }
        }
    }
}

 
void Solve(void){
    int count = 0;
    for(int h = 1; h <= N; h++){
        for(int w= h; w <= N; w++){
            if(h != w && graph[h][w] == 0){
            // 0인 좌표를 확인했을 때,
                graph[h][w] = 1;
                graph[w][h] = 1;
                coordinate[count][0] = h;
                coordinate[count][1] = w;
                //printf("coordinate[%d][0] : %d, coordinate[%d][1] : %d\n",count, coordinate[count][0], count, coordinate[count][1]);
                count += 1;
            }
            if(count == K){
                //printf("hello\n");
                //memset(visited,0,sizeof(visited));
                //wp = rp =0;
                //push(coordinate[count-1][0]);
                //printf("coordinate[%d][0] : %d\n",count, coordinate[count][0]);
                BFS(coordinate[count-1][0]);

                // graph 원상복구 해주기
                for(int i = 0; i < count; i++){
                    int start = coordinate[i][0];
                    int end = coordinate[i][1];
                    graph[start][end] = 0;
                    graph[end][start] = 0;
                }
                count = 0;
            }
        }
    }
}
int main(void) {
	int ans = -1;
    InputData();//입력받는 부분
    init_graph();
    //print_graph();
	// 여기서부터 작성
    Solve();
    ans = total_cnt;
	
    printf("%d\n", ans);// 출력하는 부분
    return 0;
}