
#include <stdio.h>

#include <string.h>


struct B{
    int x;
    int y;
    int (*iiaddB)(int a,int b);

    int (*addB)(struct B *sVar);


}

int iiaddB(int a,int b){
    return a + b;
    }

int addB(struct B *sVar){
    return sVar->x+sVar->y;
    }

void Bconstructor(struct B *sVar){
    sVar->iiaddB = iiaddB;
    sVar->addB = addB;
}





int main(){

    int a,b;
    a = 1;
    b = 2;
        struct B myB;
    Bconstructor(&myB);

        myB.x = 3;
    myB.y = 4;
        int sum = myB.addB(struct B *sVar);
    sum = myB.iiaddB(a,b);
	return 0;

}
