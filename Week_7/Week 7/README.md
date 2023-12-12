# Bài tập tuần 7: Lập trình assembly

## Các thanh ghi trong kiến trúc Intel x86
For convenience, I will respond in English in this section.
### General purpose register
General register are the one we use most of the time Most of the instructions perform on these registers. They all can be broken down into 16 and 8 bit registers.
- EAX(32 bit), AX(16 bit), AL AL(8 bit) 
- EBX(32 bit), BX(16 bit), BL BH(8 bit)
- ECX(32 bit), CX(16 bit), CL CX(8 bit)
- EDX(32 bit), DX(16 bit, DL DH(8 bit))

The "H" and "L" suffix on the 8 bit registers stand for high byte and low byte. With this out of the way, let's see their individual main use:

- EAX,AX,AH,AL : Called the Accumulator register. It is used for I/O port access, arithmetic, interrupt calls, etc...
- EBX,BX,BH,BL : Called the Base register. It is used as a base pointer for memory access. Gets some interrupt return values
- ECX,CX,CH,CL : Called the Counter register. It is used as a loop counter and for shifts. Gets some interrupt values
- EDX,DX,DH,DL : Called the Data register. It is used for I/O port access, arithmetic, some interrupt calls.

### Segment register
Segment registers hold the segment address of various items. They are only available in 16 values. They can only be set by a general register or special instructions. Some of them are critical for the good execution of the program and you might want to consider playing with them when you'll be ready for multi-segment programming:

- CS: Holds the Code segment in which your program runs. Changing its value might make the computer hang.
- DS: Holds the Data segment that your program accesses. Changing its value might give erronous data.
- ES, FS, GS: These are extra segment registers available for far pointer addressing like video memory and such.
- SS         : Holds the Stack segment your program uses. Sometimes has the same value as DS.Changing its value can give unpredictable results, mostly data related.

### Indexes and pointers
Indexes and pointer and the offset part of and address. They have various uses but each register has a specific function. They some time used with a segment register to point to far address (in a 1Mb range). The register with an "E" prefix can only be used in protected mode.

- ES:EDI EDI DI : Destination index register
Used for string, memory array copying and setting and for far pointer addressing with ES

- DS:ESI EDI SI : Source index register. Used for string and memory array copying

- SS:EBP EBP BP : Stack Base pointer register. Holds the base address of the stack
                
- SS:ESP ESP SP : Stack pointer register. Holds the top address of the stack

- CS:EIP EIP IP : Index Pointer. Holds the offset of the next instruction. It can only be read 

### The EFLAGS register
The EFLAGS register hold the state of the processor. It is modified by many intructions and is used for comparing some parameters, conditional loops and conditionnal jumps. Each bit holds the state of specific parameter of the last instruction. Here is a listing :
|  Bit  | Label |     Description      |
| :---: | :---: | :------------------: |
|   0   |  CF   |      Carry flag      |
|   2   |  PF   |     Parity flag      |
|   4   |  AF   | Auxiliary carry flag |
|   6   |  ZF   |      Zero flag       |
|   7   |  SF   |      Sign flag       |
|  10   |  DF   |    Direction flag    |
|  11   |  OF   |    Overflow flag     |
|  21   |  ID   |       ID flag        |

## The basic structure of an Assembly language instruction on Intel architecture
The basic structure of an Assembly language instruction on Intel architecture typically consists of the following parts:
>|[label:]    | instruction   |   operand(s)|
>|:----------:|:-------------:|:-----------:|

- Label (Optional): A label is used to mark a position in the program. It is optional and is often used in jump instructions or to mark the location of functions or code blocks.

- Instruction: This is the most crucial part of the instruction, determining the specific action the instruction will perform. Examples of instructions include MOV (move data), ADD (addition), SUB (subtraction), JMP (jump), and many more.

- Operand(s): Operands are data or memory locations that the instruction will operate on. Operands can be registers, constants, or memory locations. An instruction may have one or multiple operands, depending on the specific instruction.

For example, an instruction like MOV (move data) on the Intel x86-32 architecture could look like this:
> MOV EAX, 42

## Ý nghĩa của một số thanh ghi đặc biệt: stack pointer, frame pointer, v.v..
Để nói về ý nghĩa của các thanh ghi, trước hết chúng ta cần nói về tổ chức bộ nhớ trong máy tính
![Screenshot 2023-10-15 140542](https://i.imgur.com/PLoPkj6.png)

- text segment: chứa các lệnh thực thi, có thể share được, read-only
- initialized data(data segment): chứa các biến global, các biến tĩnh đã được khởi tạo hoặc khác 0 
-  uninitialized data(data segment): chứa các biến global, các biến tĩnh bằng 0 hoặc chưa được khởi tạo
-  heap: vùng nhớ động
-  stack![stack](https://i.imgur.com/lNw41nO.png)

theo hình vẽ, stack pointer là con trỏ trỏ đến đầu stack
còn ebp là con trỏ ghi địa chỉ của hàm trả về 

## Cách viết hàm và gọi tham số trong assembly trên kiến trúc Intel
Viết hàm và gọi tham số trong Assembly trên kiến trúc Intel x86 có thể thực hiện thông qua việc sử dụng ngăn xếp (stack) để truyền tham số và quản lý việc gọi hàm. Dưới đây là một ví dụ đơn giản về cách viết một hàm và gọi nó trong Assembly trên kiến trúc x86-32:



```asm
.386
.model flat, stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\kernel32.lib

.data
myNumber DWORD 5

.data?
result DWORD ?

.code
start:
    ; Gọi hàm và truyền tham số
    push myNumber  ; Đẩy tham số (myNumber) vào ngăn xếp
    call myFunction  ; Gọi hàm myFunction

    ; Kết quả trả về được lưu trong thanh ghi EAX

    ; Kết thúc chương trình
    invoke ExitProcess, 0

myFunction PROC
    ; Hàm myFunction bắt đầu từ đây
    push ebp  ; Lưu giá trị của ebp
    mov ebp, esp  ; Gán ebp cho giá trị của esp

    ; Lấy tham số từ ngăn xếp
    mov eax, [ebp + 8]  ; Offset 8 là vị trí của tham số

    ; Thực hiện các thao tác với tham số ở đây
    ; Ví dụ:
    mov ebx, eax  ; Di chuyển tham số vào thanh ghi khác nếu cần
    add ebx, 10   ; Ví dụ thực hiện phép cộng

    ; Lưu kết quả vào biến result
    mov result, ebx

    ; Trả về giá trị kết quả
    mov eax, ebx

    pop ebp  ; Khôi phục giá trị của ebp
    ret
myFunction ENDP

end start

```

Trong ví dụ này:
- Chúng ta sử dụng .386 để chỉ định kiến trúc x86-32 và .model flat, stdcall để sử dụng kiến trúc phẳng và chuẩn định kiểu tham số.
- Sử dụng include và includelib để kết nối với các thư viện hệ thống.
- Tham số được đẩy vào ngăn xếp bằng lệnh push, và hàm được gọi bằng call.
- Kết quả trả về từ hàm myFunction được lưu trong thanh ghi EAX.
- Cuối cùng, chương trình kết thúc bằng lệnh invoke ExitProcess, 0.
