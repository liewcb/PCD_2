#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#pragma warning(disable:4996)

#define MAXSIZE 100

typedef struct {
	char trainID[8], location1[30], location2[30];
	int departHour, departMinute, arrivalHour, arrivalMinute;
}placeTime;

typedef struct {
	char staffName[30], staffPw[20];
}Staff;
Staff lg;

void menu();
void userMode();
void staffMode();

//Validation

void dHourValidate(int hour, int *condition) {

	if (hour >= 0 && hour <= 5) {
		printf("Trains only operate after 5am...\n");
		*condition = 1;
	}
	else if (hour >= 21) {
		printf("Train must depart before 9pm(2100)...\n");
		*condition = 1;
	}
	else if (hour < 0){
		printf("Invalid input.......\n");
		*condition = 1;
	}
	else {
		*condition = 0;
	}
}   //validate departing hour

void dMinuteValidate(int minute, int *condition) {
	if (minute < 0 || minute >= 60) {
		printf("Invalid input.......\n");
		*condition = 1;
	}
	else {
		*condition = 0;
	}
}	//validate departing minute

void aHourValidate(int dhour, int ahour, int *condition) {
	if (ahour < dhour) {
		printf("INVALID!! Arrive hour before depart hour?!\n");
		*condition = 1;
	}
	else if (ahour >= 24 || ahour >= 0 && ahour <= 5) {
		printf("Train only operate until 12am...\n");
		*condition = 1;
	}
	
	else {
		*condition = 0;
	}
} //validate arrive hour

void aMinuteValidate(int dhour, int ahour, int dminute, int aminute, int *condition) {
	if (ahour == dhour) {
		if (aminute <= dminute) {
			printf("Invalid. Time must be after depart time!!\n");
			return *condition = 1;
		}
		else if (aminute < 0 || aminute >= 60) {
			printf("Invalid input\n");
			return *condition = 1;
		}
		else {
			return *condition = 0;
		}
	}

	if (aminute < 0 || aminute >= 60) {
		printf("Invalid input.....\n");
		return *condition = 1;
	}
	else {
		return *condition = 0;
	}
	
} //validate arrive minute

void arriveLocValidate(char depart[], char arrival[], int *condition) {

	char d[40] ;
	char a[40] ;

	strcpy(d, depart);
	strcpy(a, arrival);

	int length = strlen(depart);
	for (int i = 0; i < length; i++) {
		d[i] = toupper(d[i]);
	}

	int leng = strlen(arrival);
	for (int i = 0; i < leng; i++) {
		a[i] = toupper(a[i]);
	}

	if (strcmp(d, a) == 0) {
		printf("Same place....Enter another location\n");
		*condition = 1;
	}
	else {
		*condition = 0;
	}

}  //validate destination

void showID() {
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	fclose(ptr);

	printf("\n-------------\n");
	for (int i = 0; i < found; i++) {
		printf("%02d.) %s\n", i + 1, p[i].trainID);
	}
	printf("-------------\n");
} //show only exist train id

void atrainIdValidate(char train_id[], int *condition) {
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0, choice = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	fclose(ptr);


	for (int i = 0; i < found; i++) {
		if (strcmp(p[i].trainID, train_id) == 0) {
			printf("This train id already exist, use another one....\n");
			printf("1 to continue, 2 to show exist train IDs: ");
			rewind(stdin);
			scanf("%d", &choice);
			
			if (choice == 1) {
				*condition = 1;
			}
			else if (choice == 2) {
				showID();
				*condition = 1;
			}

			*condition = 1;
			return;
		}
	}
	*condition = 0;
}		//train id validation for adding function

void showSch() {
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	fclose(ptr);

	printf("\n-------------------------------------------------------------------------------------------------------\n");
	for (int j = 0; j < found; j++) {
		printf("%02d.) %-20s%-20s    %02d%02d               %-20s  %02d%02d\n",j+1 ,p[j].trainID, p[j].location1, p[j].departHour,
			p[j].departMinute, p[j].location2, p[j].arrivalHour, p[j].arrivalMinute);
	}
	printf("\n-------------------------------------------------------------------------------------------------------\n");
}; //show schedule to help staff

