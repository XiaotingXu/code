import java.io.Serializable;

/**
 * @author  Xiaoting Xu
 * @version 1.0
 * @since   2016-03-28
 */

public class CreditCard implements Serializable{
	
	private Long creditCardNumber;
	private boolean valid;
	
	CreditCard() {
		
		creditCardNumber = 0L;
		valid = false;
	}
	
	CreditCard(Long creditCardNumber) {
		
		this.creditCardNumber = creditCardNumber;
		this.valid = false;
	}

	/**
	 * @return  This returns the credit card number
	 */
	public Long getCreditCardNumber() {
		return creditCardNumber;
	}

	/**
	 * @param This resets credit card number
	 */
	public void setCreditCardNumber(Long creditCardNumber) {
		this.creditCardNumber = creditCardNumber;
	}

	/**
	 * @return  This returns the credit card number is valid or not
	 */
	public boolean isValid() {
		return valid;
	}
	
	/**
	 * @param This sets the validation of the credit card number
	 */
	public void setValid(boolean valid) {
		this.valid = valid;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((creditCardNumber == null) ? 0 : creditCardNumber.hashCode());
		result = prime * result + (valid ? 1231 : 1237);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof CreditCard)) {
			return false;
		}
		CreditCard other = (CreditCard) obj;
		if (creditCardNumber == null) {
			if (other.creditCardNumber != null) {
				return false;
			}
		} else if (!creditCardNumber.equals(other.creditCardNumber)) {
			return false;
		}
		if (valid != other.valid) {
			return false;
		}
		return true;
	}

	@Override
	public String toString() {
		return "CreditCard: creditCardNumber=" + creditCardNumber + ", valid=" + valid;
	}
}
