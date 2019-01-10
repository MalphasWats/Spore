#ifndef SPIKE_H
# define SPIKE_H

#define F_CPU 16000000

#define ever ;;

#define LOW     0
#define HIGH    1

#define TRUE    0xFF
#define FALSE   0x00

#define SND   5  // PORTD

/* Display Pins (PORTB) */
#define CS      1
#define DC      3
#define RST     2

#define SCK     0

/* Display Pins (PORTD) */
#define MOSI    1

/* Button Pins (PORTC) */
#define UP          6
#define DOWN        5
#define LEFT        4
#define RIGHT       3
#define BTN_A       2
#define BTN_B       1
#define BTN_C       0

/* Button Masks */
#define _UP        0b01000000
#define _DOWN      0b00100000
#define _LEFT      0b00010000
#define _RIGHT     0b00001000
#define _A         0b00000100
#define _B         0b00000010
#define _C         0b00000001

#define BTN_DELAY       20

#define SPLASH_DELAY    1500

#define CMD             LOW
#define DATA            HIGH

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   64

#define HALF_SCREEN_WIDTH   128/2
#define HALF_SCREEN_HEIGHT  64/2

#define SCREEN_COLUMNS  16
#define SCREEN_ROWS     8

// http://www.soundoctor.com/freq.htm
//      NOTE    OCR1A  FREQ.(Hz)  Note        
#define _A4      2273 // 440,     Concert A(4)  0
#define _Bb4     2146 // 466,     Bb(4)         1
#define _B4      2024 // 494,     B(4)          2
#define _C5      1912 // 523,     C(5)          3
#define _Cs5     1805 // 554,     C#(5)         4
#define _D5      1703 // 587,     D(5)          5
#define _Ds5     1608 // 622,     D#(5)         6
#define _E5      1518 // 659,     E(5)          7
#define _F5      1433 // 698,     F(5)          8
#define _Fs5     1351 // 740,     F#(5)         9
#define _G5      1337 // 748,     G(5)          A
#define _Gs5     1203 // 831,     G#(5)         B
#define _A5      1250 // 800,     A(5)          C
#define _Bb5     1073 // 932,     Bb(5)         D
#define _B5      1012 // 988,     B(5)          E
#define _A8      142  // 7040,    A8            F
#define _A9      71   // 14080    A9            X

#define NOTE_DURATION_MULTIPLIER 15    // 1ms

typedef unsigned char byte;
typedef unsigned int word;

typedef struct Viewport {
    int x;
    int y;
} Viewport;

byte buffer[SCREEN_WIDTH * SCREEN_ROWS];

static const __flash byte LOGO[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x78, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x02, 0x03, 0x03, 0x03, 0xff, 0x0e, 0xff, 0x03, 0x03, 0x03, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x18, 0x18, 0x18, 0x18, 0x08, 0x10, 0x18, 0x18, 0x18, 0x18, 0xd0, 0xe0, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x10, 0x18, 0x18, 0x18, 0x18, 0x17, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe3, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0xc3, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0xd7, 0x18, 0x18, 0x18, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x17, 0x0f, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x10, 0x00, 0x00, 
};

#define LOGO_WIDTH 96
#define LOGO_HEIGHT 24/8

#define rngM 7919
#define rngA 17
#define rngC 3
word rng( void );

void delay_ms( word ms );

// http://www.oz4.us/2015/12/recoding-bare-millis-clock-on-avr.html
// https://github.com/sourceperl/millis/blob/master/millis.c
// https://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-timers?page=all
void initialise( void );
word millis( void );

/* OLED Function */
void shift_out_byte(byte val);

void initialise_oled(void);
void clear_buffer(void);

void draw(void);
void display_off(void);
void display_on(void);

void note(word note, word dur);
void click( void );

#endif