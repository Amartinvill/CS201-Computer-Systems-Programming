.globl vectorized_copy
vectorized_copy:
  cmpq  $4, %rdx
  jl    2f
  
  movq  %rdx, %rcx
  shrq  $2,   %rcx
  leaq  (, %rcx, 4),  %rax
  subq  %rax, %rdx
1:
  vmovupd  (%rdi), %ymm0
  vmovupd  %ymm0,  (%rsi)
  addq  $32,  %rdi
  addq  $32,  %rsi
  loop  1b

2:
  cmpq  $2, %rdx
  jb    3f

  movupd  (%rdi), %xmm0
  movupd  %xmm0,  (%rsi)
  addq  $16,  %rdi
  addq  $16,  %rsi

  subq  $2, %rdx
3:
  cmpq  $0, %rdx
  je    4f

  movsd (%rdi), %xmm0
  movsd %xmm0,  (%rsi)

4:
  ret


.globl vectorized_compare
vectorized_compare:
  cmpq  $4, %rdx
  jl    2f
  
  movq  %rdx, %rcx
  shrq  $2,   %rcx
  leaq  (, %rcx, 4),  %rax
  subq  %rax, %rdx
1:
  # Move four doubles from v1 and four doubles from v2 into %ymm0 and %ymm1, respectively
  vmovupd  (%rdi),  %ymm0
  vmovupd  (%rsi),  %ymm1

  # Compare all four doubles at a time. If a pair of doubles matches, the corresponding bits in
  # %ymm2 will all be set
  vcmppd  $0, %ymm0, %ymm1, %ymm2

  # Move the sign bit from each double in %ymm2 into the lower four bits of %eax and check to ensure
  # that they are all set
  vmovmskpd %ymm2,  %rax
  cmpq  $15,  %rax
  jne   5f

  # Increment pointers appropriately
  addq  $32,  %rdi
  addq  $32,  %rsi
  loop  1b

2:
  cmpq  $2, %rdx
  jb    3f

  vmovupd (%rdi), %xmm0
  vmovupd (%rsi), %xmm1

  vcmppd  $0, %xmm0, %xmm1, %xmm2

  vmovmskpd %xmm2,  %rax
  cmpq  $3, %rax
  jne   5f

  addq  $16,  %rdi
  addq  $16,  %rsi

  subq  $2, %rdx
3:
  cmpq  $0, %rdx
  je    4f

  movsd (%rdi), %xmm0
  cmpsd $0, (%rsi), %xmm0
  movmskpd  %xmm0,  %rax
  andq  $1, %rax
  cmpq  $1, %rax
  jne   5f

  # If we got this far, return true
4:
  movq  $1, %rax
  ret

5:
  movq  $0, %rax
  ret

.global scalar_fma_asm
scalar_fma_asm:
1:
  movsd (%rdi), %xmm0
  movsd (%rsi), %xmm1
  movsd (%rdx), %xmm2
  vfmadd231sd %xmm1, %xmm2,  %xmm0
  movsd %xmm0,  (%rdi)
  addq  $8, %rdi
  addq  $8, %rsi
  addq  $8, %rdx
  loop 1b

.globl rdtsc
rdtsc:
  rdtsc
  shlq  $32,  %rdx
  addq  %rdx, %rax
  ret
