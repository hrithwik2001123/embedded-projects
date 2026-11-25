#include <stdio.h>
#include <stdlib.h>
struct node{
int data ;
struct node*next;
};
int main()
{
    int count;
    struct node*head,*head1,*head2,*prev,*temp;
    head=(struct node *)malloc(sizeof(struct node));
    head1=(struct node *)malloc(sizeof(struct node));
    head2=(struct node *)malloc(sizeof(struct node));
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
          count++;
      }
      printf("\n the count is =%d\n",count);
      printf("deleting in the last position 1 for yes /0 for no ");

      int a;
      scanf("%d",&a);
      if (a==1)
     {
     temp=head;

     while(temp->next!=NULL)
     {

         prev=temp;
         temp=temp->next;
     }
     if(temp==head)
     {
         head=0;
     }
     else{
        prev->next=NULL;
        free(temp);
     }
     }

          temp=head;
      while(temp!=NULL)
      {
          printf("%d,",temp->data);
          temp=temp->next;
      }
    return 0;
}
