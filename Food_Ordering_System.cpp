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
		MAX_ROW = 2,
		MAX_CREDS = 50,
		MAX_RESTAURANT = 20,
		MAX_ITEM = 10,
		MINUTES_PER_HOUR = 60,
		AVERAGE_PREP_TIME = 15,
		INITIAL_STOCK = 50;
const float AVERAGE_KM_PER_HOUR = 60,
			RATE_PER_KM = 0.50;
const string PASS_FLAG = "0xCD",
			 BASE_ID = "0x";

// All functions prototype, proper explanation is below main function, xxxMOD means the function is module-like, which consists of multiple functions
void removeNewLine(string&);
void clearInputBuffer();
void validateRepeat(char&);
void askRepeat(char&, string);
void displaySignOutMessage();
void openRestaurantFile(fstream&, string&, char);
void displayFoodMenu(string, float);
void validatePickMenu(int&);
void validatePrice(float&);
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
int pickMenuItem(string);
void updateMenuMOD(string&, string&, string&, string);
void checkStockAvailabilityMOD(string&, string&, string&);
void checkOrderMOD(string&, string&, string&, string);
void runManagerFunction(int&, string&, string&, string&);
void managerInterfaceMOD(char&, string&);
void displayCustomerInterface(string&);
void displayCustomerMenu(string&);
void validateCustomerPick(int&);
void pickCustomerFunction(int&);
void displayRestaurantList(string[][MAX_COLUMN], int&, string&);
void validateRestaurantPick(int&, int&);
void pickRestaurant(int&, int&);
void fetchMenuAndStock(string, string, float, int);
void validateOrderAvailability(float&, int&, int[]);
void getOrderItem(int&);
void getOrderQuantity(int&, float[][MAX_ITEM], int[]);
void calculateAndUpdateOrderPrice(int&, float[][MAX_ITEM], float[]);
float calculateTotalAmount(float[][MAX_ITEM]);
void displayCurrentOrder(float[][MAX_ITEM], string[], float);
void getAndTrackOrderMOD(int&, float&, float[][MAX_ITEM], string[], float[], int[]);
void validateDeliveryDistance(float&);
void getDeliveryDistance(float&, string&);
int calculateDeliveryTime(float&);
float calculateDeliveryFee(float&);
void updateOrderAndStockFile(string&, string&, float&, int&, float[][MAX_ITEM], string[], int[]);
void displayBill(string&, string&, string&, float[][MAX_ITEM], string[], float&, float&, float&, int&);
void validateMakePayment(int&);
void makePayment();
void orderFoodMOD(string&);
void runCustomerFunction(int&, string&);
void customerInterfaceMOD(char&, string&);


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

//removeNewLine will remove '\n' in the string
void removeNewLine(string& word) {

	if (word[0] == '\n') {
		word = string(word.begin() + 1, word.end());
	}
}

