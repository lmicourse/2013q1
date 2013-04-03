
#include <iostream>
#include "Calculator.h"
#include "Logger.h"

using namespace std;

int main() {
	Calculator calculator;
	Logger logger;

	logger.log("hello");

	int result = calculator.add(1, 2);
	logger.log(result);

	result = calculator.mul(10, 20);
	logger.log(result);
}
