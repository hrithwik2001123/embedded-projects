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
        temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
    printf(" enter a position for deleting");
    int c;
    scanf("%d",&c);
    if(c==0)
    {
    temp=head;
    head=head->next;
     free(temp);
    }

    else{

        temp=head;
    for(int i=0;i<c-1&&temp!=NULL;i++)
    {

       temp=temp->next;
    }
    temp->next=temp->next->next;

    }

    temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
    return 0;
}
