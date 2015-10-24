a = input()
b = input()
c = input()
if a > c:
    a,c = c,a
if b > c:
    b,c = c,b
if a > b:
    a,b = b,a

if a + b == c or b + b == c or a + a == c or a + a == b:
    print "YES"
else:
    print "NO"
