import PySimpleGUI as sg
from subprocess import call


file_name = "data_files/PVZ.txt"
f = open(file_name)

months = ["1. January", "2. February", "3. March", "4. April", "5. May", "6. June", "7. July", "8. August", "9. September", "10. October", "11. November", "12. December"]  # is used in buttons

layout = [[sg.Text(" " * 97), sg.Text("Month:", justification='center', font="Any 14")],
    [sg.Button(months[0], size=(15, 5)), sg.Button(months[1], size=(15, 5)), sg.Button(months[2], size=(15, 5)), sg.Button(months[3], size=(15, 5)),
     sg.Button(months[4], size=(15, 5)), sg.Button(months[5], size=(15, 5))],
    [sg.Button(months[6], size=(15, 5)), sg.Button(months[7], size=(15, 5)), sg.Button(months[8], size=(15, 5)), sg.Button(months[9], size=(15, 5)),
     sg.Button(months[10], size=(15, 5)), sg.Button(months[11], size=(15, 5))],
    [sg.Text("Enter or delete the name of the event and its day of month:", font="Any 12")],
    [sg.Text("", size=(20,2), key="selected_month", font="Any 12")],
    [sg.Multiline(f.read(), key="data", size=(80, 15))],
    [sg.Button("Enter data", size=(9, 1)), sg.Text(key="validation", size=(9, 2))],
    [sg.Button("Check for any upcoming events", size=(14, 3))]]

f.close()
window = sg.Window("annual reminder", layout)

if __name__ == '__main__':
    while True:  # main event loop
        event, values = window.read()
        if event == sg.WIN_CLOSED:
            break
        elif event:
            for x in months:
                if event == x:
                    window["selected_month"].Update(event+":ss") # prints out name of the selected month
                    window["validation"].Update("")  # removes "Updated successsfully" text that pops up when "Enter data" button is pressed
                    file_name = "data_files/" + x.replace(". ", "") + ".txt"
                    with open(file_name) as f:
                        window["data"].Update(f.read())  # prints out contents of a selected file in the sg.Multiline() (line 21)
                elif event == "Enter data": # if button "Enter data is pressed:
                    with open(file_name, 'r+') as f:  # overwriting a file with input data from sg.Multiline() section
                        text = f.read()
                        f.seek(0)
                        f.truncate()
                        f.write(values["data"])
                    window["validation"].Update("Updated successfully")
                elif event == "Check for any upcoming events":
                    call(["../back_end/main"])  # executes compiled c++ executable
                    with open("output.txt") as of:  # prints out upcoming events:
                        sg.popup(of.read(), keep_on_top=True, title="Upcoming events")
                    event = ""  # clears the event, so the popup doesn't open again right after closing

    window.close()
