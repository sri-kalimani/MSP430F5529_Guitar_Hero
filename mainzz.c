//#include <msp430.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <math.h>
//#include "peripherals.h"
//
//// Temperature Sensor Calibration = Reading at 30 degrees C is stored at addr 1A1Ah
//// See end of datasheet for TLV table memory mapping
//#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)
//// Temperature Sensor Calibration = Reading at 85 degrees C is stored at addr 1A1Ch                                            //See device datasheet for TLV table memory mapping
//#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)
//
//unsigned int timer_cnt;
//unsigned int in_temp;
//
//void arrayTempC(float temp);
//char displayTime(unsigned long time);
//char ftoString(float temp);
//char itoString(int time);
//void runTimerA2(void);
//void stoptimerA2(int reset);
//
//
//int mainzz(void)
//{
//  volatile float tempC;
//  volatile float tempF;
//  volatile float degC_per_bit;
//  volatile unsigned int bits30, bits85;
//  long long int timer_cnt = 4675505;
//
//  WDTCTL = WDTPW + WDTHOLD;      // Stop WDT
//  _BIS_SR(GIE);
//
//  REFCTL0 &= ~REFMSTR;    // Reset REFMSTR to hand over control of
//                          // internal reference voltages to
//              // ADC12_A control registers
//
//  ADC12CTL0 = ADC12SHT0_9 | ADC12REFON | ADC12ON;     // Internal ref = 1.5V
//
//  ADC12CTL1 = ADC12SHP | ADC12CONSEQ0;                     // Enable sample timer
//
//  while(ADC12CTL1 & ADC12BUSY)
//      __no_operation();
//
//  // Using ADC12MEM0 to store reading
//  ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;  // ADC i/p ch A10 = temp sense
//                                        // ACD12SREF_1 = internal ref = 1.5v
//
//  __delay_cycles(100);                    // delay to allow Ref to settle
//  ADC12CTL0 |= ADC12ENC;              // Enable conversion
//
//  // Use calibration data stored in info memory
//  bits30 = CALADC12_15V_30C;
//  bits85 = CALADC12_15V_85C;
//  degC_per_bit = ((float)(85.0 - 30.0))/((float)(bits85-bits30));
//
//
//  while(1)
//  {
//    ADC12CTL0 &= ~ADC12SC;  // clear the start bit
//    ADC12CTL0 |= ADC12SC;       // Sampling and conversion start
//                                // Single conversion (single channel)
//
//    // Poll busy bit waiting for conversion to complete
//    while (ADC12CTL1 & ADC12BUSY)
//        __no_operation();
//    in_temp = ADC12MEM0;      // Read in results if conversion
//
//    // Temperature in Celsius. See the Device Descriptor Table section in the
//    // System Resets, Interrupts, and Operating Modes, System Control Module
//    // chapter in the device user's guide for background information on the
//    // formula.
//    tempC = (float)((long)in_temp - CALADC12_15V_30C) * degC_per_bit +30.0;
//
//    Graphics_clearDisplay(&g_sContext); // Clear the display
//    Graphics_drawStringCentered(&g_sContext, displayTime(timer_cnt), AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
//    Graphics_drawStringCentered(&g_sContext,     displayTemp(tempC), AUTO_STRING_LENGTH, 48, 20, TRANSPARENT_TEXT);
//    Graphics_flushBuffer(&g_sContext);
//
//
//    // Temperature in Fahrenheit
//
//    __no_operation();                       // SET BREAKPOINT HERE
//  }
//}
//
//void arrayTempC(float temp){
//
//}
//
//char displayTime(unsigned long time){
//        time = timer_cnt; //MAKE ALL THE REST OF THESE UNSIGNED LONGS
//
//        int i = 5;
//        char output = NULL;
//        unsigned char outDate = NULL;
//
//        unsigned long calc_day = time % (60L * 60L * 24L);
//        unsigned long days = (time - calc_day)/(60L*60L*24L);
//        unsigned long calc_hour = calc_day % (60L * 60L);
//        unsigned long hours = (calc_day - calc_hour)/(60L*60L);
//        unsigned long calc_min = calc_hour % 60L;
//        unsigned long mins = (calc_hour - calc_min)/60L;
//        unsigned long secs = calc_min;
//
//
//
//        char timeDisplay[9] = {(char)(hours % 10), (char)(hours % 100), ':', (char)(mins % 10), (char)(mins % 100), ':', (char)(secs % 10), (char)(secs % 100)};
//        char dateDisplay[10];
//
//        if(days > 0 && days <= 31){
//                strcpy(outDate, "Jan ");
//                dateDisplay[7] = {'J', 'a', 'n', ':'};
//        }
//        else if(days > 31 && days <= 59){
//                strcpy(outDate, "Feb ");
////                dateDisplay[7] = {'F', 'e', 'b', ':', (char)days};
//        }
//        else if(days > 59 && days <= 90){
//                strcpy(outDate, "Mar ");
////                dateDisplay[7] = {'M', 'a', 'r', ':', (char)days};
//        }
//        else if(days > 90 && days <= 120){
//                strcpy(outDate, "Apr ");
////                dateDisplay[7] = {'A', 'p', 'r', ':', (char)days};
//        }
//        else if(days > 120 && days <= 151){
//                strcpy(outDate, "May ");
////                dateDisplay[7] = {'M', 'a', 'y', ':', (char)days};
//        }
//        else if(days > 151 && days <= 181){
//                strcpy(outDate, "Jun ");
////                dateDisplay[7] = {'J', 'u', 'n', ':', (char)days};
//        }
//        else if(days > 181 && days <= 212){
//                strcpy(outDate, "Jul ");
////                dateDisplay[7] = {'J', 'u', 'l', ':', (char)days};
//        }
//        else if(days > 212 && days <= 243){
//                strcpy(outDate, "Aug ");
////                dateDisplay[7] = {'A', 'u', 'g', ':', (char)days};
//        }
//        else if(days > 243 && days <= 273){
//                strcpy(outDate, "Sep ");
////                dateDisplay[7] = {'S', 'e', 'p', ':', (char)days};
//        }
//        else if(days > 273 && days <= 304){
//                strcpy(outDate, "Oct ");
////                dateDisplay[7] = {'O', 'c', 't', ':', (char)days};
//        }
//        else if(days > 304 && days <= 334){
//                strcpy(outDate, "Nov ");
////                dateDisplay[7] = {'N', 'o', 'v', ':', (char)days};
//        }
//        else if(days > 334 && days <= 365){
//                strcpy(outDate, "Dec ");
////                dateDisplay[7] = {'D', 'e', 'c', ':', (char)days};
//        }
//        else {
//                strcpy(outDate, "Oops ");
//        }
//
//        for (i = 5; i<10; i++){
//              dateDisplay[i] = (char) days/10;
//              days = days %10;
//          }
//
////        char storeDays[20] = itoString(days, output);
////        strcat(outDate, storeDays[20]);
//
//        // graphic print time display
//
//        return(outDate);
//
//}
//
//char displayTemp(float tempC){
//        //getTemp();
//        char outTemp = NULL;
//        char output = NULL;
//        unsigned long tempF;
//        tempF = tempC * 9.0/5.0 + 32.0;
//
//        strcpy(outTemp, "F:");
//        char storeTempF[20] = ftoString(tempF, output);
//        strcat(outTemp, storeTempF[20]);
//        strcat(outTemp, " C:");
//        char storeTempC[20] = ftoString(tempC, output);
//        strcat(outTemp, storeTempC[20]);
//
//        return outTemp;
//}
//char ftoString(float temp, char store[20]){//float to string
//
//
//    return store[20];
//}
//
//char itoString(int time, char store[20]){ //int to string
//
//    int i = 0;
//    for (i = 0; i<20; i++){
//
//        store[i] = (char) time % (powf(10, (n-i)));
//    }
//    return store[20];
//
//}
//
//void runTimerA2(void){
//    TA2CTL = TASSEL_2 | MC_1 | ID_0;
//    TA2CCR0 = 1048575;
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
//        timer_cnt++;
//
//}
//
