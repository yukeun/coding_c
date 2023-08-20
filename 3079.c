#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;                         // 입국 심사대 수
int M;                         // 친구들 수
long long time[100000];        // 각 입국심사대에서 걸리는 시간
long long result;

int static comp(const void* first, const void* second) {
    if (*(long long*)first > *(long long*)second) return 1;
    else return -1;
}

void InputData(void) {
    scanf("%d", &N);
    scanf("%d", &M);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &time[i]);
    }
    qsort(time, N, sizeof(time[0]), comp);
}

void Binary_search(void) {
    long long start = 1;
    long long end = time[0] * (long long)M;
    result = end;
    while (start <= end) {
        long long mid = (start + end) / 2;
        long long total = 0;
        for (int i = 0; i < N; i++) {
            total += (mid / time[i]);
        }

        if (total >= M) {
            if (mid < result) result = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }
}

int main(void) {
    InputData();
    Binary_search();
    printf("%lld\n", result);
    return 0;
}
