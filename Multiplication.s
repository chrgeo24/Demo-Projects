#  Author:  Chris George
#  Filename: project3.s
#  Creation Date: 11/6/25
#  Last Modified: 11/10/25
#  Due Date: 11/12/25
#  Course: CPSC235-020
#  Professor Name:  Professor Jacklitsch
#  Assignment:   Project 3  
#  Purpose: convert two strings into ints
#           multiply them then output them  


.intel_syntax noprefix
.global _start

.data
    multiplicandRequestMessage: .asciz "Please enter your multiplicand: "
    multiplierRequestMessage:   .asciz "Please enter your multiplier:   "
    productNoticeMessage:       .asciz "Your product is "

.text

# ======================================================================
# Procedure Name:   StdinToCstringProc
# Description:      Reads characters from stdin into an array until a 
#                   newline and null terminates it so its a cstring
# Parameters:       [ebp+8]  - address of array
#                   [ebp+12] - maximum length
#                   [ebp+16] - prompt string address
# Local Variables:  none
# Returns:          EAX = number of characters stored in array
# ======================================================================
StdinToCstringProc:
    push ebp
    mov  ebp, esp

    # print multiplicandRequestMessage
    mov eax, 4
    mov ebx, 1
    mov ecx, [ebp+16]
    mov edx, 32                         # 32 characters in the message
    int 0x80


    # parameters
    mov esi, [ebp+8]                    # array
    mov edi, [ebp+12]                   # max length
    dec edi                             # leaves room for null terminator

    # reads user input into 
    mov eax, 3              
    mov ebx, 0              
    mov ecx, esi      
    mov edx, edi       
    int 0x80


    mov ecx, 0                          # char counter
    mov edx, esi                        # move array address into edx

    LengthLoop1:
        cmp byte ptr [edx], 10          # checks for newline terminator
        je Done1
        cmp byte ptr [edx], 0           # null terminator
        je Done1
        inc ecx                         # goes to next char
        inc edx                         # count++
        jmp LengthLoop1


    Done1:
    mov byte ptr [esi+ecx], 0

    mov eax, ecx
    mov esp, ebp
    pop ebp
    ret



# ======================================================================
# Procedure Name:   CstringToIntProc
# Description:      Converts a cstring to an int
# Parameters:       [ebp+8] - address of input cstring
# Local Variables:  none
# Returns:          EAX = integer switched from cstring
# ======================================================================
CstringToIntProc:
    #save registers
    push ebp
    mov  ebp, esp
    push ebx
    push ecx
    push edx
    

    mov  ebx, [ebp+8]                   # points to string
    mov  eax, 0                         # result
    mov  ecx, 0                         # count
    

    Convert:
        movzx edx, byte ptr [ebx+ecx]   # load char
        cmp   dl, 0                     # checks for null terminator
        je    Done2
        cmp   dl, 10                    # checks for newline
        je    Done2

        sub   dl, '0'                   # ASCII to digit
        imul  eax, eax, 10              # multiply by ten 
        add   eax, edx                  # add new digit
        inc   ecx                       # count++
        jmp   Convert

    Done2:
        pop   edx
        pop   ecx
        pop   ebx
        pop   ebp
        ret



# ======================================================================
# Procedure Name:   InputIntStdinProc
# Description:      read an int from stdin
# Parameters:       [ebp+8] - prompt string address
# Local Variables:  [ebp-12] - 12 byte array of chars
# Returns:          EAX = integer value entered by the user
# ======================================================================
InputIntStdinProc:
    push ebp
    mov  ebp, esp

    sub esp, 12                 # allocate for array
    lea eax, [ebp-12]           # eax = address of array

    push dword ptr [ebp+8]      # push prompt
    push 12                     # pushes max length
    push eax                    # pushes array address
    call StdinToCstringProc     
    add  esp, 12                # clean args

    lea eax, [ebp-12]           # eax = address of array
    push eax
    call CstringToIntProc
    add  esp, 4                 # clean args

    mov esp, ebp
    pop ebp
    ret



