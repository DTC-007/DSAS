//https://leetcode.cn/problems/two-sum/
#include <stdlib.h>

#define SIZE 128

typedef int K;
typedef int V;

typedef struct LNode {   //结点定义需要稍微修改一下，因为除了存关键字还需要存一下下标
    K key;
    V value;    //对应的下标
    struct LNode * next;
} * Node;

typedef struct HashTable{   //哈希表
    struct LNode * table;   //这个数组专门保存头结点
} * HashTable;

void init(HashTable hashTable){
    hashTable->table = malloc(sizeof(struct LNode) * SIZE);
    for (int i = 0; i < SIZE; ++i) {
        hashTable->table[i].key = -1;   //将头结点key置为-1，value也变成-1，next指向NULL
        hashTable->table[i].value = -1;
        hashTable->table[i].next = NULL;
    }
}

int hash(unsigned int key){  //因为哈希表用的数组，要是遇到负数的key，肯定不行，先把符号舍了再算
    return key % SIZE;
}

Node create(K key, V value){   //创建结点，跟之前差不多
    Node node = malloc(sizeof(struct LNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

void insert(HashTable hashTable, K key, V value){
    int hashCode = hash(key);
    Node head = hashTable->table + hashCode;
    while (head->next) head = head->next;
    head->next = create(key, value);   //这里同时保存关键字和对应的下标
}

Node find(HashTable hashTable, K key){
    int hashCode = hash(key);
    Node head = hashTable->table + hashCode;     //直接定位到对应位置
    while (head->next && head->next->key != key)   //直接看有没有下一个结点，并且下一个结点不是key
        head = head->next;  //继续往后找
    return head->next;   //出来之后要么到头了下一个是NULL，要么就是找到了，直接返回
}

int * result(int i, int j, int * returnSize){   //跟上面一样
    *returnSize = 2;
    int * result = malloc(sizeof(int) * 2);
    result[0] = i;
    result[1] = j;
    return result;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    struct HashTable table;    //初始化哈希表
    init(&table);
    for (int i = 0; i < numsSize; ++i) {   //挨个遍历
        Node node = find(&table, target - nums[i]);  //直接去哈希表里面寻找匹配的，如果有直接结束，没有就把当前的key丢进哈希表，之后如果遇到与其匹配的另一半，那么就直接成功了
        if(node != NULL) return result(i, node->value, returnSize);
        insert(&table, nums[i], i);
    }
    return NULL;   //无视即可，因为不可能
}