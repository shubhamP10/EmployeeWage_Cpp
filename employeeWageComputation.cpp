#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int WAGE_PER_HOUR = 20;
    int HOURS_PER_DAY = 8;
    int PART_TIME_HOURS = 4;
    int wage = 0;
    srand(time(0));
    int isPresent = (rand() % 2);

    if(isPresent == 1){
        cout << "Employee is Present" << endl;
        int jobType = (rand() % 2) + 1;
        switch (jobType)
        {
        case 1:
            cout << "Part Time" << endl;
            wage = WAGE_PER_HOUR * PART_TIME_HOURS;
            break;
        case 2:
            cout << "Full Time" << endl;
            wage = WAGE_PER_HOUR * HOURS_PER_DAY;
            break;
        default:
            break;
        }
        cout << "Wage = " << wage;
    }
    else
        cout << "Employee is Absent" << endl;
    return 0;
}