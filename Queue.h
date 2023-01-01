#include <iostream>
#include <cassert>
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
//        ConstIterator i = otherQueue.begin();
        /// omer 29/12: what's the intention in the loop?
        /// why =i? what do we check
        /// ; in two lines ahead - is it in purpose?
//        m_head = i;
//        temp = m_head;
//        for (i != end(); i++) /// for(Element el : otherQueue)
        for (const Element element : otherQueue)
        {
            try
            {
                pushBack(element.value);
            }
            catch (std::bad_alloc& badAlloc)
            {
                while(!empty())
                {
                    popFront();
                }
                throw badAlloc;
            }
        }
    }

    Queue& operator=(const Queue& otherQueue)
    {
        int originalSize = size();

        if(this == &otherQueue)
        {
            return *this;
        }

        for (const Element element : otherQueue)
        {

            try
            {
                pushBack(element.value);
            }
            catch (std::bad_alloc& badAlloc)
            {
                int currentSize = size();

                for (int i = 0; i < originalSize; i++) {
                    pushBack(front());
                }
                for (int i = 0; i < currentSize; i++) {
                    popFront();
                }
                throw badAlloc;
            }
        }
        for(int i = 0; i < originalSize; i++)
        {
            popFront();
        }
        return *this;
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

    bool empty() const
    {
        return m_head == nullptr;
    }

    void pushBack(T data)
    {
        /// omer 29/12: if fails throw bad alloc
        Element* newElement = new Element(data); ///omer 31/12: can we do it without dynamic allocation?

        // /// if fails throw bad alloc ?
        // newElement->value = data;
        // newElement->next = nullptr;

        if(empty())
        {
            m_head = newElement;
            m_tail = newElement;
            return;
        }

        m_tail->next = newElement;
        m_tail = newElement;
    }

    T& front() const ///omer 31/12: isn't it open to changing from user even when const?
    {
        if(empty())
        {
            throw EmptyQueue();
        }
        return m_head->value;
    }

    void popFront()
    {
        /// omer 31/12: do we need to return or to throw EmptyQueue()?
        if(empty()) {
            throw EmptyQueue();
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

    int size() const
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

    class Iterator;
    class ConstIterator;

    Iterator begin()
    {
        return Iterator(this, m_head);
    }
    Iterator end()
    {
        if(empty()) {
            return Iterator(this, m_tail);
        }
        return Iterator(this, m_tail->next);
    }

    ConstIterator begin() const
    {
        return ConstIterator(this, m_head);
    }
    ConstIterator end() const
    {
        if(empty()) {
            return ConstIterator(this, m_tail);
        }
        return ConstIterator(this, m_tail->next);
    }

    class EmptyQueue{};

    template<class S, class F>
    friend Queue<S> filter(const Queue<S>& queue, F condition);

    template <class S, class F>
    friend void transform(Queue<S>& queue, F func);


private:

    struct Element
    {
        ///need to check we're not calling default c'tor of T (may not exist)
        T value; /// think it's ok, but do we need T* or T ?
        Element *next;
        /// add c'tor, d'tor, copy c'tor, operator=() (default if generated automatically)
        Element(T data): value(data), next(nullptr){};

        //~Element() = default; Do I need to have this defined?
    };

    Element* m_head;
    Element* m_tail;

};

//
//template <class S, class F>
//Queue<S> filter(const Queue<S>& queue, const F condition)
//{
//    // TODO: IMPLEMENT THIS
//    Queue<S> newQueue = Queue<S>();
//    for (const typename Queue<S>::Element& element : queue)
//    {
//        if(condition(element.value))
//        {
//            newQueue.pushBack(element.value);
//        }
//    }
//
//    return newQueue;
//}

template <class S, class F>
Queue<S> filter(const Queue<S>& queue, const F condition)
{
    // TODO: IMPLEMENT THIS
    Queue<S> newQueue = Queue<S>();
    for (const S& value : queue)
    {
        if(condition(value))
        {
            newQueue.pushBack(value);
        }
    }

    return newQueue;
}

template <class S, class F>
void transform(Queue<S>& queue, const F func)
{
    for(S& value:queue)
    {
        func(value);
    }
}

//template <class S, class F>
//void transform(Queue<S>& queue, const F func)
//{
//    // TODO: IMPLEMENT THIS
//    for(typename Queue<S>::Element& element: queue)
//    {
////        std::cout << element.value << std::endl;
//        func(*element);
//    }
//}
//



///do we need to implement iterator -> ?
template<class T>
class Queue<T>::Iterator
{
private:
    Queue<T>* const m_queue; ///the iterators queue
    Queue<T>::Element* m_elementPtr;

     Iterator(Queue<T>* const queue, Queue<T>::Element* const element)
                      : m_queue(queue), m_elementPtr(element) {};

    ///is op=() needed?
    Iterator& operator=(const Iterator& iterator) ///of the same set!!
    {
        if (iterator == m_queue->end()) {
            throw InvalidOperation();
        }
        assert (m_queue == iterator.m_queue && (this != iterator)); ///this or *this?? -> this
        m_elementPtr = iterator.m_elementPtr;
    }

    friend class Queue<T>; /// does set access iterator members? think so - m_elementPtr



public:

    class InvalidOperation {};

    ///are these needed?
    Iterator(const Iterator& iterator) = default;
    /// does this copy c'tor need to be non default?-> : m_queue(iterator.m_queue), m_elementPtr(iterator.m_elementPtr) {}

    T& operator*() const
    {
        if (*this == m_queue->end()) { /// omer 31/12: this or *this?
            throw InvalidOperation();
        }
        assert(m_elementPtr!= nullptr);
        return m_elementPtr->value;
    }

    Iterator& operator++()
    /// change all iterators++ to ++iterators in set
    {
        if (*this == m_queue->end()) { /// omer 31/12: this or *this?
            throw InvalidOperation();
        }
        m_elementPtr= m_elementPtr->next;
        return *this;
    }


    Iterator operator++(int) ///not must
    ///whats the problem with Iterator no-const return here?
    {
        Iterator result = *this;
        ++(*this); //Calls the prefix operator on the original iterator
        return result; //returns the value of the iterator before the change
    }

    bool operator==(const Iterator& iterator) const ///not must
    {
        assert(m_queue == iterator.m_queue);
        return m_elementPtr == iterator.m_elementPtr;
    }

    bool operator!=(const Iterator& iterator) const
    {
        return !( *this == iterator );
    }

};

///do we need to implement iterator -> ?
template<class T>
class Queue<T>::ConstIterator
{
private:
    const Queue<T>* const m_queue; ///the const queue of cIterator
    const Queue<T>::Element* m_elementPtr;

    ConstIterator(const Queue<T>* const queue, const Queue<T>::Element* element)
            : m_queue(queue), m_elementPtr(element) {};
    friend class Queue<T>; /// does set access cIterator members? think so - m_elementPtr



public:
    class InvalidOperation {};
    ///operator=() deleted
    ///are these needed?
    ConstIterator(const ConstIterator& cIterator) = default;
    ///copy c'tor - default or not? -> : m_queue(cIterator.m_queue), m_elementPtr(cIterator.m_elementPtr) {}
    ConstIterator& operator=(const ConstIterator& cIterator) = delete;

    const T& operator*() const
    {
        if (*this == m_queue->end()) { /// omer 31/12: this or *this?
            throw InvalidOperation();
        }
        return m_elementPtr->value;
    }

    ConstIterator& operator++()
    /// change all cIterators++ to ++iterators in set
    {
        if (*this == m_queue->end()) { /// omer 31/12: this or *this?
            throw InvalidOperation();
        }
        m_elementPtr= m_elementPtr->next;
        return *this;
    }

    ConstIterator operator++(int) ///not must
    ///whats the problem with cIterator no-const return here?
    {
        ConstIterator result = *this;
        ++(*this); //Calls the prefix operator on the original cIterator
        return result; //returns the object of the cIterator before the change
    }

    bool operator==(const ConstIterator& cIterator) const ///not must
    {
        assert(m_queue == cIterator.m_queue);
        return m_elementPtr == cIterator.m_elementPtr;
    }

    bool operator!=(const ConstIterator& cIterator) const
    {
        return !( *this == cIterator );
    }

};


///prev ConstIterator implementation
//// ConstIterator class for the Queue class
//template<class T>
//class Queue<T>::ConstIterator
//{
//    Element<T>* m_element;
//
//public:
//    ConstIterator(Element<T>* element) : m_element(element){};
//    const T& operator*()
//    {
//        return m_element->value;
//    }
//
//    const ConstIterator& operator++(int)
//    {
//        Iterator iterator = *this;
//        ++(*this); //Calls the prefix operator on the original iterator
//        return iterator; //returns the value of the iterator before the change
//    }
//
//    const Iterator& operator++()
//    {
//        m_element++;
//        return *this
//    }
//
//    bool operator==(const Iterator& iterator) const
//    {
//        return m_element == iterator.m_element;
//    }
//    bool operator!=(const Iterator& iterator) const
//    {
//        return m_element != iterator.m_element;
//    }
//
//    Iterator(const Iterator& iterator): m_element(iterator.m_element) {}
//    const Iterator& operator=(const Iterator& iterator): m_element(iterator.m_element) {}
//};



#endif