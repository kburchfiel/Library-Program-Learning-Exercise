//AMDG

//For this learning exercise, which aims to answer one of the questions in Programming: Principles and Practice using C++ (a book that I am studying independently), I went off the script a little but still fulfilled the major concepts. I had represented books and patrons as elements of a vector, so I ran into trouble when asked to create a vector of transactions that was based on books and patrons. At this stage in my C++ learning journey, I wasn't sure how to model a vector of vectors, all with custom types. So instead, I created a giant vector that held copies of all the members of the other relevant classes, and not the classes themselves. This was unwieldy and clunky, but it was intuitive enough and it worked.
//I'm not sure that the exercise even asked us to respond to user input, but I figured that would be an important learning tool.
//I also aimed to allow users to correct erroneous input through the use of while loops, rather than terminating the program with an error message.
//I imagine this program still has some bugs, and there are plenty of ways it can be improved and simplified. However, I learned a lot from this experinece, and hope to incorporate some of the practices I used in future C++ programming.

//Credit to Chrinkus for showing me how to get the genre to successfully cout (my code for that is copied from his), and for serving as a reference at other points as well. (https://github.com/Chrinkus/stroustrup-ppp/blob/master/chapter09/ex05-9_library/ex05_book.cpp)

//Kenneth Burchfiel, 4/25/2020



using namespace std;
#include <iostream>
#include <vector>

//Putting this within Book didn't seem to work, so I moved it outside of the definition for class Book instead
enum class Genre
{
    fiction = 0,
    nonfiction,
    periodical,
    biography,
    children
};

class Book
{
public:
    vector<Book> booklist;

    void book_entry();
    void list_books();
    void checkout();
    void returnbook();
    void data();
    Book(string title, string author, Genre genre, string ISBN, int cdate, bool checkedout);
    //See p. 1111 of PPAP 2nd ed. for more about Friend functions

private:
    //I tried using the friend element to make ISBN and checkout public, but it didn't work--so I made everything public instead.
    friend struct Transaction;
    string title;
    string author;
    string ISBN;
    Genre genre;
    int cdate;
    bool checkedout;
};

class Patron
{
public:
    vector<Patron> patronlist;
    Patron(string username, int cardnum, double fees);
    void addpatron();
    void patrondata();
    void listpatrons();
    void patronfee();
    void whoowesfees();
    //Made these public so that they could be accessed (as part ofthe vector "patronlist") by the helper function arefeesowed. Perhaps there's a better way to go about this.
    string username;
    double fees;

private:
    friend struct Transaction;
    int cardnum;
};

class Library
{ //I didn't end up using this class, as I had already made vectors of books and patrons within my Book and Patron classes.
};

class Date
{
public:
    Date(int day, string month, int year);
    void verifydate();
    vector<Date> dates;

private:
    friend struct Transaction;
    int day;
    string month;
    int year;
};

//The order of these classes matters! I had placed Transaction before Date, but then the compiler didn't realize that Date existed and therefore said that Date had not been declared. Putting Date before Transaction solved that problem.

struct Transaction
{
    //When selecting values (e.g. bo, pa, da) for these members, you don't want to use values that are also the values of objects for those classes. I had used x for Book, but that messed up a function because the function thought x was referring to the Book in this class, and not the original Book class. (So it ended up referencing two different booklist vectors. )
    Book bo;
    Patron pa;
    Date da;
    Transaction(Book bo, Patron pa, Date da);
    void checkout();
    bool checkout_user();
    bool checkout_ISBN();
    vector<Transaction> transactions;
    int userposition;
    int bookposition;
};

struct Transactionvec
{
    vector<Transactionvec> transactionlist;
    string title2;
    string author2;
    Genre genre2;
    string ISBN2;
    int cdate2;
    bool checkedout2;
    string username2;
    int cardnum2;
    double fees2;
    int day2;
    string month2;
    int year2;
    Transactionvec(string a, string b, Genre c, string d, int e, bool f, string g, int h, double i, int j, string k, int l)
        : title2{a}, author2{b}, genre2{c}, ISBN2{d}, cdate2{e}, checkedout2{f}, username2{g}, cardnum2{h}, fees2{i}, day2{j}, month2{k}, year2{l} {}
};

