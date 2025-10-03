//https://leetcode.cn/problems/jC7MId/description/
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
//力扣C语言提交不行，用C++在方法中使用代码可以提交
int result = -2147483648;    //使用一个全局变量来存储一下当前的最大值
int max(int a, int b){   //求两值最大
    return a > b ? a : b;
}

int maxValue(struct TreeNode* root){
    if(root == NULL) return 0;
    //先把左右两边走或是不走的情况计算一下，取出值最大的情况
    int leftMax = max(maxValue(root->left), 0);
    int rightMax = max(maxValue(root->right), 0);
    //因为要么只走左边，要么只走右边，要么左右都走，所以说我们计算一下最大情况下的结果
    int maxTmp = leftMax + rightMax + root->val;
    result = max(maxTmp, result);   //更新一下最大值
    //然后就是从上面下来的情况了，从上面下来要么左要么右，此时我们只需要返回左右最大的一个就行了
    return max(leftMax, rightMax) + root->val;  //注意还要加上当前结点的值，因为肯定要经过当前结点
}

int maxPathSum(struct TreeNode* root){
    maxValue(root);
    return result;   //最后返回完事之后最终得到的最大值
}