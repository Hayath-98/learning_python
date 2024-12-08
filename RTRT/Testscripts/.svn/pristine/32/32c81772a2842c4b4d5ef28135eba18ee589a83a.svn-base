#FILEHEADER hdudispfstartupstm32f746xx,Source Code Ver : 1.2,TestScript Ver : 1.3
# --------------------------------------------------------------------------------
#-- Author Name         : Neha Rai R
#--
#-- Tested module       : hdudispfstartupstm32f746xx.s
#--
#-- Tested CSUs         : ResetHandler,
#--			  			  DefaultHandler,
#--			  			  GPfnVectors
#--			  
#-- Test script file    : TSF_hdudispfstartupstm32f746xx.s
#-- History
#
#-- VERSION        WHEN           WHO          		WHAT
#-- -------      ----------     --------       	-------------
#--  1.1       	 12.10.2017	   Neha Rai R		Created the TSF.
#--  1.2         11.11.2017    Neha Rai R     	Updated as per #PR100171
#--  1.3         14.11.2017    Neha Rai R     	Updated as per #PR100171
# --------------------------------------------------------------------------------
# Include Files Section

#Global variable Section

   	  #COMMENT Author Name      :Neha Rai R
      #COMMENT
      #COMMENT File Name        :TSF_hdudispfstartupstm32f746xx.s 
      #COMMENT
      #COMMENT Tested Functions :ResetHandler,
	  #COMMENT			  		 DefaultHandler,
	  #COMMENT			  		 GPfnVectors     
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
	  #COMMENT In function 'ResetHandler', sets the stack pointer. 
      #COMMENT
      #COMMENT Class 2
      #COMMENT In function 'ResetHandler', data segment initializers are copied from flash to SRAM.
      #COMMENT 
	  #COMMENT Class 3
	  #COMMENT In function 'ResetHandler', bss segment is filled with ZERO. 
      #COMMENT 
	  #COMMENT Class 4
	  #COMMENT In function 'ResetHandler', Vector_tab_sel to two to load flight application vector table address is set
      #COMMENT 
	  #COMMENT Class 5
	  #COMMENT In function 'ResetHandler', SystemInit function is called. 
      #COMMENT       
	  #COMMENT Class 6
	  #COMMENT Function 'ResetHandler' calls static constructors to invoke function pointers during Startup. 
      #COMMENT          
	  #COMMENT Class 7
	  #COMMENT In function 'ResetHandler', DisplayMain function is called.
      #COMMENT  
	  #COMMENT Class 8
	  #COMMENT Function 'DefaultHandler', enters an infinite loop when processor receives unexpected interrupt 
      #COMMENT  
 	  #COMMENT Class 9
	  #COMMENT In function 'GPfnVectors', vector table for Cortex M7 is initialised. 
	  #COMMENT
      #COMMENT Invalid Class(es)
      #COMMENT  None.
      #COMMENT </ECD> 
#------------------------------------------------------------------------------- 
TESTSTART:
 
#Macro definitions

   #None
        
#-------------------------------------------------------------------------------   
                    
TEST_1:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' sets the stack pointer
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 1
    #COMMENT  Class 2
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1 : Set breakpoint at line #89 in 'hdudispfstartupstm32f746xx.s' file where R1 is set to 0.
    #COMMENT Step 2 : Observe value of sp which is equal to _estack( i.e, 0x20050000) value
	#COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    	init          ev
    #-------------------------------------------------------------------------------
    # RVAL	sp			0x0			0x20050000
    #-------------------------------------------------------------------------------  
                    
    #--Test script start here
    ldr   sp, =_estack
    
    #-- CSU Under Test    
    ResetHandler();
        
