/*									tab:8
 *
 * text.c - font data and text to graphics conversion utility
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
 * Version:	    2
 * Creation Date:   Thu Sep  9 22:06:29 2004
 * Filename:	    text.c
 * History:
 *	SL	1	Thu Sep  9 22:06:29 2004
 *		First written.
 *	SL	2	Sat Sep 12 13:45:33 2009
 *		Integrated original release back into main code base.
 */

#include <string.h>
#include <stdlib.h>
#include "text.h"
/*
unsigned char * get_textgraphic_buffer(char * text)
{
    
    unsigned char * ret_buff = (unsigned char *)malloc(sizeof((unsigned char *) * 25));
    int m;
    for(m = 0; m < (int)strlen(text); m++)
    {
        ret_buff[m] = (unsigned char)malloc(16);
    }
    int init_row, init_col;
    for(init_row = 0; init_row < 25; init_row++)
    {
        for(init_col = 0; init_col < 16; init_col++)
        {
            ret_buff[init_row][init_col] = 0;
        }
    }

    int i,j,k;
    for(i = 0, k=0; i < (int)strlen(text) && k < 25; i++, k++)
    {
        for(j = 0; j < 16; j++)
        {
            ret_buff[k][j] = font_data[(int)text[i]][j];
        }
    }
    return ret_buff;
}

*/
/*
unsigned char * get_textgraphic_buffer(char * text, unsigned char * text_graphic_buffer)
{
    int string_length = strlen(text);
    if(string_length > 25)
        return NULL; 
    //printf("%d\n", string_length);

    unsigned char req_font_data[string_length][16];

    int p,q;
    for(p = 0; p < string_length; p++)
    {
        for(q = 0; q < 16; q++)
        {
            req_font_data[p][q] = font_data[(int)text[p]][q];
        }
    }

    int i=0,j;
    int count = 0;
    for(j = 0; j < 16; j++)
    {
        for(i=0; i < string_length; i++,count++)
        {
            unsigned char the_pix = req_font_data[i][j];
            int k;
            unsigned char mask = 0x80;
            for(k=0; k < 8; k++)
            {

                if((the_pix & mask) != 0)
                {
                    text_graphic_buffer[k + count] = 0xff;
                }
                else
                {
                    text_graphic_buffer[k + count] = 0x15;
                }
                mask >>= 2;

            }

        }
    }

    return text_graphic_buffer;
}
*/

