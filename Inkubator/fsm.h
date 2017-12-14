/* 
 * File:   fsm.h
 * Author: Gunawan Marbun
 *
 * Created on September 28, 2017
 */

#ifndef FSM_H
#define  FSM_H

#define DATA_KEEP 0
#define TIME_KEEP 1
#define TIME_SET_DAY1 2
#define TIME_SET_DAY2 3
#define TIME_SET_HOUR1 4
#define TIME_SET_HOUR2 5
#define TIME_SET_MIN1 6
#define TIME_SET_MIN2 7
#define TIME_SET_SEC1 8
#define TIME_SET_SEC2 9
#define MODE_OFF 10
#define MODE_ON 11
#define SET_OFF 12
#define SET_ON 13
#define TIMEOUT 30


void fsm(int Mode_Evt, int Set_Evt, 
		 int *DAY_digit1, int *DAY_digit2, int *HOUR_digit1, int *HOUR_digit2, int *MIN_digit1, int *MIN_digit2,
		 int *SEC_digit1, int *SEC_digit2, int *state);
void detectmodeevent(int pushMode,int *Mode_Evt,int *statemodeeevent);
void detectsetevent(int pushSet,int *Set_Evt,int *statseteevent);
#endif  /* FSM_H */
