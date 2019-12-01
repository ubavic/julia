#include "global.h"

double getRandom()
{
    return (double)rand()/(double)(RAND_MAX);
}

double sigmoid1(double x)
{
    return (0.5 + (2*x - 1)/(sqrt(2 + 2 * (2*x - 1) * (2*x - 1))));
}

double sigmoid2(double x)
{
    return (0.5 + (2*x - 1)/(sqrt(2 + 2 * (2*x - 1) * (2*x - 1))));
}

double sigmoid3(double x)
{
    return 2/PI*atan(pow(x+0.5,10));
}

complex Add (complex a, complex b){
	complex sum;
	sum.re = a.re + b.re;
	sum.im = a.im + b.im;
	return sum;
}

complex Sub (complex a, complex b){
	complex c;
	c.re = a.re - b.re;
	c.im = a.im - b.im;
	return c;
}

complex Mul (complex a, complex b){
	complex c;
	c.re = a.re*b.re - a.im*b.im;
	c.im = a.re*b.im + a.im*b.re;
	return c;
}

complex Div (complex a, complex b){
	complex c;
	c.re = (a.re*b.re + a.im*b.im)/(b.re * b.re + b.im * b.im);
	c.im = (a.im*b.re - a.re*b.im)/(b.re * b.re + b.im * b.im);
	return c;
}

complex Con (complex a){
	complex c;
	c.re = a.re;
	c.im = -c.im;
	return c;
}

double NormSq (complex a){
	return a.re * a.re + a.im * a.im;
}

double Norm (complex a){
	return sqrt(a.re * a.re + a.im * a.im);
}

complex RealExp (complex a, double exponent){
	complex c;
	double tmp1, tmp2;

	tmp1 = a.re * a.re + a.im * a.im;
	tmp1 = pow(tmp1, exponent/2);
	tmp2 = atan2(a.im, a.re);
	tmp2 = tmp2 * exponent;
	c.re = tmp1 * cos(tmp2);
	c.im = tmp1 * sin(tmp2);

	return c;
}

void Print (complex a){
	printf("%+f%+fi\n", a.re, a.im);
}