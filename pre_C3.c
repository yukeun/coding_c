#include <stdio.h>
#include <stdlib.h>

#define MAXN ((int)1e3)
int N;//연잎수
int A[MAXN+10];//연잎좌표
int total_cnt = 0;
void InputData(void){
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%d", &A[i]);
	}
}
//일단 정렬해
int static comp(int* first, int* second){
    int a = (*first);
    int b = (*second);
    if (a > b) return 1;
    else return -1;
}

void init_index(void){
    qsort(A, N, sizeof(A[0]), comp);
}

int find_upper(int start ,int end, int std){
    // start : 시작점, end 끝 인덱스, std : 기준인덱스?
    // 이진탐색을 시작하자
    int left = start;
    int right = end;
    int result = end;
    while(left <= right){
        int mid = (right + left) / 2;
        if (A[mid] <= std){
            left = mid + 1;
            result = mid;
        }
        else{
            right = mid - 1;
        }
    }
    return result;
}

int find_lower(int start, int end, int std){
    int left = start;
    int right = end;
    int result = end;
    while(left <= right){
        int mid = (left + right) / 2;
        if (A[mid] >= std){
            right = mid - 1;
            result = mid;
        }
        else left = mid + 1;
    }
    return result;
}


int Solve(void){
    int cnt = 0;
    int first_dist=  0;
    for(int i=0; i <N-2; i++){
        for(int j=i+1;j <N-1; j++){
            first_dist = A[j] - A[i];
            int low = find_lower(0, N-1, A[j]+first_dist);
            if (low < 0) break;
            int up = find_upper(0, N-1, A[j] + 2*first_dist);
            cnt += (up - low) + 1;
        }
    }
    return cnt;
}
int main(void){
	int ans = -1;
	InputData();//입력받는부분
    init_index();
    ans = Solve();
	//여기서부터작성

	printf("%d\n", ans);//출력하는부분
	return 0;
}