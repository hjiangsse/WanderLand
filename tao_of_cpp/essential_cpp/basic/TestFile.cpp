#include <iostream>
#include <fstream>

using namespace std;

int main() {
  ofstream outfile("seq_date.txt");

  if(!outfile)
  {
    cerr << "Sorry, unable save data to file!" << endl;
  }
  else
  {
    outfile << "Name: hjiang\n"
            << "Age: 30\n"
            << "Flag: Keep coding\n";
  }

  ifstream infile("seq_file.txt");
  if(!infile)
  {
    cerr << "Sorry, unable to open file!" << endl;
  }
  else
  {
    string key;
    string value;
    while(infile >> key >> value)
    {
      cout << key << "**" <<value << endl;
    }
  }
  
  return 0;
}
