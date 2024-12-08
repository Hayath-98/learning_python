#FILEHEADER hdudispfoscpua,Source Code Ver : 1.1,TestScript Ver : 1.3
# --------------------------------------------------------------------------------
#-- Author Name         : Hemalatha S
#--
#-- Tested module       : hdudispfoscpua.s
#--
#-- Tested CSUs         : OsCtxSw,
#--			  			  OsIntCtxSw,
#--			  			  SaveStatusReg,
#--			  			  RestoreStatusReg,
#--			  			  OsStartHighRdy,
#--			  			  PendSvHandler
#--			  
#-- Test script file    : TSF_hdudispfoscpua.s
#-- History
#--
#-- VERSION      WHEN           WHO             	WHAT
#-- -------      ----------     --------       		-------------
#--  1.1       	30.10.2017	   Hemalatha S			Created the TSF.
#--  1.2         11.11.2017    Hemalatha S    	Updated as per #PR100171
#--  1.3         14.11.2017    Hemalatha S     	Updated as per #PR100171	
# --------------------------------------------------------------------------------
# Include Files Section

#Global variable Section

   	  #COMMENT Author Name      :Hemalatha S
      #COMMENT
      #COMMENT File Name        :TSF_hdudispfoscpua.s 
      #COMMENT
      #COMMENT Tested Functions :OsCtxSw
	  #COMMENT			  		 OsIntCtxSw,
	  #COMMENT			  		 SaveStatusReg,
	  #COMMENT		  			 RestoreStatusReg,
	  #COMMENT			  		 OsStartHighRdy,
	  #COMMENT			  		 PendSvHandler      
      #COMMENT 
      #COMMENT Assumptions and Constraints
      #COMMENT <AC>
      #COMMENT Assumptions
      #COMMENT None
      #COMMENT Constraints
	  #COMMENT None
      #COMMENT </AC>   
      
      #COMMENT Equivalence Class Description
      #COMMENT <ECD>
      #COMMENT Valid Classes
      #COMMENT Class 1
	  #COMMENT In function 'OsCtxSw', PendSV exception is triggered. 
      #COMMENT
      #COMMENT Class 2
      #COMMENT In function 'OsIntCtxSw', PendSV exception is triggered . 
      #COMMENT 
	  #COMMENT Class 3
	  #COMMENT In function 'SaveStatusReg', interrupt mask register is saved and interrupts are disabled. 
      #COMMENT 
	  #COMMENT Class 4
	  #COMMENT In function 'RestoreStatusReg',interrupts are enabled by restoring saved interrupts. 
      #COMMENT 
	  #COMMENT Class 5
	  #COMMENT In function 'OsStartHighRdy', PendSV exception priority is set . 
      #COMMENT       
	  #COMMENT Class 6
	  #COMMENT In function 'OsStartHighRdy', PSP is set to 0 for initial context switch . 
      #COMMENT          
	  #COMMENT Class 7
	  #COMMENT In function 'OsStartHighRdy', Os_running flag is set to TRUE to indicate  multitasking will start. 
      #COMMENT  
	  #COMMENT Class 8
	  #COMMENT In function 'OsStartHighRdy', PendSV exception is triggered. 
      #COMMENT  
 	  #COMMENT Class 9
	  #COMMENT In function 'OsStartHighRdy', interrupts are enabled. 
      #COMMENT 
      #COMMENT Class 10
	  #COMMENT In function 'PendSVHandlerFlight', interrupts are prevented during context switch. 
      #COMMENT
      #COMMENT Class 11
	  #COMMENT In function 'PendSVHandlerFlight',  process stack pointer (PSP) is saved. 
      #COMMENT    
      #COMMENT Class 12
	  #COMMENT In function 'PendSVHandlerFlight',  register saving is skipped for the first time. 
      #COMMENT   
      #COMMENT Class 13
	  #COMMENT In function 'PendSVHandlerFlight',  register R4-R11 is saved on process stack.
      #COMMENT  
      #COMMENT Class 14
	  #COMMENT In function 'PendSVHandlerFlight',  floating point register S16-S31 is saved on stack.
      #COMMENT   
      #COMMENT Class 15
	  #COMMENT In function 'PendSVHandlerFlight',  Stack pointer is loaded to the TCB stack.
      #COMMENT   
      #COMMENT Class 16
	  #COMMENT In function 'PendSVHandlerFlight', set highest priority task ready to execute into the current TCB when 
	  #COMMENT branch PendSvHandler_NoSave is invoked.
      #COMMENT          
      #COMMENT Invalid Class(es)
      #COMMENT  None.
      #COMMENT </ECD> 
