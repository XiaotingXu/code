    //********************************************************************************//
    //* Name :  XiaoTing Xu                                                          *//
    //********************************************************************************//

function detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization) {

    //********************************************************************************//
    //*   This function calculates the monthly payment based on the following:       *//
    //*                                                                              *//
    //*               M = P [ i(1 + i)n ] / [ (1 +  i)n - 1]                         *//
    //*                                                                              *//
    //********************************************************************************//
     var paymentError = "";
     var v = mortAmount * 1;
     var d = mortDownPayment * 1;
     var i = mortRate * 1;
     var y = mortAmortization * 1;
     var a = v - d;
         i = i/100/12;
         n = y * 12;
     var f = Math.pow((1+i),n);

     var p = (a * ((i*f)/(f-1))).toFixed(2);

     if (p=="NaN" || p=="Infinity") {
         document.forms[0].payment.value = "";
     }
     else {
           document.forms[0].payment.value = p;
     }

} // End of detailPaymentCalculation function


function validationForPayment() {   

    //********************************************************************************//
    //*  This function will call the functions that validate the following:          *//
    //********************************************************************************//
    //*        (1)              (2)              (3)             (4)                 *//
    //********************************************************************************//
    //*   Property value  -  Down payment  -  Interest rate -  Amortization          *//
    //********************************************************************************//
    //*   If there are no errors, then call                                          *//
    //*                                                                              *//
    //*      detailPaymentCalculation(...., ......, ......, ......);                 *//
    //*                                                                              *//
    //*   and make sure to pass the four values in the order shown above.            *//
    //*                                                                              *//
    //********************************************************************************//
    //*   If there are errors, simply update the comments area with the message:     *//
    //*   Please complete the form first and then click on Calculate Monthly Payment *//
    //*                                                                              *//
    //********************************************************************************//
	var paymentError = "Please complete the form first and then click on Calculate Monthly Payment.";
	if ( validatePropValue() === "" && validateDownPay()=== "" && validateAmortization() === "" &&  validateIntRate() === "" ) {
		var mortAmount = Number(document.mortgage.propValue.value);
		var mortDownPayment = Number(document.mortgage.downPay.value);
		var mortRate = Number(document.mortgage.intRate.value);
		var mortAmortization = Number(document.mortgage.amortization.value);
		document.getElementById("comments").value = "";
		detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization);
	}
	else {
		document.getElementById("comments").value = paymentError;
	}
} // End of validationForPayment function

function completeFormValidation() {

    //********************************************************************************//
    //*                                                                              *//
    //* This function calls the different functions to validate all required fields  *//
    //*                                                                              *//
    //* Once you have validated all field,                                           *//
    //* determine if any error(s) have been encountered                              *//
    //*                                                                              *//
    //* If any of the required fields are in error:                                  *//
    //*                                                                              *//
    //*    present the client with a list of all the errors in reserved area         *//
    //*         on the form and                                                      *//
    //*          don't submit the form to the CGI program in order to allow the      *//
    //*          client to correct the fields in error                               *//
    //*                                                                              *//
    //*    Error messages should be meaningful and reflect the exact error condition.*//
    //*                                                                              *//
    //*    Make sure to return false                                                 *//
    //*                                                                              *//
    //* Otherwise (if there are no errors)                                           *//
    //*                                                                              *//
    //*    Change the 1st. character in the field called client to upper case        *//
    //*                                                                              *//
    //*    Change the initial value in the field called jsActive from N to Y         *//
    //*                                                                              *//
    //*    Make sure to return true in order for the form to be submitted to the CGI *//
    //*                                                                              *//
    //********************************************************************************//
	var errMessages = ""; 
	errMessages = validateUserId(errMessages);
	errMessages = validateClient(errMessages);
	errMessages = validateIncome(errMessages);
	errMessages += validatePropValue();
	errMessages += validateDownPay();
	errMessages = validatePropDetails(errMessages);
	errMessages = validatePropLocation(errMessages);
	errMessages = validateMortYear(errMessages);
	errMessages = validateMortMonth(errMessages);
	errMessages += validateIntRate();
	errMessages += validateAmortization();
	var client = document.mortgage.client.value;

	if( errMessages !== "") {
		document.getElementById("errors").innerHTML = errMessages;
		return false;
	}
	else {
		if ( validatePropValue() === "" && validateDownPay()=== "" && validateAmortization() === "" &&  validateIntRate() === "" ){
			var mortAmount = Number(document.mortgage.propValue.value);
			var mortDownPayment = Number(document.mortgage.downPay.value);
			var mortRate = Number(document.mortgage.intRate.value);
			var mortAmortization = Number(document.mortgage.amortization.value);
			document.getElementById("comments").value = "";
			detailPaymentCalculation(mortAmount,mortDownPayment,mortRate,mortAmortization);
			client = client.substr(0,1).toUpperCase() + client.substr(1,client.length-1);
			document.mortgage.client.value = client;
			document.mortgage.jsActive.value = "Y";
			document.getElementById("errors").innerHTML = errMessages;
			return true;
		}
		else {
			document.getElementById("comments").value = "  Please complete the form first and then click on Calculate Monthly Payment.";
			return false;
		}
	}

} // End of completeFormValidation

