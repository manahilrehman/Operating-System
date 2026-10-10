#include<iostream>
#include<jthread>

using namespace std;
jtworker_fn(){
cout<<"child executing with unique thread ID";
}
int main(){
	thread t (logger);
	t.detach();
	return 0;
}