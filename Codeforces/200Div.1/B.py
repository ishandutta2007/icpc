s,a = raw_input(),[]
for c in s:
        if len(a) and a[-1]==c: del a[-1]
        else: a.append(c)
print ('NO','YES')[len(a)==0]
