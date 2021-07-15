# Check if user as pressed a button on ther website via a file
# Then send a command to the arduino according to user input
# Then wait for data from the arduino to write in a file
# Also writes everything that comes to the serial comm in a log file
import serial
import datetime


# Clear a file
def clearFile(path):
    file = open(path, "w")
    file.close()

# Send a start command to Arduino
def start():
    ser.write("{\"command\":\"start\"}\r\n")
    ser.write("{\"setinterval\":\"1\"}\r\n")
    print("start")

# Send a stop command to Arduino
def stop():
    ser.write("{\"command\":\"stop\"}\r\n")
    print("stop")

ser = serial.Serial("/dev/ttyACM0", 9600, timeout=1)

# Generate log file name and opens it (file name is : "Logs-dd-mm-yyyy.json")
htmlPath = "/var/www/html/logs/"
date = datetime.datetime.now()
date_format = date.strftime("%d-%m-%Y")
log_FileName = "Logs-{}.txt".format(date_format)
log_Path = htmlPath + log_FileName
Logs = open(log_Path, "a")

lastId = 0
_start = False
clearFile("/var/www/html/data/commandeWeb.txt")

while True:
    #Check for user command
    f = open("/var/www/html/data/commandeWeb.txt", "r")
    strList = f.read().split(",")

    if len(strList) < 2:
        print "No command"
        continue

    id = strList[0]
    command = strList[1]

    if id != lastId:
        lastId = id
        if command == "start":
            start()
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
