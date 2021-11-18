int x=0;
int y=0;
void doSomeWork(int seconds){
std::this_thread::sleep_for(std::chrono::seconds(seconds));
	
}
void incxy(int& xory, std::mutex& const *char desc){
	for (int i=0;i<5;i++){
		m.lock();
			xory++;
		cout<<desc<<xory<<'\n';
		m.unlock();
		doSomeWork(1);
}

}

void consumerxy(){
	int useCount=0;
	int xplusy=0;
	while(1){
		int lockResult=std::try_lock(m1,m2);
		if(lockResult==-1){
			if(x!=0 && y!=0){

				useCount--;
				xplusy+=x+y;
				x=0;
				y=0;
				cout<<"xplusy"<<xplusy<<'\n';

			}
		  	m1.unlock();
		  	m2.unlock();
			if(useCount==0){
				break;
			}
			
		}

	}

}
