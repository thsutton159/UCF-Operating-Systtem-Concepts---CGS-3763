/* Thomas Sutton
 * CGS 3763
 * Assignment 5 Page Replacement
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
//new constants for assignment 5
const PAGE = 4;
const FIFO = 0;
const LRU = 1;
const FRAMES = 3;

int displayMenu();
void clearScreen();
void memoryManagement();
void displayProcess(int allocation[], int processes, int processSize[]);
void firstFit(int blockSize[], int blocks, int processSize[], int processes);
void worstFit(int blockSize[], int blocks, int processSize[], int processes);
void bestFit(int blockSize[], int blocks, int processSize[], int processes);
void nextFit(int blockSize[], int blocks, int processSize[], int processes);
//newly added function prototypes
void pageReplacement();
void lru();
int findLRU();
void fifo();
void displayPages(int page, int allocation[]);

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
        
        if(choice == 4){
            pageReplacement();
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
        printf("4. Page Replacement\n");
        printf("0. Exit\n");
        
        scanf("%d", &choice);
        
        if((choice >= 0) && (choice <= 4)){
            //choice must be between an inclusive range of 0 to 4
            return choice;
        }
        else{
            //if the user's input exceeds this range the variable is reset
            choice = -1;
            //the loop will continue
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
        
        if(algorithm[i] == FIRST){
            //call firstFit function
            firstFit(blockSize, blocks, processSize, processes);
        }
        else if(algorithm[i] == BEST){
            //call bestFit function
            bestFit(blockSize, blocks, processSize, processes);
        }
        else if(algorithm[i] == WORST){
            //call worstFit function
            worstFit(blockSize, blocks, processSize, processes);
        }
        else if(algorithm[i] == NEXT){
            //call nestFit function
            nextFit(blockSize, blocks, processSize, processes);
        }
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
                    bestIdx = blockSize[j];//if bestIdx is invalid, sets new bestIdx
                else
                    bestIdx = blockSize[j];//sets new bestIdx
            }
        }
        
        if(bestIdx != INVALID){
            allocation[i] = bestIdx;//sets the allocation of position i to bestIdx
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

void displayProcess(int allocation[], int processes, int processSize[]){
    
    for(int i=0; i<processes; i++){
        printf("%d  ", i+1);
        //prints the process the looping structure is on
        //the +1 modifier is so that the process number is accurate
        
        printf("%d  ", processSize[i]);
        //prints the size of the process slotted in position i
        
        if(processSize[i] == INVALID)
            printf("Not Allocated");
        else
            printf("%d", allocation[i]);//prints process allocation to console
    }
}

void pageReplacement(){
    clearScreen();
    
    for(int i=0; i<2; i++){
        
        if(i == FIFO)
            fifo(); //calls fifo function when i = 0
        
        if(i == LRU)
            lru(); //calls lru when i = 1
    }
}

void fifo(){
    
}

void lru(){
    
}

void displayPages(int page, int allocation[]){
    printf("%d", page); //prints page number to console
    
    for(int i = 0; i<FRAMES; i++){
        if(allocation[i] == INVALID)
            printf("-");//prints dash to console to represent invalid allocation
        else
            printf("%d", allocation[i]);//prints allocation to console
    }
}