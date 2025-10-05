//https://leetcode.cn/problems/validate-binary-search-tree/
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isValid(struct TreeNode* root, long min, long max){   //这里上界和下界用 long 表示，因为它的范围给到整个 int
    if(root == NULL) return true;   //到头了就直接返回真
    //如果左边不是空，并且左边还比当前结点值小的话，那肯定不是了
    //这里还需要判断是否正常高于下界
    if(root->left != NULL && (root->left->val >= root->val || root->left->val <= min))
        return false;
    //这里还需判断一下是否正常低于上界
    if(root->right != NULL && (root->right->val <= root->val || root->right->val >= max))
        return false;
    return isValid(root->left, min, root->val) && isValid(root->right, root->val, max);
    //注意往左走更新上界，往右走更新下界
}

bool isValidBST(struct TreeNode* root){
    return isValid(root, -2147483649, 2147483648);   //下界刚好比 int 少 1，上界刚好比 int 多 1
}