function validateUserId(errMessages){
	
    //********************************************************************************//
    //*  This function will validate the user ID.                                    *//
    //********************************************************************************//   
	var userId = document.mortgage.userId.value;
	userId = userId.trim();
	var userIdLength = userId.length;
	var leftSum = 0;
	var rightSum = 0;
	var errorsCount = 0;
	if( userIdLength === 0) { 
		errMessages += "  <span class='bold'>The <span class='highlight'>Client ID</span> field cannot be left empty or just blank characters.</span><br/>";
		errorsCount++;
	}
	else {
		if( userIdLength !== 10) {
			errMessages += "  <span class='bold'>The length of <span class='highlight'>Client ID</span> must be 10.</span><br/>" ;	
			errorsCount++; 
		}
		else {
			if (userId.charAt(4) !== "-") {
				errMessages += "  <span class='bold'>The fifth position of <span class='highlight'>Client ID</span> must be a hyphen.</span><br/>";
				errorsCount++;
			}
			else {
				var userIdArray = userId.split("-");
				if(isNaN(userIdArray[0]) || isNaN(userIdArray[1])) {
					errMessages += "  <span class='bold'>Apart from the fifth position of <span class='highlight'>Client ID</span>, the rest must be numeric digits.</span><br/>";
					errorsCount++;
				}	
				else {
					for (var i=0;i<userIdArray[0].length;i++) {
						leftSum += Number(userIdArray[0].charAt(i));
					}	
					for (var i=0;i<userIdArray[1].length;i++) {
						rightSum += Number(userIdArray[1].charAt(i));
					}	
					if (leftSum <= 0 || rightSum <= 0) {
						errMessages += "  <span class='bold'>In the <span class='highlight'>Client ID</span> field, the sum of the numbers to the left of the hyphen (-) must be greater than zero and the sum of the numbers to the right of the hyphen (-) must be greater than zero.</span><br/>";
						errorsCount++;
					}
					else {
						if(rightSum !== (leftSum * 2 + 1) ) {
							errMessages +=  "  <span class='bold'>In the <span class='highlight'>Client ID</span> field, the sum of the numbers to the right of the hyphen (-) must be (double plus 1) the sum of the numbers to the left of the hyphen (-).</span><br/>";
							errorsCount++;
						}
					}
				}
			}	
		}
	}
	if (errorsCount > 0) {
		errMessages += "<ol>Six Rules of the Client ID field:<li>It cannot be left empty or just blank characters.</li><li>The length of this field must be 10.</li><li>The fifth position of this field must be a hyphen.</li><li>Apart from the fifth position, the rest must be numeric digits.</li><li>The sum of the numbers to the left of the hyphen (-) must be greater than zero and the sum of the numbers to the right of the hyphen (-) must be greater than zero.</li><li>The sum of the numbers to the right of the hyphen (-) must be (double plus 1) the sum of the numbers to the left of the hyphen (-).</li></ol><br/>";
	}
	return errMessages;
}

