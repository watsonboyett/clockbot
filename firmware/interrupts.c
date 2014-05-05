

#include <p24Fxxxx.h>

#include "pin_defs.h"
#include "display.h"
#include "utils.h"
#include "globals.h"

unsigned long accum = 0;
unsigned int count = 0;
signed short cal = 0;

short discharOne = 0;
short discharTwo = 0;

//"mov.w 0x0100, w9"

void __attribute__((interrupt(__preprologue__("nop")), no_auto_psv)) _RTCCInterrupt(void) {
    IFS3bits.RTCIF = 0;

    /*
            accum = accum + TMR1;
            count++;
            if(minutes_ones == 0x0000 && seconds == 0x0000)
            {
                    accum = accum / count;
                    cal = (accum - 31250) * 15;
                    if(cal > 127) { cal = 127; }
                    else if(cal < -128) { cal = -128; }
                    RCFGCALbits.CAL = cal;
                    accum = 0;
                    count = 0;
            }
     */
    if (model == clock_1 || model == clock_2 || model == clock_3) {
        IFS0bits.T1IF = 1; // set Timer1 interrupt flag to confirm one second has passed
    }
    else if (model == belt_1) {
        RCFGCALbits.RTCPTR = 0b00; // set pointer to read minutes/seconds (remains here)
        minutes = (RTCVAL & 0x7F00) >> 8;
        minutes_tens = (minutes & 0x0070) >> 4;
        minutes_ones = (minutes & 0x000F);
        seconds = (RTCVAL & 0x007F);
        seconds_tens = (seconds & 0x0070) >> 4;
        seconds_ones = seconds & 0x000F;

        if (seconds_ones == 0) {

            discharOne++;

            if (discharOne > 10) {
                discharOne = 0;
            }

            faceOne_ptr = sprites[discharOne];
            faceTwo_ptr = sprites[discharOne];

            transition_flag = 1;
        }
    }

    TMR1 = 0x0000;
}

void __attribute__((interrupt(__preprologue__("nop")), no_auto_psv)) _CNInterrupt(void) {
    IEC1bits.CNIE = 0;

    faderate_buf = faderate;


    if (IN_LEFT == 0 || IN_RIGHT == 0) {
        if (model == clock_1 || model == clock_2 || model == clock_3) {
            RCFGCALbits.RTCEN = 0;
            PR5 = 0x3CF0;

            IFS1bits.T5IF = 0; // clear button scan interrupt flag????
            IPC7bits.T5IP = 4; // set interrupt level priority
            IEC1bits.T5IE = 1; // set interrupt enable for button scanning
            IFS1bits.T5IF = 0; // cause Timer5 interrupt to occur
        } else {
            IFS1bits.T5IF = 0; // clear button scan interrupt flag????
            IPC7bits.T5IP = 4; // set interrupt level priority
            IEC1bits.T5IE = 1; // set interrupt enable for button scanning
            IFS1bits.T5IF = 0; // cause Timer5 interrupt to occur

            if (model == counter_2) {
                PR5 = 0x4CF0;
            } else {
                PR5 = 0x7CF0;
            }
        }

    } else if (IN_LEFT == 1 && IN_RIGHT == 1) {
        if (model == clock_1 || model == clock_2 || model == clock_3) {
            RCFGCALbits.RTCEN = 1;
        }
        IEC1bits.T5IE = 0; // set interrupt enable for button scanning
        IFS1bits.T5IF = 0; // clear button scan interrupt flag
    }

    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;

}

