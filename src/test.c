
#include "node_manipulation.h"
#include "node_arithmetic.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

	int l1,l2;
	char neg_pos1, neg_pos2;

	printf("L1: ");
	scanf("%d", &l1);
	printf("L2: ");
	scanf("%d", &l2);
	printf("Num1 negative/positive? (-1 | 0): ");
	scanf("%d", &neg_pos1);
	printf("Num2 negative/positive? (-1 | 0): ");
	scanf("%d", &neg_pos2);


	// safeguards
	if (l1 < 1 || l2 < 1) {
		printf("[-] L1 and L2 must be bigger than 1\n");
		return -1;
	}
	if (neg_pos1 != 0 || neg_pos1 != -1 || neg_pos2 != 0 || neg_pos2 != -1) {
		printf("[-] Negative/Positive choice was invalid\n");
		return -1;
	}

	node* head1;
	node* head2;
	metaData* data1 = head1->data; // Meta data does NOT need to be freed, it has been handled by free_all_nodes()
	metaData* data2 = head2->data;

	if (l1 > l2) {
		head1 = create_branch(l1, 0, 0);
		head2 = create_branch(l2, l1-l2, 0); 
	} else if (l1 < l2) {
		head1 = create_branch(l1, l2-l1, 0);
		head2 = create_branch(l2, 0, 0); 
	} else {
		head1 = create_branch(l1, 0, 0);
		head2 = create_branch(l2, 0, 0); 
	}
	
	data1->negative_integer = neg_pos1;
	data2->negative_integer = neg_pos2;
	data1->digit_count = get_branch_length(head1);
	data2->digit_count = get_branch_length(head2);

	node* test = meta_handler(head1, head2, data1->digit_count, '+');
	//node* add_test = ADD(head1, head2, get_branch_length(head1));

	if (test == NULL) {
		free_all_nodes(head1);
		free_all_nodes(head2);
		return -1;
	}

	diagnostics(test);
	diagnostics(head1);
	diagnostics(head2);
	//print_branch_digit(add_test);
	print_branch_diagnostic(test);
	print_branch_diagnostic(head1);
	print_branch_diagnostic(head2);

	free_all_nodes(head1);
	free_all_nodes(head2);
	free_all_nodes(test);

	return 0;
}
