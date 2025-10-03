//https://leetcode.cn/problems/range-sum-of-bst/
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//创建结点
struct TreeNode * createNode(int val){
    struct TreeNode * node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->val = val;
    return node;
}

//核心递归分治实现
struct TreeNode* buildTreeCore(int * preorder, int * inorder, int start, int end, int index){
    if(start > end) return NULL;   //如果都超出范围了，肯定不行
    if(start == end) return createNode(preorder[index]);   //如果已经到头了，那么直接创建结点返回即可
    struct TreeNode * node = createNode(preorder[index]);   //先从前序遍历中找到当前子树的根结点值，然后创建对应的结点
    int pos = 0;
    while (inorder[pos] != preorder[index]) pos++;   //找到中序的对应位置，从这个位置开始左右划分
    node->left = buildTreeCore(preorder, inorder, start, pos - 1, index+1);
    //当前结点的左子树按照同样的方式建立
    //因为前序遍历的下一个结点就是左子树的根结点，所以说这里给 index+1
    node->right = buildTreeCore(preorder, inorder, pos+1, end, index+(pos-start)+1);
    //当前结点的右子树按照同样的方式建立
    //最后一个 index 需要先跳过左子树的所有结点，才是右子树的根结点，所以这里加了个 pos-start，就是中序划分出来，左边有多少就减去多少
    return node;   //向上一级返回当前结点
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    return buildTreeCore(preorder, inorder, 0, preorderSize - 1, 0);
    //这里传入了前序和中序序列，并且通过 start 和 end 指定当前中序序列的处理范围，最后的一个 index 是前序遍历的对应头结点位置
}