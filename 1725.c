#include <stdio.h>
int N;
int arr[10010] = {0,};
long long max_area = 0;

struct STACK{
    int h;
    int idx;
};
struct STACK stack[100 * 100 * 100 + 10];
int sp = 0;

void push(int h, int idx){
    stack[++sp].h =h;
    stack[sp].idx = idx;
}
struct STACK top(void){
    return stack[sp];
};
int empty(void){
    return sp == 0;
}

void InputData(void){
    scanf(" %d", &N);
    for(int i = 0; i < N; i++){
        scanf(" %d", &arr[i]);
    }
}

void Solve(void){
    sp = 0;
    for(int i = 0; i < N; i++){
        int high = arr[i];
        int top_idx = i;
        while(top().h > high && (!empty())){
            top_idx = top().idx;
            long long area = top().h * (i- top_idx);
            //printf("top_h : %d, %d - top_idx  : %d, area : %d\n", top().h, i, i-top_idx, area);
            if (area > max_area) max_area = area;
            sp--;
        }
        push(high, top_idx);
    }
    while(!empty()){
        long long area = top().h * (N - top().idx);
        if(area > max_area) max_area = area;
        sp--;
    }
}

int main(void){
    InputData();
    Solve();
    printf("%lld\n", max_area);
    return 0;
}