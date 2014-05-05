

#include <p24Fxxxx.h>

#include "pin_defs.h"
#include "display.h"
#include "globals.h"
#include "utils.h"

void InitPIC() {
    // Declare all port pins directions
    TRISA = 0b0000000000000000;
    TRISB = 0b0000000110000000;

    // Initialize outputs to 0
    PORTA = 0b0000000000000000;
    PORTB = 0b0000000000000000;

    // disable all open-drain pin configurations
    ODCA = 0b0000000000000000;
    ODCB = 0b0000000000000000;

    // Disable Shift Register outputs
    OE_ANODE = 1; //delay(d);
    OE_RED = 1; //delay(d);
    OE_GREEN = 1; //delay(d);

    // Get ready to clock in contents of Shift Registers
    STORE = 0;

    // Clear all Shift Registers
    MCLR = 0;
    delay(d);

    // Clock in contents of empty Shift Registers
    STORE = 1;


    __builtin_write_OSCCONL(OSCCON & 0xbf);


#ifdef H24
    CLKDIVbits.PLLPRE = 0;
    CLKDIVbits.PLLPOST = 0;
    PLLFBDbits.PLLDIV = 30;
#else
    CLKDIVbits.RCDIV = 0b000;
#endif

    PMCONbits.PMPEN = 0;
    PMCONbits.PTWREN = 0;
    PMCONbits.PTRDEN = 0;
    U1MODEbits.UARTEN = 0;
    SPI1STATbits.SPIEN = 0;
    SPI2STATbits.SPIEN = 0;
    I2C1CONbits.I2CEN = 0;
    //	I2C2CONbits.I2CEN = 0;
    CVRCONbits.CVREN = 0;
    CVRCONbits.CVROE = 0;
    CMCONbits.C1EN = 0;
    CMCONbits.C2EN = 0;
    AD1CON1bits.ADON = 0;

#ifdef H24
    ADPCFG = 0xFFFF;
#else
    AD1PCFG = 0xFFFF;
#endif

    if (model == clock_1 || model == clock_2 || model == clock_3 || model == belt_1) {
        // Enable the RealTimeClock
        NVMKEY = 0x55;
        NVMKEY = 0xAA;
        RCFGCALbits.RTCWREN = 1; // enable user write
        RCFGCALbits.RTCEN = 1; // enable RTCC peripheral
        RCFGCALbits.RTCSYNC = 0; // maybe change this for error handling?
        RCFGCALbits.RTCOE = 0; // RTCC output pin disabled

        if (model == counter_2) {

        } else {
            ALCFGRPTbits.ALRMEN = 1; // Enable alarm
            ALCFGRPTbits.CHIME = 1; // Enable interrupt events to occur
            ALCFGRPTbits.AMASK = 0b0001; // Set interrupt mask for every second
            ALCFGRPTbits.ARPT = 0xFF; // Allow them to occur indefinately (forever..)

            RCFGCALbits.RTCPTR = 0b01; // set pointer window for weekday/hours
            RTCVAL = 0x0000; // set initial weekday/hour values
            RCFGCALbits.RTCPTR = 0b00; // set pointer window for minutes/seconds
            RTCVAL = 0x0000; // set initial minutes/seconds values
        }

        // Enable Timer1 for RTCC correction
        T1CONbits.TON = 1; // Enable Timer1
        T1CONbits.TCKPS = 0b11; // Timer1 clock prescaler 1:256
        T1CONbits.TCS = 0; // Timer1 clock select set to main clock (internal RC)
        T1CONbits.TGATE = 0; // Disable Gated Timer1 accummulation
        T1CONbits.TSYNC = 1; // i forget what this does...
        T1CONbits.TSIDL = 0; // Do not turn off when in Idle Mode
    }

    // Enable Timer5 for button scanning
    T5CONbits.TON = 1; // Enable Timer5
    T5CONbits.TCKPS = 0b11; // Timer5 clock prescaler 1:?
    T5CONbits.TCS = 0; // Timer5 clock select set to main clock (internal RC)
    PR5 = 0xC3F0; // subtle reference to Star Wars, anyone?

    // Enable Input Pull-Ups on RB0 and RB1
    CNPU2bits.CN22PUE = 1; // RB8 pull-up (left input)
    CNPU2bits.CN23PUE = 1; // RB7 pull-up (right input)

    __asm__ volatile ("MOV #OSCCON, w1");
    __asm__ volatile ("MOV #0x46, w2");
    __asm__ volatile ("MOV #0x57, w3");
    __asm__ volatile ("MOV.b w2, w1");
    __asm__ volatile ("MOV.b w3, w1");
    __asm__ volatile ("BCLR OSCCON, #6");

    // Assign Peripheral Select Pins for corresponding outputs
    RPOR0 = 0x00; // set to 00 for NULL
    RPOR1 = 0x00;
    RPOR2 = 0x00;
    RPOR3 = 0x00;
    RPOR4 = 0x00;
    RPOR5bits.RP10R = 21; // set to 21 for PWM4(OE_ANODE)
    RPOR6bits.RP12R = 19; // set to 19 for PWM2(OE_RED)
    RPOR7bits.RP15R = 20; // set to 20 for PWM3(OE_GREEN)

    RPINR18bits.U1RXR = 7; //Assign U1 RXD (func. 18) to RP7
    RPOR4bits.RP8R = 3; //Assign U1 TXD (func. 3) to RP8

    __asm__ volatile ("MOV #OSCCON, w1");
    __asm__ volatile ("MOV #0x46, w2");
    __asm__ volatile ("MOV #0x57, w3");
    __asm__ volatile ("MOV.b w2, w1");
    __asm__ volatile ("MOV.b w3, w1");
    __asm__ volatile ("BSET OSCCON, #6");

    __builtin_write_OSCCONL(OSCCON | 0x42);

}


