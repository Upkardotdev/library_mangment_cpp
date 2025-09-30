#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Book {

    private:
        int id;
        string name;
        string author;
        bool isIssued;
    
    public:
        Book (int bid, string bname, string bauthor, bool status = false){
            id = bid;
            name = bname;
            author = bauthor;
            isIssued = status;
        }

        void display (){
            cout << "Id: " << id
                << " , Name: " << name
                << " ,Author: " << author
                << " , is issued? " << (isIssued ? "yes" : "no") 
                << endl;
        }


        int getId () {return id;}
        string getName(){return name;}
        string getAuthor () {return author;}
        bool getIsIssued () {return isIssued;}

        void setIsIssued (bool status) {isIssued = status;}
};

class Library {

    private:
        vector<Book> books;

    public:

        Library(){
            loadBooks();
        }

        ~Library(){
            saveBooks();
        }

        // all the methods
        void addBook(int id, string name, string author){
            for (auto &book : books){
                if (id == book.getId() || name == book.getName()){
                    cout << "This book is already added in library" << endl;
                    return;
                }
            }
            books.push_back(Book(id , name , author));
            cout << "Book added" << endl;
        }

        void displayBooks () {
            if (books.empty()){
                cout << "No books in the library \n";
                return;
            }
            for(auto &book : books){
                book.display();
            }
        }


        void issueBook (int bookId) {
            for(auto &book : books){
                if(bookId == book.getId()){
                    if(book.getIsIssued()){
                        cout << "Book is availabel but already taken\n";
                    }else {
                        book.setIsIssued(true);
                        cout << "Book issued\n";
                    }
                    return;
                }
            }
            cout << "Book isn't availabel\n";
        }

        void returnBook (int bookId) {
            for (auto &book : books){
                if(bookId == book.getId()){
                    if(book.getIsIssued()){
                        book.setIsIssued(false);
                        cout << "Thank you for returning book. \n";
                    }else{
                        cout << "this is extra book.\n";
                    }
                    return;
                }
            }
            cout << "Invalid id\n";
        }

        void saveBooks () {
            ofstream fout("books.txt");
            for(auto &book : books){
                fout << book.getId() << " " 
                << book.getName() << " " 
                << book.getAuthor() << " " 
                << (book.getIsIssued() ? 1 : 0) << endl;
            }
            fout.close();
        }

        void loadBooks(){
            ifstream fin("books.txt");
            if (!fin) return;

            string line;
            while(getline(fin , line)){
                stringstream ss(line);
                int id , issuedInt;
                string name , author;
                ss >> id >> name >> author >> issuedInt;
                books.push_back(Book(id , name , author , issuedInt == 1));
            }
            fin.close();
        }

        void searchBook(string name){
            for (auto &book : books){
                if(name == book.getName()){
                    book.display();
                    return;
                }
            }
            cout << "Book not availabel.\n";
        }
};

int main (){

    Library lib;
    int choice, tempId;
    string tempName , tempAuthor;

    while(true){
        cout << "1. Add New Book\n" << "2. Search Book\n"
        << "3. Display All Books\n" << "4. Take a Book\n"
        << "5. Return a book\n" << "6. Leave the program\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice){
            case 1:
                cout << "Enter Book ID: ";
                cin >> tempId;
                cin.ignore();
                cout << "Enter Book Name: ";
                getline(cin , tempName);
                cout << "Enter Author Name: ";
                getline(cin , tempAuthor);
                lib.addBook(tempId , tempName , tempAuthor);
                break;

            case 2:
                cout << "Name of the book you want to search for? ";
                getline(cin , tempName);
                lib.searchBook(tempName);
                break;

            case 3:
                lib.displayBooks();
                break;

            case 4:
                cout << "Enter the Id of the book: ";
                cin >> tempId;
                lib.issueBook(tempId);
                break;

            case 5:
                cout << "Enter the Id of the book: ";
                cin >> tempId;
                lib.returnBook(tempId);
                break;

            case 6:
                cout << "Exiting program..." << endl;
                return 0;
            
            default:
                cout << "Invalid choice";
                break;
        }


    }
}