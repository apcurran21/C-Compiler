# Debugging Notes

##
* The 

## Changes
*   I moved the pop_back call (located in the I_rule action) into the else case so that we don't pop from an empty vector whenever encountering the very first Irule instance (ie the start of an entry-point rule)

## Failing tests
* test57
    * at instruction 'mem r13 0 <- rdi' (line 22) there are only two items on parsed_items stack, so popping three elements results in overflow.
    * This is likely due to some combination of a specific register rule not firing and certain register check conditions failing
        * solution is to just assume correctness of the program, and to just create a generic register struct (will need to replace everywhere in the parser yikes)
        * also its very likely that r13 is not getting recognized correctly and getting put into parsed_items