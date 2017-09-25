#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>

// allows us to create a Heap for any datatype
template <typename T, typename Comparator>

class Heap{
public:
	Heap();							// construct m-ary heap for any m>=2
  	~Heap();						// destructor
  	void push(const T& item);		// adds an item to the heap
  	T const & top() const;			// returns element on top of heap
  	void pop();						// removes top element of heap
  	bool empty() const;				// returns true if heap is empty
  	unsigned int size() const;		// returns the size of the heap

private:
	std::vector<T> _store;			// use a vector to store keys of the Heap
	Comparator _c;					// Comparator for keys of the Heap
};

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap() : 
  _store(),
  _c()
{ }

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{ }

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item){
  _store.push_back(item);
  std::push_heap( _store.begin(), _store.end(), _c);
}

template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _store.front();
}

/// Removes the top element
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop(){
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  std::pop_heap( _store.begin(), _store.end(), _c );
  _store.pop_back();
}

/// returns true if the heap is empty
template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const{
  return _store.empty();
}

/// returns the size
template <typename T, typename Comparator>
unsigned int Heap<T,Comparator>::size() const{
  return _store.size();
}

#endif