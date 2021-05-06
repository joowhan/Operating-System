#include <stdio.h>

#include "Console.h"

int main(int argc, char *argv)
{
    clrscr();            // clear screen

    // retrieve the size of window
    int screen_width = getWindowWidth();
    int screen_height = getWindowHeight() - 3;

    printf("i: up, j: left, k: down, l: right, c: change color, q: quit\n");
    printf("screen size: %d x %d\n", screen_width, screen_height);

    int x = screen_width / 2;    // horizontal coordinate
    int y = screen_height / 2;    // vertical coordinate
    int key = 0;
    int repeat = 1;
    char c = '*';        // initial color

    gotoxy(x, y);        // move the cursor to (x, y)
    putchar('#');

    int oldx = 0, oldy = 0;
    while(repeat){
        // TO DO: save current coordinate in (oldx, oldy)
        oldx = x;
        oldy = y;
        gotoxy(1, 3);
        printf("x = %3d, y = %3d", x, y);

        //gotoxy(screen_width, 1);    // move cursor to upper right corner
        //key = getch();        // read a key not waiting for ENTER

        // these two lines are only to show how to use gotoxy() and getch()
        // remove them when you complete the homework
        gotoxy(1, 4);
        printf("key = %c (%3d)\n", key, key);
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
        key = getch();
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
        }
        if(x<1) x++;
        if(y<1) y++;
        else if(x>screen_width) x--;
        else if(y>screen_height) y--;
        
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