# ======================================================================
# Procedure Name:   IntToCstringProc
# Description:      Converts an integer into cstring
# Parameters:       [ebp+8]  - array address
#                   [ebp+12] - integer to convert
# Local Variables:  none
# Returns:          EAX = number of chars in cstring without null
# ======================================================================
IntToCstringProc:
    push ebp
    mov  ebp, esp

    # save registers
    push ebx
    push ecx
    push edx
    

    mov  edi, [ebp+8]           # edi = array    
    mov  eax, [ebp+12]          # eax = value to be converted  

            
        mov ebx, 10             # for base 10 coversion            
        mov ecx, 0              # count           


    reconvertStart:
        mov edx, 0
        div ebx                 # puts remainder in edx              
        add dl, '0'             # converts remainder to digit            
        push dx                 # push digit onto stack              
        inc ecx                 # count ++             
        cmp eax, 0              # if not zero got back to start
        jnz reconvertStart

                 

    Flip:
        pop dx                  # pop digit of stack
        mov [edi], dl           # write low byte
        inc edi                 # edi++
        dec ecx
        jnz Flip                # goes till ecx = 0

        mov byte ptr [edi], 0   # null terminates

        mov eax, edi            # returns how many chars
        sub eax, [ebp+8]        # start of array   

    Done4:
        pop edx
        pop ecx
        pop ebx
        pop ebp
        ret




# ======================================================================
# Procedure Name:   CstringToStdoutProc
# Description:      writes a cstring to stdout
# Parameters:       [ebp+8] - address of array
# Local Variables:  none
# Returns:          EAX = number of characters written
# ======================================================================
CstringToStdoutProc:
    push ebp
    mov  ebp, esp

    # saves registers
    push ecx
    push edx
    push edi

    mov edi, [ebp+8]                # edi = address of array
    mov ecx, edi                    # counter to scan string
    mov edx, 0                      # char counter                  

    LengthLoop2:
        cmp  byte ptr [ecx], 0      # checks for null terminator
        je   Done5
        inc  ecx                    # goes to next char
        inc  edx                    # count++
        jmp  LengthLoop2

    Done5:
        mov  eax, 4                 # write
        mov  ebx, 1           
        mov  ecx, edi               # array address
        int  0x80

        mov  eax, edx               # return count

        pop  edi
        pop  edx
        pop  ecx
        pop  ebp
        ret



# ======================================================================
# Procedure Name:   OutputIntStdoutProc
# Description:      Writes an int to stdout
# Parameters:       [ebp+8] - int value to print
# Local Variables:  [ebp-12] - 12 byte array of chars
# Returns:          None
# ======================================================================
OutputIntStdoutProc:
    push ebp
    mov  ebp, esp

    sub esp, 16                 # allocates for local array      
    lea eax, [ebp-12]           # eax = address of array

    push dword ptr [ebp+8]      # push int     
    push eax                    # push array address               
    call IntToCstringProc
    add  esp, 8                 # cleans args

    lea eax, [ebp-12]           # eax = address of array
    push eax                    # push array address
    call CstringToStdoutProc
    add  esp, 4                 # clean args

    mov esp, ebp
    pop ebp
    ret



# ======================================================================
# Procedure Name:   _start
# Description:      multiplies two numbers
# Parameters:       None
# Local Variables:  [ebp-4]  - multiplicand
#                   [ebp-8]  - multiplier
#                   [ebp-12] - product
# Returns:          0 on success
# ======================================================================
_start:
    push ebp
    mov  ebp, esp
    sub  esp, 12                                # allocates 12 bytes

    lea ebx, [multiplicandRequestMessage]       # loads prompts address

    push ebx                                    # push prompt onto stack
    call InputIntStdinProc
    add  esp, 4                                 # clean args
    mov  [ebp-4], eax                           # mutiplicand = eax

    lea ebx, [multiplierRequestMessage]         # loads prompt address

    push ebx                                    # push prompt onto stack 
    call InputIntStdinProc
    add  esp, 4                                 # clean args
    mov  [ebp-8], eax                           # multiplier = eax

    mov  eax, [ebp-4]
    imul eax, dword ptr [ebp-8]
    mov  [ebp-12], eax                          # product = eax

    lea ebx, [productNoticeMessage]             # loads prompt address

    push ebx                                    # push prompt onto stack 
    call CstringToStdoutProc
    add  esp, 4                                 # clean args

    push dword ptr [ebp-12]                     # push product
    call OutputIntStdoutProc
    add  esp, 4                                 # clean args


    # \n 
    sub esp, 1
    mov byte ptr [esp], 10
    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    mov edx, 1
    int 0x80
    add esp, 1

    # exit
    mov eax, 1
    mov ebx, 0
    int  0x80
