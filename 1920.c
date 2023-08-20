/*N개의 정수 A[1], A[2], …, A[N]이 주어져 있을 때, 이 안에 X라는 정수가 존재하는지 알아내는 프로그램을 작성하시오.

입력
첫째 줄에 자연수 N(1 ≤ N ≤ 100,000)이 주어진다. 다음 줄에는 N개의 정수 A[1], A[2], …, A[N]이 주어진다. 다음 줄에는 M(1 ≤ M ≤ 100,000)이 주어진다. 다음 줄에는 M개의 수들이 주어지는데, 이 수들이 A안에 존재하는지 알아내면 된다. 모든 정수의 범위는 -231 보다 크거나 같고 231보다 작다.

출력
M개의 줄에 답을 출력한다. 존재하면 1을, 존재하지 않으면 0을 출력한다.

예제 입력 1 
5
4 1 5 2 3
5
1 3 7 9 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 0;
int M = 0;
long long A[100 * 100 * 100 + 10] = {0,};
long long B[100 * 100 * 100 + 10] = {0,};
void InputData(void){
    
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);
    for(int i = 0; i < M; i++){
        scanf("%d", &B[i]);
    }
    
}

int static comp(long long* first, long long* second){
    long long a = (*(first));
    long long b = (*(second));
    if (a > b) return 1;
    else return -1;
}

// 먼저 오름차순 정렬한 후, 이진탐색으로 탐색을 진행한다.
void init_array(void){
    qsort(A, N, sizeof(A[0]), comp);        // 오름차순 정렬
    /*for(int i = 0; i < N; i++){
        printf("%d ", A[i]);
    }
    printf("\n");*/
}


int Binary_Search(long long start, long long end, long long target){
    //target 원하는 값 (B)
    long long left = start;                           // 첫 left는 배열 내 최소 인덱스
    long long right = end;                            // 아마 첫 right는 배열 내 최대 인덱스

    while(left <= right){
        long long mid = (left + right) / 2;

        if (target == A[mid]) return 1;

        if (target < A[mid]){
            // target보다 크므로 mid 범위를 줄여야 한다.
            right = mid - 1;
        }
        else if (target > A[mid]){
            // target보다 mid 가 더 작으므로, mid를 증가시켜야한다.
            left = mid + 1;
        }
    }
    return 0;
}

int main(void){
    InputData();
    init_array();
    int result = 0;
    for(int i = 0; i < M; i++){
        result = Binary_Search(0, N, B[i]);
        printf("%d\n", result);
    }
    return 0;
}


