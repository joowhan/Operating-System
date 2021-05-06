
#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv)
{
	// TO DO: open SHM_FILE for using shm_open()
	//  check if the file was successfully open
	int shm_fd;
	shm_fd = shm_open(SHM_FILE, O_RDWR, 0666);

	if(shm_fd ==-1){
		printf("fail to open\n");
		return 1;
	}

	int buffer_size = sizeof(KeyBuffer);
	KeyBuffer *key_buffer = NULL;
	// TO DO: map the shared memory file and receive the return address into     key_buffer
	// check if the file was successfully mapped
	key_buffer = mmap(0, buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(key_buffer == MAP_FAILED) return 1;

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();

	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;

	gotoxy(x, y);
	putchar('#');
	while(repeat){
		int oldx = x;
		int oldy = y;
		
		// TO DO: read a key from the key buffer in the shared memory
		// if the key is zero, repeat until a non-zero key is read
		//msync(key_buffer, key_buffer->size, MS_SYNC);
		key = key_buffer->buffer[key_buffer->out];
		if(!key) continue;
	        key_buffer->out = (key_buffer->out +1)%key_buffer->size;
	    

/*
		TO DO: implement the following actions
		if key is 'i', 'j', 'k', or 'l', move the coordinate accordingly
			'i': move up
			'j': move left
			'k': move down
			'l': move right

			Note! The coordinate should be in the valid range.
			(1 <= x <= screen_width, 1 <= y <= screen_height)

		if key is 'c', change color
			toggle c between ' ' and '*' 

		if key is 'q', break the loop
			
*/
		gotoxy(x,y);
		if(key == 'i'||key=='j'||key=='k'||key=='l'){
			switch (key) {
				case 'i':
					y--;
					break;
				case 'j':
					x--;
					break;
				case 'k':
					y++;
					break;
				case 'l':
					x++;
					break;
				default:
					break;
			}

			if(x<1) x++;
			if(y<1) y++;
			else if(x>screen_width) x--;
			else if(y>screen_height) y--;
		}

		if(key == 'c'){
			if(c=='*') c = ' ';
			else if(c==' ') c = '*';
		}
		if(key=='q') break;
		// TO DO: print c at (oldx, oldy)
		gotoxy(oldx, oldy);
		printf("%c", c);
		// TO DO: print '#' at (x, y)
		gotoxy(x, y);
		printf("#");
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}
