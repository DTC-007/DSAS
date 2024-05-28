#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct LNode {
    E element;
    struct LNode * next;
};

typedef struct LNode * Node;

struct Queue{
    Node front, rear;
};

typedef struct Queue * LinkedQueue;   //因为要存储首尾两个指针，所以这里封装一个新的结构体吧

//初始化队列
_Bool initQueue(LinkedQueue queue){
    Node node = malloc(sizeof(struct LNode));
    if(node == NULL) return 0;
    node->next = NULL;
    queue->front = queue->rear = node;   //一开始两个指针都是指向头结点的，表示队列为空
    return 1;
}

//入队
_Bool inQueue(LinkedQueue queue, E element){
    Node node = malloc(sizeof(struct LNode));
    if(node == NULL) return 0;
    node->next = NULL;
    node->element = element;
    queue->rear->next = node;   //先让尾结点的下一个指向新的结点
    queue->rear = node;   //然后让队尾指针指向新的尾结点
    return 1;
}

//打印队列数据
void printQueue(LinkedQueue queue){
    printf("<<< ");
    Node node = queue->front->next;
    while (1) {    //注意不能直接判空，因为前面我们没考虑，也就没将新结点 next 设定为 NULL
        printf("%d ", node->element);
        if(node == queue->rear) break;    //当已经打印最后一个元素后，再结束
        else node = node->next;
    }
    printf("<<<\n");
}

_Bool isEmpty(LinkedQueue queue){   //在出队之前需要先看看容量是否为空
    return queue->rear == queue->front;
}

//出队
E outQueue(LinkedQueue queue){
    E e = queue->front->next->element;  //队首下一元素为出队元素
    Node node = queue->front->next;
    queue->front->next = queue->front->next->next;  //直接让头结点指向下下个结点
    if(queue->rear == node) queue->rear = queue->front;   //如果队尾就是待出队的结点，那么队尾回到队首位置上
    free(node);   //释放内存
    return e;
}

int main(){
    struct Queue queue;
    initQueue(&queue);
    for (int i = 0; i < 5; ++i) {
        inQueue(&queue, i);
    }
    printQueue(&queue);
    while (!isEmpty(&queue)){
        printf("%d ", outQueue(&queue));
    }
}