void mtrainIdValidate(char train_id[], placeTime p[MAXSIZE], int *condition) {
	int choice;
	*condition = 1; // Assume the train ID doesn't exist until found

	for (int i = 0; i < MAXSIZE; i++) {
		if (strcmp(p[i].trainID, train_id) == 0) {
			// If train ID matches current element
			*condition = 0; // Set condition to 0 (indicating valid)
			return;
		}
	}

	// If loop completes without finding a match
	printf("This train id does not exist. 1 to retry, 2 to show existing records then retry: ");
	scanf("%d", &choice);

	if (choice == 2) {
		showSch();
	}
} //validate train id for modify function

//User

void displayAll() {
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	placeTime p[MAXSIZE];
	int found = 0;
	char choice;

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	printf("\n==========================================================================================\n");
	printf("Train ID            Departure               Time               Arrival               Time");
	printf("\n==========================================================================================\n");

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);

	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	for (int j = 0; j < found; j++) {
		printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n", p[j].trainID, p[j].location1, p[j].departHour,
			p[j].departMinute, p[j].location2, p[j].arrivalHour, p[j].arrivalMinute);
	}

	printf("------------------------------------------------------------------------------------------\n");
	printf("\t\t\t**Time display in 24hr-clock**\n");

	printf("\n\n");
	fclose(ptr);
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' to quit user mode, any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		userMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void searchDepart() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                            SEARCH BY ORIGIN                            **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	char searchLocation1[25], cont, choice;
	int f = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	do {
		printf("\n\nSearch Depart Location: ");				//prompt user to search origin location
		rewind(stdin);
		scanf("%[^\n]", searchLocation1);

		char s[40], d[40];
		strcpy(s, searchLocation1);
		int length = strlen(searchLocation1);
		for (int i = 0; i < length; i++) {
			s[i] = toupper(s[i]);
		}

		printf("\n==========================================================================================\n");
		printf("Train ID            Departure               Time               Arrival               Time");
		printf("\n==========================================================================================\n");

		for (int i = 0; i < found; i++) {

			strcpy(d, p[i].location1);
			int lengt = strlen(p[i].location1);
			for (int i = 0; i < lengt; i++) {
				d[i] = toupper(d[i]);
			}

			if (strcmp(s, d) == 0) {
				printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n", p[i].trainID, p[i].location1, p[i].departHour,
					p[i].departMinute, p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
				f++;
			}												 //show the related element of array that read from file
		}
		printf("------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t**Time display in 24hr-clock**\n\n");
		printf("\t\t\tTotal %d schedule depart from %s\n\n", f, searchLocation1);

		if (f == 0) {
			printf("No record found...\n");
		}

		f = 0;

		printf("Continue to search? ('C' to continue)\n");
		rewind(stdin);
		scanf("%c", &cont);
	} while (toupper(cont) == 'C');

	printf("\n\n");

	fclose(ptr);

	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu, any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		userMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void searchArrival() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                        SEARCH BY DESTINATION                           **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	int f = 0;
	char searchLocation2[25], cont, choice;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	do {
		printf("\n\nSearch Destination: ");     //prompt user to search destination
		rewind(stdin);
		scanf("%[^\n]", searchLocation2);

		char s[40], a[40];
		strcpy(s, searchLocation2);
		int length = strlen(searchLocation2);
		for (int i = 0; i < length; i++) {
			s[i] = toupper(s[i]);
		}

		printf("\n==========================================================================================\n");
		printf("Train ID            Departure               Time               Arrival               Time");
		printf("\n==========================================================================================\n");

		for (int i = 0; i < found; i++) {

			strcpy(a, p[i].location2);
			int lengt = strlen(p[i].location2);
			for (int i = 0; i < lengt; i++) {
				a[i] = toupper(a[i]);
			}

			if (strcmp(s,a) == 0) {
				printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n", p[i].trainID, p[i].location1, p[i].departHour,
					p[i].departMinute, p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
				f++;							//show the related element of array that read from file
			}
		}
		printf("------------------------------------------------------------------------------------------\n");
		printf("\t\t\t\t**Time display in 24hr-clock**\n\n");
		printf("\t\t\tTotal %d schedule travel to %s\n\n", f, searchLocation2);

		if (f == 0) {
			printf("No record found...\n");
		}
		f = 0;

		printf("Continue to search? ('C' to continue)\n");
		rewind(stdin);
		scanf("%c", &cont);
	} while (toupper(cont) == 'C');


	printf("\n\n");

	fclose(ptr);

	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu, any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		userMode();
	case 'Q':
		menu();
	default:
		system("pause");
		exit(-1);
	}
}

