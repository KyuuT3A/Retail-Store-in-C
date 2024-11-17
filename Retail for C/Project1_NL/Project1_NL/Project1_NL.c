// --------------------------------------------------------------------------------
// Name: Nicolas Le
// Abstract: Project 1 Create a retail store that will allow us to calculate
// the discounts for the employee when they buy items.
// Discounts are based on the # of years worked and if they are a manager or hourly employee
// The are allowed no discounts once they have recieved 200 in discount for the the year
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Includes – built-in libraries of functions
// --------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
const long lngARRAY_SIZE = 100;
// Create Maximum discount
const float MAX_DISCOUNT = 200.0;
// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------
// 

// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
void NumberOfYearsEmployed(int* intYears);
void PreviousTotalPurchases(float* sngPrevTotalPurchases);
void EmployeeStatus(char* chrEmployeeStatus);
void TotalPurchases(float* sngTotalPurchases);
void CalculateDiscount(int* intYears, char* chrEmployeeStatus, float* sngDiscount);
void CalculateYTDDiscount(float* sngPrevTotalPurchases, float* sngDiscount, float* sngYTDTotal);
void CalculateTotalBeforeDiscount(float* sngTotalPurchases);
void CalculateDiscountThisPurchase(float* sngTotalPurchases, float* sngDiscount, float* sngYTDTotal, float* sngDiscountThisPurchase);
float CalculateTotalWithDiscount(float* sngTotalPurchases, float* sngDiscountThisPurchase);
void TotalBeforeDiscountForDay(float sngTotalBeforeDiscount);
void TotalAfterDiscountForDay(float sngTotalAfterDiscount);

// --------------------------------------------------------------------------------
// Name: main
// Abstract: To start running the program
// --------------------------------------------------------------------------------
int main()
{	
    // Declare variable
    int intYearsEmployed;
    float sngPrevTotalPurchases;
    char chrEmployeeStatus;
    float sngTotalPurchases;
    float sngDiscount;
    float sngYTDTotal;
    float sngDiscountThisPurchase;
    char chrMoreEmployer = 'Y';
    float sngTotalBeforeDiscount = 0.0;
    float sngTotalAfterDiscount = 0.0;

    while (chrMoreEmployer == 'Y' || chrMoreEmployer == 'y')
    {
        float sngTotalWithDiscount;

        // input    
        NumberOfYearsEmployed(&intYearsEmployed);
        PreviousTotalPurchases(&sngPrevTotalPurchases);
        EmployeeStatus(&chrEmployeeStatus);
        TotalPurchases(&sngTotalPurchases);

        // output
        CalculateDiscount(&intYearsEmployed, &chrEmployeeStatus, &sngDiscount);
        CalculateYTDDiscount(&sngPrevTotalPurchases, &sngDiscount, &sngYTDTotal);
        CalculateTotalBeforeDiscount(&sngTotalPurchases);
        CalculateDiscountThisPurchase(&sngTotalPurchases, &sngDiscount, &sngYTDTotal, &sngDiscountThisPurchase);

        // Only call this once
        sngTotalWithDiscount = CalculateTotalWithDiscount(&sngTotalPurchases, &sngDiscountThisPurchase);

        // Accumulate the totals
        sngTotalBeforeDiscount += sngTotalPurchases;
        sngTotalAfterDiscount += sngTotalWithDiscount;

        // Check if there are more employees to process
        printf("Anymore employees? Say 'N' for total outputs (Y/N): ");
        scanf(" %c", &chrMoreEmployer);
    }

    // Output total before and after discount for all employees
    TotalBeforeDiscountForDay(sngTotalBeforeDiscount);
    TotalAfterDiscountForDay(sngTotalAfterDiscount);

    return 0;
}

// --------------------------------------------------------------------------------
// Inputs
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Function: Numbers of years employed
// Abstract: Numbers of years employed (required, numeric, >0) 
// --------------------------------------------------------------------------------
void NumberOfYearsEmployed(int *intYears)
{   
    // prompt user input
    do
    {
        printf("Enter the number of years worked (must be greater than 0): ");
        scanf("%d", intYears);
        // Validate input
        if (*intYears <= 0) 
        {
            printf("Enter a number greater than 0.\n");
        }
    // Input is valid
    } while (*intYears <= 0);
}        




