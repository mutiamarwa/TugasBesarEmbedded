#include "fsm.h"

/**
 * implementasi finite state machine dengan software
 * @param push push dari switch, active high
 * @param output output LED, active high
 * @param state state internal FSM. belum didefinisikan
 * @param digit merupaka digit seven segment mulai dari kanan ke kiri
 */
void fsm(int Mode_Evt, int Set_Evt, 
		 int *DAY_digit1, int *DAY_digit2, int *HOUR_digit1, int *HOUR_digit2, int *MIN_digit1, int *MIN_digit2,
		 int *SEC_digit1, int *SEC_digit2, int *state) {
  
  static int counter = 0;
  
	switch (*state){
		case DATA_KEEP:
		{
		if (Mode_Evt==1){
			*state = TIME_KEEP;
			counter=0;
		} 
		if (Set_Evt==1){
			*state = TIME_SET_DAY1;
		}
      break;
    }
		case TIME_KEEP:
		{
		if ((Mode_Evt==0)&&(Set_Evt==0)) {
        *state = TIME_KEEP;
        counter++;
         if (counter >= TIMEOUT) {
            *state = DATA_KEEP;
        }
       }
      if (Mode_Evt==1){
        *state = DATA_KEEP;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_DAY1;
      }
      break;
    }
	case TIME_SET_DAY1:
		{
      if (Mode_Evt==1){
        if (*DAY_digit1>=9){
          *DAY_digit1=0;
        }else{
          (*DAY_digit1)++;
        }
        *state = TIME_SET_DAY1;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_DAY2;
      }
      break;
    }
	case TIME_SET_DAY2:
		{
      if (Mode_Evt==1){
        if (*DAY_digit2>=9){
          *DAY_digit2=0;
        }else{
          (*DAY_digit2)++;
        }
        *state = TIME_SET_DAY2;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_HOUR1;
      }
      break;
    }
		case TIME_SET_HOUR1:
		{
      if (Mode_Evt==1){
        if (*HOUR_digit1>=2){
          *HOUR_digit1=0;
        }else{
          (*HOUR_digit1)++;
        }
        *state = TIME_SET_HOUR1;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_HOUR2;
      }
      break;
    }
		case TIME_SET_HOUR2:
		{
			if (Mode_Evt==1){
        if ((*HOUR_digit1==2)&&(*HOUR_digit2>=4)){
          *HOUR_digit2=0;
        } else if ((*HOUR_digit1!=2)&&(*HOUR_digit2>=9)){
          *HOUR_digit2=0;
        }else{
          (*HOUR_digit2)++;
        }
        *state = TIME_SET_HOUR2;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_MIN1;
      }
      break;
    }
		case TIME_SET_MIN1:
		{
			if (Mode_Evt==1){
        if (*MIN_digit1>=5){
          *MIN_digit1=0;
        } else {
          (*MIN_digit1)++;
        }
        *state = TIME_SET_MIN1;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_MIN2;
      }
      break;
    }
		case TIME_SET_MIN2: 
		{
			if (Mode_Evt==1){
        if (*MIN_digit2>=9){
          *MIN_digit2=0;
        } else {
          (*MIN_digit2)++;
        }
        *state = TIME_SET_MIN2;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_SEC1;
      }
      break;
    }
		case TIME_SET_SEC1:
		{
			if (Mode_Evt==1){
        if (*SEC_digit1>=5){
          *SEC_digit1=0;
        } else {
          (*SEC_digit1)++;
        }
        *state = TIME_SET_SEC1;
      } 
      if (Set_Evt==1){
        *state = TIME_SET_SEC2;
      }
      break;
    }
		case TIME_SET_SEC2:
		{
			if (Mode_Evt==1){
        if (*SEC_digit2==9){
          *SEC_digit2=0;
        } else {
          (*SEC_digit2)++;
        }
        *state = TIME_SET_SEC2;
      } 
      if (Set_Evt==1){
        *state = TIME_KEEP;
      }
      break;
    }
   default:
   {

   }
}
}

void detectmodeevent(int pushMode,int *Mode_Evt,int *statemodeevent){
  switch (*statemodeevent){
    case MODE_OFF:
    {
      if (pushMode==1){
        *Mode_Evt=1;
        *statemodeevent = MODE_ON;
      } 
      if (pushMode==0){
        *statemodeevent = MODE_OFF;
      } 
      break;
    }
   case MODE_ON:
   {
      if (pushMode==0){
		*Mode_Evt=0;
        *statemodeevent = MODE_OFF;
      } 
      if (pushMode==1){
        *statemodeevent = MODE_ON;
      } 
      break;
   }
  }
}

void detectsetevent(int pushSet,int *Set_Evt,int *statesetevent){
  switch (*statesetevent){
    case SET_OFF:
    {
      if (pushSet==1){
        *Set_Evt=1;
        *statesetevent = SET_ON;
      }
      if (pushSet==0){
        *statesetevent = SET_OFF;
      } 
      break;
    }
   case SET_ON:
   {
      if (pushSet==0){
		*Set_Evt=0;
        *statesetevent = SET_OFF;
      } 
      if (pushSet==1){
        *statesetevent = SET_ON;
      } 
      break;
   }
  }
}