#include <stdio.h>
#include <stdlib.h>


#define CMP_EQ(a,b) ((a) == (b))
#define CMP_LT(a,b) ((a) < (b))
#define CMP_GT(a,b) ((a) > (b))

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;
//создать новый узел по родителю
Node* getFreeNode(int value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

/*
    ВСТАВКА НОВОГО УЗЛА
    1) Дерево пустое. В этом случае новый узел становится корнем ДДП.
    2) Новое значение меньше корневого. В этом случае значение должно быть вставлено слева. Если слева уже стоит элемент, то повторяем эту же операцию, только в качестве корневого узла рассматриваем левый узел. Если слева нет элемента, то добавляем новый узел.
    3) Новое значение больше корневого. В этом случае новое значение должно быть вставлено справа. Если справа уже стоит элемент, то повторяем операцию, только в качестве корневого рассматриваем правый узел. Если справа узла нет, то вставляем новый узел.
*/
void Insert(Node **head, int value){
    Node *tmp = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }
    tmp = (*head);
    while(tmp){
        if (CMP_GT(value, tmp->data)){
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        } else if (CMP_LT(value, tmp->data)){
            if (tmp->left){
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        } else {
            exit(2);
        }
    }
}

Node *getMinNode(Node *root){
    while (root->left){
        root = root->left;
    }
    return root;
}

Node* getMaxNode(Node *root) {
    while (root->right) {
        root = root->right;
    }
    return root;
}

Node *getNodeByValue(Node *root, int value) {
    while (root){
        if (CMP_GT(root->data, value)){
            root = root->left;
            continue;
        } else if (CMP_LT(root->data, value)) {
            root = root->right;
            continue;
        } else {
            return root;
        }
    }

}

void removeNodeByPtr(Node *target) {
    if (target->left && target->right) {
        Node *localMax = getMaxNode(target->left);
        target->data = localMax->data;
        removeNodeByPtr(localMax);
        return;
    } else if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        } else {
            target->parent->right = target->left;
        }
    } else if (target->right) {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        } else {
            target->parent->left = target->right;
        }
    } else {
        if (target == target->parent->left) {
            target->parent->left = NULL;
        } else {
            target->parent->right = NULL;
        }
    }
    free(target);
}
//  удаляла узел по значению
void deleteValue(Node *root, int value) {
    Node *target = getNodeByValue(root, value);
    removeNodeByPtr(target);
}

void printTree(Node *root, const char *dir, int level) {
    if (root) {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}

void main() {
    Node *root = NULL;
    Insert(&root, 10);
    Insert(&root, 12);
    Insert(&root, 8);
    Insert(&root, 9);
    Insert(&root, 7);
    Insert(&root, 3);
    Insert(&root, 4);
    printTree(root, "root", 0);
    printf("max = %d\n", getMaxNode(root)->data);
    printf("min = %d\n", getMinNode(root)->data);
    deleteValue(root, 4);
    printf("parent of 7 is %d\n", getNodeByValue(root, 7)->parent->data);
    printTree(root, "root", 0);
    deleteValue(root, 8);
    printTree(root, "root", 0);
    printf("------------------\n");
    deleteValue(root, 10);
    printTree(root, "root", 0);

    //getch();
}
