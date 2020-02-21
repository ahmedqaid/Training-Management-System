#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#pragma warning (disable: 4996)
#pragma warning (disable: 6001)
#pragma warning (disable: 6031)
#pragma warning (disable: 6054)

void mainMenu();
void schedule();
void book(int pass);
void payment(int pass2);
int checkID(char idd[10]);
void registerP();
void updatePart(char idR[10]);
void cancel();
void viewCourses(char idR[10]);
void cancel();
void search();
void change();
void invoice();
void invoiceEach();
void invoiceAll();
void checkAvailability();

struct participant {
	char id[10];
	char firstName[20];
	char lastName[20];
	char gender[8];
	int collected;
	int outstanding;
}p;

struct participantCourses {
	char id[10];
	char courseName[50];
	char startDate[20];
	bool meal;
	bool mealsVeg;
}c;

struct courseDetails {
	char category[20];
	char courseName[50];
	char startDate[20];
	int duration;
}cd;

int main() {
	FILE* file;
	if ((file = fopen("Participants.txt", "r")) == NULL) {
		file = fopen("Participants.txt", "w");
		fclose(file);
	}
	if ((file = fopen("Courses.txt", "r")) == NULL) {
		file = fopen("Courses.txt", "w");
		fclose(file);
	}
	if ((file = fopen("Participants Courses.txt", "r")) == NULL) {
		file = fopen("Participants Courses.txt", "w");
		fclose(file);
	}
	mainMenu();
}

void mainMenu() {
	system("cls");
	printf("TRAINING COURSE PACKAGE MANAGEMENT SYSTEM\n");
	printf("------------------------------------------\n");
	printf("1. Create course schedule\n");
	printf("2. Book course\n");
	printf("3. Change\n");
	printf("4. Check Availability\n");
	printf("5. Search\n");
	printf("6. Pay Bills\n");
	printf("7. Cancel\n");
	printf("8. Invoice Check\n");
	printf("9. Exit\n");
	printf("------------------------------------------\n");
	printf("Input your choice: ");

	switch (getche()) {
	case '1':
		schedule();
		break;
	case '2':
		system("cls");
		printf("1. New Participant\n2. Existing Participant\nEnter number: ");
		switch (getche()) {
		case '1':
			registerP();
			break;
		case '2':
			book(0);
			break;
		default:
			printf("\nInvalid choice!\n");
			mainMenu();
		}
		break;
	case '3':
		change();
		break;
	case '4':
		checkAvailability();
		break;
	case '5':
		search();
		break;
	case '6':
		payment(0);
		break;
	case '7':
		cancel();
		break;
	case '8':
		invoice();
		break;
	case '9':
		exit(0);
	default:
		printf("\nInvalid input\n");
		system("pause");
		mainMenu();
	}
	mainMenu();
}

void schedule() {
	system("cls");
	int choice, choice2;
	printf("Categories\n");
	printf("------------------------------------------\n");
	printf("1. Soft Skills\n");
	printf("2. computing skills\n");
	printf("------------------------------------------\n");
	printf("Enter the category number: ");
	scanf("%i", &choice);
	switch (choice) {
	case 1:
		printf("\nCourses\n");
		printf("------------------------------------------\n");
		printf("1. Team Building\n");
		printf("2. Communications\n");
		printf("3. Corporate Career Growth\n");
		printf("4. Conflict Management\n");
		break;

	case 2:
		printf("\nCourses\n");
		printf("------------------------------------------\n");
		printf("\n1. Software Design\n");
		printf("2. Web Development\n");
		printf("3. Cloud Computing\n");
		printf("4. Mobile Content Design and Development\n");
		break;

	default:
		printf("\nInvalid input\n");
		system("pause");
		mainMenu();
	}
	printf("------------------------------------------\n");
	printf("Enter the number of course to join: ");
	scanf("%i", &choice2);

	printf("Enter date (dd/mm/yyyy): ");
	scanf("%s", &cd.startDate);
	if (choice == 1 && choice2 == 1) {
		strcpy(cd.courseName, "Team Building");
		strcpy(cd.category, "Soft Skills");
		cd.duration = 3;
	}
	else if (choice == 1 && choice2 == 2) {
		strcpy(cd.courseName, "Communications");
		strcpy(cd.category, "Soft Skills");
		cd.duration = 3;
	}
	else if (choice == 1 && choice2 == 3) {
		strcpy(cd.courseName, "Corporate Career Growth");
		strcpy(cd.category, "Soft Skills");
		cd.duration = 3;
	}
	else if (choice == 1 && choice2 == 4) {
		strcpy(cd.courseName, "Conflict Management");
		strcpy(cd.category, "Soft Skills");
		cd.duration = 3;
	}
	else if (choice == 2 && choice2 == 1) {
		strcpy(cd.courseName, "Software Design");
		strcpy(cd.category, "Computing Skills");
		cd.duration = 5;
	}
	else if (choice == 2 && choice2 == 2) {
		strcpy(cd.courseName, "Web Development");
		strcpy(cd.category, "Computing Skills");
		cd.duration = 5;
	}
	else if (choice == 2 && choice2 == 3) {
		strcpy(cd.courseName, "Cloud Computing");
		strcpy(cd.category, "Computing Skills");
		cd.duration = 3;
	}
	else if (choice == 2 && choice2 == 4) {
		strcpy(cd.courseName, "Mobile Content Design and Development");
		strcpy(cd.category, "Computing Skills");
		cd.duration = 5;
	}
	else {
		printf("Ivalid Input!\n");
		system("pause");
		schedule();
	}
	FILE* addCourse;
	addCourse = fopen("Courses.txt", "a+");
	fwrite(&cd, sizeof(cd), 1, addCourse);
	fclose(addCourse);

	return;
}

