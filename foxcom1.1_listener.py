import sys
import socket

def dtb(decimal,L):
#################
    
    try:
        type(decimal) == type(5)
    except:
        print("[0.0]dtb: Type Error")
        quit()
    
    alpha = []
    
    while decimal > 0:
        alpha.append(decimal%2)
        
        decimal //= 2
        
    while len(alpha) < L:
        alpha.append(0)
        
    alpha_return = []
        
    index = 0
    
    while index < len(alpha):
        alpha_return.append(alpha[len(alpha) - (1+index)])
        
        index += 1
        
    return alpha_return

if sys.argv[1] == "h":
    print("foxcom_listener.py <address> <port>")
    
    quit()

sierra = socket.socket(socket.AF_INET,socket.SOCK_DGRAM,socket.IPPROTO_UDP)

try:
    sierra.bind((sys.argv[1],int(sys.argv[2])))
except:
    print("Enter a valid socket")
    quit()
    
alpha = ''

index = 0
    
while True:
    alpha = sierra.recv(65535)
    
    for i,element in enumerate(alpha):
        alpha_binary = ""
        for bit in dtb(element,8):
            alpha_binary += str(bit)
        print(f"{alpha_binary}\t\t{element}\t\t...\t\t{chr(element)}\t\t{str(i)}\t\t{index}")
        
    print("***")
    
    index += 1
