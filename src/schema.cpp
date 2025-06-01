#include "../headers/read.h"
#include<map>
#include<string>
#include<iostream>
using namespace std;
                         
map<string , string> create()
{
    map<string , string> data;
    char choice;
    string key , value;
    do 
    {
      cout<<"enter a key value"<<endl;
      cin>>key;

      cout<<"enter a value for key"<<endl;
      cin>>value;

       if (data.find(key) != data.end())// 
       {
            cout << "Key already exists! Overwriting value." << endl;
       }

      data[key] = value;

      cout<<"do you want to add another value"<<endl;
      cin >> choice;

       // to exit loop cleanly
       while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') 
        {
            cout << "Invalid choice! Please enter 'y' or 'n': ";
            cin >> choice;
        }
    }
    while (choice == 'y' ||  choice == 'Y');

return data;    
}
