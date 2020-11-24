/*
 *
 *  Diego Sealtiel Valderrama García
 *
 *  1/Octuber/2020
 *
 */

#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <exception>

#include "Node.hpp"

template<typename Type>
class LinkedList {

private:
    std::size_t sizeList;
    Node<Type> *root;

public:
    LinkedList() {
        root = nullptr;
        sizeList = 0;
    }
    LinkedList(const std::size_t size, Type value_initialize) {
        sizeList = 0;
        for(auto it = 0u; it < size; it++) {
            push_back(value_initialize);
        }
    }
    LinkedList(std::initializer_list<Type> array);

    void push_back(Type value) {
        one_more();
        if(empty()) {
            root = new Node<Type>(value);
        } else {
            auto parent = travel_queue();
            auto aux = new Node<Type>(value);
            parent->setChild(aux);
        }
    }
    void push_back(std::initializer_list<Type> array_value) {
        for(const auto it: array_value) {
            push_back(it);
        }
    }
    void push_back(Type *array_value, const std::size_t size) {
        for(auto it = 0u; it < size; it++) {
            push_back(array_value[it]);
        }
    }

    void pop_back(Type value) {
        one_more();
        if(empty()) {
            root = new Node<Type>(value);
        } else {
            auto parent = new Node<Type>(value);
            parent->setChild(root);
            root = parent;
        }
    }
    void pop_back(std::initializer_list<Type> array_value) {
        for(const auto it: array_value) {
            pop_back(it);
        }
    }
    void pop_back(Type *array_value, const std::size_t size) {
        for(auto it = 0u; it < size; it++) {
            push_back(array_value[it]);
        }
    }

    void insert(std::size_t position, Type value) {
        if(empty() or out_of_range(position)) {
            throw std::out_of_range("");
        } else {
            one_more();
            auto node = new Node<Type>(value);
            auto aux = travel_to(position);
            if(aux->getPrevious()) {
                auto child = aux->getPrevious();
                child->setChild(node);
            }
            aux->setParent(node);
            if(root->getPrevious()) {
                root = node;
            }
        }
    }

    void swap(LinkedList<Type> swap_list) {
        this->clear();
        for(auto it = 0u; it < swap_list.size(); it++) {
            push_back(swap_list.at(it));
        }
    }

    Type* data() {
        Type *data_arr = new Type[sizeList];
        for(auto it = 0u; it < sizeList; it++) {
            data_arr[it] = this->at(it);
        }

        return data_arr;
    }

    void erase(const std::size_t position) {
        if(!empty() && position < size()) {
            auto aux = travel_to(position);
            auto previous = aux->getPrevious();
            auto next = aux->getNext();

            sizeList--;

            if(!previous) {
                aux->freeNext();
                root = next;
            } else {
                aux->freePrevious();
                aux->freeNext();
                if(next) {
                    previous->setChild(next);
                }
            }

        }
    }

    void clear() {
        if(!empty()) {
            auto aux = travel_queue();
            while(!aux->emptyPrevious()) {
                aux = aux->getPrevious();
                auto next_node = aux->getNext();
                aux->freeNext();
                delete next_node;
            }

            sizeList = 0;
            delete root;
            root = nullptr;
        }
    }

    Type at(const std::size_t position) const {
        auto aux = travel_to(position);
        return aux->getValue();
    }
    Type &at(const std::size_t position) {
        auto aux = travel_to(position);
        return aux->getValue();
    }

    Type operator[](const std::size_t position) const {
        auto aux = travel_to(position);
        return aux->getValue();
    }

    Type &operator[](const std::size_t position) {
        auto aux = travel_to(position);
        return aux->getValue();
    }

    LinkedList<Type> &operator=(const LinkedList<Type> &list);
    LinkedList<Type> &operator=(const Type list[]);
    LinkedList<Type> &operator=(std::initializer_list<Type> array_value);


    std::size_t size() const {
        return sizeList;
    }

    bool empty() const {
        if(root != nullptr) {
            return false;
        }

        return true;
    }

protected:
    void one_more() {
        sizeList++;
    }
    bool out_of_range(const std::size_t position) {
        if(position > this->sizeList) {
            return true;
        }

        return false;
    }
    Node<Type>* travel_to(const std::size_t position) {
        auto aux = root;

        if(empty()) {
            return aux;
        }

        if(out_of_range(position)) {
            throw std::out_of_range("");
        } else {
            for(auto it = 0u; it < position; it++) {
                aux = aux->getNext();
            }
        }

        return aux;
    }
    Node<Type>* travel_queue() {
        if(empty()) {
            return root;
        }

        auto aux = root;
        while(aux->getNext()) {
            aux = aux->getNext();
        }

        return aux;
    }
};

#endif //LINKEDLIST_HPP
