# compute a given fibonacci number

# set r0 to the fibonacci number to find
# the result will be placed in r1 at program end
# since this an 8-bit system without carry,
# only the first 12 fibonacci numbers can be
# computed
#    0  1  2  3  4  5   6   7   8   9  10   11   12
# 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
set r0 12

# variables, r1 is the n term, r2 is the n-1 term
set r1 1
set r2 0

# intermediate calculation register (also n)
set r3 1

# left 0 for unconditional jump
set r4 0

# loop counter
mov r0 r5

# used for decrementing loop counter
set r6 -1

loop:
  # end condition
  jmpz r5 end
  
  # n-1 + n
  add r1 r2 r3
  mov r1 r2
  mov r3 r1
  
  # decrement the loop counter
  add r6 r5 r5
  
  # repeat loop
  jmpz r4 loop 
  

end:
  mov r3 r1
  set r2 0
  set r3 0
  set r4 0
  set r5 0
  set r6 0

halt
