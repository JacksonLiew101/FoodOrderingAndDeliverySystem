#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

const int MAX_COLUMN = 3,
		MAX_CREDS = 50,
		MAX_RESTAURANT = 10;
const string PASS_FLAG = "0xCD",
			 BASE_ID = "0x";


void displayWelcomeMessage() {
	system("cls");

	cout << "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\t|        Welcome to YUMYUM Food Order and Delivery!        |\n"
		<< "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\tA great place for you to order at the comfort of your own place" << endl;
}

//clear all the unwanted input buffer first before next input, only for 'cin' type input
//test case: 
//Enter your User ID: hey there >> 'hey' will be save into the variable, 'there' will be remove
void clearInputBuffer() {
	while (getchar() != '\n') cin.clear();
}

void validateRepeat(char& repeat) {
	while (!(repeat == 'y' || repeat == 'Y' || repeat == 'n' || repeat == 'N')) {
		cout << "Invalid input! Only accept (Y/N) as input.\n"
			<< "Your input: ";
		cin >> repeat;
		clearInputBuffer();
	}
}

void askRepeat(char& repeat, string item) {
	cout << "\n\nDo you want to " << item << " ?(Y/N)";
	cin >> repeat;
	clearInputBuffer();
	validateRepeat(repeat);
}

void getCredentials(string& input_ID, string& input_pass) {
	cout << "\n\nEnter your User ID: ";
	cin >> input_ID;

	clearInputBuffer();

	cout << "Enter your passwords: ";
	cin >> input_pass;

	clearInputBuffer();

	input_pass.append(PASS_FLAG);
}

void validateUserType(char& user_type) {
	while (!(user_type == 'm' || user_type == 'c')) {
		cout << "Invalid input for account type! Only Enter 'm' for manager and 'c' for customer!\n"
			<< "Your new account type: ";
		cin >> user_type;

		clearInputBuffer();
	}
}

void getUserType(char& user_type) {
	system("cls");
	cout << "\t\t\t\tAccounts not found! It's time to sign up!\n"
		<< "\nDo you want to create a manager or customer account?\n"
		<< "['m' for manager, 'c' for customer]\n";
	cin >> user_type;
	clearInputBuffer();
	validateUserType(user_type);
}

void getRestaurantName(string& name) {
	cout << "\t\t\t\t\tYou successfully create a manager account!\n"
		<< "Time to create your online restaurant\n"
		<< "\nWhat is the name of your online restaurant?\n";
	getline(cin, name);
}

//create 3 files for new online restaurant
void createRestaurantFiles(string& restaurant_ID) {
	ofstream File_menu, File_stock, File_order;

	File_menu.open(restaurant_ID + "_menu.txt");
	File_stock.open(restaurant_ID + "_stock.txt");
	File_order.open(restaurant_ID + "_order.txt");

	File_menu.close();
	File_stock.close();
	File_order.close();

	cout << "File created successfully" << endl;
}

void createMenu(string& restaurant_ID) {

	//open necessary files
	ofstream File_menu, File_stock;

	File_menu.open(restaurant_ID + "_menu.txt");
	File_stock.open(restaurant_ID + "_stock.txt");

	//create menu and update stock
	if (File_menu.is_open() && File_stock.is_open()) {

	}
	else {
		cout << "Menu and stock files do not exist" << endl;
	}

	File_menu.close();
	File_stock.close();

}

void createNewRestaurant(string& user_ID) {
		string Restaurant_name, Restaurant_ID;
		int Array_size = 0;

		//create dynamic arrays
		string** restaurant;
		restaurant = new string * [MAX_RESTAURANT];
		for (int i = 0; i < MAX_RESTAURANT; ++i) {
			restaurant[i] = new string[MAX_COLUMN];
		}

		//read and save into array
		fstream File_restaurant;
		File_restaurant.open("restaurant.txt");
		if (File_restaurant.is_open()) {

			while (!File_restaurant.eof()) {
				//store the restaurant name
				getline(File_restaurant, restaurant[Array_size][0], '\t');

				//remove '\n' in the string
				if (restaurant[Array_size][0][0] == '\n') {
					restaurant[Array_size][0] = string(restaurant[Array_size][0].begin() + 1, restaurant[Array_size][0].end());
				}

				//store the restaurant id
				File_restaurant >> restaurant[Array_size][1];

				//store the manager id who will be managing the restaurant account
				File_restaurant >> restaurant[Array_size][2];

				++Array_size;
			}
		}
		else {
			cout << "The restaurant.txt file does not exist!" << endl;
		}

		//generate new id for the restaurant
		Restaurant_ID = BASE_ID + to_string(Array_size + 1);
	
		//get restaurant name
		getRestaurantName(Restaurant_name);
		
		createRestaurantFiles(Restaurant_ID);

		//add menu and update stock



		//add to restaurant array then rewrite to the restaurant file
		restaurant[Array_size][0] = Restaurant_name;
		restaurant[Array_size][1] = Restaurant_ID;
		restaurant[Array_size][2] = user_ID;

		//rewrite the array into the file

		//remove the dynamic array
		for (int i = 0; i < MAX_RESTAURANT; ++i) {
			delete[] restaurant[i];
		}
		delete[] restaurant;

		File_restaurant.close();
}

