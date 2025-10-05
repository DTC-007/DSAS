#include <stdio.h>
#include <stdlib.h>

//https://leetcode.cn/problems/remove-duplicates-from-sorted-list/
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head){
    if(head == NULL) return head;  //首先如果进来的就是 NULL，那就不用再浪费时间了
    struct ListNode * node = head;  //这里用一个指针来表示当前所指向的结点
    while (node->next != NULL) {   //如果结点的下一个为空，就没必要再判断了，否则不断进行判断
        if(node->next->val == node->val) {  //如果下一个节点跟当前节点值一样，那么删除下一个节点
            node->next = node->next->next;
        } else {
            node = node->next;   //否则继续从下一个节点开始向后判断
        }
    }
    return head;   //最后原样返回头结点
}