#------------------------------------------------------------------------------- 
TESTSTART:
        
#Define the stack initial address               


# set up the stack initial address 

   
#Macro definitions
   /*  absolute or relocatable values  */
    .equ NVIC_INT_CTRL,     temp_NVIC_INT_CTRL/*Modified for testing purpose */
    .equ NVIC_SYSPRI14,     temp_NVIC_SYSPRI14/*Modified for testing purpose */
 
    .equ NVIC_PENDSV_PRI,   0xFF       
    .equ NVIC_PENDSVSET,    0x10000000  

    .equ DEFAULT_VAL,       0x0       
    .equ DEFAULT_TRUE_VAL,  0x1          
    .equ EXCEPTION_RETURN,  0x4         
    /*Modified for Testing Purpose*/
	.equ CONST_ZERO,		0x0
	.equ CONST_ONE,			0x1
    .equ CONST_THREE,		0x3
        
#-------------------------------------------------------------------------------   
                    
TEST_1:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'OsCtxSw'triggers the PendSV exception by 
    #COMMENT - Loading the Interrupt control state register(NVIC_INT_CTRL) to R0
    #COMMENT - Loading the Value to trigger PendSV isr(NVIC_PENDSVSET) to R1
    #COMMENT - write R1 to address R0 content
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-OsCtxSw-CB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 1
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at line number 134 to call the function DisplayMain in 'hdudispfstartupstm32f746xx.s' file 
    #COMMENT 		  and press F5 to enter function under test.
    #COMMENT 		  In DisplayMain, at line number 250 set a breakpoint and add testcase_number in watch window 
    #COMMENT          and enter value of testcase_number as 1.
    #COMMENT          Set breakpoint at line number 258 in function 'OsCtxSw' and press F5 to enter function under test.
    #COMMENT          Below mentioned steps has to be followed to verify Low Level Requirement.
    #COMMENT Step 2 : Check the initial value of R0, R1, R7 and temp_NVIC_INT_CTRL in watch window.
	#COMMENT Step 3 : Set breakpoint at line number 86 in source 'hdudispfoscpua.s' where value of R1 is set to 'NVIC_PENDSVSET'.
	#COMMENT          Observe values of R0 is equal to &temp_NVIC_INT_CTRL and R1 is equal to NVIC_PENDSVSET(0x10000000).
	#COMMENT Step 4 : Set breakpoint at line number 93 in source 'hdudispfoscpua.s' where content of R1(i.e NVIC_PENDSVSET) is stored to 
	#COMMENT		  content of R0(i.e content is stored in temp_NVIC_INT_CTRL.).Observe value of temp_NVIC_INT_CTRL is equal to NVIC_PENDSVSET. 
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    	init          ev
    #-------------------------------------------------------------------------------
    # RVAL	R0				0x0		&temp_NVIC_INT_CTRL
    # RVAL  R1      		0x0     NVIC_PENDSVSET
    #
    #VAR temp_NVIC_INT_CTRL	0x0 	NVIC_PENDSVSET
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    temp_NVIC_INT_CTRL = 0;
                
	__ASM("MOV R7,0x0");
	__ASM("MOV R0,0x0");
	__ASM("MOV R1,0x0");
    OsCtxSw();
        
