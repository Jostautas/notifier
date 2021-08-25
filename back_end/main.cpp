#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
//#include <chrono> //uncomment for compatibility with windows
//#include <ctime> //uncomment for compatibility with windows

using namespace std;

time_t t = time(0);     // gets time
tm*now = localtime(&t);    // gets current time

int February_days(){   // counts how many days are in February
    if(((now->tm_year + 1900) % 400 == 0) || ((now->tm_year + 1900) % 4 == 0 && (now->tm_year + 1900) %100 !=0))
        return 29;
    else
        return 28;
}

string Month[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

string Data(int x = 0){     // when this function will used for upcoming month, the x will be 1
    int variable = now->tm_mon + 1 + x;
    string beginning = "[ENTER_ABSOLUTE_PATH]/GUI_and_data/data_files/"; // in linux, before adding this program to launch on startup, an absolute path to the "data_files" folder is required, eg:
									// string beginning = "/home/[username]/Programs/notifier/GUI_and_data/data_files/";
    string end = ".txt";
    stringstream ss;
    ss << variable;
    string string_variable;
    ss >> string_variable;
    return beginning + string_variable + Month[variable-1] + end;
}

void output_path(string &path){ // reads contents from path_to_output_folder.txt and determines where to save the output file
    ifstream F("../GUI_and_data/path_to_output_folder.txt");
    getline(F, path);
    F.close();
}

int Days[12] = {31, February_days(), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // how many days are in each month

int main()
{
    string path;
    output_path(path);
    ofstream R(path + "/output.txt"); // "path" stores an absolute path to where output.txt is stored
    R << " _________ " << (now->tm_year + 1900) << "-" << setw(2) << setfill('0') << (now->tm_mon + 1) << "-" << setw(2) << setfill('0') << now->tm_mday << " _________" << endl << endl; // prints out current time (YYY-MM-DD)
    ifstream F(Data(0));    // start of reading current month events
    int k1 = 0; // if there are upcoming events, and the month of the event hasn't been printed out, prints out the month. If there are no upcoming events, k1 if remain 0 and "There are no upcoming events" will be printed
    int k2 = 0; // checks if there are any upcoming events next month
    int day; // temporary variable for event day
    string name, surname; // temporary variables for name ant surname
    while(F >> name >> surname >> day){ // while cycles until all data is read. data consists of name, surname and day.
        if((now->tm_mday + 7 >= day) && (day >= now->tm_mday)){ // if day of the event is in 7 or less days, and current day is not greater that the day of the event
            if(k1 == 0){
                R << "     " << Month[now->tm_mon] << ":" << endl; // prints out name of current month
                k1++;
            }
            R << name << " " << surname << " " << setw(2) << setfill('0') << day << endl;    // print out name, surname, and day of the event
        }
    }
    //------- Next month
    if(now->tm_mday > Days[now->tm_mon] - 7){   // if there are less than a week of the current month remaining, data from next month is read
        if(now->tm_mon < 11){ // if month is not December (because 12+1=13)
            ifstream F(Data(1));    // start of reading next month events
            while(F >> name >> surname >> day){
                if(((day - 7) >= -7) && (day - 7 <= now->tm_mday - Days[now->tm_mon])){   // if next month's event day minus 7 days <= -7 and <= current day minus total day count of the month
                    if(k2 == 0){
                        R << endl << "     " << Month[now->tm_mon+1] << ":" << endl;
                        k2++;
                    }
                    R << name << " " << surname << " " << setw(2) << setfill('0') << day << endl;
                }
            }
        }
        else if(now->tm_mon == 11){ // if current month is december, we need to read data from the first month file
            ifstream F(Data(-11));    // start of reading next month (first month) events
            while(F >> name >> surname >> day){ 
                if(((day - 7) >= -7) && (day - 7 <= now->tm_mday - Days[0])){   // if day of the event - 7 >= -7, but day of the event - 7 <= current day - total day count of the month
                    if(k2 == 0){
                        R << endl << "     " << Month[0] << ":" << endl;
                        k2++;
                    }
                    R << name << " " << surname << " " << setw(2) << setfill('0') << day << endl;
                }
            }
        }
        else
            R << "Error" << endl;
    }
    if((k1 == 0) && (k2 == 0)) // if there are no upcoming events print:
	    R << "There are no upcoming events" << endl;
    F.close();
    R.close();
    return 0;
}
