//Group Project - Airplane Seating Assignment System Solution

//Include library
#include <iostream> //console input&output library
#include <fstream> //file input&output library
#include <string> //string library
#include <vector> //list library
#include <stdio.h> //file rename library
#include <iomanip> //output format library
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
    string Class;
    vector<string> AZ = {"A","B","C","D","E","F"};
	int buff2 = 0;

	cout << "Input Class: ";
	cin >> Class;

    for(int l=1;l < 14;l++){
        bool occupied = false;
        for(auto buff1 : readfile()){
            for(auto o: )
            buff2 = 
            if(buff2 == l){
                occupied = true;
                cout << 
            }
        }
        if(!occupied){
            cout << “vacant” 
        }
    }
	for(auto buff1 : readfile()){
        buff2 = stoi(split(buff1)[2].substr(0, split(buff1)[2].size()-1));
        if(buff2 < 3){
            
        }else if(buff2 < 8){
            cout << "Business";
        }else{
            cout << "Economy";
        }
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