#include <stdio.h>
#include <stdlib.h>
struct node{
int data;
struct node *next;
struct node *prev;
};
 struct node*head,*temp;
    struct node*head1;
    struct node*head2;
struct node* deleting (){
    printf(" enter a position for deleting");
    int c;
    scanf("%d",&c);
    if(c==0)
    {
    temp=head;
    head=head->next;
    if(head!=NULL)
    {
        head->prev=NULL;
    }
     free(temp);
    }

    else
    {
        for (int i = 0;i < c -1&&temp!= NULL; i++) {
            temp = temp->next;
        }

        if (temp == NULL) {
            printf("Position not found.\n");
            return;
        }
        if (temp->prev != NULL) {
            temp->prev->next = temp->next;
        }
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        free(temp);
    }

    struct node*t=head;
    while(t!=NULL)
    {

        printf("%d\n",t->data);
        t=t->next;
    }
}
int main()
{

    head=(struct node *)malloc(sizeof(struct node));
    head1=(struct node *)malloc(sizeof(struct node));
    head2=(struct node *)malloc(sizeof(struct node));
    head->data=13;
    head1->data=14;
    head2->data=15;
    head->next=head1;
    head1->next=head2;
    head2->next=NULL;
        temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
    deleting();
}
