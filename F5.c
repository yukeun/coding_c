#include <stdio.h>
int N;//히스토그램수
int H[100000+10];//히스토그램 높이
 max_area = 0;
struct stack{
    long long index;
    long long h;      // 높이
};

struct stack STACK[100 * 100 * 100 + 10];
long long sp;             // stack pointer

void push(int index, int h){
    STACK[++sp].index = index;
    STACK[sp].h = h;
}
struct stack top(void){
    return STACK[sp];
};
void pop(void){
    sp--;
}
int empty(void){
    return sp == 0;
}

int InputData(void) {
    scanf("%d", &N);
    if (N == 0) return 0;
    
    for (int i=0; i<N; i++){
        scanf("%d", &H[i]);
    }
    return 1;
}

void Solve(void){
    for(int i = 0; i < N; i++){
        long long high = H[i];
        long long st_index = i;
        while(!empty() && top().h >= high){
            // 지금 집어 넣으려는 애보다 스택탐에 있는게 더 높다면
            //스택에서 꺼내서 스택에 있는거 다 넓이 계산
            long long temp_high = top().h;
            st_index = top().index;
            pop();          // 완전히 팝해버리고요
            long long temp_area = temp_high * (i - st_index);
            if (temp_area > max_area) max_area = temp_area;
        }
        push(st_index, high);
    }
    while(!empty()){
        long long index = top().index;
        long long high = top().h;
        pop();
        long long temp_area =((N) - index) * high;
        if (temp_area > max_area) max_area = temp_area;
    }
}

int main(void) {
    long long ans = -1;
    while(InputData()){//입력받는 부분
        max_area = 0;           // max_area 초기화
        Solve();
        memset(H,0,sizeof(H));
        ans = max_area;

        //여기서부터 작성

        printf("%lld\n", ans);//출력하는 부분
    }
    return 0;
}