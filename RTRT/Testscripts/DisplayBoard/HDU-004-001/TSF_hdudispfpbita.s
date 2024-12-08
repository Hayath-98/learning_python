#FILEHEADER hdudispfpbita,Source Code Ver : 1.1,TestScript Ver : 1.2
# --------------------------------------------------------------------------------
#-- Author Name         : LakshmiKumari K
#--			 			  
#-- Tested module       : hdudispfpbita.s
#-- Tested CSUs         : AluTest
#--			  
#-- Test script file    : TSF_hdudispfpbita.s
#-- History

#-- VERSION      WHEN           WHO             	WHAT
#-- -------     ----------     	--------       		-------------
#--  1.1       	31.10.2017		LakshmiKumari K 	Created the TSF.s
#--	 1.2       	10.11.2017		LakshmiKumari K 	Updated as per PR 100171							
# --------------------------------------------------------------------------------
# Include Files Section

#Global variable Section
	T_BOOL Proc_test_res = FALSE;
 
 
    #COMMENT Author Name      :LakshmiKumari K
    #COMMENT				   
    #COMMENT File Name        :TSF_hdudispfpbita.s 
    #COMMENT
    #COMMENT Tested Functions :AluTest
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
	#COMMENT Valid Class(es)
	#COMMENT Class 1
	#COMMENT In function 'AluTest', carry_flag test is performed.
	#COMMENT 
	#COMMENT Class 2
	#COMMENT In function 'AluTest', carry_flag test is not performed.
	#COMMENT 
	#COMMENT Class 3
	#COMMENT In function 'AluTest', result (R2) obtained by addition operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_ELEVEN. 
    #COMMENT
    #COMMENT Class 4
	#COMMENT In function 'AluTest', result (R2) obtained by addition operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_ELEVEN. 
	#COMMENT 
    #COMMENT Class 5
	#COMMENT In function 'AluTest', zero_flag test is performed.
	#COMMENT
	#COMMENT Class 6
	#COMMENT In function 'AluTest', zero_flag test is not performed.
    #COMMENT 
    #COMMENT Class 7
 	#COMMENT In function 'AluTest', status of carry flag is stored from APSR into R4(Result).
 	#COMMENT
    #COMMENT Class 8
 	#COMMENT In function 'AluTest', obtained result(R4) is equal to value CONST_CARRY_FLAG .
  	#COMMENT
    #COMMENT Class 9
 	#COMMENT In function 'AluTest', obtained result(R4) is not equal to value CONST_CARRY_FLAG .	  
    #COMMENT 
    #COMMENT Class 10
	#COMMENT In function 'AluTest', overflow_flag test is performed.
	#COMMENT
	#COMMENT Class 11
	#COMMENT In function 'AluTest', overflow_flag test is not performed.
    #COMMENT 
    #COMMENT Class 12
 	#COMMENT In function 'AluTest', status of overflow_flag is stored from APSR into R4(Result).
 	#COMMENT
    #COMMENT Class 13
 	#COMMENT In function 'AluTest', obtained result(R4) is equal to value CONST_ZERO_FLAG.
  	#COMMENT
    #COMMENT Class 14
 	#COMMENT In function 'AluTest', obtained result(R4) is not equal to value CONST_ZERO_FLAG.	
 	#COMMENT
    #COMMENT Class 15
	#COMMENT In function 'AluTest', subtract test is performed.
	#COMMENT
	#COMMENT Class 16
	#COMMENT In function 'AluTest', subtract test is not performed.
    #COMMENT 
    #COMMENT Class 17
 	#COMMENT In function 'AluTest', status of zero flag is stored from APSR into R4(Result).
 	#COMMENT
   	#COMMENT Class 18
 	#COMMENT In function 'AluTest', obtained result(R4) is equal to value CONST_OVERFLOW_FLAG .
  	#COMMENT
    #COMMENT Class 19
 	#COMMENT In function 'AluTest', obtained result(R4) is not equal to value CONST_OVERFLOW_FLAG . 	  
 	#COMMENT
	#COMMENT Class 20
	#COMMENT In function 'AluTest', multiply test is performed.
	#COMMENT
	#COMMENT Class 21
	#COMMENT In function 'AluTest', multiply test is not performed.
	#COMMENT 
	#COMMENT Class 22
	#COMMENT In function 'AluTest', result (R1) obtained by subtract operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_ONE. 
	#COMMENT
	#COMMENT Class 23
	#COMMENT In function 'AluTest', result (R1) obtained by subtract operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_ONE. 
	#COMMENT 
 	#COMMENT Class 24
	#COMMENT In function 'AluTest', division test is performed.
	#COMMENT
	#COMMENT Class 25
	#COMMENT In function 'AluTest', division test is not performed.
	#COMMENT 
	#COMMENT Class 26
	#COMMENT In function 'AluTest', result (R1) obtained by multiply operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_SIX. 
    #COMMENT
    #COMMENT Class 27
	#COMMENT In function 'AluTest', result (R1) obtained by multiply operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_SIX. 
	#COMMENT 
 	#COMMENT Class 28
	#COMMENT In function 'AluTest',  logicaland test  is performed.
	#COMMENT
	#COMMENT Class 29
	#COMMENT In function 'AluTest',  logicaland test  is not performed.
	#COMMENT 
	#COMMENT Class 30
	#COMMENT In function 'AluTest', result (R1) obtained by division operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_TWO. 
    #COMMENT
    #COMMENT Class 31
	#COMMENT In function 'AluTest', result (R1) obtained by division operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_TWO. 
	#COMMENT
 	#COMMENT Class 32
	#COMMENT In function 'AluTest',  logicalor test  is performed.
	#COMMENT
	#COMMENT Class 33
	#COMMENT In function 'AluTest',  logicalor test  is not performed.
	#COMMENT 
	#COMMENT Class 34
	#COMMENT In function 'AluTest', result (R3) obtained by  logical AND  operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_ONE. 
    #COMMENT
    #COMMENT Class 35
	#COMMENT In function 'AluTest', result (R3) obtained by  logical AND  operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_ONE. 
	#COMMENT
 	#COMMENT Class 36
	#COMMENT In function 'AluTest', exlusiveor test is performed.
	#COMMENT
	#COMMENT Class 37
	#COMMENT In function 'AluTest', exlusiveor test is not performed.
	#COMMENT 
	#COMMENT Class 38
	#COMMENT In function 'AluTest', result (R3) obtained by  logical OR  operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_SEVENTEEN. 
    #COMMENT
    #COMMENT Class 39
	#COMMENT In function 'AluTest', result (R3) obtained by  logical OR  operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_SEVENTEEN. 
	#COMMENT
	#COMMENT Class 40
	#COMMENT In function 'AluTest', result (R3) obtained by  logical XOR  operation on 2 registers (R1 ,R2)is 
	#COMMENT equal to value CONST_SIXTEEN . 
    #COMMENT
    #COMMENT Class 41
	#COMMENT In function 'AluTest', result (R3) obtained by  logical XOR  operation on 2 registers (R1 ,R2)is not 
	#COMMENT equal to value CONST_SIXTEEN . 
	#COMMENT
	#COMMENT Class 42
	#COMMENT In function 'AluTest', Test Result is pass (i.e Proc_test_res = TRUE ).
    #COMMENT
    #COMMENT Class 43
	#COMMENT In function 'AluTest', Test Result is fail (i.e Proc_test_res = FALSE ).
	#COMMENT	  
    #COMMENT Invalid Class(es)
    #COMMENT None
	#COMMENT </ECD>
