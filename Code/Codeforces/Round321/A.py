n = input()
A,pre,now,answer = map(int,raw_input().split()),0,0,0

for i in range(n):
    if pre <= A[i]:
        now += 1
        if now > answer:
            answer = now
    else:
        now = 1
    pre = A[i]
print answer