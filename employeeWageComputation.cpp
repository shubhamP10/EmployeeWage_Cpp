#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <list>
#include <sstream>

using namespace std;

vector<int> dailyWageList;
vector<int> hoursList;

struct Employee
{
    int id;
    int monthlySalary;
    string month;
    string companyName;
    int wagePerHour;
};

class Company{
    public: 
    string companyName;
    int WAGE;
    int WORK_DAYS;
    int WORKING_HOURS_PER_MONTH;
    int totalEmployees;
    int totalMonths = 4;

    Company(){}

    Company(string name, int wage, int workDays, int hoursPerMonth){
        companyName = name;
        WAGE = wage;
        WORK_DAYS = workDays;
        WORKING_HOURS_PER_MONTH = hoursPerMonth;
    }
};

list<Company> companyWages;

struct employeeWageResultSet
{
    string companyName, month;
    int day, dailyWage, empId, workDays; 
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
        int dailyWage = WORK_HOURS * company.WAGE;
        dailyWageList.push_back(dailyWage);
        hoursList.push_back(WORK_HOURS);
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

void writeToFile(Employee employee[], int workDays, int size){
    fstream writer;
    writer.open("EmployeeData.csv" , ios::out | ios::app);

    if(writer.is_open())
    {
        writer.seekp(0, ios::end);
        if(writer.tellg() == 0){
            writer << "EMP_ID, COMPANY, MONTH, DAY, HOURS_WORKED, WAGE_PER_HOUR, DAILY_WAGE, WORK_DAYS" << endl;

        }
        int count = 0;
        writer.seekp(0, ios::beg);
        while (count < size)
        {
           for (int i = 0; i < workDays; i++)
           {
                writer << employee[count].id << ", "  << employee[count].companyName << ", " << employee[count].month << ", " << i+1 
                << ", " << hoursList[i] << ", " << employee[count].wagePerHour << ", " << dailyWageList[i] << ", " << workDays << endl;
           }           
            count++;
        }
        writer.close();
    }
}

vector<string> split(const string& line, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(line);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

list <employeeWageResultSet> readFile() 
{ 
    string file = "EmployeeData.csv";
    fstream fileStream; 
    fileStream.open(file, ios::in);

    vector<string> details; 
    string line, word;

    list<employeeWageResultSet> employeeWages;
    getline(fileStream, line);
    while (!fileStream.eof())
    {
        details.clear();
        getline(fileStream, line);
        stringstream s(line);
        while (getline(s, word))
        {
            details = split(word, ',');
            employeeWageResultSet employeeDetails;
            employeeDetails.empId = stoi(details[0]);
            employeeDetails.companyName = details[1];
            employeeDetails.month = details[2];
            employeeDetails.day = stoi(details[3]);
            employeeDetails.dailyWage = stoi(details[6]);
            employeeDetails.workDays = stoi(details[7]);
            employeeWages.push_back(employeeDetails);
        }
        
    }

    fileStream.close();   
    return employeeWages;
} 

void displayEmployeeData(){
    list<employeeWageResultSet> employeeList = readFile();
    list<Company> :: iterator company;
    int companyWage = 0;
    int totalEmps, totalMonths, totalDays;
    vector<int> monthlyWage;
    cout << "Enter Company Name: ";
    string companyName;
    cin >> companyName;
    cout << "Read Size: " << employeeList.size() << endl;
    if(employeeList.size() != 0){
         cout << "Inside if(disp)" << endl;
        for(company = companyWages.begin(); company != companyWages.end(); company++){
            cout << "Inside First For(disp)" << endl;
            if((*company).companyName == companyName){
               totalEmps = (*company).totalEmployees;
               totalMonths = (*company).totalMonths;
               totalDays = (*company).WORK_DAYS;
            }
        } 
        cout << "Out of 1st For\n";
        int count = 0;
        for(list<employeeWageResultSet>::iterator emp = employeeList.begin(); count < employeeList.size(); emp++){
            if((*emp).companyName == companyName){
                int totalWage = 0;
                for(int day = 0; day < totalDays; day++){
                    totalWage += (*emp).dailyWage;
                    if(day < (totalDays - 1)){
                        emp++;
                        count++;
                    }
                }
                monthlyWage.push_back(totalWage);
            }
            else{
                count++;
            }
        }

        for(int emp = 0; emp < totalEmps; emp++){
            for(int month = 0; month < totalMonths; month++){
                cout << "\n Company: " << companyName << "\nMonth: " << (month + 1) << "\nEmp_ID: " << (emp + 1) 
                << "\nMonthly Salary: " << monthlyWage[month] << endl; 
            }
        }
    }
    else{
        cout << "No Data!!!" << endl;
    }   
}

void insertEmployeeWageData(){
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
    companyWages.push_back(company);
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
                cout << "Enter Wage Per Hour: " << endl;
                cin >> company.WAGE;
                cout << "Enter Work Days For Month: " << endl;
                cin >> company.WORK_DAYS;
                cout << "Enter MAX Working Hours In Month: " << endl;
                cin >> company.WORKING_HOURS_PER_MONTH;

                cout << company.companyName << endl;

                cout << "Enter Number of Employees in Company: " << endl;
                cin >> numOfEmp;
                company.totalEmployees = numOfEmp;       
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
                        employee[empCount].wagePerHour = company.WAGE;
                        cout << "Monthly Wage: " << empWageBuilder.monthlyWage << endl;
                        empCount++; 
                    }  
                    writeToFile(employee, company.WORK_DAYS, numOfEmp);
                    dailyWageList.clear();
                    hoursList.clear();
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
}

int main(){
    int flag = 0, choice;
    while (flag == 0)
    {
        cout << "Perss: " << "\n1. Insert Employee Wage\n2. Display Data\n3. Exit" << endl;
        cin >> choice;
        switch(choice){
            case 1:
                insertEmployeeWageData();
                break;
            case 2:
                displayEmployeeData();
                break;
            case 3:
                flag = 1;
                break;
        }
    }
    
    return 0;
}