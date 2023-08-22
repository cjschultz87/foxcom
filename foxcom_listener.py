import sys
import socket

if sys.argv[1] == "h":
    print "foxcom_listener.py <address> <port>"
    
    quit()

sierra = socket.socket(socket.AF_INET,socket.SOCK_RAW,socket.IPPROTO_UDP)

try:
    sierra.bind((sys.argv[1],int(sys.argv[2])))
except:
    print "Enter a valid socket"
    quit()
    
alpha = ''
alpha_packet = []
    
while True:
    alpha = sierra.recv(65535)
    for element in bytearray(alpha):
        alpha_packet.append(element)
    
    for element in alpha_packet:
        print element
        
    print '\n'