Book::Book(string a, string b, Genre f, string c, int d, bool e)
    : title{a}, author{b}, genre{f}, ISBN{c}, cdate{d}, checkedout{e} {}

Patron::Patron(string a, int b, double c) : username{a}, cardnum{b}, fees{c}
{
}

Transaction::Transaction(Book a, Patron b, Date c)
    : bo{a}, pa{b}, da{c} {}

Date::Date(int a, string b, int c)
    : day(a), month(b), year(c) {}

//These "dummy objects" allow us to run functions within the classes to which these objects belong. Not sure if there's a more sophisticated way to do this.
Book x{"title", "author", Genre::fiction, "000a", 1991, false};
//I couldn't reuse y due to a conflict with x being used as the dummy object for the Book class.
Patron y{"username", 0, 0.0};
//To get this default constructor (for a class whose constructor members are also clasess) to work, you need to use actual objects for the different clasess. These objects are defined with these letters nearby.

Date a{1, "Jan", 2020};

Transaction z{x, y, a};

Transactionvec b{"a", "b", Genre::nonfiction, "d", 1, true, "g", 2, 1.1, 3, "k", 2};

istream &operator>>(istream &is1, const Genre genre)
{
    //This vector is also necessary for this operator overloading to work; without it, I was getting a segmentation fault when trying to cout the genre
    vector<string> genre_tbl = {"fiction", "nonfiction", "periodical", "biography", "children"};

    return is1 >> genre_tbl[int(genre)];
}

void Book::book_entry()
{
    string ISBN1;
    string ISBN2;
    string ISBN3;
    string ISBN4;
    string checkedouttest;
    bool correct1 = 1;
    bool correct2 = 1;
    bool correct3 = 1;
    bool correct4 = 1;
    int genreentry;

    vector<string> genre_tbl = {"fiction", "nonfiction", "periodical", "biography", "children"};
    while (true)
    {
        cout << "Please enter the title of a book (using underscores instead of spaces). When you have finished entering books, enter Endentry0. \n";
        cin >> title;
        if (title == "Endentry0")
        {
            break;
        }
        cout << "Now please enter the author's last name.\n";
        cin >> author;
        while (true)
        {
            cout << "Now please add the book's genre. You may enter 0 for fiction; 1 for nonfiction; 2 for a periodical; 3 for a biography; and 4 for a children's book.\n";
            if (cin >> genreentry)
            {
                if (genreentry < 0 || genreentry > 4)
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "You must enter an integer between 1 and 4.\n";
                    continue;
                }
                else
                {
                    //The following cin.clear() and cin.ignore are added so that if a user enters a decimal, the decimal value will be cleared out and won't affect the ISBN analysis. This doesn't appear to clear out the integer value, fortunately. 
                    //It would be more ideal to use a method that would reject decimal input, of course.
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Sorry, that input was not recognized. Please try again.\n";
            }
        }
        Genre genre = Genre(genreentry);

        cout << "Now please enter the ISBN in n-n-n-x format, where n is an integer and x is either a letter or a digit. Separate each part of the ISBN with a space (e.g. 1234 5678 9012 a).\n";
        //Because the ns can be integers, we need to run a for loop for each of them to ensure that there are digits. We also need to make sure that only one integer/digit was entered for x. We'll accept negative integers because who knows--maybe those will sometimes appear in ISBNs? And because checking to see if the integer was negative would require converting the string to an integer, which may not be an easy process.
        while (cin >> ISBN1 >> ISBN2 >> ISBN3 >> ISBN4)
        {

            for (int j = 0; j < ISBN1.size(); j++)
                if (!(isdigit(ISBN1[j])))
                {
                    correct1 = 0;
                }

            for (int j = 0; j < ISBN2.size(); j++)
                if (!(isdigit(ISBN2[j])))
                {
                    correct2 = 0;
                }

            for (int j = 0; j < ISBN3.size(); j++)
                if (!(isdigit(ISBN3[j])))
                {
                    correct3 = 0;
                }

            if (ISBN4.size() != 1)
            {
                correct4 = 0;
            }

            for (int j = 0; j < ISBN4.size(); j++)
                if ((!(isdigit(ISBN4[j]))) && (!(isalpha(ISBN4[j]))))
                {
                    correct4 = 0;
                }

            if (correct1 == 0 || correct2 == 0 || correct3 == 0 || correct4 == 0)
            {
                cout << "Sorry, that ISBN was entered in an invalid format. Please try again.\n";
                //We need to reset the bools; otherwise they'll stay stuck at 0 and no entry will be considered correct.
                correct1 = 1;
                correct2 = 1;
                correct3 = 1;
                correct4 = 1;
            }
            else
            {
                ISBN = ISBN1 + ISBN2 + ISBN3 + ISBN4;
                break;
            }
        }
        cout << "Now please enter the copyright date.\n";
        while (cin)
        {
            if (cin >> cdate)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                break;
            }

            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Sorry, please enter a year using only integers.\n";
            }
        }
        while (true)
        {
            cout << "Finally, please state (using 1 for \"yes\" or 0 for \"no\" whether this book has been checked out or not.\n";
            cin >> checkedouttest;
            if (checkedouttest == "1")
            {
                checkedout = 1;
            }
            else if (checkedouttest == "0")
            {
                checkedout = 0;
            }

            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Sorry, that input was not recognized.\n";
                continue;
            }
            //Note that you have to put Book in parentheses before these other items. It's similar to the format of the constructor.
            //Interestingly, even though we don't specify that the following booklist is x.booklist, it seems that the program considers x.booklist and this booklist as the same, as using the list function after using this function will enter both the data from this function and the sample value entered through x.booklist within int(main).
            {
                booklist.push_back(Book{title, author, genre, ISBN, cdate, checkedout});

                break;
            }
        }
    }
}

