

#include<stdio.h>
#include<stdlib.h>
 
main()
{
    int i;
printf("This c program will exit in 10 seconds.\n");        
 
//    delay(10000);                         
for(i=10;i>0;i--)
{
printf("%d \n",i);
sleep(1);
}
printf("\n");
    return 0;
}
