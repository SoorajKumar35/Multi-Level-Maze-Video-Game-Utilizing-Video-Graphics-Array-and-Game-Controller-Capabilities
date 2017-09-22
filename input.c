/*									tab:8
 *
 * input.c - source file for input control to maze game
 *
 * "Copyright (c) 2004-2009 by Steven S. Lumetta."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Steve Lumetta
 * Version:	    5
 * Creation Date:   Thu Sep  9 22:25:48 2004
 * Filename:	    input.c
 * History:
 *	SL	1	Thu Sep  9 22:25:48 2004
 *		First written.
 *	SL	2	Sat Sep 12 14:34:19 2009
 *		Integrated original release back into main code base.
 *	SL	3	Sun Sep 13 03:51:23 2009
 *		Replaced parallel port with Tux controller code for demo.
 *	SL	4	Sun Sep 13 12:49:02 2009
 *		Changed init_input order slightly to avoid leaving keyboard
 *              in odd state on failure.
 *	SL	5	Sun Sep 13 16:30:32 2009
 *		Added a reasonably robust direct Tux control for demo mode.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

#include "assert.h"
#include "input.h"
#include "maze.h"
#include "module/tuxctl-ioctl.h"


/* set to 1 and compile this file by itself to test functionality */
#define TEST_INPUT_DRIVER 1

/* set to 1 to use tux controller; otherwise, uses keyboard input */
#define USE_TUX_CONTROLLER 1


/* stores original terminal settings */
static struct termios tio_orig;

int fd;

/* 
 * init_input
 *   DESCRIPTION: Initializes the input controller.  As both keyboard and
 *                Tux controller control modes use the keyboard for the quit
 *                command, this function puts stdin into character mode
 *                rather than the usual terminal mode.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: 0 on success, -1 on failure 
 *   SIDE EFFECTS: changes terminal settings on stdin; prints an error
 *                 message on failure
 */
int
init_input ()
{
    struct termios tio_new;

    /*
     * Set non-blocking mode so that stdin can be read without blocking
     * when no new keystrokes are available.
     */
    if (fcntl (fileno (stdin), F_SETFL, O_NONBLOCK) != 0) {
        perror ("fcntl to make stdin non-blocking");
	return -1;
    }

    /*
     * Save current terminal attributes for stdin.
     */
    if (tcgetattr (fileno (stdin), &tio_orig) != 0) {
	perror ("tcgetattr to read stdin terminal settings");
	return -1;
    }

    /*
     * Turn off canonical (line-buffered) mode and echoing of keystrokes
     * to the monitor.  Set minimal character and timing parameters so as
     * to prevent delays in delivery of keystrokes to the program.
     */
    tio_new = tio_orig;
    tio_new.c_lflag &= ~(ICANON | ECHO);
    tio_new.c_cc[VMIN] = 1;
    tio_new.c_cc[VTIME] = 0;
    if (tcsetattr (fileno (stdin), TCSANOW, &tio_new) != 0) {
	perror ("tcsetattr to set stdin terminal settings");
	return -1;
    }

    /* Return success. */
    return 0;
}


/* 
 * get_command
 *   DESCRIPTION: Reads a command from the input controller.  As some
 *                controllers provide only absolute input (e.g., go
 *                right), the current direction is needed as an input
 *                to this routine.
 *   INPUTS: cur_dir -- current direction of motion
 *   OUTPUTS: none
 *   RETURN VALUE: command issued by the input controller
 *   SIDE EFFECTS: drains any keyboard input
 */
cmd_t 
get_command (dir_t cur_dir)
{
    static dir_t prev_cur = DIR_STOP; /* previous direction sent  */
    static dir_t pushed = DIR_STOP;   /* last direction pushed    */
#if (USE_TUX_CONTROLLER == 0) /* use keyboard control with arrow keys */
    static int state = 0;             /* small FSM for arrow keys */
#endif
    cmd_t command;
    int ch;
   
    /*
     * If the direction of motion has changed, forget the last
     * direction pushed.  Otherwise, it remains active.
     */
    if (prev_cur != cur_dir) {
	pushed = DIR_STOP;
	prev_cur = cur_dir;
    }
    
    /* Read all characters from stdin. */
    while ((ch = getc (stdin)) != EOF) {

	/* Backquote is used to quit the game. */
	if (ch == '`')
	    return CMD_QUIT;
	
#if (USE_TUX_CONTROLLER == 0) /* use keyboard control with arrow keys */
	/*
	 * Arrow keys deliver the byte sequence 27, 91, and 'A' to 'D';
	 * we use a small finite state machine to identify them.
	 */
	if (ch == 27)
	    state = 1; 
	else if (ch == 91 && state == 1)
	    state = 2;
	else {
	    if (state == 2 && ch >= 'A' && ch <= 'D') {
		switch (ch) {
		    case 'A': pushed = DIR_UP; break;
		    case 'B': pushed = DIR_DOWN; break;
		    case 'C': pushed = DIR_RIGHT; break;
		    case 'D': pushed = DIR_LEFT; break;
		}
	    }
	    state = 0;
	}
#endif
    }
    //ioctl(fd, TUX_BUTTONS, store);

    /*
     * Once a direction is pushed, that command remains active
     * until a turn is taken.
     */
    if (pushed == DIR_STOP)
	command = TURN_NONE;
    else
	command = (pushed - cur_dir + NUM_TURNS) % NUM_TURNS;

    return command;
}

