#include "GenStack.h"
#include <cassert>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  GenStack<int> stack;

  assert(stack.isEmpty());

  for (int i = 0; i < 128; ++i) {
    stack.push(i);
  }

  assert(stack.isFull());

  for (int i = 0; i < 10; ++i) {
    stack.push(i * 10);
  }

  assert(!stack.isFull());

  while (!stack.isEmpty()) {
    cout << stack.pop() << endl;
  }

  cout << "Max size of stack: " << stack.maxSize << endl;

  cout << "Test of stack succeeded!" << endl;
  return 0;
}
