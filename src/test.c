
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


	node* head1;
	node* head2;

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
	
	node* add_test = ADD(head1, head2, get_branch_length(head1));

	diagnostics(add_test);
	diagnostics(head1);
	diagnostics(head2);
	//print_branch_digit(add_test);
	print_branch_diagnostic(add_test);
	print_branch_diagnostic(head1);
	print_branch_diagnostic(head2);

	free_all_nodes(head1);
	free_all_nodes(head2);
	free_all_nodes(add_test);

	return 0;
}
