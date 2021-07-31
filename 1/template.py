#!/usr/bin/env python3

from pwn import *
import struct


def create_note(conn, size, note):
    conn.sendafter('Enter an option:', '1')
    conn.sendafter('Enter an option:', str(size))
    conn.sendafter('Press enter to stop.\n', note)


def delete_note(conn, index):
    conn.sendafter('Enter an option:', '2')
    conn.sendafter('Enter an option:', str(index))


if __name__ == '__main__':
    binary = ELF('./a.out')
    # conn = gdb.debug("./a.out", '''
    # b * create_note
    # ''')
    conn = process("./a.out")

    # Step 1: Performing the overflow into the top_chunk size field.
    # TODO

    # Step 2: Allocate a "bridging" chunk to get close to our target pointer.
    # TODO
    
    # Step 3: Allocate the chunk that overlaps with our target address. This is where we overwrite the target.
    # TODO

    # Continue interacting with the process.
    conn.interactive()

