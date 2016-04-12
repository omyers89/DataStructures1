/*
Written by Mayers, Omri & Dukhan, Dvir
Some algorithms implemntaions are taken from, or inspired by
1 .Technion's CS faculty's "Data Structurs 230402" course lecture notes made by Prof. Dan Guyger
2. "Introduction to Algorithms" by Cormen, Leiserson, Rivest & Stein
*/


#ifndef _OONE_QUEUE_H
#define _OONE_QUEUE_H
#include "Oone_array.h"
#include <exception>

class QueueIsFull : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Queue is full\n";
	}

};

class QueueIsEmpty : public std::exception{
public:
	virtual const char* what() const throw(){
		return "Queue is empty\n";
	}

};

/*
Oone_Array object is array intialized in O(1) time complexity to a given "Zero Object"
object is template of class T. T should have operator=
inherits from Oone_Array
*/
template <class T>
class Oone_Queue : public Oone_Array<T>{
private:
	int first;
	int last;
	int count;
	int size;
	int indexToInsert() const;

	T get(int i){
		return Oone_Array<T>::get(i);
	}

	void store(unsigned i, const T& element){
		Oone_Array<T>::store(i, element);
	}
public:
	/*
	Oone_Queue intialztion requires size (k) and T object (r) which act as the "Zero Object"
	*/
	Oone_Queue(unsigned k, const T& r) : Oone_Array<T>(k, r), first(0), last(0), count(0), size(k){}
	void enqueue(T data);
	T dequeue();
	/*
	function isFull will return if queue is full
	*/
	bool isFull() const{
		return (count == size);
	}
	/*
	function isEmpty will return if queue is empty
	*/
	bool isEmpty() const{
		return (count == 0);
	}

};


/*
function enqueue will insert an object to the queue
set the next write placeholder in the right position
increase count
*/
template <class T>
void Oone_Queue<T>::enqueue(T data){
	if (isFull()){
		throw QueueIsFull();
	}
	store(last, data);
	if (last + 1 < size){
		++last;
	}
	else{
		last = 0;
	}
	++count;
}

/*
function dequeue will return an object from the queue
set the next read placeholder in the right position
decrease count
*/
template <class T>
T Oone_Queue<T>::dequeue(){
	if (isEmpty()){
		throw QueueIsFull();
	}
	T data=get(first);
	if (first + 1 < size){
		++first;
	}
	else{
		first = 0;
	}
	--count;
	return data;
}

#endif