//https://leetcode.cn/problems/sum-root-to-leaf-numbers/
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int sumNumbersImpl(struct TreeNode * root, int parent){
    if(root == NULL) return 0;   //如果到头了，直接返回 0
    int sum = root->val + parent * 10;   //因为是依次向后拼接，所以说直接将之前的值 x10 然后加上当前值即可
    if(!root->left && !root->right)    //如果是叶子结点，那么直接返回结果
        return sum;
    //否则按照同样的方式将左右的结果加起来
    return sumNumbersImpl(root->left, sum) + sumNumbersImpl(root->right,  sum);
}

int sumNumbers(struct TreeNode* root){
    return sumNumbersImpl(root, 0);
}