//Group Project - Test File

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
//Data format return in vector
vector<string> readfile(){
	//declare variables
	string filename = "Client_data.txt";
	string buffer;
	vector<string> data = {};

	//Create ifstream for read data in file
	ifstream infile;

	//Get data in each line and add to vector
	infile.open(filename, ifstream::in);
	while (getline(infile,buffer)) {
		data.push_back(buffer);
	}

	//Returning data in vector
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
	//declare variables
	char buffer[256];
	bool empty = true;

	//Create ifstream for read data in file
	ifstream infile;
	//Create ofstream for write data to file
    ofstream outfile;
    
	//Check if file is empty or not
	infile.open(filename, fstream::in);
	if(infile.getline(buffer, 100)){
		empty = false;
	}
	infile.close();

	//If not empty, create a newline and write data
	//If empty, only write data
    outfile.open(filename,fstream::out | fstream::app);
	if(!empty){
        outfile << "\n";
    }
	outfile << data;
	outfile.close();
	outfile.clear();
}

int main() 
{   

}
//Function3 - Add assignments in batch
void F3(){   
    //declare variables
	string input;
    vector<string> data = {};
    vector<string> suces = {};
    vector<string> fail = {};

    //Clear input cache
    input="\n";
    getline(cin,input);
    
    //Input name, ID and seat in the specified format
    cout << "Please input in \"Name/PassportID/Seat\" or \"0\" to end input:" << endl;
    getline(cin,input);
    while(input!= "0"){
        data.push_back(input);
        getline(cin,input);
    }
    cout << endl;

	//Store data for data in vector
    for(auto buffer : data){
		//declare variables
        bool sucess = true;
        vector<string> buffer1 = split(buffer);

		//Check if any data exist in data file
		if(readfile().size()==0){
			goto file_not_exist;
		}

		//Get data to check
        for(auto str : readfile()){
			vector<string> buffer2 = split(str);

            //Check if found data match in data file
			if(buffer1[0]== buffer2[0] || buffer1[1]== buffer2[1] || buffer1[2]== buffer2[2]){
                sucess = false;
            }
        }
		//Bypass the for loop if there is not data file to prevent error
		file_not_exist:;

		//Store success and fail cases
        if(sucess){
            suces.push_back(buffer);
            store(buffer,"Client_data.txt");
        }else{
            fail.push_back(buffer);
        }

    }

	//Display success case list
    if(!suces.empty()){
        cout << "Successful requests:" << endl;
        for(auto buffer3 : suces){
            cout << buffer3 << endl;
        }
        cout << endl;
    }

	//Display fail case list
    if(!fail.empty()){
        cout << "Unsuccessful requests:" << endl;
        for(auto buffer4 : fail){
            cout << buffer4 << endl;
        }
        cout << endl;
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