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

int cll (string ID){
    const string az="abcdefghijklmnopqrstuvwxyz";
    for (char temp : ID){
        if(az.find(temp)!=string::npos){
            return 1;
        }else{
            continue;
        }
    }
    return 0;
}

//Solution
int main(){
    cout << cll("ASD123A");
}