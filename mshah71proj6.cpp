#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Classes.h"
class TravelNetwork
{
private:
	// Create the Data Members for the Travel Network here
	Airport* All_airports;
	int CAPACITY;
	int carrCAP;
	char** filearr;
public:
	// Use a constructor to initialize the Data Members for Travel Network
	TravelNetwork()
	{
		CAPACITY = 10;
		carrCAP = 1;
		All_airports = new Airport[CAPACITY];
		filearr = (char**)malloc((carrCAP)*sizeof(char*));
		
	}

	TravelNetwork(int newCAPACITY)
	{
		CAPACITY = newCAPACITY;
		 All_airports = (Airport*)malloc((CAPACITY) * sizeof(Airport));
	}
	void grow() {
		printf("growing file array\n");
		char **temp;
		temp = (char**)malloc((carrCAP * 2) * sizeof(char*));
		int i;
		for (i = 0; i < carrCAP; i++)
		temp[i] = filearr[i];
		free (filearr);
		filearr = temp;
		carrCAP = carrCAP * 2;		
	}

	void Free_TN() {
		printf("freeing airports ");
		for (int i = 0; i < CAPACITY; i++) {
			Airport temp = All_airports[i];
			printf(" %d", i + 1);
			temp.Airport_free();
		}
		printf("\n");
		delete(All_airports);
		CAPACITY = 0;
		All_airports = NULL;
	}

	void Free_filearr(){
		free(filearr);
		filearr = NULL;
	}
	

	void List_TN() {
		for (int i = 0; i < CAPACITY; i++) {
			Airport temp = All_airports[i];
			printf("Airports which can be reached from Airport %d directly\n", i + 1);
			temp.printnetwork();
		}
	}

	bool dfs(int a, int b) {
		//printf("current x:%d current y:%d \n", a, b);
		Airport temp1 = All_airports[a - 1];
		Mylist* c = temp1.getlistp();
		MyNODE* p = c->gethead();
		
		while(p) {
			//Airport temp2 = All_airports[p->getkey() - 1];
			//temp2.printnetwork();
			if (p->getkey() == b) { return true; }
			//printf("airport %d is  visited? %d\n", p->getkey(), temp2.getVISITED());
			if (All_airports[p->getkey() - 1].getVISITED()==false) {
				All_airports[p->getkey() - 1].T_VISITED();
				//printf("not implimented\n"); return false;
				//printf("\nairport %d is now marked as visited -------%d\n", p->getkey(), temp2.getVISITED());
				if (dfs(p->getkey(), b) == true) {
					return true;
				}
			}
			p = p->getNextp();
		}
		return false;
	}

	void DepthfirstsearchH(int x, int y) {
		for (int i = 0; i < CAPACITY; i++) {All_airports[i].F_VISITED();}
		
		if (dfs(x, y)) {
			printf("you can get from airport %d to airport %d in one or more flights\n",x,y);
		}
		else{ printf("you can't get from airport %d to airport %d in one or more flights\n", x, y); }
		
	}

	// The main loop for reading in input
	void processCommandLoop(FILE* inFile)
	{
		char  buffer[300];
		char* input;

		input = fgets(buffer, 300, inFile);   // get a line of input

											  // loop until all lines are read from the input
		while (input != NULL)
		{
			// process each line of input using the strtok functions 
			char* command;
			command = strtok(input, " \n\t");

			printf("*%s*\n", command);

			if (command == NULL)
				printf("Blank Line\n");

			else if (strcmp(command, "q") == 0)
				exit(1);

			else if (strcmp(command, "?") == 0)
				showCommands();

			else if (strcmp(command, "t") == 0)
				doTravel();

			else if (strcmp(command, "r") == 0)
				doResize();

			else if (strcmp(command, "i") == 0)
				doInsert();

			else if (strcmp(command, "d") == 0)
				doDelete();

			else if (strcmp(command, "l") == 0)
				doList();

			else if (strcmp(command, "f") == 0)
				doFile();

			else if (strcmp(command, "#") == 0)
				;

			else
				printf("Command is not known: %s\n", command);

			input = fgets(buffer, 300, inFile);   // get the next line of input

		}
	}

	void showCommands()
	{
		printf("The commands for this project are:\n");
		printf("  q \n");
		printf("  ? \n");
		printf("  # \n");
		printf("  t <int1> <int2> \n");
		printf("  r <int> \n");
		printf("  i <int1> <int2> \n");
		printf("  d <int1> <int2> \n");
		printf("  l \n");
		printf("  f <filename> \n");
	}

