
#ifndef NODE_MANIPULATION_H
#define NODE_MANIPULATION_H

#include <stdio.h>
#include <stdlib.h>

#endif

typedef struct tmp1 {
    char negative_integer;
    unsigned long digit_count;
} metaData;

typedef struct tmp2 {
	char digit; // highest should be 9
	struct tmp2 *left;
	struct tmp2 *right;
    struct tmp1 *data;
} node;

unsigned long get_branch_length(node* head) {
    unsigned long counter = 0;
    while (head != NULL) {
        counter++;
        head = head->right;
    }
    return counter;
}

void create_and_link_node(char value, node* leftLink, node* rightLink) {
    node* newNode = (node* ) calloc(1, sizeof(node));

    newNode->left = leftLink;
    newNode->right = rightLink;
    newNode->digit = value;
    newNode->data = NULL;

    if (leftLink != NULL) leftLink->right = newNode;
    if (rightLink != NULL) rightLink->left = newNode;

}

node* create_head(char value, char meta_negative) {
    node* head = (node* ) calloc(1, sizeof(node));
    metaData* data = (metaData* ) calloc(1, sizeof(metaData));

    head->left = NULL;
    head->right = NULL;
    head->digit = value;
    head->data = data;

    data->negative_integer = meta_negative;

    return head;
}

void free_all_nodes(node* head) {
    
    metaData* data = head->data;
    free(data);
    printf("[*] Meta data freed.\n");

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
/*
void print_branch_digit(node* head) {
    printf("\n----------\n");
    
    node* tmp = head;
    
    int preFillZeroCheck = 1;
    while (tmp != NULL) {
        if (preFillZeroCheck == 1 && head->digit == 0) {
            //printf("%d", tmp->digit);
            tmp = tmp->right;
        } else if (preFillZeroCheck == 1 && head->digit != 0) {
            preFillZeroCheck = 0;
            printf("%d", tmp->digit);
            tmp = tmp->right;
        } else {
            printf("%d", tmp->digit);
            tmp = tmp->right;
        }
    }
    printf("\n----------\n");
    printf("[*] Printing branch complete.\n");
}
*/
void print_branch_diagnostic(node* head) {
    printf("\n----------\n");

    node* tmp = head;
    metaData* data = head->data;
    
    if (data->negative_integer == 0) {
        printf("+");
    } else {
        printf("-");
    }

    while (tmp != NULL) {
        printf("%d", tmp->digit);
        tmp = tmp->right;
    }

    printf("\n----------\n");
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

node* create_branch(int length, int zeroPreFill, char meta_negative) {
	int tmp = -1;
	int count = length;
    /*
    while (count < 1 || count > 10) {
        printf("Digit count: ");
	    scanf("%d", &count);
    }
    */
	// safeguards.
	/*
    while (tmp < 0 || tmp > 9) {
        printf("\n> ");
	    scanf("%d", &tmp);
    }
    */
	
    node* head;
    node* tempNode;
	
    if (zeroPreFill != 0) { // create head according to zero prefill
        head = create_head(0, meta_negative);
        tempNode = head;
    }
    for (int i=0; i<zeroPreFill-1; i++) { // fill out the zeroes
        create_and_link_node(0, tempNode, NULL);
        tempNode = tempNode->right;
    } // all of this will never execute if zeroPreFill == 0

    while (tmp < 1 || tmp > 9) {
        printf("\n> ");
	    scanf("%d", &tmp);
    }
    if (zeroPreFill == 0) {
        head = create_head(tmp, meta_negative);
        tempNode = head;
    } else {
        create_and_link_node(tmp, tempNode, NULL);
        tempNode = tempNode->right;
    }

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


