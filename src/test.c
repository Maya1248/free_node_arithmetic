
#include "node_manipulation.h"
#include "node_arithmetic.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

	int l1,l2;

	printf("L1: ");
	scanf("%d", &l1);
	printf("L2: ");
	scanf("%d", &l2);

	node* head1;
	node* head2;

	if (l1 > l2) {
		head1 = create_branch(l1, 0);
		head2 = create_branch(l2, l1-l2); 
	} else if (l1 < l2) {
		head1 = create_branch(l1, l2-l1);
		head2 = create_branch(l2, 0); 
	} else {
		head1 = create_branch(l1, 0);
		head2 = create_branch(l2, 0); 
	}
	
	node* add_test = ADD(head1, head2, get_branch_length(head1));

	diagnostics(add_test);
	//print_branch_digit(add_test);
	print_branch_diagnostic(add_test);
	print_branch_diagnostic(head1);
	print_branch_diagnostic(head2);

	free_all_nodes(head1);
	free_all_nodes(head2);
	free_all_nodes(add_test);

	return 0;
}