	void doTravel()
	{	
		int val1 = 0;
		int val2 = 0;

		// get an integer value from the input
		char* next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val1 = atoi(next);
		if (val1 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}

		// get another integer value from the input
		next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val2 = atoi(next);
		if (val2 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}

		if (val2 > CAPACITY || val1 > CAPACITY) { printf("Not valid input\n"); return; }
		if (val2 < 1 || val1 < 1) { printf("Not valid input\n");  return; }
		printf("Performing the Travel Command from %d to %d\n",
			val1, val2);
		DepthfirstsearchH(val1, val2);
		return;
	}

	void doResize()
	{
		int val1 = 0;
		// get an integer value from the input
		char* next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val1 = atoi(next);
		if (val1 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}
		printf("Performing the Resize Command with %d\n", val1);
		Free_TN();
		CAPACITY = val1;
		All_airports = new Airport[CAPACITY];
		printf("printing travelnetwork for check on resize\n");
		List_TN();
	}

	void doInsert()
	{
		int val1 = 0;
		int val2 = 0;

		// get an integer value from the input
		char* next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val1 = atoi(next);
		if (val1 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}

		// get another integer value from the input
		next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val2 = atoi(next);
		if (val2 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}

		if (val2 > CAPACITY || val1 > CAPACITY) { printf("Not valid input\n"); return; }
		if (val2 < 1 || val1 < 1) { printf("Not valid input\n");  return; }
		printf("creating edge from %d to %d\n",
			val1, val2);
		for (int i = 0; i < CAPACITY; i++) {
			Airport temp = All_airports[i];
			if (i+1 == val1) { temp.insert_edge(val2); return; }
		}
	}

	void doDelete()
	{
		int val1 = 0;
		int val2 = 0;

		// get an integer value from the input
		char* next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val1 = atoi(next);
		if (val1 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}

		// get another integer value from the input
		next = strtok(NULL, " \n\t");
		if (next == NULL)
		{
			printf("Integer value expected\n");
			return;
		}
		val2 = atoi(next);
		if (val2 == 0 && strcmp(next, "0") != 0)
		{
			printf("Integer value expected\n");
			return;
		}


		printf("deleting edge from %d to %d\n",
			val1, val2);
		if (val2 > CAPACITY || val1 > CAPACITY) { printf("Not valid input\n"); return; }
		if (val2 < 1 || val1 < 1) { printf("Not valid input\n");  return; }
		for (int i = 0; i < CAPACITY; i++) {
			Airport temp = All_airports[i];
			//printf("Airports which can be reached from Airport %d directly\n", i + 1);
			if (i+1 == val1) { temp.del_edge(val2); return; }
		}
	}

	void doList()
	{
		List_TN();
	}

	void doFile()
	{
		
		// get a filename from the input
		char* fname = strtok(NULL, " \n\t");
		if (fname == NULL)
		{
			printf("Filename expected\n");
			return;
		}

		printf("Performing the File command with file: %s\n", fname);
		int x = 0;
		int i = 0;
		for ( i = 0; i < carrCAP+1; i++) {
			if (i == carrCAP) { grow(); }
			if (filearr[i] != NULL && strcmp(filearr[i], fname) == 0) { x = 0; printf("file has already been opened\n"); break; }
			if (filearr[i] == NULL) { x = 1; filearr[i] = fname; break; }
		}
		if(x){	FILE* newfile= fopen(fname, "r");
				processCommandLoop(newfile);
				fclose(newfile);
				if (strcmp(filearr[i], fname) == 0) {filearr[i] = NULL;}
		}
		// next steps:  (if any step fails: print an error message and return ) 
		//  1. verify the file name is not currently in use
		//  2. open the file using fopen creating a new instance of FILE*
		//  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
		//  4. close the file when processCommandLoop() returns
	}
};

int main(int argc, char** argv)
{	
	

	// set up the variable inFile to read from standard input
	FILE* inFile = stdin;

	// set up the data needed for the airport adjcency list
	TravelNetwork airportData;
	// call the method that reads and parses the input
	airportData.processCommandLoop(inFile);
	//airportData.List_TN();
	airportData.Free_TN();
	airportData.Free_filearr();
	
	printf("Goodbye\n");
	return 1;
}