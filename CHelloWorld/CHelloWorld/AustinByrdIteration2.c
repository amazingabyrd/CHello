/*
Austin Byrd
Iteration 1 Full Program

Program is used for setup of Organizations planning Bike Race Fundraisers
and Riders to registration for the race
Program is modular and maintainable
*/

//preprocessor directives libraries 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

//Preprocessor Constants
//password for ADMIN
#define PASSWORD "1"
//size of strings arrays
#define SIZE 80
#define ORGSIZE 1
#define NUMORG 1
#define NUMRID 10
//max and min values
#define DISTANCEMAX 200
#define DISTANCEMIN 1
#define PERCENTMAX 30
#define PERCENTMIN 5
#define JERSEYCOSTMAX 150
#define JERSEYCOSTMIN 50
#define RACECOSTMAX 250
#define RACECOSTMIN 50

//global const array for Jersey Sizes
#define JERSEYS 4
#define YN 2
const char* SIZES[JERSEYS] = { "(s)mall", "(m)edium", "(l)arge", "(x)tra-large" };
const char* CHOICE[YN] = { "(y)es", "(n)o" };

//structs maybe 
typedef struct ORGANIZATIONS{
	//race info
	char organizationName[SIZE];
	double raceDistance;
	double raceCost;
	double jerseyCost;
	double charityPercentage;
	//race data
	int shirtsSold;
	int registrants;
	struct ORGANIZATIONS* orgPtr;
}ORGANIZATIONS;

typedef struct RIDERS{
	ORGANIZATIONS* raceChoice;
	char riderName[SIZE];
	char jersey;
	bool choice;
	char payment[SIZE];
	struct RIDERS* ridPtr;
}RIDERS;

//Function Prototypes
void   adminSetup(ORGANIZATIONS** orgHead);
int    riderSetup(ORGANIZATIONS** const o, RIDERS** r);
void   payVerify(RIDERS* const r);
void   jerseySize(RIDERS* const r);
//print
void   adminData(ORGANIZATIONS* orgs);
void   adminDataDisplay(ORGANIZATIONS* orgss);
void   receipt(const ORGANIZATIONS* const o, const RIDERS* const r);
void   adminReceipt(const ORGANIZATIONS* const o, const RIDERS* const r);
//dont change
void   fgetsRemoveNewLine(char* const str);
double getValidDouble(char* const str, const int min, const int max);
int    quit();
int    verifyPass();
char   charCheck(const char* arr[], int size);
//new
ORGANIZATIONS* orgChoice(ORGANIZATIONS** orgHead);
void oinsertNode(ORGANIZATIONS** headPtr, ORGANIZATIONS* oInsert);
void rinsertNode(RIDERS** headPtr, RIDERS* rInsert);
void fileWrite(const ORGANIZATIONS* oheadPtr);
void closeAll(ORGANIZATIONS* oheadPtr, RIDERS* rheadPtr);


int main()
{
	//Structure Instance
	ORGANIZATIONS* orghPtr = NULL;
	RIDERS* ridhPtr = NULL;

	puts("ADMIN MODE");
	//Goes to verifyPass function to get verify ADMIN 
	int verifyPassword = verifyPass();
	//after adminVerification Get admin data and display it for the admin
	if (verifyPassword == 1)
	{
		printf("%s", "\nSet up the fundraising information for the organizations\n");
		//ADMIN MODE
		//admin setup and data display
		//add yes or no loop to insertNode or not
		adminSetup(&orghPtr);

		//RIDER setup MODE
		//Tell rider RACES available Setup Riders until users are finished
		puts("\n\n\nRIDER MODE");
		riderSetup(&orghPtr, &ridhPtr);

		closeAll(orghPtr, ridhPtr);
		//adminReceipt(Organization, r);
	}
}//end of main

