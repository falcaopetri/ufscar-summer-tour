#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Deque.hpp"

namespace tour {
    template <class T>
    class Queue {
    private:

    Deque<T> _deque;

    public:
		Queue(); //construtor
		~Queue (); //metodo destruidor
        bool push(T); //insere elemento no final da fila, usa pushBack do deque
        void pop (); //remove primeiro elemento, usa popFront do deque
        T& front(); //mostra o primeiro elemento da fila, usa o front do deque
        bool empty(); //retorna verdadeiro se Fila estiver vazio, falso caso contrario, usa o empty do deque
    };

    template <class T>
	tour::Queue<T>::Queue() {
	}
	template <class T>
	tour::Queue<T>::~Queue() {
	}

	template <class T>
	void tour::Queue<T>::pop() {
		_deque.popFront();;
	}

	template <class  T>
	bool tour::Queue<T>::push(T element){
		return _deque.pushBack(element);
  	}

	template <class T>
	T& tour::Queue<T>::front(){
		return _deque.front();

	}

	template <class T>
	bool tour::Queue<T>::empty() {
		return _deque.empty();
	}

}
#endif
