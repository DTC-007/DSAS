#include <stdio.h>

int main(){
    int size;
    scanf("%d", &size);   //读取需要求的 N
    int dp[size + 1];
    dp[0] = dp[1] = 1;   //没有结点或是只有一个结点直接得到 1
    for (int i = 2; i <= size; ++i) {
        dp[i] = 0;   //一开始先等于 0 再说
        for (int j = 0; j < i; ++j) {   //内层循环是为了计算所有情况，比如 i 等于 3，那么就从 j = 0 开始，计算 dp [0] 和 dp [2] 的结果，再计算 dp [1] 和 dp [1]...
            dp[i] += dp[j] * dp[i - j - 1];
        }
    }
    printf("%d", dp[size]);   //最后计算的结果就是 N 个结点构造的二叉树数量了
}
