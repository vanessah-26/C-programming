/*
* Using the Functions
*
*   Use these functions to create and manipulate sets of integers 0 through 7.
*   Read the function headers for descriptions of their use.
*
* Implement these functions using the C bitwise operations:
*
*   &   bitwise and
*   |   bitwise or
*   ^   bitwise xor (exclusive or)
*   <<  shift left
*   >>  shift right
*   ~   invert all bits (one's complement)
*
* You are not required to use ALL of the operators mentioned above,
* although you will use most of them.
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>

/*
*
* This type lets you declare a set with type Set.  We represent the Set
* using an 8-bit, unsigned integer.  Sets can contains integers from 0
* through 7.  The table below shows how each member is represented.  If
* more than one member is in a set, then more than one 1 will appear in the
* binary representation.
*
*                                representation
*   set member  bit number    binary    hexadecimal
*   ----------  ----------  ----------  -----------
*        0           0      0b00000001     0x01
*        1           1      0b00000010     0x02
*        2           2      0b00000100     0x04
*        3           3      0b00001000     0x08
*        4           4      0b00010000     0x10
*        5           5      0b00100000     0x20
*        6           6      0b01000000     0x40
*        7           7      0b10000000     0x80
*/
typedef uint8_t Set;

/*
* This function returns an empty set.  You can assign its return value
* to a variable of type Set.
*/
Set set_empty(void);

/*
* This function returns the universal set.  You can assign its return value
* to a variable of type Set.
*/
Set set_universal(void);

/*
* Determine whether the Set s has member x.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 7.
*
* Return value:  true (== 1) if x is in s
*                false (== 0) otherwise
*/
bool set_member(Set s, int x);

/*
* Add the member x to the Set s.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 7.
*
* Return value:  the new Set, which will contain member x.
*/
Set set_insert(Set s, int x);

/*
* Remove the member x from the Set s.
*
*   s:  a variable of type Set.
*   x:  an integer value from 0 through 7.
*
* Return value:  the new Set, which will not contain member x.
*/
Set set_remove(Set s, int x);

/*
* Compute the union of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain members that are in
*                either s or t.
*/
Set set_union(Set s, Set t);

/*
* Compute the intersection of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that are in
*                both s and t.
*/
Set set_intersect(Set s, Set t);

/*
* Compute the difference of two sets.
*
*   s:  a variable of type Set.
*   t:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that are in
*                s but NOT in t.
*/
Set set_difference(Set s, Set t);

/*
* Compute the complement of a set.
*
*   s:  a variable of type Set.
*
* Return value:  the new Set, which will contain only members that
*                are NOT in s.
*/
Set set_complement(Set s);
