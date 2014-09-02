#include <sstream>
#include <iostream>

#include "DLinkedList.h"

DLinkedList::DLinkedList() {
  _head = NULL;
  _tail = NULL;
  _size = 0;
}

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
      newList->setPrev(new DNode(traverser->getPrev()->getValue()));
      newList = newList->getNext();
      traverser = traverser->getNext();
    }
    _tail = newList; //TODO: Check this
    _size = original._size;
  }
}

DLinkedList::~DLinkedList() {

  // Same as SinglyLinked
  DNode* traverser = _head;

  while(traverser != NULL) {
    DNode* next = traverser->getNext();
    delete traverser;
    traverser = next;
  }

  // Reset
  _head = NULL;
  _size = 0;
  _tail = NULL;
}

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

DLinkedList* DLinkedList::getReverse() const {

  DLinkedList* newList = new DLinkedList();
  DNode* traverser = _head;

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
    return true;
  }

  // Insert at the head 
  if(offset == 0) {
    newNode->setNext(_head);
    _head->setPrev(newNode);
    _head = newNode;
    return true;
  }

  DNode* current;

  // Start iteratign from back
  if (offset >= _size/2) {
    current = _tail;

    while (offset != 0) {
    current = current->getPrev();
    offset--;
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

bool DLinkedList::erase(int value){
  std::cerr << "Function not yet implemented" << std::endl;
  exit(1);
}

int DLinkedList::size() const {
  return _size;
}
