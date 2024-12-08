typedef struct 
         {
	       int day,month,yeear;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024};
			 printf("%c%d%f%f%f%d%d%c%d%d%d%d",st.name,st.rollno,st.marks,st.pd.ht,st.pd.wt,st.pd.ad.hsno,st.pd.ad.stno,st.pd.ad.area,st.pd.ad.pinno,st.pd.dob.day,st.pd.dob.month,st.pd.dob.year);
		 }
==============================================

typedef struct {
       unsigned int element_a;
       unsigned int element_b;
} EXAMPLE_STRUCT;

and you have an array of pointer to variables of this type like this:


EXAMPLE_STRUCT inst1,inst2,inst3,inst4,inst5,inst6,inst7,inst8;

EXAMPLE_STRUCT* const array_of_ptr_2_struct[8]=
{
    &inst1,
    &inst2,
    &inst3,
    &inst4,
    &inst5,
    &inst6,
    &inst7,
    &inst8,
};







ARRAY   *array_of_ptr_2_struct[0..7],
&               INIT = {4=>{element_a=>2,element_b=>7},
&                            5=>{element_a=>10, element_b => 8},
&                            others=>{element_a=>2,element_b=>7}},
&               EV   = {4=>{element_a=>6,element_b=>7},
&                            5=>{element_a=>10, element_b => 8},
&                            others=>{element_a=>2,element_b=>7}}
===========================================
 #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr;
			 ptr=&st;
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",ptr->name,ptr->rollno,ptr->marks,ptr->pd.ht,ptr->pd.wt,ptr->pd.ad.hsno,ptr->pd.ad.stno,ptr->pd.ad.area,ptr->pd.ad.pinno,ptr->pd.dob.day,ptr->pd.dob.month,ptr->pd.dob.year);
		 }
===========================================
		 
		 #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
	 void fun(student ***ptr);		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr,**ptr1;
			 ptr=&st;
			 ptr1=&ptr;
			 fun(&ptr1);
		 }
		 void fun(student ***ptr)
		 {
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*ptr)->name,(*ptr)->rollno,(*ptr)->marks,(*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,(*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,(*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
		 }
===========================================		 
		  #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
	 void fun(student ***ptr);		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr,**ptr1;
			 ptr=&st;
			 ptr1=&ptr;
			 fun(&ptr1);
		 }
		 void fun(student ***ptr)
		 {
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*(*ptr))->name,(*(*ptr))->rollno,(*(*ptr))->marks,(*(*ptr))->pd.ht,(*(*ptr))->pd.wt,(*(*ptr))->pd.ad.hsno,(*(*ptr))->pd.ad.stno,(*(*ptr))->pd.ad.area,(*(*ptr))->pd.ad.pinno,(*(*ptr))->pd.dob.day,(*(*ptr))->pd.dob.month,(*(*ptr))->pd.dob.year);
		 }
===========================================		 
		  #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
		 
	 void fun(student ****ptr);		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr,**ptr1,***ptr2;
			 ptr=&st;
			 ptr1=&ptr;
			 ptr2=&ptr1;
			 fun(&ptr2);
		 }
		 void fun(student ****ptr)
		 {
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*(*(*ptr)))->name,(*(*(*ptr)))->rollno,(*(*(*ptr)))->marks,\
			 (*(*(*ptr)))->pd.ht,(*(*(*ptr)))->pd.wt,(*(*(*ptr)))->pd.ad.hsno,(*(*(*ptr)))->pd.ad.stno,(*(*(*ptr)))->pd.ad.area,\
			 (*(*(*ptr)))->pd.ad.pinno,(*(*(*ptr)))->pd.dob.day,(*(*(*ptr)))->pd.dob.month,(*(*(*ptr)))->pd.dob.year);
		 }
