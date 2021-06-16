#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>

using namespace std;

const int MAX_TAG = 50;

struct userRecord
{
	int accountNumber;
	double balanceAmount;
	string userName;
	string accountType;
	int userPin;
};

void ShowUserInterface();

int main()
{
	userRecord main[MAX_TAG];

	ifstream userData;

	int tag = 0;
	int userOption = 0;
	int pinInput = 0;
	int accNumberInput = 0;

	double depositAmount;
	double withdrawalAmount;

	//Open the input file
	userData.open("UserDatabase.txt");

	//Primer
	//Read in the user's name
	getline(userData, main[tag].userName);

	while (userData.peek() != EOF && tag < MAX_TAG)
	{
		//Read in the user's data
		userData >> main[tag].userPin;
		userData >> main[tag].accountNumber;

		//Clear the input
		userData.clear();
		userData.ignore(100, '\n');

		getline(userData, main[tag].accountType);

		userData >> main[tag].balanceAmount;

		//Clear the input
		userData.clear();
		userData.ignore(100, '\n');

		//Increment the tag field
		tag++;

		//Changer
		getline(userData, main[tag].userName);
	}

	//Set the output of floating point values to 2 decimal values
	cout << fixed << setprecision(2);

	//Prompt the user to enter their PIN
	cout << "Enter Your Account Number: ";
	cin >> accNumberInput;

	for (int index = 0; index < MAX_TAG; index++)
	{
		if (accNumberInput == main[index].accountNumber)
		{
			cout << "Enter Your PIN: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> pinInput;

			for (int i = 0; i < MAX_TAG; i++)
			{
				if (pinInput == main[i].userPin)
				{
					cout << "Welcome \n" << main[i].userName << endl;

					do {

						//Outputs the banking system user interface
						ShowUserInterface();
						cout << "Option: ";
						cin.clear();
						cin.ignore(100, '\n');
						cin >> userOption;

						switch (userOption)
						{
						case 1:
							cout << "Your Balance is: $" << main[i].balanceAmount << endl;
							break;

						case 2:
							cout << "Enter the amount you wish to deposit: ";
							cin.clear();
							cin.ignore(100, '\n');
							cin >> depositAmount;

							if (cin >> depositAmount)
							{
								main[i].balanceAmount += depositAmount;

								cout << "Transaction Successfully Completed" << endl;
							}
							
							else
							{
								cout << "Transaction Unsuccessful" << endl;
							}
							break;

						case 3:
							cout << "Enter the amount you wish to withdraw: ";
							cin.clear();
							cin.ignore(100, '\n');
							cin >> withdrawalAmount;

							if (withdrawalAmount <= main[i].balanceAmount && cin >> withdrawalAmount)
							{
								main[i].balanceAmount -= withdrawalAmount;

								cout << "Transaction Successfully Completed" << endl;
							}

							else
							{
								cout << "Transaction Unsuccessful" << endl;
							}
							break;
						}

					} while (userOption != 4);

					if (userOption == 4)
					{
						exit(1);
					}
				}

				

				else if (i == MAX_TAG -1 && pinInput != main[i].userPin && userOption != 4)
				{
					cout << "Incorrect PIN \nPlease Try Again or Press 4 to Exit" << endl;
					cin.clear();
					cin.ignore(100, '\n');
					cin >> pinInput;

					i = -1;

					if (pinInput == 4)
					{
						exit(1);
					}
				}
			}
		}

		else if (index == MAX_TAG - 1 && accNumberInput != main[index].accountNumber)
		{
			cout << "Account Could Not Be Found \nRe-Enter Your Account Number or Press 4 to Exit: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> accNumberInput;

			index = -1;

			if (accNumberInput == 4)
			{
				exit(1);
			}
		}
	}

	userData.close();

	return 0;
}

void ShowUserInterface()
//////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: UserInterface
// Inputs:  None
// Outputs: 
// Description: Outputs the banking system user interface
//////////////////////////////////////////////////////////////////////////////////////////////////
{
	//Output the banking system user interface
	cout << setfill('*') << setw(10) << '*' << "Select A Transaction" << setw(10) << '*' 
		 << endl;
	cout << "1. Check Balance" << endl;
	cout << "2. Deposit" << endl;
	cout << "3. Withdraw" << endl;
	cout << "4. Exit" << endl;
	cout << setw(47) << '*' << setfill(' ') << endl;
}

