import mouse
import serial
import time
import re

def parse_coordinates(s):
    # Extract the numbers from the string
    numbers = re.findall(r'\d+', s)

    # Convert the numbers to integers and return them as a list
    return [int(number) for number in numbers]

def read_serial():
    while True:
        try:
            ser = serial.Serial('COM7', 9600)
            ser.flush()

            while True:
                b = ser.readline().decode('utf-8')
                if b != b'':
                    if b.startswith("X: "):
                        coords = parse_coordinates(b)
                        x = int(coords[0])
                        y = int(coords[1])
                        mouse.move((x - 520) / 10, (-y + 513) / 10, absolute=False)

        except serial.serialutil.SerialException:
            print("Serial port not available. Please reconnect the Arduino and try again.")
            time.sleep(2)

        except KeyboardInterrupt:
            print("User terminated the script.")
            ser.close()
            break

if __name__ == '__main__':
    read_serial()