===========================================	
		 
		  #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
		 
	 void fun(student *****ptr);		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr,**ptr1,***ptr2,****ptr3;
			 ptr=&st;
			 ptr1=&ptr;
			 ptr2=&ptr1;
			 ptr3=&ptr2;
			 fun(&ptr3);
		 }
		 void fun(student *****ptr)
		 {
			 printf("%c %d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*(*(*(*ptr))))->name,(*(*(*(*ptr))))->rollno,(*(*(*(*ptr))))->marks,\
			 (*(*(*(*ptr))))->pd.ht,(*(*(*(*ptr))))->pd.wt,(*(*(*(*ptr))))->pd.ad.hsno,\
			 (*(*(*(*ptr))))->pd.ad.stno,\
			 (*(*(*(*ptr))))->pd.ad.area,\
			 (*(*(*(*ptr))))->pd.ad.pinno,(*(*(*(*ptr))))->pd.dob.day,\
			 (*(*(*(*ptr))))->pd.dob.month,(*(*(*(*ptr))))->pd.dob.year);
		 }
==========================================================================================================================		 
		  #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
		 
		 void main()//with dot oprator
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr;
			 ptr=&st;
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*ptr).name,(*ptr).rollno,(*ptr).marks,(*ptr).pd.ht,(*ptr).pd.wt,(*ptr).pd.ad.hsno,(*ptr).pd.ad.stno,(*ptr).pd.ad.area,(*ptr).pd.ad.pinno,(*ptr).pd.dob.day,(*ptr).pd.dob.month,(*ptr).pd.dob.year);
		 }
		 
===========================================
 #include<stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
		 
		 void main()
		 {
			 student st={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},*ptr,**ptr1;
			 ptr=&st;
			 ptr1=&ptr;
			 printf("%c%d%f\n%.2f%.2f\n%d%d%c%d\n%d%d%d",(*(*ptr1)).name,(*(*ptr1)).rollno,(*(*ptr1)).marks,(*(*ptr1)).pd.ht,\
			 (*(*ptr1)).pd.wt,(*(*ptr1)).pd.ad.hsno,(*(*ptr1)).pd.ad.stno,(*(*ptr1)).pd.ad.area,(*(*ptr1)).pd.ad.pinno,(*(*ptr1)).pd.dob.day,\
			 (*(*ptr1)).pd.dob.month,(*(*ptr1)).pd.dob.year);
		 }
		 
==========================================================================================		 
Bit fileds
#include<stdio.h>
#pragma pack(1)
typedef struct
{
   unsigned sfid  :  7;    /* Source Fucntionial Identifier.                  */
   unsigned rsd   :  1;    /* Reserved = 0 for all One to Many.               */
   unsigned lcl   :  1;    /* local, = 1 if for this network segment only. */
   unsigned pvt   :  1;    /* = 1 if only for a subset of nodes.              */
   unsigned doc   :  14;      /* Data Object Code for the payload.            */
  // unsigned rci   :  2;    /* Redundancy Channel ID.                          */
}  T_A825_BROADCAST_ID;


void main()
{
    printf("%d",sizeof(T_A825_BROADCAST_ID));
}
output:-  3
=============================================================================
// Online C compiler to run C program online
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}};
			 printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",st[0].name,st[0].rollno,st[0].marks,
			 st[0].pd.ht,st[0].pd.wt,st[0].pd.ad.hsno,st[0].pd.ad.stno,st[0].pd.ad.area,
			 st[0].pd.ad.pinno,st[0].pd.dob.day,st[0].pd.dob.month,st[0].pd.dob.year);
			 
			 printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d",st[1].name,st[1].rollno,st[1].marks,
			 st[1].pd.ht,st[1].pd.wt,st[1].pd.ad.hsno,st[1].pd.ad.stno,st[1].pd.ad.area,
			 st[1].pd.ad.pinno,st[1].pd.dob.day,st[1].pd.dob.month,st[1].pd.dob.year);
		 
}

