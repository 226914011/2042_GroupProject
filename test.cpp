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
//Data format return in array
string* split(string s){
    string delimiter = "/";
    string* datadata = new string[3];
    size_t pos = 0;
    string buffer;
    int counter = 0;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        buffer = s.substr(0, pos);
        datadata[counter] = buffer;
        s.erase(0, pos + delimiter.length());
        counter++;
    }
    datadata[counter + 1] = s; 
    return datadata;
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


//Rmb use class as mentioned in guildline!!!!!!!!!!!!!!!!!!!!
class cus {       	// The cus
  public:			// Access specifier
    string name;	// Attribute (string variable)
    string id;  	// Attribute (string variable)
    string seat;  	// Attribute (string variable)
};

int main() {
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
                data_buffer.append("/");
            }
        }
        cout << data_buffer << endl;
    }*/
    //For example your data is "Chan Tai Man","HK12345678A","10D"
    string data[3] = {"Chan Tai Man","HK12345678A","10D"};
    cout << data[0] << endl;
    cout << data[1] << endl;
    cout << data[2] << endl;
    
    /*
    string data_buffer;
    
    cus cus_list[][1];  // Create an object of cus
    

    // Access attributes and set values
    cus_list[0][0].name = "Chan Tai Man";
    cus_list[0][0].id = "HK12345678A";
    cus_list[0][0].sit = "10D";
  
    cus_list[1][0].name = "Pan Peter";
    cus_list[1][0].id = "US2356AAD11";
    cus_list[1][0].sit = "2E";

    // Print values
    int rows = (sizeof(cus_list)/sizeof(cus_list[0]));
    int cols = (sizeof(cus_list[0])/sizeof(string));
    for(int i=0;i<rows;i++){
        data_buffer = "";
        for(int j=0;j<cols;j++){
            data_buffer.append(cus_list[i][j]);
            if(j < 2){
                data_buffer.append("/");
            }
        }
        cout << data_buffer;
    }*/
  return 0;
}





