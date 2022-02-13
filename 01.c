#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void message()
{
	system("cls");
	
	printf("\n************************************************************************************************************************\n\n");
	printf("\t\t\t\t\t\tAUTOMATED BILL GENERATOR\n");
	printf("\n************************************************************************************************************************\n\n");
}

void getInput(int * itemNumber, char * itemName, char * itemPrice)
{
	fflush(stdin);
	
	printf("\nAvailable Apparels\n");
	printf("1 : Shirt | Price : Rs 500\n");
	printf("2 : Trouser | Price : Rs 800\n");
	printf("3 : Jeans | Price : Rs 1200\n");
	printf("4 : Hoodie | Price : Rs 1500\n");
	printf("5 : Leather Jacket | Price : Rs 2500\n");
	printf("\nChoose the Apparel from the above List. (Press Corresponding Number)\n");
	scanf("%d", & * itemNumber);
	
	switch (* itemNumber)
	{
		case 1:
			strcpy(itemName, "Shirt");
			strcpy(itemPrice, "500");
			break;
		case 2:
			strcpy(itemName, "Trouser");
			strcpy(itemPrice, "800");
			break;
		case 3:
			strcpy(itemName, "Jeans");
			strcpy(itemPrice, "1200");
			break;
		case 4:
			strcpy(itemName, "Hoodie");
			strcpy(itemPrice, "1500");
			break;
		case 5:
			strcpy(itemName, "Leather Jacket");
			strcpy(itemPrice, "2500");
			break;
		default:
			printf("\nInvalid Apparel Choosen!\n");
	}
}

char * replaceWord (const char * str, const char * oldWord, const char * newWord)
{
	char * resultString;
	int i, count = 0;
	int oldWordLength = strlen(oldWord);
	int newWordLength = strlen(newWord);
	
	// Lets Count the Number of times Old Word Occurs in the String.
	
	for (i = 0; str[i] != '\0'; i ++)
	{
		if ((strstr(&str[i], oldWord)) == (&str[i]))
		{
			count ++;
			
			// Jump Over this Word.
			
			i += (oldWordLength - 1);
		}
	}
	
	// Making a New String to fit in the Replaced Words.
	
	resultString = (char *) malloc (i + (count * (newWordLength - oldWordLength)) + 1);
	
	i = 0;
	
	while (* str)
	{
		// Compare the substring with Result.
		
		if ((strstr(str, oldWord)) == (str))
		{
			strcpy(&resultString[i], newWord);
			str += oldWordLength;
			i += newWordLength;
		}
		
		else
		{
			resultString[i] = * str;
			str ++;
			i ++;
		}
	}
	
	resultString[i] = '\0';
	
	return resultString;
}

int main()
{
	FILE * templateBill = NULL;
	FILE * bill = NULL;
	
	templateBill = fopen("Template Bill.txt", "r");
	bill = fopen("Bill.txt", "w");
	
	char str [200];
	
	fgets(str, 200, templateBill);
	
	int itemNumber;
	char userName [50], itemName [20], itemPrice [6];
	
	message();
	
	printf("Enter User Name : ");
	
	fflush(stdin);
	
	fgets(userName, sizeof(userName), stdin);
	
	strtok(userName, "\n");
	
	fflush(stdin);
	
	getInput(&itemNumber, itemName, itemPrice);
	
	// Call the replaceWord function and Generate generatedBill.
	
	if ((itemNumber > 0) && (itemNumber < 6))
	{
		char * generatedBill;
		
		generatedBill = replaceWord(str, "{{name}}", userName);
		generatedBill = replaceWord(generatedBill, "{{item}}", itemName);
		generatedBill = replaceWord(generatedBill, "{{price}}", itemPrice);
		generatedBill = replaceWord(generatedBill, "{{outlet}}", "Balaji Apparels");
		
		printf("\nGenerated Bill\n\n%s\n", generatedBill);
		printf("\nThe Generated Bill has been successfully written to the file Bill.txt\n");
		
		fprintf(bill, "%s", generatedBill);
	}
	
	fclose(templateBill);
	fclose(bill);
	
	return 0;
}

