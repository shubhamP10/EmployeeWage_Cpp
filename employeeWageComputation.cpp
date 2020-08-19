#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int day = 1;
    int WAGE_PER_HOUR = 20;
    int WORK_HOURS = 0;
    int DAYS_IN_MONTH = 20;
    int wage = 0;
    int monthlyWage = 0;
    srand(time(0));
    
    while (day <= DAYS_IN_MONTH)
    {
        int isPresent = (rand() % 2);
        if(isPresent == 1){
            int jobType = (rand() % 2) + 1;
            switch (jobType)
            {
            case 1:
                WORK_HOURS = 4;
                break;
            case 2:
                WORK_HOURS = 8;
                break;
            default:
                WORK_HOURS = 0;
            }
            wage = WORK_HOURS * WAGE_PER_HOUR;
            monthlyWage += wage;
            cout << "Day" << day << " Wage = " << wage << endl;
        }
        else{
            WORK_HOURS = 0;
            wage = WORK_HOURS * WAGE_PER_HOUR;
            monthlyWage += wage;
            cout << "Day" << day << " Wage = " << wage << endl;
        }
            
        day++;
    }

    cout << "Monthly Wage: " << monthlyWage << endl;   
    return 0;
}