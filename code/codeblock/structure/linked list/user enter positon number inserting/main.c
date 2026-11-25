#include <stdio.h>
#include <stdlib.h>
struct node{
int data ;
struct node*next;
};
int main()
{
    int data;
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
      printf(" which position you want to insert  ");
      int n1;
      scanf("%d",&n1);
      //in the case of zero
      if(n1==0)
      {
      printf("enter a new data");
       scanf("%d", &n->data);
       n->next = head;
        head = n;
      }
      else{
        temp=head;
      for( int i=1;i<n1-1&&temp!=NULL;i++)
      {

          temp=temp->next;
      }
      printf("enter a new data");
      scanf("%d",&data);
       n->data = data;
        n->next = temp->next;
        temp->next = n;
          temp=head;

      }
      //printing
      temp=head;
      while(temp!=NULL)
      {
          printf("%d,",temp->data);
          temp=temp->next;
      }
    return 0;
}
