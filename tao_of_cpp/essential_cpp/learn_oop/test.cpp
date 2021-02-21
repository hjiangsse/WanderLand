#include <iostream>
#include <string>

using namespace std;

class LibMat {
public:
    LibMat() {
		cout << "LibMat::LibMat() default constructor!\n";
    }
	
    virtual ~LibMat() {
		cout << "LibMat::~LibMat() destructor!\n";
    }

	virtual void print() const {
		cout << "LibMat:: print -- I am a LibMat object!\n";
	}
};

class Book : public LibMat {
public:
	Book(const string &title, const string& author)
		:_title(title), _author(author) {
		cout << "Book::Book( " << _title
			 << ", " << _author << " )" <<endl;
	}

	virtual ~Book() {
		cout << "Book::~Book() destructor!\n";
	}

	virtual void print() const {
		cout << "Book:: print -- I am a Book object!\n"
			 << "My title is: " << _title << '\n'
			 << "My author is: " << _author << endl;
	}

	const string& title() const { return _title; }
	const string& author() const { return _author; }
protected:
	string _title;
	string _author;
};

class AudioBook: public Book {
public:
	AudioBook(const string &title,
			  const string &author,
			  const string &speaker)
		:Book(title, author),
		 _speaker(speaker)
	{
		cout << "AudioBook::AudioBook( " << _title
			 << ", " << _author
			 << ", " << _speaker
			 <<" )" <<endl;
	}

	virtual ~AudioBook() {
		cout << "AudioBook::~AudioBook() destructor!\n";
	}

	virtual void print() const {
		cout << "AudioBook:: print -- I am a AudioBook object!\n"
			 << "My title is: " << _title << '\n'
			 << "My author is: " << _author << '\n'
			 << "The speaker is: " << _speaker << endl;
	}
private:
	string _speaker;
};

void print(const LibMat &mat)
{
	cout << "in global print(): about to print mat.print()\n";
	mat.print();
}

int main(int argc, char **argv) {
	LibMat libmat;
	print(libmat);

	Book book("The book of change", "God");
	print(book);

	AudioBook ab("zuangzi", "zhuangzhou", "hjiang");
	print(ab);
    return 0;
}
