//#include <msp430.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include "peripherals.h"
//
//#define NUM_NOTES 28
//
//char note;	// note
//int time;	// duration note
//char win = 1;	// flag to determine win state
//int state;
//volatile int timer_cnt = 0;
//int leap_cnt = 0;
//char currKey = 0;
//char currButton = 0;
//int sec_count = 0;
//int currScore = 0;
//char displayScore;
//int miss = 0;	// keeps track of missed notes from user input
//
//void swDelay (char numLoops);
//void runTimerA2(void);
//void stoptimerA2(int reset);
//void checkInput(char note);		// Checks user input and updates score based on miss
//unsigned char note2HEX (char note);	// converts char input to HEX value to compare. Helper function
//
////create structs to hold notes and time
//struct song {
//    char note;
//    int time;
//} s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15, s16, s17, s18, s19, s20, s21, s22, s23, s24, s25, s26, s27, s28;
//
////create array to hold all structs
//struct song songArr[NUM_NOTES];
//
//
//int main_guitar(void){
//
//    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
//    _BIS_SR(GIE);
//
//
//    s1.note = 'A';
//    s1.time = 2000;
//
//    s2.note = 'Z';
//    s2.time = 3000;
//
//    s3.note = 'B';
//    s3.time = 4000;
//
//    s4.note = 'C';
//    s4.time = 5000;
//
//    s5.note = 'E';
//    s5.time = 6000;
//
//    s6.note = 'F';
//    s6.time = 8000;
//
//    s7.note = 'Y';
//    s7.time = 8500;
//
//    s8.note = 'X';
//    s8.time = 10000;
//
//    s9.note = 'G';
//    s9.time = 11000;
//
//    s10.note = 'A';
//    s10.time = 12000;
//
//    s11.note = 'B';
//    s11.time = 13000;
//
//    s12.note = 'C';
//    s12.time = 14000;
//
//    s13.note = 'C';
//    s13.time = 15000;
//
//    s14.note = 'K';
//    s14.time = 16000;
//
//    s15.note = 'P';
//    s15.time = 17000;
//
//    s16.note = 'Q';
//    s16.time = 18000;
//
//    s17.note = 'X';
//    s17.time = 19000;
//
//    s18.note = 'Y';
//    s18.time = 20000;
//
//    s19.note = 'F';
//    s19.time = 21000;
//
//    s20.note = 'G';
//    s20.time = 22000;
//
//    s21.note = 'E';
//    s21.time = 23000;
//
//    s22.note = 'F';
//    s22.time = 24000;
//
//    s23.note = 'B';
//    s23.time = 25000;
//
//    s24.note = 'P';
//    s24.time = 26000;
//
//    s25.note = 'Q';
//    s25.time = 27000;
//
//    s26.note = 'F';
//    s26.time = 28000;
//
//    s27.note = 'G';
//    s27.time = 29000;
//
//    s28.note = 'E';
//    s28.time = 30000;
//
//    songArr[0] = s1;
//    songArr[1] = s2;
//    songArr[2] = s3;
//    songArr[3] = s4;
//    songArr[4] = s5;
//    songArr[5] = s6;
//    songArr[6] = s7;
//    songArr[7] = s8;
//    songArr[8] = s9;
//    songArr[9] = s10;
//    songArr[10] = s11;
//    songArr[11] = s12;
//    songArr[12] = s13;
//    songArr[13] = s14;
//    songArr[14] = s15;
//    songArr[15] = s16;
//    songArr[16] = s17;
//    songArr[17] = s18;
//    songArr[18] = s19;
//    songArr[19] = s20;
//    songArr[20] = s21;
//    songArr[21] = s22;
//    songArr[22] = s23;
//    songArr[23] = s24;
//    songArr[24] = s25;
//    songArr[25] = s26;
//    songArr[26] = s27;
//    songArr[27] = s28;
//
//    initLeds();
//    configDisplay();
//    configKeypad();
//    configButtons();
//    Graphics_clearDisplay(&g_sContext);
//
//
//   int i = 0;
//   state = 1;
//   currButton = 0;
//   win = 0;
//
//
//   Graphics_clearDisplay(&g_sContext);
//
//   while (1){
//       currKey = getKey();
//       currButton = buttonState();
//
//       switch (state){
//
//           case 1:
//
//
//
//               //display welcome message and ask to press '*' to start
//               Graphics_drawStringCentered(&g_sContext, "MSP430 Hero", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
//               Graphics_drawStringCentered(&g_sContext, "Press '*'!", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
//               Graphics_flushBuffer(&g_sContext);
//
//               if (currKey == '*'){
//
//                   runTimerA2();
//                   Graphics_clearDisplay(&g_sContext); // Clear the display
//                   Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//
//                   while (timer_cnt < 1000){
//                       setLeds (0x2);
//                   }
//                   setLeds(0);
//                   timer_cnt = 0;
//                   stoptimerA2(1);
//
//                   runTimerA2();
//                   Graphics_clearDisplay(&g_sContext); // Clear the display
//                   Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//                   while (timer_cnt < 1000){
//                       setLeds (0x4);
//                   }
//                   setLeds(0);
//                   timer_cnt = 0;
//                   stoptimerA2(1);
//
//                   runTimerA2();
//                   Graphics_clearDisplay(&g_sContext); // Clear the display
//                   Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//                   while (timer_cnt < 1000){
//                       setLeds (0x8);
//                   }
//                   setLeds(0);
//                   timer_cnt = 0;
//                   stoptimerA2(1);
//
//                   runTimerA2();
//                   Graphics_clearDisplay(&g_sContext); // Clear the display
//                   Graphics_drawStringCentered(&g_sContext, "GO!", AUTO_STRING_LENGTH, 48, 55, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//                   while (timer_cnt < 1000){
//                       setLeds (0xF);
//                   }
//                   setLeds(0);
//                   timer_cnt = 0;
//                   stoptimerA2(1);
//
//
//                   state = 2;
//               }
//               break;
//
//           case 2:
//               //play buzzer and lights
//
//               Graphics_clearDisplay(&g_sContext); // Clear the display
//               runTimerA2();
//
//
//               for (i = 0; i<NUM_NOTES; i++){				// loop runs for the length of total notes = 28
//                   while (timer_cnt < songArr[i].time){			// while loop runs with condition that every note played lasts for the duration from struct
//                       currButton = buttonState();			// setting up button input
//                       BuzzerOn(songArr[i].note);			// BuzzerOn takes note as parameter to play correct frequency and light up LED
//                       currScore++;					// score-to-achieve increments with every played note.
//                       displayScore = currScore + 0x30;			// displays score by converting to HEX
//                       Graphics_clearDisplay(&g_sContext); // Clear the display
//                       Graphics_drawStringCentered(&g_sContext, currButton, AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
//                       Graphics_flushBuffer(&g_sContext);
//                       checkInput(songArr[i].note);			// function to check input and find missed notes. Updates score and outputs to display
//
//                   }
//
//               }
//
//               stoptimerA2(1);
//               state = 4;
//               break;
//
//
//           case 4:
//               BuzzerOff();
//               if (win == 1){
//
//                   Graphics_drawStringCentered(&g_sContext, "You WIN!", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
//                   Graphics_drawStringCentered(&g_sContext, "Press '#'", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
//                   Graphics_drawStringCentered(&g_sContext, "To Play Game", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//                  //runtimer
//                   if (currKey == '#'){ //Replay game
//
//                       //runtimer
//                       state = 1;
//                       Graphics_clearDisplay(&g_sContext);
//                  }
//               }
//
//               if (win == 0){
//
//                   Graphics_drawStringCentered(&g_sContext, "You LOSE!", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
//                   Graphics_drawStringCentered(&g_sContext, "Press '#'", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
//                   Graphics_drawStringCentered(&g_sContext, "To Play Game", AUTO_STRING_LENGTH, 48, 45, TRANSPARENT_TEXT);
//                   Graphics_flushBuffer(&g_sContext);
//                   //runtimer
//                   if (currKey == '#'){ //Replay game
//
//                       //runtimer
//                       state = 1;
//                       Graphics_clearDisplay(&g_sContext);
//                  }
//               }
//
//                break;
//       }//switch
//   }//while
//}//main
//
//int duration (int time){
//    //Use TimerA to create a delay for notes to be played
//}
//
//
//void checkInput(char note){
//    //use getKey() function to compare user input to existing song
//    if (currButton != note2HEX(note)){
//        miss++;
//    }
//    if (miss >= (currScore*0.5)){
//        win = 0;
//        state = 4;
//    }
//    else if (miss < (currScore*0.5)){
//        win = 1;
//    }
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//    Graphics_drawStringCentered(&g_sContext, (char)miss, AUTO_STRING_LENGTH, 48, 65, TRANSPARENT_TEXT);
//    Graphics_flushBuffer(&g_sContext);
//}
//
//void runTimerA2(void){
//    TA2CTL = TASSEL_2 | MC_1 | ID_0;
//    TA2CCR0 = 1048;
//    TA2CCTL0 = CCIE;
//}
//
//void stoptimerA2(int reset){
//    TA2CTL = MC_0; //stop timer
//    TA2CCTL0 &= ~CCIE;
//    if (reset)
//        timer_cnt = 0;
//}
//
//#pragma vector=TIMER2_A0_VECTOR
//__interrupt void TimerA2_ISR (void){
//    if (leap_cnt < 2473056){
//        timer_cnt++;
//        leap_cnt++;
//    }
//    else{ //skip a count
//        leap_cnt = 0;
//        timer_cnt+= 2;
//    }
//}
//
//void swDelay(char numLoops)
//{
//    // This function is a software delay. It performs
//    // useless loops to waste a bit of time
//    //
//    // Input: numLoops = number of delay loops to execute
//    // Output: none
//    //
//    // smj, ECE2049, 25 Aug 2013
//
//    volatile unsigned int i,j;  // volatile to prevent removal in optimization
//                                // by compiler. Functionally this is useless code
//
//    for (j=0; j<numLoops; j++)
//    {
//        i = 50000 ;                 // SW Delay
//        while (i > 0)               // could also have used while (i)
//           i--;
//    }
//}
//
//
//unsigned char note2HEX (char note){
//
//
//    if(note == ('A' | 'Y' | 'F' | 'P')){
//        return 0x1;
//    }
//
//    if(note == ('Z' | 'D' | 'K')){
//        return 0x2;
//    }
//
//    if(note == ('B' | 'X' | 'G')){
//        return 0x4;
//    }
//
//    if(note == ('C' | 'E' | 'Q')){
//        return 0x8;
//    }
//
//
//}
//
