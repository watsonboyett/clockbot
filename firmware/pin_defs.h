

#ifndef PIN_DEFS_H
#define	PIN_DEFS_H

// RA2 = pin 9(osci)
// RA3 = pin 10(osco)
// RB5 = pin 14
// RB6 = pin 15
// RB4 = pin 11(sosci)
// RA4 = pin 12(sosco)

#define HEARTBEAT       PORTBbits.RB13

#define OE_GREEN	PORTBbits.RB15	// RB15 = pin 26
#define OE_RED		PORTBbits.RB12	// RB12 = pin 23
#define OE_ANODE	PORTBbits.RB10	// RB10 = pin 21

#define MCLR		PORTBbits.RB14	// RB14 = pin 25
#define DATA		PORTBbits.RB13	// RB13 = pin 24
#define STORE		PORTBbits.RB11	// RB11 = pin 22

#define CLK_ANODE	PORTBbits.RB9	// RB9 = pin 18
#define CLK_LEFT_RED	PORTBbits.RB2	// RB2 = pin 6
#define CLK_LEFT_GREEN	PORTBbits.RB3	// RB3 = pin 7
#define CLK_RIGHT_RED	PORTAbits.RA0	// RA0 = pin 2
#define CLK_RIGHT_GREEN	PORTAbits.RA1	// RA1 = pin 3

#define IN_LEFT		PORTBbits.RB8	// RB8 = pin 17
#define IN_RIGHT	PORTBbits.RB7	// RB7 = pin 16

#define PGD		PORTBbits.RB0	// RB0 = pin 4
#define PGC		PORTBbits.RB1	// RB1 = pin 5


#endif	/* PIN_DEFS_H */
