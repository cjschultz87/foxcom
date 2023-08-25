import sys
import socket
import time

foxtrot = sys.argv[1]
port_0  = sys.argv[2]
port_1  = sys.argv[3]
address_0 = sys.argv[4]
address_1 = sys.argv[5]



#################
def dtb(decimal,L):
#################
    
    try:
        type(decimal) == type(5)
    except:
        print "[0.0]dtb: Type Error"
        quit()
    
    alpha = []
    
    while decimal > 0:
        alpha.append(decimal%2)
        
        decimal /= 2
        
    while len(alpha) < L:
        alpha.append(0)
        
    alpha_return = []
        
    index = 0
    
    while index < len(alpha):
        alpha_return.append(alpha[len(alpha) - (1+index)])
        
        index += 1
        
    return alpha_return
    
################    
def btd(binary):
################

    try:
        type(binary) == type([])
    except:
        print "[1.0]]btd: Type Error"
        quit()
        
    try:
        len(binary) > 0
    except:
        print "[1.1]btd: Array must have at least one element"
        quit()

    for digit in binary:
        if digit > 1:
            print "[1.2]btd: Elements in array must be binary"
            quit()
        
        
    int_return = 0
    
    index = 0
    
    while index < len(binary):
        int_return += binary[index] * pow(2,len(binary) - (1+index))
        
        index += 1
        
    return int_return
    

########################
def dth(decimal,L):
########################
    
    try:
        type(decimal) == type(5)
    except:
        print "[2.0]dtb: Type Error"
        quit()
    
    alpha = []
    
    while decimal > 0:
        alpha.append(decimal%16)
        
        decimal /= 16
    
    while len(alpha) < L:
        alpha.append(0)
    
    alpha_return = []
        
    index = 0
    
    while index < len(alpha):
        alpha_return.append(alpha[len(alpha) - (1+index)])
        
        index += 1
        
    return alpha_return
    
    
#############    
def htd(hex):
#############
    
    try:
        type(hex) == type([])
    except:
        print "[3.0]]htd: Type Error"
        quit()
        
    if type(hex) == type("sierra"):
        for element in hex:
            element = int(element)
        
    try:
        len(hex) > 0
    except:
        print "[3.1]htd: Array must have at least one element"
        quit()

    for digit in hex:
        if digit > 15:
            print "[3.2]htd: Elements in array must be hex"
            quit()
        
        
    int_return = 0
    
    index = 0
    
    while index < len(hex):
        int_return += hex[index] * pow(16,len(hex) - (1+index))
        
        index += 1
        
    return int_return
    
###################    
def hex_str(array):
###################

    alpha = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']
    
    bravo = ""
    
    index_0 = 0
    
    while index_0 < len(array):
        index_1 = 0
        
        while index_1 < len(alpha):
            if array[index_0] == index_1:
                bravo += alpha[index_1]
                
                break
            index_1 += 1
        index_0 += 1
                
    return bravo

    
    
########################    
def blank(L):
########################

    index = 0
    
    alpha = []
    
    while index < L:
        alpha.append(0)
        
        index += 1

    return alpha
    
####################    
def dice(bitLength):
####################

    alpha = []
    
    index = 0
    
    while index < bitLength:
        alpha.append(int((time.clock()*1000000)%2))
        
        index += 1
        
    return alpha

if foxtrot == "h" or not(len(sys.argv) == 7):
    print "foxcom.py <payload> <source port> <destination port> <source address> <destination address>"
    
    quit()
    
    
    
    
def reg_number(c,b):
    bravo = 0
    
    numbers = "0123456789abcdefghijklmnopqrstuvwxyz"
    
    numbers = numbers[0:int(b)]
    
    index = 0
    
    while index < len(numbers):
        if numbers[index] == c:
            bravo = 1
            
            break
        
        index += 1
        
    return bravo
    
def address_ident(address):
    ident = 1
    
    def address_verification(array,bound):
        ident = 1
        
        index = 0
        
        ident_val = 1
        
        n_bound = 0
        
        if bound == '.':
            n_bound = 10
        elif bound == ':':
            n_bound = 16
        else:
            n_bound = 0
        
        while index < len(array):
            while array[index] == bound:
                index += 1
            
            if reg_number(array[index],n_bound) == 0:
                ident = 0
                
                break
                
            index += 1
            
        return ident
    
    if address_verification(address,'.') == 0:
        ident = 2
        
    if ident == 2 and address_verification(address,':') == 0:
        ident = 0
    
    if ident == 1:
        return "four"
    elif ident == 2:
        return "six"
    else:
        return "zero"
        
        
        
        
