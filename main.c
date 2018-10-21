#include <msp430.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "peripherals.h"

unsigned long timer_cnt = 4675505; // + 890; for bell toll

char* displayDate(void);
char* displayTime(void);
void runTimerA2(void);
void stoptimerA2(int reset);
char* itoaa(int i, char b[]);
void buzzerCtrl(void);
char* ftoa(float n, char *res);
float readPotVoltage(void);
char* convertToTemp(void);
int intToStr(int x, char str[], int d);
void swDelay(char numLoops);

#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)

volatile float degC_per_bit;
volatile unsigned int bits30, bits85;

unsigned long curTime = 0;
volatile float tempC;
volatile float tempF;
char output[100];
char outTemp[500];
char outTime[500];
char outDate[500];
unsigned long seconds = 0;
char time[100];
volatile float in_temp;
int times[120];
int temps[120];
int buzzerState = 0;


int main(){


    bits30 = CALADC12_15V_30C;
    bits85 = CALADC12_15V_85C;
    degC_per_bit = ((float)(85.0 - 30.0)) / ((float)(bits85 - bits30));

    WDTCTL = WDTPW + WDTHOLD;      // Stop WDT
    _BIS_SR(GIE);

    // configure ADC Temperature (configADCTemp())
    REFCTL0 &= ~REFMSTR;
    ADC12CTL0 = ADC12SHT0_9|ADC12REFON|ADC12ON;
    ADC12CTL1 = ADC12SHP;
    ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;
    P6SEL |= BIT0;
    ADC12CTL0 |= ADC12SC + ADC12ENC;

    // configure everything else
    initLeds();
    configDisplay();
    configKeypad();
    configButtons();
    Graphics_clearDisplay(&g_sContext);

    runTimerA2();
    curTime = timer_cnt;
    while (1){
        buzzerCtrl();
        displayTime();
            if(buttonState() == 0x01){
                buzzerState = 1;
            }
            if(buttonState() == 0x02){
                BuzzerOff();
                buzzerState = 0;
            }
            if(timer_cnt - curTime >= 1){
                curTime = timer_cnt;
                seconds++;
                Graphics_drawStringCentered(&g_sContext, displayDate(), AUTO_STRING_LENGTH, 48, 20, OPAQUE_TEXT);
                Graphics_drawStringCentered(&g_sContext, displayTime(), AUTO_STRING_LENGTH, 48, 30, OPAQUE_TEXT);
                Graphics_drawStringCentered(&g_sContext, convertToTemp(), AUTO_STRING_LENGTH, 48, 40, OPAQUE_TEXT);

                Graphics_flushBuffer(&g_sContext);


            }
        }

    }

char* convertToTemp(){
    REFCTL0 &= ~REFMSTR;
    ADC12CTL0 = ADC12SHT0_9|ADC12REFON|ADC12ON;
    ADC12CTL1 = ADC12SHP;
    ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_10;

    P6SEL |= BIT0;

    ADC12CTL0 |= ADC12SC + ADC12ENC;

    ADC12CTL0 &= ~ADC12SC;
    ADC12CTL0 |= ADC12SC;

    while(ADC12CTL1 & ADC12BUSY){
        __no_operation();
    }

    in_temp = ADC12MEM0;

    tempC = (float)(in_temp - CALADC12_15V_30C) * degC_per_bit + 30.0; //(float)((long)in_temp - CALADC12_15V_30C) * degC_per_bit + 30.0;
    tempF = tempC * 9.0/5.0 + 32.0;

    strcpy(outTemp, "F:");
    strcat(outTemp, ftoa(tempF, output));
    strcat(outTemp, " C:");
    strcat(outTemp, ftoa(tempC, output));

    return outTemp;
}

void buzzerCtrl(){
    int freq = (int)readPotVoltage();
    freq = freq *250;
    if (buzzerState){
    BuzzerOn(freq);
    }
}

float readPotVoltage(){
    unsigned int potReading = 0;
    float potVolts;

    ADC12CTL0 = ADC12SHT0_9 | ADC12ON; // Turn on ADC
    ADC12CTL1 = ADC12SHP; // Sample and Hold mode
    ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_0; //ref = 3.3V, ch = A0
    P6SEL |= BIT0; // Port 6 pin 0 to function mode in ADC
    ADC12CTL0 &= ~ADC12SC; // clear start bit
    // enable and start single conversion
    ADC12CTL0 |= ADC12SC | ADC12ENC;
    while (ADC12CTL1 & ADC12BUSY)
    __no_operation();
    potReading = ADC12MEM0 & 0x0FFF; //keep low 12 bits
    potVolts = potReading * 3.3/ 4096; // convert to volts
    return potVolts;
}


