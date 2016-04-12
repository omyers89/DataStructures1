/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2014                                          */
/*                                                                         */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "library1.h"
#include <cstring>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif




/* The command's strings */
typedef enum {
  NONE_CMD = -2,
  COMMENT_CMD = -1,
  INIT_CMD = 0,
  ADDJOBSEARCHER_CMD = 1,
  REMOVEJOBSEARCHER_CMD = 2,
  HIRE_CMD = 3,
  HIREBYSALARY_CMD = 4,
  BONUS_CMD = 5,
  FIRE_CMD = 6,
  GETNUMEMPLOYED_CMD = 7,
  HIGHESTPAID_CMD = 8,
  CUTBACKS_CMD = 9,
  QUIT_CMD = 10
} commandType;



static const int   numActions   = 11;
static const char *commandStr[] = {
  "Init",
  "AddJobSearcher",
  "RemoveJobSearcher",
  "Hire",
  "HireBySalary",
  "Bonus",
  "Fire",
  "GetNumEmployed",
  "HighestPaid",
  "CutBacks",
  "Quit"
};


static const char* ReturnValToStr(int val) {
	switch (val) {
		case (SUCCESS):          return "Success";
		case (FAILURE):          return "Failure";
		case (ALLOCATION_ERROR): return "Allocation_error";
		case (INVALID_INPUT):    return "Invalid_input";
		default:                 return "";
	}
}
	





/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

/*#define Max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
	*/ 
//#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),Max(strlen(Src1), strlen(Src2))) == 0 )

int Max(int a, int b)
{
	if (a>b)
		return a;
	else
		return b;
}

bool StrCmp(const char *src1, const char *src2)
{
	return (strncmp(src1, src2,Max(strlen(src1),strlen(src2)))==0);
}

typedef enum {error_free, error} errorType;
static errorType parser(const char* const command);



#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }


static bool isInit = false;


/* Print an array */
string PrintIntArray(const int* arr, int size) {
	char buffer[MAX_BUFFER_SIZE];
	string str = "";

	for (int i=0; i < size; i++) {
		sprintf(buffer,"%d",arr[i]);
		str += string(buffer) + ((i == (size - 1)) ? "" : ",");
	}
	return str.c_str();
}




/***************************************************************************/
/* main                                                                    */
/***************************************************************************/

int main(int argc, const char**argv) {
  char buffer[MAX_STRING_INPUT_SIZE];
  // Reading commands
  while ( fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL ) {
    fflush(stdout); 
    if ( parser(buffer) == error )
      break;
  };
  return 0;
};

/***************************************************************************/
/* Command Checker                                                         */
/***************************************************************************/

static commandType CheckCommand(const char* const command, const char** const command_arg) {
  if ( command == NULL || strlen(command) == 0 || StrCmp("\n", command) )
    return(NONE_CMD);
  if ( StrCmp("#\n", command) ) {
    if (strlen(command) > 1)
      printf("%s", command);
    return(COMMENT_CMD);
  };
  
  char* word = strtok((char *)command, " \n");
  for (int index=0; index < numActions; index++) {
    if ( StrCmp(commandStr[index], word) ) {
      *command_arg = command + strlen(commandStr[index]) + 1;
      return((commandType)index);
    };
  };
  return(NONE_CMD);
};

/***************************************************************************/
/* Commands Functions                                                      */
/***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddJobSearcher(void* DS, const char* const command);
static errorType OnRemoveJobSearcher(void* DS, const char* const command);
static errorType OnHire(void* DS, const char* const command);
static errorType OnHireBySalary(void* DS, const char* const command);
static errorType OnBonus(void* DS, const char* const command);
static errorType OnFire(void* DS, const char* const command);
static errorType OnGetNumEmployed(void* DS, const char* const command);
static errorType OnHighestPaid(void* DS, const char* const command);
static errorType OnCutBacks(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);




/***************************************************************************/
/* Parser                                                                  */
/***************************************************************************/

static errorType parser(const char* const command) { 
  static void *DS = NULL; /* The general data structure */
  const char* command_args = NULL;
  errorType rtn_val = error;

  commandType command_val = CheckCommand(command, &command_args);
 
  switch (command_val) {

	case (INIT_CMD):                   rtn_val = OnInit(&DS, command_args);	break;
	case (ADDJOBSEARCHER_CMD):         rtn_val = OnAddJobSearcher(DS, command_args);	break;
	case (REMOVEJOBSEARCHER_CMD):      rtn_val = OnRemoveJobSearcher(DS, command_args);	break;
	case (HIRE_CMD):                   rtn_val = OnHire(DS, command_args);	break;
	case (HIREBYSALARY_CMD):           rtn_val = OnHireBySalary(DS, command_args);	break;
	case (BONUS_CMD):                  rtn_val = OnBonus(DS, command_args);	break;
	case (FIRE_CMD):                   rtn_val = OnFire(DS, command_args);	break;
	case (GETNUMEMPLOYED_CMD):         rtn_val = OnGetNumEmployed(DS, command_args);	break;
	case (HIGHESTPAID_CMD):            rtn_val = OnHighestPaid(DS, command_args);	break;
	case (CUTBACKS_CMD):               rtn_val = OnCutBacks(DS, command_args);	break;
	case (QUIT_CMD):                   rtn_val = OnQuit(&DS, command_args);	break;
	
	case (COMMENT_CMD):                rtn_val = error_free;	break;
	case (NONE_CMD):                   rtn_val = error;	break;
	default: assert(false);
  };
  return(rtn_val);
};