// Online C compiler to run C program online
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}};
							  
			 			for(int i=0;i<TWO;i++)
			 {
			 printf("%c %d %.1f %.1f %.1f %d %d %c %d %d %d %d\n",st[i].name,st[i].rollno,st[i].marks,
			 st[i].pd.ht,st[i].pd.wt,st[i].pd.ad.hsno,st[i].pd.ad.stno,st[i].pd.ad.area,
			 st[i].pd.ad.pinno,st[i].pd.dob.day,st[i].pd.dob.month,st[i].pd.dob.year);
			 }	 
}
=================================================================================================
			// Online C compiler to run C program online
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}};
				student *ptr=&st[0];			  
			 			for(int i=0;i<TWO;i++)
			 {
			 printf("%c %d %.1f %.1f %.1f %d %d %c %d %d %d %d\n",ptr->name,ptr->rollno,ptr->marks,
			 ptr->pd.ht,ptr->pd.wt,ptr->pd.ad.hsno,ptr->pd.ad.stno,ptr->pd.ad.area,
			 ptr->pd.ad.pinno,ptr->pd.dob.day,ptr->pd.dob.month,ptr->pd.dob.year);
			 ptr++;
			 }	 
}

			// Online C compiler to run C program online
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
				student *ptr=st;			  
			  for(int i=0;i<TWO;i++)
			 {
			 printf("%c %d %.1f %.1f %.1f %d %d %c %d %d %d %d\n",(ptr+i)->name,(ptr+i)->rollno,(ptr+i)->marks,
			 (ptr+i)->pd.ht,(ptr+i)->pd.wt,(ptr+i)->pd.ad.hsno,(ptr+i)->pd.ad.stno,(ptr+i)->pd.ad.area,
			 (ptr+i)->pd.ad.pinno,(ptr+i)->pd.dob.day,(ptr+i)->pd.dob.month,(ptr+i)->pd.dob.year);
			 } 
}
=========================================================================================
#include <stdio.h>
typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;		 
#define TWO 2
		 void main()
		 {
			 student st[TWO][TWO]={{{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}},
							  {{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}}
							 };
				student *ptr=&st[0][0];			  
			 			for(int i=0;i<4;i++)
			 {
			 printf("%c %d %.1f %.1f %.1f %d %d %c %d %d %d %d\n",(ptr+i)->name,(ptr+i)->rollno,
			 (ptr+i)->marks,
			 (ptr+i)->pd.ht,(ptr+i)->pd.wt,(ptr+i)->pd.ad.hsno,(ptr+i)->pd.ad.stno,(ptr+i)->pd.ad.area,
			 (ptr+i)->pd.ad.pinno,(ptr+i)->pd.dob.day,
			 (ptr+i)->pd.dob.month,(ptr+i)->pd.dob.year);
			 } 
}

================================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
         	 void fun(student **Ptr1);
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}},*ptr;
			                  
			       ptr=&st[0];           
			      fun(&ptr);            
			                  
		 }
			 void fun(student **Ptr1)
			 {
			     
			    
			 for(int i=0;i<TWO;i++)
			 {
			     
			    
		printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",
			(*Ptr1)->name,(*Ptr1)->rollno,(*Ptr1)->marks,
			 (*Ptr1)->pd.ht,(*Ptr1)->pd.wt,(*Ptr1)->pd.ad.hsno,(*Ptr1)->pd.ad.stno,(*Ptr1)->pd.ad.area,
			 (*Ptr1)->pd.ad.pinno,(*Ptr1)->pd.dob.day,
			 (*Ptr1)->pd.dob.month,(*Ptr1)->pd.dob.year);
			 
			 
			 (*Ptr1)++;
			 
			 
			 }
			 printf("%d\n",sizeof(student));
}
===============================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
         	 void fun(student ***Ptr1);
#define TWO 2
		 void main()
		 {
			 student st[TWO]={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
			                  {'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}},*ptr,**ptr2;
			                  
			       ptr=&st[0]; 
			       ptr2=&ptr;
			      fun(&ptr2);            
			                  
		 }
			 void fun(student ***Ptr1)
			 {
			     
			    
			 for(int i=0;i<TWO;i++)
			 {
			     
			    
		printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",
			(*(*Ptr1))->name,(*(*Ptr1))->rollno,(*(*Ptr1))->marks,
			 (*(*Ptr1))->pd.ht,(*(*Ptr1))->pd.wt,(*(*Ptr1))->pd.ad.hsno,(*(*Ptr1))->pd.ad.stno,(*(*Ptr1))->pd.ad.area,
			 (*(*Ptr1))->pd.ad.pinno,(*(*Ptr1))->pd.dob.day,
			 (*(*Ptr1))->pd.dob.month,(*(*Ptr1))->pd.dob.year);
			 
			 
			 (*(*Ptr1))++;
			 
			 
			 }
			 printf("%d\n",sizeof(student));
}
=============================================================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
void main()
{
 date a={1,2,24};
 date b={2,3,24};
 date c={3,4,24};
    date *array[3]={&a,&b,&c};
    date **ptr=array;
    date *p=*ptr;
    for(int i=0;i<3;i++)
    {
          date *p=*ptr;
    printf("%d %d %d\n",p->day,p->month,p->year);
    ptr++;
    }
    
}
==========================================================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			 student st1 ={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024};
			 student st2 ={'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024};
		student *array[2]={&st1,&st2};
		student **ptr=array,*p;
		
		for(int i=0;i<2;i++)
		{
		    p=*ptr;
		printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",
			p->name,p->rollno,p->marks,
			 p->pd.ht,p->pd.wt,p->pd.ad.hsno,p->pd.ad.stno,p->pd.ad.area,
			 p->pd.ad.pinno,p->pd.dob.day,
			 p->pd.dob.month,p->pd.dob.year);
			 ptr++;
		 }
		 }