//This operator overloading is necessary for list_books() to successfully cout a book's genre.
ostream &operator<<(ostream &os, const Genre genre)
{
    //This vector is also necessary for this operator overloading to work; without it, I was getting a segmentation fault when trying to cout the genre
    vector<string> genre_tbl = {"fiction", "nonfiction", "periodical", "biography", "children"};

    return os << genre_tbl[int(genre)];
}

void Book::list_books()
{
    cout << "Here are all the books you have entered so far:\n";
    for (int x = 0; x < booklist.size(); x++)
        cout << booklist[x].title << " " << booklist[x].author << " " << booklist[x].genre << " " << booklist[x].ISBN << " " << booklist[x].cdate << " " << booklist[x].checkedout << "\n";
}

void Book::data()
{
    string enteredISBN;

    bool trueflag = 0;
    while (true)
    {
        trueflag = 0;
        cout << "Please enter the ISBN of a book to retrieve information about it. When you are finished using this feature, enter quit.\n";

        cin >> enteredISBN;
        if (enteredISBN == "quit")
        {
            return;
        }
        else
        {
            for (int x = 0; x < booklist.size(); x++)
            {
                if (enteredISBN == booklist[x].ISBN)
                {
                    trueflag = 1;
                    cout << "Here is information in our system on that book: Title: " << booklist[x].title << " Author's last name: " << booklist[x].author << " Genre: " << booklist[x].genre << " ISBN: " << booklist[x].ISBN << " Copyright date: " << booklist[x].cdate << " Checked out? (1 for yes, 0 for no) " << booklist[x].checkedout << "\n";
                    cout << "You may now enter a new ISBN, or press quit if you wish to exit this feature.\n";
                }
            }
            if (trueflag == 1)
            {
                continue;
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "I'm sorry, that ISBN was not recognized. Please try again, or enter quit if you are finished using this feature. It is also possible that you will need to enter the book to which this ISBN is assigned into our system as a new book.\n";
            continue;
        }
    }
}

void Book::returnbook()
{
    bool running = 1;
    bool trueflag = 0;
    string enteredISBN;
    while (running == 1)
    { //trueflag = 0 is added here to reset it when needed.
        trueflag = 0;
        cout << "Please enter the ISBN of the book that has been returned. When you are finished using this feature, enter quit.\n";
        while (cin >> enteredISBN)
        {
            if (enteredISBN == "quit")
            {
                running = 0;
                break;
            }
            else
            {
                for (int x = 0; x < booklist.size(); x++)
                {
                    if (enteredISBN == booklist[x].ISBN)
                    {
                        booklist[x].checkedout = 0;
                        trueflag = 1;
                        cout << "The book whose ISBN number is " << booklist[x].ISBN << " has successfully been returned. \n";
                    }
                }
                //This statement skips the following text if we did indeed find a match for our entered ISBN. If we did not find a match, we proceed to the next statement.
                if (trueflag == 1)
                {
                    break;
                }

                {
                    if (trueflag == 0)
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "I'm sorry, that ISBN was not recognized. It is also possible that you will need to enter the book to which this ISBN is assigned into our system as a new book.\n";
                        break;
                    }
                }
            }
        }
    }
}

