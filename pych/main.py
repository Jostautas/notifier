import PySimpleGUI as sg

def print_hi(name):
    # Use a breakpoint in the code line below to debug your script.
    print(f'Hi, {name}')  # Press Ctrl+F8 to toggle the breakpoint.

f = open('data.txt')

layout = [
    [sg.Text(" " * 97), sg.Text("Month:", justification='center')],
    [sg.Button("1. Jan", size=(15, 5)), sg.Button("2. Feb", size=(15, 5)), sg.Button("3. Mar", size=(15, 5)), sg.Button("4. Apr", size=(15, 5)), sg.Button("5. May", size=(15, 5)), sg.Button("6. Jun", size=(15, 5))],
    [sg.Button("7. Jul", size=(15, 5)), sg.Button("8. Aug", size=(15, 5)), sg.Button("9. Sep", size=(15, 5)), sg.Button("10. Oct", size=(15, 5)), sg.Button("11. Nov", size=(15, 5)), sg.Button("12. Dec", size=(15, 5))],
    [sg.Text("Enter or delete the name of the event and its day of month:")],
    [sg.Multiline(f.read())]
]

window = sg.Window("annual reminder", layout, size=(880, 400))

if __name__ == '__main__':
    while True:
        event, values = window.read()
        if event:
            print(event)
        else:
            if event == sg.WIN_CLOSED:
                break
    window.close()
