#include <stdio.h>
#include <string.h>

#define MAXN ((int)1e6)
#define MAXB (36)
char str[MAXN + 10];
char boom[MAXB + 10];
struct QUE{
    int index;
    int cnt;
};

struct QUE que[100 * 100 * 100 + 10];
int wp, rp;
void push(int index, int cnt){
    que[wp].index = index;
    que[wp].cnt = cnt;
    wp++;
}
struct QUE deque(void){
    return que[rp++];
}
int empty(void){
    return wp == rp;
}
void InputData(void) {
	scanf("%s", str);
	scanf("%s", boom);
}
int BFS(int index){
    wp = rp = 0;
    int cnt = 1;
    int char_len = strlen(boom);
    //printf("char_len : %d\n", char_len);
    push(index, 1);                 // 처음에는 cnt == 0;
    // 탐색을 시작하지...
    while(!empty()){
        struct QUE cur = deque();
        printf("Deque!\n");
        if (cur.cnt == char_len){
            printf("return 1\n");
            return 1;
        }
        if (str[cur.index+1] == boom[cnt]){
            push(cur.index+1, cur.cnt+1);               // 이게 틀렸네...
            cnt+=1;
        }
    }
    return 0;
}
int bridge(int index, int len){
    // 폭발된 문자열 자리를 연결시켜주는 것.
    // 앞 뒤로 검사해야 한다.
    // .자리부터 탐색을 시작한다.
    printf("start bridge\n");
    for(int i=index; i >= 0 ;i++){
        str[i] = str[i-1];
        str[i-1] = '.';
        printf("%s\n",str);
    }
}

int Bomb(int index){
    int len = strlen(boom);
    // printf("boom len : %d\n",len);
    for(int i = index; i < index + len; i++){
        str[i] = '.';   // 문자열을 폭발시키고 그자리를 . 으로 만들어버린다.
        printf("str[%d] : %c\n",i, str[i]);
    }
    bridge(index, len);
}

void Solve(void){
    int flag = 0;
    int len = strlen(str);
    while(!flag){
        for(int i = 0; i < len; i++){
            //printf("str[i] = %c, boom[0] : %c\n",str[i],boom[0]);
            if (str[i] == boom[0]){
                printf("start! BFS\n");
                int flag = BFS(i);
                if(flag){
                    printf("start!\n");
                    Bomb(i);
                    flag = 0;
                    break;}
                // 문자열을 폭발시켜야 한다.
                // visited에 표시된 곳을 폭발시키자.
            }
        }
        if(!flag) break;
    }
    if(str[0] == '.') printf("FRULA\n");
    else{
        for(int i = 0; i < len; i ++){
            if (str[i] != '.') printf("%c", str[i]);
        }
        printf("\n");
    }
}
int main(void) {
	InputData();
	Solve();
	return 0;
}