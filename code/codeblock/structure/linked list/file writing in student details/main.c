#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int roll_number;
    char name[10];
    int total_mark;
    struct node* next;
};
int count;
struct node *head = NULL, *temp = NULL, *new_node;
    int choice, rollno, mark, show_output;
    char name[10];

struct node* create_node(int rollnumber, char *name, int total) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->roll_number = rollnumber;
    strcpy(new_node->name, name);
    new_node->total_mark = total;
    new_node->next = NULL;
    count++;
    return new_node;
}
struct node*sorting()
{
    for(int i=0;i<count;i++)
    {

        for(temp=head;temp->next!=NULL;temp=temp->next)
        {
            if(temp->total_mark < temp->next->total_mark)
            {
               int  t=temp->total_mark;
                temp->total_mark=temp->next->total_mark;
                temp->next->total_mark=t;
            }
        }
    }
}
int main() {
    FILE *ptr = NULL;


    do {
        printf("Enter roll number: ");
        scanf("%d", &rollno);
        printf("Enter name: ");
        scanf("%s", name);
        printf("Enter mark: ");
        scanf("%d", &mark);

        new_node = create_node(rollno, name, mark);

        if (head == NULL) {
            head = new_node;
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }

        printf("Do you want to create another? (1 for Yes / 0 for No): ");
        scanf("%d", &choice);

    } while (choice == 1);

    printf("Do you want to print the output to a file? (1 for Yes / 0 for No): ");
    scanf("%d", &show_output);
    sorting(head);
    ptr = fopen("student_details.txt", "w");
    if (ptr == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    if (show_output == 1) {
        printf("Check the file 'student_details.txt'\n");
        temp = head;
        while (temp != NULL) {
            fprintf(ptr, "%d %s %d\n", temp->roll_number, temp->name, temp->total_mark);
            temp = temp->next;
        }
        fclose(ptr);
    } else {
        printf("You chose not to display the linked list.\n");
    }

    return 0;
}
