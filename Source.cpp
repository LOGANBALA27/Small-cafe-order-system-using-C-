/*
Developed by: (Group 11)
Muhammad Syah Firdaus Bin Shahruzzaman 		(main function, compiler)
Logan A/L Balakrishnan 						(food and drink function)
Muhammad Syahmie Fakhri Bin Ahmad Azhar	(dessert function and overall idea)
Muhammad Aizat Fahmi Bin Adbull Ropor 		(receipt function and payment & change)
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

double order(ofstream& oFile, double& food, int& q, int& l);
double order2(ofstream& oFile, double& drink, int& r, int& l);
double order3(ofstream& oFile, double& dessert, int& s, int& l);
double recipt(ofstream& oFile, double price, double payment, double change);

int main()
{
	double food = 0, drink = 0, dessert = 0;		//Declared variables
	int r, q, s, l = 1;
	double price = 0, payment = 0, change = 0;

	ofstream outputFile("Order.txt", ios::out);		//Outputfile created
	if (!outputFile)								//Validate file existence
	{
		cerr << "File could not be opened\n";
		exit(1);
	}

	cout << "Welcome to 100% Regret! :D\n";

	recipt(outputFile, price, payment, change);		//Calling receipt function line 302
	order(outputFile, food, q, l);					//Calling order (food) function line 62
	order2(outputFile, drink, r, l);				//Calling order2 (drink) function line 150
	order3(outputFile, dessert, s, l);				//Calling order3 (dessert) function line 238

	price = food + drink + dessert;					//Calculate total price

	cout << "\nTotal: RM " << price << setprecision(2) << fixed;	//Informed user the total price to pay

	pay: cout << "\n\nEnter the payment : ";		//Ask user to pay
	cin >> payment;

	if (payment >= price)
	{
		change = payment - price;
		cout << "\nYour change : RM " << change << setprecision(2) << fixed << endl;	//Calculate changes
	}
	else
	{
		cout << "Your payment is not enough. Please enter again." << endl;
		goto pay;
	}

	recipt(outputFile, price, payment, change);		//Calling receipt function line 302
}

double order(ofstream& oFile, double& food, int& q, int& l)
{
	int k;
	char a;

	string row[6][2] =
	{
		{{"Nasi Goreng Kampung\t"},
		{"Nasi Goreng Cina\t"}},
		{{"Nasi Goreng TomYam\t"},
		{"Nasi Goreng Pataya\t"}},
		{{"Nasi Ayam\t\t"},
		{"Nasi Kerabu\t\t"}},
		{{"Nasi Lemak Ayam  \t"},
		{"Burger Benjo    \t"}},
		{{"Burger Ayam\t\t"},
		{"Char Kuew Teow  \t"}},
		{{"Mee Goreng\t\t"},
		{"Maggie Goreng   \t"}}
	};												//List of food in array of 6 rows and 2 columns

	double fd[6][2] =
	{
		{1.50, 1.25}, {2.25, 2.50}, {2.25, 2.75}, {2.50, 1.00}, {1.25, 0.75}, {1.00, 0.75}
	};												//List of price for food in array of 6 rows and 2 columns

	cout << "What food would you like?\n\n";		//Ask user for their choice
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				cout << i + 1 << ". " << row[i][j] << "(RM " << fd[i][j] << setprecision(2) << fixed << ")\t";
			}
			else if (j == 1)
			{
				cout << i + 7 << ". " << row[i][j] << "(RM " << fd[i][j] << setprecision(2) << fixed << ")\n";
			}
		}
	}												//Display food and price

	do
	{
		cout << "Please enter the food code (Press 0 to skip food): ";
		cin >> k;									//User input based on food list

		if (k > 0 && k < 7)							//First column selection
		{
			k = k - 1;
			cout << "\nHow much would you like? Quantity: ";
			cin >> q;								//Quantity of selected item

			oFile << l << ".\t" << row[k][0] << q << "\t\t" << q * fd[k][0] << setprecision(2) << fixed << endl;
			food = food + q * fd[k][0];				//Update receipt
			l++;
		}
		else if (k > 6 && k < 13)					//Second column selection
		{
			k = k - 7;
			cout << "\nHow much would you like? Quantity: ";
			cin >> q;								//Quantity for selected item

			oFile << l << ".\t" << row[k][1] << q << "\t\t" << q * fd[k][1] << setprecision(2) << fixed << endl;
			food = food + q * fd[k][1];				//Update receipt
			l++;
		}
		else if (k == 0)							//Skip food
		{
			goto labelex;
		}				
		
		label: cout << "\nWould you like to order more?\n";
		cout << "y for yes, n for no\n";
		cin >> a;									//User input for repetition

	} while (a == 'y');								//Point of repetition

	if (a != 'y' && a != 'n')						//User input validation, must be y or n
	{
		cout << "Invalid character. Please try again.";
		goto label;
	}

	labelex: return food, q, l;						//Return total food price, quantity and bill
}

double order2(ofstream& oFile, double& drink, int& r, int& l)
{
	int k;
	char b;
	
	string rows[6][2] =
	{
		{{"Milo\t\t\t"},
		{"Teh Tarik\t\t"}},
		{{"Teh O   \t\t"},
		{"Kopi\t\t\t"}},
		{{"Kopi O  \t\t"},
		{"Tongkat Ali\t\t"}},
		{{"Nescafe \t\t"},
		{"Sirap Ais Bandung\t"}},
		{{"Ice Lemon Tea   \t"},
		{"Jus Anggur\t\t"}},
		{{"Jus Mangga\t\t"},
		{"Jus Tembikai    \t"}}
	};												//List of drink in array of 6 rows and 2 columns
	
	double dr[6][2] =
	{
		{1.50, 1.25}, {1.00, 1.50}, {2.00, 1.20}, {2.00, 1.00}, {1.25, 1.75}, {1.00, 1.25}
	};												//List of price for drink in array of 6 rows and 2 columns

	cout << "\nWhat drink would you like?\n\n";		//Ask user for their choice
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
			{
				cout << i + 1 << ". " << rows[i][j] << "(RM " << dr[i][j] << setprecision(2) << fixed << ")\t";
			}
			else if (j == 1)
			{
				cout << i + 7 << ". " << rows[i][j] << "(RM " << dr[i][j] << setprecision(2) << fixed << ")\n";
			}
		}
	}												//Display drink and price

	do
	{
		cout << "Please enter the drink code (Press 0 to skip drink): ";
		cin >> k;									//User input based on drink list
		
		if (k > 0 && k < 7)							//First column selection
		{
			k = k - 1;
			cout << "\nHow much would you like? Quantity: ";
			cin >> r;								//Quantity for selected item
			
			oFile << l << ".\t" << rows[k][0] << r << "\t\t" << r * dr[k][0] << setprecision(2) << fixed << endl;
			drink = drink + r * dr[k][0];			//Update receipt
			l++;
		}
		else if (k > 6 && k < 13)					//Second column selection
		{
			k = k - 7;
			cout << "\nHow much would you like? Quantity: ";
			cin >> r;								//Quantity for selected item

			oFile << l << ".\t" << rows[k][1] << r << "\t\t" << r * dr[k][1] << setprecision(2) << fixed << endl;
			drink = drink + r * dr[k][1];			//Update receipt
			l++;
		}
		else if (k == 0)							//Skip drink
		{
			goto labele;
		}

		label2: cout << "\nWould you like to order more?\n";
		cout << "y for yes, n for no\n";
		cin >> b;									//User input for repetition

	} while (b == 'y');								//Point of repetition
	
	if (b != 'y' && b != 'n')						//User input validation, must be y or n
	{
		cout << "Invalid character. Please try again.";
		goto label2;
	}

	labele: return drink, r, l;						//Return drink price, quantity and bill
}

double order3(ofstream& oFile, double& dessert, int& s, int& l)
{
	int d;
	char c;

	string row3[5][1] =
	{
		{"Sundae  \t"},
		{"Caramel Brownie "},
		{"Cheesecake      "},
		{"coconut soufflé "},
		{"Matcha cake     "},
	};												//List of dessert in array of 5 rows and 1 column
	
	double dsr[5][1] =
	{
		3.50, 3.25, 5.50, 4.50, 6.25
	};												//List of price for dessert in array of 5 rows and 1 column
	
	cout << "\nWhat dessert would you like?\n\n";	//Ask user for their choice
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			cout << i + 1 << ". " << row3[i][j] << "\t(RM " << dsr[i][j] << ")\n";
		}
	}												//Display dessert and price
	
	do
	{
		cout << "Please enter the dessert code: ";
		cin >> d;									//User input based on dessert list
		
		if (d > 0 && d < 6)							//Dessert selection
		{
			d = d - 1;
			cout << "\nHow much would you ? Quantity: ";
			cin >> s;								//Quantity for selected item
			
			oFile << l << ".\t" << row3[d][0] << "\t" << s << "\t\t" << s * dsr[d][0] << setprecision(2) << fixed << endl;
			dessert = dessert + s * dsr[d][0];		//Update file
			l++;
		}
		else if (d == 0)							//End of order
		{
			goto labelexi;
		}

		label3: cout << "\nWould you like to order more?\n";
		cout << "y for yes, n for no\n";
		cin >> c;									//User input for repetition

	} while (c == 'y');								//Point of repetition
	
	if (c != 'y' && c != 'n')						//User input validation, must be y or n
	{
		cout << "Invalid character. Please try again.";
		goto label3;
	}

	labelexi: return dessert, s, l;					//Return dessert price, quantity and bill
}

double recipt(ofstream& oFile, double price, double payment, double change)
{
	if (price == 0)									//Start of order
	{
		oFile << "\t\t  Cafe 100% Regret! :D\n";
		oFile << "*********************************************************\n";
		oFile << "\t\t     Order Summary\n";
		oFile << "*********************************************************\n\n";
		oFile << "Bil\tItem(s)\t\t\tQuantity\tPrice(RM)\n";
	}


	if (price > 0)									//End of order
	{
		oFile << "\n\t\t\tTotal Price  :\tRM\t" << price << setprecision(2) << fixed;
		oFile << "\n\t\t\tTotal Payment:\tRM\t" << payment << setprecision(2) << fixed;
		oFile << "\n\t\t\tTotal Change :\tRM\t" << change << setprecision(2) << fixed;
		oFile << "\nThank you for your order.";
		oFile << "\nSincerely from us";
		oFile << "\nCafe 100% Regret! :D";
	}

	return 0;
}

