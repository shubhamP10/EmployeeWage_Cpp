#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    srand(time(0));
    int isPresent = (rand() % 2);
    if(isPresent == 1)
        cout << "Employee is Present" << endl;
    else
        cout << "Employee is Absent" << endl;
    return 0;
}