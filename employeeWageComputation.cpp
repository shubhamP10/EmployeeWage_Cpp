#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(){
    int day = 1;
    int WAGE_PER_HOUR = 20;
    int WORK_HOURS = 0;
    int DAYS_IN_MONTH = 20;
    int MAX_HOURS_IN_MONTH = 100;
    int wage = 0;
    int monthlyWage = 0, totalWorkingDays = 0, totalWorkingHours = 0;
    srand(time(0));
    
    while (totalWorkingHours <= MAX_HOURS_IN_MONTH && totalWorkingDays <= DAYS_IN_MONTH)
    {
        totalWorkingDays++;
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
            totalWorkingHours += WORK_HOURS;
        }
        else{
            WORK_HOURS = 0;
            totalWorkingHours += WORK_HOURS;
        }      
        day++;
    }
    monthlyWage = totalWorkingHours * WAGE_PER_HOUR;
    cout << "Monthly Wage: " << monthlyWage << endl;   
    return 0;
}