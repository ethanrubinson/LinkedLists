#include <sstream>
#include <iostream>

#include "DLinkedList.h"

DLinkedList::DLinkedList() {
  _head = NULL;
  _tail = NULL
  _size = 0;
}

DLinkedList::DLinkedList(const DlinkedList& original) {
  // Reference cannot be null 
  if (original._size == 0) {
    _head = NULL;
    _tail = NULL;
    _size = 0;
  }

  else {
    _head = new Node(original._first->getValue());

    Node* traverser = original._first->getNext();
    Node* newList = _first;

    while (traverser != NULL) {
      newList.setNext(new Node(traverser->getValue()));
      newList.setPrev(new Node(traverser->getPrev()->getPrev()));
      newList = newList->getNext();
      traverser = traverser->getNext();
    }
    _tail = newList; //TODO: Check this
    _size = original._size;
  }
}

DLinkedList::~DlinkedList() {

  // Same as SinglyLinked
  Node* traverser = _first;

  while(traverser != NULL) {
    Node* next = traverser->getNext();
    delete traverser;
    traverser = next;
  }

  // Reset
  _head = NULL;
  _size = NULL;
  _tail = NULL;
}

std::string DLinkedList::toString() const {
  std::ostringstream result;
  Node* traverser = _head;

  while (traverser != NULL) {
    result << traverser->getValue();

    if (traverser->getNext() != NULL) {
      result << " ";
    }
    traverser = traverser->getNext();
  }

  return result.str();
}




