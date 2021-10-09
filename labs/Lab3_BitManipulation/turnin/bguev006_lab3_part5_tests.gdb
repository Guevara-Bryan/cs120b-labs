# Test file for "Lab3_BitManipulation"


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

# Add tests below

#Test 1 - Edge case: current weight = 5lbs
test "TEST 5lbs - PIND: 0x02 PINB: 0x01 => PORTB: 0x01"\n\n
#--
setPIND 0x02
setPINB 0x01
continue 20
#--
printPIND
printPINB 
printPORTB
echo ---------------------------------\n
expectPORTB 0x01
checkResult
echo =================================\n\n


#Test 2 - Edge case: current weight = 70lbs
test "TEST 70lbs - PIND: 0x23 PINB: 0x00 => PORTB: 0x02"\n\n
#--
setPIND 0x23
setPINB 0x00
continue 20
#--
printPIND
printPINB 
printPORTB
echo ---------------------------------\n
expectPORTB 0x02
checkResult
echo =================================\n\n


#Test 3 - Control: current weight > 70lbs
test "TEST 100lbs - PIND: 0x32 PINB: 0x00 => PORTB: 0x02"\n\n
#--
setPIND 0x32
setPINB 0x00
continue 20
#--
printPIND
printPINB 
printPORTB
echo ---------------------------------\n
expectPORTB 0x02
checkResult
echo =================================\n\n

#Test 4 - Control: Test 5 < current weight < 70
test "TEST 45lbs - PIND: 0x16 PINB: 0x01 => PORTB: 0x05"\n\n
#--
setPIND 0x16
setPINB 0x01
continue 20
#--
printPIND
printPINB 
printPORTB
echo ---------------------------------\n
expectPORTB 0x05
checkResult
echo =================================\n\n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n


