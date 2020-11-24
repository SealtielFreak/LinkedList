/*
 *
 *  Diego Sealtiel Valderrama García - 20110339
 *  IDS, 2M-1 T/Vespertino
 *
 *  1/Octuber/2020
 *
 */

#ifndef NODE_HPP
#define NODE_HPP

template<typename Type>
struct Node {
protected:
	Node<Type> *nextNode, *previousNode;
	Type valueNode;
public:
	Node() {
		nextNode = nullptr;
        previousNode = nullptr;
	}

	Node(Type value) {
		nextNode = nullptr;
        previousNode = nullptr;
		setValue(value);
	}

	Node(Node<Type> &previus, Node<Type> &next) {
		setParent(previus);
		setChild(next);
	}
	Node(Node<Type> *previus, Node<Type> *next) {
		setPrevius(previus);
		setNext(next);
	}

	Node(Type value, Node<Type> *previus, Node<Type> *next) {
		setValue(value);
		setPrevius(previus);
		setNext(next);
	}

	void setValue(Type value) {
		valueNode = value;
	}

	Type& getValue() {
		return valueNode;
	}
	Type getValue() const {
		return valueNode;
	}

	void setChild(Node<Type> &next) {
		if (emptyNext()) {
			freeNext();
		}

		next.previousNode = this;
		nextNode = &next;
	}

	void setChild(Node<Type> *next) {
		if(emptyNext()) {
			freeNext();
		}
		nextNode = next;
		nextNode->previousNode = this;
	}

	void setParent(Node<Type> &previous) {
		if (emptyPrevious()) {
            freePrevious();
		}

        previous.nextNode = this;
        previousNode = &previous;
	}

	void setParent(Node<Type> *previous) {
		if(emptyPrevious()) {
            freePrevious();
		}

        previousNode = previous;
        previousNode->nextNode = this;
	}

	Node<Type>* getNext() const {
		if(nextNode)
			return nextNode;

		return nullptr;
	}

	Node<Type>* getPrevious() const {
		if(previousNode)
			return previousNode;

		return nullptr;
	}

	void freePrevious() {
		if (!emptyPrevious()) {
            previousNode->nextNode = nullptr;
		}

        previousNode = nullptr;
	}

	void freeNext() {
		if (!emptyNext()) {
			nextNode->previousNode = nullptr;
		}

		nextNode = nullptr;
	}

	bool emptyPrevious() const {
		if (previousNode) {
			return false;
		}

		return true;
	}

	bool emptyNext() const {
		if (nextNode) {
			return false;
		}

		return true;
	}

	Node<Type> &operator=(Node<Type> &node) {
		valueNode = node.valueNode;
		nextNode = node.nextNode;
        previousNode = node.previousNode;
		return *this;
	}

	Node<Type> &operator=(Type value) {
		valueNode = value;

		return *this;
	}

public:
	template<typename>
	friend
	class LinkedList;
};


#endif // NODE_HPP
