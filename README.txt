# Food Ordering System

Food Ordering System is a C++ program to allow customer to order food delivery and manager to manage
their online restaurant

## Getting Started

Make sure you have at least these text files in the same folder:

credentials.txt, restaurant.txt, 0x1_menu, 0x1_order, 0x1_stock, 0x2_menu,
0x2_order, 0x2_stock, 0x3_menu, 0x3_order, 0x3_stock, 0x4_menu, 0x4_order, 0x4_stock

Important on files:

*Ensure the '|' end after the last character of the content(e.g. "item 50|")
and not the new line for the file that contain contents
This is to make sure the file updating runs well with the program

*The files's content are based after the screenshots of input and output in the documentation

## Using the program

Sign in:

Refer to the credentials.txt file to get user id and passwords(omit the "0xCD" part).
['m' indicates a manager account, 'c' indicates a customer account]

Example for customer account:
User ID  : jackie 
Password : jackson8989

Example for manager account:
User ID  : liew 
Password : liew5656

Sign up:

You can create whatever user id and password for either customer or manager account.

Customer account:

You can only order food and make payment

Manager account:

You can create online restaurant and food menu if you sign up as restaurant
After signing in, you can change menu item, price and check stock availability, total payment per order,
delivery time, total sale  