//clearInputBuffer will remove all the unwanted input buffer first before next input(especially for 'cin' type input)
void clearInputBuffer() {
	/*Overall purpose is to remove all unwanted input after accidentally type space' '
	test case:
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
		cout << right << setw(2) << i + 1 << ". " << left << setw(60) << item[i] << "| " << fixed << setprecision(2) << price[i] << " |" << endl;
	}
}

//validatePickMenu will validate during pickMenuItem and getOrderItem Function
void validatePickMenu(int& choice) {
	while (choice < 1 || choice > 10) {
		cout << "\nInvalid item! Pick again.(From 1 to 10 only)\n"
			<< "Item number: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//validatePrice will validate during getItemAndPrice and UpdateMenuMOD
void validatePrice(float& price) {
	while (price < 0) {
		cout << "\nOnly positive price is allowed. Please enter price again: ";
		cin >> price;
		clearInputBuffer();
	}
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
	while (user_type != 'm' && user_type != 'c') {
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
	validatePrice(price);
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
				File_stock << Item << "\t" << INITIAL_STOCK;
			}
			else {
				File_menu << Item << "\t" << fixed << setprecision(2) << Price << "\n";
				File_stock << Item << "\t" << INITIAL_STOCK << "\n";
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

			removeNewLine(restaurant[Array_size][0]);

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

			removeNewLine(name);

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

			removeNewLine(Item[i]);

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
			validatePrice(Price[Item_changed]);
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
			File_stock << Item[j] << "\t" << INITIAL_STOCK;
		}
		else {
			File_menu << Item[j] << "\t" << fixed << setprecision(2) << Price[j] << "\n";
			File_stock << Item[j] << "\t" << INITIAL_STOCK << "\n";
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

			removeNewLine(Item);

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

			removeNewLine(Order_ID);

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

//displayRestaurantList will get the restaurant details from file, save to array and display the names
void displayRestaurantList(string restaurant[][MAX_COLUMN], int& count, string& user_ID) {

	//fetch the restaurant data from files
	ifstream File_restaurant;
	File_restaurant.open("restaurant.txt");

	if (File_restaurant.is_open()) {
		while (!File_restaurant.eof() && (count < MAX_RESTAURANT)) {

			//store the restaurant name
			getline(File_restaurant, restaurant[count][0], '\t');

			removeNewLine(restaurant[count][0]);

			//store the restaurant ID
			File_restaurant >> restaurant[count][1];

			//store the related manager user_ID
			File_restaurant >> restaurant[count][2];

			//count the number of restaurant available
			++count;
		}
	}
	else {
		cout << "The restaurant.txt file does not exist" << endl;
	}

	File_restaurant.close();

	//output the restaurant list
	displayCustomerInterface(user_ID);
	cout << "\t\t\t-----------------------------------\n"
		<< "\t\t\t|      Restaurant Available       |\n"
		<< "\t\t\t-----------------------------------\n" << endl;
	for (int i = 0; i < count; ++i) {
		cout << i + 1 << ". " << restaurant[i][0] << endl;
	}


}

//validateRestaurantPick will validate during pickRestaurant Function
void validateRestaurantPick(int& choice, int& number) {
	while (choice < 1 || choice > number) {
		cout << "Invalid item! Pick again.(From 1 to " << to_string(number) << " only)\n"
			<< "Item number: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//pickRestaurant will request input for picking the restaurant to order
void pickRestaurant(int& choice, int& number) {
	cout << "\nWhich restaurant do you want to order from?\n"
		<< "Restaurant no: ";
	cin >> choice;
	clearInputBuffer();
	validateRestaurantPick(choice, number);

}

//fetch necessary menu and stock data from specific restaurant into array
void fetchMenuAndStock(string ID, string item[], float price[], int stock[]) {

	fstream File_menu, File_stock;
	openRestaurantFile(File_menu, ID, 'm');
	openRestaurantFile(File_stock, ID, 's');

	//fetch menu item and price and store into array
	if (File_menu.is_open()) {
		for (int i = 0; i < MAX_ITEM; ++i) {

			//store the menu item
			getline(File_menu, item[i], '\t');

			removeNewLine(item[i]);

			//store the item price
			File_menu >> price[i];
		}
	}
	else {
		cout << "The " << ID << "_menu.txt file does not exist" << endl;
	}


	//fetch stock item and quantity and store into array
	if (File_stock.is_open()) {
		for (int i = 0; i < MAX_ITEM; ++i) {

			//store the stock item
			getline(File_stock, item[i], '\t');

			removeNewLine(item[i]);

			//store the stock availability
			File_stock >> stock[i];
		}
	}
	else {
		cout << "The " << ID << "_stock.txt file does not exist" << endl;
	}

	File_menu.close();
	File_stock.close();
}

//validateOrderAvailability will validate the order quantity during getOrderQuantity
void validateOrderAvailability(float& quantity, int& choice, int stock[]) {
	while (quantity < 0 || quantity > stock[choice - 1]) {
		cout << "\nOpps, either value is less than zero or the order is unable to fullfill due to limited availability\n"
			<< "\nPlease order less than " << stock[choice - 1] << "!" << endl;
		cin >> quantity;
		clearInputBuffer();
	}
}

//getOrderItem will request input for picking order item
void getOrderItem(int& choice) {
	cout << "\nWhich menu item do you want to order?\n"
		<< "Item number: ";
	cin >> choice;
	clearInputBuffer();
	validatePickMenu(choice);
}

//getOrderQuantity will request input for order quantity and save it into array
void getOrderQuantity(int& choice, float order[][MAX_ITEM], int stock[]) {
	cout << "How many do you want to order?\n";
	cin >> order[0][choice - 1];
	validateOrderAvailability(order[0][choice - 1], choice, stock);
}

//calculateAndUpdateOrderPrice will calculate the total amount for specific item
void calculateAndUpdateOrderPrice(int& choice, float order[][MAX_ITEM], float price[]) {

	//total amount = quantity * price per item
	order[1][choice - 1] = order[0][choice - 1] * price[choice - 1];
}

//calculatetotalAmount will calculate the total amount of order for all order item
float calculateTotalAmount(float order[][MAX_ITEM]) {
	float Total = 0;

	for (int i = 0; i < MAX_ITEM; ++i) {

		//overall sum += total amount for the specific item only if it containt >0 quantity
		if (order[0][i] > 0) {
			Total += order[1][i];
		}

	}

	return Total;
}

//displayCurrentOrder will display the list of order item, quantity and total amount for the item
void displayCurrentOrder(float order[][MAX_ITEM], string item[], float total_amount) {
	cout << "\nYour current order:\n";
	for (int i = 0; i < MAX_ITEM; ++i) {

		//only print out the specific item when customer order it
		if (order[0][i] > 0) {
			cout << left << setw(50) << item[i] << setw(3) << "-" << order[0][i] << " -  RM" << fixed << setprecision(2) << order[1][i] << endl;
		}
	}
	cout << endl;
	cout << right << setw(60) << "Total order amount: RM" << fixed << setprecision(2) << total_amount << endl;
}

//getAndTrackOrder will get order and update order repeatedly until user finish order food
void getAndTrackOrderMOD(int& choice, float& total_amount, float order[][MAX_ITEM], string item[], float price[], int stock[]) {

	char Repeat = 'y';

	while (Repeat == 'y' || Repeat == 'Y') {

		getOrderItem(choice);

		getOrderQuantity(choice, order, stock);

		calculateAndUpdateOrderPrice(choice, order, price);

		total_amount = calculateTotalAmount(order);

		displayCurrentOrder(order, item, total_amount);

		askRepeat(Repeat, "add other item");
	}
}

//validateDeliveryDistance will validate the distance during getDeliveryDistance
void validateDeliveryDistance(float& distance) {
	while (distance < 0 || distance>20) {
		cout << "\nSorry, your distance is not available for the food delivery.\n"
			<< "Distance for delivery(km): ";
		cin >> distance;
		clearInputBuffer();
	}
}

//getDeliveryDistance will request input for the delivery distance
void getDeliveryDistance(float& distance, string& user_ID) {
	displayCustomerInterface(user_ID);
	cout << "\nThe restaurant is in the city\n"
		<< "How far are you away from the restaurant?\n"
		<< "[Disclaimer: We accept maximum distance of 20km only]\n\n"
		<< "Distance for delivery(km): ";
	cin >> distance;
	clearInputBuffer();
	validateDeliveryDistance(distance);
}

//calculateDeliveryTime will calculate the delivery time based on distance and prep time
int calculateDeliveryTime(float& distance) {

	return (int)(distance / AVERAGE_KM_PER_HOUR * MINUTES_PER_HOUR) + AVERAGE_PREP_TIME;
}

//calculateDeliveryFee will calculate the delivery fee based on distance times fixed rate
float calculateDeliveryFee(float& distance) {
	return distance * RATE_PER_KM;
}

//updateOrderAndStockFile will update all order details to file
void updateOrderAndStockFile(string& order_ID, string& restaurant_ID, float& total, int& time, float order[][MAX_ITEM], string item[], int stock[]) {

	int Count_order = 0;
	string Order_ID[MAX_CREDS] = {};
	float Order_details[MAX_ROW][MAX_CREDS] = {};
	//first row is for grand total, second row is for total time

	fstream File_order, File_stock;
	openRestaurantFile(File_order, restaurant_ID, 'o');
	openRestaurantFile(File_stock, restaurant_ID, 's');

	//fetch all order into array first
	if (File_order.is_open()) {
		while (!File_order.eof() && Count_order < MAX_CREDS) {

			//store order id
			File_order >> Order_ID[Count_order];

			removeNewLine(Order_ID[Count_order]);
			
			//store total amount
			File_order >> Order_details[0][Count_order];

			//store delivery time
			File_order >> Order_details[1][Count_order];

			++Count_order;
		}
	}
	else {
		cout << "The " << restaurant_ID << "_order.txt file does not exist" << endl;
	}
	File_order.close();

	//for new file, it will automatically Count_order = 1, this line is to avoid outputing empty line later
	if (Count_order == 1 && Order_ID[0] < " ") {
		Count_order = 0;
	}

	//add the new order to the array first
	Order_ID[Count_order] = order_ID;
	Order_details[0][Count_order] = total;
	Order_details[1][Count_order] = time;

	//open the file again for rewriting order.txt
	openRestaurantFile(File_order, restaurant_ID, 'o');
	for (int i = 0; i <= Count_order; ++i) {

		//this format is for the total amount while inner one is for time
		cout << fixed << setprecision(2);
		if (i == Count_order) {
			File_order << Order_ID[i] << "\t" << Order_details[0][i] << "\t" << Order_details[1][i];
		}
		else {
			File_order << Order_ID[i] << "\t" << Order_details[0][i] << "\t" << Order_details[1][i] << endl;
		}

	}
	File_order.close();

	//update the stock array first, the reason I do at last, because need to comfirm user really gonna order stuff
	for (int i = 0; i < MAX_ITEM; ++i) {

		//if the user have specific number for order for the item then only update the stock array
		if (order[0][i] > 0) {
			stock[i] -= order[0][i];
		}
	}

	//start rewriting stock.txt file
	for (int i = 0; i < MAX_ITEM; ++i) {

		if (i == (MAX_ITEM - 1)) {
			File_stock << item[i] << "\t" << stock[i];
		}
		else {
			File_stock << item[i] << "\t" << stock[i] << endl;
		}

	}
	File_stock.close();
}

//displayBill will display bill to the customer with their respective order id, list of orders, and delivery related details
void displayBill(string& user_ID, string& restaurant_name, string& order_ID, float order[][MAX_ITEM], string item[], float& total, float& delivery_fee, float& grand_total, int& time) {

	displayCustomerInterface(user_ID);

	//header for the bill
	cout << "\n-----------------------------------------------------------------------------------\n"
		<< "                       Food Order from " << restaurant_name << "\n\n"
		<< "Order ID: " << order_ID << endl;

	//show every item customer order
	displayCurrentOrder(order, item, total);

	//lower half of the bill
	cout << fixed << setprecision(2);
	cout << right << setw(60) << "Delivery fee: RM" << delivery_fee << "\n"
		<< right << setw(60) << "Grand Total Billable: RM" << grand_total << "\n"
		<< "-----------------------------------------------------------------------------------\n"
		<< "                     THANK YOU FOR ORDERING! Your order  \n"
		<< "                  will be delivered in the next " << time << " minutes" << endl;

}

//validateMakePayment will validate the choice during makePayment
void validateMakePayment(int& choice) {
	while (choice != 1 && choice != 2) {
		cout << "\nInvalid payment method. Pick 1 or 2 only\n"
			<< "Your payment method: ";
		cin >> choice;
		clearInputBuffer();
	}
}

//makePayment will request input from user to determine the method of payment
void makePayment() {
	int Choice;

	cout << "\nHow do you want to make payment?\n"
		<< "1. Cash On Delivery\n"
		<< "2. Online Banking\n"
		<< "\nYour payment method: ";
	cin >> Choice;
	clearInputBuffer;
	validateMakePayment(Choice);

	if (Choice == 1) {
		cout << "\nNice. You will pay via cash on delivery when the food delivery reach your place. Enjoy your food later! XD" << endl;
	}
	else if (Choice == 2) {
		cout << "\nNice. You already paid via online banking. Enjoy your food later! XD" << endl;
	}
	else {
		cout << "\nOpps, something went wrong!" << endl;
	}
}

//orderFoodMOD will allow customer to see the restaurant and menu list, order food, and update all data to the respective files
void orderFoodMOD(string& user_ID) {

	//reason for static is because you can keep counting the order if the program didn't close
	static int s_Count_order = 1000;

	int No_restaurant = 0,
		Choice = 0,
		Delivery_time = 0;
	float Total_order_amount = 0,
		Grand_total_bill = 0,
		Delivery_distance = 0,
		Delivery_fee = 0;
	string Selected_restaurant_name, Selected_restaurant_ID, Order_ID;

	string Restaurant[MAX_RESTAURANT][MAX_COLUMN] = {},
		Item[MAX_ITEM] = {};
	int Stock[MAX_ITEM] = {};
	float Price[MAX_ITEM] = {},
		OrderQuantityandPrice[MAX_ROW][MAX_ITEM] = {};
	//for Order array first line is for order quantity, second line is for total amount for the item

	displayRestaurantList(Restaurant, No_restaurant, user_ID);

	pickRestaurant(Choice, No_restaurant);

	//store the choosen restaurant name and id from array to a variable first, later easier to know
	Selected_restaurant_name = Restaurant[Choice - 1][0];
	Selected_restaurant_ID = Restaurant[Choice - 1][1];

	//fetch necessary menu and stock data from specific restaurant into array
	fetchMenuAndStock(Selected_restaurant_ID, Item, Price, Stock);

	//show the menu from the restaurant
	displayCustomerInterface(user_ID);
	cout << "\nThis is menu from the restaurant called " << Selected_restaurant_name << endl;
	displayFoodMenu(Item, Price);

	getAndTrackOrderMOD(Choice, Total_order_amount, OrderQuantityandPrice, Item, Price, Stock);

	getDeliveryDistance(Delivery_distance, user_ID);

	//update delivery time and delivery fee
	Delivery_time = calculateDeliveryTime(Delivery_distance);
	Delivery_fee = calculateDeliveryFee(Delivery_distance);

	//calculate the grand total of the bill
	Grand_total_bill = Total_order_amount + Delivery_fee;

	//create order_ID, it is here because we only need when the user successfully order 
	++s_Count_order;
	Order_ID = user_ID + to_string(s_Count_order);

	//update all order details to file
	updateOrderAndStockFile(Order_ID, Selected_restaurant_ID, Grand_total_bill, Delivery_time, OrderQuantityandPrice, Item, Stock);

	displayBill(user_ID, Selected_restaurant_name, Order_ID, OrderQuantityandPrice, Item, Total_order_amount, Delivery_fee, Grand_total_bill, Delivery_time);

	makePayment();

	system("pause");
}

//runCustomerFunction will run the function picked by the customer
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