model_t model;

void GetModel(void) {
    // Declare all port pins directions
    TRISA = 0b0000000000000000;
    TRISB = 0b0000000110000000;

    // Initialize outputs to 0
    PORTA = 0b0000000000000000;
    PORTB = 0b0000000000000000;

    // disable all open-drain pin configurations
    ODCA = 0b0000000000000000;
    ODCB = 0b0000000000000000;

    // Enable Input Pull-Ups on RB0 and RB1
    CNPU2bits.CN22PUE = 1; // RB8 pull-up (left input)
    CNPU2bits.CN23PUE = 1; // RB7 pull-up (right input)

    if (PORTBbits.RB7 == 0 && PORTBbits.RB8 == 0) {
        model = monk_1;
    }

    if (PORTBbits.RB7 == 0 && PORTBbits.RB8 == 1) {
        model = clock_2;
    }
    if (PORTBbits.RB7 == 1 && PORTBbits.RB8 == 0) {
        model = counter_2;
    }
    if (PORTBbits.RB7 == 1 && PORTBbits.RB8 == 1) {
        model = belt_1;
    }


    model = monk_1;

    // DisEnable Input Pull-Ups on RB0 and RB1
    CNPU2bits.CN22PUE = 0; // RB8 pull-up (left input)
    CNPU2bits.CN23PUE = 0; // RB7 pull-up (right input)
}

void InitPWM() {
    // PWM2 = Red | PWM3 = Green | PWM4 = Anode
    // LOW level on OE results in display being on (lower DC produces longer ON time)

    // set period of PWM to 255 clock cycles
    PR2 = PERIOD;
    PR3 = PERIOD;
    PR4 = PERIOD;

    // set duty cycle of PWMs
    RED_DC = 0;
    GREEN_DC = 0;
    ANODE_DC = 0;

    // set PWMs to non fault mode
    OC2CONbits.OCM = 0b110;
    OC3CONbits.OCM = 0b110;
    OC4CONbits.OCM = 0b110;

    // set TMR2/TMR3 & TMR4/TMR5 to operate in 16bit mode
    T2CONbits.T32 = 0;
    T4CONbits.T32 = 0;

    // set TMRs prescale value to 1:256
    T2CONbits.TCKPS = 0b01;
    T3CONbits.TCKPS = 0b01;
    T4CONbits.TCKPS = 0b01;

    // use Fosc/2 as clock sourse
    T2CONbits.TCS = 0;
    T3CONbits.TCS = 0;
    T4CONbits.TCS = 0;

    // turn TMRs on
    T2CONbits.TON = 1;
    T3CONbits.TON = 1;
    T4CONbits.TON = 1;
}

void InitUART(void) {
    //int BAUD_9600 = 103;
    int BAUD_38400 = 25;
    //int BAUD_230400 = 3;

    RPINR18bits.U1RXR = 7; //Assign U1 RXD (func. 18) to RP7
    RPOR4bits.RP8R = 3; //Assign U1 TXD (func. 3) to RP8

    U1BRG = BAUD_38400; //set up baud rate

    IPC3bits.U1TXIP = 6; //Set Uart TX Interrupt Priority
    IPC2bits.U1RXIP = 6; //Set Uart RX Interrupt Priority

    U1STAbits.UTXBRK = 0; //Sync break transmission disables
    U1STAbits.UTXINV = 0; //TX idle state is LOW (no inversion)
    U1STAbits.UTXISEL0 = 0; //interrupt at end of all transmitted characters
    U1STAbits.UTXISEL1 = 0;
    //U1STAbits.URXDA = data available?
    //U1STAbits.OERR = receive buffer overflow
    //U1STAbits.FERR = framing error?
    //U1STAbits.PERR = parity error?
    //U1STAbits.RIDLE = receive idle bit?
    U1STAbits.ADDEN = 0; //address detect mode disabled
    U1STAbits.URXISEL = 0; //RX interrupt generated on every receive character
    //U1STAbits.TRMT = transmit register empty?
    //U1STAbits.UTXBF = transmit buffer full?

    U1MODEbits.USIDL = 0; //stop operation in idle mode
    U1MODEbits.IREN = 0; //disable IrDA
    U1MODEbits.RTSMD = 0; //flow control mode
    U1MODEbits.UEN = 0; //use just TXD and RXD pins
    U1MODEbits.WAKE = 0; //wake disabled
    U1MODEbits.LPBACK = 0; //disable loopback mode
    U1MODEbits.ABAUD = 0; //Auto-Buad detect disables
    U1MODEbits.RXINV = 0; //RX idle is HIGH (no inversion)
    U1MODEbits.BRGH = 0; //disable high baud rate select
    U1MODEbits.PDSEL = 0; //8-bit data, no parity
    U1MODEbits.STSEL = 0; //1 stop bit
    U1MODEbits.UARTEN = 1; //enable UART

    IFS0bits.U1TXIF = 0;
    IEC0bits.U1TXIE = 1; //Enable Transmit Interrupt
    IEC0bits.U1RXIE = 1; //Enable Receive Interrupt

    U1STAbits.UTXEN = 1; //enable transmission pin
    IFS0bits.U1TXIF = 0;

}
