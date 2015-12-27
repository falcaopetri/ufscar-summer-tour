#ifndef STACK_HPP
#define STACK_HPP

#include "Deque.hpp"

namespace tour {
    template <class T>
    class Stack{
    private:

    Deque<T> _deque;

    public:
		Stack(); //construtor
		~Stack (); //metodo destruidor
        bool push(T); //insere elemento no inicio da pilha, usa pushFront do deque
        void pop (); //remove ultimo elemento, usa popBack do deque
        T& top(); //mostra o primeiro elemento da pilha, usa o front do deque
        bool empty(); //retorna verdadeiro se pilha estiver vazio, falso caso contrario, usa o empty do deque
    };

    template <class T>
	tour::Stack<T>::Stack() {
	}
	template <class T>
	tour::Stack<T>::~Stack() {
	}

	template <class T>
	void tour::Stack<T>::pop() {
		_deque.popFront();
	}

	template <class  T>
	bool tour::Stack<T>::push (T element){
		return _deque.pushFront(element);
  	}

	template <class T>
	T& tour::Stack<T>::top(){
		return _deque.front();

	}

	template <class T>
	bool tour::Stack<T>::empty() {
		return _deque.empty();
	}

}
#endif
