#include <iostream>
#include "stdio.h"
#include "fann.h"
#include "floatfann.h"

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char* argv[])
{
	const unsigned int num_input = 3;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 3;
	const float desired_error = (const float) 0.00002;
	const unsigned int max_epochs = 1500000000;
	const unsigned int epochs_between_reports = 2;
	fann_type *calc_out;
	fann_type input[3];
	char argvv[4][2];

	if (argc < 3) {
		cin >> argvv[1] >> argvv[2] >> argvv[3];
		for (int i = 0; i < 3; i++) {
			input[i] = atof(argvv[i + 1]);
		}
	}
	else {
		for (int i = 0; i < 3; i++) 
			input[i] = atof(argv[i + 1]);
	}

	struct fann *ann;
	if (FILE *fp = fopen("Function.net", "r")) {
		ann = fann_create_from_file("Function.net");
	}
	else {
		ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);

		fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
		fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

		fann_train_on_file(ann, "training.txt", max_epochs, epochs_between_reports, desired_error);
	}

	calc_out = fann_run(ann, input);

	cout << "Input Values" << endl;
	cout << input[0] << " " << input[1] << " " << input[2] << " " << endl;

	printf("Function Result: (%.0f,%.0f,%.0f) -> %.0f\n", input[0], input[1], input[2], calc_out[0]);

	fann_save(ann, "Function.net");
	fann_destroy(ann);

	getchar() ;

	return 0;
}