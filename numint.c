#include <stdio.h>
#define NUM_COEFFICIENTS 5

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

void clear_string(char *s, int len) {
	for (int i = 0; i < len; i++) {
		s[i] = '\0';
	}
}

int main(int argc, char *argv[]) {
	int lower_limit, upper_limit, num_subints;
	int coefficients[NUM_COEFFICIENTS];
	char *s = malloc(16);

	/* get user input */
	lower_limit = getn("Lower limit");
	upper_limit = getn("Upper limit");
	num_subints = getn("Number of subintervals");

	for (int i = 0; i < NUM_COEFFICIENTS; i++) {
		sprintf(s, "Coefficient %c", i + 65);
		coefficients[i] = getn(s);
		clear_string(s, 16);
	}
	free(s);

	/* calculate */

	return 0;
}
