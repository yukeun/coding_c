#include <stdio.h>
#include <stdlib.h>

#define MAX_N (500 + 10)

int N;
int grids[MAX_N][MAX_N];
int visited[MAX_N][MAX_N];

struct QUE {
    int h;
    int w;
    int height;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;

// 절댓값을 반환하는 함수
int abs(int a) {
    return (a > 0 ? a : -a);
}

// BFS를 위한 상하좌우 이동 배열
int dh[] = {-1, 1, 0, 0};
int dw[] = {0, 0, -1, 1};

// 입력을 받는 함수
void InputData(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grids[i][j]);
        }
    }
}

// 큐에 좌표와 높이를 추가하는 함수
void push(int h, int w, int height) {
    visited[h][w] = 1;
    que[wp].h = h;
    que[wp].w = w;
    que[wp].height = height;
    wp++;
}

// 큐에서 좌표와 높이를 가져오는 함수
struct QUE deque(void) {
    return que[rp++];
}

// 큐가 비어있는지 확인하는 함수
int empty(void) {
    return wp == rp;
}

// BFS를 통해 탐색하며 방문한 농장의 개수를 세는 함수
int BFS(int h, int w, int mid) {
    wp = 0;
    rp = 0;
    push(h, w, grids[h][w]);
    int cnt = 1;

    while (!empty()) {
        struct QUE cur = deque();
        int cur_h = cur.h;
        int cur_w = cur.w;
        int cur_height = cur.height;

        // 최소 방문 개수 이상이면 cnt 반환
        if (cnt >= ((N * N + 1) / 2))
            return cnt;

        // 상하좌우 이동
        for (int i = 0; i < 4; i++) {
            int next_h = cur_h + dh[i];
            int next_w = cur_w + dw[i];

            // 좌표가 유효한지 확인하고 방문한 농장인지 확인
            if (next_h < 0 || next_h >= N || next_w < 0 || next_w >= N || visited[next_h][next_w] == 1)
                continue;

            // 현재 위치와 다음 위치의 높이 차이 계산
            int strength = abs(grids[next_h][next_w] - cur_height);

            // 높이 차이가 mid보다 크면 이동 불가
            if (strength > mid)
                continue;

            // 다음 위치를 큐에 추가하고 방문 처리
            push(next_h, next_w, grids[next_h][next_w]);
            cnt++;
        }
    }

    return cnt;
}

int main(void) {
    InputData(); // 입력 받기

    int max_farm = -1;
    int min_farm = 1000000001;

    // 최대, 최소 농장 높이를 구해서 이걸 기준으로 이진 탐색을 진행할 거임
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grids[i][j] > max_farm)
                max_farm = grids[i][j];
            if (grids[i][j] < min_farm)
                min_farm = grids[i][j];
        }
    }

    int sol = -1;
    int left = 0;
    int right = max_farm - min_farm;
    // 시작은 0 right 같은 경우는 최대 농장과 최소농장의 높이의 차로 입력할 것임
    while (left <= right) {
        // 처음에는 당영히 left가 right보다 크겠지
        //printf("left : %d, right : %d\n", left, right);
        int mid = (left + right) / 2;
        int flag = 0; // BFS 탐색 중단을 위한 플래그 변수

        // visited 배열 초기화(방문 여부를 초기화하기 위함)
        // visited 배열이 0일 때에만 BFS를 돌릴 수 있다.
        // 그럼 어떨 때 0이 되어야 하는거지???
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                visited[i][j] = 0;
            }
        }

        // 모든 농장에서 BFS 탐색 실행
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // 이미 방문한 농장인 경우 건너뜀
                if (visited[i][j] == 1)
                    continue;
                // (i,j)번째 좌표에서 BFS를 진행할 거임
                int count = BFS(i, j, mid);     // 반환 값은 해당 시작점을 기준으로 얼마나 많이 움직일 수 있는지 count 출력
                // 만약 입력한 높이차(mid)를 기준으로 반이상 도달했다면! mid 값을 갱신해서 다시 탐색을 진행해봐야 함!
                // 그렇지 않다면,다른 높이 기준으로 같은 mid를 가지고 탐색을 진행한다.
                // 왜? 다른 높이에서는 될 수도 있으니까!
                if (count >= ((N * N + 1) / 2)) {
                    flag = 1;
                    break;
                }
            }
            if (flag)
                break;
        }

        // flag 변수를 기준으로 이분 탐색 범위 조정
        // 만약 count >= 반 이면! mid를 좀 더 작게 만들어야 겠지?? 그렇기 때문에 right = mid - 1을 해준다.
        if (flag) {
            right = mid - 1;
            sol = mid;
        } else {
            // 도저히 기존 mid(높이차)로는 반 이상 움직이지 못한다?(모든 높이 기준!) => mid(높이차 = 파워)를 키워서 더 많이 움직일 수 있도록 해야함 
            left = mid + 1;
        }
    }

    printf("%d\n", sol); // 결과 출력

    return 0;
}
