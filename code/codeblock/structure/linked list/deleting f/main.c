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
    printf(" if you want to deleting in begining y/n\n");
    char a,b,c;
    a='y';
    scanf("%c",&c);
    if(c==a)
    {
       temp=head;
       head=head->next;
       free(temp);
    }
    temp=head;
    while(temp!=NULL)
    {

        printf("%d\n",temp->data);
        temp=temp->next;
    }
   // printf("you need to deleting the last position Y/N?\n");
  //  scanf("%c",b);

    return 0;
}