//Functions for Patron class
//You need to enter Patron here in order for the program to recognize that you're referring to a function within the Patron class. This is also necessary for the program to realize that username (and likely the other items as well) is a member of Patron.
void Patron::addpatron()
{
    while (true)
    {
        cout << "Please enter the patron's username, or \"quit\" to exit this feature.\n";
        cin >> username;
        if (username == "quit")
        {
            break;
        }
        else
            //Using a while (true) loop here allows us to return to the first cout statement within this loop if the user does not enter a valid input.
            while (true)
            {
                //If the user enters an integer followed by nonsense text, it will store the integer and move on, which probably isn't a good thing. I'm not sure yet how to resolve this--I'll leave it as is for now as a "good enough" solution.
                cout << "\nNow please enter the patron's library card number.\n";
                if (cin >> cardnum)
                {
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "You must enter an integer value.\n";
                }
            }

        while (true)
        {
            cout << "\nFinally, please enter the numerical value of the user's late fees, if any. You may enter decimals, but don't use a dollar sign. (e.g. $23.71 in late fees should be entered as 23.71)\n";
            if (cin >> fees)
            {
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "That input was invalid.\n";
            }
        }
        //We normally wouldn't need the "y" in y.patronlist, but because we have a helper function that doesn't directly access the Patron class, we need to add a y so that the helper function can access patronlist. Not sure whether this actually has to be added to all the instances of patronlist, but it seems like a good idea since otherwise we may end up with two different patronlists.
        y.patronlist.push_back(Patron{username, cardnum, fees});
        cout << "That patron was successfully added to the system.\n";
    }
}

void Patron::listpatrons()
{
    cout << "Here are all the patrons you have entered so far:\n";
    for (int x = 0; x < y.patronlist.size(); x++)
        cout << y.patronlist[x].username << " " << y.patronlist[x].cardnum << " " << y.patronlist[x].fees << "\n";
}

void Patron::patronfee()
{
    bool running = 1;
    double newfee = 0.0;
    while (running == 1)
    {
        cout << "Please enter the username of the patron whose fee you would like to set. When you are finished using this feature, enter quit.\n";
        cin >> username;
        {
            for (int x = 0; x < y.patronlist.size(); x++)
            {
                if (username == y.patronlist[x].username)
                {
                    while (true)
                    {
                        cout << "What fee would you like to set for this user?\n";
                        if (cin >> newfee)
                        {
                            y.patronlist[x].fees = newfee;
                            cout << "Fee updated successfully.\n";
                            break;
                        }
                        else
                        {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Invalid input. Please try again.\n";
                        }
                    }
                }
                else if (username == "quit")
                {
                    running = 0;
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "I'm sorry, that username was not recognized. It is also possible that this patron has not yet been entered into the system.\n";
                    break;
                }
            }
            //Because the statement closed out by the following bracket is not a while statement, we don't need an extra "break" statement here as we did with the checkout() function. Adding that break actually closes out the whole while loop, even though "running" is still set to 1.
        }
    }
}

