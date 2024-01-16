# Debugging Notes

##
* The 

## Changes
*   I moved the pop_back call (located in the I_rule action) into the else case so that we don't pop from an empty vector whenever encountering the very first Irule instance (ie the start of an entry-point rule)