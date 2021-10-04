# Array of tests to run (in order)
# Each test contains
#   description - 
#   steps - A list of steps to perform, each step can have
#       inputs - A list of tuples for the inputs to apply at that step
#       *time - The time (in ms) to wait before continuing to the next step 
#           and before checking expected values for this step. The time should be a multiple of
#           the period of the system
#       *iterations - The number of clock ticks to wait (periods)
#       expected - The expected value at the end of this step (after the "time" has elapsed.) 
#           If this value is incorrect the test will fail early before completing.
#       * only one of these should be used
#   expected - The expected output (as a list of tuples) at the end of this test
# An example set of tests is shown below. It is important to note that these tests are not "unit tests" in 
# that they are not ran in isolation but in the order shown and the state of the device is not reset or 
# altered in between executions (unless preconditions are used).
tests = [ 
    {
        'description': 'More than 140kg and edge case at 141kg.\nPINA: 0x32\nPINB: 0x32\nPINC: 0x29\nExpect - PORTD: 0x21',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0x32), ('PINB', 0x32), ('PINC', 0x29) ],
                'iterations': 10
            }
        ],

        'expected': [ ('PORTD', 0x21) ],
    }, ################# test case 1 - more than 140kg and edge case at 141kg.

    {
        'description': 'Less than 140kg and edge case at 140kg.\nPINA: 0x32\nPINB: 0x32\nPINC: 0x28\nExpect - PORTD: 0x20',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0x32), ('PINB', 0x32), ('PINC', 0x28) ],
                'iterations': 10
            }
        ],

        'expected': [ ('PORTD', 0x20) ],
    }, ################# test case 2 - less than 140kg and edge case at 140kg.

    {
        'description': 'Balance test |A - C| > 80kg.\nPINA: 0x51\nPINB: 0x28\nPINC: 0x00\nExpect - PORTD: 0x1E', #testing with 121kg with |A - C| = 81kg

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0x51), ('PINB', 0x28), ('PINC', 0x00) ],
                'iterations': 10
            }
        ],

        'expected': [ ('PORTD', 0x1E) ],
    }, ################# test case 3 - Balance test |A - C| > 80kg.

    {
        'description': 'Balance test |A - C| <= 80kg.\nPINA: 0x50\nPINB: 0x28\nPINC: 0x00\nExpect - PORTD: 0x1C', #testing with 120kg with |A - C| = 80kg.

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0x50), ('PINB', 0x28), ('PINC', 0x00) ],
                'iterations': 10
            }
        ],

        'expected': [ ('PORTD', 0x1C) ],
    }, ################# test case 4 - Balance test |A - C| <= 80kg.

    {
        'description': 'Control case - Unballanced, overweight.\nPINA: 0x82\nPINB: 0x14\nPINC: 0x04\nExpect - PORTD: 0x27', #250kg with |A - C| = 126 (unbalanced).

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0x82), ('PINB', 0x14), ('PINC', 0x04) ],
                'iterations': 10
            }
        ],

        'expected': [ ('PORTD', 0x27) ],
    }, ################# test case 5 - Control case - Unballanced, overweight.
    ]

#watch = ['PORTB']
# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
# watch = ['<function>::<static-var>','PORTB']