/*
    DESCRIPTION: Takes input string and creates buffer with graphical represenation of string
    Inputs:
        text - The input string
        text_graphic_buffer - the buffer to write the graphical string chars to
    Outputs:
        text_graphic_buffer - the address of the buffer that was written to
*/
unsigned char * get_textgraphic_buffer(char * text, unsigned char * text_graphic_buffer)
{
  /* int string_length = strlen(text);
   unsigned char req_font_data[25][16];

    int free_space = 25 - string_length;
    int offset = (free_space/2) * 8;

    int font_count, horiz_trav;
    for(font_count = 0; font_count < (free_space/2); font_count++)
    {
        for(horiz_trav = 0; horiz_trav < 16; horiz_trav++)
        {
            req_font_data[font_count][horiz_trav] = 0x00;
        }
    }
    int text_trav;
    for(font_count = offset, text_trav = 0; font_count < (offset + string_length) && text_trav < 25; font_count++, text_trav++)
    {
        for(horiz_trav = 0; horiz_trav < 16; horiz_trav++)
        {
            req_font_data[font_count][horiz_trav] = font_data[(int)text[text_trav]][horiz_trav];
        }
    }
    for (font_count = offset + string_length; font_count < 25; font_count++)
    {
        for(horiz_trav = 0; horiz_trav < 16; horiz_trav++)
        {
            req_font_data[font_count][horiz_trav] = 0x00;
        }
    }*/

    int p_off = 0;
    unsigned char * start_of_buffer = text_graphic_buffer;

    //int top_x = 0, top_y = 0;
    p_off = 0;
    int top_count = 0;
    for(top_count = 0; top_count < 320; top_count++)
    {
        text_graphic_buffer[p_off * 1440] = 0x15;
        if(--p_off < 0)
        {
            p_off = 3;
            text_graphic_buffer++;
        }
    }

    text_graphic_buffer = start_of_buffer;

    int bottom_x = 0, bottom_y = 17;
    p_off = 0;
    int bottom_count = 0;
    text_graphic_buffer = text_graphic_buffer + (bottom_x >> 2) + (bottom_y * 320);
    for(bottom_count = 0; bottom_count < 320; bottom_count++)
    {
        text_graphic_buffer[p_off * 1440] = 0x15;
        if(--p_off < 0)
        {
            p_off = 3;
            text_graphic_buffer++;
        }
    }


/*

    int j = 0, i = 0;
    int buff_x = 0;
    int buff_y = 1;
    int p_off;
    for(j = 0; j < 16; j++)
    {
        for(i = 0; i < 25; i++)
        {

            unsigned char the_pix = req_font_data[i][j];
            int k;
            unsigned char mask = 0x80;
            p_off = 3 - (3 & buff_x);
            for(k=0; k < 8; k++)
            {
                if((the_pix & mask) != 0)
                {
                    unsigned char * addr = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
                    addr[p_off * 1440] = 0xff;
                }
                else
                {
                    unsigned char * addr = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
                    addr[p_off * 1440] = 0x15;
                }
                mask >>= 2;
                buff_x++;
                if (--p_off < 0) 
                {
                    p_off = 3;
                }
            }
        }

        buff_y++;

    }
  
    buff_x = 0;
    buff_y = 0;
    p_off = 3 - (buff_x & 3);
    unsigned char * addr_2 = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
    int trav;
    for(trav = 0; trav < 320; trav++)
    {
        addr_2[p_off * 1440] = 0x00;
        if(--p_off < 0)
            {
                p_off = 3;
            }
            addr_2 = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
            buff_x++;
    }
    buff_x = 0;
    buff_y = 17;
    unsigned char * addr_3 = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
    int trav_2;
        p_off = 3 - (buff_x & 3);

    for(trav_2 = 0; trav_2 < 320; trav_2++)
    {
        addr_3[p_off * 1440] = 0x00;
        if(--p_off < 0)
            {
                p_off = 3;
            }
            addr_3 = text_graphic_buffer + (buff_x >> 2) + (buff_y * 320);
            buff_x++;
    }
 
*/
    return start_of_buffer;

}

/* 
 * These font data were read out of video memory during text mode and
 * saved here.  They could be read in the same manner at the start of a
 * game, but keeping a copy allows us to run the game to fix text mode
 * if it is broken (font data missing, usually).
 *
 * Each character is 8x16 pixels and occupies two lines in the table below.
 * Each byte represents a single bitmapped line of a single character.
 */