#------------------------------------------------------------------------------- 
TESTSTART:      
 #Macro definitions

    .equ CONST_CARRY_FLAG,     0x20000000
    .equ CONST_ZERO_FLAG,      0x60000000
    .equ CONST_OVERFLOW_FLAG,  0x90000000
    .equ CONST_PATTERN,        0x7FFFFFFF
    .equ CONST_HEX_ONE,        0x01
    .equ CONST_ONE,            0x1
    .equ CONST_TWO,            0x2
    .equ CONST_THREE,          0x3
    .equ CONST_FOUR,           0x4
    .equ CONST_FIVE,           0x5
    .equ CONST_SIX,            0x6
    .equ CONST_ELEVEN,         0xB
    .equ CONST_SIXTEEN,        0x10
    .equ CONST_SEVENTEEN,      0x11
#-------------------------------------------------------------------------------   
                    
TEST_1:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' performs below mentioned tests
    #COMMENT successfully and Proc_test_res is set to TRUE.
    #COMMENT 1)carry_flag test
    #COMMENT 2)zero_flag test
    #COMMENT 3)overflow_flag test
    #COMMENT 4)subtract test
    #COMMENT 5)multiply test
    #COMMENT 6)division test
    #COMMENT 7)logicaland test
    #COMMENT 8)logicalor test 
    #COMMENT 9)exlusiveor test
    #COMMENT when
    #COMMENT 1)Addition operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE and 
    #COMMENT   result stored in R2 equals to CONST_ELEVEN.
    #COMMENT 2)Addition operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE and 
    #COMMENT   result stored in R2 .Status of carry flag is stored from APSR to R4 and  gives result(R4) equals to CONST_CARRY_FLAG.     
    #COMMENT 3)Addition operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE,R2 is compared with CONST_ELEVEN
    #COMMENT   and status of zero flag is stored APSR to R4 and result(R4)equals to CONST_ZERO_FLAG.   
    #COMMENT 4)Addition operation is performed on registers(R1,R2) with operands  CONST_PATTERN  and  CONST_PATTERN,
    #COMMENT   status of zero flag is stored from APSR to R4 and  R4 equals to CONST_OVERFLOW_FLAG.      
    #COMMENT 5)Subtract operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE
    #COMMENT   and  result stored in R1 equals to CONST_ONE.    
    #COMMENT 6)Multiply operation is performed on registers(R1,R2) with operands CONST_THREE and CONST_TWO 
    #COMMENT   and  result stored in R1 equals to CONST_SIX. 
    #COMMENT 7)Division operation is performed on registers(R1,R2) with operands CONST_FOUR and CONST_TWO
    #COMMENT   and  result stored in R1 equals to CONST_TWO.
    #COMMENT 8)Logical AND operation is performed on registers(R1,R2) with operands CONST_HEX_ONE and CONST_SEVENTEEN
    #COMMENT   and  result stored in R1 equals to CONST_ONE. 
    #COMMENT 9)Logical OR operation is performed on registers(R1,R2) with operands CONST_SIXTEEN and CONST_HEX_ONE
    #COMMENT   and result stored in R1 equals to CONST_SEVENTEEN.
    #COMMENT 10)Logical XOR operation is performed on registers(R1,R2) with operands CONST_SEVENTEEN and CONST_HEX_ONE
    #COMMENT   and result stored in R3 equals to CONST_SIXTEEN and branches to Testresult .
    #COMMENT 11)Testresult operation is performed on registers(R4,R2) with operands CONST_ONE and (address of Proc_test_res) 
    #COMMENT   and result stored in the global variable Proc_test_res to TRUE by writing R4 to content of R2 address    
    #COMMENT </TD>                
   
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-001
    #COMMENT hdudispfpbita-AluTest-DB-LLR-002
    #COMMENT hdudispfpbita-AluTest-DB-LLR-003
    #COMMENT hdudispfpbita-AluTest-DB-LLR-004
    #COMMENT hdudispfpbita-AluTest-DB-LLR-005
    #COMMENT hdudispfpbita-AluTest-DB-LLR-006
    #COMMENT hdudispfpbita-AluTest-DB-LLR-007
    #COMMENT hdudispfpbita-AluTest-DB-LLR-008
    #COMMENT hdudispfpbita-AluTest-DB-LLR-009
    #COMMENT hdudispfpbita-AluTest-DB-LLR-010
    #COMMENT hdudispfpbita-AluTest-DB-LLR-011
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 1
    #COMMENT  Class 3
    #COMMENT  Class 5
    #COMMENT  Class 7
    #COMMENT  Class 8
    #COMMENT  Class 10
    #COMMENT  Class 12
    #COMMENT  Class 13
    #COMMENT  Class 15
    #COMMENT  Class 17
    #COMMENT  Class 18
    #COMMENT  Class 20
    #COMMENT  Class 22
    #COMMENT  Class 24
    #COMMENT  Class 26
    #COMMENT  Class 28
    #COMMENT  Class 30
    #COMMENT  Class 32
    #COMMENT  Class 34
    #COMMENT  Class 36
    #COMMENT  Class 38
    #COMMENT  Class 40
    #COMMENT  Class 42
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 1.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.
	#COMMENT Step 1  : Check the initial value of R1,R2,R3,R4 ,Proc_test_res ,testcase_number and Testcase_result in watch window.
	#COMMENT Step 2  : Set breakpoint at line number 80 in source 'hdudispfpbita.s' where R2 is compared with CONST_ELEVEN.
	#COMMENT           Check R2 is equal to CONST_ELEVEN in watch window.
	#COMMENT Step 3  : Set breakpoint at line number 87 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating carry_flag test is performed.
	#COMMENT Step 4  : Set breakpoint at line number 91 in source 'hdudispfpbita.s' where R4 is compared with CONST_CARRY_FLAG.
	#COMMENT           Check R4 is equal to CONST_CARRY_FLAG in watch window.
	#COMMENT Step 5  : Set breakpoint at line number 110 in source 'hdudispfpbita.s'. Observe control hits the breakpoint 
	#COMMENT           indicating zero_flag test is performed.      
	#COMMENT Step 6  : Set breakpoint at line number 115 in source 'hdudispfpbita.s' where R4 is compared with CONST_ZERO_FLAG.
	#COMMENT           Check R4 is equal to CONST_ZERO_FLAG in watch window.
	#COMMENT Step 7  : Set breakpoint at line number 99 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating overflow_flag test is performed.        
	#COMMENT Step 8  : Set breakpoint at line number 103 in source 'hdudispfpbita.s' where R4 is compared with
	#COMMENT           CONST_OVERFLOW_FLAG. Check R4 is equal to CONST_OVERFLOW_FLAG in watch window.
	#COMMENT Step 9  : Set breakpoint at line number 124 in source 'hdudispfpbita.s'.Observe control hits the breakpoint
	#COMMENT           indicating subtract test is performed.        
	#COMMENT Step 10 : Set breakpoint at line number 127 in source 'hdudispfpbita.s' where R1 is compared with CONST_ONE.
	#COMMENT           Check R1 is equal to CONST_ONE in watch window. 
	#COMMENT Step 11 : Set breakpoint at line number 135 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating multiply test is performed.        
	#COMMENT Step 12 : Set breakpoint at line number 138 in source 'hdudispfpbita.s' where R1 is compared with CONST_SIX.
	#COMMENT           Check R1 is equal to CONST_SIX in watch window. 
	#COMMENT Step 13 : Set breakpoint at line number 146 in source 'hdudispfpbita.s'.Observe control hits the breakpoint
	#COMMENT           indicating division test is performed.        
	#COMMENT Step 14 : Set breakpoint at line number 149 in source 'hdudispfpbita.s' where R1 is compared with CONST_TWO.
	#COMMENT           Check R1 is equal to CONST_TWO in watch window
	#COMMENT Step 15 : Set breakpoint at line number 157 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating logicaland test is performed.        
	#COMMENT Step 16 : Set breakpoint at line number 160 in source 'hdudispfpbita.s' where R3 is compared with CONST_ONE.
	#COMMENT           Check R3 is equal to CONST_ONE in watch window.
	#COMMENT Step 17 : Set breakpoint at line number 169 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating logicalor test is performed.        
	#COMMENT Step 18 : Set breakpoint at line number 172 in source 'hdudispfpbita.s' where R3 is compared with CONST_SEVENTEEN.
	#COMMENT           Check R3 is equal to CONST_SEVENTEEN in watch window.
	#COMMENT Step 19 : Set breakpoint at line number 181 in source 'hdudispfpbita.s'.Observe control hits the breakpoint 
	#COMMENT           indicating exlusiveor test is performed.        
	#COMMENT Step 20 : Set breakpoint at line number 184 in source 'hdudispfpbita.s' where R3 is compared with CONST_SIXTEEN. 
	#COMMENT           Check R3 is equal to CONST_SIXTEEN in watch window.
	#COMMENT Step 21 : Set breakpoint at line number 191 in source 'hdudispfpbita.s'.Observe control hits the breakpoint indicating 
	#COMMENT           Testresult evaluation is performed. 
	#COMMENT Step 22 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 1.Observe control hits the breakpoint indicating 
	#COMMENT           AluTest is successful.
	#COMMENT Step 23 : Set breakpoint at break statement in case 1.Observe values of Proc_test_res is (TRUE)1 and Testcase_result 
	#COMMENT			is (PASSED)1 in watch window indicating success of AluTest and test result is pass.
	#COMMENT </SCRIPT_NOTES> 
  
    #-------------------------------------------------------------------------------         
    #VAR    name    	init    ev
    #------------------------------------------------------------------------------  

    # RVAL	R1			0x0		0x6
	# RVAL  R2      	0x0     0xB

	carry_flag:
	# RVAL	R1			0x0		0x6
	# RVAL  R2      	0x0     0xB
	# RVAL  R4      	0x0     0x20000000

	zero_flag:
	# RVAL	R1			0x0		0x6
	# RVAL  R2      	0x0     0xB
	# RVAL  R4      	0x0     0x60000000
	
	overflow_flag:
	# RVAL	R1			0x0		0x7FFFFFFF
	# RVAL  R2      	0x0     0x7FFFFFFF
	# RVAL  R4      	0x0     0x90000000

	subtract:
	# RVAL	R1			0x0		0x1
	# RVAL  R2      	0x0     0x5  

	multiply:
	# RVAL	R1			0x0		0x6
	# RVAL  R2      	0x0     0x2  

	division:
	# RVAL	R1			0x0		0x2
	# RVAL  R2      	0x0     0x2	

	logicaland:
	# RVAL	R1			0x0		0x01
	# RVAL  R2      	0x0     0x17
	# RVAL  R3      	0x0     0x1

	logicalor:
	# RVAL	R1			0x0		0x16
	# RVAL  R2      	0x0     0x1
	# RVAL  R3      	0x0     0x17	

	exlusiveor:
	# RVAL	R1			0x0		0x17
	# RVAL  R2      	0x0     0x1
	# RVAL  R3      	0x0     0x16

	Testresult:
    # RVAL	R1			0x0		0x17
    # RVAL  R2      	0x0 	0x20008AD3
    # RVAL  R3 			0x0		0x16
    # RVAL  R4 			0x0		0x01
    
    #VAR Proc_test_res	FALSE	TRUE
    #VAR Testcase_result FAILED PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    
  	__ASM("MOV R1,0x0");
  	__ASM("MOV R2,0x0");
  	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
    #-- Function Under Test
    AluTest();
    
	#--Compare Proc_test_res with expected values
   	if(Proc_test_res == TRUE)
   	{
		Testcase_result = PASSED;
   	}
   	else
	{
		Testcase_result = FAILED;
	}
        
