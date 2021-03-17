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
	string name,ID,seat,str,data,parameter = {"ABCDEF"},back;
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

		//Data validity check for seat
		try{
			int buff2 = stoi(seat.substr(0, seat.size()-1));
			back = seat.substr(seat.size()-1,seat.size());
			if((buff2<0) && (buff2>14) && false){
				cout << "Error: Your seat is invalid. Please try again." << endl;
				goto fail;
			}
			//(parameter.find(back) == string::npos)
		//Catch expection
		}catch(...){
			cout << "Error: Your seat is invalid. Please try again." << endl;
			goto fail;
		}

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
			vector<string> buffer2 = split(str);
        	// buffer2[0] = Name , buffer2[1] = ID , buffer2[2] = seat

			//Check if user's name have booked
			if(buffer2[0]== name){
				cout << "Error: You have booked for name: "<< name <<"." << endl;
				cout << "Error: Please try again." << endl;
				goto fail;

			//Check if user's ID have booked
			}else if(buffer2[1] == ID){
				cout << "Error: You have booked for ID:"<< ID <<"." << endl;
				cout << "Error: Please try again." << endl;
				goto fail;

			//Check if sear have booked
			}else if(buffer2[2] == seat){
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
    //declare 3 string
	string input;
    vector<string> data = {};
    vector<string> suces = {};
    vector<string> fail = {};

    //Clear input cache
    input="\n";
    getline(cin,input);
    
    //Input name,ID and seat
    cout << "Please input in \"Name/PassportID/Seat\" or \"0\" to end input:" << endl;
    getline(cin,input);
    while(input!= "0"){
        data.push_back(input);
        getline(cin,input);
    }
    cout << endl;
    //
    for(auto buffer : data){
        bool sucess = true;
        vector<string> buffer1 = split(buffer);
        for(auto str : readfile()){
			vector<string> buffer2 = split(str);
            //Check if 
			if(buffer1[0]== buffer2[0] || buffer1[1]== buffer2[1] || buffer1[2]== buffer2[2]){
                sucess = false;
            }
        }
        if(sucess){
            suces.push_back(buffer);
            store(buffer,"Client_data.txt");
        }else{
            fail.push_back(buffer);
        }

    }
    if(!suces.empty()){
        cout << "Successful requests:" << endl;
        for(auto buffer3 : suces){
            cout << buffer3 << endl;
        }
        cout << endl;
    }
    if(!fail.empty()){
        cout << "Unsuccessful requests:" << endl;
        for(auto buffer4 : fail){
            cout << buffer4 << endl;
        }
        cout << endl;
    }
	system("pause");
}

//Function4 - Show latest seating plan
void F4(){
	vector<string> AZ = {"A","B","C","D","E","F"};
    string buff;
    cout << setw(5) << " ";
    for(auto header : AZ){
        cout << setw(5) << header;
    }cout << endl;
    for(int numb = 1;numb < 14;numb++){
        cout << setw(5) << numb;
        for(int count = 0; count < 6; count++){
            for(auto string1 : readfile()){
                if(to_string(numb)+AZ[count]==split(string1)[2]){
                    cout << setw(5) << "X";
                    goto X;
                }
            }
            cout << setw(5) << "*";
            X:;
        }
        cout << endl;
    }
	system("pause");
}

//Function5_1 - Show Passenger details
void F5_1(){   
    string ID;
	int buff2 = 0;

	cout << "Input your passport ID(e.g.\"HK12345678A\"): ";
	cin >> ID;

	for(auto buff1 : readfile()){
		if(ID == split(buff1)[1]){
			cout << "Name: " << split(buff1)[0] << endl;
			cout << "ID: " << split(buff1)[1] << endl;
			
			cout << "Ticket class: ";
			buff2 = stoi(split(buff1)[2].substr(0, split(buff1)[2].size()-1));
			if(buff2 < 3){
				cout << "First";
			}else if(buff2 < 8){
				cout << "Business";
			}else{
				cout << "Economy";
			}
			cout << endl;

			cout << "Seat: " << split(buff1)[2] << endl;
            goto end_loop;
        }
	}
    cout << "Error: Invalid ID";
    end_loop:;
	cout << endl;

	system("pause");
}

//Function5_2 - Show Class details
void F5_2(){
	string Class,buff2;
    vector<string> AZ = {"A","B","C","D","E","F"};
    int class1,class2;

	cout << "Input Class: ";
	cin >> Class;
    if(Class == "First"){
        class1 = 1;
        class2 = 3;
    }else if(Class == "Business"){
        class1 = 3;
        class2 = 8;
    }else if(Class == "Economy"){
        class1 = 8;
        class2 = 14;
    }

    for(int l= class1;l < class2;l++){
        for(auto o: AZ){
            bool occupied = false;
            cout << l << o << ": ";
            for(auto buff1 : readfile()){
                buff2 = to_string(l)+o;
                if(split(buff1)[2] == buff2){
                    occupied = true;
                    cout << split(buff1)[0] << endl;
                }
            }
            if(!occupied){
            cout << "vacant" << endl;
            }
        }
    }
    cout << endl;
	system("pause");
}

//Function5 - Show details Main Menu
void F5(){
	char sub_prog_choice;
	do{	//Main Menu
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
	}while (sub_prog_choice != '3');
	cout << endl << "Exitting." << endl;
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