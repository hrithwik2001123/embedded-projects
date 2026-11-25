#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;

};
int main()
{

    struct node*head,*temp;
    struct node*head1;
    struct node*head2;
    head=(struct node *)malloc(sizeof(struct node));
    head1=(struct node *)malloc(sizeof(struct node));
    head2=(struct node *)malloc(sizeof(struct node));
    head->data=13;
    head1->data=14;
    head2->data=15;
    head->next=head1;
    head1->next=head2;
    head2->next=NULL;
  // printf("%d\n",head->data);
    temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
    return 0;
}
