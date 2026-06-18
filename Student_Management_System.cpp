#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

struct Student
{
    int rollNo;
    char name[50];
    int age;
    char course[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n      STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "\nThank You!\n";
                break;
            default:
                cout << "\nInvalid Choice!";
        }

    } while(choice != 6);

    return 0;
}

void addStudent()
{
    Student s;

    ofstream file("students.dat", ios::binary | ios::app);

    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;

    cin.ignore();

    cout << "Enter Name: ";
    cin.getline(s.name,50);

    cout << "Enter Age: ";
    cin >> s.age;

    cin.ignore();

    cout << "Enter Course: ";
    cin.getline(s.course,50);

    cout << "Enter Marks: ";
    cin >> s.marks;

    file.write((char*)&s,sizeof(s));

    file.close();

    cout << "\nStudent Added Successfully!";
}

void displayStudents()
{
    Student s;

    ifstream file("students.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo Records Found!";
        return;
    }

    cout << "\n-------------------------------------------------------------";
    cout << "\nRoll\tName\t\tAge\tCourse\t\tMarks";
    cout << "\n-------------------------------------------------------------";

    while(file.read((char*)&s,sizeof(s)))
    {
        cout << endl;
        cout << s.rollNo << "\t"
             << s.name << "\t\t"
             << s.age << "\t"
             << s.course << "\t\t"
             << s.marks;
    }

    file.close();
}

void searchStudent()
{
    Student s;
    int roll;
    bool found=false;

    ifstream file("students.dat", ios::binary);

    cout << "\nEnter Roll Number: ";
    cin >> roll;

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollNo==roll)
        {
            cout << "\nStudent Found";
            cout << "\nRoll No : " << s.rollNo;
            cout << "\nName    : " << s.name;
            cout << "\nAge     : " << s.age;
            cout << "\nCourse  : " << s.course;
            cout << "\nMarks   : " << s.marks;
            found=true;
            break;
        }
    }

    if(!found)
        cout << "\nStudent Not Found!";

    file.close();
}

void updateStudent()
{
    Student s;
    int roll;
    bool found=false;

    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollNo==roll)
        {
            found=true;

            cout << "\nEnter New Name: ";
            cin.ignore();
            cin.getline(s.name,50);

            cout << "Enter New Age: ";
            cin >> s.age;

            cin.ignore();

            cout << "Enter New Course: ";
            cin.getline(s.course,50);

            cout << "Enter New Marks: ";
            cin >> s.marks;

            file.seekp(-sizeof(s), ios::cur);

            file.write((char*)&s,sizeof(s));

            cout << "\nRecord Updated Successfully!";
            break;
        }
    }

    if(!found)
        cout << "\nStudent Not Found!";

    file.close();
}

void deleteStudent()
{
    Student s;
    int roll;
    bool found=false;

    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.rollNo==roll)
        {
            found=true;
        }
        else
        {
            temp.write((char*)&s,sizeof(s));
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat","students.dat");

    if(found)
        cout << "\nRecord Deleted Successfully!";
    else
        cout << "\nStudent Not Found!";
}