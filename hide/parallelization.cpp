#include <iostream>
#include <string>
#include <thread>
#include <vector>

class MyClass {
public:
  MyClass(const std::string& name) : name_(name) {}

  void main() {
    // Perform some operations using the name
    std::cout << "Hello from " << name_ << "!" << std::endl;
  }

private:
  std::string name_;
};

int main() {
  // Create a vector of MyClass objects with different names
  std::vector<MyClass> objects;
  objects.emplace_back("Object 1");
  objects.emplace_back("Object 2");
  objects.emplace_back("Object 3");

  // Create threads to run main for each object
  std::vector<std::thread> threads;
  for (auto& obj : objects) {
    threads.emplace_back([&obj]() { obj.main(); });
  }

  // Join the threads
  for (auto& thread : threads) {
    thread.join();
  }

  return 0;
}