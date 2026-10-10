#include<iostream>
#include<thread>

using namespace std;
logger(){
cout<<"child executing with unique thread ID";
}
int main(){
	thread t (logger);
	t.detach();
	return 0;
}