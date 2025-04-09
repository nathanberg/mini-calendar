#include <stdio.h>
#include <stdbool.h>

// 1. Leap year function
bool is_leap_year(int year) {
    // A year is leap if:
    //  - divisible by 4, AND
    //  - ( not divisible by 100 OR divisible by 400 )
    return ( (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)) );
}

// 2. Days in each month (index 1 corresponds to January, etc.)
int days_in_month[] = {
    0,  // index 0 (placeholder)
    31, // index 1 (January)
    28, // index 2 (February) -- might be 29 if leap year
    31, // index 3 (March)
    30, // index 4 (April)
    31, // index 5 (May)
    30, // index 6 (June)
    31, // index 7 (July)
    31, // index 8 (August)
    30, // index 9 (September)
    31, // index 10 (October)
    30, // index 11 (November)
    31  // index 12 (December)
};

// 3. Function to add days to a given date
void add_days_to_date(int* mm, int* dd, int* yy, int days_left_to_add) {
    // Keep adding days as long as we have days_left_to_add
    while (days_left_to_add > 0) {
        // How many days remain in the current month?
        int days_left_in_month = days_in_month[*mm] - *dd;

        // Check if current month is February in a leap year
        if (*mm == 2 && is_leap_year(*yy)) {
            // In a leap year, February has 29 days instead of 28
            days_left_in_month += 1;
        }

        // If we have more days to add than what remains in this month,
        // move to the next month/year accordingly.
        if (days_left_to_add > days_left_in_month) {
            // Use up the remainder of this month (+1 more day to jump to next month)
            days_left_to_add -= (days_left_in_month + 1);

            // Move to the 1st of the next month
            *dd = 1;

            // If it was December, roll over to January of next year
            if (*mm == 12) {
                *mm = 1;
                *yy += 1;
            } else {
                *mm += 1;
            }
        } else {
            // We can fit all remaining days in the current month
            *dd += days_left_to_add;
            days_left_to_add = 0;  // done!
        }
    }
}

int main() {
    int mm, dd, yy, days_left_to_add;

    printf("Please enter a date in the format: mm dd yyyy <days_to_add>\n");
    printf("Example: 3 14 2021 45\n");
    printf("-> This will add 45 days to March 14, 2021.\n\n");

    printf("Your input: ");
    scanf("%d %d %d %d", &mm, &dd, &yy, &days_left_to_add);

    add_days_to_date(&mm, &dd, &yy, days_left_to_add);

    printf("New date after adding %d day(s): %d %d %d\n",
           days_left_to_add, mm, dd, yy);

    return 0;
}