TEST_2:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform carry_flag test and Proc_test_res is set to FALSE
    #COMMENT when addition operation on registers(R1,R2) with operands CONST_SIX and CONST_FIVE ,
    #COMMENT gives result(R2) not equal to CONST_ELEVEN.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-001
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 2
    #COMMENT  Class 4
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 2.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.          
    #COMMENT Step 1 : Check the initial value of registers R1 ,R2 Proc_test_res ,testcase_number and Testcase_result in watch window.
	#COMMENT Step 2 : Set break point at line number 79 in source 'hdudispfpbita.s' where addition is performed using R1,R2.Press F5
	#COMMENT          to observe the value of R2.Change the value of R2 to 0x1 in watch window.	
	#COMMENT Step 3 : Set break point at line number 80 in source 'hdudispfpbita.s' where R2 is compared with CONST_ELEVEN.
	#COMMENT		  Check the value of R2.(R2 != CONST_ELEVEN)
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 2 .Observe control hits the breakpoint
	#COMMENT          indicating failure to perform carry_flag test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 2.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 indicating failure to perform carry_flag test and test result is pass. 
    #COMMENT </SCRIPT_NOTES> 
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		 init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1     			0x0     0x6
    # RVAL  R2 			 	0x0	 	0x7
    # VAR 	Proc_test_res	FALSE	FALSE
    # VAR Testcase_result 	FAILED 	PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	Proc_test_res = FALSE;
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}

