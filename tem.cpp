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

void matching(string seatinput,char& seat,int& row)
{
    seat = seatinput.back();
    row = stoi(seatinput.substr(0, seatinput.size() - 1));
}

//Solution
int main(){
    char seat;
    int row;
    matching("10A",seat,row);
    cout << seat << endl << row;
}