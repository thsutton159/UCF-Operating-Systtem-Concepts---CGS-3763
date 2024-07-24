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
void memoryManagement();
void displayProcess(int allocation[], int processes, int processSize[]);
void firstFit(int blockSize[], int blocks, int processSize[], int processes);
void worstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void nextFit(int blockSize[], int blocks, int processSize[], int processes);

int main(){
    int choice = -1;
    
    while(choice != 0){
        choice = displayMenu();
        
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

void memoryManagement(){
    clearScreen();
    
    printf("        ********** Memory Management **********\n");
    
    for(int i=0; i<4; i++){
        int blockSize[5] = {80, 10, 65, 35, 70};
        int processSize[5] = {25, 70, 5, 45, 60};
        int blocks = 5;
        int processes = 5;
        
        int algorithm[] = {FIRST, BEST, WORST, NEXT};
        
        if(algorithm[i] == FIRST)
            firstFit(blockSize, blocks, processSize, processes);
        else if(algorithm[i] == BEST)
            bestFit(blockSize, blocks, processSize, processes);
        else if(algorithm[i] == WORST)
            worstFit(blockSize, blocks, processSize, processes);
        else if(algorithm[i] == NEXT)
            nextFit(blockSize, blocks, processSize, processes);
    }
}

void nextFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    int id = 0;
    
    memset(allocation, INVALID, sizeof(allocation));
    
    for(int i=0, i<processes, i++){
        while(id < blocks){
            if(blockSize[i] >= processSize[i]){
                allocation[i] = id;
                blockSize[id] -= processSize[i];
                break;
            }
            
            id = (id + 1) % blocks;
        }
    }
    
    printf("        ********** Operating Next Fit **********\n");
    
    displayProcess(allocation, processes, processSize);
    
}
        
void firstFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    
    memset(allocation, INVALID, sizeof(allocation));
    
    for(int i=0; i<processes; i++){
        while(int j=0; j<blocks; j++){
            if(blockSize[j] >= processSize[i]){
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    
    printf("        ********** First Fit **********\n");
    
    displayProcess(allocation, processes, processSize);
    
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    
    memset(allocation, INVALID, sizeof(allocation));
    
    for(int i=0; i<processes; i++){
        int bestIdx = INVALID;
        
        for(int j=0; j<blocks; j++){
            if(blockSize[j] >= processSize[i]){
                if(bestIdx == INVALID)
                    bestIdx = blockSize[j];
                else
                    bestIdx = blockSize[j];
            }
        }
        
        if(bestIdx != INVALID){
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    
    printf("        ********** Best Fit **********\n");
    
    displayProcess(allocation, processes, processSize);
    
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes){
    int allocation[processes];
    
    memset(allocation, INVALID, sizeof(allocation));
    
    for(int i=0; i<processes; i++){
        int wstIdx = INVALID;
        
        for(int j=0; j<blocks; j++){
            if(blockSize[j] >= processSize[i]){
                if(wstIdx == INVALID)
                    wstIdx = blockSize[j];
                else
                    wstIdx = blockSize[j];
            }
        }
        
        if(wstIdx != INVALID){
            allocation[i] wstIdx;
            blockSize[wstIdx] -= processSize[i];
        }
    }
    
    printf("        ********** Worst Fit **********\n");
    
    displayProcess(allocation, processes, processSize);
    
}

void displayProcess(int allocation[], int processes, int processSize){
    
    for(int i=0; i<processes; i++){
        printf("%d  ", i+1);
        printf("%d  ", processSize[i]);
        
        if(processSize[i] == INVALID)
            printf("Not Allocated");
        else
            printf("%D", allocation[i]);
    }
}