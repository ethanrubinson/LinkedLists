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

DLinkedList* DLinkedList::getReverse() const {

  DlinkedList* newList = new DLinkedList();
  Node* traverser = _first;

  while (traverser != NULL) {
    newList->insert(traverser->getValue(),0);
    traverser = traverser->getNext();
  }
  
  return newList;

}

bool DLinkedList::insert(int value, int offset) {
  // IV: 0 <= offset <= _size 
  if (offset > _size || offset < 0) {
    return false;
  }

  Node* newNode = new Node(value);
  
  // Insert in empty list
  if (_size == 0) {
    _head = NewNode;
    _tail = NewNode;
    _size++;
    return true;
  }

  // Insert at the tail
  if (offset == size) {
    newNode->setPrev(_tail);
    _tail->setNext(newNode);
    _tail = newNode;
    return true;
  }

  // Insert at the head 
  if(offset == 0) {
    newNode->setNext(_head);
    _head->setPrev(newNode);
    _head = NewNode;
    return true;
  }

  // Start iteratign from back
  if (offset >= size/2) {
    Node* current = _tail;

    while (offset != 0) {
    current = current->getPrev();
    offset--;
    }
  }

  // Start iterating from the front
  else {
    Node* current = _head;
    while (offset != 0) {
      current = current->getNext();
      offset--;
    }
  }

  newNode->setNext(current);
  newNode->setPrev(current->getPrev);
  current->getPrev->setNext(newNode);
  current->setPrev(newNode);
  _size++;
  return true;

}











