#include<stdio.h>
#include<conio.h>
void main()
{
    int h=0,m=0,s=0,i;
    printf("enter a time formate in HH:MM:SS\n");
    start:
    for(h=0;h<24;h++)
    {
      for(m=0;m<60;m++) 
      {
       for(s=0;s<60;s++)    
       {
	       clrscr();
           printf("%d:%d:%d",h,m,s);
           if(h<12)
           printf("AM");
           else
           printf("PM");
           for(double i=0;i<3619999;i++)
           i++;
           i--;
       }
       s=0;
      }
      m=0;
    }
    h=0;
    goto start;
	getch();
}
