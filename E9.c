#include <stdio.h>

int N;              // 색종이 수
int X[100 + 10];    // 색종이의 왼쪽 변과 도화지의 왼쪽 변 사이의 거리
int Y[100 + 10];    // 색종이의 아래쪽 변과 도화지의 아래쪽 변 사이의 거리

void InputData(void) {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
}

int Solve(void) {
    int W[100][100] = {0};    // 도화지 배열 초기화
    int map[100][100] = {0};   // 검은색 직사각형의 높이 배열 초기화
    int answer = 0;           // 최대 넓이

    for (int t = 0; t < N; t++) {

        // 색종이를 도화지에 표시
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                W[99 - Y[t] - i][X[t] + j] = 1;
            }
        }
    }

    // 직사각형 높이를 계산해보자
    for(int h = 0; h < 100; h++){
        for(int w = 0; w < 100; w++){
            int i= 0;
            while(W[h+i][w] == 1 && map[h+i][w] == 0){
                map[h+i][w] = i+1;
                i++;
            }
        }
    }
    /*
    // 색종이 높이가 입력된 map 도화지 출력
    for(int h = 0; h < 100; h++)
    {
        for(int w = 0; w < 100; w++)
        {
            printf("%d ",map[h][w]);
        }
        printf("\n");
    }
    */
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (map[i][j] != 0) {
                int m = map[i][j];
                int w = 0;
                int k = j;

                while (k < 100 && map[i][k] != 0) {
                    m = (m < map[i][k]) ? m : map[i][k];                // 높이 누적합을 저장한다.
                    w += 1;                                             // 가로 누적합 저장
                    answer = (answer > m * w) ? answer : m * w;
                    k++;
                }
            }
        }
    }

    return answer;
}

int main(void) {
    int ans = -1;
    InputData();    // 입력받는 부분
    
    ans = Solve();
    
    printf("%d\n", ans);    // 출력하는 부분
    return 0;
}