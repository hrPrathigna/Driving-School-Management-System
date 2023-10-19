#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct customer
{
    string name;
    long long int id;
    string num;
};
customer x[100];

struct car
{
	string name, color, type, model;
};
car c[50];

int noofItems = -1;

void readfile()
{
	fstream readfile;
	string x;
	readfile.open("cars.txt", ios::in);
	int i = 0;
	while (!readfile.eof())
	{
		i++;
		getline(readfile, x);
		cout << x << endl;
	}
	readfile.close();
}

void Addcar()
{
	ofstream writetofile;
	writetofile.open("cars.txt", ios::app);

	car c1;

	cout << "\t\t\tPlease enter the name of new car " ;
	cin >> c1.name;
	cout << "\t\t\tPlease enter the model of new car " ;
	cin >> c1.model;
	cout << "\t\t\tplease enter the color of new car " ;
	cin >> c1.color;
	cout << "\t\t\tplease enter the type of new car " ;
	cin >> c1.type;
	writetofile << endl<< c1.name << "\t\t\t" << c1.model << "\t\t\t" << c1.color << "\t\t\t" << c1.type << endl;
	writetofile.close();
	cout << "\t\t\tcar has been added succesfully ";
}


bool checkId(customer arr[], int noofitems, int id)
{
    for (int i = 0; i < noofitems; i++)
    {
        if (id == arr[i].id)
            return 1;
    }
    return 0;
}

void savefile(customer arr[], int noofitems)
{
    fstream file("users.txt", ios::in | ios::out);
    for (int i = 0; i < noofitems; i++)
    {
        file << arr[i].name << "\t\t" << arr[i].id << "\t\t" << arr[i].num << "\n";
    }
}
void DataToArr(customer arr[])
{
    fstream file("users.txt", ios::in | ios::out | ios::app);
    customer  temp;
    int i = 0;
    file >> temp.name;
    while (!file.eof())
    {
        file >> temp.id >> temp.num;
        arr[i] = temp;
        file >> temp.name;
        i++;
    }
}

void noOfItems(int& x)
{
    fstream file("users.txt", ios::in | ios::out | ios::app);
    string str;
    while (!file.eof())
    {
        getline(file, str);
        x++;
    }
}

void printData(string arr[][5], int sizeR) {         // prints 2D array
    cout << "\t\t\t---------------------------\n";
    for (int i = 0; i < sizeR; i++) {
        cout <<"\t\t\t";
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\t\t\t---------------------------\n";

}

void writeData(string arr[][5], int sizeR) {         // save 2D array into txt file 
    ofstream file("Book2.txt");
    for (int i = 0; i < sizeR; i++) {
        for (int j = 0; j < 5; j++) {
            file << arr[i][j] << ",";
        }
    }
}

void addSession(string arr[][5], int sizeR) {
    string day, type, time; int counter = 0;
    cout << "\t\t\t---------------------------\n";
    cout << "\t\t\tAdd Session:\n";
    cout << "\t\t\t---------------------------\n";
    cout << "\n\t\t\tEnter your preferences \n\t\t\tDay (sat, sun, mon ...): "; // reading preferences from the user
    cin >> day;
    cout << "\t\t\tTime (6, 7, 8, 9): ";
    cin >> time;
    cout << "\t\t\tType (A, M): ";
    cin >> type;
    for (int i = 0; i < sizeR; i++) {         // loop for rows
        bool book = false;                    // boolean condition to break the loop when booked
        for (int j = 0; j < 5; j++) {         // loop for columns      
            if (arr[i][j] == day) {
                if (arr[i][j + 1] == time) {
                    if (arr[i][j + 2] == type) {
                        if (arr[i][j + 4] == "none") {
                            cout << "\n\t\t\tchoosen time is available with " << arr[i][j + 3] << "\n";
                            cout << "\t\t\tDo you want to book this session? if yes type 'yes': ";
                            string opt;
                            cin >> opt;
                            if (opt == "yes") {
                                cout << "\n\t\t\tEnter Your ID: ";
                                string id;
                                cin >> id;
                                arr[i][j + 4] = id;
                                cout << "\t\t\tSession has been booked successfully :) \n";
                                book = true;    // will end the loop
                            }
                        }
                        else {
                            counter++;
                        }
                        if (counter == 2) {
                            cout << "\t\t\tchoosen time is fully booked \n";
                            cout << "\t\t\t---------------------------\n";
                        }
                    }
                }
            }
        }
        if (book)
            break;
    }

}

void bookFree(string arr[][5], int sizeR, string day, string type, string time, string cap, string id) {
    for (int i = 0; i < sizeR; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == day) {
                if (arr[i][j + 1] == time) {
                    if (arr[i][j + 2] == type) {
                        if (arr[i][j + 3] == cap) {
                            arr[i][j + 4] = id;
                            cout << "\t\t\tSession has been booked successfully :) \n";
                            cout << "\t\t\t---------------------------\n";
                        }
                    }
                }
            }
        }
    }

}

