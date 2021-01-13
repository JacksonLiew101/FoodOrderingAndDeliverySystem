/*****************************************************************************************************************************
/* CPT111 Assignment 2: Food Ordering System
/* Programmer name: LIEW MAN HONG
/* Programmer Matric #: 151807
/*****************************************************************************************************************************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<iomanip>
using namespace std;

// Global Constants declaration
const int MAX_COLUMN = 3,
		MAX_CREDS = 50,
		MAX_RESTAURANT = 20,
		MAX_ITEM = 10;
const string PASS_FLAG = "0xCD",
			 BASE_ID = "0x";

// All functions prototype, proper explanation is below main function, xxxMOD means the function is module-like, which consists of multiple functions
void clearInputBuffer();
void validateRepeat(char&);
void askRepeat(char&, string);
void displayWelcomeMessage();
void displayWelcomeMessage();
void getCredentials(string&, string&);
void validateUserType(char&);
void getUserType(char&);
void getRestaurantName(string&);
void createRestaurantFiles(string&);
void getItemAndPrice(string&, float&, int);
void displayCreateMenuMessage();
void createMenu(string&);
void createNewRestaurantMOD(string&);
void displaySignUpInterface();
void signUpMOD(char&, string&);
void displaySignInInterface();
bool signInMOD(char&, string&);
void displayManagerInterface(string&, string&);
void displayManagerMenu(string&, string&);
void validateManagerPick(int&);
void pickManagerFunction(int&);
void fetchRestaurantDetails(string&, string&, string&);
void updateMenuMOD(string&, string&, string&, string);
void checkStockAvailabilityMOD(string&, string&, string&);
void checkOrderMOD(string&, string&, string&, string);
void runManagerFunction(int&, string&, string&, string&);
void managerInterfaceMOD(char&, string&);



//displaySignOutMessage will display sign out message
void displaySignOutMessage() {
	cout << "\nYou choose to sign out for now!" << endl;
}

//openRestaurantFile will open the necessary files related to the specific function
void openRestaurantFile(fstream& handle, string& ID, char type) {
	switch (type)
	{
	case 'm':
		handle.open(ID + "_menu.txt");
		break;
	case 'o':
		handle.open(ID + "_order.txt");
		break;
	case 's':
		handle.open(ID + "_stock.txt");
		break;
	default:
		cout << "Opps, something went wrong." << endl;
		break;
	}
}

//displayFoodMenu will display the specific menu for the restaurant
void displayFoodMenu(string item[], float price[]) {
	cout << "\n                    Food                                      Price(RM)    " << endl;
	for (int i = 0; i < MAX_ITEM; ++i) {
		cout << right << setw(2) << i+1 << ". " << left << setw(60) << item[i] << "| " << price[i] << " |" << endl;
	}
}

//validatePickMenu will validate during pickMenuItem Function
void validatePickMenu(int& choice) {
	while (choice < 1 || choice > 10) {
		cout << "\nInvalid item! Pick again.(From 1 to 10 only)\n"
			<< "Item number: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//pickMenuItem will request input for picking one of the item on menu
int pickMenuItem(string type) {

	int Choice = 0;

	cout << "\nWhich menu " << type << " you want to change now?\n"
		<< "Item number: ";
	cin >> Choice;
	clearInputBuffer();
	validatePickMenu(Choice);

	return Choice;
}

//displayCustomerInterface will indicate it is a Customer Interface
void displayCustomerInterface(string& user_ID) {
	system("cls");
	cout << "-----------------\n"
		<< "|    Customer    |\n"
		<< "-----------------\n" << endl;
	cout << "You have signed in as " << user_ID << endl;
}

//displayCustomerMenu will display all the functions customer can access
void displayCustomerMenu(string& user_ID) {
	displayCustomerInterface(user_ID);

	cout << "\t\t\t-----------------------------------\n"
		<< "\t\t\t|          Customer Menu           |\n"
		<< "\t\t\t-----------------------------------\n"
		<< "0. Sign out current account\n"
		<< "1. Order Food\n" << endl;

}

//validateCustomerPick will validate during pickCustomerFunction Function
void validateCustomerPick(int& choice) {
	while (choice != 0 && choice != 1) {
		cout << "Invalid item! Pick again.(0 or 1 only)\n"
			<< "Item number: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//pickCustomerFunction will request input for picking customer functions 
void pickCustomerFunction(int& choice) {
	cout << "\nWhich customer function you want to access now?\n"
		<< "Item number: ";
	cin >> choice;
	clearInputBuffer();
	validateManagerPick(choice);
}

void orderFoodMOD(string& user_ID) {
	displayCustomerInterface(user_ID);

	 
}

void runCustomerFunction(int& choice, string& user_ID) {
	switch (choice)
	{
	case 0:
		displaySignOutMessage();
		break;
	case 1:
		orderFoodMOD(user_ID);
		break;
	default:
		cout << "Opps, something went wrong!" << endl;
		break;
	}

}

//customerInterfaceMOD will let customer to order food and make payment
void customerInterfaceMOD(char& repeat, string& user_ID) {

	int Choice = 0;

	//customer module
	while ((repeat == 'Y') || (repeat == 'y')) {
		
		displayCustomerMenu(user_ID);

		pickCustomerFunction(Choice);

		runCustomerFunction(Choice, user_ID);

		//0 is sign out, hence other than 0 will ask whether to create new order
		if (Choice != 0) {
			askRepeat(repeat, "create new order");
		}
		else {
			break;
		}
	}
}

//************************************************************************************************************************
// Main Function                                      
//************************************************************************************************************************

int main()
{
	char repeat = 'Y', user_type;
	string user_ID;

	while ( (repeat =='Y') || (repeat =='y'))
	{
		displayWelcomeMessage();

		//First will prompt for sign in, if unable will ask user to sign up accordingly
		if (!signInMOD(user_type, user_ID)) {
			signUpMOD(user_type, user_ID);
		}

		//After successful sign in / sign up, will turn to respective interface
		if (user_type == 'm') {

			managerInterfaceMOD(repeat, user_ID);
			
		}
		else if (user_type == 'c') {

			customerInterfaceMOD(repeat, user_ID);

		}
		else {
			cout << "Opps, something went wrong!" << endl;
		}
		
		askRepeat(repeat, "return to the home screen");
	}

}


//************************************************************************************************************************
// General Functions                                  
//************************************************************************************************************************

//clearInputBuffer will remove all the unwanted input buffer first before next input(only for 'cin' type input)
void clearInputBuffer() {
	/*test case:
	Enter your User ID: hey there
	>> 'hey' will be save into the variable, 'there' will be remove*/
	while (getchar() != '\n') cin.clear();
}

