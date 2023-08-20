#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N = 0;
int capacity = 0;
int num = 0;
int result = 0;
int truck[10000 + 10] = {0,};

struct information{
    int start;
    int end;
    int value;
};

struct information INFORMATION[100 * 100 * 100 + 10] = {0,};

void InputData(void){
    scanf(" %d", &N);
    scanf(" %d", &capacity);
    scanf(" %d", &num);
    for(int i = 0; i < num; i++){
        scanf(" %d",&INFORMATION[i].start);
        scanf(" %d", &INFORMATION[i].end);
        scanf(" %d", &INFORMATION[i].value);
    }
}

// 구조체 정렬
int static comp(struct information *first, struct information *second){
    if ((*first).end > (*second).end) return 1;
    else return -1;
}

void sort(void){
    qsort(INFORMATION, num, sizeof(INFORMATION[0]), comp);
    /*for(int i = 0; i < num; i++){
        printf("%d %d %d\n", INFORMATION[i].start, INFORMATION[i].end, INFORMATION[i].value);
    }*/
}
void Solve(void){
    int flag = 0;
    int start, end, value;
    for(int i = 0; i < num; i++){
        //1. 먼저 출발지와 도착지, 및 전달해야할 택배 수를 전달받는다.
        start = INFORMATION[i].start;
        end = INFORMATION[i].end;
        value = INFORMATION[i].value;

        // 트럭 용량을 확인한다.
        int capable = value;
        for(int i = start; i < end; i++){  
            if ((capacity - truck[i]) <= 0){
                flag = 1;
                break;
            }
            if (capable > (capacity - truck[i])) capable = (capacity - truck[i]);
        }
        if(flag){
            flag = 0;
            continue;
        }
        // 트럭에 물건을 싣는다.
        for(int i = start; i < end; i++){
            truck[i] += capable;
        }
        result += capable;

    }
}

int main(void){
    InputData();
    sort();
    Solve();
    printf("%d\n", result);
    return 0;
}