#include <stdio.h>
#define INF (1 << 30)

int N;
int case_cnt;
int h[1010];
int w[1010];
int min_dist = INF;
int temp[1010]; // 사건별 경찰차 번호 저장 배열
int result[1010];

int abs(int a) {
    return ((a < 0) ? -a : a);
}

void InputData(void) {
    scanf("%d", &N);
    scanf("%d", &case_cnt);
    for (int i = 0; i < case_cnt; i++) {
        scanf("%d %d", &h[i], &w[i]);
    }
}

void DFS(int idx, int h1, int w1, int h2, int w2, int sum) {
    // 1. 가지치기
    if (sum >= min_dist)
        return;

    // 2. 종료조건
    if (idx == case_cnt) {
        if (sum < min_dist) {
            min_dist = sum;
            // 경로 및 경찰차 할당 정보 저장
            for(int i = 0; i < idx; i++){
                result[i] = temp[i];
            }
        }
        return;
    }

    // 3. 재귀
    temp[idx] = 1;
    DFS(idx + 1, h[idx], w[idx], h2, w2, sum + abs(h1 - h[idx]) + abs(w1 - w[idx]));
    temp[idx] = 2;
    DFS(idx + 1, h1, w1, h[idx], w[idx], sum + abs(h2 - h[idx]) + abs(w2 - w[idx]));
}

int main(void) {
    InputData();
    DFS(0, 1, 1, N, N, 0);
    printf("%d\n", min_dist);

    // 사건별 경찰차 할당 정보 출력
    for (int i = 0; i < case_cnt; i++) {
        printf("%d\n", result[i]);
    }

    return 0;
}
