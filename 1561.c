#include <stdio.h>

#define MAX_TIME 60000000000
#define MAX_M 10000 + 1

int N, M;
int arrM[MAX_M];

int main() {
    // 입력 받기
    scanf("%d %d", &N, &M);
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        int sub_m;
        scanf("%d", &sub_m);
        arrM[m_idx] = sub_m;
    }

    long long left = 0;
    long long right = MAX_TIME;
    long long total_time = 0;

    // N이 M보다 작거나 같은 경우, 가장 마지막에 탑승하는 사람의 번호가 정답
    if (N <= M) {
        printf("%d\n", N);
        return 0;
    }

    // 이진 탐색을 통해 최소 시간을 구함
    while (left <= right) {
        long long mid = (left + right) / 2;
        long long person = M;
        for (int m_idx = 1; m_idx <= M; m_idx++) {
            person += mid / arrM[m_idx];
        }

        if (person >= N) {
            // 탑승한 사람의 수가 N보다 크거나 같으면 시간을 갱신하고 왼쪽 구간으로 이동
            total_time = mid;
            right = mid - 1;
        }
        else {
            // 탑승한 사람의 수가 N보다 작으면 오른쪽 구간으로 이동
            left = mid + 1;
        }
    }

    // total_time에 해당하는 시간 이전까지 탑승한 인원을 전부 더함
    long long person = M;
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        person += ((total_time - 1) / arrM[m_idx]);
    }

    // total_time에 해당하는 시간에 탑승한 사람을 확인하여 정답을 출력
    for (int m_idx = 1; m_idx <= M; m_idx++) {
        if (total_time % arrM[m_idx] == 0) person++;
        if (person == N) {
            printf("%d\n", m_idx);
            break;
        }
    }

    return 0;
}