function validateClient(errMessages){
	
    //********************************************************************************//
    //*  This function will validate the client name.                                *//
    //********************************************************************************//   
	var client = document.mortgage.client.value;
	client = client.trim();
	var clientLength = client.length;
	var NoOfApostrophe = 0;
	var NoOfHyphen = 0;
	var errorsCount = 0;
	
	if ( clientLength === 0 ) {
		errMessages += "  <span class='bold'><span class='highlight'>Client Name</span> field cannot be left empty or just blank characters.</span><br/>";
		errorsCount++;	
	}
	else {
		client = client.toUpperCase();
		var clientArray1 = client.split("-");
		NoOfApostrophe = clientArray1.length -1;
		if ( NoOfApostrophe !== 0 && NoOfApostrophe !== 1 ) {
			errMessages += "  <span class='bold'><span class='highlight'>Client Name</span> field can only contain a combination of alphabetic characters(a to z) (A to Z), zero or one apostrophe(') and zero or one hyphen(-).</span><br/>";
			errorsCount++;	
		}
		else{
			var clientArray2 = client.split("'");
			NoOfHyphen = clientArray2.length -1;
			if ( NoOfHyphen !== 0 && NoOfHyphen !== 1 ) {
				errMessages += "  <span class='bold'><span class='highlight'>Client Name</span> field can only contain a combination of alphabetic characters(a to z) (A to Z), zero or one apostrophe(') and zero or one hyphen(-).</span><br/>";
				errorsCount++;	
			}
			else {
				var wrongName = 0;
				for ( var i=0;i<clientLength;i++ ) {
					if( !(((client.charCodeAt(i) > 64) && (client.charCodeAt(i) < 91 )) || (client.charCodeAt(i) === 39) ||(client.charCodeAt(i) === 45)) ){
						errMessages += "  <span class='bold'><span class='highlight'>Client Name</span> field can only contain a combination of alphabetic characters(a to z) (A to Z), zero or one apostrophe(') and zero or one hyphen(-).</span><br/>";
						errorsCount++;
						wrongName = 1;
						break;	
					}	
				}
				if(!wrongName) {
					for ( var i=0;i<3;i++ ) {
						if (!((client.charCodeAt(i) > 64) && (client.charCodeAt(i) < 91 )) ) {
							errMessages += "  <span class='bold'><span class='highlight'>Client Name</span> must have at least 3 alphabetic characters (a-z) (A-Z) at the beginning of its field.</span><br/>";
							errorsCount++;
							wrongName = 1;
							break;
						}
					}
					if(!wrongName) {
						if(client.indexOf("-") === 0 || client.indexOf("-") === eval(clientLength - 1) ) {
							errMessages += "  <span class='bold'>A hyphen(-) cannot be at the beginning or at the end of the <span class='highlight'>Client Name</span> field.</span><br/>";
							errorsCount++;
						}	
						else{
							if((eval(client.indexOf("-") - client.indexOf("'")) === 1) || (eval(client.indexOf("'") - client.indexOf("-")) === 1) ) {
								errMessages += "  <span class='bold'>An apostrophe and a hyphen next to each other are not valid in the <span class='highlight'>Client Name</span> field.</span><br/>";
								errorsCount++;
							}
						}
					}
				}
			}
		}	
	}
	if (errorsCount > 0) {
		errMessages += "<ol>Five Rules of the Client Name field:<li>It cannot be left empty or just blank characters.</li><li>It can only contain a combination of alphabetic characters(a to z) (A to Z), zero or one apostrophe(') and zero or one hyphen(-).</li><li>It must have at least 3 alphabetic characters (a-z) (A-Z) at the beginning of its field.</li><li>A hyphen(-) cannot be at the beginning or at the end of this field.</li><li>An apostrophe and a hyphen next to each other are not valid in this field.</li></ol><br/>";
	}
	return errMessages;
}

function validatePropValue() {
	
    //********************************************************************************//
    //*  This function will validate the property value.                             *//
    //********************************************************************************//   
	var mortAmount = document.mortgage.propValue.value;
	mortAmount = mortAmount.trim();
	var mortAmountLength = mortAmount.length;
	var tempError ="";
	var errorsCount = 0;
	
	if ( mortAmountLength === 0 ) {
		tempError += "<span class='bold'>The <span class='highlight'>Property Value</span> field cannot be empty or meaningless blanks. </span><br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(mortAmount) || Number(mortAmount) <= 0) {
			tempError += "<span class='bold'>The value in <span class='highlight'>Property Value</span> field should be positive numbers. </span><br/>";
			errorsCount++;
		}
		else {
			if ( +mortAmount < eval(65000 + Number(document.mortgage.downPay.value)) || document.mortgage.downPay.value === "") {
				tempError += "<span class='bold'><span class='highlight'>Property Value</span> must be at least 65,000 dollars more than the down payment. Make sure you input the downpay value.</span><br/>";
				errorsCount++;
			}	
		}
	}
	if (errorsCount > 0) {
		tempError += "<ol>Three Rules of the Property Value field:<li>It cannot be empty or meaningless blanks.</li><li>The value in this field should be positive numbers.</li> <li>It must be at least 65,000 dollars more than the down payment.</li></ol><br/>";
	}
	return tempError;
}


