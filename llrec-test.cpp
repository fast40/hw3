#include <iostream>
#include <fstream>
#include <cassert>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
        Node* h = NULL;
        ifstream ifile(filename);
        int v;
        if( ! (ifile >> v) ) return h;
        h = new Node(v, NULL);
        Node *t = h;
        while ( ifile >> v ) {
                t->next = new Node(v, NULL);
                t = t->next;
        }
        return h;
}

void print(Node* head)
{
        while(head) {
                cout << head->val << " ";
                head = head->next;
        }
        cout << endl;
}

void dealloc(Node* head)
{
        Node* temp;
        while(head) {
                temp = head->next;
                delete head;
                head = temp;
        }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------


bool lists_are_equal(Node* head1, Node* head2) {
        if (head1 == NULL) {
                return head2 == NULL;
        }
        else if (head2 == NULL) {
                return head1 == NULL;
        }

        return head1->val == head2->val && lists_are_equal(head1->next, head2->next);
}


template<typename T>
Node* create_list(T first) {
        return new Node(first, NULL); 
}

template<typename T, typename... Args>
Node* create_list(T first, Args... rest) {
        return new Node(first, create_list(rest...));
}

Node* copy_list(Node* head) {
        if (head == NULL) {
                return NULL; 
        }

        return new Node(head->val, copy_list(head->next));
}

bool is_even(int val) {
        return val % 2 == 0;
}

bool is_odd(int val) {
        return val % 2 == 1;
}

void print(char string[]) {
        cout << string << endl;
}

void test_filter() {
        Node* source = create_list(1, 2, 3, 10, 11, 12);
        Node* filtered = llfilter(source, is_odd);

        assert(lists_are_equal(filtered, create_list(2, 10, 12)));

        dealloc(source);
        dealloc(filtered);
}

void test_pivot() {
        Node* smaller;
        Node* larger;

        Node* source = create_list(1, 2, 3, 5, 6, 7);

        llpivot(source, smaller, larger, 4);

        assert(source == NULL);
        assert(lists_are_equal(smaller, create_list(1, 2, 3)));
        assert(lists_are_equal(larger, create_list(5, 6, 7)));

        dealloc(smaller);
        dealloc(larger);
        dealloc(source);
}

int main(int argc, char* argv[])
{
        if(argc < 2) {
                cout << "Please provide an input file" << endl;
                return 1;
        }

        // -----------------------------------------------
        // Feel free to update any code below this point
        // -----------------------------------------------

        Node* head = readList(argv[1]);
        cout << "Original list: ";
        print(head);

        test_filter();
        test_pivot();

        return 0;

}
