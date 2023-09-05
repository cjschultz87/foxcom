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
    
while True:
    alpha = sierra.recv(65535)
    index = 0
    for element in alpha:
        alpha_byte = bytearray(alpha)[index]
        alpha_binary = ""
        for bit in dtb(alpha_byte,8):
            alpha_binary += str(bit)
        print alpha_binary + "\t\t" + str(alpha_byte) + "\t\t...\t\t" + element + "\t\t" + str(index)
        
        index += 1
        
    print '***'
