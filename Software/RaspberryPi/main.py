# Check if user as pressed a button on ther website via a file
# Then send a command to the arduino according to user input
# Then wait for data from the arduino to write in a file
# Also writes everything that comes to the serial comm in a log file
import serial
import datetime
import os


# Clear a file
def clearFile(path):
    file = open(path, "w")
    file.close()

# Send a start command to Arduino
def start(int):
    ser.write("{\"command\":\"start\"}\r\n")
    ser.write("{\"setinterval\":\""+int+"\"}\r\n")
    print("start\ninterval =" + int)

# Send a stop command to Arduino
def stop():
    ser.write("{\"command\":\"stop\"}\r\n")
    print("stop")

ser = serial.Serial("/dev/ttyACM0", 9600);

htmlPath = "/var/www/html/logs/"
log_FileName = "Logs.txt"
log_Path = htmlPath + log_FileName
i = 1

while os.path.isfile(log_Path):
    log_FileName = "Logs-{}.txt".format(i)
    log_Path = htmlPath + log_FileName
    i+=1

lastlog = open(htmlPath + "lastlog.txt", "w")
lastlog.write(log_FileName)
lastlog.close()

Logs = open(log_Path, "a")

lastId = 0
_start = False
clearFile("/var/www/html/data/commandeWeb.txt")

while True:
    #Check for user command
    f = open("/var/www/html/data/commandeWeb.txt", "r")
    strList = f.read().split(",")
    print strList[0]

    if strList[0] == '':
        continue

    id = strList[0]

    if id != lastId:
        lastId = id
        command = strList[1]
        if command == "start":
            interval = strList[2]
            start(interval)
            _start = True
        elif command == "stop":
            stop()
            _start = False

    # If user has not input a command or a stop command, do nothing
    if not _start :
        continue

    print("Reading Serial")

    # Else, read serial comm
    line = ser.read_until('\n')

    # If a message is available
    if len(line) == 0:
        print("Serial unavailable")
        continue

    print("Serial received")
    Logs.write(line.decode("utf-8") + " ...\r\n") # Writes to log file
    dataLog = open("/var/www/html/data/data.txt", "w") # Open data log and erase it if it exists

    # Write only json in data log
    if line[0] == "{" :
        dataLog.write(line.decode("utf-8") + " ...\r\n")

    dataLog.close()
