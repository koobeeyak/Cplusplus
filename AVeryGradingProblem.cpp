// Program will calculate student grades based on the weights of 4 exams.
// Grades are outputted to a file, average grade, highest grade, lowest grade are also calculated.
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
void computeAndPrintStudentData(double percentage1, double percentage2, double percentage3, double percentage4, int count){
	// Function will use these parameters to calulate grade for each inputted student based on certain wights defined in main
	// Count is a number the user inputs in main
	ofstream cprn ("grade_report.txt"); // Designate output report file
	cprn << "Student Grade Report" << endl; // cprn will be used to output to file. This is the first line
	cprn << "\n\nStudent's Name     | Student's ID | Student's Grade" << endl;
    string studentName;
    string studentID;
    double grade1, grade2, grade3, grade4, finalGrade;
    double maxGrade = -1; // Initialize max and min variables with a value.
    double minGrade = 101; // It is impossible to score above a 100 or below 0, they will be given new values in for loop
    double totalGrades = 0;
    for (int i=0; i < count; i++){ // Do this loop for the number of students (inputted in main)
        cout << "Enter the name of a student." << endl;
        cin >> studentName;
        cout << "Enter " << studentName << "'s ID" << endl;
        cin >> studentID;
        cout << "Enter " << studentName << "'s grade for Exam 1" << endl;
        cin >> grade1;
        cout << "Enter " << studentName << "'s grade for Exam 2" << endl;
        cin >> grade2;
        cout << "Enter " << studentName << "'s grade for Exam 3" << endl;
        cin >> grade3;
        cout << "Enter " << studentName << "'s grade for Exam 4" << endl;
        cin >> grade4;
        finalGrade = (grade1 * percentage1) + (grade2 * percentage2) + (grade3 * percentage3) + (grade4 * percentage4);
		// Calculated student's final grade based on weights. Next line will output to file.
        cprn << setw(18) << studentName << " | " << setw(12) << studentID << " | " << finalGrade << endl;
        if (finalGrade > maxGrade) // If value of finalgrade is larger than maxgrade, -
            maxGrade = finalGrade; // assign value to maxgrade
        else
            if (finalGrade < minGrade) // If value of finalgrade is less than mingrade, -
                minGrade = finalGrade; // assign value to mingrade
        totalGrades += finalGrade; // One float will keep our total grades, we add a grade to it for every loop
    } // end for
    double averageOfGrades = totalGrades / count; // After exiting loop, we find the average grade
    cprn << "\nAverage : "<< averageOfGrades << endl; // Three lines added to bottom of file
    cprn << "Lowest Grade : " << minGrade << endl;
    cprn << "Highest Grade : " << maxGrade << endl;
} // end computestudentdata()
int main (){
    
    double weightExam1 = .10;
    double weightExam2 = .20;
    double weightExam3 = .25;
    double weightExam4 = .45;
    int numberOfStudents;
    cout << "How many students are in the class?" << endl;
    cin >> numberOfStudents; // An int to be used in our for loop. Next line calls function based on these parameters
    computeAndPrintStudentData(weightExam1, weightExam2, weightExam3, weightExam4, numberOfStudents);
	cout << "\nSee grade_report.txt file for each student's final grade, class average, and lowest and highest grades." << endl;
    return 0;
} // end main()


