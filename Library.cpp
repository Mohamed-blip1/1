#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

class Book
{
public:
    string title;
    string author;
    int year;

    void printBooksInfo()
    {
        string alinedString = "Author :";
        int index = alinedString.length() - 1;

        cout << "\n📖 Book Details:" << endl;
        cout << endl;
        cout << setw(index) << left << "Title" << ": " << title << endl;
        cout << setw(index) << left << "Author" << ": " << author << endl;
        cout << setw(index) << left << "Year" << ": " << year << endl;
    }
    void ReadFromUser()
    {
        cout << "Enter the title of your book: ";
        getline(cin, title);
        cout << endl;

        cout << "Enter the name of the author: ";
        getline(cin, author);
        cout << endl;

        bool ValidNumber = false;
        do
        {
            cout << "Enter the year of the book: ";
            cin >> year;
            cout << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << "\n❌ Not Valid Year!\n";
            }
            else
                ValidNumber = true;
        } while (!ValidNumber);
    }
};

int ReadValidNumber()
{
    int validNumber;
    cin >> validNumber;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
        return -1;
    }
    else
        return validNumber;
}

string StringTolower(const string &str)
{
    string lowerCaseString;
    transform(str.begin(), str.end(), lowerCaseString.begin(), ::tolower);
    return lowerCaseString;
}

int menu()
{
    int choice;
    do
    {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "• 1.Add a Book 📔" << endl;
        cout << "• 2.Search 🔎" << endl;
        cout << "• 3.Delete 🗑️" << endl;
        cout << "• 4.library 📚" << endl;
        cout << "• 5.Clear all" << endl;
        cout << "• 0.Exit ↙" << endl;
        cout << endl;
        cout << ">";

        choice = ReadValidNumber();
        if (choice < 0 || choice > 5)
            cout << "\n❌ Wrong Choice, Please Enter a valid Choice" << endl;

    } while (choice == -1 || choice < 0 || choice > 5);

    cout << endl;
    cin.ignore();

    if (choice == 0)
        cout << "Goodbye 👋";

    return choice;
}

void notValidTitleWarning(vector<Book> &library, string bookTitle)
{
    if (library.empty())
        cout << "\n🚫 Library is empty!" << endl;
    else
    {
        cout << endl;
        cout << "⚠️  Warning" << endl;
        cout << endl;
        cout << "🤔 No book found with this Title '" << bookTitle << "'!" << endl;
        cout << endl;
        cout << "📚 Try opening your library 📚" << endl;
    }
}

void PrintLibrary(vector<Book> &library)
{
    cout << "\n📚  Library:\n";

    if (library.empty())
        cout << "\n🚫 Library is empty!" << endl;
    else
        for (int i = 0; i < library.size(); i++)
        {
            cout << "\n"
                 << i + 1 << ".";
            library[i].printBooksInfo();
        }
}

int Search(vector<Book> &library, string bookTitle)
{
    for (int i = 0; i < library.size(); i++)
    {
        if (StringTolower(library[i].title) == StringTolower(bookTitle))
        {
            return i;
        }
    }
    return -1;
}

void BookSearchAndDelet(vector<Book> &library, int choice)
{
    string bookTitle;
    int ValidTitle;
    string msg;

    if (choice == 2)
        msg = "srearch for: ";
    else
        msg = "delete🗑️ : ";

    cout << "🧐 Enter Book Title you want to " << msg;
    getline(cin, bookTitle);

    ValidTitle = Search(library, bookTitle);
    cout << endl;

    if (ValidTitle == -1)
    {
        notValidTitleWarning(library, bookTitle);
    }
    else
    {
        library[ValidTitle].printBooksInfo();

        if (choice == 3)
        {
            cout << endl;
            library.erase(library.begin() + ValidTitle);
            cout << "Deletion success ✅️" << endl;
        }
    }
}

void clearAll(vector<Book> &library)
{
    int choice;
    cout << "Confirm clear all Library:" << endl;
    do
    {
        cout << endl;
        cout << "• 1.Confirm" << endl;
        cout << "• 2.Undo" << endl;
        cout << endl;
        cout << ">";
        choice = ReadValidNumber();

        if (choice < 1 || choice > 2)
            cout << "\n❌ Wrong Choice, Please Enter a valid Choice" << endl;

    } while (choice == -1 || choice < 1 || choice > 2);
    cout << endl;
    if (choice == 1)
    {
        library.clear();
        cout << "Success, all Clear ✅️" << endl;
    }
}

void AplayingOnLibrary(vector<Book> &library, const int choice)
{

    switch (choice)
    {
    case 1: // Add book
    {
        Book book;

        book.ReadFromUser();
        library.push_back(book);
        book.printBooksInfo();
    }
    break;
    case 2: // Search by Title
    case 3: // Delete by Title
        BookSearchAndDelet(library, choice);
        break;
    case 4: // Show library
        PrintLibrary(library);
        break;
    case 5:
        clearAll(library);
        break;
    }
}

int main()
{
    vector<Book> library;
    int choice;
    int i = 0;

    cout << "🚪 Welcom to your lite Library:";
    do
    {
        cout << endl;
        choice = menu();
        if (!choice)
            break;
        AplayingOnLibrary(library, choice);
    } while (choice);

    return 0;
}
