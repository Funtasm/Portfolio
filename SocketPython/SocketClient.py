#Seth Larson
#example taken from https://realpython.com/python-sockets/ for base of program.
import socket 
import time  #used for sleep commands for better user experience
a=True
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #create socket s
    while a:#sloppy method to allow a re-attempt at connecting to a different IP
       try: #try+except handler if bad IP is given.
        a=False  
        print("Input the IP or website to connect to.")
        HOST = input()  # The server's hostname or IP address, must be inputted
        PORT = 23456       # Server Port
        print ("Connecting to ",HOST,"...")
        s.connect((HOST, PORT))
       except Exception as e: #give IP and port back, and error message.
        print("Cannot connect with %s:%d. %s" % (HOST, PORT, e))
        a=True #restart the loop, allowing for more connection attempts.
        time.sleep(.5)
    time.sleep(.5)
    print ("Connected.") 
    print ("List of valid commands: \n\nTIME\nQUIT\n")
    while True:
                Command=input() 
                s.sendall(Command.encode('utf-8')) #makes sure input is in bytes
                data = s.recv(1024)
                if (data==b"QUIT"): #if reply from server is QUIT, connection is terminated.
                     break
                print(data.decode('utf-8')) #removes the b in front of string message.
print("Connection Terminated.")
time.sleep(1)
print("Closing Program...")
time.sleep(1.5)
