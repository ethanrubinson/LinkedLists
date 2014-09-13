#include <iostream>

#include "LinkedList.h"
#include "DLinkedList.h"

using namespace std;

// This is a C++ precompiler macro that makes it easier to test whether the
// implementation of LinkedList is behaving as expected. If
// EXPECTED == ACTUAL then this macro does nothing. Otherwise,
// the macro prints an error message.
#define ASSERT_EQUAL(EXPECTED, ACTUAL) \
	if (EXPECTED != ACTUAL) { \
		cerr << __FILE__ << ":" << __LINE__ << ": "; \
		cerr << "Expected value \"" << EXPECTED << "\" does not match "; \
		cerr << "actual value \"" << ACTUAL << "\"" << endl; \
	}

// This macro does nothing if ACTUAL != NULL. However, if ACTUAL == NULL
// then it prints an error message.
#define ASSERT_NOT_NULL(ACTUAL) \
	if (ACTUAL == NULL) { \
		cerr << __FILE__ << ":" << __LINE__ << ": "; \
		cerr << "NULL pointer was passed to ASSERT_NOT_NULL" << endl; \
	}

void testLL();
void testLLAdditional_Ours();
void testLLAdditional_Susans();


void testDLL();
void testDLLAdditional_Ours();
void testDLLAdditional_Susans();

int main(int argc, const char **argv)
{
	cerr << "Testing LinkedList implementation..." << endl;
	testLL();
	testLLAdditional_Ours();
	testLLAdditional_Susans();

	cerr << "Testing DLinkedList implementation..." << endl;
	testDLL();
	testDLLAdditional_Ours();
	testDLLAdditional_Susans();

	cerr << "Checking for memory leaks..." <<endl;
	ASSERT_EQUAL(0, _CrtDumpMemoryLeaks());

	cerr << "Passed all tests. Everything looks good to me!" << endl;

	cin.get();
}

