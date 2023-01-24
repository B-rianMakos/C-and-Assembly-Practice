/*
Description : Ce fichier C contient le code pour les fonction de display
              Ces fonctions sont : 
              initLCD(void)
              void printLCDStr(char *, byte)
                            
*/


//
#include "alarm.h" //lignes de code pour inclure les fichier necessaire
#include "lcd_asm.h"// pour le bonne fonctionnement du code 

/*
Fonction : initLCD      Parametre : Aucun       Return : Aucun

Cette fonction initialize le materiel LCD avec une fonction present fans LCD.ASM .  
*/
void initLCD(void){
    lcd_init();
}


/*
Fonction : printLCDString 
Parametres : 
           1. str 
            Ce parametre est le "string" qui sera afficer sur le LCD 
           2. linenumb
            Ce parametre est soit 0 (premier ligne du afficheur LCD) ou 1 
            (deuxieme ligne du afficheur LCD). Ill sera utiliser pour choisir
            la ligne sur laquelle imprimer le 'string'
Return  : Aucun
                  
*/
void printLCDString(char *str,byte linenumb){

    if(linenumb ==0){
        set_lcd_adresse(0x00); //address de ligne 0
        type_lcd(str); // imprime le string voulu sur le LCD
    }
    
     if(linenumb ==1){
        set_lcd_adresse(0x40); //address de ligne 1
        type_lcd(str); // imprime le string voulu sur le LCD
    }
}