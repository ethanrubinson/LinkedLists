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

void TestLL();
void TestDLL();

int main(int argc, const char **argv)
{
	cerr << "Testing LinkedList implementation..." << endl;
	TestLL();

	cerr << "Testing DLinkedList implementation..." << endl;
	TestDLL();

	cerr << "Passed all tests. Everything looks good to me!" << endl;

	cin.get();
}

void TestLL() {
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

void TestDLL() {
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

  // Checking sort - Dan Tests
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
