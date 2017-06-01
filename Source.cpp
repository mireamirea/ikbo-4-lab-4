#include "stdlib.h"
#include "stdio.h"
#include "fann.h"
#include "floatfann.h"

int main(int argc, char **argv) {
	int i;
	fann_type *calc_out;
	fann_type input[3];
	struct fann *ann = fann_create_standard(3,3,3,1);
	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
	ann = fann_create_from_file("func.net");
	for (i = 0; i < 3; i++)
		if (argv[i + 1][0] == '0')
			input[i] = 0;
		else
			input[i] = 1;
	calc_out = fann_run(ann, input);
	if (calc_out[0] > 0.5)
		printf("%d", 1);
	else
		printf("%d", 0);
	fann_destroy(ann);
	return 0;
}