unsigned char font_data[256][16] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7E, 0x81, 0xA5, 0x81, 0x81, 0xBD,
     0x99, 0x81, 0x81, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7E, 0xFF, 0xDB, 0xFF, 0xFF, 0xC3,
     0xE7, 0xFF, 0xFF, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x6C, 0xFE, 0xFE, 0xFE,
     0xFE, 0x7C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7C, 0xFE,
     0x7C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x18, 0x3C, 0x3C, 0xE7, 0xE7,
     0xE7, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x18, 0x3C, 0x7E, 0xFF, 0xFF,
     0x7E, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3C,
     0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0xC3,
     0xC3, 0xE7, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x42,
     0x42, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC3, 0x99, 0xBD,
     0xBD, 0x99, 0xC3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x1E, 0x0E, 0x1A, 0x32, 0x78, 0xCC,
     0xCC, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C,
     0x18, 0x7E, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3F, 0x33, 0x3F, 0x30, 0x30, 0x30,
     0x30, 0x70, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7F, 0x63, 0x7F, 0x63, 0x63, 0x63,
     0x63, 0x67, 0xE7, 0xE6, 0xC0, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x18, 0x18, 0xDB, 0x3C, 0xE7,
     0x3C, 0xDB, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFE, 0xF8,
     0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x06, 0x0E, 0x1E, 0x3E, 0xFE, 0x3E,
     0x1E, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18,
     0x7E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
     0x66, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7F, 0xDB, 0xDB, 0xDB, 0x7B, 0x1B,
     0x1B, 0x1B, 0x1B, 0x1B, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x7C, 0xC6, 0x60, 0x38, 0x6C, 0xC6, 0xC6,
     0x6C, 0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18,
     0x7E, 0x3C, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x3C, 0x7E, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
     0x18, 0x7E, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0C, 0xFE,
     0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x60, 0xFE,
     0x60, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0,
     0xC0, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x6C, 0xFE,
     0x6C, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x7C,
     0x7C, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0x7C, 0x7C,
     0x38, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x3C, 0x3C, 0x3C, 0x18, 0x18,
     0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x66, 0x66, 0x66, 0x24, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x6C, 0x6C, 0xFE, 0x6C, 0x6C,
     0x6C, 0xFE, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x7C, 0xC6, 0xC2, 0xC0, 0x7C, 0x06,
     0x06, 0x86, 0xC6, 0x7C, 0x18, 0x18, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0xC2, 0xC6, 0x0C, 0x18,
     0x30, 0x60, 0xC6, 0x86, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x6C, 0x6C, 0x38, 0x76, 0xDC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x30, 0x30, 0x30, 0x60, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x18, 0x0C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x0C,
     0x0C, 0x0C, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x3C, 0xFF,
     0x3C, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E,
     0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x18, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0C, 0x18,
     0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x38, 0x78, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0x06, 0x0C, 0x18, 0x30,
     0x60, 0xC0, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0x06, 0x06, 0x3C, 0x06,
     0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0C, 0x1C, 0x3C, 0x6C, 0xCC, 0xFE,
     0x0C, 0x0C, 0x0C, 0x1E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0xC0, 0xC0, 0xC0, 0xFC, 0x06,
     0x06, 0x06, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x60, 0xC0, 0xC0, 0xFC, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0xC6, 0x06, 0x06, 0x0C, 0x18,
     0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7C, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0x7E, 0x06,
     0x06, 0x06, 0x0C, 0x78, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00,
     0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00,
     0x00, 0x18, 0x18, 0x30, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x06, 0x0C, 0x18, 0x30, 0x60,
     0x30, 0x18, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00,
     0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x60, 0x30, 0x18, 0x0C, 0x06,
     0x0C, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x0C, 0x18, 0x18,
     0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xDE, 0xDE,
     0xDE, 0xDC, 0xC0, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6, 0xFE,
     0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x66,
     0x66, 0x66, 0x66, 0xFC, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0,
     0xC0, 0xC2, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x66,
     0x66, 0x66, 0x6C, 0xF8, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68,
     0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0x66, 0x62, 0x68, 0x78, 0x68,
     0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xDE,
     0xC6, 0xC6, 0x66, 0x3A, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xFE, 0xC6,
     0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x18, 0x18, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
     0xCC, 0xCC, 0xCC, 0x78, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xE6, 0x66, 0x66, 0x6C, 0x78, 0x78,
     0x6C, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xF0, 0x60, 0x60, 0x60, 0x60, 0x60,
     0x60, 0x62, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6,
     0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE, 0xCE,
     0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x60,
     0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xD6, 0xDE, 0x7C, 0x0C, 0x0E, 0x00, 0x00},
    {0x00, 0x00, 0xFC, 0x66, 0x66, 0x66, 0x7C, 0x6C,
     0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7C, 0xC6, 0xC6, 0x60, 0x38, 0x0C,
     0x06, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x7E, 0x7E, 0x5A, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0x6C, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xD6,
     0xD6, 0xFE, 0xEE, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0xC6, 0x6C, 0x7C, 0x38, 0x38,
     0x7C, 0x6C, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0xC6, 0x86, 0x0C, 0x18, 0x30,
     0x60, 0xC2, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x30, 0x30, 0x30, 0x30, 0x30,
     0x30, 0x30, 0x30, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0x70, 0x38,
     0x1C, 0x0E, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
     0x0C, 0x0C, 0x0C, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00},
    {0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xE0, 0x60, 0x60, 0x78, 0x6C, 0x66,
     0x66, 0x66, 0x66, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC0,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1C, 0x0C, 0x0C, 0x3C, 0x6C, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xFE,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60,
     0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xCC, 0x78, 0x00},
    {0x00, 0x00, 0xE0, 0x60, 0x60, 0x6C, 0x76, 0x66,
     0x66, 0x66, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x06, 0x06, 0x00, 0x0E, 0x06, 0x06,
     0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3C, 0x00},
    {0x00, 0x00, 0xE0, 0x60, 0x60, 0x66, 0x6C, 0x78,
     0x78, 0x6C, 0x66, 0xE6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xEC, 0xFE, 0xD6,
     0xD6, 0xD6, 0xD6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66,
     0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x66, 0x66,
     0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0x0C, 0x1E, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xDC, 0x76, 0x66,
     0x60, 0x60, 0x60, 0xF0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0xC6, 0x60,
     0x38, 0x0C, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x10, 0x30, 0x30, 0xFC, 0x30, 0x30,
     0x30, 0x30, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66,
     0x66, 0x66, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xD6,
     0xD6, 0xD6, 0xFE, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x6C, 0x38,
     0x38, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0xF8, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xCC, 0x18,
     0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0E, 0x18, 0x18, 0x18, 0x70, 0x18,
     0x18, 0x18, 0x18, 0x0E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18,
     0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0E, 0x18,
     0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x76, 0xDC, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x6C, 0xC6,
     0xC6, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3C, 0x66, 0xC2, 0xC0, 0xC0, 0xC0,
     0xC2, 0x66, 0x3C, 0x0C, 0x06, 0x7C, 0x00, 0x00},
    {0x00, 0x00, 0xCC, 0x00, 0x00, 0xCC, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x0C, 0x18, 0x30, 0x00, 0x7C, 0xC6, 0xFE,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x10, 0x38, 0x6C, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xCC, 0x00, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x6C, 0x38, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x60, 0x60,
     0x66, 0x3C, 0x0C, 0x06, 0x3C, 0x00, 0x00, 0x00},
    {0x00, 0x10, 0x38, 0x6C, 0x00, 0x7C, 0xC6, 0xFE,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0x00, 0x00, 0x7C, 0xC6, 0xFE,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x00, 0x7C, 0xC6, 0xFE,
     0xC0, 0xC0, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x66, 0x00, 0x00, 0x38, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x3C, 0x66, 0x00, 0x38, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x00, 0x38, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0xC6, 0x00, 0x10, 0x38, 0x6C, 0xC6, 0xC6,
     0xFE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x38, 0x6C, 0x38, 0x00, 0x38, 0x6C, 0xC6, 0xC6,
     0xFE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x30, 0x60, 0x00, 0xFE, 0x66, 0x60, 0x7C,
     0x60, 0x60, 0x66, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xCC, 0x76, 0x36,
     0x7E, 0xD8, 0xD8, 0x6E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x3E, 0x6C, 0xCC, 0xCC, 0xFE, 0xCC,
     0xCC, 0xCC, 0xCC, 0xCE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x10, 0x38, 0x6C, 0x00, 0x7C, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0x00, 0x00, 0x7C, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x00, 0x7C, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x30, 0x78, 0xCC, 0x00, 0xCC, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x60, 0x30, 0x18, 0x00, 0xCC, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xC6, 0x00, 0x00, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7E, 0x06, 0x0C, 0x78, 0x00},
    {0x00, 0xC6, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0xC6, 0x00, 0xC6, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x18, 0x3C, 0x66, 0x60, 0x60, 0x60,
     0x66, 0x3C, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x6C, 0x64, 0x60, 0xF0, 0x60, 0x60,
     0x60, 0x60, 0xE6, 0xFC, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x66, 0x66, 0x3C, 0x18, 0x7E, 0x18,
     0x7E, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0xF8, 0xCC, 0xCC, 0xF8, 0xC4, 0xCC, 0xDE,
     0xCC, 0xCC, 0xCC, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x0E, 0x1B, 0x18, 0x18, 0x18, 0x7E, 0x18,
     0x18, 0x18, 0x18, 0x18, 0xD8, 0x70, 0x00, 0x00},
    {0x00, 0x18, 0x30, 0x60, 0x00, 0x78, 0x0C, 0x7C,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x0C, 0x18, 0x30, 0x00, 0x38, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x30, 0x60, 0x00, 0x7C, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x30, 0x60, 0x00, 0xCC, 0xCC, 0xCC,
     0xCC, 0xCC, 0xCC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x76, 0xDC, 0x00, 0xDC, 0x66, 0x66,
     0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00},
    {0x76, 0xDC, 0x00, 0xC6, 0xE6, 0xF6, 0xFE, 0xDE,
     0xCE, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x3C, 0x6C, 0x6C, 0x3E, 0x00, 0x7E, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x7C, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x30, 0x30, 0x00, 0x30, 0x30, 0x60,
     0xC0, 0xC6, 0xC6, 0x7C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xC0,
     0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x06,
     0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0xC0, 0xC0, 0xC2, 0xC6, 0xCC, 0x18, 0x30,
     0x60, 0xDC, 0x86, 0x0C, 0x18, 0x3E, 0x00, 0x00},
    {0x00, 0xC0, 0xC0, 0xC2, 0xC6, 0xCC, 0x18, 0x30,
     0x66, 0xCE, 0x9E, 0x3E, 0x06, 0x06, 0x00, 0x00},
    {0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18,
     0x3C, 0x3C, 0x3C, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x6C, 0xD8,
     0x6C, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xD8, 0x6C, 0x36,
     0x6C, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44,
     0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44},
    {0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
     0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA},
    {0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77,
     0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77, 0xDD, 0x77},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0x18, 0xF8,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xF6,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x18, 0xF8,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0xF6, 0x06, 0xF6,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x06, 0xF6,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0xF6, 0x06, 0xFE,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xFE,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0xF8, 0x18, 0xF8,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xFF,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x18, 0x1F,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x3F,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x30, 0x37,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0xF7, 0x00, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xF7,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x37,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0xF7, 0x00, 0xF7,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x00, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xFF,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x3F,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x18, 0x1F,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x18, 0x1F,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xFF,
     0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0xFF, 0x18, 0xFF,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xF8,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
     0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
    {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
     0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0},
    {0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
     0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xDC, 0xD8,
     0xD8, 0xD8, 0xDC, 0x76, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0xD8, 0xCC,
     0xC6, 0xC6, 0xC6, 0xCC, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xFE, 0xC6, 0xC6, 0xC0, 0xC0, 0xC0,
     0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0xFE, 0x6C, 0x6C, 0x6C,
     0x6C, 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0xFE, 0xC6, 0x60, 0x30, 0x18,
     0x30, 0x60, 0xC6, 0xFE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xD8, 0xD8,
     0xD8, 0xD8, 0xD8, 0x70, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66,
     0x66, 0x7C, 0x60, 0x60, 0xC0, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x76, 0xDC, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x7E, 0x18, 0x3C, 0x66, 0x66,
     0x66, 0x3C, 0x18, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xFE,
     0xC6, 0xC6, 0x6C, 0x38, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C,
     0x6C, 0x6C, 0x6C, 0xEE, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1E, 0x30, 0x18, 0x0C, 0x3E, 0x66,
     0x66, 0x66, 0x66, 0x3C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7E, 0xDB, 0xDB,
     0xDB, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x03, 0x06, 0x7E, 0xDB, 0xDB,
     0xF3, 0x7E, 0x60, 0xC0, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x1C, 0x30, 0x60, 0x60, 0x7C, 0x60,
     0x60, 0x60, 0x30, 0x1C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x7C, 0xC6, 0xC6, 0xC6, 0xC6,
     0xC6, 0xC6, 0xC6, 0xC6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xFE,
     0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x7E, 0x18,
     0x18, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x30, 0x18, 0x0C, 0x06, 0x0C,
     0x18, 0x30, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x0C, 0x18, 0x30, 0x60, 0x30,
     0x18, 0x0C, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x0E, 0x1B, 0x1B, 0x18, 0x18, 0x18,
     0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
     0xD8, 0xD8, 0xD8, 0x70, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x7E,
     0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0xDC, 0x00,
     0x76, 0xDC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x38, 0x6C, 0x6C, 0x38, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18,
     0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x0F, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0xEC,
     0x6C, 0x6C, 0x3C, 0x1C, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0xD8, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x70, 0xD8, 0x30, 0x60, 0xC8, 0xF8, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x7C, 0x7C, 0x7C, 0x7C,
     0x7C, 0x7C, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

