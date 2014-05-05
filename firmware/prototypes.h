
#ifndef __PROTOTYPES_H
#define __PROTOTYPES_H

// internal 8MHz w/ 4x PLL - clock cycle is 1/2 in freq.
#define Fcy         (8e6*4)/2
#define START_FLAG  240
#define STOP_FLAG   247

#define showsec
#define showsec_bkwrd


void send_data(short);


#endif

