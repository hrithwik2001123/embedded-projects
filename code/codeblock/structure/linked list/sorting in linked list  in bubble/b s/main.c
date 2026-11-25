#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;

};
 int count,t;
int main()
{

    struct node*head,*temp;
    struct node*head1;
    struct node*head2;
    head=(struct node *)malloc(sizeof(struct node));
    head1=(struct node *)malloc(sizeof(struct node));
    head2=(struct node *)malloc(sizeof(struct node));
    head->data=19;
    head1->data=18;
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
     temp=head;

    while(temp!=NULL)
    {
        temp=temp->next;
        count++;
    }
    printf("after sorting\n");
   for(int i=0;i<count;i++)
    {

        for(temp=head;temp->next!=NULL;temp=temp->next)
        {
            if(temp->data > temp->next->data)
            {
                t=temp->data;
                temp->data=temp->next->data;
                temp->next->data=t;
            }
        }

    }
    temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
    return 0;
}
