//  Program will read in employee data from file.
//  Then it will print department and overall information to output file.
//  Uses Report class.
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
ifstream infile("C:\\Users\\pk130211\\Desktop\\employees.dat"); // input file
ofstream outfile("employee_report.txt"); // output file
const int COMMONARRAYSIZE = 10; // will be used for both arrays
class Report{
public:
 void printHeader();
 void printDepartmentHeader(string dept);
 void printDepartmentFooter(string dept, int number);
 void printLocationHeader(string loc);
 void printLocationFooter(string loc, int number);
 void printLine(string empNum, string lName, string fName, string title, string area, string dept);
 void printFooter(string namesArray[], int countArray[]);
};
void Report::printHeader(){
	outfile << "\t\t\tEMPLOYEE REPORT\n\n" << endl;
}
void Report::printDepartmentHeader(string dept){
	outfile << "\t" << dept << " Department:\n" << endl;
}
void Report::printDepartmentFooter(string dept, int number){
	outfile << "\n\t" << dept << " total: " << number << " employees.\n\n\n\n" << endl;
}
void Report::printLocationHeader(string loc){
	outfile << "\tLocation " << loc << ":" << endl;
}
void Report::printLocationFooter(string loc, int number){
	outfile << "\t" << number << " employees in location " << loc << "." << endl;
}
void Report::printLine(string empNum, string lName, string fName, string title, string area, string dept){
	// this will print out  each line of data, call it frequently
	outfile << setw(12) << empNum << setw(12) << lName << setw(12) << fName << setw(10) << title << setw(5) << area << setw(7) << dept << endl;
}
void Report::printFooter(string namesArray[], int countArray[]){
	outfile << "\n\tFINAL NUMBER OF EMPLOYEES IN EACH DEPARTMENT" << endl;
	int totalCount = 0;
	for (int i=0;i<COMMONARRAYSIZE;i++){ // at the end, output department info
		if (namesArray[i] != "" && countArray[i] != 0){ // some array elements are left unassigned
			outfile << namesArray[i] << " : " << countArray[i] << endl;
			totalCount += countArray[i]; // this will be a grand total of employees
		}
	}
	outfile << "GRAND TOTAL OF EMPLOYEES : " << totalCount << endl;
}
int main ()
{
if (!infile) // check input file
	cerr << "Can't open input file\n"; 
else if (!outfile) // check output file
	cerr << "Can't open output file\n";
else { // we can open files, lets continue
	string iD, lastName, firstName, jobTitle, location, department;
	int index = 0;
	string departmentNames[COMMONARRAYSIZE]; // store all names
	int departmentCounts[COMMONARRAYSIZE]; // store all counts
	Report employeeReport;
	employeeReport.printHeader();
	int deptCount = 0, locCount = 0; // initialize counts
	infile >> iD >> lastName >> firstName >> jobTitle >> location >> department;
	string currentDept = department, currentLoc = location; // initialize first values
	employeeReport.printDepartmentHeader(currentDept);
	employeeReport.printLocationHeader(currentLoc);
	employeeReport.printLine(iD, lastName, firstName, jobTitle, location, department);
	while (infile >> iD >> lastName >> firstName >> jobTitle >> location >> department){
	if (currentDept == department && currentLoc == location){ // we are in the same dept, loc
		employeeReport.printLine(iD, lastName, firstName, jobTitle, location, department);
		deptCount++;
		locCount++;
		} //end if
	else if (currentDept == department && currentLoc != location){ // we have a new loc in the same dept
		employeeReport.printLocationFooter(currentLoc, locCount);
		currentLoc = location;
		locCount = 0;
		employeeReport.printLocationHeader(currentLoc);
		employeeReport.printLine(iD, lastName, firstName, jobTitle, location, department);
	} // end else if
	else { // we are changing depts
		employeeReport.printLocationFooter(currentLoc, locCount);
		employeeReport.printDepartmentFooter(currentDept, deptCount);
		departmentNames[index] = currentDept;
		departmentCounts[index] = deptCount;
		index++; // this is how new elements are added to the next index for each loop
		currentDept = department;
		currentLoc = location;
		deptCount = 0;
		locCount = 0;
		employeeReport.printDepartmentHeader(currentDept);
		employeeReport.printLocationHeader(currentLoc);
		employeeReport.printLine(iD, lastName, firstName, jobTitle, location, department);
		} // end else
	} // end while
	employeeReport.printDepartmentFooter(currentDept, deptCount); // don't want to miss the final dept
	departmentNames[index] = currentDept; // as well as its name
	departmentCounts[index] = deptCount; // and count
	employeeReport.printFooter(departmentNames, departmentCounts); // last grand totals are outputted
	cout << "Done, see employee_report.txt." << endl; // success!
	return 0;
} // end else from very beginning of main
} // end main
