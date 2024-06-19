
#ifndef NODE_MANIPULATION_H
#define NODE_MANIPULATION_H

#include "node_manipulation.h"

#include <stdio.h>
#include <stdlib.h>

#endif


node* generate_null_number(int length) {
    node* head = create_head(0, 0);
    node* tmp = head;
    
    for (int i=1; i<length; i++) {
        create_and_link_node(0, tmp, NULL);  // Do not worry, everything has been pre-set.
        tmp = tmp->right; // Become CURRENT node.
    }

    return head;
}

node* meta_handler(node* head1, node* head2, int length, char operation) {
    metaData* data1 = head1->data;
    metaData* data2 = head2->data;

    node* result;
    metaData* data_result;

    switch (operation) {
        case '+':
            if (data1->negative_integer == 0 && data2->negative_integer == 0) {
                result = ADD(head1, head2, length);
                data_result = result->data;
                data_result->negative_integer = 0;

            } else if (data1->negative_integer == 0 && data2->negative_integer == -1) {
                if (data1->digit_count >= data2->digit_count) {
                    result = SUBTRACT(head1, head2, length);
                    data_result = result->data;
                    data_result->negative_integer = 0;

                } else {
                    result = SUBTRACT(head2, head1, length);
                    data_result = result->data;
                    data_result->negative_integer = -1;

                }
                
            }

            break;
    }

    return result;
}

node* ADD(node* head1, node* head2, int length) { 
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

node* SUBTRACT(node* head1, node* head2, int length) {
    node* result = generate_null_number(length);

    metaData* data1 = head1->data;
    metaData* data2 = head2->data;

    
}