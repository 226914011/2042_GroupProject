//Group Project - Airplane Seating Assignment System Solution

//Include library
#include <iostream> //console input&output library
#include <fstream> //file input&output library
#include <string> //string library
#include <vector> //list library
#include <stdio.h> //file rename library
#include <iomanip> //output format library

//Include std 
using namespace std;

//Solution

//Function - Store data
void store(string data, string filename) {
	//declare variables
	char buffer[256];
	bool empty = true;

	//Create ifstream for read data in file
	ifstream infile;
	//Create ofstream for write data to file
	ofstream outfile;

	//Check if file is empty or not
	infile.open(filename, fstream::in);
	if (infile.getline(buffer, 100)) {
		empty = false;
	}
	infile.close();

	//If not empty, create a newline and write data
	//If empty, only write data
	outfile.open(filename, fstream::out | fstream::app);
	if (!empty) {
		outfile << "\n";
	}
	outfile << data;
	outfile.close();
	outfile.clear();
}


//Function - Read file data
//Data format return in vector
vector<string> readfile() {
	//declare variables
	string filename = "Client_data.txt";
	string buffer;
	vector<string> data = {};

	//Create ifstream for read data in file
	ifstream infile;

	//Get data in each line and add to vector
	infile.open(filename, ifstream::in);
	while (getline(infile, buffer)) {
		data.push_back(buffer);
	}

	//Returning data in vector
	return data;
}
//Please use following commands to get string in each line
/*
for(auto str : readfile()){
	cout << str << endl;
}
*/

//Function - Split string by delimiter
//Data format return in array
string* split(string s) {
	//declare variables
	string delimiter = "/";
	string* data = new string[3];
	size_t pos = 0;
	string buffer;

	//Split	words by using delimiter and add to array
	int counter = 0;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		buffer = s.substr(0, pos);
		data[counter] = buffer;
		s.erase(0, pos + delimiter.length());
		counter++;
	}
	data[counter] = s;

	//Returning data in array
	return data;
}
//Please use following commands to get strings in each line
/*
vector<string> buffer = split(data);
*/

//Function - Delete data
void Delete(string name, string ID) {
	//Declare variables
	string confirm;
	bool detected = false, erased = false;
	vector<string> data = {};

	string* buffer2 = new string[3];

	//Get data from file
	for (auto buffer : readfile()) {
		buffer2 = split(buffer);
		// buffer2[0] = Name , buffer2[1] = ID , buffer2[2] = seat

		//Check if name and ID both match record in Client_data.txt
		if ((buffer2[0] == name) && (buffer2[1] == ID)) {

			//Action for record found
			while (true) {
				cout << endl;
				cout << "Record found. Are you sure you want to delete it?" << endl;
				cout << "Input \"Confirm\" to confirm or \"c\" to cancel." << endl;
				cin >> confirm;
				cout << endl;
				if (confirm == "Confirm") {
					cout << "Data Deleted!" << endl;
					detected = true;
					erased = true;
					goto erase;
				}
				else if (confirm == "c") {
					cout << "Delete action has been canceled!" << endl;
					detected = true;
					goto cancelled;
				}
				else {
					cout << "Error : Invalid input. Try again." << endl;
				}
			}
		}
		data.push_back(buffer);

		//Jump out of the while loop if user delete data
	erase:;
	}
	//Indicate data not match
	if (!detected || !erased) {
		cout << "No match detected!" << endl;
	}

	//If data match and deleted, overwrite Client_data.txt with new data
	if (erased) {
		for (auto str : data) {
			store(str, "temp.txt");
		}
		remove("Client_data.txt");
		rename("temp.txt", "Client_data.txt");
		cout << "Data file has been updated!" << endl;
	}
cancelled:;
}