//collect data from Organization Admin
void adminSetup(ORGANIZATIONS** orgHead)
{
	//initialize variables for choice errors and the new node
	char choice= ' ';
	do
	{
		ORGANIZATIONS* newOrganization = *orgHead;
		//decide for another organization in the list
		printf("%s", "\nAnother organization? (y/n): ");
		choice = getchar();
		while (getchar() != '\n');

		if (choice == 'y')
		{
			oinsertNode(orgHead, newOrganization);
		}
		if (choice != 'n' || choice != 'y')
		{
			printf("%s", "Error: enter y or n:");
		}
		
	} while (choice != 'n');
}//end of adminSetup

int  riderSetup(ORGANIZATIONS** const o, RIDERS** r)
{
	int choice = 0;
	int error = 0;
	do
	{
		//make new rider
		RIDERS tempRider;

		if (error > 1)
		{
			printf("%s", "Error enter y or n");
		}
		//riders name
		char name[SIZE] = { " " };
		//display race options
		adminDataDisplay(*o);

		//have them enter riders name or quit
		printf("%s", "\nEnter your Full Name or 'quit' to exit : ");
		fgetsRemoveNewLine(name);

		//check if they entered quit
		size_t strsize = strlen(name);
		for (int i = 0; i < strsize; i++)
		{
			name[i] = tolower(name[i]);
		}
		//whats entered was quit
		int strcompare;
		strcompare = strcmp(name, "quit");
		if (strcompare == 0)
		{
			int q = 0;
			q = quit();
			if (q == 0)
			{
				return 0;
			}
			if (q == 1)
			{
				printf("%s", "ERROR INVAlID PASSWORD\n");
				riderSetup(o, r);
			}
		}
		//if they didnt enter quit save their name
		strcpy(tempRider.riderName, name);
		char rec;

		//riders organization choice
		ORGANIZATIONS* ochoice;
		ochoice = orgChoice(o);

		tempRider.raceChoice = ochoice;

		printf("Would you like a jersey?: (y/n) ");
		rec = charCheck(CHOICE, YN);
		if (rec == 'y')
		{
			tempRider.choice = 1;
			tempRider.raceChoice->shirtsSold += 1;
			jerseySize(*r);
		}

		//calculate cost for Racer
		double totalCost = 0;
		if (tempRider.choice == true)
		{
			totalCost = tempRider.raceChoice->raceCost + tempRider.raceChoice->jerseyCost;
		}
		else
			totalCost = tempRider.raceChoice->raceCost;

		//prompt for credit card
		printf("%s%.02lf%s", "Your total cost is ", totalCost, ".\nEnter your credit card: ");
		//goes to pay verify and gets credit card number as string and saves it to rider struct
		payVerify(&tempRider);
		printf("%s%s%s%.02lf%s", "Thank you ", tempRider.riderName, " for your purchase. $", totalCost * (tempRider.raceChoice->charityPercentage * .01), " of the ticket sales will go to charity.\n");


		//prompt for receipt
		printf("%s", "Would you like your receipt? (y/n): ");
		rec = charCheck(CHOICE, YN);
		if (rec == 'y')
		{
			receipt(tempRider.raceChoice, &tempRider);
		}
	}while (choice != 'n');

	return 1;
}//end of riderSetup

void jerseySize(RIDERS* const r)
{
	printf("%s", "Select your Shirt size by entering the character in parenthesis: ");
	for (int i = 0; i < JERSEYS; i++)
	{
		printf(" %s", SIZES[i]);
	}

	char size;
	size = charCheck(SIZES, JERSEYS);
	size = tolower(size);
	printf("%s%c\n\n", "Jersey Size Choice: ", size);
	r->jersey = size;
}


