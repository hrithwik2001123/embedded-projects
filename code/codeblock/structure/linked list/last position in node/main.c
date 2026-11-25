#include <stdio.h>
#include <stdlib.h>
struct node{
int data ;
struct node*next;
};
int main()
{
    struct node*head,*head1,*head2,*n,*temp;
    head=(struct node *)malloc(sizeof(struct node));
    head1=(struct node *)malloc(sizeof(struct node));
    head2=(struct node *)malloc(sizeof(struct node));
     n=(struct node *)malloc(sizeof(struct node));
    printf("you need to enter the 3 data ");
    scanf("%d",&head->data);
     scanf("%d",&head1->data);
      scanf("%d",&head2->data);
       head->next=head1;
    head1->next=head2;
    head2->next=NULL;
      temp=head;
      while(temp!=NULL)
      {
          printf("%d,",temp->data);
          temp=temp->next;
      }
      printf("\n");
      printf("enter a new data in the last position ");
      int n1;
      scanf("%d",&n1);
      n->data=n1;
      n->next=NULL;
         head2->next=n;
          n->next=NULL;
          temp=head;
      while(temp!=NULL)
      {
          printf("%d,",temp->data);
          temp=temp->next;
      }
    return 0;
}
