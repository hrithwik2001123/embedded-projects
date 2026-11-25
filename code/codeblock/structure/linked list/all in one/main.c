#include <stdio.h>
#include <stdlib.h>
struct node{
   int data;
   struct node*next;
   };
   int data,show_output,choice;
   struct node *head = NULL, *temp = NULL, *new_node,*n;
struct node*create_node()
{
    do{
       printf("enter the a data");
       scanf("%d",&data);
       struct node*new_node=(struct node*)malloc(sizeof(struct node));
       new_node->data=data;
       new_node->next=NULL;
    if(head==NULL)
    {
        head=new_node;

    }
    else
        {
        temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=new_node;

        }

        printf("Do you want to add another node? (1 for Yes / 0 for No): ");
        scanf("%d", &choice);
         }while(choice==1);

        printf("Do you want to show the linked list? (1 for Yes / 0 for No): ");
        scanf("%d", &show_output);

    if (show_output == 1) {
        printf("The linked list is:\n");
        temp = head;
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    } else {
        printf("You chose not to display the linked list.\n");
    }

    }
struct node*deleting()
{
    create_node();
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
}
struct node*insert_new()
{
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
}
struct node*Display()
{
   temp=head;
      while(temp!=NULL)
      {
          printf("%d,",temp->data);
          temp=temp->next;
      }
}
int main()
{
    while(1){
     int choice;
    printf("You have selected option e.g.1: Create Node. you enter 1 is it create a node\n ");
    printf("Choose an operation:\n");
    printf("1. Create Node based on your input\n");
    printf("2. Delete Node\n");
    printf("3. inserting Node\n");
    printf("4. sorting List\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            printf("You chose to Create Node.\n");
            create_node();
            break;
        case 2:
            printf("You chose to Delete Node.\n");
            deleting();
            break;
        case 3:
            printf("You chose to insert a Node.\n");
            insert_new();
            break;
        case 4:
            printf("You chose to Display List.\n");
            Display();
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
            break;
    }
    }

    return 0;
}


