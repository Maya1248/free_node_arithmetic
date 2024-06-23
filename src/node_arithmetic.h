
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

node* SUBTRACT(node* head1, node* head2, int length) { // meta handler has ENSURED that this function only ever recieves head1 BIGGER OR EQUAL TO head2
    node* result = generate_null_number(length);

    // Prepare
    node* tmp_res = result;
    node* tmp1 = head1;
    node* tmp2 = head2;

    while (tmp1->right != NULL) {
        tmp1 = tmp1->right;
        tmp2 = tmp2->right;
        tmp_res = tmp_res->right;
    }

    char buffer=0, carry=0;
    while (tmp1 != NULL) {
        if (tmp1->digit - tmp2->digit - carry < 0) {
            buffer = tmp1->digit+10 - tmp2->digit - carry;
            carry = 1;
        } else {
            buffer = tmp1->digit - tmp2->digit - carry;
            carry = 0;
        }

        tmp_res->digit = buffer;

        // Move on towards next digit.
        tmp_res = tmp_res->left;
        tmp1 = tmp1->left;
        tmp2 = tmp2->left;
        buffer = 0;
    }

    return result;
}

int isBiggerThanOrEqualTo(node* head1, node* head2) { // it ignores negative/positive notation, all numbers are assumed positive in this function
    metaData* data1;
    metaData* data2;

    data1 = head1->data;
    data2 = head2->data;

    // real quick check
    if (data1->digit_count > data2->digit_count) {
        return 0;
    } else if (data1->digit_count < data2->digit_count) {
        return -1;
    }

    while (head1->right != NULL) { // if it comes to here, they inherently have same digit count
        if (head1->digit < head2->digit) {
            return -1;
        }

        head1 = head1->right;
        head2 = head2->right;
    }

    return 0;
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
                if (isBiggerThanOrEqualTo(head1, head2) == 0) {
                    result = SUBTRACT(head1, head2, length);
                    data_result = result->data;
                    data_result->negative_integer = 0;

                } else {
                    result = SUBTRACT(head2, head1, length);
                    data_result = result->data;
                    data_result->negative_integer = -1;

                }
                
            } else if (data1->negative_integer == -1 && data2->negative_integer == 0) { // basically switch them around and repeat as previous elseif did it, then negate result
                if (isBiggerThanOrEqualTo(head1, head2) == 0) {
                    result = SUBTRACT(head1, head2, length);
                    data_result = result->data;
                    data_result->negative_integer = 0;
                    
                } else {
                    result = SUBTRACT(head2, head1, length);
                    data_result = result->data;
                    data_result->negative_integer = -1;

                }
                
                if (data_result->negative_integer == -1) {
                    data_result->negative_integer = 0;
                } else {
                    data_result->negative_integer = -1;
                }

            } else if (data1->negative_integer == -1 && data2->negative_integer == -1) {
                result = ADD(head1, head2, length);
                data_result = result->data;
                data_result->negative_integer = -1;
            }

            break;
        
        case '-':
            if (data1->negative_integer == 0 && data2->negative_integer == 0) {
                if (isBiggerThanOrEqualTo(head1, head2) == 0) {
                    result = SUBTRACT(head1, head2, length);
                    data_result = result->data;
                    data_result->negative_integer = 0;

                } else {
                    result = SUBTRACT(head2, head1, length);
                    data_result = result->data;
                    data_result->negative_integer = -1;
                }

            } else if (data1->negative_integer == 0 && data2->negative_integer == -1) {
                result = ADD(head1, head2, length);
                data_result = result->data;
                data_result->negative_integer = 0;

            } else if (data1->negative_integer == -1 && data2->negative_integer == 0) {
                result = ADD(head1, head2, length);
                data_result = result->data;
                data_result->negative_integer = -1;

            } else if (data1-> negative_integer == -1 && data2->negative_integer == -1) {
                if (isBiggerThanOrEqualTo(head1, head2) == 0) {
                    result = SUBTRACT(head1, head2, length);
                    data_result = result->data;
                    data_result->negative_integer = 0;

                } else {
                    result = SUBTRACT(head2, head1, length);
                    data_result = result->data;
                    data_result->negative_integer = -1;

                }

                if (data_result->negative_integer == -1) {
                    data_result->negative_integer = 0;
                } else {
                    data_result->negative_integer = -1;
                }
            }

            break;
        default:
            printf("[-] Invalid operation!\n");
            return NULL;
            break;
    }

    return result;
}