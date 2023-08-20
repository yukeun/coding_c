#include <stdio.h>
#define MAXN ((int)1e4)
int N, M;
int A[MAXN+10];         // 지방 예산안

void InputData(void){
	scanf("%d", &N);
	for (int i=0 ; i<N ; i++){
		scanf("%d", &A[i]);
	}
	scanf("%d", &M);
}

int Find_money(int money){
    // money : 상한액
    int country = M;
    for(int i=0; i < N; i++){
        if (A[i] < money){
            country -= A[i];
        }
        else{
            country -= money;
        }
    }
    if (country >= 0) return 0;                 // 예산이 남으므로 돈을 늘려야한다.
    else return 1;                                      // 예산이 부족하므로 돈을 줄여야한다.
}
int Binary_Search(int start, int end){
    int left = start;
    int right = end;
    int sol = end;

    while(left <= right){
        int mid = (right + left) / 2;
        int state = Find_money(mid);
        if (state){
            // state == 1이면 국가예산안 초과이므로 줄여야 한다.
            right = mid - 1;
        }
        else{
            left = mid + 1;
            sol = mid;
            //printf("origin mid : %d, update mid : %d\n", mid, (left + right) / 2);
        }
    }
    return sol;
}

int main(void){
	int ans = -1;
    int init_money = 0;
	InputData();// 입력받는 부분

	// 여기서부터 작성
    for(int i = 0;i < N; i++){
        if (A[i] > init_money) init_money = A[i];
    }
    ans = Binary_Search(0,init_money);

	printf("%d\n", ans);// 출력하는 부분
	return 0;
}