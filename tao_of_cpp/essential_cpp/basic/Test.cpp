#include <iostream>
#include <vector>

using namespace std;

const int seq_size = 20;
const int seq_cnt = 6;

void SeqGen(vector<int> *pSeq, const char *name);
void PrintSeq(vector<int> *pSeq);

int seq_sum(uint i);

int main() {
   vector<int> fibonacci(seq_size);
   vector<int> lucas(seq_size);
   vector<int> pell(seq_size);
   vector<int> triangular(seq_size);
   vector<int> square(seq_size);
   vector<int> pentagonal(seq_size);

   SeqGen(&fibonacci, "Fibonacci");
   SeqGen(&lucas, "Lucas");
   SeqGen(&pell, "Pell");
   SeqGen(&triangular, "Triangular");
   SeqGen(&square, "Square");
   SeqGen(&pentagonal, "Pentagonal");

   vector<int> *seq_addrs[seq_cnt] =
   {
      &fibonacci, &lucas, &pell,
      &triangular, &square, &pentagonal
   };

   //print out the six seq
   for(int i = 0; i < seq_cnt; i++) {
     PrintSeq(seq_addrs[i]);
   }
   
   return 0;
}

void PrintSeq(vector<int> *pSeq)
{
    for(int idx = 0; idx < pSeq->size(); idx++)
    {
        cout << (*pSeq)[idx] << " ";
    }
    cout << endl;
}

void SeqGen(vector<int> *pSeq, const char *name)
{
  if(string(name) == "Fibonacci") {
    if(pSeq->size() > 1) {
      (*pSeq)[0] = 1;
    }

    if(pSeq->size() > 2) {
      (*pSeq)[1] = 1;
    }

    if(pSeq->size() > 3) {
      for(int idx = 2; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = (*pSeq)[idx-1] + (*pSeq)[idx-2]; 
      }
    }
  }

  if(string(name) == "Lucas") {
    if(pSeq->size() > 1) {
      (*pSeq)[0] = 1;
    }

    if(pSeq->size() > 2) {
      (*pSeq)[1] = 3;
    }

    if(pSeq->size() > 3) {
      for(int idx = 2; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = (*pSeq)[idx-1] + (*pSeq)[idx-2]; 
      }
    }
  }

  if(string(name) == "Pell") {
    if(pSeq->size() > 1) {
      (*pSeq)[0] = 1;
    }

    if(pSeq->size() > 2) {
      (*pSeq)[1] = 2;
    }

    if(pSeq->size() > 3) {
      for(int idx = 2; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = 2 * (*pSeq)[idx-1] + (*pSeq)[idx-2]; 
      }
    }
  }

  if(string(name) == "Triangular") {
      for(int idx = 0; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = seq_sum(idx + 1);   
      }
  }

  if(string(name) == "Square") {
      for(int idx = 0; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = (idx + 1) * (idx + 1);   
      }
  }

  if(string(name) == "Pentagonal") {
      for(int idx = 0; idx < pSeq->size(); idx++) {
	(*pSeq)[idx] = ((idx + 1) * (3 * (idx + 1) - 1)) / 2;   
      }
  }
}

int seq_sum(uint i) {
  int sum = 0;
  for(int j = 0; j <= i; j++) {
    sum += j;
  }
  return sum;
}
