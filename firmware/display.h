

#ifndef DISPLAY_H
#define	DISPLAY_H


// Define PWM output register associations
#define	RED_DC      OC2RS
#define	GREEN_DC    OC3RS
#define	ANODE_DC    OC4RS



void display(void);
void update_number();

void load_buffer(void);
void rotate_right(void);
void rotate_left(void);
void rotate_180(void);
void unload_buffer(void);


#endif	/* DISPLAY_H */
