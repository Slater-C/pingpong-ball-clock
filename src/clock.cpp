#include "clock.h"

void writeFormattedTime(displayBuffer* buffer, uint16_t time){

    uint8_t dig_pos = 0;
    position pos[4];
    pos[0].x = 15; pos[0].y = 1;
    pos[1].x = 11; pos[1].y = 1;
    pos[2].x = 5; pos[2].y = 1;
    pos[3].x = 1; pos[3].y = 1;

    while (dig_pos < 4) {
    
        int digit = time % 10;
        writeCharacter(buffer, digit, pos[dig_pos].x, pos[dig_pos].y);
        time /= 10;
        dig_pos++;
        
    }

    writeCharacter(buffer, 10, 8, 1);
}