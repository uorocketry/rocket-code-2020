#include <iostream>
#include <queue>
using namespace std;

struct Customer
{
	int time;
	int priority;
}cust;

int main()
{
    Customer c1 = {45,1};
    Customer c2 = {46,2};
    Customer c3 = {47,3};

    queue<Customer> myqueue;
    myqueue.push(c1);
    myqueue.push(c2);
    myqueue.push(c3);

    while(!myqueue.empty())
    {
        Customer temp = myqueue.front();
        myqueue.pop();
        cout << "Priority: " << temp.priority << endl;
        cout << "Time: "<< temp.time << endl;
        cout << "\n";
    }

    return 0;
}
