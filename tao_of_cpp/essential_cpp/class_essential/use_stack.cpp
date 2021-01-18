#include "stack.h"
#include <iostream>

using namespace std;

int main() {
  Stack stack;
  stack.push("this");
  stack.push("is");
  stack.push("the");
  stack.push("the");
  stack.push("the");
  stack.push("end");

  /*
  string top_elem;
  if(stack.peek(top_elem)) {
	cout << "Now the top element of stack is: " << top_elem << endl;
  }

  if(stack.pop(top_elem)) {
	if(stack.peek(top_elem)) {
	cout << "Now the top element of stack is: " << top_elem << endl;
	}
  }

  if(stack.sfind("is")) {
	cout << "Find it!" << endl;
	}*/

  cout << "The count of \"the\" " << stack.count("the") << endl;

  return 0;
}
