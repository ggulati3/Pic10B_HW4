//
//  main.cpp
//  hmw_4_1
//
//  Created by Gaurav Gulati on 11/3/18.
//  Copyright © 2018 Gaurav Gulati. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int recurse(string big, string small, int index){
    if(index == big.length()-small.length()+1){
        return -1;
    } else if( small == big.substr(index, small.length())){
        return index;
    } else {
        return recurse(big, small, ++index);
    }
}

int main() {
    char answer = 'y';
    while(answer == 'y'){
        string full;
        string snippet;
        string test = "sip";
        cout << "Enter a string: ";
        getline(cin, full);
        cout << "Enter a string to search for: ";
        getline(cin, snippet);
        int value = recurse(full, snippet, 0);
        if(value == -1){
            cout << "Not found!" << endl;
        } else {
            cout << "The position = " << value << endl;
        }
        
        cout << "Continue (y/n) ";
        cin >> answer;
        cout << endl;
        cin.ignore(256,'\n');
    }

    
    return 0;
}
