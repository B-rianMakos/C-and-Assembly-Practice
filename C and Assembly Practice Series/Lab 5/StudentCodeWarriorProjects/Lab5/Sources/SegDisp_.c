#include "mc9s12dg256.h"
#include "SegDisp.h"

#define Nouveau_Interval (ONETENTH_MS * 10)
#define NumeroDisplay 4
#define espace ""
#define DelayDisplay 3750

byte codes[NumeroDisplay];  //tous les codes ascii des affichage

struct ascii_to_code 
{
   byte ascii;
   byte code;  
}; 

#define NumerosDispTb1 18
struct tranforme_ASCII_a_code dispTb1[NumerosDispTb1] =
{          
    { '0',0b00111111 },
    { '1',0b00000110 },
    { '2',0b01011011 },
    { '3',0b01001111 },
    { '4',0b01100110 },
    { '5',0b01101101 },
    { '6',0b01111101 },
    { '7',0b00000111 },
    { '8',0b01111111 },
    { '9',0b01101111 },
    { '*',0b01000110 },
    { '#',0b01110000 },
    { 'a',0b01110111 },
    { 'b',0b01111100 },
    { 'c',0b00111001 },
    { 'd',0b01011110 },
    { 'e',0b01111001 },
    { ' ',0b00000000 } 
};

byte enableCodes[NumeroDisplay]= {  
     0b00001110,	
     0b00001101,
     0b00001011,	
     0b00000111	  
};
/*--------------------------------------------
Fonction: initDisp

Initialise le matériel (port B et port P) branché aux afficheurs à 7-segments.
Il initialise aussi les afficheurs en blanc (aucun segment allumé)
---------------------------------------------*/

void initDisp(void){


    DDRB = 0xFF; //init PORTB to output
    DDRP = 0xFF; // init PORTP to output
    PTP = 0x0F;
    clearDisp();

    TIOS_IOS1 |= 0b00000010; //TC1 = output-compare
    TIE_C1I |= 0b00000010; //permet une interuuption sur channel 1
    TC1 = TCNT + DelayDisplay; 
}




/*--------------------------------------------
Fonction: setCharDisplay

Une fonction qui ajoute un caractère (identifier avec son
code ASCII) à afficher. Réservez 4 octets en mémoire (un tableau) pour contenir soit des caractères ou
codes pour afficher les caractères sur les afficheurs correspondants. Lorsque la fonction est appelée,
deux arguments sont fournies, le caractère à afficher (premier argument) et un numéro d’afficheur
(débute à 0) pour indiquer sur lequel des afficheurs le caractère doit apparaitre. 
---------------------------------------------*/

void setCharDisplay(char cha, byte numdisp){

    byte check = 0x00;

    if (cha=='0'){
        check = 0x3F;
    }
    else if (cha == '1'){
        check = 0x06;
    }
    else if (cha == '2'){
        check = 0x5B;
    }
    else if (cha == '3'){
        check = 0x4F;
    }
    else if (cha == '4'){
        check = 0x66;
    }
    else if (cha == '5'){
        check = 0x6D;
    }
    else if (cha == '6'){
        check = 0x7D;
    }
    else if (cha == '7'){
        check = 0x07;
    }
    else if (cha == '8'){
        check = 0x7F;
    }
    else if (cha == '9'){
        check = 0x6F;
    }
    else if (cha == 'a'){
        check = 0x77;
    }
    else if (cha == 'b'){
        check = 0x7D;
    }
    else if (cha == 'c'){
        check = 0x39;
    }
    else if (cha == 'd'){
        check = 0x5E;
    }
    else if (cha == '#'){
        check = 0x70;
    }
    else if (cha == '*'){
        check = 0x46;
    }

    digit[numDisp] = check;

    void interrupt VectorNumber_Vtimch1 premierCounteur(void) {
      static byte numero = 0;
      PTP = 0xF0;
      PORTB = check;
      dNum++;
      dNum = dNum%NumeroDisplay;
     
     


    TC1 = (TC1 + Nouveau_Interval);

/*--------------------------------------------
Fonction: segDisp
Une fonction qui met à jour les afficheurs pour une période de temps en
100 ms. Ceci permet de la fonction appelante de regagner le contrôle périodiquement pour lui
permettre de compléter d’autres tâches tel que la vérification du clavier
---------------------------------------------*/

/*
void segDisp(void){
    int a,b;

    for (a = 0; a < 5; a++)
    {
        for(b  = 0; b < 4; b++)
        {
            PTP = PTPDir[b];
			PORTB = digit[b];
			delayms(5);
        } 
    }
}
*/


/*--------------------------------------------
Fonction: clearDisp
 Cette fonction met les afficheurs en blanc
---------------------------------------------*/
}

void clearDisp(void){
    PTP = 0x0e;
    PORTD = 0;
    PTP = 0x0d;
    PORTD = 0;
    PTP = 0x0b;
    PORTD = 0;
    PTP = 0x0e;
    PORTD = 0;

}

/*--------------------------------------------
 Fonction : getCode
 transforme code character ASCII en code pour le afficheur 7 segment.
--------------------------------------------*/ 
byte getCode(byte ch){
    byte = x;
    byte code =0; //null pour commencer
    for(x = 0; i < NumerosDispTb1; x++)
        if(ch == dispTb1[x].ascii)
            code = dispTb1[x].code;
    return code;
}


/*--------------------------------------------
 Fonction : turnOnDp
 Cette fonction allume le point decimal de l'afficheur identifié par dNum
--------------------------------------------*/ 
void turnOffDP(int dNum){
    code[dNum] = code[dNum] & 0x80; //allume point decimal et clears le 7ieme bit
}

/*--------------------------------------------
 Fonction : turnOnDp
 Cette fonction eteint le point decimal de l'afficheur identifié par dNum
--------------------------------------------*/ 
void turnOffDP(int dNum){
    code[dNum] = code[dNum] & 0x7f; //allume point decimal et clears le 7ieme bit
}


