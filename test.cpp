//Group Project - Airplane Seating Assignment System Solution

//Include library
#include <iostream> //console input&output library
#include <fstream> //file input&output library
#include <string> //string library
#include <vector> //list library
#include <stdio.h> //file rename library
#include <cstring> //split string library
#include <typeinfo> //debug library

//Include std 
using namespace std;

//Solution

//Function - Read file data
vector<string> readfile(){
    string filename = "Client_data.txt";
    string buffer;
    vector<string> data;
    fstream filetoworkwith;
    filetoworkwith.open(filename, fstream::in );
	while (getline(filetoworkwith,buffer)) {
		data.push_back(buffer);
	}
    return data;
}

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

//Function - Store data
void store(string data,string filename){
	char buffer[256];
	fstream filetoworkwith;
	filetoworkwith.open(filename, fstream::in | fstream::out | fstream::app);
	if(filetoworkwith.getline(buffer, 100)){
		cout << "Not empty." << endl;
        filetoworkwith << "\n";
	}else{
        cout << "Empty." << endl;
        filetoworkwith << "foobar";
        filetoworkwith.flush();
    }
    cout << (!filetoworkwith) << endl;
	filetoworkwith << data;
	filetoworkwith.close();
	filetoworkwith.clear();
}

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
        /*
        remove( "Client_data.txt" );
        rename("temp.txt", "Client_data.txt");
        */
        cout << "Data file has been updated!" << endl;
    }

}


int main() 
{   //declare 3 string
	string name,ID;

    //Clear input cache
    name="\n";
    getline(cin,name);
    
    //Input name,ID and seat
    cout << "Input your name(e.g.\"Chan Tai Man\"): ";
    getline(cin,name);
    cout << "Input your passport ID(e.g.\"HK12345678A\"): ";
    cin >> ID;
    Delete(name,ID);
    system("pause");
}



/*
//Write data
string data_buffer;
string data[][3] = {{"Chan Tai Man","HK12345678A","10D"},{"Pan Peter","US2356AAD11","2E"},{"Chu Mimi","ER273","1A"}}; 
int rows = (sizeof(data)/sizeof(data[0]));
int cols = (sizeof(data[0])/sizeof(string));
for(int i=0;i<rows;i++){
    data_buffer = "";
    for(int j=0;j<cols;j++){
        data_buffer.append(data[i][j]);
        if(j < 2){
            data_buffer.append("/"");
        }
    }
    store(data_buffer);
}
*/