void testLL() {
	// Create a new empty list
	LinkedList list;
	ASSERT_EQUAL("", list.toString());

	// Add some new elements to the list
	ASSERT_EQUAL(true, list.insert(1, 0));
	ASSERT_EQUAL(true, list.insert(2, 1));
	ASSERT_EQUAL(true, list.insert(3, 2));

	ASSERT_EQUAL("1 2 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	// Test out the copy constructor
	LinkedList list2(list);
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	// Test out the list.getReverse() function
	LinkedList *reversed = list.getReverse();
	ASSERT_NOT_NULL(reversed);
	ASSERT_EQUAL("3 2 1", reversed->toString());
	ASSERT_EQUAL(3, reversed->size());

	// Delete an element from the list
	list.erase(2);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	// Try deleting an element that isn't present in the list
	list.erase(42);
	ASSERT_EQUAL("1 3", list.toString());

	// Do some insertions
	ASSERT_EQUAL(true, list.insert(0, 0));
	ASSERT_EQUAL("0 1 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	ASSERT_EQUAL(true, list.insert(0, 2));
	ASSERT_EQUAL("0 1 0 3", list.toString());
	ASSERT_EQUAL(4, list.size());

	// And now some deletions
	list.erase(0);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	list.erase(1);
	ASSERT_EQUAL("3", list.toString());
	ASSERT_EQUAL(1, list.size());

	list.erase(3);
	ASSERT_EQUAL("", list.toString());
	ASSERT_EQUAL(0, list.size());

	list.erase(3);
	ASSERT_EQUAL("", list.toString());
	ASSERT_EQUAL(0, list.size());

	// Make sure that "reversed" wasn't affected by the changes that were
	// made to "list"
	ASSERT_EQUAL("3 2 1", reversed->toString());

	// Make sure that "list2" wasn't affected by the changes that were
	// made to "list"
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());


	// Since list is a pointer, it will eating up memory until we manually
	// delete it. We don't use "reversed" after this point in the program,
	// so we need to tell the heap manager that we're done with it.
	delete reversed;
}

/*These are additional tests that we derived*/
void testLLAdditional_Ours() {
	LinkedList list3;
	list3.insert(3,0);
	list3.insert(2,1);
	list3.insert(1,2);

	list3.sort();

	ASSERT_EQUAL("1 2 3", list3.toString());

	list3.erase(1);
	list3.erase(2);
  
	ASSERT_EQUAL("3", list3.toString());

	list3.sort();
  
	ASSERT_EQUAL("3", list3.toString());

	list3.insert(1,0);
	list3.sort();

	ASSERT_EQUAL("1 3", list3.toString());

	list3.erase(1);
	list3.erase(3);

	list3.sort();

	list3.insert(3,0);
	list3.insert(8,0);
	list3.insert(10,0);

	list3.sort();

	ASSERT_EQUAL("3 8 10", list3.toString());

	LinkedList list4(list3);

	ASSERT_EQUAL("3 8 10", list4.toString());
	ASSERT_EQUAL(3, list4.size());
	ASSERT_EQUAL("3 8 10", list3.toString());

	list4.erase(10); 
	list4.erase(8);
	list4.erase(3);

	ASSERT_EQUAL("", list4.toString());

	ASSERT_EQUAL("3 8 10", list3.toString());
}

/*These are additional tests derived by Susan Chiang https://piazza.com/class/hy62ifd44wk3k4?cid=23 */
void testLLAdditional_Susans(){
	//Insert in non sequential order. 
	LinkedList l;
	ASSERT_EQUAL(true, l.insert(1,0));
	LinkedList l1(l);
	ASSERT_EQUAL("1",l1.toString());
	ASSERT_EQUAL(false,l.insert(2,2));
	ASSERT_EQUAL(true, l.insert(2, 1));
	LinkedList l4(l);
	ASSERT_EQUAL("1 2",l4.toString());
	ASSERT_EQUAL(true, l.insert(4,2));
	ASSERT_EQUAL(true, l.insert(3,2));
	ASSERT_EQUAL(true, l.insert(33,2));
	
	ASSERT_EQUAL("1 2 33 3 4", l.toString());

	//Insert into the front
	ASSERT_EQUAL(true, l.insert(22,0));

	ASSERT_EQUAL("22 1 2 33 3 4", l.toString());

    LinkedList l2;
	LinkedList l3(l2);
	ASSERT_EQUAL("",l3.toString());

    LinkedList * rev = l2.getReverse();
   	ASSERT_EQUAL("", rev->toString());
	delete rev; //Won't use this reference of rev later
	rev = l4.getReverse();
	ASSERT_EQUAL("2 1", rev->toString());
	delete rev;

    //Test that all instances are removed...
	ASSERT_EQUAL(true,l.insert(2,5));
	ASSERT_EQUAL("22 1 2 33 3 2 4", l.toString());

	l.erase(2);
	ASSERT_EQUAL("22 1 33 3 4", l.toString());
	ASSERT_EQUAL(5, l.size());
}

void testDLL() {
	// Create a new empty list
	DLinkedList list;
	ASSERT_EQUAL("", list.toString());

	// Add some new elements to the list
	ASSERT_EQUAL(true, list.insert(1, 0));
	ASSERT_EQUAL(true, list.insert(2, 1));
	ASSERT_EQUAL(true, list.insert(3, 2));

	ASSERT_EQUAL("1 2 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	// Test out the copy constructor
	DLinkedList list2(list);
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	// Test out the list.getReverse() function
	DLinkedList *reversed = list.getReverse();
	ASSERT_NOT_NULL(reversed);
	ASSERT_EQUAL("3 2 1", reversed->toString());
	ASSERT_EQUAL(3, reversed->size());

	// Delete an element from the list
	list.erase(2);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	// Try deleting an element that isn't present in the list
	list.erase(42);
	ASSERT_EQUAL("1 3", list.toString());

	// Do some insertions
	ASSERT_EQUAL(true, list.insert(0, 0));
	ASSERT_EQUAL("0 1 3", list.toString());
	ASSERT_EQUAL(3, list.size());

	ASSERT_EQUAL(true, list.insert(0, 2)); 
	ASSERT_EQUAL("0 1 0 3", list.toString());
	ASSERT_EQUAL(4, list.size());

	// And now some deletions
	list.erase(0);
	ASSERT_EQUAL("1 3", list.toString());
	ASSERT_EQUAL(2, list.size());

	list.erase(1);
	ASSERT_EQUAL("3", list.toString());
	ASSERT_EQUAL(1, list.size());

	list.erase(3);
	ASSERT_EQUAL("", list.toString());
	ASSERT_EQUAL(0, list.size());

	// Make sure that "reversed" wasn't affected by the changes that were
	// made to "list"
	ASSERT_EQUAL("3 2 1", reversed->toString());

	// Make sure that "list2" wasn't affected by the changes that were
	// made to "list"
	ASSERT_EQUAL("1 2 3", list2.toString());
	ASSERT_EQUAL(3, list2.size());

	// Since list is a pointer, it will eating up memory until we manually
	// delete it. We don't use "reversed" after this point in the program,
	// so we need to tell the heap manager that we're done with it.
	delete reversed;
}

/*These are additional tests that we derived*/
void testDLLAdditional_Ours() {
	DLinkedList list3;
	list3.insert(3,0);
	list3.insert(2,1);
	list3.insert(1,2);

	list3.sort();

	ASSERT_EQUAL("1 2 3", list3.toString());

	list3.erase(1);
	list3.erase(2);
  
	ASSERT_EQUAL("3", list3.toString());

	list3.sort();
  
	ASSERT_EQUAL("3", list3.toString());

	list3.insert(1,0);
	list3.sort();

	ASSERT_EQUAL("1 3", list3.toString());

	list3.erase(1);
	list3.erase(3);

	list3.sort();

	list3.insert(3,0);
	list3.insert(8,0);
	list3.insert(10,0);

	list3.sort();

	ASSERT_EQUAL("3 8 10", list3.toString());

	DLinkedList list4(list3);

	ASSERT_EQUAL("3 8 10", list4.toString());
	ASSERT_EQUAL(3, list4.size());
	ASSERT_EQUAL("3 8 10", list3.toString());

	list4.erase(10); 
	list4.erase(8);
	list4.erase(3);

	ASSERT_EQUAL("", list4.toString());

	ASSERT_EQUAL("3 8 10", list3.toString());
}

/*These are additional tests derived by Susan Chiang https://piazza.com/class/hy62ifd44wk3k4?cid=23 */
void testDLLAdditional_Susans(){
	//Insert in non sequential order. 
	DLinkedList l;
	ASSERT_EQUAL(true, l.insert(1,0));
	DLinkedList l1(l);
	ASSERT_EQUAL("1",l1.toString());
	ASSERT_EQUAL(false,l.insert(2,2));
	ASSERT_EQUAL(true, l.insert(2, 1));
	DLinkedList l4(l);
	ASSERT_EQUAL("1 2",l4.toString());
	ASSERT_EQUAL(true, l.insert(4,2));
	ASSERT_EQUAL(true, l.insert(3,2));
	
	ASSERT_EQUAL(true, l.insert(33,2));
	
	ASSERT_EQUAL("1 2 33 3 4", l.toString());

	//Insert into the front
	ASSERT_EQUAL(true, l.insert(22,0));

	ASSERT_EQUAL("22 1 2 33 3 4", l.toString());

    DLinkedList l2;
	DLinkedList l3(l2);
	ASSERT_EQUAL("",l3.toString());

    DLinkedList * rev = l2.getReverse();
   	ASSERT_EQUAL("", rev->toString());
	delete rev; //Won't use this reference of rev later
	rev = l4.getReverse();
	ASSERT_EQUAL("2 1", rev->toString());
	delete rev;

    //Test that all instances are removed...
	ASSERT_EQUAL(true,l.insert(2,5));
	ASSERT_EQUAL("22 1 2 33 3 2 4", l.toString());

	ASSERT_EQUAL(true,l.insert(88,2));
	ASSERT_EQUAL("22 1 88 2 33 3 2 4", l.toString());

	ASSERT_EQUAL(true,l.insert(98,3));
	ASSERT_EQUAL("22 1 88 98 2 33 3 2 4", l.toString());

	l.erase(2);
	ASSERT_EQUAL("22 1 88 98 33 3 4", l.toString());
	ASSERT_EQUAL(7, l.size());
}

