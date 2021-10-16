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

#Test 1 - Edge case No FUEL
test "PINA: 0xFF => PORTC: 0x20"\n\n
#--
setPINA 0xFF
continue 20
#--
printPINA
printPORTC t
echo ---------------------------------\n
expectPORTC 0x40
checkResult
echo =================================\n\n

#Test 2 - Control LOW FUEL
test "PINA: 0xFC => PORTC: 0x58"\n\n
#--
setPINA 0xFC
continue 20
#--
printPINA
printPORTC t
echo ---------------------------------\n
expectPORTC 0x70
checkResult
echo =================================\n\n

#Test 3 - CONTROL NOT LOW FUEL
test "PINA: 0xF5 => PORTC: 0x1F"\n\n
#--
setPINA 0xF5
continue 20
#--
printPINA
printPORTC t
echo ---------------------------------\n
expectPORTC 0x3E
checkResult
echo =================================\n\n


#Test 4 - Edge case FUEL FULL
test "PINA: 0x00 => PORTC: 0x1F"\n\n
#--
setPINA 0x00
continue 20
#--
printPINA
printPORTC t
echo ---------------------------------\n
expectPORTC 0x3F
checkResult
echo =================================\n\n

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n