void Patron::patrondata()
{
    bool running = 1;
    while (running == 1)
    {
        cout << "Please enter the username of the patron whose data you would like to view. When you are finished using this feature, enter quit.\n";
        cin >> username;
        {
            for (int x = 0; x < y.patronlist.size(); x++)
            {
                if (username == y.patronlist[x].username)
                {
                    cout << "username: " << y.patronlist[x].username << " library card number: " << y.patronlist[x].cardnum << " fees owed (if any): " << y.patronlist[x].fees << "\n";
                }

                else if (username == "quit")
                {
                    running = 0;
                    break;
                }
                else
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "I'm sorry, that username was not recognized. It is also possible that this patron has not yet been entered into the system.\n";
                    break;
                }
            }
        }
    }
}

void Patron::whoowesfees()
{
    cout << "Here are the usernames of all the patrons who owe fees. If no patrons appear, that means that no one owes any fees.\n";
    for (int x = 0; x < patronlist.size(); x++)
        if (patronlist[x].fees > 0)
            cout << patronlist[x].username << " ";
}

//"Helper function"--not declared within the Patron class itself, but references components of that class

bool arefeesowed()

{
    //This string has to be placed before the while loop for it to be recognized by the code within the loop.
    string username1;

    cout << "Please enter the username of the patron whose fee status you would like to check.\n";
    cin >> username1;
    {
        for (int x = 0; x < y.patronlist.size(); x++)
        {
            if (username1 == y.patronlist[x].username)
            {
                if (y.patronlist[x].fees > 0)
                {
                    cout << "Yes, this patron owes fees.\n";
                    return 1;
                }
                else
                {
                    cout << "No, this patron does not owe fees.\n";
                    return 0;
                }
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "I'm sorry, that username was not recognized. It is also possible that this patron has not yet been entered into the system.\n";
                break;
            }
        }
    }
}

//Date-class function
void Date::verifydate()
{
    string yesno;
    while (true)
    {
        cout << "Now please enter today's date in the following format: YYYY MMM DD (where MM may equal Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, or Dec).\n";
        cin >> year >> month >> day;
        if (day < 1 || day > 31)
        {
            cout << "Error: day cannot be less than 1 or greater than 31. Please try again.\n";
            continue;
        }
        else if (month != "Jan" && month != "Feb" && month != "Mar" && month != "Apr" && month != "May" && month != "Jun" && month != "Jul" && month != "Aug" && month != "Sep" && month != "Oct" && month != "Nov" && month != "Dec")
        {
            cout << "Error: month was not entered correctly. Please try again.\n";
            continue;
        }

        a.dates.push_back(Date{year, month, day});

        return;
    }
}

