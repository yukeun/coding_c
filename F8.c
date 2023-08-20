// 용돈관리
#include <stdio.h>

#define MAX_N (100000)

int N, M;
int need[MAX_N];

void Input_Data(void) {
	int i;
	scanf("%d %d", &N, &M);
	for (i = 0; i < N;i++) {
		scanf("%d", &need[i]);
	}
}
int Find_Money(int money){
    int wallet = 0;                 // 처음에 가지고 있는 돈은 뺴낸다.
    int cnt = 0;                    // 돈을 몇번 꺼냈는지
    for(int i =0; i < N; i++){
        if(money < need[i]) return 1;

        if (wallet < need[i]){
            wallet += money;            // 돈을 보충해준다.
            cnt++;
        }
        
        // 하루가 지나면 돈을 need[i]만큼 빼낸다.
        wallet -= need[i];
    }
    if (wallet < 0) cnt++;      // i일 동안 썼는데 돈이 마이너스면 한 번 더꺼내야 하므로
    if (cnt > M) return 1;      // 돈을 꺼낸 횟수가 M번 보다 많으면 보충할 돈을 늘려야 한다.
    else return 0;              // 돈을 꺼낸 횟수가 M번보다 적으면 보충할 돈을 줄여야한다. => 기록하기
}

int Binary_Search(int start, int end){
    int left = start;
    int right = end;
    int result = end;       // 최종 돈 보다 부족할 시,
    while(left <= right){
        int mid = (left + right) / 2;
        int state = Find_Money(mid);
        if (state){
            left = mid + 1;
        }
        else{
            right = mid -1;
            result = mid;
        }
    }
    return result;
}


int main(void) {
	int sol = -1;
    int sum_money = 0;
    int min_money = 100000000;
	// 입력 받는 부분
	Input_Data();
    // 맨 처음 시작은 각 요일의 합계를 먼저 구한 다음 합계부터 시작한다.
    for(int i = 0; i < N; i++){
        sum_money += need[i];
        if (min_money > need[i]) min_money = need[i];
    }
   //printf("sum_money : %d\n", sum_money);
    sol = Binary_Search(min_money, sum_money);
	// 출력하는 부분
	printf("%d\n", sol);

	return 0;
}