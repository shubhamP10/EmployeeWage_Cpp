#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <random>
#include <unistd.h>

using namespace std;

struct Employee
{
    int id;
    int monthlySalary;
    string month;
};

void writeToFile(Employee employee[], int size){
    ofstream writer;
    ifstream reader("EmployeeData.csv");
    reader.seekg(0, ios::end);
    if (reader.tellg() == 0)
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        
        writer << "ID,MONTH,SALARY" << endl;
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }
    else
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }    
}

int getTotalWorkingHours(){
    srand(time(0));
    int WORK_HOURS = 0;
    int DAYS_IN_MONTH = 20;
    int MAX_HOURS_IN_MONTH = 100;
    int  totalWorkingDays = 0, totalWorkingHours = 0;
    
    while (totalWorkingHours <= MAX_HOURS_IN_MONTH && totalWorkingDays < DAYS_IN_MONTH)
    {   
        totalWorkingDays++;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1,9999);
        int isPresent = (dis(gen) % 2);
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
    }
}

int main(){
    string months[] = {"Jan", "Feb", "Mar", "Apr"};
    int WAGE_PER_HOUR = 20;
    int monthlyWage = 0, totalWorkingHours = 0;
    int numOfEmp = 0, empCount = 0, monthCount = 0;

    cout << "Enter Number of Employees in Company: " << endl;
    cin >> numOfEmp;
    Employee employee[numOfEmp];
    
    while (monthCount < 4)
    {
        empCount = 0;
        while (empCount < numOfEmp)
        {        
            sleep(2);
            totalWorkingHours = getTotalWorkingHours();
            
            monthlyWage = totalWorkingHours * WAGE_PER_HOUR;
            employee[empCount].id = empCount + 1;
            employee[empCount].monthlySalary = monthlyWage;
            employee[empCount].month = months[monthCount];
            cout << "Employee ID: " << employee[empCount].id << endl;
            cout << "Month: " << months[monthCount] << endl;
            cout << "Monthly Wage: " << monthlyWage << endl;
            empCount++; 
        }  
        writeToFile(employee, numOfEmp);
        monthCount++;     
    }    
    return 0;
}