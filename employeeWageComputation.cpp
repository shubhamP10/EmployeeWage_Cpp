#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int WAGE_PER_HOUR = 20;
    int HOURS_PER_DAY = 8;
    int wage = 0;
    srand(time(0));
    int isPresent = (rand() % 2);
    if(isPresent == 1){
        cout << "Employee is Present" << endl;
        wage = WAGE_PER_HOUR * HOURS_PER_DAY;
        cout << "Wage = " << wage;
    }
    else
        cout << "Employee is Absent" << endl;
    return 0;
}