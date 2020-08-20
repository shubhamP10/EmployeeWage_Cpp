#include <iostream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <random>
#include <unistd.h>

using namespace std;

class Company{
    public: 
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;

    Company(string name, int wage, int workDays, int hoursPerMonth){
        companyName = name;
        WAGE = wage;
        WORK_DAYS = workDays;
        WORKING_HOURS_PER_MONTH = hoursPerMonth;
    }
};

struct Employee
{
    int id;
    int monthlySalary;
    string month;
    string companyName;
};

void writeToFile(Employee employee[], int size){
    ofstream writer;
    ifstream reader("EmployeeData.csv");
    reader.seekg(0, ios::end);
    if (reader.tellg() == 0)
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        
        writer << "ID,COMPANY,MONTH,SALARY" << endl;
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].companyName << "," << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }
    else
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].companyName << "," << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }    
}

int getTotalWorkingHours(Company company){
    srand(time(0));
    int WORK_HOURS = 0;
    int  totalWorkingDays = 0, totalWorkingHours = 0;
    
    while (totalWorkingHours <= company.WORKING_HOURS_PER_MONTH && totalWorkingDays < company.WORK_DAYS)
    {   
        totalWorkingDays++;
        int isPresent = (rand() % 2);
        if(isPresent == 1){
            srand((unsigned)time(NULL));
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
    
    //Company Details
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;

    cout << "Enter Company Name: " << endl;
    cin >> companyName;
    cout << "Enter Wage Per Day: " << endl;
    cin >> WAGE;
    cout << "Enter Work Days For Month: " << endl;
    cin >> WORK_DAYS;
    cout << "Enter MAX Working Hours In Month: " << endl;
    cin >> WORKING_HOURS_PER_MONTH;

    Company company(companyName, WAGE, WORK_DAYS, WORKING_HOURS_PER_MONTH);

    cout << company.companyName << endl;

    cout << "Enter Number of Employees in Company: " << endl;
    cin >> numOfEmp;
    Employee employee[numOfEmp];
    
    while (monthCount < 4)
    {
        empCount = 0;
        while (empCount < numOfEmp)
        {        
            sleep(2);
            totalWorkingHours = getTotalWorkingHours(company);
            
            monthlyWage = totalWorkingHours * company.WAGE;
            employee[empCount].id = empCount + 1;
            employee[empCount].monthlySalary = monthlyWage;
            employee[empCount].month = months[monthCount];
            employee[empCount].companyName = company.companyName;
            cout << "Employee ID: " << employee[empCount].id << endl;
            cout << "Company Name: " << company.companyName << endl;
            cout << "Month: " << months[monthCount] << endl;
            cout << "Monthly Wage: " << monthlyWage << endl;
            empCount++; 
        }  
        writeToFile(employee, numOfEmp);
        monthCount++;     
    }    
    return 0;
}