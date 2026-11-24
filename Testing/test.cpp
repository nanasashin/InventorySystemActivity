#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    float price;
    int quantity;
};

int main()
{
    Product inventory[100];
    int count = 0;
    string choice;

    do
    {
        cout << "\ninbentori" << endl;
        cout << " Press '1' to add  Product" << endl;
        cout << " Press '2' to Display Products" << endl;
        cout << " Press '3' to Update Product" << endl;
        cout << " Enter 'Exit' to Exit " << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == "1")
        {
            if (count < 100)
            {
                cin.ignore();

                cout << "\ndenan meng lagyu pare: ";
                getline(cin, inventory[count].name);

                cout << "presyu naman: ";
                cin >> inventory[count].price;

                cout << "pilan buri mu: ";
                cin >> inventory[count].quantity;

                count++;

                cout << "\nokey ne, me add ne!" << endl;
            }
            else
            {
                cout << "\noyta sapak ne!" << endl;
            }
        }

        else if (choice == "2")
        {
            cout << "\nlistahan da reng produktu ning monupolyu mu kumpadre : " << endl;

            if (count == 0)
            {
                cout << "\nala yang laman!." << endl;
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    cout << "\nProductu pampanga #" << i + 1 << endl;
                    cout << "lagyu: " << inventory[i].name << endl;
                    cout << "presyu sapa: " << inventory[i].price << endl;
                    cout << "pilan: " << inventory[i].quantity << endl;
                }
            }
        }

        else if (choice == "3")
        {
            int number;

            cout << "\nnanung number ning product buri mung palitan: ";
            cin >> number;

            if (number >= 1 && number <= count)
            {
                cin.ignore();

                cout << "o nanung buri mung palagyu ulit: ";
                getline(cin, inventory[number - 1].name);

                cout << "nanung presyu boi: ";
                cin >> inventory[number - 1].price;

                cout << "pilan: ";
                cin >> inventory[number - 1].quantity;

                cout << "\noki na na apdit na ang imong prodak!" << endl;
            }
            else
            {
                cout << "\ne pwedi ing product namber boi!!!" << endl;
            }
        }

        else if (choice == "ikset" || choice == "Ikset")
        {
            cout << "\nsalamat keng pamag gamit keng system, pare!" << endl;
        }

        else
        {
            cout << "\n dili poidi ang choice! Try ulit." << endl;
        }

    } while (choice != "ikset" && choice != "Ikset");

    return 0;
}