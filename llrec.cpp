#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot) {
        if (head == NULL) {
                smaller = NULL;
                larger = NULL;

                return;
        }
        else if (head->val > pivot) {
                larger = head;
                Node* next = head->next;
                head = NULL;
                llpivot(next, smaller, larger->next, pivot);
        }
        else {
                smaller = head;
                Node* next = head->next;
                head = NULL;
                llpivot(next, smaller->next, larger, pivot);
        }
}
