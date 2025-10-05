#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct ListNode {
    E element;   //保存当前元素
    struct ListNode * next;   //指向下一个结点的指针
    struct ListNode * prev;   //指向上一个结点的指针
};

typedef struct ListNode * Node;   //为结点指针起别名，可以直接作为表实现

//初始化链表
void initList(Node node){
    node->next = node->prev = NULL;   //头结点默认下一个为 NULL
}

//链表插入
_Bool insertList(Node head, E element, int index){
    if(index < 1) return 0;   //跟单链表一样，还是先找到对应的位置
    while (--index) {
        head = head->next;
        if(head == NULL) return 0;
    }

    Node node = malloc(sizeof (struct ListNode));  //创建新的结点
    if(node == NULL) return 0;
    node->element = element;

    if(head->next) {   //首先处理后继结点，现在有两种情况，一种是后继结点不存在的情况，还有一种是后继结点存在的情况
        //如果存在则修改对应的两个指针
        node->next = head->next;    //插入元素后继指针指向要插入位置的元素
        head->next->prev = node;    //插入位置前驱结点指向插入元素
    } else {
        node->next = NULL;   //不存在直接将新结点的后继指针置为 NULL
    }

    head->next = node;  //前驱结点后继指针指向插入元素
    node->prev = head;  //插入元素前驱指针指向前驱结点
    return 1;
}

//链表删除
_Bool deleteList(Node head, int index){
    if(index < 1) return 0;   //跟单链表一样，还是先找到对应的位置
    while (--index) {
        head = head->next;
        if(head == NULL) return 0;
    }
    if(head->next == NULL) return 0;

    Node tmp = head->next;  //先拿到待删除结点
    if(head->next->next) {   //这里有两种情况待删除结点存在后继结点或是不存在
        head->next->next->prev = head;  //后继结点前驱指针指向待删除元素上个结点
        head->next = head->next->next;  //前驱结点后继指针指向待删除元素下个结点
    }else{
        head->next = NULL;   //相当于删的是最后一个结点，所以直接后继为 NULL 就完事
    }
    free(tmp);   //最后释放已删除结点的内存
    return 1;
}

int main() {
    struct ListNode head;
    initList(&head);
    for (int i = 1; i <= 5; ++i)  //插 5 个元素吧
        insertList(&head, i, i);
    insertList(&head, 0, 1);
    deleteList(&head, 1);

    Node node = &head;   //先来正向遍历一次
    do {
        node = node->next;
        printf("%d -> ", node->element);
    } while (node->next != NULL);

    printf("\n");   //再来反向遍历一次
    do {
        printf("%d -> ", node->element);
        node = node->prev;
    } while (node->prev != NULL);
}