void payVerify(RIDERS* r)
{
	//prompt for payment and setup to process input
	printf("%s", "\nEnter payment in form \"XXXX-####-##### (X as Letters # as numbers) Ex. FVMS-4832-93367\"");
	char payment[SIZE];
	char tempPayment[SIZE];
	int error = 0;
	int check = 0;
	do
	{
		if (error > 0)
		{
			printf("%s", "ERROR: Enter in \"XXXX - #### - ##### (X as Letters # as numbers) Ex.FVMS - 4832 - 93367\" form: \n");
		}
		//collect input and format
		fgetsRemoveNewLine(payment);
		strcpy(tempPayment, payment);

		//check validity
		if (strlen(tempPayment) == 15)
		{
			char* token = strtok(tempPayment, "-");
			for (int i = 0; i < strlen(token); i++)
			{
				token[i] = tolower(token[i]);
				if (isalpha(token[i]))
				{
					check++;
				}
			}
			token = strtok(NULL, "-");
			for (int i = 0; i < strlen(token); i++)
			{
				if (isdigit(token[i]))
				{
					check++;
				}
			}
			token = strtok(NULL, "-");
			for (int i = 0; i < strlen(token); i++)
			{
				if (isdigit(token[i]))
				{
					check++;
				}
			}
		}

		//check what was saved
		error++;
	} while (check != 13);

	strcpy(r->payment, payment);

}//end of Payment Verification







//Diplay Race Data for Organizations
void adminData(ORGANIZATIONS* orgs)
{
	puts("Organizations in order: \n");
	ORGANIZATIONS* currentPtr = orgs;
	while(currentPtr != NULL)
	{
		//print Data
		printf(" %s", "\nOrganization Data:");
		printf(" %s%s", "Organization Name : ", currentPtr->organizationName);
		printf(" %s%.2lf%s", "Race Distance: ", currentPtr->raceDistance, " miles");
		printf(" %s%.2lf", "Race Cost: $", currentPtr->raceCost);
		printf(" %s%.2lf", "Jesey Cost: $", currentPtr->jerseyCost);
		printf(" %s%.2lf%s", "Percent for Charity: ", currentPtr->charityPercentage, "%");
		currentPtr = currentPtr->orgPtr;
	}

}//end of adminData Function

//Display Race Organization Data for RIDERS
void adminDataDisplay(ORGANIZATIONS* orgss)
{
	ORGANIZATIONS* currentPtr = orgss;
	printf("%s", "You can register for one of the following races");
	while(currentPtr != NULL)
	{
		//After Admin Setup is completed display the info of the organization structure
		printf("\n\n%.02lf%s%s%s%d%s%.02lf%s%.02lf%s%.02lf", orgss->charityPercentage,
			"% will be raised for ", orgss->organizationName, ".\nRide\tDistance\tCost\n#", 1, "\t", orgss->raceDistance,
			" miles\t$", orgss->raceCost, "\nYou can purchase a jersey for $ ", orgss->jerseyCost);
		currentPtr = currentPtr->orgPtr;
	}

}//end of adminDataDisplay


//Exit Summary Display
void   adminReceipt(const ORGANIZATIONS* const o, const RIDERS* const r)
{
	double sum = (o->registrants * o->raceCost);
	double total = sum + (o->shirtsSold * o->jerseyCost);
	double ctotal = (total * (o->charityPercentage * .01));
	printf("\n%s%.02lf%s", "Summary of race sales where ", o->charityPercentage, "% goes to charity \n");
	printf("%s", "Race\tDistance\tPrice\tRegistrants\tTotal Sales\t Charity Amount\n");
	printf("#%d\t%0.02lf miles\t$%.02lf\t\t$%d\t$%.02lf\t\t$%.02lf", 1, o->raceDistance, o->raceCost, o->registrants, o->registrants * o->raceCost, sum * (o->charityPercentage * .01));
	printf("\n\nShirts Sold\tSales\tCharity\n");
	printf("%d\t\t$%.02lf\t$%.02lf", o->shirtsSold, o->jerseyCost * o->shirtsSold, (o->jerseyCost * o->shirtsSold) * (o->charityPercentage * .01));
	printf("\n\n%s%.02lf", "TotalSales:\t", total);
	printf("\n%s%.02lf", "Total Funds Raised for Charity:\t", ctotal);
}//end of adminReceipt

char charCheck(const char* arr[], int size)
{
	char entered;
	int loop = 0;
	do
	{
		if (loop > 0)
		{
			printf("%s", "Error: enter a valid choice \n");
		}
		printf("%s", "Enter Choice: ");
		entered = getchar();
		while (getchar() != '\n');
		entered = tolower(entered);
		for (int i = 0; i <= size; i++)
		{
			if (entered == arr[i][1])
			{
				return entered;
			}
		}
		loop++;
	} while (true);
}

