#include <stdio.h>
#include <stdlib.h>

//https://leetcode.cn/problems/rotate-list/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (head == 0 || head->next == 0 || k == 0) return head;
    struct ListNode * node = head;
    int len = 1;
    while (node->next) {   //先计算链表的长度
        node = node->next;
        len++;
    }
    if(k == len) return head;   //如果 len 和 k 长度一样，那也没必要继续了

    node->next = head;   //将链表连起来变成循环的，一会再切割
    int i = len - k % len;  //计算头结点最终位置

    node = head;
    while (--i) node = node->next;
    head = node->next;    //找到新的头结点
    node->next = NULL;   //切断尾部与头部
    return head;  //返回新的头结点
}