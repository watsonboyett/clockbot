

#include <p24Fxxxx.h>

#include "prototypes.h"
#include "init_device.h"
#include "display.h"
#include "transitions.h"
#include "utils.h"
#include "globals.h"


// set processor configuration registers
#ifdef H24
_FOSCSEL(FNOSC_PRIPLL & IESO_OFF)
_FOSC(POSCMD_XT & FCKSM_CSDCMD & IOL1WAY_ON & OSCIOFNC_OFF)
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPOST_PS1)
_FPOR(ALTI2C_OFF & FPWRT_PWR1)
_FICD(BKBUG_OFF & COE_OFF & JTAGEN_OFF & ICS_PGD1)
#else

_CONFIG1(FWDTEN_OFF & JTAGEN_OFF & GCP_OFF & GWRP_OFF & COE_OFF & ICS_PGx1)
_CONFIG2(FNOSC_FRCPLL & POSCMOD_HS & FCKSM_CSDCMD & IESO_OFF & OSCIOFNC_ON & IOL1WAY_ON)
//_CONFIG2( FNOSC_PRIPLL & POSCMOD_XT & FCKSM_CSDCMD & IESO_OFF & OSCIOFNC_OFF & IOL1WAY_ON )
#endif





int main(void) {
    GetModel();
    InitPIC();
    InitPWM();
    //InitUART();

    Intro();



    // Note: Lowest Priority = 0 -> Highest Priority = 7
    if (model == clock_1 || model == clock_2 || model == clock_3 || model == belt_1) {
        IEC3bits.RTCIE = 1; // enable RTCC interrupt for crystal calibration and correction
        IFS3bits.RTCIF = 0; // make sure the interrupt flag is clear
        IPC15bits.RTCIP = 6; // set RTCC second passing priority to highest level

        IFS0bits.T1IF = 0; // use TMR1 interrupt flag for one second notification in software
        IEC0bits.T1IE = 0; // disable TMR1 interrupts -> used only as a counter
        IPC0bits.T1IP = 1; // no need for TMR1 interrupt priority..

        if (model == belt_1) {

        } else {
            update_number();
        }
    } else if (model == counter_2) {
        update_number();
    }

    CNEN2bits.CN23IE = 1; // enable Change Notification interrupt for CN27 (minutes)
    CNEN2bits.CN22IE = 1; // enable Change Notification interrupt for CN24 (hours)
    IFS1bits.CNIF = 0; // clear Change Notification interrupt flag
    IEC1bits.CNIE = 1; // enable Change Notification interrupt
    IPC4bits.CNIP = 3; // set Change Notification interrupt priority

    IFS1bits.T5IF = 0; // clear button scan interrupt flag
    IEC1bits.T5IE = 0; // set interrupt enable for button scanning
    IPC7bits.T5IP = 4; // set interrupt level priority


    /* infinite routine - keep as short as possible */
    while (1) {

        left_ptr = &left[7];
        right_ptr = &right[7];
        anode_ptr = &anode[7];

        display();


        // can only trigger when model is of clock type
        if (IFS0bits.T1IF == 1) // has one second passed?
        {
            IFS0bits.T1IF = 0; // clear Timer1 interrupt flag to allow for next one
            update_number(); // and update the output
        }

        // can only trigger when model is of monk type
        if (transition_flag == 1) {
            transition_flag = 0;
            load_buffer();
            transition_crossdissolve();
            //unload_buffer( );
        }


        if (data_to_process == 1) {
            process_Message();
        }


        if (U1STAbits.FERR == 1) {
            delay(100);
        }
        if (U1STAbits.PERR == 1) {
            delay(100);
        }
        if (U1STAbits.UTXBF == 1) {
            delay(100);
        }


    }

    return 0;
}
