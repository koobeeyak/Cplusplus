// Your Loss is Our Gain
// Program will ask for clients' name, weight before, weight after,
// then will calculate their weight loss.
// At the end we have a winner and a booby.
#include <iostream>
#include <string>
using namespace std;

int main() {
    double beforeWeight, afterWeight, weightLoss, minLoss, maxLoss;
    string name;
    string best; // This will be the name of the person who lost the most weight
    string booby; // This will be the name of the person who lost the least weight
    cout << "Please input your client's name, or type DONE" << endl;
    cin >> name;
    if (name != "DONE") { // First client will populate our variables with values
        cout << "What is " << name <<"'s initial weight?" << endl;
        cin >> beforeWeight;
        cout << "What is " << name <<"'s current weight?" << endl;
        cin >> afterWeight;
        weightLoss =  beforeWeight - afterWeight; // Calculate weight loss
        cout << name << " lost " << weightLoss << " pounds!" << endl;
        minLoss = weightLoss; // Give these four variables the values -
        maxLoss = weightLoss; // of the first client -
        best = name; // They'll be properly reassigned as more clients are added -
        booby = name; // in the following while loop
        cout << "Please input your client's name, or type DONE" << endl;
        cin >> name;
        while (name != "DONE") { // DONE is sentinel value, loop will continue otherwise
            cout << "What is " << name <<"'s initial weight?" << endl;
            cin >> beforeWeight;
            cout << "What is " << name <<"'s current weight?" << endl;
            cin >> afterWeight;
            weightLoss = beforeWeight - afterWeight;
            cout << name << " lost " << weightLoss << " pounds!" << endl;
            if (weightLoss > maxLoss) { // If the weightLoss for this client is greater -
                maxLoss = weightLoss;  // than maxLoss, assign to maxLoss
                best = name;
            } // end if
            else
                if (weightLoss < minLoss) { // If the weightLoss for this client is less than -
                    minLoss = weightLoss; // minLoss, assign to minLoss
                    booby = name;
                } // end else if
            cout << "Please input your client's name, or type DONE." << endl;
            cin >> name; // New value assigned to name. If not DONE, loop continues
		} // end while
		// When loop terminates, user is done inputting clients, so we show winner and booby
        cout << best << " is your winner with " << maxLoss << " pounds lost." << endl;
        cout << booby << " is your booby with " << minLoss << " pounds lost." << endl;
	} // end if
	else // If first input was DONE
		cout << "No clients were entered." << endl;
    return 0;
} // end main()