// validateRepeat will validate the input during askRepeat Function
void validateRepeat(char& repeat) {
	while (!(repeat == 'y' || repeat == 'Y' || repeat == 'n' || repeat == 'N')) {
		cout << "Invalid input! Only accept (Y/N) as input.\n"
			<< "Your input: ";
		cin >> repeat;
		clearInputBuffer();
	}
}

// askRepeat will ask the user whether to stay in the same interface or not
void askRepeat(char& repeat, string item) {
	cout << "\n\nDo you want to " << item << " ?(Y/N)";
	cin >> repeat;
	clearInputBuffer();
	validateRepeat(repeat);
}


//***********************************************************************************************************************
// Welcome Functions                                       
//***********************************************************************************************************************

//displayWelcomeMessage will display welcome interface
void displayWelcomeMessage() {
	system("cls");

	cout << "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\t|             Welcome to YUMYUM Food Order and Delivery!               |\n"
		<< "\t\t\t-----------------------------------------------------------------------\n"
		<< "\t\t\tA great place for you to order at the comfort of your own place" << endl;
}

//getCredentials will request input for id and password
void getCredentials(string& input_ID, string& input_password) {
	cout << "\n\nEnter your User ID: ";
	cin >> input_ID;

	clearInputBuffer();

	cout << "Enter your passwords: ";
	cin >> input_password;

	clearInputBuffer();

	//add "0xCD" for a level of encryption
	input_password.append(PASS_FLAG);
}

