#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>

using namespace std;

class Company{
    public: 
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;

    Company(){}

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

getTotalWorkingHours(Company company){
    srand(time(0));
    int WORK_HOURS = 0;
    int  totalWorkingDays = 0, totalWorkingHours = 0;
    
    while (totalWorkingHours <= company.WORKING_HOURS_PER_MONTH && totalWorkingDays < company.WORK_DAYS)
    {   
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
    }
    return totalWorkingHours;
}

class EmpWageBuilder{
    public :
    int monthlyWage;
    Company company;

    void calculateWage(){
        monthlyWage = getTotalWorkingHours(company) * company.WORKING_HOURS_PER_MONTH;
    }
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
    Employee employee[numOfEmp];
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
                cout << "Enter Wage Per Day: " << endl;
                cin >> company.WAGE;
                cout << "Enter Work Days For Month: " << endl;
                cin >> company.WORK_DAYS;
                cout << "Enter MAX Working Hours In Month: " << endl;
                cin >> company.WORKING_HOURS_PER_MONTH;

                cout << company.companyName << endl;

                cout << "Enter Number of Employees in Company: " << endl;
                cin >> numOfEmp;
                                
                while (monthCount < 4)
                {
                    empCount = 0;
                    while (empCount < numOfEmp)
                    {        
                        sleep(1.5);
                        empWageBuilder.company = company;
                        empWageBuilder.calculateWage();
                        employee[empCount].id = empCount + 1;
                        employee[empCount].monthlySalary = empWageBuilder.monthlyWage;
                        employee[empCount].month = months[monthCount];
                        employee[empCount].companyName = company.companyName;
                        cout << "Employee ID: " << employee[empCount].id << endl;
                        cout << "Company Name: " << company.companyName << endl;
                        cout << "Month: " << months[monthCount] << endl;
                        cout << "Monthly Wage: " << empWageBuilder.monthlyWage << endl;
                        empCount++; 
                    }  
                    writeToFile(employee, numOfEmp);
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