

#include <stdio.h>

#include <string.h>


void print(char *str);


struct B {
    int x;
    int y;
    int (*addB)(struct B *sVar);

    int (*iiaddB)(int a, int b);


}

int addB(struct B *sVar){
        int z;
        z = sVar->x + sVar->y;
        return z;	    }

int iiaddB (int a, int b){
        int c;
        c = a + b;
        return c;
    }

void Bconstructor(struct B *sVar){
    sVar->addB = addB;
    sVar->iiaddB = iiaddB;
}




void print(char *str){
    printf("%s",str);

}


struct B myB1;


int main (int argc, char *argv){
    int a = 1;
    int b = 2;
        struct B myB2;
    Bconstructor(&myB2);

        myB2.x = 3;
    myB2.y = 4;
    int sum = myB2.add(a,b);
    printf("%d\n",sum);
    sum = myB2.add();
    printf("%d\n",sum);
        return 0;    
}

