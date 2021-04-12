// g++ -g -O0 priority_queue_stl_impl.cpp -o priority_queue_stl_impl.out -std=c++11

// ./priority_queue_stl_impl.out
// Topping and poping out all elements...
// priority 100 name task_100
// priority 10 name task_10
// priority 5 name task_5
// priority 3 name task_3
// priority 2 name task_2
// priority 1 name task_1

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <functional>     // std::greater and std::less

class ELEMENT
{
 public:
    ELEMENT() {}
    ELEMENT(std::string name, int priority) :
        m_name(name), m_priority(priority) {}

    virtual ~ELEMENT() {}

    int get_priority() const { return m_priority;}
    std::string get_name() const { return m_name; }

    friend bool operator < (const ELEMENT& lhs, const ELEMENT& rhs)
    {
        return lhs.get_priority() < rhs.get_priority();
    }

    friend bool operator > (const ELEMENT& lhs, const ELEMENT& rhs)
    {
        return lhs.get_priority() > rhs.get_priority();
    }

 private:
    std::string m_name;
    int m_priority;
};

int main()
{
    std::priority_queue<ELEMENT,std::vector<ELEMENT>> my_pqueue;

    ELEMENT task_3("task_3", 3);
    ELEMENT task_5("task_5", 5);
    ELEMENT task_1("task_1", 1);
    ELEMENT task_10("task_10", 10);
    ELEMENT task_2("task_2", 2);
    ELEMENT task_100("task_100", 100);

    my_pqueue.push(task_3);
    my_pqueue.push(task_5);
    my_pqueue.push(task_1);
    my_pqueue.push(task_10);
    my_pqueue.push(task_2);
    my_pqueue.push(task_100);

    std::cout << "Topping and poping out all elements..." << std::endl;
    while (!my_pqueue.empty())
    {
        std::cout << "priority " << my_pqueue.top().get_priority() << " name " << my_pqueue.top().get_name() << std::endl;
        my_pqueue.pop();
    }

    return 0;
}