===================================================================================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			 student st1 ={'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024};
			 student st2 ={'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024};
		student *array[2]={&st1,&st2};
		student **ptr=array;
		
		for(int i=0;i<2;i++)
		{
		    
		printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",
			(*ptr)->name,(*ptr)->rollno,(*ptr)->marks,
			 (*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,
			 (*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,
			 (*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
			 ptr++;
		 }
		 }
=================================================================================
#include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks;
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			 student st1[2] ={{'a',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
	{'b',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}};
	 student st2[2] ={{'c',1,12.1,5.1,50.5,101,32,'s',562159,14,03,2024},
	{'d',2,12.3,5.3,50.6,102,34,'r',562160,15,03,2024}};
		student *array[]={&st1[0],&st2[0]};
		student **ptr=&array[0];
	 for(int j=0;j<2;j++)
	 {
		for(int i=0;i<2;i++)
		{
		
		printf("%c%d%.1f%.1f%.1f%d%d%c%d%d%d%d\n",
			(*ptr)->name,(*ptr)->rollno,(*ptr)->marks,
			 (*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,
			 (*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,
			 (*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
			 (*ptr)++;
		 }
		 ptr++;
	 }
 }
==============================================================================================
		        			        #include <stdio.h>

typedef struct 
         {
	       int day,month,year;
         }date;
		 
typedef struct 
         {
	       int hsno,stno;
		   char area;
		   int pinno;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno;
		   float marks[2];
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			 student st1[2] ={{'a',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024},
	{'b',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
	 student st2[2] ={{'c',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024},
	{'d',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
		student *array[]={&st1[0],&st2[0]};
		student **ptr=&array[0];
	 for(int j=0;j<2;j++)
	 {
		for(int i=0;i<2;i++)
		{
		
		printf("%c %d %.1f %.1f %.1f %.1f %d%d%c%d%d%d%d\n",
			(*ptr)->name,(*ptr)->rollno,(*ptr)->marks[0],(*ptr)->marks[1],
			 (*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,
			 (*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,
			 (*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
			 (*ptr)++;
		 }
		 ptr++;
	 }
		 }
=====================================================================================================
#include <stdio.h>
#pragma pack(1)
typedef struct 
         {
	     unsigned   day:5;
	     unsigned   month:4;
	     unsigned   year:11;
         }date;
		 
typedef struct 
         {
	       int hsno:20,stno:20;
		   char area;
		   int pinno:30;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno:4;
		   float marks[2];
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			 student st1[2] ={{'a',1,12.1,12.2,5.1,50.5,101,32,'s',562159,31,12,2024},
	{'b',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
	 student st2[2] ={{'c',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024},
	{'d',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
		student *array[]={st1,st2};
		student **ptr=&array[0];
	 for(int j=0;j<2;j++)
	 {
		for(int i=0;i<2;i++)
		{
		
		printf("%c %d %.1f %.1f %.1f %.1f %d %d %c %d %d %d %d\n",
			(*ptr)->name,(*ptr)->rollno,(*ptr)->marks[0],(*ptr)->marks[1],
			 (*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,
			 (*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,
			 (*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
			 (*ptr)++;
		 }
		 ptr++;
	 }
	 printf("%d",sizeof(student));
		 }
============================================================================
#include <stdio.h>
#pragma pack(1)
typedef struct 
         {
	     unsigned   day:5;
	     unsigned   month:4;
	     unsigned   year:11;
         }date;
		 
typedef struct 
         {
	       int hsno:20,stno:20;
		   char area;
		   int pinno:30;
         }address;
		 
typedef struct 
         {
	       float ht,wt;
		   address ad;
		   date  dob;
         }details;		 
		 
typedef struct 
         {
	       char name;
		   int rollno:4;
		   float marks[2];
           details pd;
         }student;
         
#define TWO 2
		 void main()
		 {
			student st1[2][2] ={{'a',1,12.1,12.2,5.1,50.5,101,32,'s',562159,31,12,2024,
	'b',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024},{'c',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024,
	'd',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
	
	 student st2[2][2]={{'e',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024,
	'f',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024},{'g',1,12.1,12.2,5.1,50.5,101,32,'s',562159,14,03,2024,
	'h',2,12.3,12.4,5.3,50.6,102,34,'r',562160,15,03,2024}};
		student *array[]={&st1[0][0],&st2[0][0]};
		student **ptr=&array[0];
	 for(int j=0;j<2;j++)
	 {
		for(int i=0;i<4;i++)
		{
		
		printf("%c %d %.1f %.1f %.1f %.1f %d %d %c %d %d %d %d\n",
			(*ptr)->name,(*ptr)->rollno,(*ptr)->marks[0],(*ptr)->marks[1],
			 (*ptr)->pd.ht,(*ptr)->pd.wt,(*ptr)->pd.ad.hsno,(*ptr)->pd.ad.stno,(*ptr)->pd.ad.area,
			 (*ptr)->pd.ad.pinno,(*ptr)->pd.dob.day,
			 (*ptr)->pd.dob.month,(*ptr)->pd.dob.year);
			 (*ptr)++;
		 }
		 ptr++;
	 }
	 printf("%d",sizeof(student));
		 }
output:
a 1 12.1 12.2 5.1 50.5 101 32 s 562159 31 12 2024
b 2 12.3 12.4 5.3 50.6 102 34 r 562160 15 3 2024
c 1 12.1 12.2 5.1 50.5 101 32 s 562159 14 3 2024
d 2 12.3 12.4 5.3 50.6 102 34 r 562160 15 3 2024
e 1 12.1 12.2 5.1 50.5 101 32 s 562159 14 3 2024
f 2 12.3 12.4 5.3 50.6 102 34 r 562160 15 3 2024
g 1 12.1 12.2 5.1 50.5 101 32 s 562159 14 3 2024
h 2 12.3 12.4 5.3 50.6 102 34 r 562160 15 3 2024
31
==================================================
#include <stdio.h>
typedef struct 
{
    int *ptr1;
    float *ptr2;
}pointers;

int main() {
    // Write C code here
    pointers s;
    int a=10;float b=1.1;
    s.ptr1=&a;
    s.ptr2=&b;
    printf("%d %.1f",*(s.ptr1),*(s.ptr2));
    return 0;
}
===================================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct 
{
    int *ptr1;
    float *ptr2;
}pointers;

int main() {
    // Write C code here
    pointers s,*first;
    first=&s;
    int a=10;float b=1.1;
    first->ptr1=&a;
    first->ptr2=&b;
    printf("%d %.1f",*first->ptr1,*first->ptr2);
    return 0;
}

======================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct
{
    int day,month,year;
}date;
typedef struct 
{
    int *ptr1;
    float *ptr2;
    date *ptr3;
}pointers;

int main() {
    // Write C code here
    pointers s,*first;date dob={1,2,24};
    first=&s;
    int a=10;float b=1.1;
    first->ptr1=&a;
    first->ptr2=&b;
    first->ptr3=&dob; 
    printf("%d %.1f %d %d %d",*first->ptr1,*first->ptr2,
    (first->ptr3)->day,(first->ptr3)->month,(first->ptr3)->year);
    return 0;
}
====================================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct
{
    int day,month,year;
}date;
typedef struct 
{
    int *ptr1;
    float *ptr2;
    date *ptr3;
}pointers;

int main() {
    // Write C code here
    pointers s,*first;date dob={1,2,24};
    first=&s;
    int a=10;float b=1.1;
    first->ptr1=&a;
    first->ptr2=&b;
    first->ptr3=&dob; 
    printf("%d %.1f %d %d %d",*(first->ptr1),*(first->ptr2),
    (*first->ptr3).day,(*first->ptr3).month,(*first->ptr3).year);
    return 0;
}
==============================================================
Testing concepts
-----------------
1. how to test local variable in RTRT
a) first we have to make it as global by declaring that variable in ptu.
EXAMPLE;-
 we have integer variale locally see below
 file name 1.c
 void fun()
 {
 int a,
 bool b,c;
 if(a==1)
 {
	 b=1;
 }
 else
 {
  c=0;	 
 }
 }
-if you want to test this local varible
 file name 1.ptu
 #int a;
 #bool b,c;
    ENVIRONMENT ENV_fun
    VAR a,        init = 0,      ev = init 
    VAR b,        init = 0,      ev = init
    VAR c,        init = 0,      ev = init	
    END ENVIRONMENT -- ENV_fun
    USE ENV_fun

TEST 1
FAMILY nominal

        COMMENT  Test Description
		
		///////////////////////
		ELEMENT
        
            COMMENT INPUT SECTION :
                
                --Initializes the local variable
                VAR a,                  init = 1,             ev = init              
            COMMENT INPUT/OUTPUT SECTION :
                --none            
            COMMENT OUTPUT SECTION :                   
                VAR b,        init = 0,      ev = 1
                VAR c,        init = 0,      ev = 0
            SIMUL                
                --none           
            END SIMUL       
        --Calling Unit Under Test    
        #fun();       
        END ELEMENT
    END TEST -- TEST 1
	--similarly for service parameters aslo same as above example
=======================================================
// Online C compiler to run C program online
#include <stdio.h>
int add(int a,int b);
int sub(int a,int b);
int mul(int a,int b);
int division(int a,int b);
int (*fun_ptr)(int,int);
int main() {
  int x;
  fun_ptr=&add;
  x=(*fun_ptr)(1,2);
  printf("%d\n",x);
  fun_ptr=&mul;
  x=(*fun_ptr)(1,2);
  printf("%d\n",x);
  fun_ptr=&sub;
  x=(*fun_ptr)(3,2);
  printf("%d\n",x);
  fun_ptr=&division;
  x=(*fun_ptr)(2,2);
  printf("%d",x);
}

int add(int a,int b)
{
    return (a+b);
}
int mul(int a,int b)
{
    return (a*b);
}
int sub(int a,int b)
{
    return (a-b);
}
int division(int a,int b)
{
    return (a/b);
}
======================================================================
function pointer address in array of pointer 
#include <stdio.h>
int add(int a,int b);
int sub(int a,int b);
int mul(int a,int b);
int division(int a,int b);
int (*fun_ptr[4])(int,int);
int main() {
  int x;
  int *ptr;
  // int *p;
int (*fun_ptr[4])(int,int)={&add,&sub,&mul,&division};
  for(int i=0;i<4;i++)
  {
      
  x=(*fun_ptr[i])(2,2);
  printf("%d\n",x);
}
}

int add(int a,int b)
{
    return (a+b);
}
int mul(int a,int b)
{
    return (a*b);
}
int sub(int a,int b)
{
    return (a-b);
}
int division(int a,int b)
{
    return (a/b);
}
==============================================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
    char name[10];
    int rollno;
    float marks[3];
    date dob;
}student;
void fun(student **);
void main() {
    student st_1[2]={{"dada",101,1.1,1.2,1.3,25,03,2024},{"hayath",102,1.4,1.5,1.6,07,01,1998}};
     student st_2[2]={{"shaik",101,1.1,1.2,1.3,25,03,2024},{"anwar",102,1.4,1.5,1.6,07,01,1998}};
     student *array[2]={st_1,st_2};
     fun(array);
}
    
void fun(student **ptr)
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
    printf("%s %d %.1f %.1f %.1f %d %d %d\n",(*ptr)->name,(*ptr)->rollno,(*ptr)->marks[0],(*ptr)->marks[1],(*ptr)->marks[2],
    (*ptr)->dob.d,(*ptr)->dob.m,(*ptr)->dob.y);
	
        (*ptr)++;
        }
     ptr++;
    }
}
=======================================================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
    char name[10];
    int rollno;
    float marks[3];
    date dob;
}student;
void fun(student ***);
void main() {
     student st_1[2]={{"dada",101,1.1,1.2,1.3,25,03,2024},{"hayath",102,1.4,1.5,1.6,07,01,1998}};
     student st_2[2]={{"shaik",101,1.1,1.2,1.3,25,03,2024},{"anwar",102,1.4,1.5,1.6,07,01,1998}};
     student st_3[2]={{"hi",101,1.1,1.2,1.3,25,03,2024},{"hoo",102,1.4,1.5,1.6,07,01,1998}};
     student st_4[2]={{"hello",101,1.1,1.2,1.3,25,03,2024},{"hell",102,1.4,1.5,1.6,07,01,1998}};
     student *array_1[2]={st_1,st_2};
     student *array_2[2]={st_3,st_4};
     student **arr[2]={array_1,array_2};
     fun(&arr[0]);
}
    
void fun(student ***ptr)
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            for(int k=0;k<2;k++)
            {
             printf("%s %d %.1f %.1f %.1f %d %d %d\n",(*(*ptr))->name,(*(*ptr))->rollno,(*(*ptr))->marks[0],
	         (*(*ptr))->marks[1],(*(*ptr))->marks[2],
             (*(*ptr))->dob.d,(*(*ptr))->dob.m,(*(*ptr))->dob.y);
			 
            (*(*ptr))++;
            }
        (*ptr)++;
        }
     ptr++;
    }
}
====================================================================================================
#include<stdio.h>
void main()
{
 int a[5]={1,2,3,4,5};
 int (*ptr)[5];
 ptr=&a;
int *p=(int*)ptr;
 for(int i=0;i<5;i++)
 {
 printf("%d\n",*p);
 p++;
 }
}
==========================================================================================================
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
    char name;
    int rollno;
    float marks[3];
    date dob;
}student;
typedef struct 
{
    student array[1];
}data;
#include<stdio.h>
void main()
{
    data d;
    d.array[0].name='a';
    d.array[0].rollno=101;
    d.array[0].marks[0]=1.1;
    d.array[0].marks[1]=1.2;
    d.array[0].marks[2]=1.3;
    d.array[0].dob.d=28;
    d.array[0].dob.m=03;
    d.array[0].dob.y=2024;
    printf("%c %d %.1f %.1f %.1f %d %d %d",d.array[0].name,d.array[0].rollno,d.array[0].marks[0],
	d.array[0].marks[1],d.array[0].marks[2],d.array[0].dob.d,d.array[0].dob.m,d.array[0].dob.y);
}
============================================================================================
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
    char name;
    int rollno;
    float marks[3];
    date dob;
}student;
typedef struct 
{
    student array[1];
    student *ptr;
}data;
#include<stdio.h>
void main()
{
    data d,*p;
	p=&d;
    p->ptr=&p->array[0];
    (p->ptr)->name='a';
    (p->ptr)->rollno=101;
    (p->ptr)->marks[0]=1.1;
    (p->ptr)->marks[1]=1.2;
    (p->ptr)->marks[2]=1.3;
    (p->ptr)->dob.d=28;
    (p->ptr)->dob.m=03;
    (p->ptr)->dob.y=2024;
for(int i=0;i<1;i++)
{
    printf("%c %d %.1f %.1f %.1f %d %d %d\n",(p->ptr)->name,
    (p->ptr)->rollno,(p->ptr)->marks[0],(p->ptr)->marks[1],
    (p->ptr)->marks[2],(p->ptr)->dob.d,(p->ptr)->dob.m,
    (p->ptr)->dob.y);
}
}
===========================================================
// Online C compiler to run C program online
#include <stdio.h>
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
    char name;
    int rollno;
    float marks[3];
    date dob;
}student;
typedef struct 
{
    student array[1];
    student *ptr;
}data;
#include<stdio.h>
void main()
{
    data d,*p;
    p=&d;
   p->ptr=&(*p).array[0];
   (*p->ptr).name='a';
   (*p->ptr).rollno=101;
   (*p->ptr).marks[0]=1.1;
   (*p->ptr).marks[1]=1.2;
   (*p->ptr).marks[2]=1.3;
   (*p->ptr).dob.d=28;
   (*p->ptr).dob.m=03;
   (*p->ptr).dob.y=2024;
    printf("%c %d %.1f %.1f %.1f %d %d %d",
    (*p->ptr).name,(*p->ptr).rollno,(*p->ptr).marks[0],
    (*p->ptr).marks[1],(*p->ptr).marks[2],(*p->ptr).dob.d,
    (*p->ptr).dob.m,(*p->ptr).dob.y);

}
========================================================
#include <stdio.h>
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
 float st1,st2;   
}mark;
typedef struct
{
    char name;
    int rollno;
    mark marks[3];
    date dob;
}student;
typedef struct 
{
    student array[1];
    student *ptr;
}data;
#include<stdio.h>
void main()
{
    data d,*p;
    p=&d;
   p->ptr=&(*p).array[0];
   (*p->ptr).name='a';
   (*p->ptr).rollno=101;
   (*p->ptr).marks[0].st1=1.1;
   (*p->ptr).marks[1].st1=1.2;
   (*p->ptr).marks[2].st1=1.3;
   (*p->ptr).marks[0].st2=1.4;
   (*p->ptr).marks[1].st2=1.5;
   (*p->ptr).marks[2].st2=1.6;
   (*p->ptr).dob.d=28;
   (*p->ptr).dob.m=03;
   (*p->ptr).dob.y=2024;
    printf("%c %d %.1f %.1f %.1f %.1f %.1f %.1f %d %d %d",
    (*p->ptr).name,(*p->ptr).rollno,(*p->ptr).marks[0].st1,(*p->ptr).marks[1].st1,(*p->ptr).marks[2].st1,(*p->ptr).marks[0].st2,
(*p->ptr).marks[1].st2,(*p->ptr).marks[2].st2,(*p->ptr).dob.d,
    (*p->ptr).dob.m,(*p->ptr).dob.y);

}
==============================================================================================
#include <stdio.h>
typedef struct
{
 int d,m,y;   
}date;
typedef struct
{
 float x,y;   
}mark;
typedef struct
{
 mark st1,st2;   
}s;
typedef struct
{
    char name;
    int rollno;
    s marks[3];
    date dob;
}student;
typedef struct 
{
    student array[1];
    student *ptr;
}data;
#include<stdio.h>
void main()
{
    data d,*p;
    p=&d;
   p->ptr=&(*p).array[0];
   (*p->ptr).name='a';
   (*p->ptr).rollno=101;
   (*p->ptr).marks[0].st1.x=1.1;
   (*p->ptr).marks[1].st1.x=1.2;
   (*p->ptr).marks[2].st1.x=1.3;
   (*p->ptr).marks[0].st1.y=1.7;
   (*p->ptr).marks[1].st1.y=1.8;
   (*p->ptr).marks[2].st1.y=1.9;
   (*p->ptr).marks[0].st2.x=1.4;
   (*p->ptr).marks[1].st2.x=1.5;
   (*p->ptr).marks[2].st2.x=1.6;
   (*p->ptr).marks[0].st2.y=1.4;
   (*p->ptr).marks[1].st2.y=1.5;
   (*p->ptr).marks[2].st2.y=1.6;
   (*p->ptr).dob.d=28;
   (*p->ptr).dob.m=03;
   (*p->ptr).dob.y=2024;
    printf("%c %d %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %.1f %d %d %d",
    (*p->ptr).name,(*p->ptr).rollno,(*p->ptr).marks[0].st1.x,(*p->ptr).marks[1].st1.x,(*p->ptr).marks[2].st1.x,
(*p->ptr).marks[0].st1.y,(*p->ptr).marks[1].st1.y,
(*p->ptr).marks[2].st1.y,(*p->ptr).marks[0].st2.x,
(*p->ptr).marks[1].st2.x,(*p->ptr).marks[2].st2.x,
(*p->ptr).marks[0].st2.y,(*p->ptr).marks[1].st2.y,
(*p->ptr).marks[2].st2.y,(*p->ptr).dob.d,
    (*p->ptr).dob.m,(*p->ptr).dob.y);

}
===============================================================================================================
please find all structure program for learing