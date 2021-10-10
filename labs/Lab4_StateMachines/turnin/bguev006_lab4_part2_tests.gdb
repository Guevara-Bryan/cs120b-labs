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
set state = start
setPINA 0x00
continue 5
expectPORTC 0x07
expect state wait
checkResult
echo \n-------------------------------\n

# Test 2
test "wait transitions test"\n\n
# Set inputs
set state = wait
set PORTC = 0x00
setPINA 0x00
continue 5
expect state wait
expectPORTC 0x00
#--
set state = wait
setPINA 0x01
set PORTC = 0x00
continue 10
expect state addwait
expectPORTC 0x01
#--
set state = wait
setPINA 0x02
set PORTC = 0x02
continue 10
expect state subwait
expectPORTC 0x01
#--
set state = wait
setPINA 0x03
set PORTC = 0x07
continue 10
expect state reswait
expectPORTC 0x00
#----
checkResult
echo \n-------------------------------\n


#Test 3
test "addwait transitions test"\n\n
# Set inputs
set state = addwait
setPINA 0x00
set PORTC = 0x07
continue 5
expect state wait
expectPORTC 0x07
#--
set state = addwait
setPINA 0x01
set PORTC = 0x07
continue 5
expect state addwait
expectPORTC 0x07
#--
set state = addwait
setPINA 0x03
set PORTC = 0x07
continue 5
expect state reswait
expectPORTC 0x00
#----
checkResult
echo \n-------------------------------\n


#Test 4
test "subwait transitions test"\n\n
# Set inputs
set state = subwait
setPINA 0x00
set PORTC = 0x07
continue 5
expect state wait
expectPORTC 0x07
#--
set state = subwait
setPINA 0x02
set PORTC = 0x07
continue 5
expect state subwait
expectPORTC 0x07
#--
set state = subwait
setPINA 0x03
set PORTC = 0x07
continue 5
expect state reswait
expectPORTC 0x00
#----
checkResult
echo \n-------------------------------\n


#Test 5
test "reswait transitions test"\n\n
# Set inputs
set state = reswait
setPINA 0x00
set PORTC = 0x00
continue 5
expect state wait
expectPORTC 0x00
#--
set state = reswait
setPINA 0x03
set PORTC = 0x00
continue 5
expect state reswait
expectPORTC 0x00
#----
checkResult
echo \n-------------------------------\n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
