Prints out upcoming annual events. Events are stored in Notifier/GUI_and_data/data_files/

Data files are specific for each month. Data file format - two words and a day of the event. Seperate Events written on seperate lines.
For eg.: we want to make a notifier for birthdays. Johny's birtday takes place on January 15th, so we press "1. January" button on GUI and enter a following new line:

Johny Johnson 15

Any upcoming annual events (events that are happening within the next week) are written to an output file or can be seen by pressing "Check for any upcoming events" button in GUI.
The data of events and path of output file can also be easily modified with the help of GUI.

GUI is handled by GUI_and_data/main.py, whereas backend - back_end/main.cpp