TEST_2:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' copies the data segment initializers from flash to SRAM.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-002
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 1
    #COMMENT  Class 2
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
    #COMMENT Step 1  : Set breakpoint at line #90 in 'hdudispfstartupstm32f746xx.s' file where function branch to 'LoopCopyDataInit'
    #COMMENT	       and observe value of R1 which is equal to #0. Also observe intial values of register R0,R3 and R2.
    #COMMENT           Below mentioned steps has to be followed to verify Low Level Requirement.
    #COMMENT Step 2  : Set breakpoint at line #99 and observe the control hits the label 'LoopCopyDataInit'
    #COMMENT Step 3  : Set breakpoint at line #103 and observe value of R0,R3 and R2 which is equal to _sdata(0x20000000), _edata(0x20000428)
    #COMMENT           and 0x20000000 respectively.
	#COMMENT Step 4  : Set breakpoint at line #105 and observe the value of R4 register which is equal to 0xFFFFFFFF80000000.
	#COMMENT           By this it can be observed that 29th bit of APSR register is 0 which indicates Carry Flag is Zero(C=0).        
	#COMMENT Step 5  : Press F5 and observe control hits 'CopyDataInit'. Observe previous values of R0,R1 and R3
 	#COMMENT Step 6  : Press F5 and observe value of R3 which will be loaded with the address _sidata.
 	#COMMENT Step 7  : Observe previous values of R3. Press F5 and observe the change in value of R3 is equal to Zero
 	#COMMENT           i.e, content at the address [R3, R1].
 	#COMMENT Step 8  : To verify whether the content of R3 is stored at location [R0,R1], change the value of R3 (say for instance #7).
 	#COMMENT           Press F5 until the control reaches line #96 where register R6 is loaded with content at address [R0,R1]
 	#COMMENT           and observe the change in value of R6 which is equal to #7.
 	#COMMENT Step 9  : Press F5 and observe value of register R1 changed to #4.
 	#COMMENT Step 10 : Set breakpoint at line #106 and observe the value of R2 and R3 which are same hence the control comes out of the 
 	#COMMENT           label CopyDataInit after looping for 266 times.Also observe the value of R4 register which is equal to 0x60000000.
 	#COMMENT           By this it can be observed that 29th bit of APSR register is 1 which indicates Carry Flag is One(C=1).
 	#COMMENT Step 11 : Set breakpoint at line #107 and observe the value of Register R2 which is equal to _sbss(0x20000428).
 	#COMMENT           Press F5 and observe the control switches to label 'LoopFillZerobss'
 	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
 	
 	ResetHandler :
    # RVAL  R1      		0x0     	0x0
    
    LoopCopyDataInit : 
    # RVAL  R0      		0x0     	0x20000000
    # RVAL  R3      		0x0     	0x20000428
    # RVAL  R2      		0x0     	0x20000000
    # RVAL  R4      		0x0     	0xFFFFFFFF80000000
    
    CopyDataInit : 
    # RVAL  R3      		0x0     	_sidata
    # RVAL  R6      		0x0     	0x7
    # RVAL  R1      		0x0     	0x4
    # RVAL  R4      		0x0     	0x60000000
    # RVAL  R2      		0x0     	_sbss
    
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    b  LoopCopyDataInit
    
    #-- CSU Under Test
    ResetHandler();
        
TEST_3:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' fills ZERO to the bss segment
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-003
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 3
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Set breakpoint at line #117 and observe the value of Register R3 which is equal to _ebss.
	#COMMENT Step 2 : Set breakpoint at line #119 and observe the value of R5 register which is equal to 0xFFFFFFFF80000000. 
	#COMMENT          By this it can be observed that 29th bit of APSR register is 0 which indicates Carry Flag is Zero(C=0).   
	#COMMENT Step 3 : Press F5 and observe control hits 'FillZerobss'i.e, when starting and ending address of
 	#COMMENT          .bss section are not equal. Observe previous values of R2 and R3 registers
	#COMMENT Step 4 : Press F5 and observe the value of R3 which is equal to zero.
	#COMMENT Step 5 : Press F5 and observe the value of R2 which is equal to (0x2000042C).
 	#COMMENT Step 6 : Set breakpoint at line #129 and observe the value of R2 and R3 which are same hence the control comes out of the 
 	#COMMENT          label 'LoopFillZerobss' after looping for 8 times.Also observe the value of R5 register which is equal to 0x60000000.
 	#COMMENT          By this it can be observed that 29th bit of APSR register is 1 which indicates Carry Flag is One(C=1).
 	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    
    LoopFillZerobss : 
    # RVAL	R0				0x0			_ebss
    # RVAL  R5      		0x0     	0xFFFFFFFF80000000
    
    FillZerobss : 
    # RVAL  R3      		0x0     	0x0
    # RVAL  R2      		0x0     	0x2000042C
    # RVAL  R5      		0x0     	0x60000000
    #
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    LoopFillZerobss:
    
    #-- CSU Under Test
    ResetHandler();

TEST_4:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' fills ZERO to the bss segment
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-004
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 4
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Observe the value of Register previous value of R0 and R1
	#COMMENT Step 2 : Set breakpoint at line #124 and observe the value of R1 register which is loaded with value in Vector_tab_sel. 
	#COMMENT Step 3 : Press F5 and observe value of R0 is equal to 2 
 	#COMMENT Step 4 : Add Vector_tab_sel to watch window and press F5 to observe the value of Vector_tab_sel changing to 2
 	#COMMENT          which verifies storing of value in register R0 to variable Vector_tab_sel.
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    
    movs r0, #2 
    # RVAL	R0				0x0			0x2
    
    str r0, [r1]
    # Vector_tab_sel         0x0            0x2
    
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    ldr r1, =Vector_tab_sel
    
    #-- CSU Under Test
    ResetHandler();

        
