[BITS 16]
[ORG 0x7C00]

start:
    ; Configura Modo 13h (320x200, 256 cores)
    mov ax, 0x0013
    int 0x10

    ; Setup Segmento de Vídeo em ES
    push 0xA000
    pop es

    ; Inicializa FPU para cálculos matemáticos
    fninit

main_loop:
    inc word [t]        ; t = nosso contador de tempo (frames)
    xor di, di          ; Começa no pixel 0 da tela

draw_screen:
    ; CX = X (0 a 319), DX = Y (0 a 199)
    mov ax, di
    xor dx, dx
    mov bx, 320
    div bx              ; AX = Y, DX = X
    mov [x], dx
    mov [y], ax

    ; --- SELETOR DE PAYLOADS BASEADO NO TEMPO (t) ---
    mov ax, [t]
    shr ax, 9           ; Muda de efeito a cada 512 frames
    and ax, 3           ; Cicla entre 4 efeitos principais

    cmp ax, 0
    je effect_plasma
    cmp ax, 1
    je effect_tunnel
    cmp ax, 2
    je effect_xor_zoom
    jmp effect_mandelbrot_fake

; --- PAYLOAD 1: PLASMA WAVES ---
effect_plasma:
    mov ax, [x]
    add ax, [t]
    xor ax, [y]
    add ax, [t]         ; (x + t) ^ (y + t)
    jmp render

; --- PAYLOAD 2: RADIAL TUNNEL ---
effect_tunnel:
    mov ax, [x]
    sub ax, 160         ; Centraliza X
    imul ax, ax         ; x^2
    mov bx, [y]
    sub bx, 100         ; Centraliza Y
    imul bx, bx         ; y^2
    add ax, bx          ; x^2 + y^2 (Distância ao centro)
    shr ax, 4           ; Escala
    sub ax, [t]         ; Move o túnel para "frente"
    jmp render

; --- PAYLOAD 3: XOR ZOOM FRACTAL ---
effect_xor_zoom:
    mov ax, [x]
    sub ax, 160
    mov bx, [t]
    add ax, bx          ; Zoom/Scroll X
    mov bx, [y]
    sub bx, 100
    xor ax, bx          ; Efeito clássico de XOR
    jmp render

; --- PAYLOAD 4: INTERFERENCE PATTERNS ---
effect_mandelbrot_fake:
    mov ax, [x]
    imul ax, [t]
    mov bx, [y]
    imul bx, [t]
    add ax, bx
    shr ax, 8
    jmp render

render:
    ; Aplica uma paleta de cores "cíclica"
    and al, 0xFF        ; Limita a 256 cores
    stosb               ; Escreve AL na memória ES:DI e incrementa DI

    cmp di, 64000       ; Fim da tela?
    jb draw_screen

    ; Sincronização simples (Wait for Vertical Retrace)
    ; Isso evita que a imagem "rasgue"
    mov dx, 0x03DA
.wait_retrace:
    in al, dx
    test al, 8
    jz .wait_retrace

    jmp main_loop

; --- VARIÁVEIS ---
t dw 0
x dw 0
y dw 0

; --- ASSINATURA E PREENCHIMENTO ---
times 510-($-$$) db 0
dw 0xAA55

; --- COMO FAZER A .IMG NO ASSEMBLY ---
; O VMware exige 1.44MB. O comando abaixo preenche o resto do arquivo.
times 1474560-($-$$) db 0