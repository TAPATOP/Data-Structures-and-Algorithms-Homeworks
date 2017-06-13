/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Hristo Hristov
* @idnumber 61917
* @task 2
* @compiler VC
*
*/

#pragma once

template <typename T>
class Queue
{
public:
	Queue();
	Queue(Queue&);
	Queue(T* data, short tail, short size);

	void enqueue(T& newElement);
	void dequeue();
	T top();
	T bottom();
	T topNpop();// check if the queue is empty first
	void visualize();
	bool isEmpty();
	int queueSize();

	short getHead();
	short getTail();

	Queue<T>& operator=(Queue<T> const &Other);

	T operator [](int index) const;
	T& operator [](int index);

	~Queue();

private:
	T* data;
	short head;
	short tail;
	short size; // this is most likely unnecessary, but i think new uses it

	void copyQueue(Queue const&);
};

//
// interface is above
//

template <typename T>
Queue<T>::Queue()
{
	data = new T[1];
	head = 0;
	tail = 0;
	size = 1;
}

template <typename T>
Queue<T>::Queue(Queue& oldOne)
{
	copyQueue(oldOne);
}

template <typename T>
Queue<T>::Queue(T* data, short tail, short size)
{
	this->data = data;
	this->tail = tail;
	head = 0;
	this->size = size;
}
//
// constructors above
//

template <typename T>
void Queue<T>::enqueue(T& newElement)
{
	if (tail >= size)
	{
		T* replacer = new T[size * 2];

		for (int i = 0; i < size; i++)
		{
			replacer[i] = data[i];
		}
		size = size * 2;
		delete[] data;
		data = replacer;
	}

	data[tail] = newElement;
	tail++;
}

template <typename T>
void Queue<T>::dequeue()
{
	if (!isEmpty())
	head++;
}
//
// enqueue and dequeue
//

template <typename T>
T Queue<T>::top()
{
	return data[head];
}
//
// top
//

template <typename T>
T Queue<T>::bottom()
{
	return data[tail - 1];
}
//
// bottom
//

template <typename T>
T Queue<T>::topNpop()
{
	T output = data[head];
	head++;
	return output;
}
//
// topNpop ( top and dequeue) !!! DANGER OF POPPING NONEXISTANT ELEMENTS !!!
//

template <typename T>
void Queue<T>::visualize()
{
	for (int i = head; i < tail; i++)
	{
		cout << data[i] << endl;
	}
}
//
// visualization
//

template <typename T>
bool Queue<T>::isEmpty()
{
	return head == tail;
}
//
// is empty
//

template <typename T>
int Queue<T>::queueSize()
{
	return tail - head;
}
//
// queue size
//

template <typename T>
short Queue<T>::getHead()
{
	return head;
}

template <typename T>
short Queue<T>::getTail()
{
	return tail;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T> const &Other)
{
	copyQueue(Other);
	return *this;
}
//
// operator =
//

template <typename T>
T Queue<T>::operator [](int index) const
{
	return data[index];
}

template <typename T>
T& Queue<T>::operator[](int index)
{
	return data[index];
}
//
// [] overload
//

template <typename T>
Queue<T>::~Queue()
{
	delete[] data;
}

template<typename T>
void Queue<T>::copyQueue(Queue const &oldOne)
{
	delete[] data;
	head = 0;
	short i1 = oldOne.head;
	short i2 = oldOne.tail;

	tail = i2 - i1;

	data = new T[tail];

	for (int i = i1, size = 0; i < i2; i++, size++)
	{
		data[size] = oldOne.data[i];
	}
}
// private copier