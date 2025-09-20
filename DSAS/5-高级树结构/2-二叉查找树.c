#include <stdio.h>
#include <stdlib.h>

typedef int E;

typedef struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
} * Node;

//创建结点
Node createNode(E element){
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->element = element;
    return node;
}

//插入结点
Node insert(Node root, E element){
    if(root){
        if(root->element > element)    //如果插入结点值小于当前结点，那么说明应该放到左边去
            root->left = insert(root->left, element);
        else if(root->element < element)    //如果插入结点值大于当前结点，那么说明应该放到右边去
            root->right = insert(root->right, element);
    } else {   //当结点为空时，说明已经找到插入的位置了，创建对应结点
        root = createNode(element);
    }
    return root;   //返回当前结点
}

void inOrder(Node root){
    if(root == NULL) return;
    inOrder(root->left);
    printf("%d ", root->element);
    inOrder(root->right);
}

Node find(Node root, E target){
    while (root) {
        if(root->element > target)    //如果要找的值比当前结点小，说明肯定在左边
            root = root->left;
        else if(root->element < target)   //如果要找的值比当前结点大，说明肯定在右边
            root = root->right;
        else
            return root;   //等于的话，说明找到了，就直接返回
    }
    return NULL;   //都找到底了还没有，那就是真没有了
}

Node findMax(Node root){   //查找最大值就更简单了，最右边的一定是最大的
    while (root && root->right)
        root = root->right;
    return root;
}

Node delete(Node root, E target){
    if(root == NULL) return NULL;   //都走到底了还是没有找到要删除的结点，说明没有，直接返回空
    if(root->element > target)   //这里的判断跟之前插入是一样的，继续往后找就完事，直到找到为止
        root->left = delete(root->left, target);
    else if(root->element < target)
        root->right = delete(root->right, target);
    else {   //这种情况就是找到了
        if(root->left && root->right) {   //先处理最麻烦的左右孩子都有的情况
            Node max = findMax(root->left);  //寻找左子树中最大的元素
            root->element = max->element;  //找到后将值替换
            root->left = delete(root->left, root->element);  //替换好后，以同样的方式去删除那个替换上来的结点
        } else {   //其他两种情况可以一起处理，只需要删除这个结点就行，然后将 root 指定为其中一个孩子，最后返回就完事
            Node tmp = root;
            if(root->right) {   //不是左边就是右边
                root = root->right;
            } else {
                root = root->left;
            }
            free(tmp);   //开删
        }
    }
    return root;   //返回最终的结点
}

int main() {
    Node root = NULL;   //插入后，得到根结点
    int arr[] = {18, 10, 7, 9, 15, 20, 22};
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        inOrder(root);//用中序遍历查看一下结果
        putchar('\n');
    }

//    while (1) {
//        E element;
//        scanf("%d", &element);
//        root = insert(root, element);
//        inOrder(root);//用中序遍历查看一下结果
//        putchar('\n');
//    }

    printf("%p\n", find(root, 9));//%p打印指针地址
    printf("%p\n", find(root, 17));

    delete(root,7);
    inOrder(root);  //查看删除结果
}