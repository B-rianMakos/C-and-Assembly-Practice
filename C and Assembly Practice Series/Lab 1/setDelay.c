void setdelay(int delayTimeInMs){
    int delayTime = delayTimeInMs;
    


    pollDelay(delayTimeInMs);
    
     
}

/*
setdelay:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        mov     DWORD PTR [rbp-20], edi
        mov     eax, DWORD PTR [rbp-20]
        mov     DWORD PTR [rbp-4], eax
        mov     eax, DWORD PTR [rbp-20]
        mov     edi, eax
        mov     eax, 0
        call    pollDelay
        nop
        leave
        ret

*/