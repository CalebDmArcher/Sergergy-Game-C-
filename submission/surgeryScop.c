// Make a simple GBA state machine
// Name: YOUR NAME HERE

#include <stdbool.h>

#include "myLib.h"
#include "game.h"
// #include "gba.h"

#include "images/background.h"
#include "images/start.h"
#include "images/success.h"
#include "images/failed.h"
#include "images/interrupt.h"


extern volatile unsigned short *videoBuffer;

// State enum definition
enum GBAState {
    STATE_START,
    GAME,
    SUCCESS,
    INTERRUPT,
    FAILURE,
};

int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    enum GBAState state = STATE_START;

    // Use this somehow in the states below. When you press and
    // hold A (the z key in the emulator we recommend), it
    // should NOT cycle through all of the states!
    bool a_down = false;
    // bool start_down = false;

    while(1) {
        // waitForVblank();

        // Get the current state of the buttons for this iteration
        u32 buttons = BUTTONS;

        switch(state) {
        // all cases below:

        case STATE_START:
            drawImage3(0, 0, 240, 160, start);
            char drIs[] = "Dr. Stephen is ready";
            char ready[] = "for a surgery.";
            char pressAToStart[] = "Please press 'A' to start.";
            drawString(15, 60, drIs, CYAN);
            drawString(25, 80, ready, CYAN);
            drawString(125, 40, pressAToStart, BLUE);
            state = GAME;
            break;

        case GAME:
            // the state for game playing
            if (KEY_DOWN(BUTTON_A, buttons)) {
                if (!a_down) {
                    // drawImage3(0, 0, 240, 160, failed);
                    int indicate = startGame();
                    if (indicate == 1) {
                        // fail
                        drawImage3(0, 0, 240, 160, failed);
                        char failStr[] = "Surgery failed.";
                        char dead[] = "Patient is dead.";
                        char presAc[] = "Press 'A' to use Time Gem.";
                        drawString(50, 20, failStr, BLACK);
                        drawString(65, 20, dead, BLACK);
                        drawString(125, 40, presAc, GREEN);
                        state = FAILURE;
                    } else if (indicate == 2) {
                        //
                        drawImage3(0, 0, 240, 160, interrupt);
                        char interStrReally[] = "Really?";
                        char interStr[] = "You just interrupted a surgery.";
                        drawString(120, 60, interStrReally, WHITE);
                        drawString(135, 30, interStr, WHITE);
                        state = INTERRUPT;
                    } else if (indicate == 3) {
                        // success
                        drawImage3(0, 0, 240, 160, success);
                        char continueStr[] = "Congrates! Surgery success.";
                        char presAc[] = "Press 'A' to use Time Gem";
                        char again[] = "to try the surgery again.";
                        drawString(10, 35, continueStr, YELLOW);
                        drawString(125, 40, presAc, WHITE);
                        drawString(140, 43, again, WHITE);
                        state = SUCCESS;
                    }
                }
                a_down = true;
            } else {
                    a_down = false;
            }
            break;

        case FAILURE:
            // waitForVblank();
            // drawImage3(0, 0, 240, 160, failed);
            // char failStr[] = "Surgery failed. Patient is dead.";
            // drawString(2, 2, failStr, BLACK);

            if (KEY_DOWN(BUTTON_A, buttons)) {
                if (!a_down) {
                    state = STATE_START;
                }
                a_down = true;
            } else {
                    a_down = false;
            }

            // static int count = 0;
            // if (KEY_DOWN(BUTTON_A, buttons)) {
            //     if (!a_down && count == 1) {
            //         state = STATE_START;
            //         count = 0;
            //     } else if (!a_down && count == 0) {
            //         drawImage3(0, 0, 240, 160, failed);
            //         char continueStr[] = "Surgery failed. Patient is dead.";
            //         drawString(15, 60, continueStr, CYAN);
            //         state = SUCCESS;
            //         count++;
            //     }
            //     a_down = true;
            // } else {
            //         a_down = false;
            // }

            break;

        case SUCCESS:
            // drawImage3(0, 0, 240, 160, success);
            // char continueStr[] = "Congrates! Surgery success.";
            // drawString(2, 2, continueStr, CYAN);

            if (KEY_DOWN(BUTTON_A, buttons)) {
                if (!a_down) {
                    state = STATE_START;
                }
                a_down = true;
            } else {
                    a_down = false;
            }

            // static int count = 0;
            // if (KEY_DOWN(BUTTON_A, buttons)) {
            //     if (!a_down && count == 1) {
            //         state = STATE_START;
            //         count = 0;
            //     } else if (!a_down && count == 0) {
            //         drawImage3(0, 0, 240, 160, success);
            //         char continueStr[] = "Congrates! Surgery success.";
            //         drawString(15, 60, continueStr, CYAN);
            //         state = SUCCESS;
            //         count++;
            //     }
            //     a_down = true;
            // } else {
            //         a_down = false;
            // }

            break;

        case INTERRUPT:
            // drawImage3(0, 0, 240, 160, interrupt);
            // char interStr[] = "Really? You interrupt a surgery.";
            // drawString(15, 60, interStr, CYAN);
            if (KEY_DOWN(BUTTON_A, buttons)) {
                if (!a_down) {
                    drawImage3(0, 0, 240, 160, failed);
                    char failStr[] = "Surgery failed.";
                    char dead[] = "Patient is dead.";
                    char presAc[] = "Press 'A' to use Time Gem.";
                    drawString(50, 20, failStr, BLACK);
                    drawString(65, 20, dead, BLACK);
                    drawString(125, 40, presAc, GREEN);
                    state = FAILURE;
                }
                a_down = true;
            } else {
                    a_down = false;
            }
            break;

        } // end of switch(state)
    }

    return 0;
}


void waitForVblank(void) {
    while(*SCANLINECOUNTER > 160);
    while(*SCANLINECOUNTER < 160);
}
