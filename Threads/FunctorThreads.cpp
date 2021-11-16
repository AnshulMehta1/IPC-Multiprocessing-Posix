class Base{
public:
	void operator ()(int x){
		while (x-->0){
			cout<<x<<endl;
		}

	}
}

int main(){
	std::thread t1((Base()),99);
	t1.join();
	return 0;

}
