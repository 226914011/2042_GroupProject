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
	ifstream infile;
    ofstream outfile;
    
	infile.open(filename, fstream::in);
	infile.getline(buffer, 100);
	infile.close();

    outfile.open(filename,fstream::out | fstream::app);
	if(buffer){
		cout << 1;
        outfile << "\n";
    }
	outfile << data;
	outfile.close();
	outfile.clear();
    /*
    if(infile){
        infile.close();
        infile.clear();
    }
    if(outfile){
        outfile.close();
	    outfile.clear();
    }
    */
}

int main() 
{   
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