int checkID(char idd[10]) {
	FILE* idOpen;
	idOpen = fopen("Participants.txt", "r");
	if (idOpen == 0)
		return 0;
	while (!feof(idOpen)) {
		fread(&p, sizeof(p), 1, idOpen);
		if (strcmp(idd, p.id) == 0) {
			fclose(idOpen);
			return 1;
		}
	}
	fclose(idOpen);
	return 0;
}

void registerP() {
	int idAvailability;
	char idread[10];
	system("cls");
	printf("Enter ID: ");
	scanf("%s", &idread);
	idAvailability = checkID(idread);
	if (idAvailability == 0)
	{
		strcpy(p.id, idread);
		printf("\nEnter First Name: ");
		scanf("%s", &p.firstName);
		printf("\nEnter Last Name: ");
		scanf("%s", &p.lastName);
	gend:
		printf("\nGender\n1. Male\n2. Female\nEnter number: ");
		switch (getche()) {
		case '1':
			strcpy(p.gender, "male");
			break;
		case '2':
			strcpy(p.gender, "female");
			break;
		default:
			printf("Invlaid input!");
			goto gend;
		}
		p.collected = 0;
		p.outstanding = 0;

		FILE* addMember;
		addMember = fopen("Participants.txt", "a+");
		fwrite(&p, sizeof(p), 1, addMember);
		fclose(addMember);

		printf("\n\n%s %s has been added to the database successfully\n", p.firstName, p.lastName);
		book(1);
	}
	else if (idAvailability == 1) {
		printf("\nThis ID is already registered\nYou can add courses to an existing member from the main menu\n");
		printf("You will be redirected back immediately\n");
		system("pause");
		mainMenu();
	}
}