//Function1 - Add an assignment
void F1() {
	//declare variables
	string name, ID, seat, str, data, parameter = { "ABCDEF" }, back;
	const string AZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//Main loop
	do {
		//Clear input cache
		name = "\n";
		getline(cin, name);

		//Input name,ID and seat
		cout << "Input your name(e.g.\"Chan Tai Man\"): ";
		getline(cin, name);
		cout << "Input your passport ID(All upper case, e.g.\"HK12345678A\"): ";
		cin >> ID;
		cout << "Input your desired seat location(e.g.\"10D\"): ";
		cin >> seat;


		//Data validity check for seat
		try {
			int buff2 = stoi(seat.substr(0, seat.size() - 1));
			if ((buff2 < 0) || (buff2 > 14) || parameter.find(seat.substr(seat.size() - 1, seat.size())) == string::npos) {
				cout << "Error: Your seat is invalid. Please try again." << endl;
				cout << "The Format of the seat location should be\"RowColumn\" and without space." << endl;
				cout << "The row should be between 1-13." << endl;
				cout << "The colum shoulb be between A-F." << endl;
				goto fail;
			}
			//Catch expection
		}
		catch (...) {
			cout << "Error: Your seat is invalid. Please try again." << endl;
			cout << "The Format of the seat location should be\"RowColumn\" and without space." << endl;
			cout << "The row should be between 1-13." << endl;
			cout << "The colum shoulb be between A-F." << endl;
			goto fail;
		}

		/*
		//Unactivate
		//This validity check need to depend on ID, please check ID format b4 activate
		//Data validity check for ID
		try{
			//Check if first two letter is "HK" or not
			//Check if the last letter is in A-Z range or not
			//And check if the 3-9char is number or not
			if(ID.substr(0,2)!="HK"|AZ.find(ID.substr(10,11))==string::npos|AZ.find(ID.substr(3,9))!=string::npos){
				cout << "Error: Your ID is invalid. Please try again." << endl;
				goto fail;
			}
		//Catch expection if ID < length 11
		}catch(...){
			cout << "Error: Your ID is invalid. Please try again." << endl;
			goto fail;
		}
		*/

		//Check if any data exist in data file
		if (readfile().size() == 0) {
			goto file_not_exist;
		}

		//Inport data from data file
		for (auto str : readfile()) {
			string* buffer2 = new string[3];
			buffer2 = split(str);
			// buffer2[0] = Name , buffer2[1] = ID , buffer2[2] = Seat

			//Check if user's name have booked
			if (buffer2[0] == name) {
				cout << "Error: You have booked for name: " << name << "." << endl;
				cout << "Error: Please try again." << endl;
				goto fail;

				//Check if user's ID have booked
			}
			else if (buffer2[1] == ID) {
				cout << "Error: You have booked for ID:" << ID << "." << endl;
				cout << "Error: Please try again." << endl;
				goto fail;

				//Check if sear have booked
			}
			else if (buffer2[2] == seat) {
				cout << "Error: The seat: " << seat << " has been obtained." << endl;
				cout << "Error: Please choose another one." << endl;
				goto fail;
			}
		}

		//Bypass the for loop if there is not data file to prevent error
	file_not_exist:;

		//Store data and indicate book success
		store(name + "/" + ID + "/" + seat, "Client_data.txt");
		cout << endl << "You have booked successfully for seat " << seat << "." << endl;
		system("pause");
		break;

		//Bypass Store function if found data match in data file
	fail:;
	} while (true);
}

//Function2 - Delete an assignment
void F2() {
	//declare variables
	string name, ID;

	//Clear input cache
	name = "\n";
	getline(cin, name);

	//Input name,ID
	cout << "Input your name(e.g.\"Chan Tai Man\"): ";
	getline(cin, name);
	cout << name;
	cout << "Input your passport ID(All upper case, e.g.\"HK12345678A\"): ";
	cin >> ID;

	//Delete data if match
	Delete(name, ID);
	system("pause");
}

//Function3 - Add assignments in batch
void F3() {
	//declare variables
	string input;
	vector<string> data = {};
	vector<string> suces = {};
	vector<string> fail = {};

	//Clear input cache
	input = "\n";
	getline(cin, input);

	//Input name, ID and seat in the specified format
	cout << "Please input in \"Name/PassportID/Seat\" or \"0\" to end input:" << endl;
	getline(cin, input);
	while (input != "0") {
		data.push_back(input);
		getline(cin, input);
	}
	cout << endl;

	//Store data for data in vector
	for (auto buffer : data) {
		//declare variables
		bool sucess = true;
		string* buffer1 = split(buffer);

		//Check if any data exist in data file
		if (readfile().size() == 0) {
			goto file_not_exist;
		}

		//Get data to check
		for (auto str : readfile()) {
			string* buffer2 = split(str);

			//Check if found data match in data file
			if (buffer1[0] == buffer2[0] || buffer1[1] == buffer2[1] || buffer1[2] == buffer2[2]) {
				sucess = false;
			}
		}
		//Bypass the for loop if there is not data file to prevent error
	file_not_exist:;

		//Store success and fail cases
		if (sucess) {
			suces.push_back(buffer);
			store(buffer, "Client_data.txt");
		}
		else {
			fail.push_back(buffer);
		}

	}

	//Display success case list
	if (!suces.empty()) {
		cout << "Successful requests:" << endl;
		for (auto buffer3 : suces) {
			cout << buffer3 << endl;
		}
		cout << endl;
	}

	//Display fail case list
	if (!fail.empty()) {
		cout << "Unsuccessful requests:" << endl;
		for (auto buffer4 : fail) {
			cout << buffer4 << endl;
		}
		cout << endl;
	}

	system("pause");
}

//Function4 - Show latest seating plan
void F4() {
	//declare variables
	vector<string> AZ = { "A","B","C","D","E","F" };
	string buff;

	//Display the first line
	cout << setw(5) << " ";
	for (auto header : AZ) {
		cout << setw(5) << header;
	}cout << endl;

	//Display the seating plan by loop
	for (int numb = 1; numb < 14; numb++) {
		cout << setw(5) << numb;
		for (int count = 0; count < 6; count++) {
			for (auto string1 : readfile()) {
				//Check user's seat match current seat or not
				if (to_string(numb) + AZ[count] == split(string1)[2]) {
					cout << setw(5) << "X";
					goto X;
				}
			}
			//Default output for non occupied seat
			cout << setw(5) << "*";


		X:;
		}
		cout << endl;
	}
	system("pause");
}

