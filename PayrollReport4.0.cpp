/*	Payroll 4.0 Sorting
	Employee and PayrollReport classes.
	User inputs employee data.
	Program collects data, calculates overtime pay, sorts it based on name, prints to report file.
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

ofstream cprn("payroll_report.txt"); // Global variable to print out to the same report in every function
const int CONST_ARRAY_SIZE=15;
class Employee{
public: // functions to assign and fetch private variable values
    void setEmployeeName(int numberEntered);
    string getEmployeeName();
    void setEmployeeHours();
    double getEmployeeHours();
    void setEmployeeRate();
    double getEmployeeRate();
	void setEmployeeOvertimeHours(double hours);
	double getEmployeeOvertimeHours();
	void setEmployeeOvertimeSalary(double salary);
	double getEmployeeOvertimeSalary();
	void setEmployeeTotalSalary(double salary);
	double getEmployeeTotalSalary();
private: // Variables kept private. They cannot be directly manipulated
    string employeeName;
    double employeeHours;
    double employeeRate;
	double employeeOvertimeHours;
	double employeeOvertimeSalary;
	double employeeTotalSalary;
};
class PayrollReport{
public:
    void printHeaderLine();
    void printColumnHeadings();
    void alphabetizeEmployees(Employee empArray[], int numberEntered); // takes an array of type Employee as variable for sorting
    void printEmployeeDataLine(string string1, double double1, double double2, double double3, double double4, double double5);
    void printTotals(double double1, double double2, double double3, double double4, int int1); // Generic print
};
double findOverTimeHours(double hours);
double findOverTimeSalary(double overHours, double payRate);
double findTotalSalary(double overPay, double payRate, double overHours, double hours);
int main(){
    double totalHours = 0, totalOvertimeHours = 0, totalOvertimeSalary = 0, totalSalary = 0;
    Employee employeeArray[CONST_ARRAY_SIZE]; // Store Employee data
    int employeeIndex=0; // Keep track of number of Employees and current index
	for (employeeIndex;employeeIndex<CONST_ARRAY_SIZE;employeeIndex++){
		employeeArray[employeeIndex].setEmployeeName(employeeIndex);
		if (employeeArray[employeeIndex].getEmployeeName()=="DONE"){
			break; // do not proceed, exit loop for sentinal value
		}
		else {
			employeeArray[employeeIndex].setEmployeeHours();
			employeeArray[employeeIndex].setEmployeeRate();
			double hourlyRate = employeeArray[employeeIndex].getEmployeeRate();
			double hoursWorked = employeeArray[employeeIndex].getEmployeeHours();
			double overtimeHours = findOverTimeHours(hoursWorked);
			double overtimeSalary = findOverTimeSalary(overtimeHours, hourlyRate);
			double employeesSalary = findTotalSalary(overtimeSalary, hourlyRate, overtimeHours, hoursWorked);
			employeeArray[employeeIndex].setEmployeeOvertimeHours(overtimeHours);
			employeeArray[employeeIndex].setEmployeeOvertimeSalary(overtimeSalary);
			employeeArray[employeeIndex].setEmployeeTotalSalary(employeesSalary);
			totalHours += hoursWorked; // total variables were defined outside of this loop, they will increase as employees are added
			totalOvertimeHours += overtimeHours;
			totalOvertimeSalary += overtimeSalary;
			totalSalary += employeesSalary;
		}
    } // end for
    PayrollReport employeePayroll;
    employeePayroll.printHeaderLine();
    employeePayroll.printColumnHeadings();
    employeePayroll.alphabetizeEmployees(employeeArray,employeeIndex);
    for (int i = 0;i < employeeIndex;i++){ // for every employee that was entered
		employeePayroll.printEmployeeDataLine(employeeArray[i].getEmployeeName(), employeeArray[i].getEmployeeRate(), employeeArray[i].getEmployeeHours(), 
			employeeArray[i].getEmployeeOvertimeHours(), employeeArray[i].getEmployeeOvertimeSalary(), employeeArray[i].getEmployeeTotalSalary());
    }
    employeePayroll.printTotals(totalHours, totalOvertimeHours, totalOvertimeSalary, totalSalary, employeeIndex); // Final totals line
    cout << "\nSee payroll_report.txt file for your complete payroll report." << endl;
    return 0;
} // end main
void Employee::setEmployeeName(int numberEntered){ // Assigns value to employeeName from input
    string inputName;
    cout << "Enter employee name or type DONE. You can enter up to " << CONST_ARRAY_SIZE << " employees. So far, you have entered " 
		<< numberEntered << " employee(s)." << endl; // Inform user of max and how many so far each time
    cin >> inputName;
    double lengthOfName = inputName.length();
    while(lengthOfName>15){ // Use this loop to keep employeeName length 15 or less
        cout << "Employee name must be 15 characters or less. Please re-enter employee name." << endl;
        cin >> inputName;
        lengthOfName = inputName.length();
    } // end while
    employeeName = inputName;
}
string Employee::getEmployeeName(){
    return employeeName;
}
void Employee::setEmployeeHours(){
    double inputHours;
    cout << "Enter " << getEmployeeName() << "'s hours." << endl;
    cin >> inputHours;
    employeeHours = inputHours;
}
double Employee::getEmployeeHours(){
    return employeeHours;
}
void Employee::setEmployeeRate(){
    double inputRate;
    cout << "Enter " <<getEmployeeName() << "'s rate." << endl;
    cin >> inputRate;
    employeeRate = inputRate;
}
double Employee::getEmployeeRate(){
    return employeeRate;
}
void Employee::setEmployeeOvertimeHours(double hours){employeeOvertimeHours=hours;}
double Employee::getEmployeeOvertimeHours(){return employeeOvertimeHours;}
void Employee::setEmployeeOvertimeSalary(double salary){employeeOvertimeSalary=salary;}
double Employee::getEmployeeOvertimeSalary(){return employeeOvertimeSalary;}
void Employee::setEmployeeTotalSalary(double salary){employeeTotalSalary=salary;}
double Employee::getEmployeeTotalSalary(){return employeeTotalSalary;}
void PayrollReport::printHeaderLine(){ // First line of output file
    cprn << "\t\t\tEMPLOYEE PAYROLL REPORT -  SPRING 2014\n" << endl;
}
void PayrollReport::printColumnHeadings(){ // This will be run at start of main to setup headers
    cprn << setw(17) << "" << "\tHOURLY\t" << setw(6) << "" << "\tOVERTIME OVERTIME  TOTAL" << endl;
    cprn << setw(17) << "NAME" << "\tRATE\tHOURS\tHOURS\t SALARY\t  SALARY\n" << endl;
}
void PayrollReport::alphabetizeEmployees(Employee empArray[], int numberEntered){
    for (int j = 0;j < numberEntered;j++){
        for (int k = 0;k < numberEntered - j - 1;k++){
            if (empArray[k].getEmployeeName() > empArray[k+1].getEmployeeName()){
            Employee temp = empArray[k];
            empArray[k] = empArray[k+1];
            empArray[k+1] = temp;
            }
        }
    }
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
    // Paramaters are given unspecific names because they're arbitrary
    cprn << "\n" << setw(17) << "TOTALS:" << "\t" << setw(6) << "" << "\t" << setw(6) << double1 << "\t" << setw(4) << double2
        << "\t" << setw(8) << double3 << setw(10) << double4 << endl;
    cprn << "\n# OF EMPLOYEES: " << int1 << endl;
}
double findOverTimeHours(double hours){
    if (hours > 40)
        return hours - 40;
    else
        return 0;
}
double findOverTimeSalary(double overHours, double payRate){
    if (overHours > 10)
        return ((overHours - 10) * (2 * payRate)) + (10 * (1.5 * payRate));
    else
        if (overHours <= 10)
            return (overHours * (1.5 * payRate));
        else
            return 0;
}
double findTotalSalary(double overPay, double payRate, double overHours, double hours){
    if (overPay > 0)
        return overPay + (payRate * (hours - overHours));
    else
        return payRate * hours;
}