//downPay
function validateDownPay() {
	var mortDownPayment = document.mortgage.downPay.value;
	mortDownPayment = mortDownPayment.trim();
	var mortDownPaymentLength = mortDownPayment.length;
	var tempError ="";
	var errorsCount = 0;
	
	if ( mortDownPaymentLength === 0) {
		tempError += "<span class='bold'>The <span class='highlight'>Down Payment</span> field cannot be empty or meaningless blanks. </span><br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(mortDownPayment) || Number(mortDownPayment)<=0) {
			tempError += "<span class='bold'>The value in <span class='highlight'>Down Payment</span> field should be positive numbers. </span><br/>";
			errorsCount++;
		}
		else {
			if ( +mortDownPayment < eval(0.1 * Number(document.mortgage.propValue.value)) || document.mortgage.propValue.value === "") {
				tempError += "<span class='bold'><span class='highlight'>Down Payment</span> must be at least 10% of the property value. Make sure you input the property value. </span><br/>";
				errorsCount++;
			}	
		}
	}
	if (errorsCount > 0) {
		tempError += "<ol>Three Rules of the Down Payment field:<li>It cannot be empty or meaningless blanks.</li><li>The value in this field should be positive numbers.</li><li>It must be at least 10% of the property value.</li></ol><br/>";
	}
	return tempError;
}


function validateIncome(errMessages) {
	
    //********************************************************************************//
    //*  This function will validate the user's incpme.                              *//
    //********************************************************************************//   
	var selected = document.mortgage.income.selectedIndex;
	var errorsCount = 0;
	if ( selected === -1) {
		errMessages += "  <span class='bold'>Please choose your <span class='highlight'>Income Range</span></span>. <br/>";
		errorsCount++;
	}	
	if (errorsCount > 0) {
		errMessages += "<ol>One Rule of the Income Range field:<li>It must be selected.</li></ol><br/>";
	}
	return errMessages;	
}


//propDetails
function validatePropDetails(errMessages) {
	var NoOfRadio = document.mortgage.propDetails.length;
	var checked = 0;
	var errorsCount = 0;
	for ( var i=0;i<NoOfRadio;i++) {
		if (document.mortgage.propDetails[i].checked === true) {
			checked = 1;
			break;
		}	
	}
	if(checked === 0) {
		errMessages += "  <span class='bold'>Please choose the <span class='highlight'>Property Type</span> you have</span>. <br/>";
		errorsCount++;
	}
	if (errorsCount > 0) {
		errMessages += "<ol>One Rule of the Property Type field:<li>It must be selected.</li></ol><br/>";
	}
	return errMessages;
}

function validatePropLocation(errMessages) {
	
    //********************************************************************************//
    //*  This function will validate the location of user's property.                *//
    //********************************************************************************//   
	var NoOfOptions = document.mortgage.propLocation.options.length;
	var selected = document.mortgage.propLocation.selectedIndex;
	var errorsCount = 0;
	if (selected === -1) {
		errMessages += "  <span class='bold'>Please choose your <span class='highlight'>Property Location</span></span>. <br/>";
		errorsCount++;
	}	
	if (errorsCount > 0) {
		errMessages += "<ol>One Rule of the Property Location field:<li>It must be selected.</li></ol><br/>";
	}
	return errMessages;
}

function validateMortYear(errMessages) {
	
    //********************************************************************************//
    //*  This function will validate the mortgage year.                              *//
    //********************************************************************************//   
	var mortYear = document.mortgage.mortYear.value;
	mortYear = mortYear.trim();
	var mortYearLength = mortYear.length;
	var date = new Date();
	var errorsCount = 0;
	if ( mortYearLength === 0) {
		errMessages += "  <span class='bold'>Please fill in which year you would like to start mortgaging in the <span class='highlight'>Mortgage Year</span> field. </span><br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(mortYear) ) {
			errMessages += "  <span class='bold'>The value in the <span class='highlight'>Mortgage Year</span> field should be numeric. </span><br/>";
			errorsCount++;
		}
		else {
			if ( +mortYear < Number(date.getFullYear())) {
				errMessages += "  <span class='bold'>The value in the <span class='highlight'>Mortgage Year</span> field must be equal to or greater than the current year. </span><br/>";
				errorsCount++;
			}
		}
	}
	if (errorsCount > 0) {
		errMessages += "<ol>Three Rules of the Mortgage Year field:<li>It cannot be empty or meaningless blanks.</li><li>The value in this field should be numeric.</li><li>The value in this field must be equal to or greater than the current year.</li></ol><br/>";
	}
	return errMessages;
}

