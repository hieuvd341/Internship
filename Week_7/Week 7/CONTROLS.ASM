.386
.model flat, stdcall
option casemap: none
WinMain proto :DWORD, :DWORD, :DWORD, :DWORD

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.data
    ClassName       db "SimpleWinClass", 0
    AppName         db "Our First Window", 0
    ButtonClassName db "button", 0
    ButtonText      db "My First Button", 0
    EditClassName   db "edit", 0
    buffer          db 100 dup(?)
    result          db 512 dup(?)

.data?
    hInstance       HINSTANCE ?
    CommandLine      LPSTR ?
    hwndButton      HWND ?
    hwndEdit        HWND ?

.const
    ButtonID        equ 1    ; The control ID of the button control
    EditID          equ 2    ; The control ID of the edit control
    IDM_HELLO       equ 1
    IDM_CLEAR       equ 2
    IDM_GETTEXT     equ 3

.code
start:
    invoke GetModuleHandle, NULL
    mov    hInstance, eax
    invoke GetCommandLine
    mov    CommandLine, eax
    invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
    invoke ExitProcess, eax

WinMain proc hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:DWORD
    LOCAL wc: WNDCLASSEX
    LOCAL msg: MSG
    LOCAL hwnd: HWND

    mov   wc.cbSize, SIZEOF WNDCLASSEX
    mov   wc.style, CS_HREDRAW or CS_VREDRAW
    mov   wc.lpfnWndProc, OFFSET WndProc
    mov   wc.cbClsExtra, NULL
    mov   wc.cbWndExtra, NULL
    push  hInst
    pop   wc.hInstance
    mov   wc.hbrBackground, COLOR_BTNFACE + 1
    mov   wc.lpszClassName, OFFSET ClassName

    invoke LoadIcon, NULL, IDI_APPLICATION
    mov   wc.hIcon, eax
    mov   wc.hIconSm, eax
    invoke LoadCursor, NULL, IDC_ARROW
    mov   wc.hCursor, eax
    invoke RegisterClassEx, addr wc
    invoke CreateWindowEx, WS_EX_CLIENTEDGE, ADDR ClassName, ADDR AppName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInst, NULL
    mov   hwnd, eax
    invoke ShowWindow, hwnd, SW_SHOWNORMAL
    invoke UpdateWindow, hwnd

    .WHILE TRUE
        invoke GetMessage, ADDR msg, NULL, 0, 0
        .BREAK .IF (!eax)
        invoke TranslateMessage, ADDR msg
        invoke DispatchMessage, ADDR msg
    .ENDW

    mov     eax, msg.wParam
    ret
WinMain endp

convert proc
    pushad
    mov esi, 0
    mov edi, offset buffer

    buffer_loop:
        mov edx, 0
        xor al, al
        mov al, byte ptr [edi]
        cmp al, 0
        je done2 ; If it's null, end the function
        mov al, byte ptr [edi]
        mov ebx, 16 ; Divide the number by 16
        div ebx
        add al, '0' ; Convert the quotient to ASCII
        mov [result + esi], al
        inc esi
        inc edi
        .if edx >= 10 ; If the remainder is greater than or equal to 10, it can be ABCDEF
            mov ebx, 10
            sub edx, ebx
            add edx, 'A'
            mov [result + esi], dl
            inc esi
            jmp done1
        .endif
        add edx, '0'
        mov [result + esi], dl
        inc esi
    done1:
        jmp buffer_loop
    done2:
        mov byte ptr [result + esi], 0

    popad
    ret
convert endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
    .IF uMsg==WM_DESTROY
        invoke PostQuitMessage, NULL
    .ELSEIF uMsg==WM_CREATE
        invoke CreateWindowEx, WS_EX_CLIENTEDGE, ADDR EditClassName, NULL, WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or ES_AUTOHSCROLL, 50, 35, 200, 25, hWnd, 8, hInstance, NULL
        mov  hwndEdit, eax
        invoke SetFocus, hwndEdit
        invoke CreateWindowEx, NULL, ADDR ButtonClassName, ADDR ButtonText, WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, 75, 70, 140, 25, hWnd, ButtonID, hInstance, NULL
        mov  hwndButton, eax
    .ELSEIF uMsg==WM_COMMAND
        mov eax, wParam
        .IF lParam==0
            .IF ax==IDM_GETTEXT
                invoke GetWindowText, hwndEdit, ADDR buffer, 100
                invoke convert
                invoke MessageBox, NULL, ADDR result, ADDR AppName, MB_OK
            .ELSE
                invoke DestroyWindow, hWnd
            .ENDIF
        .ELSE
            .IF ax==ButtonID
                shr eax, 16
                .IF ax==BN_CLICKED
                    invoke SendMessage, hWnd, WM_COMMAND, IDM_GETTEXT, 0
                .ENDIF
            .ENDIF
        .ENDIF
    .ELSE
        invoke DefWindowProc, hWnd, uMsg, wParam, lParam
        ret
    .ENDIF
    xor eax, eax
    ret
WndProc endp

end start
