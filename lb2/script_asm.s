.section .note.GNU-stack,"",@progbits
.section .data
arr:
    .long 3, 7, 1, 8, 4, 9, 2, 6, 5, 1

.section .text
.global main
.type main, @function
main:
    push %ebp
    mov %esp, %ebp
    
    movl $5, %ecx   # M = 5
    movl $0, %edx   # sum = 0
    movl $0, %eax   # count = 0
    
    movl $0, %esi   # i = 0
    jmp loop_check_i
    
loop_body:
    movl arr(,%esi,4), %ebx   # arr[i]
    cmpl %ecx, %ebx   # if (arr[i] > M)
    jle else_if
    
    addl %ebx, %edx   # sum += arr[i]
    jmp end_if
    
else_if:
    cmpl %ecx, %ebx   # if (arr[i] < M)
    jge end_if
    
    addl $1, %eax   # count++
    
end_if:
    addl $1, %esi   # i++
    
loop_check_i:
    cmpl $10, %esi   # i < 10
    jl loop_body
    
    # Вывод результатов
    pushl %eax
    pushl %edx # сохранение значения суммы в стеке
    pushl $output_msg_1 # загрузка адреса строки вывода в стек
    call printf # вызов функции printf
    addl $8, %esp # очистка стека
    popl %eax
   
    pushl %eax # сохранение значения количества в стеке
    pushl $output_msg_2 # загрузка адреса строки вывода в стек
    call printf # вызов функции printf  
    addl $8, %esp # очистка стека
    
    movl $1, %eax # код возврата
    int $0x80 # системный вызов exit

output_msg_1:
    .string "S: %d\n"
output_msg_2:
    .string "Количество меньших: %d\n"
