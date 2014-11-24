def f(a,b):
        if b==0: return 0
        else: return a/b + f(b,a%b)
a,b = map(int,raw_input().split())
print f(a,b)
