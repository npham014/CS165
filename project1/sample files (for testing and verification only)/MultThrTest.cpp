#include <iostream>
#include <thread>

using namespace std;

void print1()
{
  cout << 1;
}

int main() // source: geeksforgeeks.org/multithreading-in-cpp/
{
  cout << "hello" << endl;
  thread x(print1); // acts as fork
  //cout << "goodybye" << endl;

  x.join(); // acts as wait
  cout << "\ngoodbye" << endl;
}