void userMode() {

	printf("\t\t\t\t\t\t\   __        __   _                          \n");
	printf("\t\t\t\t\t\t\   \\ \\      / /__| | ___ ___  _ __ ___   ___ \n");
	printf("\t\t\t\t\t\t\    \\ \\ /\\ / / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\\n");
	printf("\t\t\t\t\t\t\     \\ V  V /  __/ | (_| (_) | | | | | |  __/\n");
	printf("\t\t\t\t\t\t\    __\\_/\\_/ \\___|_|\\___\\___/|_| |_| |_|\\___|\n");
	printf("\t\t\t\t\t\t\   |_   _| __ __ ___   _____| | ___ _ __     \n");
	printf("\t\t\t\t\t\t\     | || '__/ _` \\ \\ / / _ \\ |/ _ \\ '__|    \n");
	printf("\t\t\t\t\t\t\     | || | | (_| |\\ V /  __/ |  __/ |       \n");
	printf("\t\t\t\t\t\t\     |_||_|  \\__,_| \\_/ \\___|_|\\___|_|       \n");

	int choice;
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                          WELCOME TO USER MODE                          **\n");
	printf("\t\t\t\t**                 You can look for the train schedule here!!             **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t\t\t\t    1. Display whole timetable\n");
	printf("\t\t\t\t\t\t\t    2. Search by depart location\n");
	printf("\t\t\t\t\t\t\t    3. Search by destination\n");
	printf("\t\t\t\t\t\t\t    4. Exit to main menu\n");
	printf("\t\t\t\t\t\t\t    Any key to exit program\n");
	printf("Sort by: ");
	rewind(stdin);
	scanf("%d", &choice);
	system("cls");

	switch (choice) {
	case 1:
		displayAll();
		break;
	case 2:
		searchDepart();
		break;
	case 3:
		searchArrival();
		break;
	case 4:
		menu();
		break;
	default:
		break;
	}

}

//Staff

