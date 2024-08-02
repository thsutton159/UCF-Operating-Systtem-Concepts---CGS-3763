int i,j;
int buffer[5];

semaphore full;
semaphore mutex;
semaphore empty;

void Producer(){
	int y = 0;
	int k = 0;
	for(i=1;i<=20;i++){
		y++;
		cout << "Item " << i << " produced" << endl;
		p(full);
		p(mutex);
		buffer[k] = y;
		k++;
		if(k == 5) k = 0;
		v(mutex);
		v(empty);
	}
}

void Consumer(){
	int a = 0;
	int x = 0;
	for(j=1;j<=20;j++){
		x++;
		p(empty);
		p(mutex);
		buffer[a] = x;
		a++;
		if(a == 5) a = 0;
		v(mutex);
		v(full);
		// output
		cout << "Item " << j << " consumed" << endl;
	}
}

main(){
	initialsem(full, 5);
	initialsem(mutex, 1);
	initialsem(empty, 0);

	cobegin {
		Producer();
		Consumer();
		}

}