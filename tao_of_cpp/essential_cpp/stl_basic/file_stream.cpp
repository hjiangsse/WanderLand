#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main() {
  ifstream infile("input_file.txt");
  ofstream outfile("output_file.txt");

  if(!infile || !outfile) {
	cerr << "!! unable to open the neccessary file.\n";
  }

  istream_iterator<string> is(infile);
  istream_iterator<string> eof;

  vector<string> text;
  copy(is, eof, back_inserter(text));

  sort(text.begin(), text.end());

  ostream_iterator<string> os(outfile, "|");
  copy(text.begin(), text.end(), os);
  return 0;
}
