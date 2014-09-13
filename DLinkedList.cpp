#include <sstream>
#include <iostream>

#include "DLinkedList.h"

/*Doubly Linked List default constructor*/
DLinkedList::DLinkedList() {
  _head = NULL;
  _tail = NULL;
  _size = 0;
}

/*Doubly Linked List constructor. Creates a copy of the provided list*/
DLinkedList::DLinkedList(const DLinkedList& original) {
  // Reference cannot be null 
  if (original._size == 0) {
    _head = NULL;
    _tail = NULL;
    _size = 0;
  }

  else {
    _head = new DNode(original._head->getValue());

    DNode* traverser = original._head->getNext();
    DNode* newList = _head;

    while (traverser != NULL) {
      newList->setNext(new DNode(traverser->getValue()));
      DNode* tmp = newList;
      newList = newList->getNext();
      newList->setPrev(tmp);
      traverser = traverser->getNext();
    }
    _tail = newList;
    _size = original._size;
  }
}

/*Doubly Linked List destructor.*/
DLinkedList::~DLinkedList() {
  DNode* traverser = _head;

  while(traverser != NULL) {
    DNode* next = traverser->getNext();
    delete traverser;
    traverser = next;
  }

  // Reset for sanity
  _head = NULL;
  _tail = NULL;
  _size = 0;
}

/*= a string representation of the Doubly Linked List*/
std::string DLinkedList::toString() const {
  std::ostringstream result;
  DNode* traverser = _head;

  while (traverser != NULL) {
    result << traverser->getValue();

    if (traverser->getNext() != NULL) {
      result << " ";
    }
    traverser = traverser->getNext();
  }

  return result.str();
}

/*= a new Doubly Linked List that is the reverse of the calling Doubly Linked List*/
DLinkedList* DLinkedList::getReverse() const {

  DLinkedList* newList = new DLinkedList();
  DNode* traverser = _head;

  while (traverser != NULL) {
    newList->insert(traverser->getValue(),0);
    traverser = traverser->getNext();
  }
  
  return newList;
}

/*Inserts an element into the Doubly Linked List at the specified offset.
  The offset must be <= the current size of the list.
  Returns a boolean indicating if the insertion was successful.*/
bool DLinkedList::insert(int value, int offset) {
  // IV: 0 <= offset <= _size 
  if (offset > _size || offset < 0) {
    return false;
  }

  DNode* newNode = new DNode(value);
  
  // Insert in empty list
  if (_size == 0) {
    _head = newNode;
    _tail = newNode;
    _size++;
    return true;
  }

  // Insert at the tail
  if (offset == _size) {
    newNode->setPrev(_tail);
    _tail->setNext(newNode);
    _tail = newNode;
    _size++;
    return true;
  }

  // Insert at the head 
  if(offset == 0) {
    newNode->setNext(_head);
    _head->setPrev(newNode);
    _head = newNode;
    _size++;
    return true;
  }

  DNode* current;

  // Start iteratign from back
  if (offset >= _size/2) {
    current = _tail;

    while (offset != _size - 1) {
	  current = current->getPrev();
	  offset++;
    }
  }

  // Start iterating from the front
  else {
    current = _head;
    while (offset != 0) {
      current = current->getNext();
      offset--;
    }
  }

  newNode->setNext(current);
  newNode->setPrev(current->getPrev());
  current->getPrev()->setNext(newNode);
  current->setPrev(newNode);
  _size++;
  return true;

}

/*Removes all elements with the specified value from the Doubly Linked List.
  Returns a boolean indicating if any elements were removed*/
bool DLinkedList::erase(int value) {

  DNode* current = _head;
  bool found = false;
  
  while (current != NULL) {
    
    // If found a match, delete 
    if (current->getValue() == value) {
      found = true;

      // Single node case 
      if (_size == 1) {
        DNode* delNode = current;
        _head = NULL;
        _tail = NULL;
        current = current->getNext();
        delete delNode;
        _size--;
      }

      // Deleting at the tail 
      else if (current == _tail) {
        DNode* delNode = _tail;
        _tail = delNode->getPrev();
        _tail->setNext(NULL);
        current = current->getNext();
        delete delNode;
        _size--;
      }
      // Deleting at the head 
      else if (current == _head) {
        DNode* delNode = _head;
        _head = delNode->getNext();
        _head->setPrev(NULL);
        current = current->getNext();
        delete delNode;
        _size--;
      }
      // Deleting arbitrary location 
      else {
        DNode* delNode = current;
        delNode->getNext()->setPrev(delNode->getPrev());
        delNode->getPrev()->setNext(delNode->getNext());
        current = current->getNext();
        delete delNode;
        _size--;
      }
    }
    else {
      current = current->getNext();
    }
  } 
  return found;
}

/*= the size of the Doubly Linked List.*/
int DLinkedList::size() const {
  return _size;
}

/*Sorts the Doubly Linked List in ascending order*/
void DLinkedList::sort() {
  if(_size <= 1) {
    return;
  }
  for (DNode *current = _head; current->getNext() != NULL; current = current->getNext()) {
    for (DNode *traverser = current->getNext(); traverser != NULL; traverser = traverser->getNext()) {
      if (current->getValue() > traverser->getValue()) {
        int data = current->getValue();
        current->setValue(traverser->getValue());
        traverser->setValue(data);
      }
    }
  }
}
