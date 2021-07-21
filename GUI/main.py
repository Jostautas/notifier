import PySimpleGUI as sg


file_name = "../back_end/data_files/PVZ.txt"
f = open(file_name)

months = ["1. January", "2. February", "3. March", "4. April", "5. May", "6. June", "7. July", "8. August", "9. September", "10. October", "11. November", "12. December"]  # is used in buttons

layout = [[sg.Text(" " * 97), sg.Text("Month:", justification='center', font=("Any 14"))],
    [sg.Button(months[0], size=(15, 5)), sg.Button(months[1], size=(15, 5)), sg.Button(months[2], size=(15, 5)), sg.Button(months[3], size=(15, 5)),
     sg.Button(months[4], size=(15, 5)), sg.Button(months[5], size=(15, 5))],
    [sg.Button(months[6], size=(15, 5)), sg.Button(months[7], size=(15, 5)), sg.Button(months[8], size=(15, 5)), sg.Button(months[9], size=(15, 5)),
     sg.Button(months[10], size=(15, 5)), sg.Button(months[11], size=(15, 5))],
    [sg.Text("Enter or delete the name of the event and its day of month:", font=("Any 12"))],
    [sg.Multiline("EXAMPLE:" + '\n' + f.read(), key="name", size=(80, 15))],
    [sg.Button("Enter data", size=(9, 2)), sg.Text(key="validation", size=(9,2))]]

window = sg.Window("annual reminder", layout, size=(880, 600))

if __name__ == '__main__':
    while True:  # main event loop
        event, values = window.read()
        if event == sg.WIN_CLOSED:
            break
        elif event:
            for x in months:
                if event == x:
                    file_name = "../back_end/data_files/" + x.replace(". ", "") + ".txt"
                    f = open(file_name)
                    window["name"].Update(f.read())  # prints out contents of a selected file in the sg.Multiline() (line 21)
                    f.close()
                elif event == "Enter data":
                    with open(file_name, 'r+') as f:
                        #print(values["name"])
                        text = f.read()
                        f.seek(0)
                        f.write(values["name"])
                        f.truncate()
                    window["validation"].Update("Updated succesfully")
    window.close()
