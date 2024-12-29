@ x035-BASIC/func.s
@ Copyright (c) 2024 - 25 C. J. Wilson

        .syntax unified

        .text
        .thumb_func
        
.global func_add
func_add:
    adds r0, r0, r1  // r0 = r0 + r1
    bx lr            // Return to caller

.global func_sub
func_sub:
    subs r0, r0, r1  // r0 = r0 - r1
    bx lr            // Return to caller

.global func_mul
func_mul:
    muls r0, r0, r1  // r0 = r0 * r1
    bx lr            // Return to caller

.global func_div
func_div:
    cbz r1, div_by_zero  // Check if divisor (r1) is zero
    udiv r0, r0, r1      // r0 = r0 / r1
    bx lr

div_by_zero:
    movs r0, #0          // Return 0 if division by zero
    bx lr
    
.global func_mod
func_mod:
    cmp r1, #0             @ Compare divisor (r1) with 0
    beq mod_error          @ Branch to error if divisor is 0
    udiv r2, r0, r1        @ Unsigned divide: r2 = r0 / r1
    mul r3, r2, r1         @ Multiply quotient by divisor: r3 = (r0 / r1) * r1
    subs r0, r0, r3        @ Subtract product from dividend: r0 = r0 - r3
    bx lr                  @ Return

mod_error:
    mov r0, #0             @ Return 0 if division by 0
    bx lr


.global func_pow
func_pow:
    movs r2, #1                @ Initialize result (r2) to 1
    cbz r1, pow_done           @ If exponent (r1) is zero, result is 1
pow_loop:
    mul r2, r2, r0             @ Multiply result (r2) by base (r0)
    subs r1, r1, #1            @ Decrement the exponent (r1)
    bne pow_loop               @ Repeat if exponent is not zero
pow_done:
    mov r0, r2                 @ Move the result to r0
    bx lr                      @ Return
 
 .global func_eq
func_eq:
    cmp r0, r1             @ Compare r0 and r1
    ite eq                 @ If-Then-Else for EQ condition
    moveq r0, #1           @ If equal, set r0 to 1
    movne r0, #0           @ If not equal, set r0 to 0
    bx lr                  @ Return

.global func_neq
func_neq:
    cmp r0, r1             @ Compare r0 and r1
    ite eq                 @ If-Then-Else for NEQ condition
    moveq r0, #0           @ If equal, set r0 to 0
    movne r0, #1           @ If not equal, set r0 to 1
    bx lr                  @ Return

.global func_gt
func_gt:
    cmp r0, r1             @ Compare r0 and r1
    ite gt                 @ If-Then-Else for GT condition
    movgt r0, #1           @ If greater, set r0 to 1
    movle r0, #0           @ Otherwise, set r0 to 0
    bx lr                  @ Return

.global func_lt
func_lt:
    cmp r0, r1             @ Compare r0 and r1
    ite lt                 @ If-Then-Else for LT condition
    movlt r0, #1           @ If less, set r0 to 1
    movge r0, #0           @ Otherwise, set r0 to 0
    bx lr                  @ Return

 .global func_gte
func_gte:
    cmp r0, r1             @ Compare r0 and r1
    ite ge                 @ If-Then-Else for GTE condition
    movge r0, #1           @ If greater or equal, set r0 to 1
    movlt r0, #0           @ Otherwise, set r0 to 0
    bx lr                  @ Return

.global func_lte
func_lte:
    cmp r0, r1             @ Compare r0 and r1
    ite le                 @ If-Then-Else for LTE condition
    movle r0, #1           @ If less or equal, set r0 to 1
    movgt r0, #0           @ Otherwise, set r0 to 0
    bx lr                  @ Return

