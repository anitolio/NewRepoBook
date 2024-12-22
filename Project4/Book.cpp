#include <iostream>  
#include <cstring>  
using namespace std;

class Book {
private:
    char* Author;
    char* text;
    int pages;
    int year;

public:
    Book() : Author(nullptr), text(nullptr), pages(0), year(0) {}

    Book(const char* author, const char* textContent, int numPages, int pubYear) {
        Author = new char[strlen(author) + 1];
        strcpy(Author, author);
        text = new char[strlen(textContent) + 1];
        strcpy(text, textContent);
        pages = numPages;
        year = pubYear;
    }

    ~Book() {
        delete[] Author;
        delete[] text;
    }

    void display() const {
        cout << "Author: " << (Author ? Author : "Unknown") << endl;
        cout << "Text: " << (text ? text : "No text") << endl;
        cout << "Pages: " << pages << endl;
        cout << "Year: " << year << endl;
    }
 
    Book(const Book& obj) = delete;
    Book& operator=(const Book& obj) = delete;

    Book(Book&& obj) noexcept
        : Author(obj.Author), text(obj.text), pages(obj.pages), year(obj.year) {
        obj.Author = nullptr;
        obj.text = nullptr;
    }

    Book& operator=(Book&& obj) noexcept {
        if (this != &obj) {
            delete[] Author;
            delete[] text;

            Author = obj.Author;
            text = obj.text;
            pages = obj.pages;
            year = obj.year;

            obj.Author = nullptr;
            obj.text = nullptr;
        }
        return *this;
    }
};

int main() {
    Book myBook("Author Name", "This is the text of the book.", 300, 2021);

    cout << "My Book Information:" << endl;
    myBook.display();

    Book anotherBook = std::move(myBook);

    cout << "\nAnother Book Information:" << endl;
    anotherBook.display();

    cout << "\nMy Book after move (not displayed due to moved resources):" << endl;

    return 0;
}