if not(address_ident(address_0) == address_ident(address_1)):
    print "addresses must be either ipv4 or ipv6 and not both or neither"
    
    quit()
        

 

 
mac_source = ""        #source
mac_destination = ""   #phone

mac_sourceA = []
mac_destinationA = []

def mac_htb(mac,array):
    index = 0
    
    mac_hex = []
    
    alpha = ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']
    
    while index < len(mac):
        
        if not(mac[index] == ':'):
            index_1 = 0
            
            while index_1 < len(alpha):
                if mac[index] == alpha[index_1]:
                    mac_hex.append(index_1)
                
                index_1 += 1
                
            if index == len(mac)-1:
                array.append(dtb(htd(mac_hex),8))
                mac_hex = []
        else:
            array.append(dtb(htd(mac_hex),8))
            mac_hex = []
        
        index += 1
    
mac_htb(mac_destination,mac_sourceA)
mac_htb(mac_source,mac_destinationA)

MAC = []

for array in mac_sourceA:
    for element in array:
        MAC.append(element)
        
for array in mac_destinationA:
    for element in array:
        MAC.append(element)
        

Payload = []

Payload_file = open(foxtrot,"rb")

while True:

    letter_m = Payload_file.readline()
        
    if letter_m == "":
        break
    elif not(letter_m == "" or letter_m == "\n"):
        Payload.append(int(letter_m))

Payload_file.close()

UDP_length = dtb(8 + len(Payload),16)

Payload_prime = []

for element in Payload:
    Payload_prime.append(dtb(element,8))

Payload = []

for array in Payload_prime:
    for element in array:
        Payload.append(element)
    
    
Options = []

IHL = (20 + len(Options)/8)/4

    
    
Base = []

###############
def baseF(val):
###############
    
    Base.append(val)



address_val = []


if address_ident(address_0) == "six":
    baseF(dtb(6,4))                                         #type 6
    baseF(blank(8))                                         #standard, no ecn
    baseF(dice(20))                                         #ident
    baseF(dtb(8+(len(Payload)/8),16))                       #payload length
    baseF(dtb(17,8))
    baseF(dtb(64,8))
    
    address_val = ["","","","","","","","","","","","","","","",""]
    
    skip_val = 0
    
    index = 0
    
    def address_compile(index,array_0,array_1):
        index_1 = 0
        
        while index_1 < len(array_0):
            if array_0[index_1] == ':':
                index += 1
                index_1 += 1
                
                if index_1+1 < len(array_0):
                    if array_0[index_1 + 1] == ':':
                        sierra_val = 0
                        for element in array_0:
                            if element == ':':
                                sierra_val += 1
                    
                        index_2 = 0
                    
                        while index_2 < 7 - sierra_val:
                            array_1[index] += '0'
            
            array_1[index] += array_0[index_1]
            
            index_1 += 1
        
        return (index,array_1)
        
    rVal = address_compile(index,address_0,address_val)
    
    address_val
    
    index = 8
    
    rVal = address_compile(index,address_0,address_val)
    
    
    for element in address_val:
        hex_array = []
        
        hex = "0123456789abcdef"
        
        for value in element:
            hex_array.append(hex.index(value))
            
        address_val[address_val.index(element)] = dtb(htd(hex_array),16)
        
    array_bits = []
    
    for array in Base:
        for element in array:
            array_bits.append(element)

    for array in address_val:
        for element in array:
            array_bits.append(element)
            
    Base = array_bits

