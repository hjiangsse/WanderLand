#include "stack.h"

bool Stack::push(const string& elem) {
  if(full())
	return false;

  _stack.push_back(elem);
  return true;
}

bool Stack::pop(string &elem) {
  if(empty())
	return false;
  
  elem = _stack.back();
  _stack.pop_back();
  return true;
}

bool Stack::peek(string &elem) {
  if(empty())
	return false;
  
  elem = _stack.back();
  return true;
}

bool Stack::sfind(const string &elem) {
  if(find(_stack.begin(), _stack.end(), elem) != _stack.end()) 
	return true;

  return false;
}

int Stack::count(const string &elem) {
  int cnt = 0;
  vector<string>::iterator pos = _stack.begin();
  while((pos = find(pos, _stack.end(), elem)) != _stack.end()) {
	pos++;
	cnt++;
  }
  return cnt;
}
