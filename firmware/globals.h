

#ifndef __GLOBALS_H
#define __GLOBALS_H

/*---------------------------------------------------------------------------*/

typedef enum {
    clock_1,
    clock_2,
    clock_3,
    monk_1,
    monk_2,
    monk_4,
    counter_1,
    counter_2,
    counter_3,
    watch,
    belt_1,
    belt_2,
    glasses
} model_t;

extern model_t model;

// declare some external global variables
extern short hours;
extern short hours_ones;
extern short hours_tens;
extern short minutes;
extern short minutes_ones;
extern short minutes_tens;
extern short seconds;
extern short seconds_ones;
extern short seconds_tens;

extern unsigned int countVar;
extern unsigned int countVarLeft;
extern unsigned int countVarRight;
/*---------------------------------------------------------------------------*/

extern short col;
extern short row;

extern signed short cal;
extern short d;
extern short transition_flag;
extern const short faderate;
extern short faderate_buf;
extern unsigned short globi;
extern char dir;
extern char offset;
extern short loop;
extern const short fadelevels;
extern short fadepos;
extern const short crossrate;
extern short crossratebuf;

extern const short PERIOD;

/*---------------------------------------------------------------------------*/

extern short data_to_process;
void process_Message(void);

/*---------------------------------------------------------------------------*/

extern unsigned long dots[24];

extern unsigned char *left_ptr;
extern unsigned char left[8];

extern unsigned char *leftbuf_ptr;
extern unsigned char leftbuf[8];

extern unsigned char *right_ptr;
extern unsigned char right[8];

extern unsigned char *rightbuf_ptr;
extern unsigned char rightbuf[8];

extern unsigned char *anode_ptr;
extern unsigned char anode[8];

extern unsigned char *anodebuf_ptr;
extern unsigned char anodebuf[8];

extern const unsigned char *left_tens_ptr;
extern const unsigned char *left_ones_ptr;
extern const unsigned char *right_tens_ptr;
extern const unsigned char *right_ones_ptr;

extern const unsigned char *numbers[11];
extern const unsigned char *faces[10];
extern const unsigned char *sprites[7];
//extern const unsigned char *letters[11];

extern unsigned char face;
extern const unsigned char *faceOne_ptr;
extern const unsigned char *faceTwo_ptr;

/*---------------------------------------------------------------------------*/

#endif	/* __GLOBALS_H__ */
