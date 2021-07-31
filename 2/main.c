#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#define NOTEMAX 10

char* notes[NOTEMAX] = { 0 };
int note_counter = 0;
int (*say)(const char*, ...) = printf;

long prompt() {
	char buf[16];

	say("Enter an option: ");
	if (read(0, buf, 16) < 0) {
		fprintf(stderr, "Error: something went wrong in the prompt.\n");
		exit(1);
	}

	return strtol(buf, NULL, 0);
}

void help() {
	say("system @ %p\n", system);
	say("gimmie ");
	say("/bin/sh\n");
	say("1. Create a note (%d/%d)\n", note_counter, NOTEMAX);
	say("2. Delete a note\n");
	say("3. Exit\n");
}

void create_note() {
	if (note_counter >= NOTEMAX) {
		say("Notes full. Exit and try again.\n");
		return;
	}

	long size = 0;
	char* note = NULL;

	say("How big is your note in bytes?\n");
	size = prompt();
	say("Size = 0x%x\n", size);
	note = malloc(size);
	notes[note_counter] = note;
	note_counter++;

	say("Begin writing your note. Press enter to stop.\n");\
	
	if(size > 0)
	{
		size = size + 0x10;
	}
	else
	{
		size = 0x20;
	}

	if (read(0, note, size) < 0) {
		fprintf(stderr, "Error: something went wrong writing your note.\n");
		exit(2);
	}

	say("Chunk @ %p\n", note);
}

void delete_note() {
	if (note_counter <= 0) {
		say("There are no notes. Go make some.");
		return;
	}

	long index = 0;

	say("Provide the index of the note.\n");
	index = prompt();
	free(notes[index]);
}

int main() {
	long option = 0;

	setvbuf(stdout, NULL, 0x2, 0);

	while (1) {
		option = 0;

		help();
		option = prompt();

		switch (option) {
			case 1:
				create_note();
				break;
			case 2:
				delete_note();
				break;
			case 3:
				exit(0);
				break;
			default:
				say("Unknown option. Try again.\n");
				break;
		}
	}
}
