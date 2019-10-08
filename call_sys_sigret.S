#include "syscall.h"
#include "traps.h"

.globl begining_call
.global end_call

begining_call: 
  movl $SYS_sigret, %eax
  int $T_SYSCALL
end_call:
