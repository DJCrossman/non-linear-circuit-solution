/*
 *	Main.cpp
 *
 *  Created on: March 23, 2014
 *  Author: David
 */

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double R = 225;
const double C = 0.0000006;
const double L = 0.5;
const double Z = 100;

void problem1();
void problem2();

double method(double);
double methodPrime(double);

double bisectionMethod(double, double);
double newtonRapsonMethod(double);
double secantMethod(double,double,double);

int problem;

int main () {
	char input = '0';
	while (tolower(input) != 'q') {
		cout << "Please enter the cooresponding letter:" << endl;
		cout << " a - Problem 1" << endl;
		cout << " b - Problem 2" << endl;
		cout << " q - Quit" << endl;
		cin >> input;
		switch (tolower(input))
		{
			case 'a' :
			{
				system("cls");
				cout << "Problem 1" << endl;
				problem1();
				break;
			}
			case 'b' :
			{
				system("cls");
				cout << "Problem 2" << endl;
				problem2();
				break;
			}
			case 'q' :
			{
				cout << "Goodbye!" << endl;
			}
			default:
				cout << "Please try again!" << endl;
				break;
		}
		cout << endl;
	}
	return 0;
}

void problem1()
{	
	problem = 1;

	double result;

	char input;
	cout << "With R = " << R << ", C = " << C << "F, L = " << L << "H" << endl; 
	cout << "Find the angular frequency that results in an impedance of " << Z << "." << endl;
	cout << "Please enter the cooresponding letter:" << endl;
	cout << " a - The Bisection Method" << endl;
	cout << " b - The Newton-Raphson Method" << endl;
	cout << " c - The Secant Method" << endl;
	cin >> input;

	switch (tolower(input))
	{
		case 'a' :
		{
			system("cls");
			cout << "The Bisection Method" << endl;
			result = bisectionMethod(1.0, 250.0);
			break;
		}
		case 'b' :
		{
			system("cls");
			cout << "The Newton-Raphson Method" << endl;
			result = newtonRapsonMethod(250);
			break;
		}
		case 'c' :
		{
			system("cls");
			cout << "The Secant Method" << endl;
			result = secantMethod(1.0, 250.0, 0);
			break;
		}
		default:
			cout << "Please try again!" << endl;
			break;
	}
	if(result >= 0)
		cout << "The root is : " << result << endl;
}

void problem2()
{
	problem = 2;
	double result[2];

	char input;
	cout << "f(x) = 230x^4 + 18 x^3 + 9x^2 - 221x - 9" << endl; 
	cout << "Approximate (both) these roots. " << endl;
	cout << "Please enter the cooresponding letter:" << endl;
	cout << " a - The Bisection Method" << endl;
	cout << " b - The Newton-Raphson Method" << endl;
	cout << " c - The Secant Method" << endl;
	cin >> input;

	switch (tolower(input))
	{
		case 'a' :
		{
			system("cls");
			cout << "The Bisection Method" << endl;
			result[0] = bisectionMethod(-1.0, 0.5);
			result[1] = bisectionMethod(1.0, -0.01);
			break;
		}
		case 'b' :
		{
			system("cls");
			cout << "The Newton-Raphson Method" << endl;
			result[0] = newtonRapsonMethod(0.0);
			result[1] = newtonRapsonMethod(1.0);
			break;
		}
		case 'c' :
		{
			system("cls");
			cout << "The Secant Method" << endl;
			result[0] = secantMethod(0.0, 0.5, 0);
			result[1] = secantMethod(0.9, 1.0, 0);
			break;
		}
		default:
			cout << "Please try again!" << endl;
			break;
	}
	if(result >= 0)
		cout << "The roots are: " << result[0] << " and " << result[1] << endl; 
}

double method(double w)
{
	if (problem == 1)
		return ( pow(C,2.0)*pow(w,4.0) + ( 1/pow(R,2.0) - 2*(C/L) - 1/pow(Z,2.0) )*pow(w,2.0) + 1/(pow(L,2.0)) );
	if (problem == 2)
		return ( 230*pow(w,4.0) + 18*pow(w,3.0) + 9*pow(w,2.0) - 221*w - 9 );
	return 0;
}

double methodPrime(double w)
{
	if (problem == 1)
		return ( 4*pow(C,2.0)*pow(w,3.0) - 2*( 1/pow(R,2.0) - 2*(C/L) - 1/pow(Z,2.0) )*w );;
	if (problem == 2)
		return ( 230*4*pow(w,3.0) + 18*3*pow(w,2.0) + 18*w - 221 );
	return 0;
}

double bisectionMethod(double lower, double upper)
{
	double middle = (lower+upper)/2;
	//cout << middle << endl;
	if(method(middle) == 0 || abs(lower - upper) < pow(0.1, 7) * max(abs(lower), abs(upper)))
		return middle;
	if(method(middle) > 0 && method(lower) > 0)
		return bisectionMethod(middle, upper);
	else
		return bisectionMethod(lower, middle);
}

double newtonRapsonMethod(double x)
{
	double y = method(x);
	double yPrime = methodPrime(x);

	if(abs(yPrime) < 1*pow(10, -7)) {
		cout << "WARNING: denominator is too small" << endl;
		return -1.0;
	}
	double x1 = x - y/yPrime;
	//cout << x1 << endl;
	if(abs(x1 - x)/abs(x) < pow(0.1, 7) * abs(x))
        return x1;
	else
		return newtonRapsonMethod(x1);
}

double secantMethod(double a, double b , double c)
{
	//cout << b << endl;
	if (abs(b-a) < pow(0.1, 7) * abs(b))
		return b;
	else
		return secantMethod(b,b + (b - c)/(method(c)/method(b)-1),a);
}