//rider receipt
void   receipt(const ORGANIZATIONS* const o, const RIDERS* const r)
{
	double totalc = ((o[0].raceCost + o[0].jerseyCost) * (o[0].charityPercentage * .01));
	printf("%s%.02lf%s%.02lf%s%.02lf%s%.02lf", "\n\t\tRider Receipt\nRace\t$", o->raceCost, "\nJersey\t$",
		o->jerseyCost, "\n\nTotal Cost: $", o->raceCost + o->jerseyCost, "\nDonation to Charity: $",
		totalc);
}//end of receipt


int quit()
{
	int pass = verifyPass();
	if (pass == 1)
	{
		return 0;
	}
	else
		return 1;
}//end of quit

//Checks Admin Password is correct. Gives 3 tries then exits program
int verifyPass()
{
	char passwordEntered[SIZE] = { "0" };
	//3 tries to enter password
	int counter = 0;
	int comparison = -1;
	do {
		printf("%s", "Enter Admin Password: ");
		fgetsRemoveNewLine(passwordEntered);
		comparison = strcmp(passwordEntered, PASSWORD);
		if (comparison == 0)
		{
			return 1;
		}
		else
		{
			printf("%s", "\t\aINVALID PASSWORD\n");
		}
		counter++;
	} while (counter < 3);
	return 0;

}//end of verifyPassword

//Reused: Ensures entered data is a double and in range and returns it
double getValidDouble(char* const str, const int min, const int max)
{
	errno = 0;
	int valid = 0;
	double x = 0;
	do
	{
		fgetsRemoveNewLine(str);
		char* end;
		x = strtod(str, &end);
		//if it is not a Decimal Number, Size Double, string has null at the end and not characters, and it is in range
		if (end == str || x < DBL_MIN || x > DBL_MAX || '\0' != *end || x < min || x > max || ERANGE == errno)
		{
			printf("%s%d%s%d%s", "ERROR: Enter a number from ", min, " to ", max, "\n");
		}
		else
		{
			valid = -1;
		}

	} while (valid != -1);
	return x;
}//end of verifyData

//collects string from user and ensures last character is null
void fgetsRemoveNewLine(char* const str)
{
	fgets(str, SIZE, stdin);
	size_t positionPtr = strlen(str);
	if (*(str + (positionPtr - 1)) == '\n')
	{
		*(str + (positionPtr - 1)) = '\0';
	}
}//end of fgetsRemoveNewLine


//Function to add new node
void oinsertNode(ORGANIZATIONS** headPtr, ORGANIZATIONS* oInsert)
{
	ORGANIZATIONS* newOrganization = malloc(sizeof(ORGANIZATIONS));
	if (newOrganization != NULL)
	{
		ORGANIZATIONS* tempPtr = NULL;
		oInsert = newOrganization;
		tempPtr = oInsert;
		newOrganization = tempPtr;
		char inputStr[SIZE];

		//values in main are updated
		printf("%s", "\nEnter Organization Name: ");
		fgetsRemoveNewLine(inputStr);
		strcpy(newOrganization->organizationName, inputStr);
		printf("%s%s\n", "Your organization is called: ", newOrganization->organizationName);
		printf("%s%d%s%d%s", "Enter Distance of Race: (between ", DISTANCEMIN, " and ", DISTANCEMAX, "): ");
		newOrganization->raceDistance = getValidDouble(inputStr, DISTANCEMIN, DISTANCEMAX);
		printf("%s%.2lf\n", "Your Race's distance is: ", newOrganization->raceDistance);
		printf("%s%d%s%d%s", "Enter Price of Race: (between ", RACECOSTMIN, " and ", RACECOSTMAX, "): ");
		newOrganization->raceCost = getValidDouble(inputStr, RACECOSTMIN, RACECOSTMAX);
		printf("%s%.2lf\n", "Your Race's cost is: ", newOrganization->raceCost);
		printf("%s%d%s%d%s", "Enter Price of Jersey: (between ", JERSEYCOSTMIN, " and ", JERSEYCOSTMAX, "): ");
		newOrganization->jerseyCost = getValidDouble(inputStr, JERSEYCOSTMIN, JERSEYCOSTMAX);
		printf("%s%.2lf\n", "Your Race's Jersey cost is: ", newOrganization->jerseyCost);
		printf("%s%d%s%d%s", "Enter Percentage for Charity: (between ", PERCENTMIN, " and ", PERCENTMAX, "): ");
		newOrganization->charityPercentage = getValidDouble(inputStr, PERCENTMIN, PERCENTMAX);
		printf("%s%.2lf%s\n", "Your Race's revenue percentage for charity is: ", newOrganization->charityPercentage, "%");


		//figure where to put new organization in the linked list
		ORGANIZATIONS* previousPtr = NULL;
		ORGANIZATIONS* currentPtr = *headPtr;
		while (currentPtr != NULL && (strcmp(currentPtr->organizationName, oInsert->organizationName)))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->orgPtr;
		}
		if (previousPtr == NULL)
		{
			*headPtr = newOrganization;
		}
		else
		{
			previousPtr->orgPtr = newOrganization;
		}
		newOrganization->orgPtr= currentPtr;
	}
	//When all nodes are gone
	else
	{
		printf("No memory to create node for %s\n", oInsert->organizationName);
	}
}

