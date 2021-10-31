#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_COEFFICIENTS 5

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
	long n;
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
		res += p.coefficients[i] * pow(x, NUM_COEFFICIENTS - i);
	}

	res += p.constant;
	return res;
}

int main(int argc, char *argv[]) {
	int lower_limit, upper_limit, num_subints;
	Polynomial p;
	char *s = malloc(4);

	/* get user input */
	lower_limit = getn("Lower limit");
	upper_limit = getn("Upper limit");
	num_subints = getn("Number of subintervals");

	/* get coefficients */
	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		sprintf(s, "%c", i + 65);
		p.coefficients[i] = getn(s);
		clear_string(s, 4);
	}
	
	/* get constant */
	sprintf(s, "%c", NUM_COEFFICIENTS + 65);
	p.constant = getn(s);
	free(s);

	/* calculate test */
	double val = evaluate(p, 0);
	printf("(0, %.2f)\n", val);

	return 0;
}
