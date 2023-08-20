#include <stdio.h>
#include <stdlib.h>
#define MAXNM ((int)1e5)
int N, M;//소마리수, 잔디구간 개수
long long A[MAXNM+10];//잔디 구간 시작
long long B[MAXNM+10];//잔디 구간 끝

void InputData(void){
	scanf("%d %d", &N, &M);
	for (int i=0; i<M; i++){
		scanf("%lld %lld", &A[i], &B[i]);
	}
}

struct farm{
    long long start;
    long long end;
};
struct farm FARM[100 * 100 * 100 + 10] = {0,};

int static comp(struct farm* first, struct farm* second){
    if ((*(first)).start > (*(second)).start) return 1;
    else return -1;
}

void init_sort(void){
    for(int i = 0; i < M; i++){
        FARM[i].start = A[i];
        FARM[i].end = B[i];
    }
    qsort(FARM, M, sizeof(FARM[0]),comp);
}

long long Calculate(long long D){
    // 소가 N 보다 많으면 return 1을 함 ==> 즉, D를 늘려야한다.
    // 소가 N 보다 적으면 return 0을 함 ==> 즉, D를 줄여야한다.
    // 우선 구간안에 있어야 한다.
    // 시작지점은?
    long long current = FARM[0].start;            // 첫 시작점은 농장이 무조건 시작되는 곳으로 진행한다.
    long long cnt = 1;                            // 시작점이 농장의 시작점이므로 무조건 소 한마리 심고 간다!
    for(int i = 0; i < M; i++){
        // M개의 목장이 존재한다.
        long long start = FARM[i].start;
        long long end = FARM[i].end;

        //case 1. 현재 위치에서 D만큼 더했을 때 end 바깥으로 나갈 경우,
        if ((current + D) > end){
            continue;
        }
        // 현재 위치 + D가 end 이내에 들어 올때,
        if( (current + D) <= start){
            current = start;
            cnt++;      // 소 한마리 심어주자!
        }
        else{
            // 현재 위치 + D가 start <= current <= end 이내에 들어올 때
            current = current + D;
            cnt++;              // 소 한마리 심어주자!
        }
        while(current+D <= end){
            current += D;
            cnt++;
        }
    }
    return cnt;
}

long long Binary_Search(int start, int end){
    long long left = start;
    long long right = end;
    long long D = end;

    while(left <= right){
        long long mid = (left + right) / 2;
        long long count = Calculate(mid);
        if (count >= N){
            // D를 늘려야 한다.
            D = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return D;
}

int main(void){
	long long ans = -1;
	long long temp = 0;
    InputData();//입력
	//여기서 부터 작성
    init_sort();            // sort는 잘됐다.
    temp = FARM[M-1].end;
    ans = Binary_Search(0,temp);
	printf("%lld\n", ans);//출력
	return 0;
}