#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv[])
{
	// TO DO: open SHM_FILE for using shm_open()
	//	check if the file was successfully open
	int shm_fd;
	shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
	if(shm_fd == -1){
		printf("fail to open\n");
		return 1;
	}
	int buffer_size = sizeof(KeyBuffer);
	// TO DO: set size of the shared memory by buffer_size

	ftruncate(shm_fd, buffer_size);
	KeyBuffer *key_buffer = NULL;
	// TO DO: map the shared memory file and receive the return address into key_buffer
	//	check if the file was successfully mapped
	key_buffer = mmap(0, buffer_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(key_buffer == MAP_FAILED) return 1;

	// TO DO: initialize the key buffer in the shared memory
	InitKeyBuffer(key_buffer);
	clrscr();

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit hw4_3b, ESC: quit both\n");

	while(1){
		gotoxy(1, 2);
		printf("Input a key: ");
		int key = getch();

		/* TO DO: implement the following action
			if key is ESC (ASCII 27), insert 'q' into the key buffer and break the loop
			otherwise, insert the key into the key buffer.

		*/
		if(key ==27){
			InsertKey(key_buffer, 113);
			break;
		}
		else{
			InsertKey(key_buffer, key);
		}

		DisplayKeyBuffer(1, 2, key_buffer);
		//key_buffer->out = (key_buffer->out+1)%key_buffer->size;
	}

	// TO DO: unmap and unlink the shared memory block
	munmap(key_buffer, buffer_size);
	shm_unlink(SHM_FILE);
	clrscr();
	printf("Bye!\n");

	return 0;
}
