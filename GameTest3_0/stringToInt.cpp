#include "stringToInt.hpp"

int stringToInt(std::string number){
    //Get length of string
	std::string num;
	int			intNum = 0;
	int			length = number.length();
	for(int i = length; i > 0; i--){
		//Get number and multiply with 10^position
		num = number.at(i-1);
		if(num == "0"){
		}else if(num == "1"){
			intNum += 1*powerOfTen(length-i);
		}else if(num == "2"){
			intNum += 2*powerOfTen(length-i);
		}else if(num == "3"){
			intNum += 3*powerOfTen(length-i);
		}else if(num == "4"){
			intNum += 4*powerOfTen(length-i);
		}else if(num == "5"){
			intNum += 5*powerOfTen(length-i);
		}else if(num == "6"){
			intNum += 6*powerOfTen(length-i);
		}else if(num == "7"){
			intNum += 7*powerOfTen(length-i);
		}else if(num == "8"){
			intNum += 8*powerOfTen(length-i);
		}else if(num == "9"){
			intNum += 9*powerOfTen(length-i);
		}else{
			//Not a number, return an error
			return -1;
		}
	}
	return intNum;
}

int powerOfTen(int power){
	//Make sure that the result can be stored in an 32-bit int
	if(power < 9 && power >= 0){
		int num = 1;
		while(power){
			//Multiply with ten
			num *= 10;
			power--;
		}
		return num;
	}
	//Error, return zero
	return 0;
}