void book(int pass) {
	int courseChoice;
	char idR[10];
	if (pass == 0) {
		int idAvailability;
		system("cls");
		printf("Enter ID: ");
		scanf("%s", &idR);
		idAvailability = checkID(idR);
		if (idAvailability == 0) {
			printf("Invalid ID!\n");
			system("pause");
			mainMenu();
		}
	}
	else
		strcpy(idR, p.id);
	int i = 1;
	FILE* viewCourses;
	printf("\nAvailable Courses >\n\n");
	viewCourses = fopen("Courses.txt", "r");
	if (viewCourses == 0)
		printf("\nThe file is not available\n");
	else {
		printf("Number   Course Name\t\t\t\t      Category\t\t       Start Date\t   Duration\n");
		printf("----------------------------------------------------------------------------------------------------------\n");
		while (fread(&cd, sizeof(cd), 1, viewCourses)) {
			printf("%-9i%-45s%-25s%-20s%i days\n", i, cd.courseName, cd.category, cd.startDate, cd.duration);
			i++;
		}
		fclose(viewCourses);
	}
	printf("\nAn admin fee of RM 50 will apply with each course registration\n");
	printf("----------------------------------------------------------------------------------------------------------\n");
choiceC:
	printf("Enter the number of course: ");
	scanf("%i", &courseChoice);
	if (courseChoice > i || courseChoice < 1) {
		printf("Invalid Choice\n");
		goto choiceC;
	}
	
	int j = 1;
	FILE* courseGet;
	courseGet = fopen("Courses.txt", "r");
	while (fread(&cd, sizeof(cd), 1, courseGet)) {
		if (j == courseChoice)
			break;
		j++;
	}
	fclose(courseGet);

	strcpy(c.courseName, cd.courseName);
	strcpy(c.startDate, cd.startDate);

	int courseFee = 0, mealVegFee = 0, mealFee = 0;
	if (strcmp(cd.courseName, "Team Building") == 0) {
		courseFee = 800;
		mealVegFee = 75;
		mealFee = 50;
	}
	else if (strcmp(cd.courseName, "Communications") == 0) {
		courseFee = 650;
		mealVegFee = 50;
		mealFee = 25;
	}
	else if (strcmp(cd.courseName, "Corporate Career Growth") == 0) {
		courseFee = 750;
		mealVegFee = 50;
		mealFee = 25;
	}
	else if (strcmp(cd.courseName, "Conflict Management") == 0) {
		courseFee = 600;
		mealVegFee = 50;
		mealFee = 25;
	}
	else if (strcmp(cd.courseName, "Software Design") == 0) {
		courseFee = 1000;
		mealVegFee = 50;
		mealFee = 25;
	}
	else if (strcmp(cd.courseName, "Web Development") == 0) {
		courseFee = 1100;
		mealVegFee = 75;
		mealFee = 50;
	}
	else if (strcmp(cd.courseName, "Cloud Computing") == 0) {
		courseFee = 1300;
		mealVegFee = 50;
		mealFee = 25;
	}
	else if (strcmp(cd.courseName, "Mobile Content Design and Development") == 0) {
		courseFee = 1200;
		mealVegFee = 75;
		mealFee = 50;
	}
meal:
	printf("\nMeals (Y/N): ");
	switch (getche()) {
	case 'Y':
	case 'y':
		c.meal = true;
		break;
	case 'N':
	case 'n':
		c.meal = false;
		mealVegFee = 0;
		mealFee = 0;
		c.mealsVeg = false;
		goto noMeal;
		break;
	default:
		printf("Invalid Entry!");
		goto meal;
	}

	mealV:
	printf("\nVegetarian (Y/N): ");
	switch (getche()) {
	case 'Y':
	case 'y':
		c.mealsVeg = true;
		mealFee = 0;
		break;
	case 'N':
	case 'n':
		c.mealsVeg = false;
		mealVegFee = 0;
		break;
	default:
		printf("Invalid Entry!");
		goto mealV;
	}

noMeal:


	p.outstanding += 50 + (courseFee + mealVegFee + mealFee) * cd.duration;
	updatePart(idR);
	strcpy(c.id, idR);
	FILE* addPCourse;
	addPCourse = fopen("Participants Courses.txt", "a+");
	fwrite(&c, sizeof(c), 1, addPCourse);
	fclose(addPCourse);

	wish:
	printf("\nDo you wish to proceed with the payment now? (Y-N): ");
	switch (getche()) {
	case 'Y':
	case 'y':
		payment(1);
		break;
	case 'N':
	case 'n':
		return;
		break;
	default:
		printf("\nInvalid Input\n");
		goto wish;
	}
}

void payment(int pass1) {
	system("cls");
	char idR[10];
	int amount, idChecking;
	if (pass1 == 0) {
		printf("Enter ID: ");
		scanf("%s", &idR);
		idChecking = checkID(idR);
		if (idChecking == 0) {
			printf("Invalid ID!\n");
			system("pause");
			mainMenu();
		}
	}
	else
		strcpy(idR, p.id);

	printf("\nName: %s %s\nOutstanding amount: %i\nTotal Collected: %i\n", p.firstName, p.lastName, p.outstanding, p.collected);
	printf("How much is the amount to be paid: ");
	scanf("%i", &amount);
	if (amount > p.outstanding || amount < 0) {
		printf("\nInvalid Input!\n");
		system("pause");
		payment(1);
	}
	p.outstanding -= amount;
	p.collected += amount;
	updatePart(idR);
}

void updatePart(char idR[10]) {
	FILE* tempAdd;
	FILE* removeP;
	FILE* tempP;

	tempAdd = fopen("Temp.txt", "w");
	fwrite(&p, sizeof(p), 1, tempAdd);
	fclose(tempAdd);

	removeP = fopen("Participants.txt", "r");
	tempP = fopen("Temp1.txt", "w");
	while (fread(&p, sizeof(p), 1, removeP))
		if (strcmp(p.id, idR) != 0)
			fwrite(&p, sizeof(p), 1, tempP);
	fclose(removeP);
	fclose(tempP);
	removeP = fopen("Participants.txt", "w");
	tempP = fopen("Temp1.txt", "r");
	tempAdd = fopen("Temp.txt", "r");
	while (fread(&p, sizeof(p), 1, tempP))
		fwrite(&p, sizeof(p), 1, removeP);
	fread(&p, sizeof(p), 1, tempAdd);
	fwrite(&p, sizeof(p), 1, removeP);
	fclose(tempAdd);
	fclose(removeP);
	fclose(tempP);
	return;
}