/* 
 * shutdown_input
 *   DESCRIPTION: Cleans up state associated with input control.  Restores
 *                original terminal settings.
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none 
 *   SIDE EFFECTS: restores original terminal settings
 */
void
shutdown_input ()
{
    (void)tcsetattr (fileno (stdin), TCSANOW, &tio_orig);
}



/* 
 * display_time_on_tux
 *   DESCRIPTION: Show number of elapsed seconds as minutes:seconds
 *                on the Tux controller's 7-segment displays.
 *   INPUTS: num_seconds -- total seconds elapsed so far
 *   OUTPUTS: none
 *   RETURN VALUE: none 
 *   SIDE EFFECTS: changes state of controller's display
 */
void
display_time_on_tux (int num_seconds)
{
    /*
#if (USE_TUX_CONTROLLER != 0)
#error "Tux controller code is not operational yet."
#endif*/
    int minutes = num_seconds / 60;
    float need_frac = ((float)num_seconds/60) - minutes;
    int seconds = need_frac * 60;
    unsigned short lower_bytes = 0;
    unsigned long enable_dot = 0x04ff0000;
    unsigned long arg = 0x0fff6312;

    printf("min %d need frac %f seconds %d \n", minutes, need_frac, seconds);

   /* if(minutes > 99)
    {
        return;
    }         */                                                                                                                         
    unsigned long to_send = 0;
    int sec_ones = seconds % 10;
    int sec_tens = (seconds/10);
    int min_ones = minutes % 10;
    int min_tens = minutes/10;
    sec_tens = sec_tens % 10;  
    min_tens = min_tens % 10;

    printf("secones %d sectens %d minones %d mintens %d\n", sec_ones, sec_tens, min_ones, min_tens);

    to_send |= sec_ones;
    to_send <<= 4;
    to_send |= sec_tens;
    to_send <<= 4;
    to_send |= min_ones;
    to_send <<= 4;
    to_send |= min_tens;
    to_send <<= 4;
    printf("test %d", to_send & 0x0ffff);
    to_send = to_send | enable_dot;
    ioctl(fd, TUX_SET_LED, to_send);
    sleep(1);

}

/*
void input_tux_open()
{
    
}

*/
#if (TEST_INPUT_DRIVER == 1)
int
main ()
{   
    int fd;
    unsigned long arg = 0x0fff6312;
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    int ldisc_num = N_MOUSE;
    ioctl(fd, TIOCSETD, &ldisc_num);
    ioctl(fd, TUX_INIT);
    sleep(1);
    ioctl(fd, TUX_SET_LED, arg);
    sleep(1);
    arg = 0x0f006313;
    ioctl(fd, TUX_SET_LED, arg);
    sleep(1);

    arg = 0x0f006314;
    ioctl(fd, TUX_SET_LED, arg);
    sleep(1);

    arg = 0x0f006315;
    ioctl(fd, TUX_SET_LED,arg);
    sleep(1);

    while(1)
    {
        unsigned long but_ret = 0;
        ioctl(fd, TUX_BUTTONS, &but_ret);
        unsigned int store = 0x0f;
        unsigned char get_press_buttons = store & but_ret;
        printf("get_press_buttons %d\n", get_press_buttons);
        if(get_press_buttons == 0xe)
        {
            printf("got to up\n");
        }
        else if(get_press_buttons == 0xb)
        {
            printf("got to down\n");
        }
        else if(get_press_buttons == 0x7)
        {
            printf("got to right\n");
        }
        else if(get_press_buttons == 0xd)
        {
            printf("got to left\n");
        }

    }

    return 0;
}    

#endif













