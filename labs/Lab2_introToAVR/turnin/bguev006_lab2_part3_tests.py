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
        'description': 'PINA: 0xF0 => PORTC: 0x04',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xF0) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x04) ],
    }, ################# test case 1

    {
        'description': 'PINA: 0xF1 => PORTC: 0x03',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xF1) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x03) ],
    }, ################# test case 2


    {
        'description': 'PINA: 0xF3 => PORTC: 0x02',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xF3) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x02) ],
    }, ################# test case 3

    {
        'description': 'PINA: 0xF7 => PORTC: 0x01',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xF7) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x01) ],
    }, ################# test case 4

    {
        'description': 'PINA: 0xFF => PORTC: 0x80',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xFF) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x80) ],
    }, ################# test case 5

    {
        'description': 'PINA: 0xF0 => PORTC: 0x04',

        'steps': 
        [
            {
                'inputs': [ ('PINA', 0xF0) ],
                'iterations': 7
            }
        ],

        'expected': [ ('PORTC', 0x04) ],
    }, ################# test case 6 -- Testing if PC7 turns off after being on.
    ]

#watch = ['PORTB']
# Optionally you can add a set of "watch" variables these need to be global or static and may need
# to be scoped at the function level (for static variables) if there are naming conflicts. The 
# variables listed here will display everytime you hit (and stop at) a breakpoint
# watch = ['<function>::<static-var>','PORTB']

