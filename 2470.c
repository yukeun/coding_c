#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N;          //2 <= N <= 100,000 => binary_search
long long liquid[100000 + 10];
long long result[2];
long long temp_value = 20000000001;

int static comp(const void *first, const void *second) {
    long long a = *((long long *)first);
    long long b = *((long long *)second);
    if (a > b) return 1;
    else return -1;
}

void InputData(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &liquid[i]);
    }
    qsort(liquid, N, sizeof(liquid[0]), comp);
}

void Binary_search(void) {
    int start = 0;
    int end = N - 1;
    while (start < end) {
        long long sum = liquid[start] + liquid[end];
        if (llabs(sum) < temp_value) {
            temp_value = llabs(sum);
            result[0] = liquid[start];
            result[1] = liquid[end];
        }
        if (sum < 0) start++;
        else end--;
    }
}

int main(void) {
    InputData();
    Binary_search();
    printf("%lld %lld\n", result[0], result[1]);
    return 0;
}
