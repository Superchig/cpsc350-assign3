#include <iostream>
using namespace std;

template <typename T>
class GenStack {
public:
  GenStack();
  GenStack(int maxSize); // Overloaded constructor
  ~GenStack();

  // Functions
  void push(T data);
  T pop();

  // Helper functions
  bool isFull();
  bool isEmpty();
  T peek();

  int maxSize; // max size
  // variable to keep track of indices representing the top of our stack
  int top;
  T *myArray;
};

// Default constructor
template <typename T>
GenStack<T>::GenStack()
{
  myArray = new T[128];
  maxSize = 128;
  top = -1;
}

// Overloaded constructor
template <typename T>
GenStack<T>::GenStack(int maxSize)
{
  myArray = new T[maxSize];
  maxSize = maxSize;
  top = -1;
}

template <typename T>
GenStack<T>::~GenStack()
{
  // We should figure this one out
  delete[] myArray;
}

template <typename T>
void GenStack<T>::push(T data)
{
  // Check if full before inserting
  if (isFull()) {
    T *origItems = myArray;
    myArray = new T[maxSize * 2];

    // Copy over items from original array to new one
    for (int i = 0; i < maxSize; ++i) {
      myArray[i] = origItems[i];
    }

    delete[] origItems;
    maxSize *= 2;
  }

  myArray[++top] = data;
}

template <typename T>
T GenStack<T>::pop()
{
  // Check if empty before proceeding to remove
  if (isEmpty()) {
    throw out_of_range("Tried to pop() from empty stack.");
    return '\0';
  }

  return myArray[top--];
}

template <typename T>
T GenStack<T>::peek()
{
  // Check if empty
  return myArray[top];
}

template <typename T>
bool GenStack<T>::isFull()
{
  return (top >= maxSize - 1);
}

template <typename T>
bool GenStack<T>::isEmpty()
{
  return (top <= -1);
}