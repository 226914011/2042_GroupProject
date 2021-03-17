//Group Project - Airplane Seating Assignment System Solution

//Include library
#include <iostream> //console input&output library
#include <fstream> //file input&output library
#include <string> //string library
#include <vector> //list library
#include <stdio.h> //file rename library

//Include std 
using namespace std;

//Solution

//Function - Store data
void store(string data,string filename){
	char buffer[256];
	fstream filetoworkwith;
    
	filetoworkwith.open(filename, fstream::in | fstream::out | fstream::app);
	if(filetoworkwith.getline(buffer, 100)){
        filetoworkwith << "\n";
    }
	
    //Fix for write error if file is empty
    if(!filetoworkwith){
        filetoworkwith.close();
    filetoworkwith.open(filename,fstream::out | fstream::app);
    }
	filetoworkwith << data;
	filetoworkwith.close();
	filetoworkwith.clear();
}


//Function - Read file data
//Data format return in vector
vector<string> readfile(){
	string filename = "Client_data.txt";
	string buffer;
	vector<string> data = {};
	fstream filetoworkwith;
	filetoworkwith.open(filename, fstream::in );
	while (getline(filetoworkwith,buffer)) {
		data.push_back(buffer);
	}
	return data;
}
//Please use following commands to get string in each line
/*
for(auto str : readfile()){
	cout << str << endl;
}
*/

//Function - Split string by delimiter
//Data format return in vector
vector<string> split(string s){
    string delimiter = "/";
    vector<string> data;
    size_t pos = 0;
    string buffer;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        buffer = s.substr(0, pos);
        data.push_back(buffer);
        s.erase(0, pos + delimiter.length());
    }
    data.push_back(s);
    return data;
}
//Please use following commands to get strings in each line
/*
vector<string> buffer = split(data);
*/

//Function - Delete data
void Delete(string name,string ID){
    //Declare variables
    string confirm;
    bool detected = false , erased = false;
    vector<string> data = {};
    vector<string> buffer2 = {};

	for (auto buffer : readfile()) {
        vector<string> buffer2 = split(buffer);
        // buffer2[0] = Name , buffer2[1] = ID , buffer2[2] = seat
        if((buffer2[0]== name) && (buffer2[1] == ID)){
            while(true){
                cout << endl;
                cout << "Record found. Are you sure you want to delete it?" << endl;
                cout << "Input \"Confirm\" to confirm or \"c\" to cancel." << endl;
                cin >> confirm;
				cout << endl;
                if(confirm=="Confirm"){
                    cout << "Data Deleted!"<< endl;
                    detected = true;
                    erased = true;
                    goto erase;
                }else if(confirm=="c"){
                    cout << "Delete action has been canceled!"<< endl;
                    detected = true;
                }else{
                    cout << "Error : Invalid input. Try again."<< endl;
                }
            }
        }
        data.push_back(buffer);
        erase:;
	}
    if(!detected || !erased){
        cout << "No match detected!"<< endl;
    }
    if(erased){
        for (auto str : data){
            store(str,"temp.txt");
        }
        remove( "Client_data.txt" );
        rename("temp.txt", "Client_data.txt");
        cout << "Data file has been updated!" << endl;
    }

}

//Function1 - Add an assignment
void F1(){
	//declare 3 string
	string name,ID,seat,str,data;
	const string AZ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//Main loop
	do{
		//Clear input cache
		name="\n";
		getline(cin,name);

		//Input name,ID and seat
		cout << "Input your name(e.g.\"Chan Tai Man\"): ";
		getline(cin,name);
		cout << "Input your passport ID(e.g.\"HK12345678A\"): ";
		cin >> ID;
		cout << "Input your desired seat location(e.g.\"10D\"): ";
		cin >> seat;

		/*
		//Data validity check for seat
		try{
			//Unfinished
			if(AZ.find(seat.substr(2))==string::npos|AZ.find(seat.substr(0,2))!=string::npos){
				cout << "Error: Your seat is invalid. Please try again." << endl;
				goto fail;
			}
		//Catch expection
		}catch(...){
			cout << "Error: Your seat is invalid. Please try again." << endl;
			goto fail;
		}
		*/

		/* This validity check need to depend on ID, please check ID format b4 activate
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
		if(readfile().size()==0){
			goto file_not_exist;
		}

		//Inport data from data file
		for(auto str : readfile()){
			//Check if user's name have booked
			if(str.find(name)!=string::npos){
				cout << "Error: You have booked for name: "<< name <<". Please try again." << endl;
				goto fail;

			//Check if user's ID have booked
			}else if(str.find(ID)!=string::npos){
				cout << "Error: You have booked for ID:"<< ID <<". Please try again." << endl;
				cout << str.find(ID);
				goto fail;

			//Check if sear have booked
			}else if(str.find(seat)!=string::npos){
				cout << "Error: The seat: "<< seat<<" has been obtained." << endl;
				cout << "Error: Please choose another one." << endl;
				goto fail;
			}
		}
		file_not_exist:;

		//Store data and indicate book success
		store(name + "/" + ID + "/" + seat,"Client_data.txt");
		cout << endl <<"You have booked successfully for seat "<< seat << "." << endl;
		system("pause");
		break;

		fail:;
	}while(true);
}

//Function2 - Delete an assignment
void F2(){
	//declare 3 string
	string name,ID;

    //Clear input cache
    name="\n";
    getline(cin,name);
    
    //Input name,ID and seat
    cout << "Input your name(e.g.\"Chan Tai Man\"): ";
    getline(cin,name);
    cout << name;
    cout << "Input your passport ID(e.g.\"HK12345678A\"): ";
    cin >> ID;
    Delete(name,ID);
	system("pause");
}

//Function3 - Add assignments in batch
void F3(){

	system("pause");
}

//Function4 - Show latest seating plan
void F4(){
	system("pause");
}

//Function5 - Show details
void F5(){
	int sub_prog_choice;
	cout << "\n\n";
	cout << "*** Details ***" << endl;
	cout << "[1] Passenger" << endl;
	cout << "[2] Class" << endl;
	cout << "[3] Back" << endl;
	cout << "*****************" << endl;
	cout << "Option (1-3): ";
	cin >> sub_prog_choice;
	cout << "\n\n";
	system("pause");
}

//Main Function
int main() 
{	//Declare variable
    char prog_choice;

	do{	//Main Menu
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
	}while (prog_choice != '6');
	
	//Exit programe
	cout << "System terminates. Good bye!" << endl;
	return 0;
}