// --------------------------------------------------------------------------------
// Function: Previous purchases 
// Abstract: Total previous purchases before discount (required, numeric, >=0)
// --------------------------------------------------------------------------------
void PreviousTotalPurchases(float *sngPrevTotalPurchases)
{   
    // prompt user input
    do
    {
        printf("Enter total amount of previous purchases: ");
        scanf("%f", sngPrevTotalPurchases);
        // Validate input
        if (*sngPrevTotalPurchases < 0)
        {
            printf("Enter a number greater than 0.\n");
        }
    // Input is valid
    } while (*sngPrevTotalPurchases < 0);
}



// --------------------------------------------------------------------------------
// Function: Employee Status 
// Abstract: Validate if the Employee is an hourly employee or a manager
// --------------------------------------------------------------------------------
void EmployeeStatus(char *chrEmployeeStatus)
{    
    do 
    {
        printf("Enter your employee status (E for employee or M for manager): ");
        scanf(" %c", chrEmployeeStatus);
        if (*chrEmployeeStatus != 'E' && *chrEmployeeStatus != 'M') {
            printf("Please enter E for employee or M for manager.\n");
        }
    } while (*chrEmployeeStatus != 'E' && *chrEmployeeStatus != 'M');   
}



// --------------------------------------------------------------------------------
// Function: Total of today's purchases
// Abstract: enter a value for all purchases
// --------------------------------------------------------------------------------
void TotalPurchases(float* sngTotalPurchases)
{
    // prompt user input
    do
    {
        printf("Enter total amount of purchases: ");
        scanf("%f", sngTotalPurchases);
        // Validate input
        if (*sngTotalPurchases < 0)
        {
            printf("Enter a number greater than 0.\n");
        }
        // Input is valid
    } while (*sngTotalPurchases < 0);
}



// --------------------------------------------------------------------------------
// Outputs
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Function: Employee discount percentage
// Abstract: enter the employee discount standard 
// Years of Employment	Management	Hourly
// 1 - 3 Years	        20 %        10 %
// 4 - 6 Years	        24 %        14 %
// 7 - 10 Years	        30 %        20 %
// 11 - 15 Years	    35 %        25 %
// More than 15 Years	40 %        30 %
// --------------------------------------------------------------------------------
void CalculateDiscount(int* intYears, char* chrEmployeeStatus, float* sngDiscount)
{
    // set to 0
    *sngDiscount = 0.0;
    // Manager discount rates
    if (*chrEmployeeStatus == 'M')
    {
        if (*intYears >= 1 && *intYears <= 3)
            *sngDiscount = 20.0;
        else if (*intYears >= 4 && *intYears <= 6)
            *sngDiscount = 24.0;
        else if (*intYears >= 7 && *intYears <= 10)
            *sngDiscount = 30.0;
        else if (*intYears >= 11 && *intYears <= 15)
            *sngDiscount = 35.0;
        else if (*intYears > 15)
            *sngDiscount = 40.0;
    }
    // Hourly employee discount rates
    else if (*chrEmployeeStatus == 'E')
    {
        if (*intYears >= 1 && *intYears <= 3)
            *sngDiscount = 10.0;
        else if (*intYears >= 4 && *intYears <= 6)
            *sngDiscount = 14.0;
        else if (*intYears >= 7 && *intYears <= 10)
            *sngDiscount = 20.0;
        else if (*intYears >= 11 && *intYears <= 15)
            *sngDiscount = 25.0;
        else if (*intYears > 15)
            *sngDiscount = 30.0;
    }
    printf("The employee discount is: %.2f%%\n", *sngDiscount);
}



