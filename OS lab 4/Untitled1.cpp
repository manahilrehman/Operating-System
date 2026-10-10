#include<iostream>
#include<thread>

using namespace std;
child_routine(){
	cout<<"child executing with unique thread ID";
	
}
int main(){
	thread t (child_routine);
	t.join();
	return 0;
}