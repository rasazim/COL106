import sys
import random as rnd
sys.set_int_max_str_digits(0)

num_cases = 100
max = 10**100

out = []

out.append(num_cases)

for _ in range(num_cases):
    l1 = rnd.randint(0,max)
    l2 = rnd.randint(0,max)
    out.append(l1)
    out.append(l2)
    out.append(l1+l2)
    out.append(l1-l2)
    out.append(l1*l2)
    out.append(l1//l2)
    rem = l1%l2
    if(rem<0):
        rem=rem+abs(l2)
    out.append(rem)


f = open("tests.txt","w")

for a in out:
    f.write(str(a)+"\n")

f.close()