void filterDayType(string arr[][5], int sizeR) {
    string day, type, opt; int free = 0;
    cout << "\t\t\t---------------------------\n";
    cout << "\t\t\tFilter by Day & Type:\n";
    cout << "\t\t\t---------------------------\n";
    cout << "\n\t\t\tEnter your preferences \n\t\t\tDay (sat, sun, mon ...): ";
    cin >> day;
    cout << "\t\t\tType (A, M); ";
    cin >> type;
    for (int i = 0; i < sizeR; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == day) {
                if (arr[i][j + 2] == type) {
                    if (arr[i][j + 4] == "none") {
                        cout << "\t\t\tSession at " << arr[i][j + 1] << " with " << arr[i][j + 3] << " is available. \n";
                        free++;
                    }
                }
            }
        }
    }
    if (free >= 1) {
        cout << "\t\t\tDo you want to book? if yes type 'yes': ";
        cin >> opt;
        if (opt == "yes") {
            string time, cap, id;
            cout << "\t\t\tEnter time: ";
            cin >> time;
            cout << "\t\t\tEnter captain: ";
            cin >> cap;
            cout << "\t\t\tEnter your ID: ";
            cin >> id;
            bookFree(arr, 112, day, type, time, cap, id);
        }
    }
    else {
        cout << "\t\t\tThe choosen preferences are fully booked :( \n";
        cout << "\t\t\t---------------------------\n";
    }
}

void filterTimeType(string arr[][5], int sizeR) {
    string time, type, opt; int free = 0;
    cout << "\t\t\t---------------------------\n";
    cout << "\t\t\tFilter by Time & Type:\n";
    cout << "\t\t\t---------------------------\n";
    cout << "\n\t\t\tEnter your preferences \n\t\t\tTime (6, 7, 8, 9): ";
    cin >> time;
    cout << "\t\t\tType (A, M); ";
    cin >> type;
    for (int i = 0; i < sizeR; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[i][j] == time) {
                if (arr[i][j + 1] == type) {
                    if (arr[i][j + 3] == "none") {
                        cout << "\t\t\tSession on " << arr[i][j - 1] << " with " << arr[i][j + 2] << " is available. \n";
                        free++;
                    }
                }
            }
        }
    }
    if (free >= 1) {
        cout << "\t\t\tDo you want to book? if yes type 'yes': ";
        cin >> opt;
        if (opt == "yes") {
            string day, cap, id;
            cout << "\t\t\tEnter day (sat, sun, mon ...): ";
            cin >> day;
            cout << "\t\t\tEnter captain: ";
            cin >> cap;
            cout << "\t\t\tEnter your ID: ";
            cin >> id;
            bookFree(arr, 112, day, type, time, cap, id);
        }
    }
    else {
        cout << "\t\t\tThe choosen preferences are fully booked :( \n";
        cout << "\t\t\t---------------------------\n";
    }
}
void clearData(string arr[][5], int sizeR) {
    for (int i = 0; i < sizeR; i++)
        arr[i][4] = "none";
    cout << "\t\t\t---------------------------\n";
    cout << "\t\t\tData has been cleared successfully (all sessions are free) \n";

}