TEST_3:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform zero_flag test and Proc_test_res value is set to FALSE
    #COMMENT when addition operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE and status 
    #COMMENT of carry flag is stored from APSR to R4.Result(R4) not equal to CONST_CARRY_FLAG.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-002
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 6
    #COMMENT  Class 9
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 3.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.      
    #COMMENT Step 1 : Check the initial value of registers R1 ,R2,R4, Proc_test_res ,testcase_number and Testcase_result in watch window.
	#COMMENT Step 2 : Set break point at line number 90 in source 'hdudispfpbita.s' where status of carry flag is stored from APSR to R4 register. 
	#COMMENT 	      Press F5 to observe the value of R4.Change the value of R4 to 0x1 in watch window.	
	#COMMENT Step 3 : Set break point at line number 91 in source 'hdudispfpbita.s' where R4 is compared with CONST_CARRY_FLAG.
	#COMMENT          Check the value of R4.( R4 != CONST_CARRY_FLAG).
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 3.Observe control hits the breakpoint
	#COMMENT          indicating failure to perform zero_flag test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 3.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform zero_flag test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    			init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      			0x0    	0x6
    # RVAL  R2 					0x0		0xB
    # RVAL  R4 					0x0		0x1
    # VAR 	Proc_test_res		TRUE	FALSE
    # VAR Testcase_result 		FAILED 	PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
        
