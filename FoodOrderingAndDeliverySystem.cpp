#include <iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

const int ITEM = 10;

void displayWelcomeMessage();
void checkValidUser(int&);
void checkValidReply(char&);
void getUserType(int&);

void signInManager();
void signInCustomer();
bool signUpCustomer(string&, string&);

void displayManagerFunc();
void pickManagerFunc();
void displayMenu(string[], float[]);
float pickMenuItem(string[], float[]);
void displayBill(float&);

//add a place to hold for user id and function for sign up and sign in
//add validation for customer function
//create a total function for calculating total(with delivery) and total order per bill and total order per day

int main()
{
	int user_type = 0;
	float total = 0;
	char reply = 'Y';


	string food[ITEM] = {};
	float price[ITEM] = {};

	while ((reply == 'Y') || (reply == 'y')) {
		displayWelcomeMessage();
		getUserType(user_type);

		//user_type 1 refer to manager, else refer to customer
		if (user_type == 1) {
			//only show the menu then display the manager interface
			signInManager();
			displayManagerFunc();
		}
		else {
			signInCustomer
			displayMenu(food, price);
			total = pickMenuItem(food, price);
			displayBill(total);
		}

		cout << "Do you want to return to the welcome page?(Y/N)";
		cin >> reply;
		checkValidReply(reply);
	}
	

	return 0;
}