/***************************************************************************/
/* OnInit                                                                  */
/***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if(isInit) {
		printf("Init was already called.\n");
		return(error_free);
	};
	isInit = true;

	int	K;	
	ValidateRead( sscanf(command, "%d" ,&K), 1, "Init failed.\n" );
		
	*DS = Init(K);
	if( *DS == NULL ) {
		printf("Init failed.\n");
		return(error);
	};
	printf("Init done.\n");

	return error_free;
}


/***************************************************************************/
/* OnAddJobSearcher                                                        */
/***************************************************************************/
static errorType OnAddJobSearcher(void* DS, const char* const command) {
	int engineerID;
	int reqSalary;
	ValidateRead( sscanf(command, "%d %d",&engineerID,&reqSalary), 2, "AddJobSearcher failed.\n" );
	StatusType res = AddJobSearcher(DS,engineerID,reqSalary);
	
	if (res != SUCCESS) {
		printf("AddJobSearcher: %s\n",ReturnValToStr(res));
	}
	else {
		printf("AddJobSearcher: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnRemoveJobSearcher                                                     */
/***************************************************************************/
static errorType OnRemoveJobSearcher(void* DS, const char* const command) {
	int engineerID;
	ValidateRead( sscanf(command, "%d",&engineerID), 1, "RemoveJobSearcher failed.\n" );
	StatusType res = RemoveJobSearcher(DS,engineerID);
	
	if (res != SUCCESS) {
		printf("RemoveJobSearcher: %s\n",ReturnValToStr(res));
	}
	else {
		printf("RemoveJobSearcher: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnHire                                                                  */
/***************************************************************************/
static errorType OnHire(void* DS, const char* const command) {
	int companyID;
	int engineerID;
	ValidateRead( sscanf(command, "%d %d",&companyID,&engineerID), 2, "Hire failed.\n" );
	StatusType res = Hire(DS,companyID,engineerID);
	
	if (res != SUCCESS) {
		printf("Hire: %s\n",ReturnValToStr(res));
	}
	else {
		printf("Hire: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnHireBySalary                                                          */
/***************************************************************************/
static errorType OnHireBySalary(void* DS, const char* const command) {
	int companyID;
	int salaryThd;
	ValidateRead( sscanf(command, "%d %d",&companyID,&salaryThd), 2, "HireBySalary failed.\n" );
	StatusType res = HireBySalary(DS,companyID,salaryThd);
	
	if (res != SUCCESS) {
		printf("HireBySalary: %s\n",ReturnValToStr(res));
	}
	else {
		printf("HireBySalary: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnBonus                                                                 */
/***************************************************************************/
static errorType OnBonus(void* DS, const char* const command) {
	int companyID;
	int engineerID;
	int bonus;
	ValidateRead( sscanf(command, "%d %d %d",&companyID,&engineerID,&bonus), 3, "Bonus failed.\n" );
	StatusType res = Bonus(DS,companyID,engineerID,bonus);
	
	if (res != SUCCESS) {
		printf("Bonus: %s\n",ReturnValToStr(res));
	}
	else {
		printf("Bonus: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnFire                                                                  */
/***************************************************************************/
static errorType OnFire(void* DS, const char* const command) {
	int companyID;
	int engineerID;
	ValidateRead( sscanf(command, "%d %d",&companyID,&engineerID), 2, "Fire failed.\n" );
	StatusType res = Fire(DS,companyID,engineerID);
	
	if (res != SUCCESS) {
		printf("Fire: %s\n",ReturnValToStr(res));
	}
	else {
		printf("Fire: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnGetNumEmployed                                                       */
/***************************************************************************/
static errorType OnGetNumEmployed(void* DS, const char* const command) {
	int companyID;
	ValidateRead( sscanf(command, "%d",&companyID), 1, "GetNumEmployed failed.\n" );
	int	num;
	StatusType res = GetNumEmployed(DS,companyID,&num);
	
	if (res != SUCCESS) {
		printf("GetNumEmployed: %s\n",ReturnValToStr(res));
	}
	else {
		printf("GetNumEmployed: %s %d\n", ReturnValToStr(res),num);
	}

	return error_free;
}


/***************************************************************************/
/* OnHighestPaid                                                           */
/***************************************************************************/
static errorType OnHighestPaid(void* DS, const char* const command) {
	int companyID;
	ValidateRead( sscanf(command, "%d",&companyID), 1, "HighestPaid failed.\n" );
	int	engineerID;
	StatusType res = HighestPaid(DS,companyID,&engineerID);
	
	if (res != SUCCESS) {
		printf("HighestPaid: %s\n",ReturnValToStr(res));
	}
	else {
		printf("HighestPaid: %s %d\n", ReturnValToStr(res),engineerID);
	}

	return error_free;
}


/***************************************************************************/
/* OnCutBacks                                                              */
/***************************************************************************/
static errorType OnCutBacks(void* DS, const char* const command) {
	int companyID;
	int salaryThd;
	int salaryDecrease;
	ValidateRead( sscanf(command, "%d %d %d",&companyID,&salaryThd,&salaryDecrease), 3, "CutBacks failed.\n" );
	StatusType res = CutBacks(DS,companyID,salaryThd,salaryDecrease);
	
	if (res != SUCCESS) {
		printf("CutBacks: %s\n",ReturnValToStr(res));
	}
	else {
		printf("CutBacks: %s\n", ReturnValToStr(res));
	}

	return error_free;
}


/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	Quit(DS);
	if( *DS != NULL ) {
		printf("Quit failed.\n");
		return(error);
	}
	isInit = false;
	printf("Quit done.\n");

	return error_free;
}




#ifdef __cplusplus
}
#endif


