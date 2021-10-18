# Test file for "Lab4_StateMachines"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Test 1
test "start transitions test"\n\n
# Set inputs
setPINA 0xFF
set state = start
c 1
expect state wait
expectPORTB 0x00
checkResult
echo \n-------------------------------\n


# Test 2
test "Pattern test"\n\n
# Set inputs
setPINA 0xFE
set state = wait
c 2
expect state hold
expectPORTB 0x01
c 2
setPINA 0xFF
c 2
setPINA 0xFE
c 2
expect state hold
expectPORTB 0x02
c 2
setPINA 0xFF
c 2
setPINA 0xFE
c 2
expect state hold
expectPORTB 0x05
c 2
setPINA 0xFF
c 2
setPINA 0xFE
c 2
expectPORTB 0x0A
c 2
setPINA 0xFF
c 2
setPINA 0xFE
c 2
expectPORTB 0x15
c 2
setPINA 0xFF
c 2
setPINA 0xFE
c 2
expectPORTB 0x2A
checkResult
echo \n-------------------------------\n


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
