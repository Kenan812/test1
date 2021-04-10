#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <IO.h>
#include <direct.h>
#include <time.h>
#include <fstream>
#include <Windows.h>
#include <conio.h> 

using namespace std;
void RenameFile();
void RemoveFile(string path);
void RemoveDir();
void CreateDir();
void Dir();

class User
{
private:
    string name;
    string surname;
    int age;
public:
    User();
    User(string _name, string _surname, int _age);
    void Put();
    void SaveToFile();
    void Display();
    static void ShowFromFile();

};


User::User()
{
    name = "";
    surname = "";
    age = 0;
}
User::User(string _name, string _surname, int _age)
{
    name = _name;
    surname = _surname;
    age = _age;
}

void User::Put()
{
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter surname: ";
    cin >> surname;
    cout << "Enter age: ";
    cin >> age;
}

void User::SaveToFile()
{
    int size;
    string path = "F/use rs.txt";
    fstream file(path, ios::out | ios::binary | ios::app);
    if (!file)
    {
        cout << "File not open for write\n";
        exit(1);
    }
    file.write((char*)&age, sizeof(age));
    size = name.length();
    file.write((char*)&size, sizeof(size));
    file.write(name.c_str(), size * sizeof(char));
    size = surname.length();
    file.write((char*)&size, sizeof(size));
    file.write(surname.c_str(), size * sizeof(char));  // c_str transforms string to const char*
    file.close();
}

void User::ShowFromFile()
{
    string path = "F/use rs.txt";
    fstream file(path, ios::in | ios::binary);
    if (!file)
    {
        cout << "File not open for write\n";
        exit(1);
    }
    char* n, * s;
    int temp;
    int a;
    while (file.read((char*)&a, sizeof(a)))
    {
        cout << "Name: ";
        file.read((char*)&temp, sizeof(int));
        n = new char[temp + 1];
        if (!n)
        {
            cout << "Memory allocation error\n";
            exit(1);
        }
        file.read(n, temp * sizeof(char));
        n[temp] = '\0';
        cout << n << "\n";

        cout << "Surname: ";
        file.read((char*)&temp, sizeof(int));
        s = new char[temp + 1];
        if (!s)
        {
            cout << "Memory allocation error\n";
            exit(1);
        }
        file.read(s, temp * sizeof(char));
        s[temp] = '\0';
        cout << s << "\n";

        cout << "Age: " << a << "\n";
        delete[] n;
        delete[] s;

    }
}

void User::Display()
{
    cout << "Name" << name << "\n";
    cout << "Surname" << surname << "\n";
    cout << "Age" << age << "\n";


}




int main()
{
    /*
    for (int i = 0; i < 500; i++)
        printf("%d : %c\n", i, i);
    */

    /*
    char key;
    int asciiValue;
    cout << "Press\n";
    while (1)
    {
        key = _getch();
        asciiValue = key;

        if (asciiValue == 27) break;

        cout << "Key pressed -> \" " << key << "\" ascii value = " << asciiValue << endl;

    }
    */

 
    char ch = '0';
    while (ch != '6')
    {
        system("cls");
        cout << "(1) Rename file\n";
        cout << "(2) Remove file\n";
        cout << "(3) Remove Dir\n";
        cout << "(4) Create dir\n";
        cout << "(5) Dir\n";
        cout << "(6) Exit\n";
        cin >> ch;
        switch (ch)
        {
        case '1':
            RenameFile();
            break;
        case '2':
            char path[50];
            cout << "Enter path: ";
            cin >> path;
            RemoveFile(path);
            break;

        case '3':
            RemoveDir();
            break;

        case '4':
            CreateDir();
            break;

        case '5':
            Dir();
            break;
        default:
            break;
        }
        system("pause");
    }
 


    /*
    int ch;
    User* u;
    do
    {
        cout << "1 - Add struct\n";
        cout << "2 - Show struct\n";
        cout << "3 - Exit\n";
        cout << "Enter option: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            system("cls");
            u = new User();
            u->Put();
            u->SaveToFile();
            delete u;
            break;
        case 2:
            system("cls");
            User::ShowFromFile();
            break;
        case 3:
            cout << "Bye\n";
            exit(1);
            break;
        default:
            cout << "Not correct input\n";
            break;
        }

    } while (true);

    */

    return 0;
}

void RemoveDir()
{
    string name;

    cout << "Enter dir name: ";
    cin >> name;
    
    if (_rmdir(name.c_str()) == -1)
        cout << "Error...\n";
    else cout << "Completed...\n";
}

void CreateDir()
{
    string name = "QWERTY\\";
    string i;
    cout << "Enter dir name: ";
    cin >> i;

    name += i;

    if (_mkdir(name.c_str()) == -1)
        cout << "Error...\n";
    else cout << "Completed...\n";

}

void RenameFile()
{
    char oldName[50];
    char newName[50];
    cout << "Old name:";
    cin >> oldName;
    cout << "New name:";
    cin >> newName;
    if (rename(oldName, newName) != 0)
    {
        cout << "Error..." << endl;
    }
    else {
        cout << "Complete..." << endl;
    }
}

void RemoveFile(string path)
{
   // string name = "F\\";
   //
   // string name_tmp;
   // cout << "Enter file name:";
   // cin >> name_tmp;
   // name += name_tmp;

    string full = "";
    
    full += path;
   

    cout << full << "\n";

    if (remove(full.c_str()) != 0)
    {
        cout << "Error..." << endl;
    }
    else
    {
        cout << "Complete..." << endl;
    }
}


void Dir()
{
    string path;
    string mask;
    cout << "Enter path:";
    cin >> path;
    cout << "Enter mask:";
    cin >> mask;

    
    path += mask;
    
    _finddata_t* fileinfo = new _finddata_t;
    long done = _findfirst(path.c_str(), fileinfo);
    int isReadable = done;
    int count = 0;

    while (isReadable != -1)
    {
        count++;
        char time[100];
        ctime_s(time, 100, &fileinfo->time_create);

        if (fileinfo->name != "." && fileinfo->name != "..")
            cout << count << " - " << fileinfo->name << "  " << time << endl;

        //cout << fileinfo->name << "\n";
        //RemoveFile(fileinfo->name);
        

        isReadable = _findnext(done, fileinfo);
    }
    
    cout << count << " files found" << endl;
    _findclose(done);
    delete fileinfo;
}
