/* Thomas Sutton
 * CGS 3763
 * Assignment 3 Project Set Up
 * Karin Markle
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const EXIT = 0;
const INVALID = -1;
const MEMORY = 1;
const FILES = 2;
const THREAD = 3;
const FIRST = 0;
const BEST = 1;
const WORST= 2;
const NEXT = 3;

int displayMenu();
void clearScreen();

int main(){
    int choice = -1;
    
    while(choice != 0){
        choice = displauMenu();
        
        if(choice == 1){
            memoryManagement();
        }
        
        if(choice == 2){
            fileManagement();
        }
        
        if(choice == 3){
            multiThreads();
        }
        else{
            exit(0);
        }
    }
    
    return 0;
}

int displayMenu(){
    int choice = -1;
    
    printf("        ********** Operating System Management Menu **********\n");
    
    while(choice == -1){
        printf("Select the OS program to run; enter the number of your selection\n");
        printf("1. Memory Management"\n);
        printf("2. File Management\n");
        printf("3. Multithreading\n");
        printf("0. Exit\n");
        
        scanf("%d", &choice);
        
        if((choice >= 0) && (choice <= 3)){
            return choice;
        }
        else{
            choice = -1;
        }
    }
}

void clearScreen(){
    char input;
    
    printf("Hit/press the 'enter' key\n");
    scanf("%c", &input);
    
    system ("cls");
    //system ("clear");
    
}