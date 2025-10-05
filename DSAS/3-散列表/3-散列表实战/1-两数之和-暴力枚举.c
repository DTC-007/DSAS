//https://leetcode.cn/problems/two-sum/
#include <stdlib.h>

int * result(int i, int j, int * returnSize){
    *returnSize = 2;
    int * result = malloc(sizeof(int) * 2);
    result[0] = i;
    result[1] = j;
    return result;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    for (int i = 0; i < numsSize; ++i) {
        for (int j = 0; j < numsSize; ++j) {
            if(j == i) continue;    //跳过自己和自己相加
            if(nums[i] + nums[j] == target)
                return result(i, j, returnSize);   //找到匹配就直接返回完事
        }
    }
    return NULL;   //无视即可，因为不可能
}