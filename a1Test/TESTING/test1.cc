
#include<stdio.h>

#include<stdlib.h>



struct A {
   int a;

};

void Aconstructor(struct A *sVar){
}

;



/* reference a class variable */
int main(int argc, char *argv[]) {

struct A myA;
    Aconstructor(&myA);

   myA.a = 3;
   if (myA.a == 3)
      return(0);
   else
      return(1);

}