TEST_2:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function  'OsIntCtxSw' does the following to trigger the PendSV exception
    #COMMENT - Load the Interrupt control state register to R0
    #COMMENT - Load the Value to trigger PendSV isr to R1
    #COMMENT - write R1 to address R0 content
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-OsIntCtxSw-CB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 2
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at line number 134 to call the function DisplayMain in 'hdudispfstartupstm32f746xx.s' file 
    #COMMENT 		  and press F5 to enter function under test.
    #COMMENT 		  In DisplayMain, at line number 250 set a breakpoint and add testcase_number in watch window 
    #COMMENT          and enter value of testcase_number as 2.
    #COMMENT          Set breakpoint at line number 258 in function 'OsCtxSw' and press F5 to enter function under test.
    #COMMENT          Below mentioned steps has to be followed to verify Low Level Requirement.
    #COMMENT Step 2 : Check the initial value of R0, R1, R7 and temp_NVIC_INT_CTRL in watch window.
	#COMMENT Step 3 : Set breakpoint at line number 113 in source 'hdudispfoscpua.s' where value of R1 is set to 'NVIC_PENDSVSET'.
	#COMMENT          Observe values of R0 is equal to &temp_NVIC_INT_CTRL and R1 is equal to NVIC_PENDSVSET(0x10000000).
	#COMMENT Step 4 : Set breakpoint at line number 94 in source 'hdudispfoscpua.s' where content of R1(i.e NVIC_PENDSVSET) is stored to 
	#COMMENT          content of R0(i.e content is stored in temp_NVIC_INT_CTRL.).Observe value of temp_NVIC_INT_CTRL is equal to NVIC_PENDSVSET.
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    # RVAL	R0				0x0			&temp_NVIC_INT_CTRL
    # RVAL  R1      		0x0     	NVIC_PENDSVSET
    #
    #VAR temp_NVIC_INT_CTRL	0x0 		NVIC_PENDSVSET
    #-------------------------------------------------------------------------------   
                    
    #--Test case start here
    
    temp_NVIC_INT_CTRL = 0;
               
	__ASM("MOV R7,0x0");
	__ASM("MOV R0,0x0");
	__ASM("MOV R1,0x0");
    OsIntCtxSw();
        
  TEST_3:
  
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'SaveStatusReg' does the following to save the interrupt mask register
    #COMMENT and then disables all the interrupts.
    #COMMENT - Read PRIMASK special register value and write it to R0
    #COMMENT - Disable IRq by setting the PRIMASK special register value.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-SaveStatusReg-CB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 3
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at line number 134 to call the function DisplayMain in 'hdudispfstartupstm32f746xx.s' file 
    #COMMENT 		  and press F5 to enter function under test.
    #COMMENT 		  In DisplayMain, at line number 250 set a breakpoint and add testcase_number in watch window 
    #COMMENT          and enter value of testcase_number as 2.
    #COMMENT          Below mentioned steps has to be followed to verify Low Level Requirement.  
    #COMMENT Step 2 : Check the initial value of R0,R3 and R5(PRIMASK initial value) in watch window.
	#COMMENT Step 3 : Set breakpoint at line number 127 in source 'hdudispfoscpua.s' where  Priority mask register contents are moved to R0 
	#COMMENT          and observe whether contents of R0 is same as R5.
	#COMMENT Step 4 : Set breakpoint at line number 280 in instruction '__ASM("MRS R3, PRIMASK")' in 'hdudispfmain.c'(switch case 3) and verify 
	#COMMENT          that R3 is set to 0x1 when BIT 0 of PRIMASK is set after disabling interrupts(i.e after CPSID I).
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    init    ev
    #-------------------------------------------------------------------------------  
    # RVAL	R0		0x0	    0x0
    # RVAL  R3		0x0	    0x1
    # RVAL  R5		0x0	    0x0
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    
    #--To check initial value of primask
    __ASM("MRS     R5, PRIMASK");
    __ASM("MOV     R3, 0");
    
    #-- Function Under Test
    U32_critical_sr = SaveStatusReg(); 
    
    #--To verify that BIT 0 of PRIMASK is set after disabling interrupts
	__ASM("MRS     R3, PRIMASK");

        
  TEST_4:
  
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'RestoreStatusReg' does the following to restore saved interrupts.
    #COMMENT - write the contents of R0 into PRIMASK register 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-RestoreStatusReg-CB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 4
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Repeat all steps in TEST 3 (since 'RestoreStatusReg' has to be tested after calling 'SaveStatusReg')
    #COMMENT	      Set breakpoint at function 'RestoreStatusReg' and press F5 to enter function under test.
    #COMMENT Step 2 : Check the initial value of R0,R5 and R4 in watch window.
	#COMMENT Step 3 : Set breakpoint at line number 212 in source 'hdudispfoscpua.s' where  R0 contents are moved to Priority mask register 
	#COMMENT          and observe whether contents of R0 is 0x0.    
	#COMMENT Step 4 : Set breakpoint at line number 287 in instruction '__ASM("MRS     R4, PRIMASK")' in 'hdudispfoscpua.c'(switch case 3)  and
	#COMMENT          check R5 is equal to R4 after call to function RestoreStatusReg().
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    init    ev
    #------------------------------------------------------------------------------- 
    # RVAL	R0		0x0	    0x0 
    # RVAL  R5		0x0	    0x0
    # RVAL  R4		0x1	    0x0
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    
    #--To check initial value of primask*/
    __ASM("MRS     R5, PRIMASK");
    __ASM("MOV     R3, 0");
    
    #-- Called to save Interrupt mask register 
    U32_critical_sr = SaveStatusReg()  
                
    #-- Function Under Test
    RestoreStatusReg(U32_critical_sr)  
    
    #--To verify that PRIMASK initial value is restored */
	__ASM("MOV     R4, 1");
	__ASM("MRS     R4, PRIMASK");
        
   TEST_5:
   
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT To test whether the function  'OsStartHighRdy' does the following 
    #COMMENT - 	Set PendSV exception priority by
    #COMMENT			-	Loading the System prio register(NVIC_SYSPRI14) to R0
	#COMMENT      		-	Loading the PendSV priority value(NVIC_PENDSV_PRI) to R1
	#COMMENT			-	Writing R1 content as unsigned byte to address of R0.
    #COMMENT - set the PSP to DEFAULT_VAL(0x0)  for initial context switch call by
    #COMMENT			-	Writing value of DEFAULT_VAL to R0
	#COMMENT			-	Writing the contents of R0 into PSP register.
    #COMMENT - set the Os_running flag to TRUE by
    #COMMENT			-	Loading the Os_running flag address to R0
	#COMMENT	      	-	Writing value of DEFAULT_TRUE_VAL to R1 
	#COMMENT			-	Writing R1 content as unsigned byte to address of R0.
    #COMMENT - Trigger the PendSV exception by
    #COMMENT      		-	Loading the Interrupt control state register(NVIC_INT_CTRL) to R0
	#COMMENT      		-	Loading the Value to trigger PendSV isr(NVIC_PENDSVSET) to R1
	#COMMENT			-	Writing R1 content as unsigned byte to address of R0.
    #COMMENT - Enable interrupts by clearing the PRIMASK special register value.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-001
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-002
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-003
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-004
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-005
    #COMMENT hdudispfoscpua-OsStartHighRdy-CB-LLR-006
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 5
    #COMMENT  Class 6
    #COMMENT  Class 7
    #COMMENT  Class 8
    #COMMENT  Class 9
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at switch statement in 'hdudispfstartupstm32f746xx.s' file and and add testcase_number in watch window and enter value of 
    #COMMENT 		  testcase_number as 5.Set breakpoint at function 'OsStartHighRdy' and press F5 to enter function under test.
    #COMMENT          Below mentioned steps has to be followed to verify Low Level Requirement.
    #COMMENT Step 2 : Check initial values of R1,R7,temp_NVIC_INT_CTRL,temp_NVIC_SYSPRI14 and Os_running in watch window.
	#COMMENT Step 3 : Set breakpoint at line number 212 in 'hdudispfoscpua.s' where R1 content is written as unsigned byte to address of R0.
	#COMMENT          Observe values of R0 is equal to &temp_NVIC_SYSPRI14, R1 is equal to NVIC_PENDSV_PRI 
	#COMMENT Step 4.  Set breakpoint at line number 218 in 'hdudispfoscpua.s' where DEFAULT_VAL is stored in R0.Observe that temp_NVIC_SYSPRI14 is 
	#COMMENT          equal to NVIC_PENDSV_PRI.
	#COMMENT Step 5 : Set breakpoint at line number 219 in 'hdudispfoscpua.s' where R0 content is written to PSP.Observe value of
	#COMMENT          R0 is equal to DEFAULT_VAL(0x0).
	#COMMENT Step 6 : Set breakpoint at line number 224 in 'hdudispfoscpua.s' where R1 content is written as unsigned byte to address of R0.
	#COMMENT          observe values of R0 equal to &Os_running, R1 is equal to DEFAULT_TRUE_VAL(0x1).
	#COMMENT Step 7 : Set breakpoint at line number 225 in 'hdudispfoscpua.s' and observe Os_running is equal to DEFAULT_TRUE_VAL(0x1). 
	#COMMENT		  
	#COMMENT Step 8 : Set breakpoint at line number 231 in 'hdudispfoscpua.s' where R1 content is written as unsigned byte to address of R0.
	#COMMENT          Observe values of R0 is equal to &temp_NVIC_INT_CTRL, R1 is equal NVIC_PENDSVSET(0x10000000).
	#COMMENT Step 9 : Set breakpoint at line number 232 in 'hdudispfoscpua.s' and observe temp_NVIC_INT_CTRL is equal to NVIC_PENDSVSET
	#COMMENT          
	#COMMENT Step 10: Set breakpoint at line number 237 in 'hdudispfoscpua.s' at label OsStartHang and observe the label is hit 2 times.
	#COMMENT          R0 is equal to &temp_NVIC_INT_CTRL, R1 is equal NVIC_PENDSVSET(0x10000000) and temp_NVIC_INT_CTRL is equal
	#COMMENT          to NVIC_PENDSVSET	.
	#COMMENT Step 11: Set breakpoint at line number 307 in instruction  __ASM("MRS     R5, PSP") in 'hdudispfoscpua.c' and observe value R5 is equal to 0x0
	#COMMENT	  	  in order to verify  PSP is set to DEFAULT_VAL(0x0).
	#COMMENT Step 12: Set breakpoint at line number 310 in at instruction __ASM("MRS     R6, PRIMASK") in 'hdudispfoscpua.c' and check value R6 is equal to 0x0
	#COMMENT	     in order to verify  BIT 0 of PRIMASK register after interrupt is enabled.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    			init          ev
    #-------------------------------------------------------------------------------  
    # RVAL	R0					0x0		&temp_NVIC_INT_CTRL	  
    # RVAL	R1					0x0		0x1	 
    # RVAL  R5      			0x1		0x0
    # RVAL  R6					0x1		0x0        
    # VAR temp_NVIC_SYSPRI14 	0x0 	NVIC_PENDSV_PRI
    # VAR temp_NVIC_INT_CTRL 	0x0 	NVIC_PENDSVSET
    # VAR Os_running			FALSE 	TRUE
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    
    #--To set PRIMASK register*/
	__ASM("CPSID   I");
	
	#--To check primask register is set*/
	__ASM("MRS     R6, PRIMASK");
	
	temp_NVIC_INT_CTRL = 0;
	temp_NVIC_SYSPRI14 = 0;
	Os_running = FALSE;
                    
    #-- Function Under Test
    OsStartHighRdy()  
        
        __ASM("MOV     R5, 1")
	#--To check PSP is set to DEFAULT_VAL*/
	__ASM("MRS     R5, PSP");
	
	#--To check BIT 0 of PRIMASK register after interrupt is enabled*/
	__ASM("MRS     R6, PRIMASK");
	
 TEST_6:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'PendSVHandlerFlight' does the following when PSP is 0.
    #COMMENT    1)-	Disable Interrupt request by setting the PRIMASK special register value.
    #COMMENT    2)-	Read PSP register value and write it to R0.
    #COMMENT    3)-	Forward branch to 'PendSVHandler_nosave' if R0 is zero.
    #COMMENT    4)sets highest priority task ready to execute into the current TCB 
    #COMEMNT      (i.e Os_tcb_cur = Os_tcb_high_rdy) when branch PendSvHandler_NoSave is invoked.
    #COMMENT	-	Load the current TCB address to R0
	#COMMENT	-	Load the address of highest priority task ready to execute to R1
	#COMMENT	-	Load the address content in R1 to R2
	#COMMENT	-	write R2 to address R0 content
	#COMEMNT	-	Load the address content in R2 to R0
	#COMMENT	-	(i.e - Set Stack Pointer (R0) = Os_tcb_high_rdy ->os_tcb_stkptr)
	#COMMENT	-	Increment R0 Before each access and restore the register 
	#COMMENT	-	S16- S31 from the Incremented address 
	#COMMENT	-	Increment R0 Before each access and load the register 
	#COMEMNT	-	R4 - R11 from the Incremented address 
	#COMMENT	-	Load PSP with the new stack pointer (R0)
	#COMMENT	-	Load the link register = link register bitwise or EXCEPTION_RETURN
	#COMMENT	-	Enable Interrupt request by clearing the PRIMASK special register value.
	#COMMENT
	#COMMENT Note : PendSVHandlerFlight is invoked during task scheduling and is used for context switch. 
	#COMMENT Above functionality is tested by calling OsStart(). HwInit() and OsInit() are called 
	#COMMENT before OsStart to initialize hardware related components and to create idle task.
	#COMMENT 
    #COMEMNT</TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>  
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-001
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-002
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-003
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-007
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 16
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at switch statement in 'hdudispfstartupstm32f746xx.s' file and and add testcase_number in watch window and enter value of 
    #COMMENT 		  testcase_number as '6'.
	#COMMENT Step 2 : Set breakpoint at function 'OsStart' in 'hdudispfucos.c' and press F5
	#COMMENT Step 3 : Set breakpoint at function 'OsStartHighRdy' in 'hdudispfucos.c' and press F5 to enter function under test.
	#COMMENT Step 4 : Set breakpoint at line number 279 'in 'hdudispfoscpua.s' where  PSP register value is read and written to R0.
	#COMMENT          and press F5.Observe value of R0 is equal to 0x0.
	#COMMENT Step 5:  Press F5 and observe control switches to label PendSvHandler_NoSave and observe context
    #COMMENT		  switch to idle task once control reaches last instruction. 
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    			init          ev
    #------------------------------------------------------------------------------- 
    # Register values are not expected as it hold stack address which keeps on changing
    # for each run . LLR is verified manually by observing context switch to idle task 
    # when no other higher priority task is created when PSP is 0x0.
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    #--To test LLR "hdudispfoscpua-PendSVHandlerFlight-LLR-007" i.e when idle task is created and scheduled for first time                   
    __ASM("MOV R7,0x1")
    #To initialise hardware related component
    HwInit();
    #To create Idle task
    OsInit();
    #Allows OS to manage the tasks that have been created. 
    OsStart();
    #Function under Test PendSVHandlerFlight() is invoked when PendSv exception is triggered while context
    #switching
                                       
 TEST_7:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT To test whether the function 'PendSVHandlerFlight' does the following
    #COMMENT - Disable Interrupt request by setting the PRIMASK special register value.
    #COMMENT - Read PSP register value and write it to R0.
    #COMMENT - R0 is not equal to zero.
    #COMMENT - Save register R4-R11 on process stack.
    #COMMENT - Save floating point register S16-S31 on process stack.
    #COMMENT - load the Stack pointer to the TCB stack. 
    #COMMENT - Load the current TCB address to R0.
	#COMMENT - Load the address of highest priority task ready to execute to R1 .
	#COMMENT - Load the address content in R1 to R2	.
	#COMMENT - write R2 to address R0 content .
	#COMEMNT - Load the address content in R2 to R0	
	#COMMENT  (i.e - Set Stack Pointer (R0) = Os_tcb_high_rdy ->os_tcb_stkptr)
	#COMMENT - Increment R0 Before each access and restore the register 
	#COMMENT - S16- S31 from the Incremented address 
	#COMMENT - Increment R0 Before each access and load the register 
	#COMEMNT   R4 - R11 from the Incremented address 
	#COMMENT - Load PSP with the new stack pointer (R0)
	#COMMENT - Load the link register = link register bitwise or M_FOUR
	#COMMENT - Enable Interrupt request by clearing the PRIMASK special register value.
	#COMMENT
    #COMMENT Note : PendSVHandlerFlight is invoked during task scheduling and is used for context switch. Above functionality is 
    #COMMENT tested by calling OsStart(). HwInit(),OsInit() and InitInit() are called before OsStart to initialize 
	#COMMENT hardware related components, to create idle task and init tasks respectively.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-001
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-002
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-003
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-004
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-005
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-006
    #COMMENT hdudispfoscpua-PendSVHandlerFlight-CB-LLR-007
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 10
    #COMMENT  Class 11
    #COMMENT  Class 12
    #COMMENT  Class 13
    #COMMENT  Class 14
    #COMMENT  Class 15
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at switch statement in 'hdudispfstartupstm32f746xx.s' file and and add testcase_number in watch window and enter value of 
    #COMMENT 		  testcase_number as '7'.
	#COMMENT Step 2 : Set breakpoint at function 'OsStart' in 'hdudispfucos.c' and press F5.
	#COMMENT Step 3 : Set breakpoint at function 'OsStartHighRdy' in 'hdudispfucos.c' and press F5 to enter function under test.
	#COMMENT Step 5 : Set breakpoint at line number 322 'in 'hdudispfoscpua.s' where  PSP register value is read and written to R0.
	#COMMENT          and press F8.Observe value of R0 is not equal to 0x0.
	#COMMENT Step 6 : Press F5 and observe context switch to InitTask once control reaches last instruction.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    init          ev
    #-------------------------------------------------------------------------------  
    # Register values are not expected as it hold stack address which keeps on changing
    #for each run. LLR is verified manually by observing context switch to high priority
    #task when 2 tasks are created(Idle and Init task)when PSP is other than 0x0.
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here 
    #--To test LLRs of 'PendSvHandler' ie when idle and Init tasks are created and scheduled
    __ASM("MOV R7,0x1");
    #To initialise hardware related component
   	HwInit();
   	#To create Idle task(Low priority task)
   	OsInit()
   	#To create Init task
   	InitInit();
   	#Allows os to manage created tasks
	OsStart();
	#Function under Test PendSvHandler() is invoked when PendSv exception is triggered while context
    #switching
         
TESTEND:

#Stub definition section