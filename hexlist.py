import sys

if (not(len(sys.argv) == 3)):
	print("hexlist.py <input file> <output file>")
	quit

foxtrot = open(sys.argv[1],"rb")

bravo = foxtrot.read()

foxtrot.close()

alpha_f = []

for b in bravo:
	alpha_f.append(str(b))
	
foxtrot = open(sys.argv[2],"w")

a_L = len(alpha_f) - 1

for i,a in enumerate(alpha_f):
	foxtrot.write(a)
	
	if i < a_L:
		foxtrot.write('\n')
		
foxtrot.close()