TEST_4:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform overflow_flag test and Proc_test_res value is set to FALSE.when addition
    #COMMENT operation is performed on registers(R1,R2) with operands CONST_SIX and CONST_FIVE and compare R2 with 
    #COMMENT CONST_ELEVEN and status of zero flag is stored from APSR to R4.Result(R4) not equal to CONST_ZERO_FLAG .
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-003
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 11
    #COMMENT  Class 14
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 4.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.
    #COMMENT Step 1 : Check the initial value of registers R1 ,R2 ,R4,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 114 in source 'hdudispfpbita.s' where status of zero flag is stored from APSR to R4.
  	#COMMENT 		  Press F5 to observe the value R4.Change the value of R4 to zero in watch window.
	#COMMENT Step 3 : Set break point at line number 115 in source 'hdudispfpbita.s' where R4 is compared with CONST_ZERO_FLAG.
	#COMMENT		  Check the value of R4.( R4 != CONST_ZERO_FLAG)
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 4.Observe control hits the breakpoint
	#COMMENT          indicating failure to perform overflow_flag test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 4.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform overflow_flag test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x0     0x6
    # RVAL  R2 				0x0		0x5
	# RVAL  R4      		0x1		0x0
	# VAR 	Proc_test_res	TRUE	FALSE
	# VAR Testcase_result   FAILED  PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
 
