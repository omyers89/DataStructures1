/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */ 
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library1.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET1_
#define _234218_WET1_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	ALLOCATION_ERROR = -2,
	INVALID_INPUT = -3

} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes the data structure with K hi-tech companies.
 * Input:         DS - A pointer to the data structure.
 *                K - Number of hi-tech companies in Haifa
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int K);







/* Description:   Adds to the system a new engineer that is searching for a job.
 *                minSalary is the salary requirement expected 
 * Input:         DS - A pointer to the data structure.
 *                engineerID - The ID of the engineer
 *                reqSalary - The salary requested by the engineer
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, engineerID<0 or reqSalary<0
 *                FAILURE - If the ID engineerID is already in use or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  AddJobSearcher(void* DS, int engineerID, int reqSalary);







/* Description:   Removes from the system an unemployed engineer.
 * Input:         DS - A pointer to the data structure.
 *                engineerID - The ID of the engineer
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or engineerID<0
 *                FAILURE - If there is no unemployed engineer in the system with the ID engineerID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  RemoveJobSearcher(void* DS, int engineerID);







/* Description:   A hi-tech company hires an unemployed engineer.
 *                The engineer will earn the salary he requested.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 *                engineerID - The ID of the engineer
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, companyID is not legal or engineerID<0
 *                FAILURE - If there is no unemployed engineer in the system with the ID engineerID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  Hire(void* DS, int companyID, int engineerID);







/* Description:   A hi-tech company hires the unemployed engineer with the highest salary request out of those who request at most salaryThd.
 *                If several unemployed engineers match this condition, the engineer with the highest ID is taken.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 *                salaryThd - The upper threshold on the given salary
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, companyID is not legal or salaryThd<0
 *                FAILURE - If there are no unemployed engineers in the system that demand at most salaryThd or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  HireBySalary(void* DS, int companyID, int salaryThd);







/* Description:   The engineer engineerID working for the hi-tech company companyID gets a bonus to his/her salary.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company.
 *                engineerID - The ID of the engineer
 *                bonus - The bonus
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, companyID is not legal, engineerID<0 or bonus<0
 *                FAILURE - If there is no engineer in the hi-tech company with the ID engineerID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  Bonus(void* DS, int companyID, int engineerID, int bonus);







/* Description:   An engineer is fired from a hi-tech company.
 *                The engineer is automatically registered to the assignment company, and requests the same salary given to him right before he was fired.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 *                engineerID - The ID of the engineer
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL, companyID is not legal or engineerID<0
 *                FAILURE - If there is no engineer in the hi-tech company with the ID engineerID or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  Fire(void* DS, int companyID, int engineerID);







/* Description:   Returns the number of employed workers in a hi-tech company.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 * Output:        num - A pointer to a variable to which the output is written.
 * Return Values: INVALID_INPUT - If DS==NULL, companyID is not legal or num==NULL
 *                FAILURE - In case of any error.
 *                SUCCESS - Otherwise.
 */
StatusType  GetNumEmployed(void* DS, int companyID, int* num);







/* Description:   Returns the engineer ID of the highest paid engineer in a hi-tech company.
 *                In case of several highest paid employees, the employee with the highest ID will be returned.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 * Output:        engineerID - A pointer to a variable to which the output is written.
 * Return Values: INVALID_INPUT - If DS==NULL, companyID is not legal or engineerID==NULL
 *                FAILURE - In case of any error.
 *                SUCCESS - Otherwise.
 */
StatusType  HighestPaid(void* DS, int companyID, int* engineerID);







/* Description:   A hi-tech company decides to cut back salaries.
 *                Any employ earning at least salaryThd will lose salaryDecrease from his/her salary.
 * Input:         DS - A pointer to the data structure.
 *                companyID - The ID of the hi-tech company
 *                salaryThd - The salary threshold from which salaries will be deducted
 *                salaryDecrease - The deduction
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, companyID is not legal, salaryThd<0, salaryDecrease<0 or salaryDecrease>salaryThd
 *                FAILURE - If there are no employees in the company or in case of any other error.
 *                SUCCESS - Otherwise.
 */
StatusType  CutBacks(void* DS, int companyID, int salaryThd, int salaryDecrease);







/* Description:   Quits and deletes the database.
 *                The variable pointed by DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */ 

