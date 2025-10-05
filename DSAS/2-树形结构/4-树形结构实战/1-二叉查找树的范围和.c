//https://leetcode.cn/problems/range-sum-of-bst/
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int rangeSumBST(struct TreeNode* root, int low, int high){
    if(root == NULL) return 0;
    if(root->val > high)    //如果最大的值都比当前结点值小，那么肯定在左边才能找到
        return rangeSumBST(root->left, low, high);
    else if(root->val < low)   //如果最小值都比当前结点大，那么肯定在右边才能找到
        return rangeSumBST(root->right, low, high);
    else
        //这种情况肯定是在范围内了，将当前结点值加上左右的，再返回
        return root->val + rangeSumBST(root->right, low, high) + rangeSumBST(root->left, low, high);
}