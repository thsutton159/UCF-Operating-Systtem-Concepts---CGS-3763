const int bufferSize = 5;
const int loopAmount = 25;

semaphore FULL1, FULL2, FULL3;
semaphore MUTEX1, MUTEX2, MUTEX3;
semaphore PRINT;
semaphore PIO, SIO;
semaphore operationComplete;
semaphore requestPending;
semaphore requestService[bufferSize];

int IORQid[bufferSize];
int IORQaddr[bufferSize];
int bufferAddress = 0, bufferID = 0, track = 0;

void User (int userID){
int i, j, address = 0;

for(j = 0; j < bufferSize; j++){

    address = random(i+1) % 200;
    p(FULL1);
    p(MUTEX1);
    
    bufferID = userID;
    bufferAddress = address;
    
    p(PRINT);
    cout << "User " << userID + 1 << " executes system call SIO or DOIO" << endl;
    v(PRINT);
    v(MUTEX1);
    v(SIO);
    p(requestService[userID]);
    }
}

void DOIO(){

int i = 0, tempID, tempAddr, index;
for (index = 0; index < loopAmount; index++){

    p(SIO);
    p(MUTEX1);
    
    tempID = bufferID;
    tempAddr = bufferAddress;
    
    v(MUTEX1);
    v(FULL1);
    p(FULL2);
    p(MUTEX2);
    
    IORQid[i] = tempID;
    IORQaddr[i] = tempAddr;
    i = (i+1) % 5;
    
    p(PRINT);
    cout << "DOIO assembles IORB for user " << tempID + 1 << " and inserts it in IORQ" << endl;
    v(PRINT);
    v(MUTEX2);
    v(requestPending);
    }
}

void DeviceDriver(){
int j = 0, driverAddress = 0, driverID = 0, i;
for (i = 0; i < loopAmount; i++){
    
    p(requestPending);
    p(MUTEX2);
    
    driverID = IORQid[j];
    driverAddress = IORQaddr[j];
    j = (j+1) % 5;
    
    v(MUTEX2);
    v(FULL2);
    p(FULL3);
    p(MUTEX3);
    
    track = driverAddress;
    
    v(MUTEX3);
    v(PIO);
    p(PRINT);
    
    cout << "Driver initiates I/O operation for user " << driverID + 1<< endl;
    
    v(PRINT);
    p(operationComplete);
    v(requestService[driverID]);
    p(PRINT);
    
    cout << "Driver signal user " << driverID + 1 <<" to informed that I/O request is served."<< endl;
    
    v(PRINT);
    }
}

void Disk(){
int i = 0, seek = 0, diskAddress = 0, j;
for (j = 0; j < loopAmount; j++){
    
    p(PIO);
    p(MUTEX3);
    
    seek = track;
    
    v(MUTEX3);
    diskAddress = seek * 20;
    
    for (i = 1; i <= diskAddress; i++){}
    
    v(operationComplete);
    p(PRINT);
    cout << "Disk signal driver(operation complete)" << endl;
    v(PRINT);
    v(FULL3);
    }
}

main () {
initialsem (MUTEX1, 1);
initialsem (MUTEX2, 1);
initialsem (MUTEX3, 1);

initialsem (PRINT,1);
    
initialsem (FULL1, 1);
initialsem (FULL2, 5);
initialsem (FULL3, 1);

initialsem (SIO, 0);

initialsem (PIO, 0);

initialsem (requestPending, 0);
    
initialsem (operationComplete, 0);

initialsem (requestService[0], 0);
initialsem (requestService[1], 0);
initialsem (requestService[2], 0);
initialsem (requestService[3], 0);
initialsem (requestService[4], 0);
    
cobegin{
    User(0);
    User(1);
    User(2);
    User(3);
    User(4);
    DOIO();
    DeviceDriver();
    Disk();
    }

}