char* displayDate(){
       unsigned long time = timer_cnt; //MAKE ALL THE REST OF THESE UNSIGNED LONGS


        unsigned long calc_day = time % (60L * 60L * 24L);
        unsigned long days = (time - calc_day)/(60L*60L*24L);
        unsigned long calc_hour = calc_day % (60L * 60L);
        unsigned long hours = (calc_day - calc_hour)/(60L*60L);
        unsigned long calc_min = calc_hour % 60L;
        unsigned long mins = (calc_hour - calc_min)/60L;
        unsigned long secs = calc_min;



//        char timeDisplay[9] = {(char)(hours % 10), (char)(hours % 100), ':', (char)(mins % 10), (char)(mins % 100), ':', (char)(secs % 10), (char)(secs % 100)};
//        char dateDisplay[10];


        if(days > 31 && days <= 59){
                strcpy(outDate, "Feb ");
                days = days % 31;
        }
        else if(days > 59 && days <= 90){
                strcpy(outDate, "Mar ");
                days = days % 59;
        }
        else if(days > 90 && days <= 120){
                strcpy(outDate, "Apr ");
                days = days % 90;
        }
        else if(days > 120 && days <= 151){
                strcpy(outDate, "May ");
                days = days % 120;
        }
        else if(days > 151 && days <= 181){
                strcpy(outDate, "Jun ");
                days = days % 151;
        }
        else if(days > 181 && days <= 212){
                strcpy(outDate, "Jul ");
                days = days % 181;
        }
        else if(days > 212 && days <= 243){
                strcpy(outDate, "Aug ");
                days = days % 212;
        }
        else if(days > 243 && days <= 273){
                strcpy(outDate, "Sep ");
                days = days % 243;
        }
        else if(days > 273 && days <= 304){
                strcpy(outDate, "Oct ");
                days = days % 273;
        }
        else if(days > 304 && days <= 334){
                strcpy(outDate, "Nov ");
                days = days % 304;
        }
        else if(days > 334 && days <= 365){
                strcpy(outDate, "Dec ");
                days = days % 365;
        }
        else {
                  strcpy(outDate, "Jan ");

          }


       strcat(outDate, itoaa(days, output));

       return outDate;

}

char* displayTime(){

    unsigned long time = timer_cnt; //MAKE ALL THE REST OF THESE UNSIGNED LONGS

    unsigned long calc_day = time % (60L * 60L * 24L);
    unsigned long days = (time - calc_day)/(60L*60L*24L);

    unsigned long calc_hour = calc_day % (60L * 60L);
    unsigned long hours = (calc_day - calc_hour)/(60L*60L);

    unsigned long calc_min = calc_hour % 60;
    unsigned long mins = (calc_hour - calc_min)/60;

    unsigned long secs = calc_min;

    //strcat(out, ", ");
    strcpy(outTime, itoaa(hours, output));
    strcat(outTime, ":");
    strcat(outTime, itoaa(mins, output));
    strcat(outTime, ":");
    if(secs < 10){
        strcat(outTime, "0");
        strcat(outTime, itoaa(secs, output));
    }
    else{
        strcat(outTime, itoaa(secs, output));
    }

    while (mins == 0 && secs == 0){
        BuzzerOn(500);
        swDelay(1);
        break;
    }
    BuzzerOff();

    return outTime;
}


void runTimerA2(void){
    TA2CTL = TASSEL_1 | MC_1 | ID_0;
    TA2CCR0 = 32767;
    TA2CCTL0 = CCIE;
}

void stoptimerA2(int reset){
    TA2CTL = MC_0; //stop timer
    TA2CCTL0 &= ~CCIE;
    if (reset)
        timer_cnt = 0;
}

char* itoaa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as you go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

char* ftoa(float n, char *res)
{
    int afterpoint = 2;// # of decimal places we want

    // Extract integer part
    int ipart = (int)n;

    // Extract floating part
    float fpart = n - (float)ipart;

    // convert integer part to string
    int i = intToStr(ipart, res, 0);

    res[i] = '.';  // add dot

    fpart = fpart * pow(10, afterpoint);

    intToStr((int)fpart, res + i + 1, afterpoint);

    return res;
}

// Helper function for the ftoa function
void reverse1(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

// Helper function for the ftoa function. Different from the itoa function.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }

    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';

    reverse1(str, i);
    str[i] = '\0';
    return i;
}

#pragma vector=TIMER2_A0_VECTOR
__interrupt void TimerA2_ISR (void){
        timer_cnt++;

}

void swDelay(char numLoops)
{
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}
