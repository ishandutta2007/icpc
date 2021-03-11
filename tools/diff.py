import filecmp
import os

os.environ['GEN'] = 'gen'
os.environ['TEST'] = 'A'
os.environ['BASELINE'] = 'A_good'

os.system('echo ${GEN} ${TEST} ${BASELINE}')

ca = 0
while True:
    os.system('./${GEN} >${TEST}.in')
    os.system('./${TEST} <${TEST}.in >test.out')
    os.system('./${BASELINE} <${TEST}.in >baseline.out')

    ca += 1
    print("case:", ca)
    if not filecmp.cmp('./test.out', './baseline.out'):
        break
