#include <stdio.h>
#define MAXN ((int)1e5)
int N;//빌딩수
int H[MAXN+10];//빌딩높이
int sol[MAXN+10];//각 빌딩에서 보이는 빌딩 번호

// sol에다가 저장하면 되겠네!

struct STACK{
    int index;
    int h;
};

struct STACK stk[100 * 100 * 100 + 10];
int sp;
void push(int index, int h){
    stk[++sp].index = index;
    stk[sp].h = h;
}
struct STACK top(void){
    return stk[sp];
};
void pop(void){
    sp--;
}
int empty(void){
    return sp == 0;
}
void InputData(void) {
	scanf("%d", &N);
	for (int i=1; i<=N; i++){
		scanf("%d", &H[i]);
	}
}

void Solve(void){
    // 1. 비어 있다면 push한다.
    for(int i = 1; i <= N; i++){
        int high = H[i];
        int index = i;
        while(!empty() && (top().h < high && top().index < index)){
            sol[top().index] = index;           // 빌딩 번호를 저장해야 하므로
            pop(); 
        }
        push(i, high);
    }
    while(!empty()){
        // 만약 보이는 빌딩이 없다면 0으로 선언해준다.
        sol[top().index] = 0;
        pop();
    }
}
void OutputData(void) {
	for (int i=1; i<=N; i++){
		printf("%d\n", sol[i]);
	}
}

int main(void) {
	InputData();//입력받는 부분
    Solve();
	//여기서부터 작성

	OutputData();//출력하는 부분
	return 0;
}