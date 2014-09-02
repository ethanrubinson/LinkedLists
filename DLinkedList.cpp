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
    DNode* previous = original._head;
    DNode* newList = _head;

    while (traverser != NULL) {
      newList->setNext(new DNode(traverser->getValue()));
      newList = newList->getNext();
      newList->setPrev(new DNode(previous->getValue()));
      traverser = traverser->getNext();
      previous = previous->getNext();
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
        _head = NULL
        _tail = NULL
        current = current->getNext();
        delete(delNode);
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
        DNone* delNode == _head;
        _head = delNode->GetNext();
        _head->setPrev(NULL);
        current = current->getNext();
        delete delNode;
        _size--;
      }
      // Deleting arbitrary location 
      else {
        DNode* delNode = current
        delNode->getNext()->setPrev(delNode->getPrev());
        delNode->getPrev()->setNext(delNode->getNext());
        current = current->getNext();
        delete(delNode);
        _size--;
      }
    }
    else {
      current = current->getNext();
    }
  } 
  return found;
}


int DLinkedList::size() const {
  return _size;
}