//validateUserType will validate the input during getUserType function
void validateUserType(char& user_type) {
	while (!(user_type == 'm' || user_type == 'c')) {
		cout << "Invalid input for account type! Only Enter 'm' for manager and 'c' for customer!\n"
			<< "Your new account type: ";
		cin >> user_type;

		clearInputBuffer();
	}
}

//getUserType will request input for user type
void getUserType(char& user_type) {
	system("cls");
	cout << "\t\t\t\t----------------------------------------------\n"
		 << "\t\t\t\t| Accounts not found! It's time to sign up!  |\n"
		 << "\t\t\t\t----------------------------------------------\n"
		 << "\nDo you want to create a manager or customer account?\n"
		 << "['m' for manager, 'c' for customer]\n";
	cin >> user_type;
	clearInputBuffer();
	validateUserType(user_type);
}

//getRestaurantName will request input for restaurant name
void getRestaurantName(string& name) {
	
	system("cls");	
	cout << "\t\t\t\t----------------------------------------------\n"
		 << "\t\t\t\t| You successfully create a manager account! |\n"
		 << "\t\t\t\t----------------------------------------------\n"
		 << "Time to create your online restaurant!\n"
		 << "\nWhat is the name of your online restaurant?\n";
	getline(cin, name);
}

//createRestaurantFiles will create 3 files for the new online restaurant
void createRestaurantFiles(string& restaurant_ID) {
	ofstream File_menu, File_stock, File_order;

	File_menu.open(restaurant_ID + "_menu.txt");
	File_stock.open(restaurant_ID + "_stock.txt");
	File_order.open(restaurant_ID + "_order.txt");

	File_menu.close();
	File_stock.close();
	File_order.close();

	cout << "\n\nFiles for your restaurant are created successfully!" << endl;
}

//getItemAndPrice will request input for menu item and price
void getItemAndPrice(string& item, float& price, int i) {
	cout << "Item " << i + 1 << " : ";
	getline(cin, item);
	cout << "Price " << i + 1 << " (in RM): ";
	cin >> price;
	clearInputBuffer();
}

//displayCreateMenuMessage will indicate it is create menu interface
void displayCreateMenuMessage() {
	system("cls");
	cout << "\t\t\t\t----------------------------------------------\n"
		 << "\t\t\t\t|            Creating new Menu               |\n"
		 << "\t\t\t\t----------------------------------------------\n"
	     << "\t\t\t\tYou are now creating 10 items for your menu.\n\n" << endl;
}

//createMenu will add menu item and price into new menu file and also initialise stock quantity
void createMenu(string& restaurant_ID) {

	string Item;
	float Price = 0;

	ofstream File_menu, File_stock;

	File_menu.open(restaurant_ID + "_menu.txt");
	File_stock.open(restaurant_ID + "_stock.txt");

	//create menu and update stock
	if (File_menu.is_open() && File_stock.is_open()) {

		

		for (int i = 0; i < MAX_ITEM; ++i) {
			//getting item and price
			getItemAndPrice(Item, Price, i);

			//update to menu and stock file
			if (i == (MAX_ITEM - 1)) {
				File_menu << Item << "\t" << fixed << setprecision(2) << Price;
				File_stock << Item << "\t" << 50;
			}
			else {
				File_menu << Item << "\t" << fixed << setprecision(2) << Price << "\n";
				File_stock << Item << "\t" << 50 << "\n";
			}
			
		}
	}
	else {
		cout << "Menu and stock files do not exist" << endl;
	}

	File_menu.close();
	File_stock.close();

}

