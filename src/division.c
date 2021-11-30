#include <stdio.h>
#include <stdint.h>

/*
 * Program to implement the hardware division from figure 3.13.
 * Values are already stored as binary, so we can just perform bitwise operations to implement.
 *
 * @author Patrick Radecki
 */

int main()
{
    //prompt user and get values
	uint32_t dividend, divisor;
	printf("Enter a dividend: ");
	scanf("%d", &dividend);
	printf("Enter a divisor: ");
	scanf("%d", &divisor);

	//initialize values
	//low and high will split the 64-bit remainder
	uint32_t low, high;
	uint64_t remainder = dividend; // first store dividend initially to remainder


    //loop through 32 times
	for (int i=0; i<32; i++) {

        //shift logical left
        remainder <<= 1;

        //split
        low = (uint32_t) remainder;
		high = (uint32_t)(remainder >> 32);
        uint32_t highTemp = high;

        //subtract divisor from remainder
        high -= divisor;

        // if the most significant bit is 1, meaning negative value
		if (high & 0x80000000) {
              high = highTemp; // restore the value back to the value before the division

              remainder = high; //continue with new left side remainder space
		      remainder <<= 32; //move left 32 bits back up
		      remainder += low; //add in the right side of remainder space

		      // if the most significant bit is 0, meaning positive
		} else {

            remainder = high; //continue with new left side remainder space
		    remainder <<= 32; //move left side 32 bits back up
		    remainder += low; //add in the right side of remainder space
             remainder >>= 1; //shift total remainder to the right 1 bit
             remainder <<= 1; //shift total remainder to the left 1 bit
             remainder += 1; //add a one to finish shifting left
        }

	}

    // print results to terminal
    // low is the quotient
    // high is the remainder
	printf("%d / %d = %u R %u\n", dividend, divisor, low, high);


	return 0;

}