void __attribute__((interrupt, no_auto_psv)) _T5Interrupt(void) {

    if (model == clock_1 || model == clock_2 || model == clock_3) {

#ifdef showsec
        if (IN_LEFT == 0) // this code increments the minutes value
        {
            RCFGCALbits.RTCPTR = 0b00;
            RTCVAL = RTCVAL + 0x0100;
            if ((RTCVAL & 0x0F00) >= 0x0A00) {
                RTCVAL = (RTCVAL & 0xF0FF) + 0x1000;
            }
            if ((RTCVAL & 0xFF00) >= 0x5A00) {
                RTCVAL = RTCVAL & 0x00FF;
            }
        }
        if (IN_RIGHT == 0) // this code increments the seconds value
        {
            RCFGCALbits.RTCPTR = 0b00;
            RTCVAL++;
            if ((RTCVAL & 0x000F) >= 0x000A) {
                RTCVAL = (RTCVAL & 0xFFF0) + 0x0010;
            }
            if ((RTCVAL & 0x00FF) >= 0x005A) {
                RTCVAL = RTCVAL & 0xFF00;
            }
        }
#else
        if (IN_LEFT == 0) //this code increments the hours value
        {
            int temp;
            RCFGCALbits.RTCPTR = 0b01;
            temp = RTCVAL + 1;
            if ((temp & 0x000F) >= 0x000A) {
                temp = (temp & 0xFFF0) + 0x0010;
            }
            if ((temp & 0x00FF) >= 0x0018) {
                temp = temp & 0xFF00;
            }
            RCFGCALbits.RTCPTR = 0b01;
            RTCVAL = temp;
        }
        if (IN_RIGHT == 0) // this code increments the minutes value
        {
            RCFGCALbits.RTCPTR = 0b00;
            RTCVAL = RTCVAL + 0x0100;
            if ((RTCVAL & 0x0F00) >= 0x0A00) {
                RTCVAL = (RTCVAL & 0xF0FF) + 0x1000;
            }
            if ((RTCVAL & 0xFF00) >= 0x5A00) {
                RTCVAL = RTCVAL & 0x00FF;
            }
        }
#endif

        update_number();
    }
    else if (model == monk_1) {
        if (IN_LEFT == 0) {
            discharOne++;

            if (discharOne > 10) {
                discharOne = 0;
            }

            faceOne_ptr = sprites[discharOne];
            faceTwo_ptr = sprites[discharOne];
        }

        if (IN_RIGHT == 0) {
            discharTwo++;

            if (discharTwo > 10) {
                discharTwo = 0;
            }

            faceOne_ptr = faces[discharTwo];
            faceTwo_ptr = faces[discharTwo];
        }

        transition_flag = 1;
    } else if (model == monk_2) {
        if (IN_LEFT == 0) {
            discharOne++;

            if (discharOne > 10) {
                discharOne = 0;
            }

            faceOne_ptr = faces[discharOne];
            faceTwo_ptr = faces[discharTwo];
        }

        if (IN_RIGHT == 0) {
            discharTwo++;

            if (discharTwo > 10) {
                discharTwo = 0;
            }
            faceOne_ptr = faces[discharOne];
            faceTwo_ptr = faces[discharTwo];
        }

        transition_flag = 1;
    }
    else if (model == counter_2) {

        IFS0bits.T1IF = 1; // set Timer1 interrupt flag to confirm one second has passed

        if (IN_LEFT == 0) // this code increments the minutes value
        {
            countVarLeft++;

            RED_DC = 200;
            GREEN_DC = 0;
            ANODE_DC = 0;
        } else if (IN_RIGHT == 0) // this code increments the minutes value
        {
            countVarRight++;

            RED_DC = 0;
            GREEN_DC = 200;
            ANODE_DC = 0;
        }

        update_number();

    }



    if (model == counter_2) {
        PR5 = 0xfff0;
    } else {
        if (PR5 >= 1500) {
            PR5 = PR5 - 0x0100;
        }
    }

    IFS1bits.T5IF = 0;
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0;

    if (U1STAbits.UTXBF == 1) {
        Nop();
        delay(100);
    }
}


unsigned char rcvd_data;
unsigned char startFlagRcvd;
unsigned char stopFlagRcvd;
unsigned char bytesRcvd;
unsigned char startFlag;
unsigned char header[3];
unsigned char messageType;
unsigned char bytesToFollow;
unsigned char dataPacket[24];
unsigned char footer;
unsigned char stopFlag;
unsigned char rcvd_data;
unsigned char message[32];
short loc = 0;
short data_to_process;

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;

    if (U1STAbits.OERR == 1) //receive buffer overflow
    {
        delay(100);
        U1STAbits.OERR = 0;
    }

    rcvd_data = U1RXREG;


    while (U1STAbits.UTXBF == 1) {
        Nop();
    } // hangout here until transmit buffer is available

    if (rcvd_data == 240) {
        startFlagRcvd = 1;

        loc = 0;
        bytesRcvd = 0;
        stopFlagRcvd = 0;
    }


    if (startFlagRcvd) {
        message[loc] = rcvd_data;

        if (loc < 1) {
            startFlag = rcvd_data;
        }
        else if (loc < 4) {
            header[loc - 1] = rcvd_data;
        } else if (loc < 5) {
            messageType = rcvd_data;
        } else if (loc < 6) {
            bytesToFollow = rcvd_data;
        } else if (loc < (6 + bytesToFollow)) {
            bytesRcvd = bytesRcvd + 1;
            dataPacket[loc - 6] = rcvd_data;
        } else if (loc < (6 + bytesToFollow + 1)) {
            footer = rcvd_data;
        } else if (loc < (6 + bytesToFollow + 2)) {
            stopFlag = rcvd_data;
        }
        else {

        }

        loc = loc + 1;
    }

    if (rcvd_data == 247) {
        if (bytesToFollow == bytesRcvd) {
            U1TXREG = bytesRcvd;
        } else {
            U1TXREG = bytesRcvd;
        }

        stopFlagRcvd = 1;

        startFlagRcvd = 0;
        bytesRcvd = 0;
        loc = 0;

        data_to_process = 1;
    }
}

void process_Message(void) {
    short i;

    if (messageType == 1) {
        for (i = 0; i < 8; i++) {
            //userSpace[footer][i] = (dataPacket[(2*i)+1] << 4) + dataPacket[(2*i)];
        }
    }

    discharOne++;

    if (discharOne > 10) {
        discharOne = 1;
    }

    //faceOne_ptr = &userSpace[footer];
    //faceTwo_ptr = &userSpace[footer];

    data_to_process = 0;
    transition_flag = 1;

}

/*
                        U1TXREG = START_FLAG;
                        loc = 0;
                        while(loc < 12)
                        {
                                while(U1STAbits.UTXBF == 1) { Nop(); }	// hangout here until transmit buffer is available
				
                                U1TXREG = message[loc];
                                loc = loc + 1;
                        }
			
                        loc = 0;
                        while(U1STAbits.UTXBF == 1) { Nop(); }	// hangout here until transmit buffer is available
	
                        U1TXREG = STOP_FLAG;
 */