//Transaction-class functions
//Originally I was going to have the features of checkout_user and checkout_ISBN together in one big function, but I then realized that it would get way too unwieldy. Instead, I separated those parts into smaller functions that I can debug more easily, and then fed those into the main checkout() function. This will probably be good practice going forward.
bool Transaction::checkout_user()
{
    string enteredusername;
    while (true)
    {
        cout << "Please enter the username of the patron who will be checking out a book.\n";
        cin >> enteredusername;
        {
            for (int x = 0; x < y.patronlist.size(); x++)
            {
                if (enteredusername == y.patronlist[x].username)
                {
                    if (y.patronlist[x].fees > 0)
                    {
                        cout << "This patron owes $" << y.patronlist[x].fees << " in fees, and therefore may not check out this book until the fees are paid.\n";
                        //These returns immediately exit the loop; however, if this function weren't boolean, you could also exit out when needed by creating a bool called running, turning while(true) into while (running == 1), and then setting while to 0 in place of entering a return statement.
                        return 1;
                    }
                    else
                    {
                        cout << "This patron does not owe any fees, and therefore may check out this book.\n";
                        userposition = x;
                        return 0;
                    }
                }
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "I'm sorry, that username was not recognized. It is also possible that this patron has not yet been entered into the system.\n";
            break;
        }
    }
}

bool Transaction::checkout_ISBN()
{
    string enteredISBN;
    while (true)
    {
        cout << "Next, please enter the ISBN of the book that you are checking out. Do not enter any spaces.\n";
        cin >> enteredISBN;
        {

            for (int y = 0; y < x.booklist.size(); y++)
            {
                if (enteredISBN == x.booklist[y].ISBN)
                {
                    if (x.booklist[y].checkedout == 1)
                    {
                        cout << "According to our system, that book has already been checked out. Therefore, this transaction cannot be completed.\n";
                        return 1;
                    }
                    else
                    {

                        bookposition = y;
                        //Even for void functions, you can use return to exit the function
                        return 0;
                    }
                }
            }

            cin.clear();
            cin.ignore(10000, '\n');
            cout << "I'm sorry, that ISBN was not recognized. It is also possible that you will need to enter the book to which this ISBN is assigned into our system as a new book.\n";
            continue;
        }
    }
}

void Transaction::checkout()
{
    bool running = 1;
    //Originally I had entry set as an int, but I found that the program would cycle back and forth between the first cout for this function and the first cout for the main function if I entered a string.
    string entry;
    string entry2;
    while (running == 1)
    {
        cout << "Welcome to the checkout feature. To create a new checkout transaction, press 1. Otherwise, press 0 to quit.\n";
        while (true)
        {
            cin >> entry;
            if (entry == "0")
            {
                running = 0;
                break;
            }
            else if (entry != "1")
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Sorry, that input was not recognized. Please try again.\n";
                break;
            }
            else
            {
                //My understanding is that the reason we don't need to preface checkout_user with an object is that checkout() and checkout_user() are both members of the Transaction class.)
                //Originally I had checkout_user written three times (the first time to run the program, and then two other times within if statements that were based on the bool this function returned). But that led the function to run three times! :)
                //I made the checkout_user return a bool so that if it returned one condition (based on a user having library fees), the function would exit, and if it returned another (the user didn't have fees), the function would continue.
                //Note that the following line is interpreted as follows: (1) run this function, and (2) act based on the bool value it returns. It will indeed run the function before making a decision based on it.
                if (checkout_user() == 1)
                {

                    //running = 0 will get us out of the main function loop; break gets us out of the current while loop.
                    running = 0;
                    break;
                }

                if (checkout_ISBN() == 1)
                {
                    running = 0;
                    break;
                }
                a.Date::verifydate();

                b.title2 = x.booklist[bookposition].title;
                b.author2 = x.booklist[bookposition].author;
                b.genre2 = x.booklist[bookposition].genre;
                b.ISBN2 = x.booklist[bookposition].ISBN;
                b.cdate2 = x.booklist[bookposition].cdate;
                b.checkedout2 = x.booklist[bookposition].checkedout;
                b.username2 = y.patronlist[userposition].username;
                b.cardnum2 = y.patronlist[userposition].cardnum;
                b.fees2 = y.patronlist[userposition].fees;
                b.day2 = a.dates[a.dates.size() - 1].day;
                b.month2 = a.dates[a.dates.size() - 1].month;
                b.year2 = a.dates[a.dates.size() - 1].year;

                b.transactionlist.push_back(Transactionvec{b.title2, b.author2, b.genre2, b.ISBN2, b.cdate2, b.checkedout2, b.username2, b.cardnum2, b.fees2, b.day2, b.month2, b.year2});

                cout << "\nHere are the details of the transaction you just entered: (Data represents title, author, genre, ISBN, copyright date, checked out (1 for yes, 0 for no), username, library card number, fees, transaction year, transaction month, and tarnsaction day, respectively:) \n";

                cout << b.transactionlist[b.transactionlist.size() - 1].title2 << " " << b.transactionlist[b.transactionlist.size() - 1].author2 << " " << b.transactionlist[b.transactionlist.size() - 1].genre2 << " " << b.transactionlist[b.transactionlist.size() - 1].ISBN2 << " " << b.transactionlist[b.transactionlist.size() - 1].cdate2 << " " << b.transactionlist[b.transactionlist.size() - 1].checkedout2 << " " << b.transactionlist[b.transactionlist.size() - 1].username2 << " " << b.transactionlist[b.transactionlist.size() - 1].cardnum2 << " " << b.transactionlist[b.transactionlist.size() - 1].fees2 << " " << b.transactionlist[b.transactionlist.size() - 1].day2 << " " << b.transactionlist[b.transactionlist.size() - 1].month2 << " " << b.transactionlist[b.transactionlist.size() - 1].year2 << "\n";

                cout << "Would you like to undo this transaction? Press 1 if yes and 0 if no.\n";
                cin >> entry2;
                if (entry2 == "1")
                {
                    b.transactionlist.pop_back();
                    cout << "Transaction has successfully been undone.\n";
                    break;
                }
                else if (entry2 != "0")
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Sorry, that input was not recognized. Please try again.\n";
                    break;
                }
                else

                    x.booklist[bookposition].checkedout = 1;
                cout << "The book whose ISBN number is " << x.booklist[bookposition].ISBN << " has successfully been checked out.\n";

                cout << "Transaction saved. Here are all the transactions you have entered so far:\n";
                for (int x = 0; x < b.transactionlist.size(); x++)
                {
                    cout << b.transactionlist[x].title2 << " " << b.transactionlist[x].author2 << " " << b.transactionlist[x].genre2 << " " << b.transactionlist[x].ISBN2 << " " << b.transactionlist[x].cdate2 << " " << b.transactionlist[x].checkedout2 << " " << b.transactionlist[x].username2 << " " << b.transactionlist[x].cardnum2 << " " << b.transactionlist[x].fees2 << " " << b.transactionlist[x].day2 << " " << b.transactionlist[x].month2 << " " << b.transactionlist[x].year2 << "\n";
                }
            }
            break;
        }
    }
}
int main()
{
    string entry;
    bool running = 1;
    //These following push_backs aren't necessary; they're just there to add in test data for debugging. However, even without these, it would probably be necessary to declare a y.patronlist somewhere in the code so that it could be used by the "arefeesowed" function.
    x.booklist.push_back(Book{"Whatislove", "Haddaway", Genre::nonfiction, "123A", 1992, 0});
    x.booklist.push_back(Book{"Never_Gonna_Give_You_Up", "Astley", Genre::nonfiction, "456B", 1987, 1});
    y.patronlist.push_back(Patron{"bjarne", 1, 0.0});
    y.patronlist.push_back(Patron{"keith", 2, 5.45});
    while (running == 1)
    {
        cout << "Welcome to Ken's library data system (KLDS). What would you like to do? Book functions: enter entry to enter a book; list to list the books in the system; data to check information for a book; checkout to check out a book; return to return a book; and quit to quit the program.\n";
        cout << "Patron functions: enter addpatron to enter a new patron into the system; listpatrons to list all patrons; patrondata to look up information on a given patron; patronfee to set a patron's fee; feesowed to see whether a patron owes any fees; and whoowesfees to view a list of the usernames of all patrons who owe fees.\n";
        cin >> entry;
        {
            if (entry == "entry")
            {
                x.Book::book_entry();
            }
            else if (entry == "list")
            {
                x.Book::list_books();
            }
            else if (entry == "data")
            {
                x.Book::data();
            }
            else if (entry == "checkout")
            {
                z.Transaction::checkout();
            }
            else if (entry == "return")
            {
                x.Book::returnbook();
            }
            else if (entry == "addpatron")
            {
                y.Patron::addpatron();
            }
            else if (entry == "listpatrons")
            {
                y.Patron::listpatrons();
            }

            else if (entry == "patronfee")
            {
                y.Patron::patronfee();
            }

            else if (entry == "patrondata")
            {
                y.Patron::patrondata();
            }

            else if (entry == "feesowed")
            {
                arefeesowed();
            }

            else if (entry == "checkout_user")
            {
                z.Transaction::checkout_user();
            }

            else if (entry == "verifydate")
            {
                a.Date::verifydate();
            }

            else if (entry == "checkout_ISBN")
            {
                z.Transaction::checkout_ISBN();
            }

            else if (entry == "verifydate")
            {
                a.Date::verifydate();
            }

            else if (entry == "whoowesfees")
            {
                y.Patron::whoowesfees();
            }

            else if (entry == "quit")
            {
                running = 0;
            }
            else
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "I'm sorry, I didn't recognize that input. Please try again.\n";
            }
        }
    }
}