//createNewRestaurantMOD will help new manager to create restaurant name, restaurant id, files for restaurant and update details into restaurant list
void createNewRestaurantMOD(string& user_ID) {
	
	string Restaurant_name, Restaurant_ID;
	int Array_size = 0;

	//create dynamic arrays, the reason I used this because I don't need the array later on, better to destroy the array after using it
	string** restaurant;
	restaurant = new string * [MAX_RESTAURANT];
	for (int i = 0; i < MAX_RESTAURANT; ++i) {
		restaurant[i] = new string[MAX_COLUMN];
	}

	//read from file and store into dynamic array, and inform the size of the array
	ifstream File_restaurant;
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
	File_restaurant.close();

	//generate new id for the restaurant
	Restaurant_ID = BASE_ID + to_string(Array_size + 1);

	getRestaurantName(Restaurant_name);

	createRestaurantFiles(Restaurant_ID);

	createMenu(Restaurant_ID);

	//add new data into restaurant array
	restaurant[Array_size][0] = Restaurant_name;
	restaurant[Array_size][1] = Restaurant_ID;
	restaurant[Array_size][2] = user_ID;

	//Test this when change the previous functions
	/*
	cout << "This is testing for latest changes of array" << endl;
	for (int i = 0; i <= Array_size; ++i) {
		for (int j = 0; j < MAX_COLUMN; ++j) {
			cout << restaurant[i][j] << "\t";
		}
		cout << endl;
	}
	system("pause");
	*/

	//add data into file
	ofstream File_change;
	File_change.open("restaurant.txt");
	if (File_change.is_open()) {
		for (int i = 0; i <= Array_size; ++i) {
			for (int j = 0; j < MAX_COLUMN; ++j) {
				if (j == (MAX_COLUMN - 1)) {
					File_change << restaurant[i][j];
				}
				else {
					File_change << restaurant[i][j] << "\t";
				}

			}
			if (i == Array_size) break;
			File_change << endl;
		}
	}
	else {
		cout << "The restaurant.txt file does not exist!" << endl;
	}
	File_change.close();

	//remove the dynamic array
	for (int i = 0; i < MAX_RESTAURANT; ++i) {
		delete[] restaurant[i];
	}
	delete[] restaurant;


}

//displaySign up will indicate it is sign up interface
void displaySignUpInterface() {
	system("cls");
	cout << "-----------------\n"
		<< "|    Sign Up    |\n"
		<< "-----------------\n" << endl;
}