//Function5_1 - Show Passenger details
void F5_1() {
	//declare variables
	string ID;
	int buff2 = 0;

	//Input ID
	cout << "Input your passport ID(All upper case, e.g.\"HK12345678A\"): ";
	cin >> ID;

	//Get data to check
	for (auto buff1 : readfile()) {

		//Display match data
		if (ID == split(buff1)[1]) {
			cout << "Name: " << split(buff1)[0] << endl;
			cout << "ID: " << split(buff1)[1] << endl;

			cout << "Ticket class: ";
			buff2 = stoi(split(buff1)[2].substr(0, split(buff1)[2].size() - 1));
			if (buff2 < 3) {
				cout << "First";
			}
			else if (buff2 < 8) {
				cout << "Business";
			}
			else {
				cout << "Economy";
			}
			cout << endl;
			cout << "Seat: " << split(buff1)[2] << endl;
			goto end_loop;
		}
	}
	//Indicate no matchs found
	cout << "Error: No matchs found!";

	//Jump out of the for loop if matchs
end_loop:;
	cout << endl;

	system("pause");
}

//Function5_2 - Show Class details
void F5_2() {
	//declare variables
	string Class, buff2;
	vector<string> AZ = { "A","B","C","D","E","F" };
	int class1, class2;

	//Input class
	cout << "Input Class(e.g. \"First\", \"Business\", \"Economy\") : ";
	cin >> Class;

	//Check which class match and set parameter
	if (Class == "First" || Class == "first") {
		class1 = 1;
		class2 = 3;
	}
	else if (Class == "Business" || Class == "business") {
		class1 = 3;
		class2 = 8;
	}
	else if (Class == "Economy" || Class == "economy") {
		class1 = 8;
		class2 = 14;
	}
	else {
		cout << "Error: Invalid Class" << endl;
		cout << "Class should be \"First\", \"Business\", or \"Economy\"? " << endl;
		goto failed;
	}

	//Display Class details
	for (int l = class1; l < class2; l++) {
		for (auto o : AZ) {
			//declare variables
			bool occupied = false;
			cout << setw(2) << l << o << ": ";

			//get data
			for (auto buff1 : readfile()) {
				buff2 = to_string(l) + o;

				//Check if seat is occupied or not
				if (split(buff1)[2] == buff2) {
					occupied = true;
					//Display name if occupied
					cout << split(buff1)[0] << endl;
				}
			}
			//Display vacant if not occupied
			if (!occupied) {
				cout << "vacant" << endl;
			}
		}
	}
failed:
	cout << endl;
	system("pause");
	system("cls");
}

//Function5 - Show details Main Menu
void F5() {
	char sub_prog_choice;
	do {	//Main Menu
		cout << "\n\n";
		cout << "*** Details ***" << endl;
		cout << "[1] Passenger" << endl;
		cout << "[2] Class" << endl;
		cout << "[3] Back" << endl;
		cout << "*****************" << endl;
		cout << "Option (1-3): ";
		cin >> sub_prog_choice;
		cout << "\n\n";

		//Choose Function
		switch (sub_prog_choice) {
		case '1': F5_1(); break;
		case '2': F5_2(); break;
		case '3': break;
		default:
			//Indicate error
			cout << "Error: No such function " << sub_prog_choice << endl;
			continue;
		}
	} while (sub_prog_choice != '3');
	cout << endl << "Exitting." << endl;
}

//Main Function
int main()
{	//Declare variable
	char prog_choice;

	do {	//Main Menu
		cout << "\n\n";
		cout << "Welcome to HKCC Airplane Seating Assignment System!" << endl;
		cout << "*** main menu ***" << endl;
		cout << "[1] Add an assignment" << endl;
		cout << "[2] Delete an assignment" << endl;
		cout << "[3] Add assignments in batch" << endl;
		cout << "[4] Show latest seating plan" << endl;
		cout << "[5] Show details" << endl;
		cout << "[6] Exit" << endl;
		cout << "*****************" << endl;
		cout << "Option (1-6): ";
		cin >> prog_choice;
		cout << "\n";

		//Choose Function
		switch (prog_choice) {
		case '1': F1(); break;
		case '2': F2(); break;
		case '3': F3(); break;
		case '4': F4(); break;
		case '5': F5(); break;
		case '6': break;
		default:
			//Indicate error
			cout << "Error: No such function " << prog_choice << endl;
			continue;
		}

		//Exit parameter
	} while (prog_choice != '6');

	//Exit programe
	cout << "System terminates. Good bye!" << endl;
	return 0;
}
