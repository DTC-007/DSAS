#include <stdio.h>
#include <stdlib.h>

typedef int E;

struct ListNode {
    E element;   //保存当前元素
    struct ListNode * next;   //指向下一个结点的指针
};

typedef struct ListNode * Node;   //为结点指针起别名，可以直接作为表实现

//初始化链表
void initList(Node node){
    node->next = NULL;   //初始化为空链表，头结点默认下一个为 NULL
}

//打印链表数据
void printList(Node head){
    while (head->next) {
        head = head->next;
        printf("%d ", head->element);   //因为头结点不存放数据，所以从第二个开始打印
    }
    printf("\n");
}

//链表插入
//head 是头结点，element 为待插入元素，index 是待插入下标
_Bool insertList(Node head, E element, int index){
    if(index < 1) return 0;   //如果插入的位置小于 1，那肯定是非法的
    while (--index) {   //通过--index 的方式不断向后寻找前驱结点
        head = head->next;   //正常情况下继续向后找
        if(head == NULL) return 0;
        //如果在寻找的过程中发现已经没有后续结点了，那么说明 index 超出可插入的范围了，也是非法的，直接润
    }

    Node node = malloc(sizeof (struct ListNode));
    if(node == NULL) return 0;   //创建一个新的结点，如果内存空间申请失败返回 0
    node->element = element;   //将元素保存到新创建的结点中
    node->next = head->next;   //先让新插入的节点指向原本位置上的这个结点
    head->next = node;   //接着将前驱结点指向新的这个结点
    return 1;
}

//链表删除
//head 就是头结点，index 依然是待删除的结点位序
_Bool deleteList(Node head, int index){
    if(index < 1) return 0;
    while (--index) {
        head = head->next;
        if(head == NULL) return 0;
    }
    if(head->next == NULL) return 0;  //注意删除的范围，如果前驱结点的下一个已经是 NULL 了，那么也说明超过了范围

    Node tmp = head->next;   //先拿到待删除结点
    head->next = head->next->next;   //直接让前驱结点指向下一个的下一个结点
    free(tmp);   //最后使用 free 函数释放掉待删除结点的内存
    return 1;
}

//按位置获取元素
E * getList(Node head, int index){
    if(index < 1) return NULL;   //如果小于 0 那肯定不合法，返回 NULL
    do {
        head = head->next;  //因为不算头结点，所以使用 do-while 语句
        if(head == NULL) return NULL;  //如果已经超出长度那肯定也不行
    } while (--index);  //到达 index 就结束
    return &head->element;
}

//查找元素位置
int findList(Node head, E element){
    head = head->next;    //先走到第一个结点
    int i = 1;   //计数器，从1开始
    while (head) {
        if(head->element == element) return i;   //如果找到，那么就返回 i
        head = head->next;   //没找到就继续向后看
        i++;   //i 记住要自增
    }
    return -1;   //都已经走到链表尾部了，那么就确实没找到了，返回-1
}

//链表长度
int sizeList(Node head){
    int i = 0;  //从 0 开始
    while (head->next) {   //如果下一个为 NULL 那就停止
        head = head->next;
        i++;   //每向后找一个就+1
    }
    return i;
}

int main() {
    struct ListNode head;   //这里创建一个新的头结点，头结点不存放任何元素，只做连接，连接整个链表
    initList(&head);  //先进行初始化
    for (int i = 1; i <= 3; ++i) {
        insertList(&head, i, i);   //依次插入 3 个元素
    }
    //插入
    insertList(&head, 0, 2);
    printList(&head);
    //删除
    deleteList(&head, 2);
    printList(&head);
    //按位置获取元素
    printf("%d\n", *getList(&head, 2));
    //查找元素位置
    printf("%d\n", findList(&head, 3));
    //链表长度
    printf("%d", sizeList(&head));
}