#include <iostream>
#ifndef Queue_h
#define Queue_h

template <class T>
class Queue
{
public:
    /*
     * C'tor of Queue class
     *
     * @param data - The data
     * @param stats - The numeral stats of the card.
     * @return
     *      A new instance of Queue
    */
    Queue(): m_head(nullptr), m_tail(nullptr){}
    Queue(const Queue&);
    ~Queue();

    bool empty() {return m_head == nullptr};

    void pushBack(T data)
    {
        Element* newElement = new Element;
        newElement->value = data;
        newElement->next = nullptr;

        if(empty()) 
        {
            m_head = newElement;
            m_tail = newElement;
            return;
        }

        m_tail->next = newElement;
        m_tail = newElement;
    }

    T& front()
    {
        if(empty())
        {
            throw EmptyQueue e;
        }
        return m_head->value;

    }

    void popFront()
    {
        if(empty()){return;}

        Element* temp = m_head;
        m_head = m_head->next;

        // Check if this operation has caused m_head to point to null
        if(m_head == nullptr)
        {
            m_tail = nullptr;
        }

        delete (temp);
    }

    int size()
    {
        if(empty()){return 0;}

        int counter = 1;
        Element* temp = m_head;
        while(temp->next != nullptr){counter++;}
        return counter;
    }

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    class EmptyQueue;


private:
    struct Element
    {
        T value;
        Element *next;
    };

    Element* m_head;
    Element* m_tail;
}




template <class S>
Queue<S> filter(const Queue<S>& queue, bool func(S))
{
    // TODO: IMPLEMENT THIS
    Queue<S> newQueue = Queue();
    Element<S>* tempElement = queue->head;
    while(tempElement != nullptr)
    {
        if(func(tempElement->value))
        {
            newQueue.pushBack(tempElement->value);
        }
        tempElement = tempElement->next;
    }

    return newQueue;
}

template <class S>
Queue<S> transform(const Queue<S>& queue, void func(S))
{
    // TODO: IMPLEMENT THIS

    Queue<S> newQueue = Queue(queue);
    Element<S>* tempElement = newQueue->head;
    while(tempElement != nullptr)
    {
        tempElement->value = func(value);
        tempElement = tempElement->next;
    }

    return newQueue;
    
}










// Iterator class for the Queue class
template<class T>
class Queue<T>::Iterator 
{
    const Queue<T>* m_queue;
    int m_index;
    Iterator(const Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    const T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int) m_index(m_index ++);

    bool operator==(const Iterator& iterator) const;
    bool operator!=(const Iterator& iterator) const;

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
};








template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const 
{
    return Iterator(this, 0);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const 
{
    return Iterator(this, m_size);
}

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int index): m_queue(queue), m_index(index) {}

template <class T>
const T& Queue<T>::Iterator::operator*() const
{
    return queue->m_data
}

#endif /* Queue_h */