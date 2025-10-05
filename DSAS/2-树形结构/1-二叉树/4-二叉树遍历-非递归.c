#include <stdio.h>
#include <stdlib.h>

typedef char E;

struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
    int flag;   //后序遍历需要经历左右子树都被遍历才行，这里用 flag 存一下状态，0 表示左子树遍历完成，1 表示右子树遍历完成
};

typedef struct TreeNode * Node;

//------------- 栈 -------------------
typedef Node T;   //这里栈内元素类型定义为上面的 Node，也就是二叉树结点指针

struct StackNode {
    T element;
    struct StackNode * next;
};

typedef struct StackNode * SNode;  //这里命名为 SNode

void initStack(SNode head){
    head->next = NULL;
}

_Bool pushStack(SNode head, T element){
    SNode node = malloc(sizeof(struct StackNode));
    if(node == NULL) return 0;
    node->next = head->next;
    node->element = element;
    head->next = node;
    return 1;
}

_Bool isStackEmpty(SNode head){
    return head->next == NULL;
}

T peekStack(SNode head){   //这里新增一个 peek 操作，用于获取栈顶元素的值，但是不出栈，仅仅是值获取
    return head->next->element;
}

T popStack(SNode head){
    SNode top = head->next;
    head->next = head->next->next;
    T e = top->element;
    free(top);
    return e;
}

//--------------- 队列 ----------------
typedef Node T;   //还是将 Node 作为元素

struct QueueNode {
    T element;
    struct QueueNode * next;
};

typedef struct QueueNode * QNode;

struct Queue{
    QNode front, rear;
};

typedef struct Queue * LinkedQueue;

_Bool initQueue(LinkedQueue queue){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    queue->front = queue->rear = node;
    return 1;
}

_Bool offerQueue(LinkedQueue queue, T element){
    QNode node = malloc(sizeof(struct QueueNode));
    if(node == NULL) return 0;
    node->element = element;
    queue->rear->next = node;
    queue->rear = node;
    return 1;
}

_Bool isQueueEmpty(LinkedQueue queue){
    return queue->front == queue->rear;
}

T pollQueue(LinkedQueue queue){
    T e = queue->front->next->element;
    QNode node = queue->front->next;
    queue->front->next = queue->front->next->next;
    if(queue->rear == node) queue->rear = queue->front;
    free(node);
    return e;
}

//-----------------遍历-----------------
//前序遍历
void preOrder(Node root){
    struct StackNode stack;  //建栈
    initStack(&stack);
    while (root || !isStackEmpty(&stack)){   //两个条件，只有当栈空并且节点为 NULL 时才终止循环
        while (root) {    //按照我们的思路，先不断遍历左子树，直到没有为止
            pushStack(&stack, root);   //途中每经过一个结点，就将结点丢进栈中
            printf("%c", root->element);   //然后打印当前结点元素值
            root = root->left;  //继续遍历下一个左孩子结点
        }
        root = popStack(&stack);  //经过前面的循环，明确左子树全部走完了，接着就是右子树了
        root = root->right;  //得到右孩子，如果有右孩子，下一轮会重复上面的步骤；如果没有右孩子那么这里的 root 就被赋值为 NULL 了，下一轮开始会直接跳过上面的 while，继续出栈下一个结点再找右子树
    }
}

//中序遍历
void inOrder(Node root){
    struct StackNode stack;
    initStack(&stack);
    while (root || !isStackEmpty(&stack)){   //其他都不变
        while (root) {
            pushStack(&stack, root);
            root = root->left;
        }
        root = popStack(&stack);
        printf("%c", root->element);   //只需要将打印时机延后到左子树遍历完成
        root = root->right;
    }
}

//后序遍历
void postOrder(Node root){
    struct StackNode stack;
    initStack(&stack);
    while (root || !isStackEmpty(&stack)){   //其他都不变
        while (root) {
            pushStack(&stack, root);
            root->flag = 0;    //首次入栈时，只能代表左子树遍历完成，所以 flag 置 0
            root = root->left;
        }
        root = peekStack(&stack);   //注意这里只是获取到结点，并没有进行出栈操作，因为需要等待右子树遍历完才能出栈
        if(root->flag == 0) {    //如果仅仅遍历了左子树，那么 flag 就等于 0
            root->flag = 1;   //此时标记为 1 表示遍历右子树
            root = root->right;   //这里跟之前是一样的
        } else {
            printf("%c", root->element);   //当 flag 为 1 时走这边，此时左右都遍历完成了，这时再打印值出来
            popStack(&stack);   //这时再把对应的结点出栈，因为左右都完事了
            root = NULL;   //置为 NULL，下一轮直接跳过 while，然后继续取栈中剩余的结点，重复上述操作
        }
    }
}

//--------------------------------
//层序遍历
void levelOrder(Node root){
    struct Queue queue;   //建一个队列
    initQueue(&queue);
    offerQueue(&queue, root);  //先把根节点入队
    while (!isQueueEmpty(&queue)) {   //不断重复，直到队列空为止
        Node node = pollQueue(&queue);   //出队一个元素，打印值
        printf("%c", node->element);
        if(node->left)    //如果存在左右孩子的话
            offerQueue(&queue, node->left);  //记得将左右孩子入队，注意顺序，先左后右
        if(node->right)
            offerQueue(&queue, node->right);
    }
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
    levelOrder(a);
}