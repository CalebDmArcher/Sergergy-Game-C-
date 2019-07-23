#include <stdbool.h>
#include <stdio.h>

#include "myLib.h"
#include "game.h"
// #include "logic.h"

#include "images/background.h"

enum directionState {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BEGIN,
};

int startGame(void) {


    // typedef struct {
    //     int timeLeft;
    //     char dispalyStr[];
    // } display;
    display display1;
    display1.timeLeft = 20;
    display1.length = 0;

    REG_DISPCNT = MODE3 | BG2_ENABLE;

    // int buttondown[NBUTTONS] = {0};
    // int button[NBUTTONS] = {0};

    u32 previousButtons = BUTTONS;
    u32 currentButtons = BUTTONS;

    enum directionState state = BEGIN;

    // background drawing
    drawRect3(0, 0, 240, 160, BLACK);
    drawImage3(15, 60, 120, 120, background);

    drawRect3(50, 80, 30, 5, LIGHTGRAY);
    drawRect3(50, 80, 5, 50, LIGHTGRAY);
    drawRect3(50, 105, 5, 30, LIGHTGRAY);
    drawRect3(80, 105, 70, 5, LIGHTGRAY);
    drawRect3(95, 80, 90, 5, LIGHTGRAY);

    drawRect3(48, 90, 3, 7, GRAY);
    setPixel(47, 91, GRAY);
    setPixel(46, 91, GRAY);
    setPixel(45, 91, GRAY);
    setPixel(45, 91, GRAY);

    // start point
    setPixel(90, 172, WHITE);

    int row = 90;
    int col = 172;
    int speed = 1;
    int speedControl = 5;

    int counter = 0;

    bool playing = true;

    int indicate = 0; // 1:fail
                      // 2:interrupt
                      // 3:success

    while(playing) { // game loop

        // if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
        //     indicate = 2; // interrupt
        //     playing = false;
        // }


        if (counter % 50 == 0) {
                display1.timeLeft -= 1;
            } // end vBlankCounter if

        setPixel(row, col, WHITE); // keep going

        if (counter % speedControl == 0) {
            display1.length += 1;
        }

        counter++;

        currentButtons = BUTTONS;

        // for (int i = 0; i < NBUTTONS; i++) {
        //     button[i] = KEY_DOWN_NOW(i) == 0 && buttondown[i];
        //     buttondown[i] = KEY_DOWN_NOW(i) != 0;
        // }

        switch(state) {
        // all cases below:

        case BEGIN:

            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                indicate = 2; // interrupt
                playing = false;
            }

            if (counter % speedControl == 0) {
                row = row - speed;
                col = col;
            } // end vBlankCounter if


            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {state = UP;}
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {state = DOWN;}
            if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {state = RIGHT;}
            if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {state = LEFT;}
            break;

        case UP:

            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                indicate = 2; // interrupt
                playing = false;
            }

            if (counter % speedControl == 0) {
                row = row - speed;
                col = col;
            } // end vBlankCounter if
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {state = UP;}
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {state = DOWN;}
            if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {state = RIGHT;}
            if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {state = LEFT;}
            break;

        case DOWN:

            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                indicate = 2; // interrupt
                playing = false;
            }

            if (counter % speedControl == 0) {
                row = row + speed;
                col = col;
            } // end vBlankCounter if
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {state = UP;}
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {state = DOWN;}
            if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {state = RIGHT;}
            if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {state = LEFT;}
            break;

        case LEFT:

            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                indicate = 2; // interrupt
                playing = false;
            }

            if (counter % speedControl == 0) {
                row = row;
                col = col - 1;
            } // end vBlankCounter if
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {state = UP;}
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {state = DOWN;}
            if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {state = RIGHT;}
            if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {state = LEFT;}
            break;

        case RIGHT:

            if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
                indicate = 2; // interrupt
                playing = false;
            }

            if (counter % speedControl == 0) {
                row = row;
                col = col + 1;
            } // end vBlankCounter if
            if (KEY_JUST_PRESSED(BUTTON_UP, currentButtons, previousButtons)) {state = UP;}
            if (KEY_JUST_PRESSED(BUTTON_DOWN, currentButtons, previousButtons)) {state = DOWN;}
            if(KEY_JUST_PRESSED(BUTTON_RIGHT, currentButtons, previousButtons)) {state = RIGHT;}
            if(KEY_JUST_PRESSED(BUTTON_LEFT, currentButtons, previousButtons)) {state = LEFT;}
            break;
        }

        previousButtons = currentButtons;
        waitForVblank();

        if (display1.timeLeft < 0) {
            indicate = 1;
            playing = false;
        }

        if ((row == 54 || row == 53) && (col == 90 || col == 91 || col == 92)) {
            indicate = 3; // success
            playing = false;
        } else if (row < 54 || row > 95 || col < 85 || col > 174) {
            indicate = 1; // fail
            playing = false;
        } else if (row >= 54 && row <=83) {
            if (col < 54 || col > 105) {
                indicate = 1; // fail
                playing = false;
            }
        } else if (row > 83 && row <= 95) {
            if (col < 53 || col > 174) {
                indicate = 1; // fail
                playing = false;
            }
        }

        // if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
        //     indicate = 2; // interrupt
        //     playing = false;
        // }

        char buffer1[51];
        char buffer2[51];
        int countDown = display1.timeLeft;
        int totalLength = display1.length;
        sprintf(buffer1, "Time Left: %d", countDown);
        if (countDown > 5) {
            drawString(2, 2, buffer1, CYAN);
        } else {
            drawString(2, 2, buffer1, RED);
        }

        sprintf(buffer2, "Length: %d", totalLength);
        drawString(15, 2, buffer2, CYAN);

        if (counter % 50 == 0) {
            drawRect3(2, 60, 50, 10, BLACK);
        }


        if (counter % speedControl == 0) {
            drawRect3(15, 45, 40, 10, BLACK);
        }

    } // end while(1)

    return indicate;

}



