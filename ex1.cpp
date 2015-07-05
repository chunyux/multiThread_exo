/* Ex 1 

Son thread prints 10 times, then the parent thread 100 times; son thread 10 times, parent thread 100 times; 50 times of such loop

*/

#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <string>

std::mutex mu;

const int nTime = 50;


void shared_print(std::string msg, int id){
	std::cout << msg << id << std::endl;
}


void thread_test_fun1(){
	std::lock_guard<std::mutex> myLock(mu);
	for (int i = 0; i < 10; i++){
		shared_print("from t1: ",i);
	}
}


int main(){

		
	for (int jj = 0; jj < nTime; jj++){
		std::thread t1(thread_test_fun1);
		
		std::lock_guard<std::mutex> mL(mu);
		for (int j = 0; j < 100; j++){
			shared_print("from main: ", j);
		}

		t1.join();
	}
	getchar();
	return 1;
}

