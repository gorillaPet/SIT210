import tkinter as tk
import RPi.GPIO as GPIO

# # rpi pins setup

GPIO.setmode(GPIO.BCM)

LED_PINS = {
    "Living Room": 17,
    "Bathroom": 27,
    "Closet": 22
}

for pin in LED_PINS.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

# # Function to control LEDs
def select_room():
    selected = room_var.get()
    for room, pin in LED_PINS.items():
        if room == selected:
            print(room + " " + str(pin) + " activated.")
        GPIO.output(pin, GPIO.HIGH if room == selected else GPIO.LOW)

# # Cleanup on exit
def on_exit():
    GPIO.cleanup()
    print("Closed.")
    root.destroy()
    

# tkinter setup
root = tk.Tk()
root.geometry("400x450")
root.title("Linda's Light Switch")
root.resizable(True, True)

room_var = tk.StringVar()
room_var.set("")

root.tk.call("tk", "scaling", 4) #make everything bigger

tk.Label(root, text="Select Room").pack(pady=10)

for room in LED_PINS:
    tk.Radiobutton(root, text=room, variable=room_var,
                   value=room, command=select_room).pack(anchor="w", pady=5, padx=20)

tk.Button(root, text="Exit", command=on_exit).pack(pady=10)

root.mainloop()