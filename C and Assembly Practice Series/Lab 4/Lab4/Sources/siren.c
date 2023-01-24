#include "mc9s12dg256.h"
#include "delay.h"
#include "siren.h"
#define Interval (ONETENTH_MS * 500)


/*--------------------------
Function: initLCD
Parameters: None.
Returns: void
Description: fonction qui initialise le matériel pour réaliser la sirène.
---------------------------*/
void initSiren()
{
   TIOS_IOS5 = 1;  // On met TC5 en output-compare
}

/*--------------------------
Function: turnOnSiren
Parameters: None.
Returns: void
Description: Cette fonction active la sirène, c’est-à-dire le haut-parleur PC. Ceci est atteint en 
générant une onde sur la broche du canal 5 de la minuterie. 
---------------------------*/
void turnOnSiren()
{
   TCTL1_OM5 = 1; // Sets high sur pin 5 lors du output-compare  
   TCTL1_OL5 = 1; // Crée un évenement sur TCS (Ex: low sur pin 5)
   CFORC_FOC5 = 1; 
  
  
   TCTL1_OL5 = 1;
   TCTL1_OM5 =; 
   TC5 = TCNT + Interval;
   TIE_C5I = 1;  // permet interuption.
}


/*--------------------------
Function: turnOffSiren
Parameters: None.
Returns: void
Description: Cette fonction désactive la sirène. Ceci est atteint en enlevant l’onde de la broche
du canal 5 de la minuterie. 
---------------------------*/

void turnOffSiren()
{
   TIE_C5I = 0;  // enlève interuption.
   TCTL1_OM5 = 1; 
   TCTL1_OL5 = 0; // met un low sur pin 5 lors de l'output-compare 
   CFORC_FOC5 = 1; // crée un évement sur TC5 (i.e low on pin 5)
}

