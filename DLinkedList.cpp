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
    _first = new Node(original._first->getValue());

    Node* traverser = original._first->getNext();
    Node* newList = _first;

    while (traverser

