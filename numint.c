/*
 * TODO calculate exact integral and print percentage errors
 * TODO figure out small error in simpson's approximation
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LEN 32 // the length of the input string
#define NUM_COEFFICIENTS 5 // the degree of the polynomial. can be changed

typedef struct {
	int coefficients[NUM_COEFFICIENTS];
	int constant;
} Polynomial;

/* sets all characters in a string to '\0' (NULL) */
void clear_string(char *s, int len) {
	for (int i = 0; i < len; i++) {
		s[i] = '\0';
	}
}

/* gets a longint from standard input. */
long getn(char *prompt) {
	char *ptr, line[128];
	long n = 0;
	printf("%s: ", prompt);
	while (fgets(line, sizeof(line), stdin)) {
		n = strtol(line, &ptr, 10);
		if (ptr == line || *ptr != '\n') {
			printf("You did not enter a valid integer.\n");
			printf("%s: ", prompt);
		} else {
			break;
		}
	}

	return n;
}

/* evaluate a polynomial with the given coefficients at x */
double evaluate(Polynomial p, double x) {
	double res = 0.0;

	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		res += ((double) p.coefficients[i]) * pow(x, NUM_COEFFICIENTS - i);
	}

	res += p.constant;
	return res;
}

/* find the exact definite integral of a polynomial */
double exact_integral(Polynomial p, int ll, int ul) {
	double a = 0.0, b = 0.0;

	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		double ta = p.coefficients[i] * pow(ll, (NUM_COEFFICIENTS - i) + 1);
		double tb = p.coefficients[i] * pow(ul, (NUM_COEFFICIENTS - i) + 1);
		ta /= (NUM_COEFFICIENTS - i) + 1;
		tb /= (NUM_COEFFICIENTS - i) + 1;

		a += ta;
		b += tb;
	}

	return b - a;
}

double midpoint_approx(Polynomial p, int ll, int ul, int num_si) {
	double width = ((double) (ul - ll)) / num_si;

	double res = 0.0;
	for (int i = 0; i < num_si; i++) {
		double x1 = width * (double) i;
		double midpoint = (double) ll + (x1 + (width / 2));
		res += evaluate(p, midpoint);
	}

	res *= width;

	return res;
}

double trapezoid_approx(Polynomial p, int ll, int ul, int num_si) {
	double width = ((double) (ul - ll)) / num_si;

	double res = 0.0;
	for (int i = 0; i < num_si; i++) {
		double x1 = (double) ll + width * i;
		double x2 = (double) ll + width * (i + 1);
		res += (evaluate(p, x1) + evaluate(p, x2)) / 2;
	}

	res *= width;
	return res;
}

double simpson_approx(Polynomial p, int ll, int ul, int num_si) {
	double ma = midpoint_approx(p, ll, ul, num_si);
	double ta = trapezoid_approx(p, ll, ul, num_si);

	double res = ((2.0 * ma) + ta) / 3.0;
	return res;
}

int main(int argc, char *argv[]) {
	int lower_limit, upper_limit, num_subints;
	Polynomial p;
	char s[INPUT_LEN];

	/* get user input */
	lower_limit = getn("Lower limit");
	upper_limit = getn("Upper limit");
	num_subints = getn("Number of subintervals");

	/* get coefficients */
	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		sprintf(s, "%c", i + 65);
		p.coefficients[i] = getn(s);
		clear_string(s, INPUT_LEN);
	}
	
	/* get constant */
	sprintf(s, "%c", NUM_COEFFICIENTS + 65);
	p.constant = getn(s);

	/* do approximations */
	double midpoint = midpoint_approx(p, lower_limit, upper_limit,
			num_subints);
	double trapezoid = trapezoid_approx(p, lower_limit, upper_limit,
			num_subints);
	double simpson = simpson_approx(p, lower_limit, upper_limit,
			num_subints);
	double exact = exact_integral(p, lower_limit, upper_limit);

	printf("Midpoint approximation: %.10f\n", midpoint);
	printf("Trapezoid approximation: %.10f\n", trapezoid);
	printf("Simpson's approximation: %.10f\n", simpson);
	printf("Exact integral: %.10f\n", exact);
	/* TODO percent error stuff */

	return 0;
}