elif address_ident(address_0) == "four":

    baseF(dtb(4,4))                                         #type 4
    baseF(dtb(IHL,4))                                       #internet header length
    baseF(blank(8))                                         #standard, no ecn
    baseF(dtb(20+(len(Options)/8)+8+(len(Payload)/8),16))   #length
    baseF(dice(16))                                    #ident
    baseF([0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0])                #frag
    baseF(dtb(65,8))                                        #ttl
    baseF(dtb(17,8))                                        #UDP protocol


    ###
    index = 0

    address_val = ["","","","","","","",""]

    #source
    for digit in address_0:
        if digit == '.':
            index += 1
        else:
            address_val[index] += digit
        
    index += 1

    #destination    
    for digit in address_1:
        if digit == '.':
            index += 1
        else:
            address_val[index] += digit

    address_array = []

    index = 0

    for element in address_val:
        address_val[index] = dtb(int(element),8)
    
        index += 1

    for array in address_val:
        for element in array:
            address_array.append(element)

    ###

    hex_val = []
    base_digits = []

    for array in Base:
        for element in array:
            base_digits.append(element)

    index = 0

    while index < len(base_digits):
        hex_val.append(dth(btd(base_digits[index:index+16]),4))
    
        index += 16

        
    index = 0

    while index < len(address_array):
        hex_val.append(dth(btd(address_array[index:index+16]),4))
    
        index += 16   
 
    hex_valR = []

    index = 0

    while index < len(hex_val):
        hex_valR.append([])
            
        index_1 = 0
    
        while index_1 < len(hex_val[index]):
            hex_valR[index].append(hex_val[index][index_1])
        
            index_1 += 1
        index += 1

    def hex_sumF(hex_val,hex_sum):

        index = 0

        while index < len(hex_val[0]):
    
            index_1 = 0
    
            hex_sum.append(0)
    
            while index_1 < len(hex_val):
        
                hex_sum[index] += hex_val[index_1][index]
            
                index_1 += 1
            
            index += 1
        

    def hex_carryF(hex_sum):

        def hex_carryFR(hex_sum):
        
            index = 0
        
            carry = 0
        
            while index < len(hex_sum):
        
                hex_sum[index] += carry
        
                carry = 0
        
                if hex_sum[index] > 15:
                    carry = hex_sum[index]/16
                    hex_sum[index] = hex_sum[index]%16
                
                if index == len(hex_sum) - 1:
                    if carry > 0:
                        hex_sum.append(carry)
                        carry = 0
        
                index += 1
            
        hex_carryFR(hex_sum)
        
        while len(hex_sum) > 4:
            hex_sum[0] += hex_sum[4]
            hex_sum.pop(4)
            hex_carryFR(hex_sum)
        
    hex_sum = []
    
    hex_sumF(hex_valR,hex_sum)
       
    hex_carryF(hex_sum)

    hex_sumR = []
    
    index = 0

    while index < len(hex_sum):
        hex_sumR.append(hex_sum[len(hex_sum)-(1+index)])
        index += 1
    
    binary_sumR = dtb(htd(hex_sum),16)
    
    binary_sum = []

    index = 0

    while index < len(binary_sumR):
        L = len(binary_sumR)-1
        if binary_sumR[L-index] == 0:
            binary_sum.append(1)
        else:
            binary_sum.append(0)
    
        index += 1


        
    Base = []

    for element in base_digits:
        Base.append(element)
    
    for element in binary_sum:
        Base.append(element)
    
    for element in address_array:
        Base.append(element)

else:
    print "Use a valid address pair"
    
    quit()



#Port numbers
UDP_source = dtb(int(port_0),16)
UDP_dest = dtb(int(port_1),16)

UDP_Header = UDP_source + UDP_dest + UDP_length + blank(16)



#Header = Base + Options + UDP_Header
#Packet = Header + Payload


def addBytes(array0,array1):
    index = 0
    
    while index < len(array0):
        alpha = btd(array0[index:index+8])
        
        array1.append(alpha)
        
        index += 8        
        
Packet = []

###
addBytes(MAC,Packet)
addBytes(dtb(8,8),Packet)
addBytes(blank(8),Packet)
###
addBytes(Base,Packet)
addBytes(Options,Packet)
addBytes(UDP_Header,Packet)
addBytes(Payload,Packet)

for element in Packet:
    element = bytes(Packet)
   
Packet_bravo = bytearray(tuple(Packet))

sierra = socket.socket(socket.AF_PACKET,socket.SOCK_RAW,socket.htons(3))

sierra.bind((sys.argv[6],int(port_1)))

sierra.send(Packet_bravo)

sierra.close()