//***************general functions*****************
void displayWelcomeMessage() {
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

void checkValidReply(char& reply)
{
	while (reply != 'Y ' || reply != 'y' || reply != 'N' || reply != 'n') {
		cout << "Too bad! Your input is invalid!\n"
			 << "Enter Y or N only: ";
		cin >> reply;
	}
}




//***************functions dedicated for manager*****************

//This function is for checking whether the sign in details for manager is correct or not
void signInManager() {
	string Email_input,
		Pass_input,
		Manager_email = "jacksonrestaurant@gmail.com",
		Manager_pass = "myrestaurantthebest1";

	system("cls");

	cout << "You just enter as a manager!\n\n";


	//check the credentials
	do {
		cout << "Enter the manager email: ";
		cin >> Email_input;
		cout << "Enter the password     : ";
		cin >> Pass_input;

		if (Email_input != Manager_email || Pass_input != Manager_pass) {
			cout << "\nThe credentials are not correct. Please try again!" << endl;
		}

	} while (Email_input != Manager_email || Pass_input != Manager_pass);

	//when credentials are verified correctly
	cout << "\nGreat! You are now signed in to the manager section of the food order and delivery system." << endl;
}

void displayManagerFunc() {
	cout << "\nHi! This is the place for you to change menu and track orders.\n"
		<< "1. Create/Update Menu\n"
		<< "2. Update prices\n"
		<< "3. Accept orders\n"
		<< "4. Count Total Payments per order\n"
		<< "5. Calculate estimated delivery time\n"
		<< "6. Calculate total sales for a day\n" << endl;
}

void pickManagerFunc()
{
	int Index = 0;
	char Reply = 'Y';

	while (Reply == 'Y' || Reply == 'y'){
		cout << "\nWhich one do you want to access? ";
		cin >> Index;

		switch (Index) {
			case 1:
				//create/update menu function
				break;
			case 2:
				//update prices function
				break;
			case 3: 
				//accept orders
				break;
			case 4: 
				//calculate total payments per order
				break;
			case 5: 
				//calculate the estimated delivery time
				break;
			case 6:
				//calculate the total sales for a day
				break;
			default:
				cout << "The selection is invalid" << endl;
				break;
		}

		cout << "Do you want to access anything else? (Y/N)\n";
		cin >> Reply;
		checkValidReply(Reply);
	}

}



//***************functions dedicated for customer*****************

void signInCustomer()
{
	string User_email, User_pass, Email_input, Pass_input;
	bool Is_valid_email = 0,
		 Is_valid_pass = 0;

	ifstream File_cred;
	File_cred.open("UserCreds.txt");

	system("cls");

	cout << "You just enter as a customer!\n\n";


	//request for sign in details
	cout << "Enter the your user ID(email address): ";
	cin >> Email_input;
	cout << "Enter the password                   : ";
	cin >> Pass_input;

	if (File_cred.is_open()) {
		while (!File_cred.eof()) {
			getline(File_cred, User_email, '\t');

			//for handling unwanted '\n' from the strings
			if (User_email[0] == '\n') {
				User_email = string(User_email.begin() + 1, User_email.end());
			}

			File_cred >> User_pass;
			
			//stop when find the exact email address
			if (User_email == Email_input) {
				Is_valid_email = 1;
				break;
			}
		}

		if (!Is_valid_email) {
			//after checking all the creds found no similar
			//function for sign up, if done//return true, skip to food menu
			cout << "Your email is not found. Feel free to sign up for a new account.\n\n";

			//set the both flags as true when you successfully sign up the account
			Is_valid_email = Is_valid_pass = signUpCustomer(Email_input, Pass_input);

		}
		else {
			//make sure the password is correct with while loop
			while(User_pass != Pass_input) {
				cout << "The password is incorrect. Try again:\n";
				cin >> Pass_input;
			}
			Is_valid_pass = 1;

		}
		
		if (Is_valid_email && Is_valid_pass) {
			cout << "You just signed in successfully!" << endl;
		}

	}
	else {
		cout << "The file called UserCreds.txt does not exist. Validation cannot run." << endl;
	}

	File_cred.close();

	return true;
}

void signUpCustomer(string& email, string& pass) {
	cout << "Enter the email address for your new account : ";
	cin >> email;
	cout << "Enter a new password for your new account    : ";
	cin >> pass;

	//later add the validation then only return true for right format

	return true;
}

//This function will fetch the food name and price from the menu.txt file, save into array and then display to user
void displayMenu(string food[], float price[]) {
	int Count = 0;

	ifstream File_menu;
	File_menu.open("Menu.txt");

	system("cls");

	cout << "       Food                                    Price\n"
		<< "------------------------------------------------------------------";

	//get all the items from menu.text file first and save them into array
	if (File_menu.is_open()) {
		while (!File_menu.eof()) {

			getline(File_menu, food[Count], '\t');

			//for handling unwanted '\n' from the strings
			if (food[Count][0] == '\n') {
				food[Count] = string(food[Count].begin() + 1, food[Count].end());
			}

			File_menu >> price[Count];

			cout << fixed << setprecision(2);
			cout << "\n[ " << Count + 1 << " ] " << left << setw(50) << food[Count]
				<< "      RM " << price[Count];

			++Count;
		}
		cout << endl;
	}
	else {
		cout << "The file does not exist";
	}

	File_menu.close();
}

//This function will prompt user to pick the item they want and repeat until they finish their order
float pickMenuItem(string food[], float price[]) {

	int Index = 0,
		Quantity = 0;
	float Total = 0;
	char Reply;

	ofstream File_order;
	File_order.open("order.txt",ios::app);

	do {
		cout << "\nWhich do you want to pick? ";
		cin >> Index;
		
		//print out to the console
		cout << "Your current order cart:\n";
		cout << food[Index - 1] << " -  RM " << price[Index - 1] << "\n";

		cout << "How many do you want?\n";
		cin >> Quantity;

		Total += (float)Quantity * price[Index - 1];

		cout << "You add order for " << Quantity << " of " << food[Index - 1] << "\n"
			<< "Total price = RM" << fixed << setprecision(2) << Total << endl;


		cout << "Do you want to add anything? (Y/N)\n";
		cin >> Reply;
	} while (Reply == 'Y' || Reply == 'y');

	//print out to a file to keep track of order
	File_order << Total << endl;

	File_order.close();

	return Total;

}

//This function will display the bill to the user 
void displayBill(float& total) {
	system("cls");

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

