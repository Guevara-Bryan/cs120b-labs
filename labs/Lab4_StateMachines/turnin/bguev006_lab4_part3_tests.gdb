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
expectPORTC wait
expect state wait
checkResult
echo \n-------------------------------\n


# Test 2
test "wait transitions test"\n\n
#--
set state = wait
set PORTB = 0x00  
setPINA 0x00
continue 5
expect state wait
expectPORTB 0x00
expectPORTC wait
#-- Control case - transition to itself
set state = wait
set PORTB = 0x00  
setPINA 0x05
continue 5
expect state wait
expectPORTB 0x00
expectPORTC wait
#-- transition to wait2
set state = wait
set PORTB = 0x00  
setPINA 0x04
continue 5
expect state wait2
expectPORTB 0x00
expectPORTC wait2
#-- transition to lock
set state = wait
set PORTB = 0x01  
setPINA 0x80
continue 5
expect state lock
expectPORTB 0x00
expectPORTC lock
#----
checkResult
echo \n-------------------------------\n


# Test 3
test "wait2 transitions test"\n\n
#-- transition to open
set state = wait2
set PORTB = 0x00  
setPINA 0x02
continue 5
expect state open
expectPORTB 0x01
expectPORTC open
#-- control: transition to wait
set state = wait2
set PORTB = 0x00  
setPINA 0x04
continue 5
expect state wait
expectPORTB 0x00
expectPORTC wait
#----
checkResult
echo \n-------------------------------\n


# Test 4
test "open transitions test"\n\n
#-- transition to wait
set state = open
set PORTB = 0x01  
setPINA 0x00
continue 5
expect state wait
expectPORTB 0x01
expectPORTC wait
#-- control: transition to itself
set state = open
set PORTB = 0x01  
setPINA 0x02
continue 5
expect state open
expectPORTB 0x01
expectPORTC open
#----
checkResult
echo \n-------------------------------\n


# Test 5
test "lock transitions test"\n\n
#-- transition to wait
set state = lock
set PORTB = 0x00 
setPINA 0x00
continue 5
expect state wait
expectPORTB 0x00
expectPORTC wait
#-- control: transition to itself
set state = lock
set PORTB = 0x00 
setPINA 0x04
continue 5
expect state lock
expectPORTB 0x00
expectPORTC lock
#----
checkResult
echo \n-------------------------------\n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
