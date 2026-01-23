[BITS 16]           ; Código de 16 bits (Real Mode)
[ORG 0x7C00]        ; Endereço padrão onde a BIOS carrega o bootloader

start:
    ; Configura o modo de vídeo: 320x200 com 256 cores (Modo 13h)
    mov ax, 0x0013
    int 0x10

    mov ax, 0xA000  ; Endereço da memória de vídeo VGA
    mov es, ax

main_loop:
    ; --- Efeito Visual (GDI Primitivo no Boot) ---
    inc word [color_offset]
    xor di, di      ; Começa no pixel 0
    mov cx, 64000   ; Total de pixels (320 * 200)

draw_screen:
    ; Um cálculo matemático simples (x ^ y + offset) para gerar padrões
    mov ax, di
    xor dx, dx
    mov bx, 320
    div bx          ; AX = y, DX = x
    
    xor ax, dx      ; Efeito clássico: x XOR y
    add ax, [color_offset]
    
    stosb           ; Escreve o pixel na memória de vídeo
    loop draw_screen

    ; --- Efeito de Áudio (Bytebeat via PC Speaker) ---
    mov al, 0xB6    ; Configura o timer do PC Speaker
    out 0x43, al
    
    ; Gera uma frequência baseada no contador de cores
    mov ax, [color_offset]
    shl ax, 2       ; Distorce a frequência
    out 0x42, al    ; Envia byte baixo
    mov al, ah
    out 0x42, al    ; Envia byte alto

    ; Liga o alto-falante
    in al, 0x61
    or al, 3
    out 0x61, al

    ; Pequeno delay para não rodar rápido demais
    mov cx, 0xFFFF
delay:
    loop delay

    jmp main_loop   ; Loop infinito

color_offset dw 0

; Preenchimento e Assinatura de Boot
times 510-($-$$) db 0
dw 0xAA55           ; Assinatura mágica para a BIOS reconhecer como bootável