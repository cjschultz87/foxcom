import sys
import os

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



alphabet = " \n\tabcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\b~!@#$%^&*()_+[]\{}|;':,.//<>?"

encoding = []

index = 0

for letter in alphabet:
    encoding.append([letter])
    
    encoding[index].append(index)
    
    index += 1

try:
    (len(sys.argv) == 5) == True

except:
    print "Invalid number of arguments"
    
    quit()
    
try:
    (sys.argv[1] == "q" or sys.argv[1] == "a") == True

except:
    print "Must use a chevron"
    
    quit()


message = 0    
message_array = []
message_bits = ""


try:
    message = open(sys.argv[2],"rb")
    
except:
    print "File does not exist"
    
    quit()    

if sys.argv[1] == "q":

    index = 0

    while index < os.path.getsize(sys.argv[2]):

        message.seek(index)

        letter_m = message.read(1)
    
        for letter in encoding:
            if letter_m == letter[0]:
                message_array.append(letter[1])
            
        index += 1
    
        
elif sys.argv[1] == "a":
    
    index = 0

    while True:

        letter_m = message.readline()
        
        if letter_m == "":
            break
        elif not(letter_m == "" or letter_m == "\n"):
            message_array.append(int(letter_m))
            
else:
    print "must use valid arg"
    quit


message.close()

for element in message_array:
    element = dtb(element,8)
    
    for bit in element:
        message_bits += str(bit)
              
        
index = 0

key = sys.argv[3]
key_bits = ""

while index < len(key):
    letter_k = key[index]
    alpha = []
    
    for letter in encoding:
        if letter_k == letter[0]:
            alpha = dtb(letter[1],8)
            
    for bit in alpha:
        key_bits += str(bit)
        
    index += 1


def fcom(alpha,bravo):
    index = 0
    
    string = ""
    
    while index < len(bravo):
        if alpha[index] == bravo[index]:
            string += str(0)
        else:
            string += str(1)
        
        index += 1
        
    return string
        

cipher_bits = ""
    
index = len(key_bits) - 1

m_element = message_bits[0:index+1]

while index < len(message_bits):

    cipher_element = fcom(m_element,key_bits)    
    cipher_elementA = []
    
    for element in cipher_element:
        cipher_elementA.append(element)
    
    if index < len(message_bits)-1:
        cipher_bits += cipher_element[0]
        
        index_1 = 0
        while index_1 < len(cipher_element) - 1:
            cipher_elementA[index_1] = cipher_element[index_1+1]
            index_1 += 1
        cipher_elementA[len(cipher_element)-1] = message_bits[index+1]
        cipher_element = ""
        for element in cipher_elementA:
            cipher_element += element
    else:
        cipher_bits += cipher_element
    
    m_element = cipher_element
    
    index += 1

cipher_bytes = []

index = 0

while index < len(cipher_bits):
    alpha = []
    for element in cipher_bits[index:index+8]:
        alpha.append(int(element))
        
    cipher_bytes.append(bytes(btd(alpha)))
        
    index += 8
    
    
if sys.argv[1] == "q":
    for byte in cipher_bytes:
        print byte

elif sys.argv[1] == "a":

    string_out = ""

    for byte in cipher_bytes:
        for letter in encoding:
            if int(byte) == letter[1]:
                string_out += letter[0]
    
    print string_out

