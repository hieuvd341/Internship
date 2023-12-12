#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person{
private:
    string name;
    int age;
public:
    virtual void getdata() {
        
    }
    virtual void putdata() {
        
    }
    void setName (string name) {
        this->name = name;
    }
    void setAge(int age) {
        this->age= age;
    }
    string getName() {
        return this->name;
    }
    int getAge() {
       return this->age; 
    }
};
class Professor : public Person{
private:
    int publications;
    int cur_id;
    static int id;
public:
    Professor(){
        id++;
        cur_id=id;
    }
    void getdata() {
        string name;
        cin >>name;
        Person::setName(name);
        int age;
        cin>>age;
        Person::setAge(age);
        cin >> publications;
    }
    void putdata(){
            cout << Person::getName() << " " << Person::getAge() << " " << publications << " " << cur_id << endl;
    }
};
int Professor ::id =0;
class Student : public Person{
private:
    static int id;
    int marks[6];
    int cur_id;
public:
    Student() {
        id++;
        cur_id = id;
    }
    void getdata() {
        string name;
        cin >>name;
        Person::setName(name);
        int age;
        cin>>age;
        Person::setAge(age);
        for(int i=0; i<6; i++) {
            cin >> marks[i];
        }
        
    }
    int sumOfTheMarks() {
        int sum=0;
        for(int i =0; i<6; i++) {
            sum += marks[i];
        }
        return sum;
    }
    void putdata() {
        cout << Person::getName() << " " << Person::getAge() << " ";
        cout << sumOfTheMarks()<<" " << cur_id<<endl;
        
    } 
    
};
int Student :: id=0;
int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}