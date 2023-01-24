/*--------------------------------------------
Fichier: thermistor.c
Description:  Thermistor Module
---------------------------------------------*/

#include "mc9s12dg256.h"
#include "thermistor.h"
#include "delay.h"

#define delai_ 7500; //delai 10ms 



/*-------------------------------------------------
Fonction: initThermistor
Description: Cette fonction configure un canal de la minuterie pour générer 
une séquence d’interruption pour permettre à tous les 100 ms l’initiation de la conversion du 
signal de température sur le ATD. Il initialise aussi le périphérique ATD pour convertie le signal de température 
reçu de la thermistance à une valeur de 10 bits et générer une interruption lorsque la conversion 
est complétée.
---------------------------------------------------*/
void initThermistor(void) {
  // Sets up the ATD

ATD0CTL2 = 0xC2; //permet une interruption, ADC on et clear on
for (i=120, i>0, i--); // crée un delai de 20ms

ATD0CTL3 = 0x08; 
ATD0CTL4 = 0x77; 
ATD0CTL5 = 0x85; // commence conversion à pin 05
  
  
TIOS_IOS3 = 1; //active channel 3
TIE |= 0b00001000; //permet interrupt sur TC3
TC3 = TCNT + ATD_TIMEOUT; // permet un delai sur channel 3 
}

/*-------------------------------------------------
Fonction: getTemp(void)
Description: Cette fonction lit la valeur de conversion de 10 bits retrouvée dans une 
variable de conversion (voir les ISRs ci-dessous) et la traduit à une valeur entière entre 000 et 
700 qui représente les 10ième de degrés (i.e. entre 00.0 oC et 70.0 oC). Cette valeur traduite est 
retournée.
---------------------------------------------------*/
int getTemp(void) {
  return (hold / 2.048) * 10;
}

/*-------------------------------------------------
Interrupt: atdd_isr
Description: exécuté à la fin d’une conversion et met à jour la variable de 
conversion (un emplacement de 16-bits en mémoire) avec la valeur de conversion de 10 bits 
présent dans l’ATD.

---------------------------------------------------*/
void interrupt VectorNumber_Vatd0 atdread_isr(void) {
  hold = ATD0DR0;
}




/*-------------------------------------------------
Interrupt: atdt_isr
Description: démarre la conversion de l’ATD qui devra être configuré pour faire 
une seule conversion du signal de la broche PAD05.
---------------------------------------------------*/
void interrupt VectorNumber_Vtimch3 atdtimer_isr(void)
{
  static byte temp = 10;  //reassign 10 à temp lorsque la fonction est utiliser à nouveau
  
  
  if (temp > 0) {
    temp--;
  } else {
    ATD0CTL5 = 0x85; // commence conversion à pin 05
    temp = 10;  // reassign 10 à temp
  }
  
	
	TC3 = TC3 + ATD_TIMEOUT; //prépare la prochaine interuuption et le vide
}














































