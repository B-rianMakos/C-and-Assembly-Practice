/*--------------------------------------------
File: SegDisp.c
Description:  Segment Display Module
---------------------------------------------*/

#include <stdtypes.h>
#include "mc9s12dg256.h"
#include "SegDisp.h"
#include "Delay_asm.h"



/*--------------------------------------------
Fonction: initDisp

Initialise le matériel (port B et port P) branché aux afficheurs à 7-segments.
Il initialise aussi les afficheurs en blanc (aucun segment allumé)
---------------------------------------------*/
void initDisp(void){

    clearDisp();
    DDRB = 0xFF; //init PORTB to output
    DDRP = 0xFF; // init PORTP to output
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
    

}




/*--------------------------------------------
Fonction: segDisp
Une fonction qui met à jour les afficheurs pour une période de temps en
100 ms. Ceci permet de la fonction appelante de regagner le contrôle périodiquement pour lui
permettre de compléter d’autres tâches tel que la vérification du clavier
---------------------------------------------*/

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

/*--------------------------------------------
Fonction: clearDisp
 Cette fonction met les afficheurs en blanc
---------------------------------------------*/
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