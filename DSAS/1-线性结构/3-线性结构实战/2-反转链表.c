#include <stdio.h>
#include <stdlib.h>

//https://leetcode.cn/problems/reverse-linked-list/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode * newHead = NULL, * tmp;   //创建一个指针存放新的头结点（注意默认要为 NULL），和一个中间暂存指针
    while (head) {
        tmp = head->next;   //head为头结点，tmp为head下一结点
        head->next = newHead;   //第一次head下一结点指向空(断链)，后面循环指向上次取出结点
        newHead = head;     //newHead指向头结点
        head = tmp;     //head指向tmp结点
    }
    return newHead;
}