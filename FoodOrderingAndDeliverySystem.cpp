#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
using namespace std;

const int BASE_ID = 0,
		MAX_COLUMN = 3,
		MAX_CRED = 50;
const string PASS_FLAG = "0xCD";


//MOD means module



//FOR WELCOMEMOD
void displayWelcomeMessage() {
	system("cls");

	cout << "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\t|        Welcome to YUMYUM Food Order and Delivery!        |\n"
		<< "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\tA great place for you to order at the comfort of your own place" << endl;
}

void fetchAndStoreCreds(fstream& file_creds, string creds[][MAX_COLUMN]) {
	if (file_creds.is_open()) {

		int i = 0;

		while (!file_creds.eof()) {
			string check;

			//fetch user id
			file_creds >> creds[i][0];

			//fetch user password
			file_creds >> creds[i][1];

			//fetch user type
			file_creds >> creds[i][2];

			++i;
		}

	}
	else {
		cout << "The file does not exist." << endl;
	}
}

void getCredentials(string& input_ID, string& input_pass) {
	cout << "\n\nEnter your User ID: ";
	cin >> input_ID;

	//clear all the unwanted input buffer first before next input
	//test case: 
	//Enter your User ID: hey there >> 'hey' will be save into the variable, 'there' will be remove
	while (getchar() != '\n') cin.clear();

	cout << "Enter your passwords: ";
	cin >> input_pass;

	input_pass.append(PASS_FLAG);
}

void validateUserType(char& user_type) {
	while (!(user_type == 'm' || user_type == 'c')) {
		cout << "Invalid input for account type! Only Enter 'm' for manager and 'c' for customer!\n"
			<< "Your new account type: ";
		cin >> user_type;
	}
}

void signIn(fstream& handle, char& user_type, string& user_ID, string creds[][MAX_COLUMN]) {

	bool Found_creds = 0;
	string Input_ID, Input_pass;
	int i = 0;

	getCredentials(Input_ID, Input_pass);

	//loop through the creds array to check the credentials
	while(!Found_creds) {
	
		//when the user ID is matched
		if (creds[i][0] == Input_ID) {

			Found_creds = 1;
			user_ID = Input_ID;

			//save the user type
			//final [0] is to access the first char of the string
			user_type = creds[i][2][0];

			//only loop the passwords when not true
			while(creds[i][1] != Input_pass) {
				cout << "You enter the wrong passwords! Try Again.";
				cin >> Input_pass;

				Input_pass.append(PASS_FLAG);
			}
		}

		//if reach empty elements in the array and still can't find the creds, time for sign up
		//ith row means empty row
		if (creds[i][0] < " " ) {
		
			//sign up
			system("cls");
			cout << "\t\t\t\tAccounts not found! It's time to sign up!\n"
				 << "\nDo you want to create a manager or customer account?\n"
				 << "['m' for manager, 'c' for customer]\n";
			cin >> user_type;
			validateUserType(user_type);

			//for customer sign up
			if (user_type == 'c') {

				cout << "\n\nYou are creating a new account as a customer!\n";
				getCredentials(Input_ID, Input_pass);


				
			}//for manager sign up
			else {
				cout << "\n\nYou are creating a new account as a manager!\n";
				getCredentials(Input_ID, Input_pass);

				//create a new restaurant
				fstream file_restaurant;
				file_restaurant.open("restaurant.txt");
			}
			
			
			//add to creds array then rewrite to the credentials file
			creds[i][0] = Input_ID;
			creds[i][1] = Input_pass;
			creds[i][2] = user_type;

			user_ID = Input_ID;
			
			system("cls");
			cout << "\nThis is testing for the array" << endl;
			for (int i = 0; i < 50; ++i) {
				if (creds[i][0] < " ") break;
				for (int j = 0; j < 3; ++j) {
					cout << creds[i][j] << "\t";
				}
				cout << endl;
			}


			Found_creds = 1;
		}
		
		++i;
	}


	
	

}




void welcomeMOD(char& user_type, string& user_id, string creds[][MAX_COLUMN]) {

	displayWelcomeMessage();

	fstream File_creds;
	File_creds.open("credentials.txt");

	fetchAndStoreCreds(File_creds, creds);

	//Test this when change the previous functions
	/*
	for (int i = 0; i < 50; ++i) {
		if (creds[i][0] < "A") break;
		for (int j = 0; j < 3; ++j) {
			cout << creds[i][j] << "\t";
		}
		cout << endl;
	}
	*/


	signIn(File_creds, user_type, user_id, creds);


	File_creds.close();

}

int main()
{
	char reply = 'Y',
		user_type;
	string user_ID;


	string creds[MAX_CRED][MAX_COLUMN] = {},
		restaurant[50][MAX_COLUMN] = {},
		fooditem[10] = {},
		order[100][MAX_COLUMN] = {};
	float price[10] = {},
		stock[10] = {};

	while ( (reply=='Y') || (reply=='y'))
	{
		//Welcome message then , sign in / sign up user
		welcomeMOD(user_type, user_ID, creds);

		/*
		//After successful sign in / sign up, will turn to a new interface
		if (user_type = 'm') {
			//manager module
			while (reply == 'Y' || reply == 'y') {
				//display message

				//start menu

				cout << "Do you want to create new order?(Y/N)";
				cin >> reply;
			}
		}
		else if (user_type = 'c') {
			//customer module
			while (reply == 'Y' || reply == 'y') {
				//diplay message


				//order food

				cout << "Do you want to create new order?(Y/N)";
				cin >> reply;
			}
		}
		else {
			cout << "Opps, something went wrong!" << endl;
		}
		*/
		
		cout << "Do you want to return to the home screen?(Y/N)";
		cin >> reply;

	}

}



