#include <stdio.h>
#include <stdlib.h>

typedef char E;

struct TreeNode {
    E element;    //存放元素
    struct TreeNode * left;   //指向左子树的指针
    struct TreeNode * right;   //指向右子树的指针
};

typedef struct TreeNode * Node;

int main(){
    Node a = malloc(sizeof(struct TreeNode));   //依次创建好这五个结点
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';

    a->left = b;   //A 的左孩子是 B
    a->right = c;   //A 的右孩子是 C
    b->left = d;   //B 的左孩子是 D
    b->right = e;   //B 的右孩子是 E
    //别忘了把其他的结点改为 NULL
    c->left = c->right = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;

    printf("%c", a->left->left->element);   //比如现在想要获取 A 左孩子的左孩子，那么就可以直接 left 二连
}