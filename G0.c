#include <stdio.h>
#define MAXN ((int)1e5)
int N;//개수
int F[MAXN + 10];

void InputData(void){
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%d", &F[i]);
	}
}

int static comp(int* first, int* second){
    if ((*first) > (*second)) return 1;
    else return -1;
}

void init_sort(void){
    qsort(F, N, sizeof(F[0]), comp);
    for(int i = 0; i < N; i++){
        printf("%d ",F[i]);
    }
    printf("\n");
}

int Binary_Search(int start, int end){
    // end : N이라고 생각해
    // start : 탐색을 시작할 인덱스
    long long left = start;
    long long right = end;
    long long index = end;                    // 초반에는 end를 반환할 index라고 생각하기
    while(left <= right){
        long long mid = (left + right) / 2;

        if (F[start] >= 0.9*F[mid]){
            // 얘는 검사해야함
            // 범위를 더 좁혀주자
            left = mid + 1;
            index = mid;
        }
        else{
            right = mid - 1;
        }       
    }
    return index;
}

int main(void){
	long long ans = -1;
    long long sum = 0;
	InputData();// 입력받는 부분
    init_sort();
	// 여기서부터 작성
    for(int i = 0; i < N-1; i++){
        int index = Binary_Search(i, N-1);
        sum += (index - i);
    }
    ans = sum;
	printf("%lld\n", ans);// 출력하는 부분
	return 0;
}