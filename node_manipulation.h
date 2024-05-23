
#ifndef NODE_MANIPULATION_H
#define NODE_MANIPULATION_H

#include <stdio.h>
#include <stdlib.h>




typedef struct tmp {
	char digit; // highest should be 9
	struct tmp *left;
	struct tmp *right;
} node;


void create_and_link_node(char value, node* leftLink, node* rightLink) {
    node* newNode = (node* ) calloc(1, sizeof(node));

    newNode->left = leftLink;
    newNode->right = rightLink;
    newNode->digit = value;

    if (leftLink != NULL) leftLink->right = newNode;
    if (rightLink != NULL) rightLink->left = newNode;

}

node* create_head(char value) {
    node* head = (node* ) calloc(1, sizeof(node));

    head->left = NULL;
    head->right = NULL;
    head->digit = value;

    return head;
}

void free_all_nodes(node* head) {
    
    while (head->right != NULL) {
        free(head->left);
        head = head->right;
    }
    free(head->left);
    free(head);

    printf("[*] All nodes freed. Branch successfuly purged.\n");
}

void free_node(node* temp) { // close off the neighbouring pointers, wipe the current node from existence; if not edge case, WILL create 2 seperate node branches
    if (temp->left != NULL) temp->left->right = NULL;
    if (temp->right != NULL) temp->right->left = NULL;

    printf("[*] Node (%p) freed.\n", temp);
    
    free(temp);
}

void print_branch(node* head) {
    printf("\n----------\n");
    
    node* tmp = head;

    while (tmp != NULL) {
        if (tmp == head && head->digit == 0) {
            //printf("%d", tmp->digit);
            tmp = tmp->right;
        } else {
            printf("%d", tmp->digit);
            tmp = tmp->right;
        }
    }
    printf("\n----------\n");
    printf("[*] Printing branch complete.\n");
}

void diagnostics(node* head) {
    int dIndex=0;

    while (head->right != NULL) {
        dIndex++;

        if (head != head->right->left) {
            printf("[!] ERROR: Broken chain at (%p), indexed position (%d).\n", head, dIndex);
            return;
        }

        head = head->right;
    }

    printf("[*] Basic diagnostics complete, no breaks found.\n");
}

node* create_branch() {
	int tmp = -1;
	int count = -1;

    while (count < 1 || count > 10) {
        printf("Digit count: ");
	    scanf("%d", &count);
    }

	// safeguards.
	
    while (tmp < 0 || tmp > 9) {
        printf("\n> ");
	    scanf("%d", &tmp);
    }
	
	node* head = create_head(tmp);
	node* tempNode = head;

	for (int i=0; i<count-1; i++) {

        tmp = -1;
		while (tmp < 0 || tmp > 9) {
            printf("\n> ");
	        scanf("%d", &tmp);
        }

		create_and_link_node(tmp, tempNode, NULL);
		tempNode = tempNode->right;
	}

	printf("\n[*] Node branch successfuly created.\n");

	return head;
}

int get_branch_length(node* head) {
    int counter = 0;
    while (head != NULL) {
        counter++;
        head = head->right;
    }
    return counter;
}

#endif