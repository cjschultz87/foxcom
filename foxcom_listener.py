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
    for element in alpha:
        alpha_byte = bytearray(alpha)[alpha.index(element)]
        alpha_binary = ""
        for bit in dtb(alpha_byte,8):
            alpha_binary += str(bit)
        print alpha_binary + "\t\t" + str(alpha_byte) + "\t\t...\t\t" + element
        
    print '\n***\n'
