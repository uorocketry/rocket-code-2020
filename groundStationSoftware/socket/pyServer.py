import socket
import serial
import time   
import sys
import glob


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
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result 

#from time import sleep

#ttyACM0
# next create a socket object 
s = socket.socket()
print("Socket successfully created")
  
# reserve a port on your computer in our 
# case it is 12345 but it can be anything 
port = 8080

# Next bind to the port 
# we have not typed any ip in the ip field 
# instead we have inputted an empty string 
# this makes the server listen to requests  
# coming from other computers on the network 

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind(('127.0.0.1', port))         
print("socket binded to %s" %(port))
  
# put the socket into listening mode 
s.listen(5)
print("socket is listening")



# ser.write(b'hello')     # write a string

# a forever loop until we interrupt it or  
# an error occurs 
def openSerial():
    global ser
    valid = False
    while(not valid):
        time.sleep(1)
        try:
            ser = serial.Serial(serial_ports()[0], 9600, timeout=1)
            ser.flush()
            valid = True
        except:
            valid = False
            

openSerial()
# s = ser.read(1)        # read up to ten bytes (timeout)
# line = ser.readline()   # read a '\n' terminated line

while True:   
    # Establish connection with client. 
    c, addr = s.accept()
    with c:
        print('Connected by', addr)
        while True:
            # data = c.recv(1024)
            # print("[RECEIVED] " + data.decode("utf-8"));
            try:
                x = ser.read()          # read one byte
            except:
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
