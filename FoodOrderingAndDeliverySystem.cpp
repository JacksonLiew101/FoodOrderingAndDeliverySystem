#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;

const int ITEM = 10;

void welcomeMessage();
void checkValidUser(int&);
void getUserType(int&);
void displayMenu(string[], float[]);
float pickItem(string[], float[]);
void displayBill(float&);

//add a place to hold for user id and function for sign up and sign in
//add validation for customer function
//create a total function for calculating total(with delivery) and total order per bill and total order per day

int main()
{
	int user_type = 0;
	float total = 0;

	string food[ITEM] = {};
	float price[ITEM] = {};

	welcomeMessage();
	getUserType(user_type);

	//user_type 1 refer to manager, else refer to customer
	if (user_type == 1) {

	}
	else {
		displayMenu(food, price);
		total = pickItem(food, price);
		displayBill(total);
	}

	return 0;
}

//***************general functions*****************
void welcomeMessage() {
	cout << "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\t|        Welcome to Jackson Restaurant Food Order and Delivery!        |\n"
		<< "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\tA great place for you to order at the comfort of your own place" << endl;
}

void getUserType(int& user) {
	cout << "\nAre you a:\n"
		<< "1. Manager? or 2. Customer?" << endl;
	cin >> user;
	checkValidUser(user);
}

//for tackling out of range input
void checkValidUser(int& user) {
	while (user < 1 || user>2) {
		cout << "Please enter the valid choice(1.Manager / 2.Customer): ";
		cin >> user;
	}
}

//***************functions dedicated for manager*****************




//***************functions dedicated for customer*****************

//This function will fetch the food name and price from the menu.txt file, save into array and then display to user
void displayMenu(string food[], float price[]) {
	int count = 0;

	ifstream file_menu;
	file_menu.open("Menu.txt");

	cout << "       Food                                    Price\n"
		<< "------------------------------------------------------------------";

	//get all the items from menu.text file first and save them into array
	if (file_menu.is_open()) {
		while (!file_menu.eof()) {

			getline(file_menu, food[count], '\t');

			//for handling unwanted '\n' from the strings
			if (food[count][0] == '\n') {
				food[count] = string(food[count].begin() + 1, food[count].end());
			}

			file_menu >> price[count];

			cout << fixed << setprecision(2);
			cout << "\n[ " << count + 1 << " ] " << left << setw(50) << food[count]
				<< "      RM " << price[count];

			++count;
		}
		cout << endl;
	}
	else {
		cout << "The file does not exist";
	}

	file_menu.close();
}

//This function will prompt user to pick the item they want and repeat until they finish their order
float pickItem(string food[], float price[]) {

	int Index = 0,
		Quantity = 0;
	float Total = 0;
	char reply;

	do {
		cout << "\nWhich do you want to pick? ";
		cin >> Index;

		cout << "Your current order cart:\n";
		cout << food[Index - 1] << " -  RM " << price[Index - 1] << "\n";

		cout << "How many do you want?\n";
		cin >> Quantity;

		Total += (float)Quantity * price[Index - 1];

		cout << "You add order for " << Quantity << " of " << food[Index - 1] << "\n"
			<< "Total price = RM" << fixed << setprecision(2) << Total << endl;


		cout << "Do you want to add anything? (Y/N)\n";
		cin >> reply;
	} while (reply == 'Y' || reply == 'y');

	return Total;

}

//This function will display the bill to the user 
void displayBill(float& total) {
	cout << fixed << setprecision(2);
	cout << "\t\t\t\t\t\t-----------------------------------------------\n"
		<< "\t\t\t\t\t\t        Jackson Restaurant Food Delivery\n"
		<< "\t\t\t\t\t\tBill number: 2424              Order: FD5353\n"
		<< "\n\n "
		<< "\t\t\t\t\t\tYOUR TOTAL ORDER: RM" << total
		<< "\n\t\t\t\t\t\tDelivery fee: RM5.00"
		<< "\n\t\t\t\t\t\tFinal Amount: RM" << total + 5.00
		<< "\t\t\t\t\t\t-----------------------------------------------\n"
		<< "\t\t\t\t\t\t       THANK YOU FOR ORDERING! Your order will\n"
		<< "\t\t\t\t\t\t          delivered in the next 40 minutes" << endl;
}