void cancel() {
	system("cls");
	char idR[10];
	int idVerification, choice;
	printf("Enter ID: ");
	scanf("%s", &idR);
	idVerification = checkID(idR);
	if (idVerification == 0) {
		printf("\nInvalid ID\n");
		system("pause");
		mainMenu();
	}
	viewCourses(idR);
	printf("Enter the number of the course to cancel/change before start: ");
	scanf("%i", &choice);

	int i = 1;
	FILE* getCancel;
	getCancel = fopen("Participants Courses.txt", "r");
	while (fread(&c, sizeof(c), 1, getCancel)) {
		if (strcmp(c.id, idR) != 0)
			continue;
		if (choice == i)
			break;
		i++;
	}
	fclose(getCancel);

	FILE* removeP;
	FILE* tempP;
	removeP = fopen("Participants Courses.txt", "r");
	tempP = fopen("Temp1.txt", "w");
	while (fread(&c, sizeof(c), 1, removeP)) {
		if (strcmp(c.id, idR) != 0 && choice != i)
			fwrite(&p, sizeof(c), 1, tempP);
		if (strcmp(c.id, idR) == 0)
			i++;
	}
	fclose(removeP);
	fclose(tempP);
	removeP = fopen("Participants Courses.txt", "w");
	tempP = fopen("Temp1.txt", "r");
	while (fread(&c, sizeof(c), 1, tempP))
		fwrite(&c, sizeof(c), 1, removeP);
	fclose(removeP);
	fclose(tempP);

	printf("\nCancellation Succeded\n");
	strcpy(p.id, idR);
	checkID(idR);
	system("pause");
	return;
}

void viewCourses(char idR[10]) {
	int i = 1;
	printf("\nParticipant ID: %s\n", idR);
	printf("Number   Course Name\t\t\t\t      Meals       Vegeterain  Start Date\n");
	printf("----------------------------------------------------------------------------------------------------\n");
	FILE* viewCs;
	viewCs = fopen("Participants Courses.txt", "r");
	while (fread(&c, sizeof(c), 1, viewCs)) {
		if (strcmp(c.id, idR) != 0)
			continue;
		printf("%-9i%-45s%-12d%-12d%s\n", i, c.courseName, c.meal, c.mealsVeg, c.startDate);
		i++;
	}
	fclose(viewCs);
	printf("\n----------------------------------------------------------------------------------------------------\n");	
	return;
}

void search() {
	char idR[10];
	int verification;
	system("cls");
	printf("Enter Participants ID: ");
	scanf("%s", &idR);
	verification = checkID(idR);
	if (idR == 0)
		printf("\nInvalid ID!\n");
	else
		viewCourses(idR);
	system("pause");
	mainMenu();
}

void change() {
	cancel();
	book(1);
}

void invoice() {
	system("cls");
	printf("1. Print amount receivable from each participant\n");
	printf("2. Print total amount receivable and total payment received\n");
	printf("Enter your choice: ");
	switch (getche()) {
	case '1':
		invoiceEach();
		break;
	case '2':
		invoiceAll();
		break;
	default:
		printf("\nInvalid Choice!\n");
		invoice();
	}
	return;
}

void invoiceEach() {
	system("cls");
	FILE* inv;
	inv = fopen("Participants.txt", "r");
	printf("Receivable\t  Full Name\n");
	printf("------------------------------------------\n");
	while (fread(&p, sizeof(p), 1, inv))
		printf("RM %-15i%s %s\n", p.outstanding, p.firstName, p.lastName);
	fclose(inv);
	printf("\n");
	system("pause");
	return;
}

void invoiceAll() {
	printf("\n\n");
	int tReceivable = 0, tReceived = 0;
	FILE* inv;
	inv = fopen("Participants.txt", "r");
	while (fread(&p, sizeof(p), 1, inv)) {
		tReceivable += p.outstanding;
		tReceived += p.collected;
	}
	fclose(inv);
	printf("\nTOTAL RECEIVABLE: RM %i", tReceivable);
	printf("\nTOTAL RECEIVED: RM %i\n", tReceived);
	system("pause");
	return;
}

void checkAvailability() {
	system("cls");
	char dateRead[20];
	int findings = 0;
	printf("Enter date (dd/mm/yyyy): ");
	scanf("%s", &dateRead);
	FILE* dateGet;
	dateGet = fopen("Courses.txt", "r");
	while (fread(&cd, sizeof(cd), 1, dateGet)) {
		if (strcmp(dateRead, cd.startDate) == 0) {
			if (findings == 0) {
				printf("Course Name\t\t\t\t     Category\t\t      Start Date\t  Duration\n");
				printf("--------------------------------------------------------------------------------------------------\n");
			}
			findings = 1;
			printf("%-45s%-25s%-20s%i days\n", cd.courseName, cd.category, cd.startDate, cd.duration);
		}
	}
	printf("--------------------------------------------------------------------------------------------------\n");
	if (findings == 0)
		printf("No course is appointed to that specific date...\n");
	system("pause");
	mainMenu();
}
