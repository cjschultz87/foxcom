import sys
import socket

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
    
    
########################    
def blank(L):
########################

    index = 0
    
    alpha = []
    
    while index < L:
        alpha.append(0)
        
        index += 1

    return alpha


Payload = []
    
    
Options = []

IHL = 20 + len(Options)
    
    
Base = []

###############
def baseF(val):
###############
    
    Base.append(val)


baseF(dtb(4,4))                                         #type 4
baseF(dtb(IHL,8)[4:8])                                  #internet header length
baseF(blank(8))                                         #standard, no ecn
baseF(dtb(20+(len(Options)/8)+8+(len(Payload)/8),16))   #length
baseF(dtb(67,8)+dtb(74,8))                              #ident
baseF([0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0])                #don't frag
baseF(dtb(64,8))                                        #ttl
baseF(dtb(17,8))                                        #UDP protocol



###
index = 0

address_0 = "255.255.255.255"
address_1 = "255.255.255.255"

address_val = ["","","","","","","",""]

#for digit in argv[4]:
for digit in address_0:
    if digit == '.':
        index += 1
    else:
        address_val[index] += digit
        
index += 1
    
#for digit in argv[5]:
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




index = 0

hex_val = []
base_digits = []

for array in Base:
    for elements in array:
        base_digits.append(elements)

for array in Base:
    for element in array:
        base_digits.append(element)

while index < len(base_digits):
    hex_val.append(dth(btd(base_digits[index:index+16]),4))
    
    index += 16

        
index = 0

while index < len(address_array):
    hex_val.append(dth(btd(address_array[index:index+16]),4))
    
    index += 16

hex_sum = []


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
                carry = hex_sum[index]-16
                hex_sum[index] = 0
            
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
    
hex_sumF(hex_val,hex_sum)       
hex_carryF(hex_sum)

hex_sumR = []
    
index = 0

while index < len(hex_sum):
    hex_sumR.append(hex_sum[len(hex_sum)-(1+index)])
    index += 1
    
binary_sumR = dtb(htd(hex_sum),16)

for element in binary_sumR:
    if element == 0:
        element = 1
    else:
        element = 0
        
Base = []

for element in base_digits:
    Base.append(element)
    
for element in binary_sumR:
    Base.append(element)
    
for element in address_array:
    Base.append(element)



#UDP_source = dtb(int(argv[2]),16)
UDP_source = dtb(30000,16)
#UDP_dest = dtb(int(argv[3]),16)
UDP_dest = dtb(30000,16)

UDP_length = dtb(8 + len(Payload),16)

UDP_Header = UDP_source + UDP_dest + UDP_length + blank(16)



#Header = Base + Options + UDP_Header
#Packet = Header + Payload

def hex_str(array):
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



def addBytes(array0,array1):
    index = 0
    
    while index < len(array0):
        alpha = btd(array0[index:index+8])
        
        array1.append(alpha)
        
        index += 8        
        
Packet = []


addBytes(Base,Packet)
addBytes(Options,Packet)
addBytes(UDP_Header,Packet)
addBytes(Payload,Packet)

for element in Packet:
    element = bytes(Packet)
    
Packet_bravo = bytearray(tuple(Packet))