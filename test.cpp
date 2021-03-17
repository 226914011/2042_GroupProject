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

int main() 
{   
    //declare 3 string
	string input;
    vector<string> data = {};

    //Clear input cache
    input="\n";
    getline(cin,input);
    
    //Input name,ID and seat
    cout << "Please input in \"Name/PassportID/Seat\" or \"0\" to end input ";
    while(input!= "0"){
        getline(cin,input);
        data.push_back(input);
    }

    
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