TEST_5:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' calls the function SystemInit to initialize embedded FLASH interface
    #COMMENT and updates the system clock(frequency variable) .
    #COMMENT
    #COMMENT The function 'ResetHandler' calls static constructors to invoke function pointers during Startup.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-005
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-006
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT Class 5
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Set breakpoint at line #129 and press F5 to enter into the function SystemInit in file "hdulibsystemstm32f7xx.c"
	#COMMENT Step 2 : Now Press F5 and observe the value of RCC->CR which is equal to HEX_ONE. HSION bit of RCC->CR is set to 1.
	#COMMENT Step 3 : Set breakpoint at line #60 in function SystemInit of file 'hdulibsystemstm32f7xx.c'. Now keep pressing F5 and observe the
	#COMMENT          control returns to hdudispfstartupstm32f746xx.s
	#COMMENT Step 4 : Function call static constructors to invoke function pointers during Startup when the control hits the label
	#COMMENT          __libc_init_array
	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    
    # RVAL	RCC->CR			0x0			HEX_ONE
    
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    bl  SystemInit       
    bl  __libc_init_array
    
    ResetHandler();

TEST_6:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'ResetHandler' sets the stack pointer
    #COMMENT The function 'DefaultHandler' enters an infinite loop when processor receives
    #COMMENT unexpected interrupt(in this case 'HardFaultHandler')
    #COMMENT The function 'GPfnVectors' initializes the vector table for Cortex M7.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-ResetHandler-DB-LLR-007
    #COMMENT hdudispfstartupstm32f746xx-DefaultHandler-DB-LLR-001
    #COMMENT hdudispfstartupstm32f746xx-GPfnVectors-DB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT Class 6
    #COMMENT Class 7
    #COMMENT Class 8
    #COMMENT Class 9
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Set the breakpoint at switch statement in 'hdudispfmain.c' file and add testcase_number to watch window and 
    #COMMENT          enter value of testcase_number as 1 in watch window.
	#COMMENT Step 2 : Set the breakpoint at line #226 in 'hdudispfmain.c' where 'p' is stored with unaligned memory address which raises
	#COMMENT          hard fault exception upon accessing nonexistent memory at address 0xFFFFFFFC
	#COMMENT          Now press F5 and observe the control enters to HardFaultHandler
 	#COMMENT Step 3 : To test function 'DefaultHandler', function definition of 'HardFaultHandler' can be removed from 
 	#COMMENT          'hdudispfmain.c' file.
 	#COMMENT Step 4 : Follow steps 1,2 and observe control hits 'DefaultHandler'.
 	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    #testcase_number         0            1
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    bl  DisplayMain   
    
    #-- CSU Under Test
    ResetHandler(); 
    DefaultHandler();

TEST_7:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'GPfnVectors' initializes the vector table for Cortex M7.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-GPfnVectors-DB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT Class 9
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Set the breakpoint at switch statement in 'hdudispfmain.c' file and add testcase_number to watch window and 
    #COMMENT          enter value of testcase_number as 2 in watch window.
	#COMMENT Step 2 : Set the breakpoint at line #140 in 'hdudispfmain.c' where temp is divided by Zero which raises usage fault exception.
	#COMMENT          Now press F5 and observe the control enters to UsageFaultHandler
	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    #testcase_number         0            2
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    bl  DisplayMain   
    
    #-- CSU Under Test
    DefaultHandler();  

TEST_8:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'GPfnVectors' initializes the vector table for Cortex M7.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfstartupstm32f746xx-GPfnVectors-DB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT Class 9
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES> 
 	#COMMENT Step 1 : Set the breakpoint at switch statement in 'hdudispfmain.c' file and add testcase_number to watch window and 
    #COMMENT          enter value of testcase_number as 3 in watch window.
	#COMMENT Step 2 : Set the breakpoint at line #162 in 'hdudispfmain.c'. The instruction at line #116 raises BUS fault exception
	#COMMENT          because a write to an invalid address is attempted.
	#COMMENT Step 3 : Now press F5 and observe the control enters to BusFaultHandler. Observe the initial value of temp2 register 
	#COMMENT          in watch window which has the value of SCB->CFSR register.   
	#COMMENT Step 4 : Set breakpoint at line #171 where the infinite while loop ends. Now observe the value of temp2 register, the 10th
	#COMMENT          bit will be set indicating imprecise bus fault which means an attempt to write to an invalid address.
 	#COMMENT  
 	#COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init          ev
    #-------------------------------------------------------------------------------
    # testcase_number         0            3
    # temp2                   0x0     	   0x400
    #-------------------------------------------------------------------------------   
                    
    #--Test script start here
    bl  DisplayMain   
    
    #-- CSU Under Test
    DefaultHandler();  
    
TESTEND:

#Stub definition section