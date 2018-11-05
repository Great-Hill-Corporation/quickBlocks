#!/usr/bin/python
#
# getBals.py
#

import sys
import subprocess
import os
import time
import signal

# Signals handler, to deal with Ctrl+C stuff
def signal_handler(signal, frame):
    print('You pressed Ctrl+C!')
    sys.exit(0)

# Define a signals handler to capture at least Ctrl+C
signal.signal(signal.SIGINT, signal_handler)

os.chdir('../monitors')
os.system('ls | grep -v scripts | grep -v README | grep -v "^file" | grep -v template | grep -v known_contracts | sort -uf >/tmp/junk')
#while True:
with open('/tmp/junk') as f:
    os.system('clear')
    contracts = f.read().splitlines()
    for contract in contracts:
        command = 'cd ' + contract + ' ; NO_COLORS=true cacheMan --cacheBals cache/0x*.acct.bin >../../test/gold/monitors/' + contract + '_bals.txt ; cd - >/dev/null'
#        print(command)
        os.system(command)
        print("Finished " + contract)
    f.close()
os.system('clearLocks')
