#include <iostream>
#ifndef Queue_h
#define Queue_h

template <class T>
class Queue
{
public:
    Queue(): m_head(nullptr), m_tail(nullptr){}
    Queue(const Queue& otherQueue)
    {
        if(otherQueue.empty())
        {
            // this = Queue()  How to do this??
            Queue();
        }

        constIterator i = begin(); 
        m_head = i
        temp = m_head
        for (i != end(); i++)
        {
            temp->next = i;
            temp = i;
            m_tail = i;
        }
    }

    ~Queue()
    {
        while(!empty())
        {
            popFront();
        }
        free(m_head);
        free(m_tail);
    }

    bool empty() {return m_head == nullptr;}

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
            throw EmptyQueue();
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
    class ConstIterator;

    Iterator begin()
    {
        return Iterator(m_head);
    }
    Iterator end()
    {
        return Iterator(m_tail->next);
    }

    ConstIterator begin() const
    {
        return ConstIterator(m_head);
    }
    ConstIterator end() const
    {
        return ConstIterator(m_tail->next);
    }

    class EmptyQueue;


private:
    struct Element
    {
        T value;
        Element *next;
    };

    Element* m_head;
    Element* m_tail;
};




template <class S>
Queue<S> filter(const Queue<S>& queue, bool func(S))
{
    // TODO: IMPLEMENT THIS
    Queue<S> newQueue = Queue();
    Element<S>* tempElement = queue->m_head;
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
    Element<S>* tempElement = newQueue->m_head;
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
    Element<T>* m_element;

public:
    Iterator(Element<T>* element) : m_element(element){};
    T& operator*()
    {
        return m_element->value;
    }

    Iterator& operator++(int)
    {
        Iterator iterator = *this;
        ++(*this); //Calls the prefix operator on the original iterator
        return iterator; //returns the value of the iterator before the change
    }

    Iterator& operator++()
    {
        m_element++;
        return *this
    }

    bool operator==(const Iterator& iterator) const
    {
        return m_element == iterator.m_element;
    }
    bool operator!=(const Iterator& iterator) const
    {
        return m_element != iterator.m_element;
    }

    Iterator(const Iterator& iterator): m_element(iterator.m_element) {}
    Iterator& operator=(const Iterator& iterator): m_element(iterator.m_element) {}
};





// ConstIterator class for the Queue class
template<class T>
class Queue<T>::ConstIterator 
{
    Element<T>* m_element;

public:
    ConstIterator(Element<T>* element) : m_element(element){};
    const T& operator*()
    {
        return m_element->value;
    }

    const ConstIterator& operator++(int)
    {
        Iterator iterator = *this;
        ++(*this); //Calls the prefix operator on the original iterator
        return iterator; //returns the value of the iterator before the change
    }

    const Iterator& operator++()
    {
        m_element++;
        return *this
    }

    bool operator==(const Iterator& iterator) const
    {
        return m_element == iterator.m_element;
    }
    bool operator!=(const Iterator& iterator) const
    {
        return m_element != iterator.m_element;
    }

    Iterator(const Iterator& iterator): m_element(iterator.m_element) {}
    const Iterator& operator=(const Iterator& iterator): m_element(iterator.m_element) {}
};



#endif