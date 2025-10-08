#include <stdio.h>

#define INF 210000000   //表示无穷大权值
#define N 4     //顶点个数

int min(int a, int b){
    return a > b ? b : a;
}

void floyd(int matrix[N][N], int n){
    for (int k = 0; k < n; ++k)    //一共需要执行 K 轮
        for (int i = 0; i < n; ++i)   //i 和 j 从 0 开始就行了，直接全看，不会影响结果的
            for (int j = 0; j < n; ++j)
                matrix[i][j] = min(matrix[i][k] + matrix[k][j], matrix[i][j]);   //按照规则更新就行了
}

int main(){
    int matrix[N][N] = {{0, 1, INF, INF},
                        {4, 0, INF, 5},
                        {INF, 2, 0, INF},
                        {3, INF, 7, 0}};

    floyd(matrix, N);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            printf("%d ", matrix[i][j]);
        putchar('\n');
    }
}