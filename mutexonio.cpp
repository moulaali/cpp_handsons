/**
 * A small example to apply c++ mutexes to synchronize io from multiple threads.
 *
 * Run command: g++ --std=c++0x -pthread thread_try1.cc ; ./a.out
 */
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

using std::mutex;
using std::unique_lock;

mutex io_mutex;

void print() {
  unique_lock<mutex> lck {io_mutex}; // acquire mutex
  std::cout << "hello from thread using function pointer. my id is " << std::this_thread::get_id() << std::endl;
}

class functor {
 public:
  void operator()() {
    unique_lock<mutex> lck {io_mutex}; // acquire mutex
    std::cout << "hello from thread using functor. my is is: " << std::this_thread::get_id() << std::endl;
  }
};


int main()
{
  // thread using function pointer
  std::thread thread1(print);

  // thread using functor (function object)
  functor fctr;
  std::thread thread2(fctr);

  thread1.join();
  thread2.join();

  std::cout << "Thread hardware concurrency : "
            <<  std::thread::hardware_concurrency() << std::endl;
}
