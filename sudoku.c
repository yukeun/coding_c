#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int N = 9;
char map[9 + 10][9 + 10] = {0,};
int map1[9 + 10][9 + 10] = {0,};
int visited_h[19][10] = {0,};
int visited_w[19][10] = {0,};
int index_num = 0;                  // 0으로 표시된 좌표개수
int stop_flag = 0;

struct QUE{
    int h;
    int w;
};

struct QUE coor[100 * 100 * 100 + 10];

void InputData(void){
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            scanf("%s", &map[i][j]);
            map1[i][j] = (int)(map[i][j] - '0');
            if (map1[i][j] == 0){
                // 좌표가 0이면 좌표추가해주기
                //printf("index_num = %d, h : %d, w : %d\n",index_num, i,j);
                coor[index_num].h = i;
                coor[index_num].w = j;
                index_num++;
            }
        }
    }
    return;
}

void PreProcessing(void){
    for(int h = 1; h <= 9; h++){
        for(int w =1; w <= 9; w++){
            if(map1[h][w]) visited_h[h][map1[h][w]] = 1;
        }
    }
    for(int w = 1; w <= 9; w++){
        for(int h = 1; h <= 9; h++){
            if(map1[h][w]) visited_w[map1[h][w]][w] = 1;
        }
    }
}

int square_search(int h, int w, int num) {
    int row_start = (h - 1) / 3 * 3 + 1;
    int col_start = (w - 1) / 3 * 3 + 1;
    
    for (int i = row_start; i < row_start + 3; i++) {
        for (int j = col_start; j < col_start + 3; j++) {
            if (map1[i][j] == num)
                return 0;
        }
    }
    
    return 1;
}

void DFS(int index, int h, int w){
    //index : 0으로 표시된 좌표갯수
    //0. 가지치기

    if (index == index_num){
        stop_flag = 1;
        return;
    }

    //1. 검증하기
    // 해당 설정한 조건이 visited에 위배되지 않는지 확인하기
    //printf("index : %d\n", index);
    for(int i = 1; i <= 9; i++){

        if(visited_h[h][i] == 0 && visited_w[i][w] == 0 && square_search(h, w, i) == 1)
        {
            //visited에 위배되지 않는다면, 그리고 정사각형에 위배되지 않는다면
            map1[h][w] = i; // 위배되지 않는다면 map 업데이트 해주기
            visited_h[h][i] = 1;
            visited_w[i][w] = 1;
           
            //print_map();
            DFS(index + 1, coor[index+1].h, coor[index+1].w);
            if(stop_flag) return;
            else{
                visited_h[h][i] = 0;
                visited_w[i][w] = 0;
                map1[h][w] = 0;
            }            
        }
        else continue;
    }
    return;
}


void print_map(void){
    for(int i = 1; i <= 9; i++){
        for(int j = 1; j <= 9; j++){
            printf("%d ", map1[i][j]);
        }
        printf("\n");
    }
    return ;
}

int main(void){
    InputData();
    PreProcessing();
    DFS(0,coor[0].h, coor[0].w);
    print_map();
    return 0;
}