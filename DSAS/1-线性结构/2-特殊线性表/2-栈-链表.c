#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct ListNode {
    E element;
    struct ListNode * next;
};

typedef struct ListNode * Node;

//初始化栈
void initStack(Node head){
    head->next = NULL;
}

//入栈
_Bool pushStack(Node head, E element){
    Node node = malloc(sizeof(struct ListNode));   //创建新的结点
    if(node == NULL) return 0;   //失败就返回 0
    node->element = element;   //设置元素
    node->next = head->next;   //将当前结点的下一个设定为头结点的下一个
    head->next = node;   //将头结点的下一个设定为当前结点
    return 1;
}

//打印栈数据
void printStack(Node head){
    head = head->next;
    while (head){
        printf("%d ", head->element);
        head = head->next;
    }
    printf("|");
    printf("\n");
}

_Bool isEmpty(Node head){
    return head->next == NULL;   //判断栈是否为空只需要看头结点下一个是否为 NULL 即可
}

//出栈
E popStack(Node head){
    Node top = head->next;  //栈顶元素为待出栈的元素
    head->next = head->next->next;  //头结点指向待出栈元素下一个
    E e = top->element;
    free(top);  //别忘了释放结点的内存
    return e;   //返回出栈元素
}

int main(){
    struct ListNode head;
    initStack(&head);
    for (int i = 0; i < 3; ++i) {
        pushStack(&head, i);
    }
    printStack(&head);
    while (!isEmpty(&head)) {
        printf("%d ", popStack(&head));   //将栈中所有元素依次出栈
    }
}