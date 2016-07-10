#include <bits/stdc++.h>
/* First node of the list is not used to store actual values*/
/* Last node has "next" pointer equal to zero */
typedef struct _node {
    int value;
    struct _node * next;
}Node,List;
/*Sets the end of list to it's start*/
void CreateList(List * list) {
    list->next=NULL;
};
void AddNode(List * list,int value) {
    Node * node;
    //if the end of list is found
    if(list->next==NULL) {
        //insert to the end
        list->next = (Node*) malloc(sizeof( List));
        list->next->value=value;
        list->next->next=NULL;
        return;
    };//end of looking up

    //if the right place is found
    if(list->next->value >= value)  {
        //insert there
        node = (Node*)malloc(sizeof( List));
        node->value = value;
        node->next = list->next;
        list->next = node;
    } else //keep searching - call the same for next node.
        AddNode(list->next,value);
};
int DelNode(List * list,int value) {
    Node * tmp;
    //if this is the end - quit.notging deleted.
    if(list->next==NULL) return 0;
    if(list->next->value==value) {
        //deleted something.return true.
        tmp = list->next->next;
        free(list->next);
        list->next = tmp;
        return 1;//else keep searching
    } else return DelNode(list->next,value);
};
void PrintList(List * list) { //thats just simple.
    Node * tmp;
    if(list->next == NULL)  {
        printf("List is empty");
        return;
    }
    tmp = list->next;
    while(tmp !=NULL) {
        printf("%d ",tmp->value);
        tmp=tmp->next;
    };
};
int CntList(List * list) { //even more simple
    int i = 0 ;
    Node * tmp = list;
    while(tmp->next != NULL) {
        i++;
        tmp=tmp->next;
    };
    return i;
};
int OccList(List * list,int value ) {
    if(list->next == NULL) return 0;
    if(list->next->value == value)
        return 1+OccList(list->next,value);
    if(list->next->value >value )
        return 0;
    return OccList(list->next,value);
};
int CdvList(List * list) {
    if(list->next == NULL)
        return 0;
    if(list->next->next ==NULL)
        return 1;
    if(list->next->value == list->next->next->value)
        return CdvList(list->next);
    else
        return 1+CdvList(list->next);
};
int RanList(List * list,int value1, int value2) {
    if(value1 >value2){
        printf("Invalid range\n");
            return -1;
    }
    if(list->next==NULL)
        return 0;
    if(list->next->value > value2 )
        return 0;
    if(list->next->value < value1 )
        return RanList(list->next,value1,value2);
    return RanList(list->next,value1,value2)+1;
};
int main () {
    char command[4];
    int param1,param2,tmp;
    List list;
    CreateList(&list);
    while(1) {
        printf("Enter command : ");
        scanf("%s",command);
        if(!strcmp(command,"pri") ) {
            PrintList(&list);
            printf("\n");
        };
        if(!strcmp(command,"ins") ) {
            scanf("%d",&param1);
            AddNode(&list,param1);
        };
        if(!strcmp(command,"del") ) {
            scanf("%d",&param1);
            if(!DelNode(&list,param1))
                printf("There is no given value in the list\n");
        };
        if(!strcmp(command,"cnt") ) {
            printf("Number of nodes : %d\n",CntList(&list));
        };
        if(!strcmp(command,"cdv") ) {
            printf("Number of unique nodes: %d\n",CdvList(&list));
        };
        if(!strcmp(command,"occ") ) {
            scanf("%d",&param1);
            printf("There are %d entries of %d in list\n",OccList(&list,param1),param1);
        };
        if(!strcmp(command,"ran") ) {
            scanf("%d %d",&param1,&param2);
            if( (tmp = RanList(&list,param1,param2))>=0)
                printf("Number of nodes within selected range is %d\n",tmp);
        };
        if(!strcmp(command,"end") )
            break;
    };
    return 0;
};