void addSchedule() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                               ADD SCHEDULE                             **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");

	int i = 1, condition;
	char choice;
	char trId[7], depart[25], arrive[25], add;
	int dpHour = 0, dpMinute = 0, arHour = 0, arMinute = 0;

	char show;
	printf("Do you want to see the exist records before adding? ('S' to show): ");   //prompt staff to see existing schedule before adding
	rewind(stdin);
	scanf("%c", &show);

	if (toupper(show) == 'S') {
		showSch();
	}

	printf("Confirm to add train id? ('Y' to yes):\n");    //ask if the staff confirm to add
	rewind(stdin);
	scanf("%c", &add);

	while(toupper(add) == 'Y'){

		do {
			printf("Train ID: ");							//prompt staff to add records then do validation by passing value to subfunctions with parameters
			rewind(stdin);
			scanf("%s", &trId);

			int length = strlen(trId);
			for (int i = 0; i < length; i++) {
				trId[i] = toupper(trId[i]);
			}

			atrainIdValidate(trId, &condition);

		} while (condition != 0);

		printf("Depart Location: ");
		rewind(stdin);
		scanf("%[^\n]", &depart);

		do {
			printf("Depart Hour(24h format): ");
			rewind(stdin);
			scanf("%d", &dpHour);
			dHourValidate(dpHour, &condition);
		} while (condition != 0);
	
		do {
			printf("Depart Minute(24h format): ");
			rewind(stdin);
			scanf("%d", &dpMinute);
			dMinuteValidate(dpMinute, &condition);
		} while (condition != 0);

		do {
			printf("Arrival Location: ");
			rewind(stdin);
			scanf("%[^\n]", &arrive);
			arriveLocValidate(depart, arrive, &condition);
		} while (condition != 0);

		do {
			printf("Arrive Time(Hour): ");
			rewind(stdin);
			scanf("%d", &arHour);
			aHourValidate(dpHour, arHour, &condition);
		} while (condition != 0);

		do {
			printf("Arrive Time(Minute): ");
			rewind(stdin);
			scanf("%d", &arMinute);
			aMinuteValidate(dpHour, arHour, dpMinute, arMinute, &condition);
		} while (condition != 0);

		FILE* ptr;
		ptr = fopen("timetable.txt", "a");

		if (ptr == NULL) {
			printf("Error opening the file, please check the file name\n");     //open the file to append then print into it
			exit(-1);
		}

		fprintf(ptr, "%s %s|%d|%d|%s|%d|%d|\n", trId, depart, dpHour, dpMinute, arrive, arHour, arMinute);
		fclose(ptr);

		printf("\nContinue to add train id? (S to stop/Y to yes): ");
		rewind(stdin);
		scanf("%c", &add);
	} 

	printf("\n");									//back or quit
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu(log out), any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}

}

void modify() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                            MODIFY SCHEDULE                             **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");

	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	int f = 0, m = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	fclose(ptr);					//read file into array

	char findId[8], modDepart[30], modArrival[30], confirm, cont;
	int modDhour, modDminute, modAhour, modAminute;
	int condition;
	
	char show;
	printf("Do you want to see the records before modifying? ('S' to show): ");    //prompt staff to see records before running the functions
	rewind(stdin);
	scanf("%c", &show);

	if (toupper(show) == 'S') {
		showSch();
	}

	printf("Confirm to modify train id? 'C' to continue: ");   //confirm to modify?
	rewind(stdin);
	scanf("%c", &cont);

	while (toupper(cont) == 'C') {
		do {
			printf("Enter a train ID to modify: ");          //prompt staff to enter the train id and pass value into subfunction to validate existing records
			rewind(stdin);
			scanf("%[^\n]", findId);

			int length = strlen(findId);
			for (int i = 0; i < length; i++) {
				findId[i] = toupper(findId[i]);
			}

			mtrainIdValidate(findId, p, &condition);
		} while (condition != 0);


		printf("\nSelected record: ");      //show the regarding records
		printf("\n==========================================================================================\n");
		printf("Train ID            Departure               Time               Arrival               Time");
		printf("\n==========================================================================================\n");

		for (int i = 0; i < found; i++) {
			if (strcmp(p[i].trainID, findId) == 0) {
				printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n\n", p[i].trainID, p[i].location1, p[i].departHour,
					p[i].departMinute, p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
				f++;
				printf("------------------------------------------------------------------------------------------\n");
				printf("\t\t\t*Time display in 24hr-clock*\n\n");
		
				printf("Update depart location: ");
				rewind(stdin);
				scanf("%[^\n]", &modDepart);										//prompt user to modify then validate those value by passing with parameters

				do {
					printf("Update depart hour: ");
					rewind(stdin);
					scanf("%d", &modDhour);
					dHourValidate(modDhour, &condition);
				} while (condition != 0);

				do {
					printf("Update depart minute: ");
					rewind(stdin);
					scanf("%d", &modDminute);
					dMinuteValidate(modDminute, &condition);
				} while (condition != 0);

				do {
					printf("Update arrive location: ");
					rewind(stdin);
					scanf("%[^\n]", &modArrival);
					arriveLocValidate(modDepart, modArrival, &condition);
				} while (condition != 0);

				do {
					printf("Update arrive hour: ");
					rewind(stdin);
					scanf("%d", &modAhour);
					aHourValidate(modDhour, modAhour, &condition);
				} while (condition != 0);

				do {
					printf("Update arrive minute: ");
					rewind(stdin);
					scanf("%d", &modAminute);
					aMinuteValidate(modDhour, modAhour, modDminute, modAminute, &condition);
				} while (condition != 0);

				printf("\nConfirm to update? ('Y' yes): ");
				rewind(stdin);
				scanf("%c", &confirm);

				if (toupper(confirm) == 'Y') {
					strcpy(p[i].location1, modDepart);
					p[i].departHour = modDhour;
					p[i].departMinute = modDminute;
					strcpy(p[i].location2, modArrival);       //save updated value into the respective array
					p[i].arrivalHour = modAhour;
					p[i].arrivalMinute = modAminute;
				}
				FILE* mptr;
				mptr = fopen("timetable.txt", "w");
				if (mptr == NULL) {
					printf("Error opening the file, please check the file name");
					exit(-1);
				}

				for (int i = 0; i < found; i++) {
					fprintf(ptr, "%s %s|%d|%d|%s|%d|%d|\n", p[i].trainID, p[i].location1, p[i].departHour, p[i].departMinute,
						p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);				//print the whole array with new values into the file
				}
				fclose(mptr);
			}
		}
		if (f == 0) {
			printf("No record found.....\n");
		}
		printf("\nAny more record to edit? ('N' no, 'C' continue): ");
		rewind(stdin);
		scanf("%c", &cont);

	}

	char choice;

	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu(log out), any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
	
}

