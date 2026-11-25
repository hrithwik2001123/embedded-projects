#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* create_node(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_at_first(struct node **head, int new_data) {
    struct node *new_node = create_node(new_data);
    new_node->next = *head;
    *head = new_node;
}

int main() {
    struct node *head = NULL, *temp = NULL, *new_node;
    int choice, data, show_output;

    do {
        printf("Enter the data for the new node: ");
        scanf("%d", &data);

        new_node = create_node(data);

        if (head == NULL) {
            head = new_node;
        } else {
            temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new_node;
        }

        printf("Do you want to add another node? (1 for Yes / 0 for No): ");
        scanf("%d", &choice);

    } while (choice == 1);


    printf("Enter a number you need to insert at the first position: ");
    int new_number;
    scanf("%d", &new_number);

    insert_at_first(&head, new_number);


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

    return 0;
}
