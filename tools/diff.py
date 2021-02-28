import filecmp
import os

ca = 0
while True:
    os.system('./gen >F.in')
    os.system('./F <F.in >F.out')
    os.system('./F_good <F.in >F_good.out')

    ca += 1
    print("case:", ca)
    if not filecmp.cmp('./F.out', './F_good.out'):
        break
