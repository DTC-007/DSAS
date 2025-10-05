#include <stdlib.h>
#include <stdio.h>

#define SIZE 9  //定义哈希表的大小

typedef struct Element {   //这里用一个Element将值包装一下
    int key;    //这里元素设定为int
} * E;

typedef struct HashTable{   //这里把数组封装为一个哈希表
    E * table;
} * HashTable;

int hash(int key){   //哈希函数
    return key % SIZE;
}

void init(HashTable hashTable){   //初始化函数
    hashTable->table = malloc(sizeof(E) * SIZE);
    for (int i = 0; i < SIZE; ++i)
        hashTable->table[i] = NULL;
}

void insert(HashTable hashTable, E element){   //插入操作，注意没考虑满的情况
    int hashCode = hash(element->key), count = 0;
    while (hashTable->table[hashCode]) {   //如果发现哈希冲突，那么需要继续寻找
        hashCode = hash(element->key + ++count);
    }
    hashTable->table[hashCode] = element;   //对号入座
}

_Bool find(HashTable hashTable, int key){
    int hashCode = hash(key), count = 0;   //首先计算元素的哈希值
    const int startIndex = hashCode;   //记录一下起始位置，要是转一圈回来了得停
    do {
        if(hashTable->table[hashCode]->key == key) return 1;  //如果找到就返回1
        hashCode = hash(key + ++count);
    } while (startIndex != hashCode && hashTable->table[hashCode]);  //没找到继续找
    return 0;
}

E create(int key){    //创建一个新的元素
    E e = malloc(sizeof(struct Element));
    e->key = key;
    return e;
}

int main() {
    struct HashTable hashTable;
    init(&hashTable);
    for (int i = 1; i <= 9; ++i) {
        insert(&hashTable, create(i * 9));
    }

    for (int i = 0; i < 9; ++i) {
        printf("%d ", hashTable.table[i]->key);
    }
}