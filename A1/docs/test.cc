#include <stdio.h>
#include <string.h>

class B{
    int x;
    int y;
    int add(int a,int b){
    return a + b;
    }
    int add(){
    return x+y;
    }
}


int main(){

    int a,b;
    a = 1;
    b = 2;
    
    class B myB;
    
    myB.x = 3;
    myB.y = 4;
    
    int sum = myB.add();
    sum = myB.add(a,b);
	return 0;
}