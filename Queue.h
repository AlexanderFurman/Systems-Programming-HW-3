#include <iostream>
#ifndef Queue_h
#define Queue_h

/** omer 29/12:
 * for debugging - better to start with int queue and then switch to T
 * run through code
 * insert exception handle with operator=() and allocations ?
 * exception - Queue<T>:EmptyQueue and empty() ?
 * exceptions - std::bad_alloc and Queue<T>:InvalidOperation ?
 * should Queue exceptions inherit std::exception?
 * func ptr or func obj ?
 * no friends - switch to get()
 * const and non const Queue support
 * code conventions
 * **/

///need to check we're not calling default c'tor of T (may not exist)

template <class T>
class Queue
{
public:
    /// omer 29/12: do we need operator=() ?
    Queue(): m_head(nullptr), m_tail(nullptr) {}
    Queue(const Queue& otherQueue) : m_head(nullptr), m_tail(nullptr)
    {
        if(otherQueue.empty()) /// omer 29/12: exception?
        {
            /// omer 29/12: tutorial 8 slide 11 bottom (copy c'tor)
            // this = Queue()  How to do this??
            //Queue();
            return;
        }
        /// Queue Q1 = existingQueue
        // create e,pty queue in initialization list
        // for (each in otherqueue) -> pushBack
        // if fails (bad alloc was thrown from pushBack):
        //      1. catch bad alloc
        //      2. delete current queue
        //      3. throw bad_alloc
        // if passes all -> yayy!!

        /// maybe we should check syntax sweet for for loop ( for(Element el : otherQueue)?? )
        ConstIterator i = otherQueue.begin();
        /// omer 29/12: what's the intention in the loop?
        /// why =i? what do we check
        /// ; in two lines ahead - is it in purpose?
        m_head = i;
        temp = m_head;
        for (i != end(); i++) /// for(Element el : otherQueue)
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
        //free(m_head); /// omer 29/12: why do we free them? whats left?
        //free(m_tail); /// omer 29/12: why do we free them? whats left?
    }

    bool empty() {return m_head == nullptr;}

    void pushBack(T data)
    {
        /// omer 29/12: if fails throw bad alloc
        Element* newElement = new Element;

        /// if fails throw bad alloc ?
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
        /// omer 29/12: do we need to return or to throw EmptyQueue()?
        if(empty()) {
            return;
        }

        Element* temp = m_head;
        m_head = m_head->next;

        // Check if this operation has caused m_head to point to null
        if(m_head == nullptr)
        {
            m_tail = nullptr;
        }

        delete (temp); /// do we delete the data T inside the element?
                       /// do we need to change element to struct with
    }

    int size()
    /// omer 29/12: use iterator
    {
        if(empty()) {
            return 0;
        }
        int counter = 1;
        Element* temp = m_head;
        while(temp->next != nullptr)
        {
            counter++;
            /// omer 29/12: added row bellow:
            temp = temp->next;
        }
        return counter;
    }

    class Iterator; /// friend?
    class ConstIterator; /// friend?

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

    class EmptyQueue{};


private:
    struct Element
    {
        ///need to check we're not calling default c'tor of T (may not exist)
        T m_value; /// think it's ok, but do we need T* or T ?
        Element *m_next;
        /// add c'tor, d'tor, copy c'tor, operator=() (default if generated automatically)
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