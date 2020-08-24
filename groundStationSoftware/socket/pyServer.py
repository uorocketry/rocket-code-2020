import socket
import serial          
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

# s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind(('127.0.0.1', port))         
print("socket binded to %s" %(port))
  
# put the socket into listening mode 
s.listen(5)
print("socket is listening")


# ser.write(b'hello')     # write a string
  
# a forever loop until we interrupt it or  
# an error occurs 

with serial.Serial('/dev/ttyACM0', 9600, timeout=1) as ser:
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
                
                x = ser.read()          # read one byte
                #x = b'1'
                # read serial
                # if not data: break
                c.send(x)
                #sleep(1)
