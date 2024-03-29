#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_LEN 32 // the length of the input string
#define NUM_COEFFICIENTS 5 // the degree of the polynomial. can be up to 26

typedef struct {
	int constant, coefficients[NUM_COEFFICIENTS];
} Polynomial;

/* gets an integer from standard input. */
int getn(char *prompt) {
	char *ptr, line[INPUT_LEN];
	int n = 0;

	printf("%s: ", prompt);
	while (fgets(line, sizeof(line), stdin)) {
		n = strtol(line, &ptr, 10);
		if (ptr == line || *ptr != '\n') {
			printf("You did not enter a valid integer.\n");
			printf("%s: ", prompt);
		} else break;
	}

	return n;
}

/* evaluate a polynomial with the given coefficients at x */
double evaluate(Polynomial p, double x) {
	double res = 0.0;

	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		res += (double) p.coefficients[i] * pow(x, NUM_COEFFICIENTS - i);
	}
	res += p.constant;

	return res;
}

/* calculate percentage error of approximation */
double percentage_error(double approx, double exact) {
	return (fabs(exact - approx) / fabs(exact)) * 100.0;
}

/* find the exact definite integral of a polynomial */
double exact_integral(Polynomial p, int ll, int ul) {
	double a = 0.0, b = 0.0;

	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		int n = NUM_COEFFICIENTS - i;
		a += (p.coefficients[i] * pow(ll, n + 1)) / (double) (n + 1);
		b += p.coefficients[i] * pow(ul, n + 1) / (double) (n + 1);
	}

	b += p.constant;

	return (b - a) + p.constant;
}

/* midpoint approximation */
double midpoint_approx(Polynomial p, int ll, int ul, int num_si) {
	double res = 0.0, width = (double) (ul - ll) / num_si;

	for (int i = 0; i < num_si; i++) {
		double x1 = (double) ll + (width * i);
		double midpoint = x1 + (width / 2.0);
		res += evaluate(p, midpoint);
	}

	return res * width;
}

/* trapezoid approximation */
double trapezoid_approx(Polynomial p, int ll, int ul, int num_si) {
	double res = 0.0, width = (double) (ul - ll) / num_si;

	for (int i = 0; i < num_si; i++) {
		double x1 = (double) ll + width * i;
		double x2 = (double) ll + width * (i + 1.0);
		res += (evaluate(p, x1) + evaluate(p, x2)) / 2.0;
	}

	return res * width;
}

/* simpson's approximation */
double simpson_approx(Polynomial p, int ll, int ul, int num_si) {
	double ma = midpoint_approx(p, ll, ul, num_si);
	double ta = trapezoid_approx(p, ll, ul, num_si);

	return ((2.0 * ma) + ta) / 3.0;
}

int main(int argc, char *argv[]) {
	int lower_limit, upper_limit, num_subints;
	char prompt[1];
	Polynomial p;

	/* get parameters */
	lower_limit = getn("Lower limit");
	upper_limit = getn("Upper limit");
	num_subints = getn("Number of subintervals");

	/* get coefficients */
	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		prompt[0] = (char) i + 65;
		p.coefficients[i] = getn(prompt);
	}

	/* get constant */
	prompt[0] = (char) NUM_COEFFICIENTS + 65;
	p.constant = getn(prompt);

	/* calculations */
	double exact = exact_integral(p, lower_limit, upper_limit);
	double mp = midpoint_approx(p, lower_limit, upper_limit, num_subints);
	double mp_err = percentage_error(mp, exact);
	double tz = trapezoid_approx(p, lower_limit, upper_limit, num_subints);
	double tz_err = percentage_error(tz, exact);
	double ss = simpson_approx(p, lower_limit, upper_limit, num_subints);
	double ss_err = percentage_error(ss, exact);

	/* print results with 10 decimal point precision */
	printf("\n\nExact integral: %.10f\n", exact);
	printf("Midpoint approximation: %.10f\n", mp);
	printf("Midpoint percentage error: %.10f\n", mp_err);
	printf("Trapezoid approximation: %.10f\n", tz);
	printf("Trapezoid percentage error: %.10f\n", tz_err);
	printf("Simpson's approximation: %.10f\n", ss);
	printf("Simpson's percentage error: %.10f\n", ss_err);

	return 0;
}
