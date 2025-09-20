#include <stdio.h>
#include <stdlib.h>

typedef char E;

typedef struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
    struct TreeNode * parent;   //指向双亲（父）结点
    int leftTag, rightTag;   //标志位，如果为 1 表示这一边指针指向的是线索，不为 1 就是正常的孩子结点
} * Node;

Node createNode(E element){   //单独写函数来创建结点
    Node node = malloc(sizeof(struct TreeNode));
    node->left = node->right = NULL;
    node->rightTag = node->leftTag = 0;
    node->element = element;
    return node;
}

Node pre = NULL;  //需要一个 pre 来保存后续结点的指向
//------------- 前序线索化遍历 -----------------
void preOrderThreaded(Node root){   //前序遍历线索化函数
    if(root == NULL) return;

    if(root->left == NULL) {   //首先判断当前结点左边是否为 NULL，如果是，那么指向上一个结点
        root->left = pre;
        root->leftTag = 1;  //记得修改标记
    }
    if(pre && pre->right == NULL) {  //然后是判断上一个结点的右边是否为 NULL，如果是那么进行线索化，指向当前结点
        pre->right = root;
        pre->rightTag = 1;  //记得修改标记
    }

    pre = root;   //每遍历完一个，需要更新一下 pre，表示上一个遍历的结点

    if(root->leftTag == 0)   //注意只有标志位是 0 才可以继续向下，否则就是线索了
        preOrderThreaded(root->left);
    if(root->rightTag == 0)
        preOrderThreaded(root->right);
}

void preOrder(Node root){  //前序遍历一棵线索化二叉树非常简单
    while (root) {   //到头为止
        printf("%c", root->element);   //因为是前序遍历，所以直接按顺序打印就行了
        if(root->leftTag == 0)
            root = root->left;   //如果是左孩子，那么就走左边
        else
            root = root->right;   //如果左边指向的不是孩子，而是线索，那么就直接走右边，因为右边无论是线索还是孩子，都要往这边走了
    }
}

//------------- 中序线索化遍历 -----------------
void inOrderThreaded(Node root){   //中序遍历线索化函数
    if(root == NULL) return;
    if(root->leftTag == 0)
        inOrderThreaded(root->left);

    //------  线索化 -------  现在放到中间去，其他的还是一样的
    if(root->left == NULL) {
        root->left = pre;
        root->leftTag = 1;
    }
    if(pre && pre->right == NULL) {
        pre->right = root;
        pre->rightTag = 1;
    }
    pre = root;
    //--------------------

    if(root->rightTag == 0)
        inOrderThreaded(root->right);
}

void inOrder(Node root){
    while (root) {   //因为中序遍历需要先完成左边，所以说要先走到最左边才行
        while (root && root->leftTag == 0)    //如果左边一直都不是线索，那么就一直往左找，直到找到一个左边是线索的为止，表示到头了
            root = root->left;

        printf("%c", root->element);   //到最左边了再打印，中序开始

        while (root && root->rightTag == 1) {   //打印完就该右边了，右边如果是线索化之后的结果，表示是下一个结点，那么就一路向前，直到不是为止
            root = root->right;
            printf("%c", root->element);   //注意按着线索往下就是中序的结果，所以说沿途需要打印
        }
        root = root->right;  //最后继续从右结点开始，重复上述操作
    }
}

//------------- 后序线索化遍历 -----------------
void postOrderThreaded(Node root){   //后序遍历线索化函数
    if(root == NULL) return;
    if(root->leftTag == 0) {
        postOrderThreaded(root->left);
        if(root->left) root->left->parent = root;  //左边完事之后，如果不为空，那么就设定父子关系
    }
    if(root->rightTag == 0) {
        postOrderThreaded(root->right);
        if(root->right) root->right->parent = root;   //右边完事之后，如果不为空，那么就设定父子关系
    }
    //------  线索化 -------   现在移到最后，就是后序遍历的线索化了
    if(root->left == NULL) {
        root->left = pre;
        root->leftTag = 1;
    }
    if(pre && pre->right == NULL) {
        pre->right = root;
        pre->rightTag = 1;
    }
    pre = root;
    //--------------------
}
//***
void postOrder(Node root){
    Node last = NULL, node = root;  //这里需要两个暂存指针，一个记录上一次遍历的结点，还有一个从 root 开始
    while (node) {
        while (node->left != last && node->leftTag == 0)    //依然是从整棵树最左边结点开始，和前面一样，只不过这里加入了防无限循环机制，看到下面就知道了
            node = node->left;
        while (node && node->rightTag == 1) {   //左边完了还有右边，如果右边是线索，那么直接一路向前，也是跟前面一样的
            printf("%c", node->element);   //沿途打印
            last = node;
            node = node->right;
        }
        //对根结点的特殊处理
        if (node == root && node->right == last) {
            //上面的操作完成之后，那么当前结点左右就结束了，此时就要去寻找其兄弟结点了，我们可以
            //直接通过 parent 拿到兄弟结点，但是如果当前结点是根结点，需要特殊处理，因为根结点没有父结点了
            printf("%c", node->element);
            return;   //根节点一定是最后一个，所以说直接返回就完事
        }
        while (node && node->right == last) {    //如果当前结点的右孩子就是上一个遍历的结点，那么一直向前就行
            printf("%c", node->element);   //直接打印当前结点
            last = node;
            node = node->parent;
        }
        //到这里只有一种情况了，是从左子树上来的，那么当前结点的右边要么是线索要么是右子树，所以直接向右就完事
        if(node && node->rightTag == 0) {  //如果不是线索，那就先走右边，如果是，等到下一轮再说
            node = node->right;
        }
    }
}

int main() {
    Node a = createNode('A');
    Node b = createNode('B');
    Node c = createNode('C');
    Node d = createNode('D');
    Node e = createNode('E');

    a->left = b;
    b->left = d;
    a->right = c;
    b->right = e;

    //前序
//    preOrderThreaded(a);
//    preOrder(a);

    //中序
//    inOrderThreaded(a);
//    inOrder(a);

    //后序
    postOrderThreaded(a);
    postOrder(a);
}