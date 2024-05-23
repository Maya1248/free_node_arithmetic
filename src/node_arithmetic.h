
#ifndef NODE_ARITHMETIC_H
#define NODE_ARITHMETIC_H

#include "node_manipulation.h"

#include <stdio.h>
#include <stdlib.h>



node* generate_null_number(int length) {
    node* head = create_head(0);
    node* tmp = head;
    
    for (int i=1; i<length; i++) {
        create_and_link_node(0, tmp, NULL);  // Do not worry, everything has been pre-set.
        tmp = tmp->right; // Become CURRENT node.
    }

    return head;
}

node* ADD(node* head1, node* head2, int length) { // For starters, assume they are of same length, 5
    node* result = generate_null_number(length+1); // extra space.
    
    // Prepare
    node* tmp_res = result->right; // extra space.
    node* tmp1 = head1;
    node* tmp2 = head2;

    while (tmp1->right != NULL) {
        tmp1 = tmp1->right;
        tmp2 = tmp2->right;
        tmp_res = tmp_res->right;
    }

    char buffer=0, carry=0;
    while (tmp1 != NULL) {
        buffer = tmp1->digit + tmp2->digit + carry;

        if (buffer > 9) {
            carry = 1;
            buffer = (char)(buffer % 10);
        } else {
            carry = 0;
        }

        tmp_res->digit = buffer;

        // Move on towards next digit.
        tmp_res = tmp_res->left;
        tmp1 = tmp1->left;
        tmp2 = tmp2->left;
        buffer = 0;
    }
    
    if (carry == 1) {
        tmp_res->digit = 1;
    }

    return result;
}

#endif