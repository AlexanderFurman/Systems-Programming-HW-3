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
/**
 * default constructor
 * inputs: none
 * outputs: none
 * possible errors: none
 */
    Queue(): m_head(nullptr), m_tail(nullptr) {}

/**
 * copy constructor
 * inputs: reference to another Queue object
 * outputs: none
 * possible errors: std::bad_alloc
 */
    Queue(const Queue& otherQueue) : m_head(nullptr), m_tail(nullptr)
    {
        if(otherQueue.empty())
        {
            return;
        }

        try
        {
            for (const Element element : otherQueue)
            {
                pushBack(element.value);
            }

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

/**
 * assignment operator
 * inputs: reference to another Queue object
 * outputs: reference to the current Queue object (*this)
 * possible errors: std::bad_alloc
 */

    Queue& operator=(const Queue& otherQueue)
    {
        int originalSize = size();
        int currentSize = 0;

        if(this == &otherQueue)
        {
            return *this;
        }

        try
        {
            for (const Element element : otherQueue)
            {
                pushBack(element.value);
                currentSize ++;
            }
        }
        catch (std::bad_alloc& badAlloc)
        {
            for (int i = 0; i < originalSize; i++) {
                pushBack(front());
                popFront();
            }
            for (int i = 0; i < currentSize; i++) {
                popFront();
            }

            throw badAlloc;
        }

        for(int i = 0; i < originalSize; i++)
        {
            popFront();
        }
        return *this;
    }

/**
 * destructor
 * inputs: none
 * outputs: none
 * possible errors: none
 */
    ~Queue()
    {
        while(!empty())
        {
            popFront();
        }
    }

/**
 * function to check if the Queue is empty
 * inputs: none
 * outputs: const bool
 * possible errors: none
 */
    bool empty() const
    {
        return m_head == nullptr;
    }

/**
 * function to add data to Queue
 * inputs: T data
 * outputs: none
 * possible errors: std::bad_alloc
 */
    void pushBack(T data)
    {
        Element* newElement = new Element(data);
        if(empty())
        {
            m_head = newElement;
            m_tail = newElement;
            return;
        }

        m_tail->next = newElement;
        m_tail = newElement;
    }

/**
 * function to return the value at the front of the Queue
 * inputs: none
 * outputs: reference to T data
 * possible errors: EmptyQueue error
 */

    T& front() const
    {
        if(empty())
        {
            throw EmptyQueue();
        }
        return m_head->value;
    }

/**
 * function to remove data from front of Queue
 * inputs: none
 * outputs: none
 * possible errors: EmptyQueue error
 */
    void popFront()
    {
        if(empty()) {
            throw EmptyQueue();
        }

        Element* temp = m_head;
        m_head = m_head->next;
        if(m_head == nullptr)
        {
            m_tail = nullptr;
        }

       delete temp;
    }

/**
 * function to get current size of the Queue
 * inputs: none
 * outputs: int size of queue
 * possible errors: none
 */
    int size() const
    {
        if(empty()) {
            return 0;
        }
        int counter = 1;
        Element* temp = m_head;
        while(temp->next != nullptr)
        {
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    class Iterator;
    class ConstIterator;

    /**
 * function to get iterator of first element in queue
 * inputs: none
 * outputs: Iterator
 * possible errors: none
 */
    Iterator begin()
    {
        return Iterator(this, m_head);
    }

    /**
 * function to get iterator after the last element in queue (element->next nullptr)
 * inputs: none
 * outputs: Iterator
 * possible errors: none
 */
    Iterator end()
    {
        if(empty()) {
            return Iterator(this, m_tail);
        }
        return Iterator(this, m_tail->next);
    }

    /**
 * function to get constant iterator of first element in queue
 * inputs: none
 * outputs: ConstIterator
 * possible errors: none
 */
    ConstIterator begin() const
    {
        return ConstIterator(this, m_head);
    }

    /**
 * function to get const iterator after the last element in queue (element->next nullptr)
 * inputs: none
 * outputs: ConstIterator
 * possible errors: none
 */
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
        T value;
        Element *next;
        /**
* constructor which creates an Element within a linked list
* inputs: T data
* outputs: none
* possible errors: std::bad_alloc
*/
        Element(T data): value(data), next(nullptr){};
    };

    /**
     * pointers to first and last element in our linked list data structure
*/
    Element* m_head;
    Element* m_tail;

};

/**
* function to return new Queue which is made up of elements of another queue
 * which meet some condition.
 *
* inputs: some Queue object, boolean Function Pointer/Object
* outputs: Queue object
* possible errors: std::bad_alloc, or any other errors from the function (user function)
*/
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

/**
* function to return new Queue which has transformed all the data of the queue
 * using some function
* inputs: some Queue object, tranformer Function Pointer/Object
* outputs: Queue object
* possible errors: std::bad_alloc, or any other errors from the function (user function)
*/

template <class S, class F>
void transform(Queue<S>& queue, const F func)
{
    for(S& value:queue)
    {
        func(value);
    }
}



template<class T>
class Queue<T>::Iterator
{
private:
    Queue<T>* const m_queue;
    Queue<T>::Element* m_elementPtr;

    /**
* constructor
* inputs: pointer to Queue, pointer to element
* outputs: none
* possible errors: none
*/
     Iterator(Queue<T>* const queue, Queue<T>::Element* const element)
                      : m_queue(queue), m_elementPtr(element) {};

    /**
* assignment operator
* inputs: reference to Iterator
* outputs: reference Iterator
* possible errors: none
*/
    Iterator& operator=(const Iterator& iterator)
    {
        if (iterator == m_queue->end()) {
            throw InvalidOperation();
        }
        assert (m_queue == iterator.m_queue && (this != iterator));
        m_elementPtr = iterator.m_elementPtr;
    }

    friend class Queue<T>;


public:

    class InvalidOperation {};

    /**
* constructor
* inputs: const reference to Iterator
* outputs: none
* possible errors: none
*/

    ///are these needed?
    Iterator(const Iterator& iterator) = default;
    /// does this copy c'tor need to be non default?-> : m_queue(iterator.m_queue), m_elementPtr(iterator.m_elementPtr) {}

    /**
* dereferencing operator which returns the Queue's value from the Iterator
* inputs: none
* outputs: reference to T data
* possible errors: InvalidOperation error
*/
    T& operator*() const
    {
        if (*this == m_queue->end()) {
            throw InvalidOperation();
        }
        assert(m_elementPtr!= nullptr);
        return m_elementPtr->value;
    }

    /**
* increment operator which returns the Queue's next iterator
* inputs: none
* outputs: reference to Iterator
* possible errors: InvalidOperation error
*/
    Iterator& operator++()
    /// change all iterators++ to ++iterators in set
    {
        if (*this == m_queue->end()) {
            throw InvalidOperation();
        }
        m_elementPtr= m_elementPtr->next;
        return *this;
    }

    /**
* postfix increment operator which returns the Queue's next iterator
* inputs: int dummy argument
* outputs: Iterator
* possible errors: none
*/
    Iterator operator++(int)
    {
        Iterator result = *this;
        ++(*this); //Calls the prefix operator on the original iterator
        return result; //returns the value of the iterator before the change
    }

    /**
*  equality operator which checks if 2 iterators (this and other) point to the same data in the linked list
* inputs: Iterator reference
* outputs: boolean value
* possible errors: none
*/

    bool operator==(const Iterator& iterator) const
    {
        assert(m_queue == iterator.m_queue);
        return m_elementPtr == iterator.m_elementPtr;
    }

    /**
*  inequality operator which checks if 2 iterators (this and other) do NOT point to the same data in the linked list
* inputs: Iterator reference
* outputs: boolean value
* possible errors: none
*/
    bool operator!=(const Iterator& iterator) const
    {
        return !( *this == iterator );
    }

};
template<class T>
class Queue<T>::ConstIterator
{
private:
    const Queue<T>* const m_queue; ///the const queue of cIterator
    const Queue<T>::Element* m_elementPtr;

    ConstIterator(const Queue<T>* const queue, const Queue<T>::Element* element)
            : m_queue(queue), m_elementPtr(element) {};
    friend class Queue<T>;



public:
    class InvalidOperation {};
    /**
* constructor
* inputs: const reference to ConstIterator
* outputs: none
* possible errors: none
*/
    ConstIterator(const ConstIterator& cIterator) = default;

    ConstIterator& operator=(const ConstIterator& cIterator) = delete;

    /**
  * dereferencing operator which returns const of the Queue's value from the ConstIterator
  * inputs: none
  * outputs: const reference to T data
  * possible errors: InvalidOperation error
  */
    const T& operator*() const
    {
        if (*this == m_queue->end()) { /// omer 31/12: this or *this?
            throw InvalidOperation();
        }
        return m_elementPtr->value;
    }

    /**
* increment operator which returns the Queue's next constiterator
* inputs: none
* outputs: reference to ConstIterator
* possible errors: InvalidOperation error
*/
    ConstIterator& operator++()
    {
        if (*this == m_queue->end()) {
            throw InvalidOperation();
        }
        m_elementPtr= m_elementPtr->next;
        return *this;
    }

    /**
* postfix increment operator which returns the Queue's next constiterator
* inputs: int dummy argument
* outputs: ConstIterator
* possible errors: none
*/
    ConstIterator operator++(int)
    {
        ConstIterator result = *this;
        ++(*this); //Calls the prefix operator on the original cIterator
        return result; //returns the object of the cIterator before the change
    }

    /**
*  equality operator which checks if 2 constiterators point (this and other) to the same data in the linked list
* inputs: ConstIterator reference
* outputs: boolean value
* possible errors: none
*/
    bool operator==(const ConstIterator& cIterator) const
    {
        assert(m_queue == cIterator.m_queue);
        return m_elementPtr == cIterator.m_elementPtr;
    }

    /**
*  inequality operator which checks if 2 constiterators (this and other) do NOT point to the same data in the linked list
* inputs: ConstIterator reference
* outputs: boolean value
* possible errors: none
*/
    bool operator!=(const ConstIterator& cIterator) const
    {
        return !( *this == cIterator );
    }

};
#endif
