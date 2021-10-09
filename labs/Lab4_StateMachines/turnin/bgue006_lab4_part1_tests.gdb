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
test "start to state1 transition"\n\n
# Set inputs
set state = start
setPINA 0x00
continue 10
expectPORTB 0x01
expect state state1
checkResult
echo \n-------------------------------\n

# Test 2
test "state1 transitions/actions test"\n\n
# Set inputs
set state = state1
setPINA 0x00
continue 10
expectPORTB 0x01
expect state state1
#--
setPINA 0x01
continue 10
expect PORTB 0x02
expect state onpress1
#--
checkResult
echo \n-------------------------------\n

# Test 3
test "onpress1 transitions/actions test"\n\n
# Set inputs
set state = onpress1 
setPINA 0x01
continue 10
expectPORTB 0x02
expect state onpress1
#--
setPINA 0x00
continue 10
expectPORTB 0x02
expect state state2
#--
checkResult
echo \n-------------------------------\n

# Test 4
test "state2 transitions/actions test"\n\n
# Set inputs
set state = state2
setPINA 0x00
continue 10
expectPORTB 0x02
expect state state2
#--
setPINA 0x01
continue 10
expectPORTB 0x01
expect state onpress2
#--
checkResult
echo \n-------------------------------\n

# Test 5
test "onpress2 transitions/actions test"\n\n
# Set inputs
set state = onpress2
setPINA 0x01
continue 10
expectPORTB 0x01
expect state onpress2
#--
setPINA 0x00
continue 10
expectPORTB 0x01
expect state state1
#--
checkResult
echo \n-------------------------------\n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
