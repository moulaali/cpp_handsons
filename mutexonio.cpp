#include <mutex>
#include <queue>

using namespace std;

mutex io_mutex;

class Message {
 
 private:
  string msg;

 public:

  Message(string message) {
    msg = message;
  }

  void print() {
    cout << "Message: " << msg << endl;
  }
};

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


void print_queue(queue<Message> q) {
  cout << "Queue contents" << endl;

  while (!q.empty()) {
    Message m = q.front();
    m.print();
    q.pop();
  }
}

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

  // Create a shared message queue for producer consumer
  Message m1("first");
  Message m2("second");

  queue<Message> message_queue;

  message_queue.push(m1);
  message_queue.push(m2);

  print_queue(message_queue);
}
