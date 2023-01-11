disk_load:
	pusha
	push dx

	mov ah, 0x02
	mov al, dh   ;number of sectors to read
	mov cl, 0x02 ;sector co-ord

	mov ch, 0x00 ;cylinder co-ord
	mov dh, 0x00 ;head co-ord

	int 0x13
	jc disk_error

	pop dx
	cmp al, dh   ;restore dh, then compare expected sectors read with actual
	jne sectors_error
	popa
	ret

disk_error:
	mov bx, DISK_ERROR
	call print
	call print_nl
	mov dh, ah   ;Print error in ah, and disk number in dl
	call print_hex
	jmp disk_loop

sectors_error:
	mov bx, SECTOR_ERROR
	call print

disk_loop:
	jmp $

DISK_ERROR:   db "Disk read error", 0
SECTOR_ERROR: db "Incorrect number of sectors read", 0