void deleteSession(string arr[][5], int sizeR) {
    string id;
    bool del = false;
    cout << "\n\t\t\tEnter ID of the session you want to delete: ";
    cin >> id;
    for (int i = 0; i < sizeR; i++) {
        if (arr[i][4] == id) {
            arr[i][4] = "none";
            cout << "\t\t\tSession has been deleted successfully\n";
            cout << "\t\t\t---------------------------\n";
            del = true;
            break;
        }
    }
    if (!del) {
        cout << "\t\t\tSession was not found !! Check your ID and try again \n";
    }

}

int main() {
    fstream file("users.txt", ios::in | ios::out | ios::app);
    noOfItems(noofItems);
    DataToArr(x);
    ifstream myFile;          // Reading Data 
    myFile.open("Book2.txt");
    string data[112][5];
    for (int i = 0; i < 112; i++) {
        for (int j = 0; j < 5; j++) {
            string line;
            getline(myFile, line, ',');
            data[i][j] = line;
        }
    }
    while (1) {
        system("CLS");
        char choice;
        cout << "\t\t\t---------------------------\n";
        cout << "\t\t\tThis is The Main Menu \n\t\t\t---------------------------\n\n\t\t\tPlease choose an option:- \n\t\t\t1. Customer Entry \n\t\t\t2. Sessions Managment \n\t\t\t3. Print full data base \n\t\t\t4. Clear data\n\t\t\t5. Car Managment\n\t\t\t\n";
        choice = _getch();
        if (choice == '1') {
            system("CLS");
            char choice1, next = 'y';
            bool back = 1;
            while (back == 1){            
                system("cls");
                cout << "\t\t\t---------------------------\n";
                cout << "\t\t\t      Customer Entery\n";
                cout << "\t\t\t---------------------------\n";
                cout << "\n \t\t\t 1. Add    Member";
                cout << "\n \t\t\t 2. List   Records";
                cout << "\n \t\t\t 3. Modify Records";
                cout << "\n \t\t\t 4. Delete Member";
                cout << "\n \t\t\t 5. Back to Main Menu";
                cout << "\n\n";
                choice1 = _getch();
                switch (choice1)
                {
                case '1':
                    while (next == 'Y' || next == 'y')
                    {
                        customer c;
                        system("cls");
                        cout << "Enter Member Name : ";
                        cin >> c.name;
                        cout << "Enter Member ID : ";
                        cin >> c.id;
                        while (checkId(x, noofItems, c.id))
                        {
                            cout << " This id is taken, enter another one\n  ";
                            cin >> c.id;
                        }
                        cout << "Enter Member phone number   : ";
                        cin >> c.num;
                        file << c.name << "\t\t" << c.id << "\t\t" << c.num << "\n";
                        noofItems++;
                        file.close();
                        DataToArr(x);
                        file.open("users.txt", ios::in | ios::out | ios::app);
                        cout << "Add another Member (y/n)\n";
                        next = _getch();
                    }
                    next = 'y';
                    break;
                case '2':
                {	system("cls");
                cout << "=== View the Records in the Database ===\n";
                DataToArr(x);
                for (int i = 0; i < noofItems; i++)
                {
                    cout << x[i].name << setw(15) << x[i].id << setw(15) << x[i].num << "\n";
                }
                cout << "Press any key to return\n";
                next = _getch();
                break;
                }
                case '3':
                {
                    int id;
                    bool flage = false;
                    customer c;
                    system("cls");
                    while (1)
                    {
                        cout << "enter Member ID\n";
                        cin >> id;
                        for (int i = 0; i < noofItems; i++)
                        {
                            if (id == x[i].id)
                            {
                                cout << "enter Member new name\n ";
                                cin >> c.name;
                                cout << "enter Member new ID\n ";
                                cin >> c.id;
                                while (checkId(x, noofItems, c.id))
                                {
                                    cout << " This id is taken, enter another one\n  ";
                                    cin >> c.id;
                                }
                                cout << "enter Member new phone number\n ";
                                cin >> c.num;
                                x[i] = c;
                                savefile(x, noofItems);
                                cout << "\n Done \n press any key to return\n";
                                next = _getch();
                                flage = true;
                                break;
                            }
                        }
                        if (flage == false)
                        {
                            cout << "member ID not found \n press any key to return\n";
                            next = _getch();
                        }
                        break;
                    }
                    break;
                }
                case '4':
                {	file.close();
                file.open("users.txt", ios::in | ios::out | ios::trunc);
                int id;
                system("cls");
                cout << "Enter ID of the Member you want to delete\n";
                cin >> id;
                for (int i = 0; i < noofItems; i++)
                {
                    if (id != x[i].id)
                    {
                        file << x[i].name << "\t\t" << x[i].id << "\t\t" << x[i].num << "\n";
                    }
                }
                cout << " Member with id " << id << " is deleted\n";
                noofItems--;
                file.close();
                DataToArr(x);
                savefile(x, noofItems);
                file.open("users.txt", ios::in | ios::out | ios::app);
                cout << "Press any key to return\n";
                next = _getch();
                break;
                }
                case '5':
                {
                    back = 0;
                    break;
                }
                }
            }
            file.close();
        }
        if (choice == '2') {
            system("CLS");
            int choice2;
            cout << "\t\t\t---------------------------\n";
            cout << "\t\t\tSessions Managment Section:\n";
            cout << "\t\t\t---------------------------\n";
            cout << "\n\t\t\t1. Add Session \n\t\t\t2. Filter by Day & Type \n\t\t\t3. Filter by Time & Type \n\t\t\t4. Cancel a session \n\t\t\t5. Return to Main Menu \n";
            choice2 = _getch();
            if (choice2 == '1') {
                system("cls");
                addSession(data, 112);
                writeData(data, 112);
                char m;
                cout << "\n\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();
            }
            if (choice2 == '2') {
                system("cls");
                filterDayType(data, 112);
                writeData(data, 112);
                char m;
                cout << "\n\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();
            }
            if (choice2 == '3') {
                system("cls");
                filterTimeType(data, 112);
                writeData(data, 112);
                char m;
                cout << "\n\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();
            }
            if (choice2 == '4') {
                system("cls");
                deleteSession(data, 112);
                writeData(data, 112);
                char m;
                cout << "\n\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();
            }
        }
        if (choice == '3') {
            system("cls");
            printData(data, 112);
            char m;
            cout << "\n\t\t\t---------------------------\n";
            cout << "\t\t\tPress any key to return to main menu.. ";
            m = _getch();
        }
        if (choice == '4') {
            system("cls");
            string opt;
            cout << "\n\t\t\tAll sessions will be canceled, to continue type 'yes': ";
            cin >> opt;
            if (opt == "yes") {
                clearData(data, 112);
                char m;
                cout << "\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();
            }
            else {
                cout << "\n\t\t\tTask canceled \n";
                char m;
                cout << "\t\t\t---------------------------\n";
                cout << "\t\t\tPress any key to return to main menu.. ";
                m = _getch();

            }
        }
        if (choice== '5'){
                while (1){
                    char choice5;
                    system("CLS");
                    cout << "\t\t\t---------------------------\n";
                    cout << "\t\t\t Car Management";
                    cout << "\n\t\t\t---------------------------\n";
                    cout <<" \n\t\t\t1.Add Car\n\t\t\t2.History of cars\n\t\t\t3.Return to main menu " << endl;
                    choice5 = _getch();
                    if (choice5 == '1')
                    {
                        system("cls");
                        Addcar();
                        system("pause");
                    }
                    if (choice5 == '2')
                    {
                        system("CLS");
                        readfile();
                        system("pause");
                    }
                    if (choice5 == '3'){
                        break ;
                    }
                }
        }
     
        }
    }