function validateMortMonth(errMessages) {
	
    //********************************************************************************//
    //*  This function will validate the mortgage month.                             *//
    //********************************************************************************//   
	var mortMonth = document.mortgage.mortMonth.value;
	mortMonth = mortMonth.trim();
	var mortMonthLength = mortMonth.length;
	var date = new Date();
	var errorsCount = 0;
	if ( mortMonthLength === 0) {
		errMessages += "  <span class='bold'>Please fill in which month you would like to start mortgaging in the <span class='highlight'>Mortgage Month</span></span>. <br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(mortMonth) ) {
			errMessages += "  <span class='bold'>The value in <span class='highlight'>Mortgage Month</span> should be numeric.</span> <br/>";
			errorsCount++;
		}
		else {
			if ( +mortMonth < eval(date.getMonth()+1) ) {
				errMessages += "  <span class='bold'>The value in the <span class='highlight'>Mortgage Month</span> field must be equal to or greater than the current month. </span><br/>";
				errorsCount++;
			}
			else {
				if ( +mortMonth > 12 ) {
					errMessages += "  <span class='bold'>The value of <span class='highlight'>Mortgage Month</span> should be between 1 and 12(inclusive). </span><br/>";
					errorsCount++;
				}	
			}
		}
	}
	if (errorsCount > 0) {
		errMessages += "<ol>Four Rules of the Mortgage Month field:<li>It cannot be empty or meaningless blanks.</li><li>The value in this field should be numeric.</li><li>The value in this field must be equal to or greater than the current month.</li><li>The value of this field should be between 1 and 12(inclusive).</li></ol><br/>";
	}
	return errMessages;
}

function validateIntRate() {
	
    //********************************************************************************//
    //*  This function will validate the interest rate.                              *//
    //********************************************************************************//   
	var intRate = document.mortgage.intRate.value;
	intRate = intRate.trim();
	var intRateLength = intRate.length;
	var tempError = "";
	var errorsCount = 0;
	
	if ( intRateLength === 0 ) {
		tempError += "<span class='bold'>The <span class='highlight'>Interest Rate</span> field cannot be empty or some meaningless blanks.  </span><br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(intRate) ) {
			tempError += "<span class='bold'>The value in the <span class='highlight'>Interest Rate</span> field must be numeric.  </span><br/>";	
			errorsCount++;
		}
		else{
			if( +intRate < 2 || +intRate > 11 ) {
				tempError += "<span class='bold'>The allowable values in the <span class='highlight'>Interest Rate</span> field are between 2.000 and 11.000(inclusive).  </span><br/>";
				errorsCount++;
			}
		}
	}
	if (errorsCount > 0) {
		tempError += "<ol>Three Rules of the Interest Rate field:<li>It cannot be empty or some meaningless blanks.</li><li>The value in this field must be numeric.</li><li>The allowable values in this field are between 2.000 and 11.000(inclusive).</li></ol><br/>";
	}
	return tempError;		
}

function validateAmortization() {
	
    //********************************************************************************//
    //*  This function will validate the amortization.                               *//
    //********************************************************************************//   
	var amortization = document.mortgage.amortization.value;
	amortization = amortization.trim();
	var amortizationLength = amortization.length;
	var tempError = "";
	var errorsCount = 0;
	if ( amortizationLength === 0 ) {
		tempError += "<span class='bold'>The <span class='highlight'>Amortization</span> field cannot be empty or some meaningless blanks.  </span><br/>";
		errorsCount++;
	}
	else {
		if ( isNaN(amortization) ) {
			tempError += "<span class='bold'>The value in the <span class='highlight'>Amortization</span> field must be numeric. </span><br/>";	
			errorsCount++;
		}
		else{
			if( +amortization< 5 || +amortization > 20 ) {
				tempError += "<span class='bold'>The allowable values in the <span class='highlight'>Amortization</span> field are between 05 and 20(inclusive). </span><br/>";
				errorsCount++;
			}
		}
	}
	if (errorsCount > 0) {
		tempError += "<ol>Three Rules of the Amortization field:<li>It cannot be empty or some meaningless blanks.</li><li>The value in this field must be numeric.</li><li>The allowable values in this field are between 05 and 20(inclusive).</li></ol><br/>";
	}
	return tempError;		
}