void signUp(char& user_type, string& user_ID) {

	
	string Input_password;
	int Array_size = 0;

	//declare a dynamic array
	string** creds;
	creds = new string* [MAX_CREDS];
	for (int i = 0; i < MAX_CREDS; ++i) {
		creds[i] = new string[MAX_COLUMN];
	}

	//read from file and store into dynamic array, and inform the size of the array
	fstream File_creds;
	File_creds.open("credentials.txt");

	if (File_creds.is_open()) {

		while (!File_creds.eof()) {

			//saving the user id
			File_creds >> creds[Array_size][0];

			//saving the user password
			File_creds >> creds[Array_size][1];

			//saving the user type
			File_creds >> creds[Array_size][2];

			++Array_size;
		}
	}
	else {
		cout << "The credentials.txt file does not exist!" << endl;
	}

	
	//Test this when change the previous functions
	/*
	cout << "This is testing for saving data from file to array" << endl;
	for (int i = 0; i <= Array_size; ++i) {
		if (creds[i][0] < " ") break;
		for (int j = 0; j < 3; ++j) {
			cout << creds[i][j] << "\t";
		}
		cout << endl;
	}
	system("pause");
	*/

	getUserType(user_type);

	//for customer sign up
	if (user_type == 'c') {

		cout << "\n\nYou are creating a new account as a customer!\n";
		getCredentials(user_ID, Input_password);

	}//for manager sign up
	else if(user_type == 'm') {
		system("cls");
		cout << "\n\nYou are creating a new account as a manager!\n";
		getCredentials(user_ID, Input_password);

		createNewRestaurant(user_ID);
	}
	else {
		cout << "Opps, something went wrong" << endl;
	}

	//add to creds array then rewrite to the credentials file
	creds[Array_size][0] = user_ID;
	creds[Array_size][1] = Input_password;
	creds[Array_size][2] = user_type;

	//rewrite everything into the file

	//Test this when the creds array is updated
	/*
	cout << "This is testing for updating" << endl;
	for (int i = 0; i <= Array_size; ++i) {
		if (creds[i][0] < " ") break;
		for (int j = 0; j < 3; ++j) {
			cout << creds[i][j] << "\t";
		}
		cout << endl;
	}
	system("pause");
	*/

	//remove the dynamic array
	for (int i = 0; i < MAX_CREDS; ++i) {
		delete[] creds[i];
	}
	delete[] creds;

	//close the credential.txt file
	File_creds.close();
}

bool signIn(char& user_type, string& user_ID) {

	bool Found_creds = 0;
	string User_password, Input_ID, Input_password;
	
	ifstream File_creds;
	File_creds.open("credentials.txt");

	getCredentials(Input_ID, Input_password);

	if (File_creds.is_open()) {
		while (!File_creds.eof()&&!Found_creds) {
			File_creds >> user_ID;
			File_creds >> User_password;
			File_creds >> user_type;

			//check the user id
			if (user_ID == Input_ID) {

				Found_creds = 1;

				//check the password
				while (User_password != Input_password) {
					cout << "You enter the wrong password. Try Again: ";
					cin >> Input_password;
					clearInputBuffer();

					//adding "0xCD" to add a level of encription to the passwords
					Input_password.append(PASS_FLAG);
				}
			}
		}
	}
	else {
		cout << "The credentials.txt file does not exist!" << endl;
	}

	File_creds.close();

	return Found_creds;
	
}


int main()
{
	char repeat = 'Y',
		user_type;
	string user_ID;

	string fooditem[10] = {};
	float price[10] = {},
		stock[10] = {};

	while ( (repeat =='Y') || (repeat =='y'))
	{
		//Welcome message then , sign in / sign up user
		displayWelcomeMessage();
		if (!signIn(user_type, user_ID)) {
			signUp(user_type, user_ID);
		}
		//After successful sign in / sign up, will turn to a new interface
		if (user_type == 'm') {

			//manager module
			while ( (repeat == 'Y') || (repeat == 'y') ) {
				//display message
				system("cls");
				cout << "This is the manager interface!" << endl;
				cout << "You have signed in as " << user_ID << endl;

				//start menu

				askRepeat(repeat, "check other items");
			}
		}
		else if (user_type == 'c') {

			//customer module
			while ( (repeat == 'Y') || (repeat == 'y') ) {
				//diplay message
				system("cls");
				cout << " This is the customer interface!" << endl;
				cout << "You have signed in as " << user_ID << endl;

				//order food

				askRepeat(repeat, "create new order");
			}
		}
		else {
			cout << "Opps, something went wrong!" << endl;
		}
		
		askRepeat(repeat, "return to the home screen");
	}

}



