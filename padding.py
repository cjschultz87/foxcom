import sys
import time

def dice(max):
    max_prime = max
    
    n = 0
    
    while max_prime > 0:
        n += 1
        
        max_prime /= 10
        
    index = 0
    
    rVal = 0
    
    while index < n:
        rVal += int((time.clock()*1000000)%10) * pow(10,index)
        
        index += 1
        
    rVal %= max
    
    return rVal

foxtrot = ""

try:
    foxtrot = open(sys.argv[1],"rb")
    
except:
    print "Invalid file"
    quit()
    
N = 0


try:
    N = int(sys.argv[2])
    
except:
    print "Invalid integer"
    quit()
    
    
    
bytes = []

alpha = 0

index = 0

while True:

    foxtrot.seek(index)

    alpha = foxtrot.read(1)
    
    if alpha == '':
        break
        
    bytes.append(alpha)
        
    index += 1
    

foxtrot.close()


index = 0

while index < N:
    bytes.append(dice(255))
    
    index += 1
    
    
foxtrot_out = open(sys.argv[1],"wb")

foxtrot_out.write(bytearray(bytes))
    
foxtrot_out.close()
