#Seth Larson
#example taken from https://realpython.com/python-sockets/ for base of program.
import socket
import datetime
import time #used for sleep commands for better user experience
HOST = ''  #Blank allows all connections leading to the current machine.
PORT = 23456        # Server Port

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #create socket s
    s.bind((HOST, PORT)) #host server socket s with given HOST and PORT
    s.listen() #listen for incoming traffic on socket s
    print("Server Started.")
    conn, addr = s.accept() #allow any connection into socket s with correct port
    with conn: #over established connection, do:...
        print('Connected by', addr)
        while True:
            data = conn.recv(1024) #data up to 1024 bytes recieved
            if (data==b"TIME"): #time command given by client, now get and send time
                TIME=datetime.datetime.now()
                print("TIME requested.")
                Timestr=TIME.strftime("%Y-%m-%d %H:%M:%S%z") #converts TIME obj into string
                print(Timestr)
                conn.sendall(Timestr.encode('utf-8'))  #removes the b in front of string message.
            elif (data==b"QUIT"): #quit command given by client, now close connection and reply.
                conn.sendall(data)
                print("QUIT requested.")
                print("Closing connection to ",addr,"...")
                s.close()
                break
            elif data: #command not understood, give feedback
                conn.sendall(b"Invalid Command.")
                print("Invalid Command.")
                
print("Exiting program...") #user knows program is ending.
time.sleep(1.5)
