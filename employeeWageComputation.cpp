#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;

struct Employee
{
    int id;
    int monthlySalary;
    string month;
    string companyName;
    vector<int> dailyWageList;
};
class Company{
    public: 
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;
    vector<Employee> employeeList;
    
    Company(){}

    Company(string name, int wage, int workDays, int hoursPerMonth){
        companyName = name;
        WAGE = wage;
        WORK_DAYS = workDays;
        WORKING_HOURS_PER_MONTH = hoursPerMonth;
    }
};


getTotalWorkingHours(Company company, int empID){
    cout << "Inside Calculate GTWH()" << endl;
    srand(time(0));
    int WORK_HOURS = 0;
    int  totalWorkingDays = 0, totalWorkingHours = 0;
    
    while (totalWorkingHours <= company.WORKING_HOURS_PER_MONTH && totalWorkingDays < company.WORK_DAYS)
    {   
        cout << "Inside GTWH While1" << endl;
        totalWorkingDays++;
        int isPresent = (rand() % 2);
        if(isPresent == 1){
            int jobType = (rand() % 3);
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
        cout << "Before Operation" << endl;
        company.employeeList.at(empID).dailyWageList.push_back(WORK_HOURS * company.WAGE);
        // company.employeeList[empID].dailyWageList.push_back(WORK_HOURS * company.WAGE);
        cout << "After Operation" << endl;
        // company.employee.dailyWage[company.WORK_DAYS] = WORK_HOURS * company.WAGE;
        // cout << "Daily Wage: " << company.employeeList[empID].dailyWage[company.WORK_DAYS] << endl; 
    }
    return totalWorkingHours;
}

class EmpWageBuilder{
    public :
    int monthlyWage;
    Company company;
    
    void calculateWage(int empID){
        cout << "Inside Calculate Wage()" << endl;
        monthlyWage = getTotalWorkingHours(company, empID) * company.WORKING_HOURS_PER_MONTH;
    }
};

void writeToFile(vector<Employee> employee, int size){
    ofstream writer;
    ifstream reader("EmployeeData.csv");
    reader.seekg(0, ios::end);
    if (reader.tellg() == 0)
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        
        writer << "EMP_ID,COMPANY,DAY,WAGE_PER_HOUR,HOURS,DAILY_WAGE,MONTH" << endl;
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].companyName << "," 
                    << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }
    else
    {
        int count = 0;
        writer.open("EmployeeData.csv" , ios::out | ios::app);
        while (count < size)
        {
            writer << employee[count].id << "," << employee[count].companyName << "," 
                    << employee[count].month << "," << employee[count].monthlySalary << endl;
            count++;
        }
    }    
}

int main(){
    string months[] = {"Jan", "Feb", "Mar", "Apr"};
    int WAGE_PER_HOUR = 20;
    int monthlyWage = 0, totalWorkingHours = 0;
    int numOfEmp = 10, empCount = 0, monthCount = 0;

    //Company Details
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;
    int choice, flag = 0;
    Company company;
    // Employee employee;
    EmpWageBuilder empWageBuilder;

    cout << "Press 1 To Enter Details, 2 for EXIT " << endl;
    while (flag == 0)
    {
        cin >> choice;
        switch (choice)
        {
            case 1:  
                cout << "Enter Company Name: " << endl;
                cin >> company.companyName;
                cout << "Enter Wage Per Hour: " << endl;
                cin >> company.WAGE;
                cout << "Enter Work Days For Month: " << endl;
                cin >> company.WORK_DAYS;
                cout << "Enter MAX Working Hours In Month: " << endl;
                cin >> company.WORKING_HOURS_PER_MONTH;
                cout << "Enter Number of Employees in Company: " << endl;
                cin >> numOfEmp;
                                
                while (monthCount < 4)
                {
                    cout << "Inside 1st Inner While Loop" << endl;
                    empCount = 1;
                    while (empCount <= numOfEmp)
                    {       
                        cout << "Inside 2nd Inner While Loop" << endl; 
                        sleep(1.5);
                        empWageBuilder.company = company;
                        Employee employee;
                        company.employeeList.push_back(employee);
                        empWageBuilder.calculateWage(empCount);
            
                        // company.employeeList[empCount].
                        company.employeeList[empCount].id = empCount;
                        company.employeeList[empCount].monthlySalary = empWageBuilder.monthlyWage;
                        company.employeeList[empCount].month = months[monthCount];
                        company.employeeList[empCount].companyName = company.companyName;
                        cout << "Employee ID: " << company.employeeList[empCount].id << endl;
                        cout << "Company Name: " << company.companyName << endl;
                        cout << "Month: " << months[monthCount] << endl;
                        cout << "Monthly Wage: " << empWageBuilder.monthlyWage << endl;
                        empCount++; 
                    }  
                    // writeToFile(company.employeeList[empCount], numOfEmp);
                    monthCount++;     
                }
                monthCount = 0;
                cout << "Press 1 To Add Another Company Details or 2 for EXIT" << endl;
                break;
            
            case 2:
                flag = 1;
                break;
        }
    }
        
    return 0;
}