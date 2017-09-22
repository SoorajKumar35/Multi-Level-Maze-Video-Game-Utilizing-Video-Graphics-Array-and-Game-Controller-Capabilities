#include <stdio.h>
#include "blocks.h"
#include "maze.h"
#include "modex.h"
#include "text.h"


void change_wall_color(int level)
{
    unsigned char buffer[3];
    switch(level)
    {
        case 1:
            break;
        case 2:
            buffer[0] = 0x18;
            buffer[1] = 0x18; 
            buffer[2] = 0x18;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x2a;
            buffer[1] = 0x15;
            buffer[2] = 0x00;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 3:
            buffer[0] = 0x2a;
            buffer[1] = 0x15;
            buffer[2] = 0x00;
            set_palette_color(WALL_FILL_COLOR, buffer);
             buffer[0] = 0x3f;
            buffer[1] = 0x15;
            buffer[2] = 0x3f;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 4:
            buffer[0] = 0x3f;
            buffer[1] = 0x15;
            buffer[2] = 0x3f;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x00;
            buffer[1] = 0x00;
            buffer[2] = 0x2a;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 5:
            buffer[0] = 0x00;
            buffer[1] = 0x00;
            buffer[2] = 0x2a;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x2a;
            buffer[1] = 0x00;
            buffer[2] = 0x00;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 6:
            buffer[0] = 0x2a;
            buffer[1] = 0x00;
            buffer[2] = 0x00;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x3F;
            buffer[1] = 0x15;
            buffer[2] = 0x15;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 7:
            buffer[0] = 0x3F;
            buffer[1] = 0x15;
            buffer[2] = 0x15;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x00;
            buffer[1] = 0x2a;
            buffer[2] = 0x2a;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 8:
            buffer[0] = 0x00;
            buffer[1] = 0x2a;
            buffer[2] = 0x2a;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x3F;
            buffer[1] = 0x3f;
            buffer[2] = 0x15;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 9:
            buffer[0] = 0x3F;
            buffer[1] = 0x3f;
            buffer[2] = 0x15;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x00;
            buffer[1] = 0x2a;
            buffer[2] = 0x00;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
        case 10:
            buffer[0] = 0x00;
            buffer[1] = 0x2a;
            buffer[2] = 0x00;
            set_palette_color(WALL_FILL_COLOR, buffer);
            buffer[0] = 0x18;
            buffer[1] = 0x18; 
            buffer[2] = 0x18;
            set_palette_color(WALL_OUTLINE_COLOR, buffer);
            break;
    }

}

void change_center_color(unsigned char * color_buff)
{
       
    
}