//signUpMOD will ask user to sign up and create account and update the new credentials to the credentials list
void signUpMOD(char& user_type, string& user_ID) {

	string Input_password;
	int Array_size = 0;

	//declare a dynamic array
	string** creds;
	creds = new string * [MAX_CREDS];
	for (int i = 0; i < MAX_CREDS; ++i) {
		creds[i] = new string[MAX_COLUMN];
	}

	//read from file and store into dynamic array, and inform the size of the array
	ifstream File_creds;
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
	File_creds.close();

	//Test this when change the previous functions
	/*
	cout << "This is testing for saving data from file to array" << endl;
	for (int i = 0; i <= Array_size; ++i) {
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

		displaySignUpInterface();
		cout << "\n\n\t\tYou are creating a new account as a customer!\n";
		getCredentials(user_ID, Input_password);

	}//for manager sign up
	else if (user_type == 'm') {
		
		displaySignUpInterface();
		cout << "\n\n\t\tYou are creating a new account as a manager!\n";
		getCredentials(user_ID, Input_password);

		createNewRestaurantMOD(user_ID);
	}
	else {
		cout << "Opps, something went wrong" << endl;
	}

	//add new data into creds array
	creds[Array_size][0] = user_ID;
	creds[Array_size][1] = Input_password;
	creds[Array_size][2] = user_type;

	//test this after changing previous function
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

	//add data into file
	ofstream File_change;
	File_change.open("credentials.txt");

	if (File_change.is_open()) {
		for (int i = 0; i <= Array_size; ++i) {
			for (int j = 0; j < MAX_COLUMN; ++j) {
				if (j == (MAX_COLUMN - 1)) {
					File_change << creds[i][j];
				}
				else {
					File_change << creds[i][j] << "\t";
				}

			}
			if (i == Array_size) break;
			File_change << endl;
		}
	}
	else {
		cout << "The credentials.txt file does not exist!" << endl;
	}
	File_change.close();

	//remove the dynamic array
	for (int i = 0; i < MAX_CREDS; ++i) {
		delete[] creds[i];
	}
	delete[] creds;

}

//displaySignInMessage will indicate it is sign in interface
void displaySignInInterface() {
	cout << "-----------------\n"
		 << "|    Sign In    |\n"
		 << "-----------------\n" << endl;
}

//signInMOD will ask user to sign in and return true if the credentials are available in the file
bool signInMOD(char& user_type, string& user_ID) {

	bool Found_creds = 0;
	string User_password, Input_ID, Input_password;

	ifstream File_creds;
	File_creds.open("credentials.txt");

	displaySignInInterface();
	getCredentials(Input_ID, Input_password);

	if (File_creds.is_open()) {
		while (!File_creds.eof() && !Found_creds) {
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


//*************************************************************************************************************************
// Manager part                                       
//*************************************************************************************************************************

//displayManagerInterface will indicate it is a Manager Interface
void displayManagerInterface(string& restaurant_name, string& user_ID) {
	system("cls");
	cout << "-----------------\n"
		<< "|     Manager    |\n"
		<< "-----------------\n" << endl;
	cout << "Current restaurant is " << restaurant_name << endl;
	cout << "You have signed in as " << user_ID << endl;
}

//displayManagerMenu will display all the functions manager can access
void displayManagerMenu(string& restaurant_name, string& user_ID) {
	displayManagerInterface(restaurant_name, user_ID);

	cout << "\t\t\t-----------------------------------\n"
		<< "\t\t\t|          Manager Menu           |\n"
		<< "\t\t\t-----------------------------------\n"
		<< "0. Sign out current account\n"
		<< "1. Update menu item\n"
		<< "2. Update item prices\n"
		<< "3. Check stock availability\n"
		<< "4. Check Total Payments per order\n"
		<< "5. Check estimated delivery time\n"
		<< "6. Calculate total sales for a day\n" << endl;

}

//validateManagerPick will validate during pickManagerFunction Function
void validateManagerPick(int& choice) {
	while (choice < 0 || choice > 6) {
		cout << "Invalid item! Pick again.(From 0 to 6 only)\n"
			<< "Item number: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//pickManagerFunction will request input for picking manager functions 
void pickManagerFunction(int& choice) {
	cout << "\nWhich manager function you want to access now?\n"
		<< "Item number: ";
	cin >> choice;
	clearInputBuffer();
	validateManagerPick(choice);
}

//fetchRestaurant will fetch the restaurant name, restaurant id from the file based on user_id
void fetchRestaurantDetails(string& name, string& restaurant_ID, string& user_ID) {

	string Check_ID;
	bool Found_ID = 0;

	//open restaurant file
	ifstream File_restaurant;
	File_restaurant.open("restaurant.txt");

	if (File_restaurant.is_open()) {
		while (!File_restaurant.eof() && !Found_ID) {
			//store the restaurant name
			getline(File_restaurant, name, '\t');

			//remove '\n' in the string
			if (name[0] == '\n') {
				name = string(name.begin() + 1, name.end());
			}

			//store the restaurant ID
			File_restaurant >> restaurant_ID;

			//store the related manager user_ID
			File_restaurant >> Check_ID;

			//check whether the user_id match or not
			if (Check_ID == user_ID) {
				Found_ID = 1;
			}
		}
	}
	else {
		cout << "The restaurant.txt file does not exist." << endl;
	}

	File_restaurant.close();
}

//updateMenuMOD will let manager to update specific item/price on the menu and update to files
void updateMenuMOD(string& restaurant_name, string& restaurant_ID, string& user_ID, string type) {

	//declare parallel array
	string Item[MAX_ITEM] = {};
	float Price[MAX_ITEM] = {};
	int i = 0, Item_changed = 0;
	char Repeat = 'y';

	displayManagerInterface(restaurant_name, user_ID);

	cout << "\nYou can change " << type << " in the menu here" << endl;

	fstream File_menu, File_stock;
	openRestaurantFile(File_menu, restaurant_ID, 'm');
	openRestaurantFile(File_stock, restaurant_ID, 's');

	//open menu.txt file and store inside dynamic array
	if (File_menu.is_open()) {

		while (!File_menu.eof() && i < MAX_ITEM) {

			//store the menu item
			getline(File_menu, Item[i], '\t');

			//remove '\n' in the string
			if (Item[i][0] == '\n') {
				Item[i] = string(Item[i].begin() + 1, Item[i].end());
			}

			//store the price of the item
			File_menu >> Price[i];

			++i;
		}
	}
	else {
		cout << "The " << restaurant_ID << "_stock.txt file does not exist" << endl;
	}

	File_menu.close();

	//display the menu item and respective price
	displayFoodMenu(Item, Price);

	//change the specific item/price 
	while (Repeat == 'y' || Repeat == 'Y') {

		Item_changed = pickMenuItem(type) - 1;

		if (type == "item") {
			cout << "\nWhat food do you want to change to?";
			getline(cin, Item[Item_changed]);
		}
		else if (type == "price") {
			cout << "\nWhat price do you want to change to?";
			cin >> Price[Item_changed];
			clearInputBuffer();
		}
		else {
			cout << "Opps, something went wrong." << endl;
		}

		askRepeat(Repeat, "change other " + type);
	}

	//open the menu file again and rewrite everything into the menu file and stock ifle
	openRestaurantFile(File_menu, restaurant_ID, 'm');
	for (int j = 0; j < MAX_ITEM; ++j) {

		if (j == (MAX_ITEM - 1)) {
			File_menu << Item[j] << "\t" << fixed << setprecision(2) << Price[j];
			File_stock << Item[j] << "\t" << 50;
		}
		else {
			File_menu << Item[j] << "\t" << fixed << setprecision(2) << Price[j] << "\n";
			File_stock << Item[j] << "\t" << 50 << "\n";
		}
	}

	File_menu.close();
	File_stock.close();

}

//checkStockAvailabilityMOD will let manager to check how much stock is available for delivery
void checkStockAvailabilityMOD(string& restaurant_name, string& restaurant_ID, string& user_ID) {

	string Item;
	int Quantity_left;

	displayManagerInterface(restaurant_name, user_ID);

	cout << "\nYou can check stock availability here" << endl;

	//open stock.txt file
	fstream File_stock;
	openRestaurantFile(File_stock, restaurant_ID, 's');

	if (File_stock.is_open()) {

		cout << "\n                    Food                                 Order Availability    " << endl;

		while (!File_stock.eof()) {

			//store the menu item
			getline(File_stock, Item, '\t');

			//remove '\n' in the string
			if (Item[0] == '\n') {
				Item = string(Item.begin() + 1, Item.end());
			}

			//store the stock availability
			File_stock >> Quantity_left;

			//output to the console app
			cout << "| " << left << setw(60) << Item << "| " << Quantity_left << " |" << endl;
		}
	}
	else {
		cout << "The " << restaurant_ID << "_stock.txt file does not exist" << endl;
	}

	File_stock.close();
}

//checkOrderMOD will let manager to check order related details such as total payment, delivery time and total sales of day
void checkOrderMOD(string& restaurant_name, string& restaurant_ID, string& user_ID, string type) {

	string Order_ID;
	int Time = 0,
		Total_order = 0;
	float Total_payment = 0,
		Total_sale_of_day = 0;

	displayManagerInterface(restaurant_name, user_ID);

	cout << "\nYou can check " << type << " for each order here" << endl;

	//open order.txt file
	fstream File_order;
	openRestaurantFile(File_order, restaurant_ID, 'o');

	if (File_order.is_open()) {

		//output title according to the type of request
		if (type == "delivery time") {
			cout << "\n            Order ID                                         Delivery Time(minutes)    " << endl;
		}
		else if (type == "total payment per order") {
			cout << "\n            Order ID                                         Payment Per Order(RM)    " << endl;
		}
		else if (type == "total sale") {
			cout << "\n            Total orders                                     Total sales of the day(RM)    " << endl;
		}


		while (!File_order.eof()) {

			//store the order ID
			getline(File_order, Order_ID, '\t');

			//remove '\n' in the string
			if (Order_ID[0] == '\n') {
				Order_ID = string(Order_ID.begin() + 1, Order_ID.end());
			}

			//store the total payment
			File_order >> Total_payment;

			//store the delivery time
			File_order >> Time;

			//caculating the sum of order and the sum of sale of the day
			++Total_order;
			Total_sale_of_day += Total_payment;

			//output to the console app according to the type of request
			if (type == "delivery time") {
				cout << "| " << left << setw(60) << Order_ID << "| " << setw(3) << Time << " |" << endl;
			}
			else if (type == "total payment per order") {
				cout << "| " << left << setw(60) << Order_ID << "| " << setw(6) << fixed << setprecision(2) << Total_payment << " |" << endl;
			}

		}

		//output to the console app specifically for counting total
		if (type == "total sale") {
			cout << "| " << left << setw(60) << Total_order << "| " << setw(6) << fixed << setprecision(2) << Total_sale_of_day << " |" << endl;
		}
	}
	else {
		cout << "The " << restaurant_ID << "_order.txt file does not exist" << endl;
	}

	File_order.close();
}

//runManagerFunction will run the specific Function based on the choice the manager pick
void runManagerFunction(int& choice, string& restaurant_name, string& restaurant_ID, string& user_ID) {
	switch (choice)
	{
	case 0:
		displaySignOutMessage();
		break;
	case 1:
		updateMenuMOD(restaurant_name, restaurant_ID, user_ID, "item");
		break;
	case 2:
		updateMenuMOD(restaurant_name, restaurant_ID, user_ID, "price");
		break;
	case 3:
		checkStockAvailabilityMOD(restaurant_name, restaurant_ID, user_ID);
		break;
	case 4:
		checkOrderMOD(restaurant_name, restaurant_ID, user_ID, "total payment per order");
		break;
	case 5:
		checkOrderMOD(restaurant_name, restaurant_ID, user_ID, "delivery time");
		break;
	case 6:
		checkOrderMOD(restaurant_name, restaurant_ID, user_ID, "total sale");
		break;
	default:
		cout << "Opps, something wrong happen!" << endl;
		break;
	}
}

//managerInterfaceMOD will let manager to update menu, check order and stock
void managerInterfaceMOD(char& repeat, string& user_ID) {

	while ((repeat == 'Y') || (repeat == 'y')) {

		string Restaurant_name, Restaurant_ID;
		int Choice;

		fetchRestaurantDetails(Restaurant_name, Restaurant_ID, user_ID);

		displayManagerMenu(Restaurant_name, user_ID);

		pickManagerFunction(Choice);

		runManagerFunction(Choice, Restaurant_name, Restaurant_ID, user_ID);

		//0 is sign out, hence other than 0 will ask whether to check other item
		if (Choice != 0) {
			askRepeat(repeat, "check other items");
		}
		else {
			break;
		}

	}
}

//*************************************************************************************************************************
// Customer part                                       
//*************************************************************************************************************************