void dlt() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                            DELETE SCHEDULE                             **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0, pos = 0;
	char dltId[25], confirm, cont;
	int f = 0;
	placeTime p[MAXSIZE];

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	fclose(ptr);					//read file into array 

	char show;
	printf("Do you want to see the records before deleting? ('S' to show): ");      //ask if the staff want to check array before running the function
	rewind(stdin);
	scanf("%c", &show);

	if (toupper(show) == 'S') {
		showSch();
	}

	printf("\nConfirm to delete? ('C' to confirm) ");     //prompt the staff to confirm deletion
	rewind(stdin);
	scanf("%c", &cont);
	
	while (toupper(cont) == 'C'){
		printf("Enter a train id to delete: ");				//find train id to delete
		rewind(stdin);
		scanf("%[^\n]", dltId);
		int length = strlen(dltId);
		for (int i = 0; i < length; i++) {
			dltId[i] = toupper(dltId[i]);
		}

		printf("\n==========================================================================================\n");
		printf("Train ID            Departure               Time               Arrival               Time");
		printf("\n==========================================================================================\n");


		for (int i = 0; i < found; i++) {
			if (strcmp(p[i].trainID, dltId) == 0) {
				pos = i;   //pos mean position of array of the record, pos is i now
				printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n", p[i].trainID, p[i].location1, p[i].departHour,
					p[i].departMinute, p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
				f++;
			}
		}															//show the searched record if found, then f++ to indicate something is found

		printf("------------------------------------------------------------------------------------------\n");
		printf("\t\t\t*Time display in 24hr-clock*\n\n");


		if (f != 0) {												//if f++, which mean there is record to delete, prompt the staff to delete
			printf("Are you sure you want to delete? (Y/N)\n");		
			rewind(stdin);
			scanf("%c", &confirm);

			if (toupper(confirm) == 'Y') {
				for (int j = pos; j < found - 1; j++) {
					p[j] = p[j + 1];							//remove the pos(which is the i th element of array) from array by putting the next value into pos
				}

				FILE* dptr;
				dptr = fopen("timetable.txt", "w");
				if (dptr == NULL) {
					printf("Error opening the file, please check the file name");
					exit(-1);
				}

				found--;      //found-- because one element is remove from array

				for (int i = 0; i < found; i++) {
					fprintf(dptr, "%s %s|%d|%d|%s|%d|%d|\n", p[i].trainID, p[i].location1, p[i].departHour, p[i].departMinute,
						p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);						//print the array into the file
				}

				fclose(dptr);
				printf("Delete successfully\n");
			}
		} else  {
			printf("No record found...\n");						//if f = 0, which mean nothing found, prompt staff to see existing records
			printf("Type 2 to show existing records:");
			int option;
			scanf("%d", &option);
			if (option == 2) {
				showSch();
			}
		}
		printf("Any more to delete(C to continue/N to leave)\n");
		rewind(stdin);
		scanf("%c", &cont);

		f = 0;
		
	} 
	
	char choice;

	printf("\n");									//back or quit
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu(log out), any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void backup() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                              BACKUP FILE                               **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");

	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	int found = 0;
	char bnr;
	placeTime p[MAXSIZE];
	SYSTEMTIME t;
	int day = 0, month = 0, year = 0, hour = 0, minute = 0;

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}																				//read file into array from timetable file to prepare for back up

	FILE* xptr;
	xptr = fopen("backup.txt", "r");
	if (xptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(xptr,"%d-%d-%d %02d:%02d\n", &day, &month, &year, &hour, &minute);

	printf("Last time back up: %d-%d-%d %02d:%02d\n", day, month, year, hour, minute);     //open back up file and prompt staff the last back up time
	printf("'B' to backup: ");
	rewind(stdin);
	scanf("%c", &bnr);										//read staff input
		
	fclose(xptr);

	if (toupper(bnr) == 'B') {								//run backup functions if input is true

		FILE* sptr;
		sptr = fopen("backup.txt", "w");
		if (sptr == NULL) {
			printf("Error opening the file, please check the file name");
			exit(-1);
		}

		GetLocalTime(&t);
		fprintf(sptr,"%d-%d-%d %02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);

		for (int i = 0; i < found; i++) {
			fprintf(sptr, "%s %s|%d|%d|%s|%d|%d|\n", p[i].trainID, p[i].location1, p[i].departHour, p[i].departMinute,
				p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
		}
		fclose(sptr);

		printf("Back up succesful\n\n");
		printf("\t\t\tBack up at %d-%d-%d %02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
	}

	char choice;			//back or quit

	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu(log out), any key to close program\n");
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void recover() {
	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                             FILE RECOVERY                              **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");

	FILE* rptr;
	rptr = fopen("backup.txt", "r");
	int found = 0;
	char recover;
	placeTime p[MAXSIZE];
	int day = 0, month = 0 , year = 0, hour = 0, minute = 0;

	if (rptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	fscanf(rptr, "%d-%d-%d %02d:%02d\n", &day, &month, &year, &hour, &minute);
	fscanf(rptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	while (!feof(rptr)) {
		found++;
		fscanf(rptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	if (found == 0) {
		printf("Nothing found, pls backup....\n");
	}

	fclose(rptr);						//read file from backup file and store it in array

	char cont;
	printf("Last time back up: %d-%d-%d %02d:%02d\n", day, month, year, hour, minute);
	printf("Are you sure you want to recover file? If you haven't back up, all the changes you've made on the file would be gone.\n");
	printf("Continue ? ('C') : ");								//prompt staff to continue functions or no
	rewind(stdin);
	scanf("%c", &cont);

	if (toupper(cont) == 'C') {

		printf("'R' to recover: ");
		rewind(stdin);
		scanf("%c", &recover);						//read input from staff to run function

		if (toupper(recover) == 'R') {

			FILE* sptr;
			sptr = fopen("timetable.txt", "w");
			if (sptr == NULL) {
				printf("Error opening the file, please check the file name");
				exit(-1);
			}

			for (int i = 0; i < found; i++) {
				fprintf(sptr, "%s %s|%d|%d|%s|%d|%d|\n", p[i].trainID, p[i].location1, p[i].departHour, p[i].departMinute,
					p[i].location2, p[i].arrivalHour, p[i].arrivalMinute);
			}																	//if input is true, print array read from backup file to timetable file
			fclose(sptr);

			printf("recover succesful\n");
		}
	}
	char choice;
	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu, any key to close program\n");    //back or quit
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void staffD_All() {
	FILE* ptr;
	ptr = fopen("timetable.txt", "r");
	placeTime p[MAXSIZE];
	int found = 0;

	if (ptr == NULL) {
		printf("Error opening the file, please check the file name");
		exit(-1);
	}

	printf("\n==========================================================================================\n");
	printf("Train ID            Departure               Time               Arrival               Time");
	printf("\n==========================================================================================\n");

	fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
		&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);

	while (!feof(ptr)) {
		found++;
		fscanf(ptr, "%s %[^|]|%d|%d|%[^|]|%d|%d|", &p[found].trainID, &p[found].location1, &p[found].departHour, &p[found].departMinute,
			&p[found].location2, &p[found].arrivalHour, &p[found].arrivalMinute);
	}

	for (int j = 0; j < found; j++) {
		printf("%-20s%-20s    %02d%02d               %-20s  %02d%02d\n", p[j].trainID, p[j].location1, p[j].departHour,
			p[j].departMinute, p[j].location2, p[j].arrivalHour, p[j].arrivalMinute);
	}

	printf("------------------------------------------------------------------------------------------\n");
	printf("\t\t\t**Time display in 24hr-clock**\n");

	printf("\n\n");
	fclose(ptr);															//read and display all records from file

	char choice;
	printf("\n");
	printf("\t\t\t\tType 'U' to back to previous page, 'Q' quit to main menu(log out), any key to close program\n");       //prompt staff to choice 
	rewind(stdin);
	scanf("%c", &choice);
	system("cls");

	choice = toupper(choice);

	switch (choice) {
	case 'U':
		staffMode();
	case 'Q':
		menu();
	default:
		system("pause");
	}
}

void staffMode() {
	int options;

	printf("\t\t\t\t__        _______ _     ____ ___  __  __ _____   ____ _____  _    _____ _____ \n");
	printf("\t\t\t\t\\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____| / ___|_   _|/ \\  |  ___|  ___|\n");
	printf("\t\t\t\t \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|   \\___ \\ | | / _ \\ | |_  | |_   \n");
	printf("\t\t\t\t  \\ V  V / | |___| |__| |__| |_| | |  | | |___   ___) || |/ ___ \\|  _| |  _|  \n");
	printf("\t\t\t\t   \\_/\\_/  |_____|_____\\____\\___/|_|  |_|_____| |____/ |_/_/   \\_\\_|   |_|    \n");

	printf("\t\t\t\t****************************************************************************\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t**                      WELCOME TO ADMINISTRATOR MODE                     **\n");
	printf("\t\t\t\t**                                                                        **\n");
	printf("\t\t\t\t****************************************************************************\n");
	printf("\n");
	printf("\t\t\t\t\t\t1 to add new schedule,\n");				//label functions for staff
	printf("\t\t\t\t\t\t2 to delete schedule,\n");
	printf("\t\t\t\t\t\t3 to modify schedule,\n");
	printf("\t\t\t\t\t\t4 to display all,\n");
	printf("\t\t\t\t\t\t5 to backup, \n");
	printf("\t\t\t\t\t\t6 to recover file,\n");
	printf("\t\t\t\t\t\t7 to log out\n");
	printf("Mode: ");
	rewind(stdin);
	scanf("%d", &options);					//read input from staff
	system("cls");

	switch (options) {						//enter functions based on input
	case 1:
		addSchedule();
		break;
	case 2:
		dlt();
		break;
	case 3:
		modify();
		break;
	case 4:
		staffD_All();
		break;
	case 5:
		backup();
		break;
	case 6:
		recover();
		break;
	case 7:
		menu();
		break;
	default:
		break;
	}

}

void staffLogin() {
	FILE* fptr;
	fptr = fopen("Staff.txt", "r");

	if (fptr == NULL) {
		printf("Error opening the file, please check the file name");    
		exit(-1);
	}

	char username[30], password[20];
	int choice = 0;

	fscanf(fptr, "%[^|]|%s", &lg.staffName, &lg.staffPw);			//read staff username and password from text file

	fclose(fptr);

	printf("\t\t\t***Please login to grant authorisation***\n");			//prompt user to login

	do {
		printf("Username: ");
		rewind(stdin);
		scanf("%[^\n]", &username);
		
		printf("Password: ");
		rewind(stdin);
		scanf("%[^\n]", &password);

		if (strcmp(username, lg.staffName) != 0 || strcmp(password, lg.staffPw) != 0) {    //validate user input with username and password read from file
			printf("Invalid username or password!!! Please enter again\n");
			printf("Type 1 to quit, 2 to continue trying.\n");	
			rewind(stdin);
			scanf("%d", &choice);

			if (choice == 1) {
				system("cls");
				menu();
			}
			else if (choice == 2) {
				printf("==========================\n");
				staffLogin();
			}
		}
		else if (strcmp(username, lg.staffName) == 0 && strcmp(password, lg.staffPw) == 0) {
			system("cls");
			staffMode();
		}

	} while (strcmp(username, lg.staffName) != 0 || strcmp(password, lg.staffPw) != 0);

}

//main menu

void menu() {
	int choice;
	printf("\t\t\t\t*********************************************************************************************\n");
	printf("\t\t\t\t\t   __        _______ _     ____ ___  __  __ _____   _____ ___                  \n");
	printf("\t\t\t\t\t   \\ \\      / / ____| |   / ___/ _ \\|  \\/  | ____| |_   _/ _ \\                 \n");
	printf("\t\t\t\t\t    \\ \\ /\\ / /|  _| | |  | |  | | | | |\\/| |  _|     | || | | |                \n");
	printf("\t\t\t\t\t     \\ V  V / | |___| |__| |__| |_| | |  | | |___    | || |_| |                \n");
	printf("\t\t\t\t\t    __\\_/\\_/__|_____|_____\\____\\___/|_|  |_|_____|   |_| \\___/                 \n");
	printf("\t\t\t\t\t   |_   _|  _ \\    / \\  |_ _| \\ | |                                            \n");
	printf("\t\t\t\t\t     | | | |_) |  / _ \\  | ||  \\| |                                            \n");
	printf("\t\t\t\t\t     | | |  _ <  / ___ \\ | || |\\  |                                            \n");
	printf("\t\t\t\t\t    _|_| |_|_\\_\\/_/ _ \\_\\___|_|_\\_|   _ _     _____   __  __  ___  ____  _____ \n");
	printf("\t\t\t\t\t   / ___| / ___| | | | ____|  _ \\| | | | |   | ____| |  \\/  |/ _ \\|  _ \\| ____|\n");
	printf("\t\t\t\t\t   \\___ \\| |   | |_| |  _| | | | | | | | |   |  _|   | |\\/| | | | | | | |  _|  \n");
	printf("\t\t\t\t\t    ___) | |___|  _  | |___| |_| | |_| | |___| |___  | |  | | |_| | |_| | |___ \n");
	printf("\t\t\t\t\t   |____/ \\____|_| |_|_____|____/ \\___/|_____|_____| |_|  |_|\\___/|____/|_____|\n\n");

	printf("\t\t\t\t*********************************************************************************************\n");

	printf("\t\t\t\t\t\tType 1 to enter User mode, 2 to enter Staff mode, any key to exit\n"); //let user choose which mode to enter
	printf("Mode: ");
	rewind(stdin);
	scanf("%d", &choice);
	system("cls");

	switch (choice) {
	case 1:
		userMode(); //for customer
		break;
	case 2:
		staffLogin(); //for staff, login to enter staff mode
		break;
	default:
		printf("Goodbye\n");
		system("pause");
		exit(-1);
	}
}

void main() {
	menu();
}