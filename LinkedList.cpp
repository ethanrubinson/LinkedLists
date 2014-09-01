#include <iostream>
#include <sstream>
#include "LinkedList.h"

LinkedList::LinkedList() {
	_first = NULL;
	_size = 0;
}

LinkedList::LinkedList(const LinkedList& original) {
	
	if (original._size == 0) {
		_first = NULL;
		_size = 0;
	}

	else {
		_first = new Node(original._first->getValue());

		Node* traverser = original._first->getNext();
		Node* newLinks = _first;

		while (traverser != NULL) {
			newLinks->setNext(new Node(traverser->getValue()));
			newLinks = newLinks->getNext();
			traverser = traverser->getNext();
		}

		_size = original._size;
	}
}

LinkedList::~LinkedList() {

	Node* traverser = _first;

	while(traverser != NULL) {
    	Node* next = traverser->getNext();
    	delete traverser;
    	traverser = next;
	}

	// Reset for sanity
	_first = NULL;
	_size = 0;
}

std::string LinkedList::toString() const {
	std::ostringstream result;
	Node* traverser = _first;

	while (traverser != NULL) {
		result << traverser->getValue();
		
		if (traverser->getNext() != NULL) {
			result << " ";
		}
		traverser = traverser->getNext();
	}

	return result.str();
}

LinkedList* LinkedList::getReverse() const {

	LinkedList* newList = new LinkedList();
	Node* traverser = _first;

	while (traverser != NULL) {
		newList->insert(traverser->getValue(), 0);
		traverser = traverser->getNext();
	}

	return newList;
}

bool LinkedList::insert(int value, int offset) {
	// Sanity checks
	// offset must be >=0 and <= _size
	if (offset > _size || offset < 0) {
		return false;
	}

	Node* newNode = new Node(value);

	// New head node
	if (offset == 0) {
		newNode->setNext(_first);
		_first = newNode;
		_size++;
		return true;
	}

	// New non-head node
	Node* current = _first->getNext();
	Node* previous = _first;
	int current_offset = 1;

	while (current_offset != offset) {
		previous = current;
		current = current->getNext();
		current_offset++;
	}

	newNode->setNext(current);
	previous->setNext(newNode);
	_size++;
	return true;
}

bool LinkedList::erase(int value) {
	Node* current = _first;
	Node* previous = current;
	bool found = false;

	while (current != NULL) {

		// Found a value match, delete the node
		if (current->getValue() == value) {
			found = true;

			// Case to delete the head of the list
			if (current == _first) {
				_first = current->getNext();
				delete current;

				current = _first;
				previous = current;
				_size--;
			}

			// Case to delete a non-head node
			else {
				previous->setNext(current->getNext());
				delete current;

				current = previous->getNext();
				_size--; 
			}
		}

		// No value match was found, move on to the next node
		else{
			previous = current;
			current = current->getNext();
		}
	}

	return found;
}

int LinkedList::size() const {
	return _size;
}

void LinkedList::sort() {
	int num_iters_remaining = _size - 1;

	while(num_iters_remaining > 0){
		int current_index = 1;
		int last_index = num_iters_remaining;
		Node* current = _first->getNext();
		Node* previous = _first;
		Node* previous_previous = NULL;

		while (current_index <= last_index) {
			std::cout << "Checking index " << current_index << " against " << current_index - 1 << std::endl;
			if (current->getValue() < previous->getValue()) {
				previous->setNext(current->getNext());
				current->setNext(previous);

				if(previous == _first){
					_first = current;
				}
				else{
					previous_previous->setNext(current);
				}

				previous_previous = current;
				current = previous->getNext();
			}
			else {
				previous_previous = previous;
				previous = current;
				current = current->getNext();
			}
			current_index++;
		}

		num_iters_remaining--;
	}
}
