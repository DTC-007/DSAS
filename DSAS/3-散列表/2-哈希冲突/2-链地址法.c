#include <stdlib.h>
#include <stdio.h>

#define SIZE 9

typedef struct ListNode {   //结点定义
    int key;
    struct ListNode * next;
} * Node;

typedef struct HashTable{   //哈希表
    struct ListNode * table;   //这个数组专门保存头结点
} * HashTable;

void init(HashTable hashTable){
    hashTable->table = malloc(sizeof(struct ListNode) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        hashTable->table[i].key = -1;   //将头结点key置为-1，next指向NULL
        hashTable->table[i].next = NULL;
    }
}

int hash(int key){   //哈希函数
    return key % SIZE;
}

Node createNode(int key){   //创建结点专用函数
    Node node = malloc(sizeof(struct ListNode));
    node->key = key;
    node->next = NULL;
    return node;
}

void insert(HashTable hashTable, int key){
    int hashCode = hash(key);
    Node head = hashTable->table + hashCode;   //先计算哈希值，找到位置后直接往链表后面插入结点就完事了
    while (head->next) head = head->next;
    head->next = createNode(key);   //插入新的结点
}

_Bool find(HashTable hashTable, int key){
    int hashCode = hash(key);
    Node head = hashTable->table + hashCode;
    while (head->next && head->key != key)   //直到最后或是找到为止
        head = head->next;
    return head->key == key;   //直接返回是否找到
}

int main(){
    struct HashTable table;
    init(&table);

    insert(&table, 10);
    insert(&table, 19);
    insert(&table, 20);

    printf("%d\n", find(&table, 20));
    printf("%d\n", find(&table, 17));
    printf("%d\n", find(&table, 19));
}