// --------------------------------------------------------------------------------
// Function: YTD Amount of discount in dollars
// Abstract: Formula for YTD discount in dollars = previous purchases * discount percentage
// --------------------------------------------------------------------------------
void CalculateYTDDiscount(float* sngPrevTotalPurchases, float* sngDiscount, float* sngYTDTotal)
{
    // Calculate the YTD discount based on previous purchases only
    *sngYTDTotal = (*sngPrevTotalPurchases) * ((*sngDiscount) / 100.0);

    // Ensure the YTD discount does not exceed the maximum allowed
    if (*sngYTDTotal > MAX_DISCOUNT)
    {
        *sngYTDTotal = MAX_DISCOUNT;
    }

    // Display the YTD discount in dollars
    printf("YTD total discount in dollars: $%.2f\n", *sngYTDTotal);
}



// --------------------------------------------------------------------------------
// Function: Total purchase today before discount
// Abstract: Calculate total purchases before applying the discount
// --------------------------------------------------------------------------------
void CalculateTotalBeforeDiscount(float* sngTotalPurchases)
{
    // calculate total before discount is applied
    printf("Total before discount: $%.2f\n", *sngTotalPurchases);
}



// --------------------------------------------------------------------------------
// Function: Employee discount this purchase
// Abstract: Calculate employee discount with purchase
// Employee discount this purchase: total purchase today * discount if < $200. If over $200 previously no discount. 
// If less than $200 prior to today, but today takes them over $200 then only allow the amount to get them to $200.
// --------------------------------------------------------------------------------
void CalculateDiscountThisPurchase(float* sngTotalPurchases, float* sngDiscount, float* sngYTDTotal, float* sngDiscountThisPurchase)
{
    // formulate the potential discount based on the total purchases and the discount percentage
    float sngPotentialDiscount = (*sngTotalPurchases) * ((*sngDiscount) / 100.0);

    // calculate how much of the discount limit is still remaining for the employee
    float sngRemainingDiscount = MAX_DISCOUNT - (*sngYTDTotal);

    // If the employee has already received the maximum discount for the year, no discount is applied
    if (*sngYTDTotal >= MAX_DISCOUNT)
    {
        *sngDiscountThisPurchase = 0.0; 
    }
    // If the discount for today's purchase exceeds the remaining discount available, limit it
    else if (sngPotentialDiscount > sngRemainingDiscount)
    {
        // apply only enough discount to reach the $200 cap
        *sngDiscountThisPurchase = sngRemainingDiscount; 
    }   
    else
    {
        // apply the full discount amount
        *sngDiscountThisPurchase = sngPotentialDiscount; 
    }

    // prompt the calculated discount for today's purchase
    printf("Employee discount this purchase: $%.2f\n", *sngDiscountThisPurchase);
}



// --------------------------------------------------------------------------------
// Function: Total with discount 
// Abstract: Calculate total with discount
// Formula: Total with discount = Total * discount allowed
// --------------------------------------------------------------------------------
float CalculateTotalWithDiscount(float* sngTotalPurchases, float* sngDiscountThisPurchase)
{
    // Subtract the discount for today's purchase from the total purchases to get the final amount after discount
    float sngTotalWithDiscount = *sngTotalPurchases - *sngDiscountThisPurchase;

    // prompt the total after applying the discount
    printf("Total after discount: $%.2f\n", sngTotalWithDiscount);

    // Return the final total with the discount applied
    return sngTotalWithDiscount;
}



// All Employee Outputs

// Calculate the total for all employees for today’s date:

// --------------------------------------------------------------------------------
// Function:  Total before discount for the day     
// Abstract:  Calculate total before discount for the day
// --------------------------------------------------------------------------------
void TotalBeforeDiscountForDay(float sngTotalBeforeDiscount)
{
    // prompt data for user
    printf("Total before discount for the day: $%.2f\n", sngTotalBeforeDiscount);
}



// --------------------------------------------------------------------------------
// Function: all Total after discount for the day     
// Abstract:  Calculate total after discount for the day
// --------------------------------------------------------------------------------
void TotalAfterDiscountForDay(float sngTotalAfterDiscount)
{
    // prompt data for user
    printf("Total after discounts for the day: $%.2f\n", sngTotalAfterDiscount);
}