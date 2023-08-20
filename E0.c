#include <stdio.h>
#include <stdlib.h>

int N;
int ID[500+10];
int S[500+10];
int E[500+10];
int sol[500+10];
void InputData(void){
    scanf("%d", &N);
    for (int i=0; i<N; i++){
        scanf("%d %d %d", &ID[i], &S[i], &E[i]);
    }
}

struct meet{
    int num;
    int str;
    int end;
};

struct meet Meeting[100 * 100 * 100 + 10];
struct meet answer[100 * 100 * 100 + 10];

// 구조체 정렬 어떻게 했더라???
int static comp(const struct meet* first, const struct meet* second){
    if ((*first).end > (*second).end) return 1;
    else return -1;
}

void init_comp(void){
    //printf("Before sorting...\n");
    for(int i = 0; i < N; i++){
        Meeting[i].num = ID[i];
        Meeting[i].str = S[i];
        Meeting[i].end = E[i];
        //printf("Meeting[%d] num : %d, str : %d, end : %d\n", i, Meeting[i].num, Meeting[i].str, Meeting[i].end);
    }
    //printf("\n");
    // 정렬하기
    qsort(Meeting, N, sizeof(Meeting[0]),comp);

    // 정렬 후
    /*printf("After sorting...\n");
    for(int i = 0; i < N; i++){
        printf("Meeting[%d] num : %d, str : %d, end : %d\n", i, Meeting[i].num, Meeting[i].str, Meeting[i].end);
    }*/
}

int Solve(void){
    //0. 초기화
    answer[0] = Meeting[0];
    int cnt = 1;
    for(int i = cnt; i < N; i++){
        // 다음 시작시간이 현재 종료시간보다 더 크다면 push하기
        if(Meeting[i].str >= answer[cnt-1].end){
            answer[cnt] = Meeting[i];
            cnt++;
        }
    }
    return cnt;
}

void OutputData(int ans){
    printf("%d\n", ans);
    for (int i=0; i<ans; i++){
        printf("%d ", sol[i]);
    }
}

int main(void){
    int ans = -1;

    InputData();// 입력받는 부분
    init_comp();
    //여기서부터 작성
    ans = Solve();
    printf("%d\n",ans);
    for(int i = 0; i < ans; i++){
        printf("%d ",answer[i].num);
    }
    //OutputData(ans);// 출력하는 부분
    return 0;
}