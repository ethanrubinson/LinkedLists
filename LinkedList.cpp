#include <iostream>
#include <sstream>
#include "LinkedList.h"

LinkedList::LinkedList() {
	_first = NULL;
	_size = 0;
}

LinkedList::LinkedList(const LinkedList& original) {
	// TODO: Fill this in
	std::cerr << "LinkedList::LinkedList(const LinkedList& original) is not yet ";
	std::cerr << "implemented" << std::endl;
	exit(1);
}

LinkedList::~LinkedList() {
	// TODO: Fill this in
	std::cerr << "LinkedList::~LinkedList() is not yet implemented" << std::endl;
	exit(1);
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
	// TODO: Fill this in
	std::cerr << "LinkedList::getReverse() is not yet implemented" << std::endl;
	exit(1);
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
	// TODO: Fill this in
	std::cerr << "LinkedList::sort() is not yet implemented" << std::endl;
	exit(1);
}
