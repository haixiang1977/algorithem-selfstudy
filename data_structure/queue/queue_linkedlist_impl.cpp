// queue implemented with linked list
// g++ queue_linkedlist_impl.cpp -o queue_linkedlist_impl.out
// ./queue_linkedlist_impl.out
// expected size 3, size 3
// expected front 100, front 100
// expected back 300, back 300
// expected front 200, front 200

#include <iostream>
#include <list>

using namespace std;

class Queue
{
 public:
    Queue();
    virtual ~Queue();

    size_t size();
    int front();
    int back();
    void push(int val);
    void pop();
    
 private:
    list<int> m_list;
};

Queue::Queue()
{
}

Queue::~Queue()
{
}

size_t Queue::size()
{
    return m_list.size();
}

int Queue::front()
{
    return m_list.front();
}

int Queue::back()
{
    return m_list.back();
}

void Queue::push(int val)
{
    return m_list.push_back(val);
}

void Queue::pop()
{
    return m_list.pop_front();
}

int main()
{
    Queue my_queue;

    my_queue.push(100);
    my_queue.push(200);
    my_queue.push(300);

    cout << "expected size 3, size " << my_queue.size() << endl;

    cout << "expected front 100, front " << my_queue.front() << endl;
    cout << "expected back 300, back " << my_queue.back() << endl;

    my_queue.pop();
    cout << "expected front 200, front " << my_queue.front() << endl;

    return 0;
}
