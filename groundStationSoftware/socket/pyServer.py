import socket
import serial
import time   
import sys
import glob
import signal
from sys import exit

address = '192.168.1.1'
port = 8080


def closeConnection():
    print("\nClosing connection.")
    try:
        server.shutdown(socket.SHUT_RDWR) 
        server.close()
    except:
        pass
    try:
        ser.close()
    except:
        pass


def handler(signal_received, frame):
    closeConnection()
    exit()


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            serialCom = serial.Serial(port)
            serialCom.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result 


def openSerial():
    global ser
    valid = False
    while(not valid):
        time.sleep(1)
        try:
            ser = serial.Serial([(port) for port in serial_ports() if 'ACM' in port][0], 9600, timeout=1)
            ser.flush()
            valid = True
            print("Serial communication established.")
        except:
            valid = False


signal.signal(signal.SIGINT, handler) # ctlr + c
signal.signal(signal.SIGTSTP, handler) # ctlr + z

global server
# next create a socket object 
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print("Socket successfully created.")

server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server.bind((address, port))         
print("Socket binded to %s." %(port))
  
# put the socket into listening mode 
server.listen(5)
print("Socket is listening.")
            
openSerial()

while True:   
    # Establish connection with client. 
    try:
        c, addr = server.accept()
    except:
        # server has been closed
        break
    with c:
        print('Connected by', addr)
        while True:
            try:
                x = ser.read()          # read one byte
            except:
                print("Serial communication lost.")
                openSerial()
                break

            try:
                c.send(x)
            except:
                break
            #x = b'1'
            # read serial
            # if not data: break
                
            #sleep(1)
        print("Client disconnected.")

          
