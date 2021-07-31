#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc.h>

#define NOTEMAX 10

int leet = 0;
char* notes[NOTEMAX] = { 0 };
int note_counter = 0;

long prompt() {
	char buf[16];

	printf("Enter an option: ");
	if (read(0, buf, 16) < 0) {
		fprintf(stderr, "Error: something went wrong in the prompt.\n");
		exit(1);
	}

	return strtol(buf, NULL, 0);
}

void help() {
	printf("Are you 1337 yet?\n");
	
	if (leet) {
		printf("YEP! You're 1337!\n");
	}
	else {
		printf("Nope. Try again :)\n");
	}

	printf("1. Create a note (%d/%d)\n", note_counter, NOTEMAX);
	printf("2. Delete a note\n");
	printf("3. Exit\n");
}

void create_note() {
	if (note_counter >= NOTEMAX) {
		printf("Notes full. Exit and try again.\n");
		return;
	}

	long size = 0;
	char* note = NULL;

	printf("How big is your note in bytes?\n");
	size = prompt();
	printf("Size = 0x%x\n", size);
	note = malloc(size);
	notes[note_counter] = note;
	note_counter++;

	printf("Begin writing your note. Press enter to stop.\n");\
	
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

	printf("Chunk @ %p\n", note);
}

void delete_note() {
	if (note_counter <= 0) {
		printf("There are no notes. Go make some.");
		return;
	}

	long index = 0;

	printf("Provide the index of the note.\n");
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
				printf("Unknown option. Try again.\n");
				break;
		}
	}
}
