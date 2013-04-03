/*
 * Calculator.h
 *
 *  Created on: 2013.04.03.
 *      Author: varrocs
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

class Calculator {
public:
	Calculator();
	virtual ~Calculator();

	int add(int a, int b);
	int mul(int a, int b);

};

#endif /* CALCULATOR_H_ */
