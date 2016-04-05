import java.util.*;

/**
 * @author  Xiaoting Xu
 * @version 1.0
 * @since   2016-03-28
 */

public class CardValidation {

	/**
	 * @param  l  the credit card number
	 * @return    a list collection of the seperated digits of credit card number in order
	 */
	public static List<Long> toDigits(long l) { 
		
		List<Long> DigitsList = new ArrayList<Long>();
		
		DigitsList = toDigitsReverse(l);
		Collections.reverse(DigitsList);
		
		return DigitsList;
	}
	/**
	 * @param  l  the credit card number
	 * @return    a list collection of the seperated digits of credit card number in reverse order
	 */
	public static List<Long> toDigitsReverse(long l) { 
		
		List<Long> DigitsListReverse = new ArrayList<Long>();
		
		while(l != 0L) {
			
			DigitsListReverse.add(l%10);
			l /= 10;
		}
		
		return  DigitsListReverse;
	}
	/**
	 * @param list  a list collection of the seperated digits of credit card number
	 * @return      a list collection of the digits of credit card number after calculation
	 */
	public static List<Long> doubleSecond(List<Long> list) {
		
		List<Long> DoubleSecondDigitsList = new ArrayList<Long>();
		
		for(int i = 0; i < list.size(); ++i) {
			
			if(i%2 != 0)
				DoubleSecondDigitsList.add(list.get(i)*2);
			else
				DoubleSecondDigitsList.add(list.get(i));
		}
		
		return DoubleSecondDigitsList;
	}
	/**
	 * @param list  a list collection of the seperated digits of credit card number
	 * @return      summary of all digits
	 */
	public static long sumDigits(List<Long> list) {
		
		long sum = 0L;
		
		for(Long digit : list){
			if(digit > 9)
				sum += (digit/10 + digit%10);
			else
				sum += digit;
		}
		
		return sum;
	}
	/**
	 * @param l  the credit card number
	 * @return   true if the credit card number is valid; otherwise, false
	 */
	public static boolean isValid(long l) {
		
		boolean valid = false;

		if(sumDigits(doubleSecond(toDigitsReverse(l)))%10 == 0)
			valid = true;
		
	    return valid;
	}
	
	public static void main(String[] args) {
		
		long creditCardNumber = 4012888888881881L; 
		System.out.println(isValid(creditCardNumber));
	}
}
