// Payroll Report 2.0
// Program will ask for employee name, hours worked, and rate.
// Salary will be computed together with overtime.
// Note class Employee.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
ofstream cprn("payroll_report.txt"); // Global variable to print out to the same report in every function
class Employee{
public: // functions to assign and fetch private variable values
	void setEmployeeName();
	string getEmployeeName();
	void setEmployeeHours();
	double getEmployeeHours();
    void setEmployeeRate();
    double getEmployeeRate();
private: // Variables kept private. They cannot be directly manipulated
	string employeeName;
	double employeeHours;
	double employeeRate;
};
class PayrollReport{
public:
	void printHeaderLine();
	void printColumnHeadings();
	void printEmployeeDataLine(string string1, double double1, double double2, double double3, double double4, double double5);
	void printTotals(double double1, double double2, double double3, double double4, int int1);
};
void Employee::setEmployeeName(){ // Assigns value to employeeName from input
    string inputName;
    cout << "Enter employee name or type DONE" << endl;
    cin >> inputName;
    double lengthOfName = inputName.length();
    while(lengthOfName>15){ // Use this loop to keep employeeName length 15 or less
        cout << "Employee name must be 15 characters or less. Please re-enter employee name." << endl;
        cin >> inputName;
        lengthOfName = inputName.length();
    } // end while
    employeeName = inputName;
}
string Employee::getEmployeeName(){ // Fetches value of employeeName
    return employeeName;
}
void Employee::setEmployeeHours(){ // Assigns value to employeeHours from input
    double inputHours;
    cout << "Enter " << getEmployeeName() << "'s hours." << endl;
    cin >> inputHours;
    employeeHours = inputHours;
}
double Employee::getEmployeeHours(){ // Fetches value of employeeHours
    return employeeHours;
}
void Employee::setEmployeeRate(){ // Assings value to employeeRate from input
    double inputRate;
    cout << "Enter " <<getEmployeeName() << "'s rate." << endl;
    cin >> inputRate;
    employeeRate = inputRate;
}
double Employee::getEmployeeRate(){ // Fetches value of employeeRate
    return employeeRate;
} // Last of the Employee member functions
void PayrollReport::printHeaderLine(){ // First line of output file
	cprn << "\t\t\tEMPLOYEE PAYROLL REPORT -  SPRING 2014\n" << endl;
}
void PayrollReport::printColumnHeadings(){ // This will be run at start of main to setup headers
	cprn << setw(17) << "" << "\tHOURLY\t" << setw(6) << "" << "\tOVERTIME OVERTIME  TOTAL" << endl;
	cprn << setw(17) << "NAME" << "\tRATE\tHOURS\tHOURS\t SALARY\t  SALARY\n" << endl;
}
void PayrollReport::printEmployeeDataLine(string string1, double double1, double double2, double double3, double double4, double double5){
	// Print data to report. setw() organizes into columns. setprecision() sets decimal place
	// Paramaters are given unspecific names because they're arbitrary to the scope of this function
	cprn << setiosflags(ios::fixed |ios::showpoint) << setprecision(2);
    cprn << setw(17) << string1 << "\t" << setw(6) << double1 << "\t" << setw(6) << double2 << "\t" << setw(4) << double3 
		<< "\t" << setw(8) << double4 << setw(10) << double5 << endl;
}
void PayrollReport::printTotals(double double1, double double2, double double3, double double4, int int1){
	// Last lines of report will display several total values
	// Paramaters are given unspecific names because they're arbitrary to the scope of this function
	cprn << "\n" << setw(17) << "TOTALS:" << "\t" << setw(6) << "" << "\t" << setw(6) << double1 << "\t" << setw(4) << double2 
		<< "\t" << setw(8) << double3 << setw(10) << double4 << endl;
	cprn << "\n# OF EMPLOYEES: " << int1 << endl;
}
double findOverTimeHours(double hours){ // Returns number of overtime hours as double
    if (hours > 40)
        return hours - 40;
    else
        return 0;
}
double findOverTimeSalary(double overHours, double payRate){ // Returns overtime pay as double
    if (overHours > 10)
        return ((overHours - 10) * (2 * payRate)) + (10 * (1.5 * payRate));
    else
        if (overHours <= 10)
            return (overHours * (1.5 * payRate));
        else
            return 0;
}
double findTotalSalary(double overPay, double payRate, double overHours, double hours){ // Returns total pay as double
    if (overPay > 0)
        return overPay + (payRate * (hours - overHours));
    else
        return payRate * hours;
}

int main(){
    double totalHours = 0, totalOvertimeHours = 0, totalOvertimeSalary = 0, totalSalary = 0;
	int count = 0;
	PayrollReport payrollOject;
	payrollOject.printHeaderLine();
	payrollOject.printColumnHeadings();
	Employee employeeObject; // This is how we will interact with the Employee class
	employeeObject.setEmployeeName();
	while (employeeObject.getEmployeeName() != "DONE"){ // DONE is sentinal value
		employeeObject.setEmployeeHours();
        employeeObject.setEmployeeRate();
        double hourlyRate = employeeObject.getEmployeeRate();
        double hoursWorked = employeeObject.getEmployeeHours();
        double overTimeHours = findOverTimeHours(hoursWorked);
        double overTimeSalary = findOverTimeSalary(overTimeHours, hourlyRate);
        double employeesSalary = findTotalSalary(overTimeSalary, hourlyRate, overTimeHours, hoursWorked);
        totalHours += hoursWorked; // total variables were defined outside of this loop, they will increase as employees are added
        totalOvertimeHours += overTimeHours;
        totalOvertimeSalary += overTimeSalary;
        totalSalary += employeesSalary;
		// Following line will print out a new line to the report for every iteration of the loop and thus for every employee
        payrollOject.printEmployeeDataLine(employeeObject.getEmployeeName(), hourlyRate, hoursWorked, overTimeHours, overTimeSalary, employeesSalary);
		count++; // For # of total employees
		employeeObject.setEmployeeName(); // Loop will iterate as long as this is not assigned to DONE
	} // end while
	// Following line prints footer to report once loop exits and thus user is done entering employee data
	payrollOject.printTotals(totalHours, totalOvertimeHours, totalOvertimeSalary, totalSalary, count);
	cout << "\nSee payroll_report.txt file for your complete payroll report." << endl;
    return 0;
}