TEST_5:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform subtract test and Proc_test_res value is set to FALSE
    #COMMENT when addition operation is performed on registers(R1,R2)with operands CONST_PATTERN and CONST_PATTERN  
    #COMMENT and store the status of the zero flag from APSR into the register (R4).Result(R4) is not equal to CONST_OVERFLOW_FLAG.
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-004
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 16
    #COMMENT  Class 19
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 5.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.      
    #COMMENT Step 1 : Check the initial value of R1, R2 ,R4 ,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 114 in source 'hdudispfpbita.s' where status of zero flag is stored from APSR to R4. 
  	#COMMENT          Press F5 to observe the value R4.Change the value of R4 to 0x0000FFFF in watch window.
  	#COMMENT Step 3 : Set break point at line number 115 in source 'hdudispfpbita.s' where R4 is compared with CONST_OVERFLOW_FLAG.
	#COMMENT		  Check the value of R4.( R4 != CONST_OVERFLOW_FLAG) 	
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 5.Observe control hits the breakpoint
	#COMMENT		  indicating failure to perform subtract test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 5.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform subtract test and test result is pass.	
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x0     0x7FFFFFFF
    # RVAL  R2 				0x0		0x7FFFFFFF
	# RVAL  R4      		0x1		0x0000FFFF
	# VAR 	Proc_test_res	TRUE	FALSE
	# VAR   Testcase_result FAILED  PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here 
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
        
