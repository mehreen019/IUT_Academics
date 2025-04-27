#include <iostream>
#include <fstream>
#include <windows.h>
#include <bits/stdc++.h>

#define len 10

using namespace std;

int main(){
    int ar[len], i, temp;
    long int before, after;

    ifstream in("random_numbers.txt");
    for(i = 0; i < len; i++){
        in >> ar[i];
    }

    //Call the sort functions here
    before = GetTickCount(); // used to start timer
    sort(ar, ar + len);
    after = GetTickCount(); // used to end timer
    
    cout<<"Sorted list: ";
    for(i = 0; i < len; i++){
        cout << ar[i] << " ";
    }

    
    cout << "\nExecution Time: " << (after - before) << "ms";
    return 0;
}