void rinsertNode(RIDERS** headPtr, RIDERS* rInsert)
{
	RIDERS* newNodePtr = malloc(sizeof(RIDERS));
	if (newNodePtr != NULL)
	{
		newNodePtr = rInsert;

		RIDERS* previousPtr = NULL;
		RIDERS* currentPtr = *headPtr;

		while (currentPtr != NULL && (strcmp(currentPtr->riderName, rInsert->riderName)))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->ridPtr;
		}
		if (previousPtr == NULL)
		{
			*headPtr = newNodePtr;
		}
		else
		{
			previousPtr->ridPtr = newNodePtr;
		}
		newNodePtr->ridPtr = currentPtr;
	}
	//When all nodes are gone
	else
	{
		printf("No memory to create node for %s\n", rInsert->riderName);
	}

}

ORGANIZATIONS* orgChoice(ORGANIZATIONS** orgHead)
{
	printf("%s", "Organizations\tDistance\tCost\tPercentage");
	ORGANIZATIONS* currentPtr;
	char* orgChoice = "";
	if (orgHead != NULL)
	{
		printf("%s", "Choose from Organizations : ");
		currentPtr = *orgHead;

		while (currentPtr != NULL)
		{
			printf("%s\t%lf\t%lf\t%lf", currentPtr->organizationName, currentPtr->raceDistance, currentPtr->raceCost, currentPtr->charityPercentage);
		}
	}
	//get choice assign to pointer find organization ptr to return
	puts("Enter organization name for the race you want to enter: ");
	fgetsRemoveNewLine(orgChoice);
	ORGANIZATIONS* choicePtr;
	choicePtr = *orgHead;
	while (choicePtr->orgPtr != NULL)
	{
		choicePtr = choicePtr->orgPtr;
		if (orgChoice == choicePtr->organizationName)
		{
			return choicePtr;
		}
	}

	//print options and give selection method
	return currentPtr;
}//end of orgChoice


void closeAll(ORGANIZATIONS* oheadPtr, RIDERS* rheadPtr)
{
	//Ptrs for heads and temporary ptrs 
	ORGANIZATIONS* ocurrentPtr = oheadPtr;
	RIDERS* rcurrentPtr = rheadPtr;
	ORGANIZATIONS* onextNode = NULL;
	RIDERS* rnextNode = NULL;
	//free organization memory
	while (ocurrentPtr != NULL)
	{
		onextNode = ocurrentPtr->orgPtr;
		free(ocurrentPtr);
		ocurrentPtr = onextNode;
	}
	//free riders memory
	while (rcurrentPtr != NULL)
	{
		rnextNode = rcurrentPtr->ridPtr;
		free(rcurrentPtr);
		rcurrentPtr = rnextNode;
	}
}//end of closeAll function
