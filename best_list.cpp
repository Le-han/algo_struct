#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef struct Node {
    int value;
    struct Node *next;
} Node;

//создать список из массива
void fromArray(Node **head, int *arr, size_t size) {
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        push(head, arr[i]);
    } while(i--!=0);
}
//напечатать содержимое списка
void printLinkedList(const Node *head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}
////////////////////////////////////////////////////////C_STYLE REVERSE_LIST
/*
void ReverseList(Node **head){
    Node *new_head=0;
    //читаем элементы старого списка
    for(Node *pos = (*head); pos;){
    //пихаем в начало нового списка
        Node *save_next = pos->next;
        pos->next = new_head;
        new_head = pos;
        pos = save_next;
    }
    //обновляем голову
    (*head) = new_head;
}
*/
void ReverseList(Node *&head){
    Node *new_head=0;
    //читаем элементы старого списка
    for(Node *pos = head; pos;){
    //пихаем в начало нового списка
        Node *save_next = pos->next;
        pos->next = new_head;
        new_head = pos;
        pos = save_next;
    }
    //обновляем голову
    head = new_head;
}
//Add First Element
void push(Node **head, int data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

//Delete First Element
int pop(Node **head) {
    Node* prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->value;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

//вернуть указатель на n-ый элемент
Node* getNth(Node* head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

//вернуть последний элемент
Node* getLast(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

//вставить новый элемент в конец списка
void pushBack(Node *head, int value) {
    Node *last = getLast(head);
    Node *tmp = (Node*) malloc(sizeof(Node));
    tmp->value = value;
    tmp->next = NULL;
    last->next = tmp;
}

//возвращает указатель на предпоследний элемент
Node* getLastButOne(Node* head) {
    if (head == NULL) {
        exit(-2);
    }
    if (head->next == NULL) {
        return NULL;
    }
    while (head->next->next) {
        head = head->next;
    }
    return head;
}

//удалить последний элемент
int popBack(Node **head) {
    int res = 0;
    Node *lastbn = NULL;
    //Получили NULL
    if (!head) {
        exit(-1);
    }
    //Список пуст
    if (!(*head)) {
        exit(-1);
    }
    lastbn = getLastButOne(*head);
    //Если в списке один элемент
    if (lastbn == NULL) {
        res = (*head)->value;
        free(*head);
        *head = NULL;
    } else {
        res = lastbn->next->value;
        free(lastbn->next);
        lastbn->next = NULL;
    }
    return res;
}

//Вставить на n-ое место новое значение
void insert(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    //Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
    //ошибка выбрасываться не будет, произойдёт вставка в конец
    while (i < n && head->next) {
        head = head->next;
        i++;
    }
    tmp = (Node*) malloc(sizeof(Node));
    tmp->value = val;
    //Если это не последний элемент, то next перекидываем на следующий узел
    if (head->next) {
        tmp->next = head->next;
    //иначе на NULL
    } else {
        tmp->next = NULL;
    }
    head->next = tmp;
}

//Удаление n-го элемента списка
int deleteNth(Node **head, int n) {
    if (n == 0) {
        return pop(head);
    } else {
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        int val = elm->value;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

//Удалить список
void deleteList(Node **head) {
    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

/*создать список из массива
void fromArray(Node **head, int *arr, size_t size) {
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        push(head, arr[i]);
    } while(i--!=0);
}
*/
//Длина списка
int length(Node *head){
    int cnt = 0;
    while (head){
        head = head->next;
        ++cnt;
    }
    return cnt;
}
//создать массив элементов из списка
int* toArray(Node *head) {
    int leng = length(head);
    int *values = (int*) malloc(leng*sizeof(int));
    while (head) {
        values[--leng] = head->value;
        head = head->next;
    }
    return values;
}




int main() {
    Node* head = NULL;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};
    //Создаём список из массива
    fromArray(&head, arr, 10);
    printLinkedList(head);
    ReverseList(head);
    printLinkedList(head);
/*
    //Вставляем узел со значением 333 после 4-го элемента (станет пятым)
    insert(head, 4, 333);
    printLinkedList(head);

    pushBack(head, 11);
    pushBack(head, 12);
    pushBack(head, 13);
    pushBack(head, 14);
    printLinkedList(head);

    printf("%d\n", pop(&head));
    printf("%d\n", popBack(&head));

    printLinkedList(head);
    //Удаляем пятый элемент (индексация с нуля)
    deleteNth(&head, 4);
    printLinkedList(head);
    deleteList(&head);
*/
    return 0;
}
