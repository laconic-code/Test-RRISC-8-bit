# multiply 2 numbers together
# multiply r0 by r1 and store
# the result in r2

# input
set r0 23
set r1 11

# output
set r2 0

# loops to do for multiplication
mov r0 r5

# loop decrementer
set r6 -1

loop:
  jmpz r5 end
  add r1 r2 r2
  add r6 r5 r5
  jmp loop
  
end:
  set r3 0
  set r4 0
  set r5 0
  set r6 0

halt