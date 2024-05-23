
#include "node_manipulation.h"
#include "node_arithmetic.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

	node* head1 = create_branch();
	node* head2 = create_branch(); 
	
	node* add_test = ADD(head1, head2, get_branch_length(head1));

	diagnostics(add_test);
	print_branch(add_test);

	free_all_nodes(head1);
	free_all_nodes(head2);
	free_all_nodes(add_test);

	return 0;
}
