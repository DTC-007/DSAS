#include <stdio.h>
#include <stdlib.h>

typedef char E;

struct TreeNode {
    E element;    //存放元素
    struct TreeNode * left;   //指向左子树的指针
    struct TreeNode * right;   //指向右子树的指针
};

typedef struct TreeNode * Node;

//前序遍历
void preOrder(Node root){   //传入的是二叉树的根结点
    if(root == NULL) return;   //如果走到 NULL 了，那就表示已经到头了，直接返回
    printf("%c", root->element);
    preOrder(root->left);
    preOrder(root->right);
}

//中序遍历
void inOrder(Node root){
    if(root == NULL) return;
    inOrder(root->left);  //先完成全部左子树的遍历
    printf("%c", root->element);   //等待左子树遍历完成之后再打印
    inOrder(root->right);   //然后就是对右子树进行遍历
}

//后序遍历
void postOrder(Node root){
    if(root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c", root->element);   //时机延迟到最后
}


int main(){
    Node a = malloc(sizeof(struct TreeNode));
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    Node f = malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';
    f->element = 'F';

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    c->left = NULL;
    d->left = e->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;

    preOrder(a);
    printf("\n");
    inOrder(a);
    printf("\n");
    postOrder(a);
    printf("\n");
}