TEST_6:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform multiply test and Proc_test_res value is set to FALSE
    #COMMENT when subtract operation is performed on registers(R1,R2) with operands CONST_SIX
    #COMMENT and CONST_FIVE and result(R1)not equal CONST_ONE. 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-005
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 21
    #COMMENT  Class 23
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 6.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.     
    #COMMENT Step 1 : Check the initial value of R1 ,R2 ,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 126 in source 'hdudispfpbita.s' where subtraction is performs on R1 and R2.
  	#COMMENT 		  Press F5 to observe the value R1.Change the value of R1 to 0x2 in watch window.	
  	#COMMENT Step 3 : Set break point at line number 127 in source 'hdudispfpbita.s' where R1 is compared with CONST_ONE.
  	#COMMENT          Check the value of R1.( R1 != CONST_ONE)
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 6.Observe control hits the breakpoint
	#COMMENT          indicating failure to perform multiply test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 6.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform multiply test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x6     0x2
    # RVAL  R2 				0x5		0x5
    
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
      
        
TEST_7:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform division test and Proc_test_res value is set to FALSE 
    #COMMENT when multiply operation is performed on registers(R1,R2) with operands CONST_THREE
    #COMMENT and CONST_TWO  and result(R1)not equal CONST_SIX. 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-006
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 25
    #COMMENT  Class 27
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 7.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.     
    #COMMENT Step 1 : Check the initial value of R1 ,R2 ,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 137 in source 'hdudispfpbita.s' where multiplication is performed on R1 ,R2.
  	#COMMENT		  Press F5 to observe the value of R1.Change the value of R1 to 0x5 in watch window.	
  	#COMMENT Step 3 : Set break point at line number 138 in source 'hdudispfpbita.s' where R1 is compared with CONST_SIX. 
  	#COMMENT          Check the value of R1.( R1 != CONST_SIX)
  	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 7.Observe control hits the breakpoint
	#COMMENT          indicating failure to perform division test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 7.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform division test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x3     0x5
    # RVAL  R2 				0x2		0x2
    #
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}

        
TEST_8:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform logicaland test and Proc_test_res value is set to FALSE 
    #COMMENT when division operation is performed on registers(R1,R2) with operands CONST_FOUR
    #COMMENT and CONST_TWO and result(R1)not equal CONST_TWO. 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-007
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 29
    #COMMENT  Class 31
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 8.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.       
   	#COMMENT Step 1 : Check the initial value of R1 ,R2 ,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 148 in source 'hdudispfpbita.s' where division operation is performed on R1,R2.
  	#COMMENT	 	  Press F5 to observe the value of R1.Change the value of R1 to 0x1 in watch window.	
  	#COMMENT Step 3 : Set break point at line number 149 in source 'hdudispfpbita.s' where R1 is compared with CONST_TWO.
  	#COMMENT		  Check the value of R1.( R1 != CONST_TWO)
  	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 8.Observe control hits the breakpoint
  	#COMMENT		  indicating failure to perform logicaland test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 8.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform logicaland test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x4     0x1
    # RVAL  R2 				0x2		0x2
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED   
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
 
        
TEST_9:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform logicalor test and Proc_test_res value is set to FALSE 
    #COMMENT when logical AND operation is performed on registers(R1,R2) with operands CONST_HEX_ONE
    #COMMENT and CONST_SEVENTEEN  and result(R3)not equal CONST_ONE . 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-008
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 33
    #COMMENT  Class 35
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 9.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.      
    #COMMENT Step 1 : Check the initial value of R1,R2,R3,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 159 in source 'hdudispfpbita.s' where AND operation is performed on R1,R2 and result is  
  	#COMMENT          stored in R3.Change the value of R2 to 0x0.	
  	#COMMENT Step 3 : Set break point at line number 160 in source 'hdudispfpbita.s' where R3 is compared with CONST_ONE.
  	#COMMENT          Check the value of R3.( R3 != CONST_ONE)	
  	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 9.Observe control hits the breakpoint
  	#COMMENT		  indicating failure to perform logicalor test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 9.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform logicalor test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x0     0x01
    # RVAL  R2 				0x0		0x0
    # RVAL  R3 				0x1		0x0
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED   
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}
  
        
TEST_10:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to perform exlusiveor test and Proc_test_res value is set to FALSE 
    #COMMENT when logical OR operation is performed on registers(R1,R2) with operands  CONST_SIXTEEN
    #COMMENT and CONST_HEX_ONE and result(R3)not equal CONST_SEVENTEEN . 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-009
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 37
    #COMMENT  Class 39
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 10.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.       
    #COMMENT Step 1 : Check the initial value of R1,R2, R3,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 171 in source 'hdudispfpbita.s' where OR operation is performed on R1,R2 and result is stored in R3. 
  	#COMMENT          Change the value of R2 to 0x0.	
  	#COMMENT Step 3 : Set break point at line number 172 in source 'hdudispfpbita.s' where r3 is compared with CONST_SEVENTEEN.
  	#COMMENT		  Check the value of R3.( R3 != CONST_SEVENTEEN)
  	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 10.Observe control hits the breakpoint
  	#COMMENT		  indicating failure to perform exlusiveor test.
	#COMMENT Step 5 : Set breakpoint at break statement in case 10.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to perform exlusiveor test and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x0     0x10
    # RVAL  R2 				0x0		0x0
    # RVAL  R3 				0x0		0x10
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED   
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}

        
TEST_11:
    #COMMENT FAMILY Nominal         
    #COMMENT Testcase description
    #COMMENT <TD>                   
    #COMMENT The function 'AluTest' fails to branch to Testresult and Proc_test_res value is set to FALSE 
    #COMMENT when logical XOR operation is performed on registers(R1,R2) with operands CONST_SEVENTEEN 
    #COMMENT and CONST_HEX_ONE and result(R3)not equal CONST_SIXTEEN. 
    #COMMENT </TD>                  
    
    #COMMENT Tested Requirements
    #COMMENT <RQ>                   
    #COMMENT hdudispfpbita-AluTest-DB-LLR-010
    #COMMENT </RQ>                  
    
    #COMMENT Equivalence Class
    #COMMENT <EC>                   
    #COMMENT  Class 41
    #COMMENT  Class 43
    #COMMENT </EC>  
    
    #COMMENT <SCRIPT_NOTES>
    #COMMENT Set breakpoint at switch case in 'hdudispfmain.c' file and add testcase_number in watch window and enter value of testcase_number as 11.
    #COMMENT Set breakpoint at AluTest() and press F5 to enter the CSU under Test.Below mentioned steps has to be followed to verify
    #COMMENT Low Level Requirements.       
    #COMMENT Step 1 : Check the initial value of R1,R2,R3,Proc_test_res ,testcase_number and Testcase_result in watch window.
  	#COMMENT Step 2 : Set break point at line number 183 in source 'hdudispfpbita.s' where exclusive OR operation is performed on R1,R2 and
  	#COMMENT		  result is stored in R3.Change the value of R2 to 0xB.	
  	#COMMENT Step 3 : Set break point at line number 184 in source 'hdudispfpbita.s' where R3 is compared with CONST_SIXTEEN.
  	#COMMENT		  Check the value of R3.( R3 != CONST_SIXTEEN)
	#COMMENT Step 4 : Set breakpoint in 'hdudispfmain.c' where Testcase_result is set to PASSED in case 11.Observe control hits the breakpoint
	#COMMENT		  indicating failure to branch to Testresult.
	#COMMENT Step 5 : Set breakpoint at break statement in case 10.Observe values of Proc_test_res is (FALSE)0 and Testcase_result 
	#COMMENT		  is (PASSED)1 in watch window indicating failure to branch to Testresult and test result is pass.
    #COMMENT </SCRIPT_NOTES> 
    
    
    #-------------------------------------------------------------------------------         
    #VAR    name    		init    ev
    #------------------------------------------------------------------------------  
    # RVAL  R1      		0x0     0x11
    # RVAL  R2 				0x0		0xB
    # RVAL  R3 				0x0		0x1A
    # VAR 	Proc_test_res	TRUE	FALSE
    # VAR   Testcase_result FAILED  PASSED 
    #-------------------------------------------------------------------------------  
                    
    #--Test case start here
    __ASM("MOV R1,0x0");
	__ASM("MOV R2,0x0");
	__ASM("MOV R3,0x0");
	__ASM("MOV R4,0x0");
	
	
    #-- Function Under Test
    AluTest() ;
    
    #--Compare Proc_test_res with expected values
	if(Proc_test_res == FALSE)
	{
		Testcase_result = PASSED;
	}
	else
	{
		Testcase_result = FAILED;
	}         
        
TESTEND:

#Stub definition section

#-------------------------------- End of Test Script --------------------------------------