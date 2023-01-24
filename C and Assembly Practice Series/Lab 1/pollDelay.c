#include<stdio.h>

#include <time.h>
void pollDelay(int countOfLoops){

    int count = countOfLoops;
    int count2 = 24;
        for(count; count =0; ++count){     //for loop qui compte combien de 1 ms on a de besoin
            while(count2 != 0){                    //while loop qui crée un delay de 1 ms quand on en a besoin)

            ;               //nop
            
            count2--; 
            }

        }

}

/*
pollDelay(int):
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-20], edi
        mov     eax, DWORD PTR [rbp-20]
        mov     DWORD PTR [rbp-8], eax
        mov     DWORD PTR [rbp-4], 24
        jmp     .L2
.L4:
        sub     DWORD PTR [rbp-4], 1
.L3:
        cmp     DWORD PTR [rbp-4], 0
        jne     .L4
        add     DWORD PTR [rbp-8], 1
.L2:
        mov     DWORD PTR [rbp-8], 0
        cmp     DWORD PTR [rbp-8], 0
        setne   al
        test    al, al
        jne     .L3
        nop
        nop
        pop     rbp
        ret

*/