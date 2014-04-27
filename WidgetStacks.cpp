// Stacks HW by Philip Kubiak
// 3.24.14
// Prof Friedman
// Program will use a class to manipulate widget stack.
// Widgets are received, stored, sold at a markup.
// Everything is inputted and printed out through the console.
#include <iostream>
#include <string>
#include <stack>
using namespace std;

const double MARKUP = 1.2;
class manageWidgetStack{
public:
    stack<double> widgetStack; 
    void receiveWidgets(string date, string time, int quantity, double price);
    void sellWidgets(string date, string time, int quantity);
};    
void manageWidgetStack::receiveWidgets(string date, string time, int quantity, double price){
    for (double i=0; i<quantity; i++) widgetStack.push(price); // store price at a certain amount of quantity
    cout << "On " << date << " at " << time << ", " << quantity << " widgets were recieved at $" <<
    price << "." << endl;
}
void manageWidgetStack::sellWidgets(string date, string time, int quantity){
    double price, sale = 0, overallSale = 0;
    int countSamePrice = 0;
    if (!widgetStack.empty()){ // we will do this a lot to ensure stack is not empty
        price = widgetStack.top(); // initialize price variable
    }
    if (widgetStack.empty()) cout << "Can't make a sale, there are no widgets." << endl;
    else {
        for (double i=0; i<quantity; i++){ // up to a certain quantity
            if (!widgetStack.empty()){
                    if (price == widgetStack.top()){
                        widgetStack.pop(); // remove each price from stack
                        countSamePrice++; // while keeping count of how much we have removed
                        } // end if
                    else{
                        sale = price * MARKUP * countSamePrice; 
                        cout << countSamePrice << " widgets sold at $" << price << ". Sale: $" <<
                        sale << "." << endl;
                        overallSale += sale; // track overall sale
                        countSamePrice = 0; // reset these
                        sale = 0; // variables for next iteration of loop
                        price = widgetStack.top(); // we have a new price
                        widgetStack.pop();
                        countSamePrice++;
                        } // end else
                } // end if
            else {
                cout << "No more widgets." << endl; // stack is empty
                cout << quantity - countSamePrice << " widgets could not be sold. " << endl; // difference between what we could and couldn't sell
                break; // end if loop, we can't make more sales
            } // end else
        } // end for
        if (sale == 0 || overallSale == 0){ // this will fix any values that didn't pass through the above if or else statements
            sale = price * MARKUP * countSamePrice;
            cout << countSamePrice << " widgets sold at $" << price << ". Sale: $" <<
            sale << "." << endl;
            overallSale += sale;
            countSamePrice = 0;
            sale = 0;
        }
        cout << "On " << date << " at " << time << ", " << quantity << " widgets were sold for $" <<
        overallSale << "." << endl;
        overallSale = 0;
        } // end else
    }
int main (){
    manageWidgetStack store;
    char a, c;
    string date, time;
    int quantity;
    double price;
    cout << "Would you like to interact with the Widget Store?" << endl;
    cin >> a;
    while (a != 'n'){ // answer is not no, continue loop
        cout << "So, will this be a selling (s) or receving (r) record?" << endl;
        cin >> c;
        while (c != 's' && c != 'r'){
            cout << "Need to know whether this is selling (s) or receiving." << endl;
            cin >> c;
        }
        cout << "Date of record? Ex 3.24.14 (no spaces, please)." << endl;
        cin >> date;
        cout << "Time of record? Ex 9:00AM (no spaces, please)." << endl;
        cin >> time;
        if (c == 's'){
            cout << "Okay, how much is being sold?" << endl;
            cin >> quantity;
            store.sellWidgets(date, time, quantity);
            cout << "Would you like to interact with the Widget Store?" << endl;
            cin >> a;
        }
        else {
            cout << "Okay, how much is being received?" << endl;
            cin >> quantity;
            cout << "At what price?" << endl;
            cin >> price;
            store.receiveWidgets(date, time, quantity, price);
            cout << "Would you like to interact with the Widget Store?" << endl;
            cin >> a;
        }
    } // end while
    cout << "Alright then, the Widget Store is closed." << endl;
    return 0;
}