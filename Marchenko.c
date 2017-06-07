#include "fann.h"
#include <stdio.h>
#include <string.h>

int i;
char ans[100];
const unsigned int num_input = 3;
const unsigned int num_layers = 2;
const unsigned int num_output = 1;
const float desired_error = (const float) 0.01;
const unsigned int max_epochs = 200;
const unsigned int epochs_between_reports = 1;

void train(char *fromwhere, char *towhere) {

	struct fann *myFann = fann_create_standard(num_layers, num_input, num_output);
	fann_train_on_file(myFann, fromwhere, max_epochs, epochs_between_reports, desired_error);
	fann_save(myFann, towhere);
	fann_destroy(myFann);
}

int main(int argc, char* argv[])
{
	if (argc < 4)
		return 1;
	if (fopen("classify.net", "r") == NULL) {
		printf("can't found train file\n");
		printf("input filename or 'exit'\n");
		scanf("%s", ans);
		if (strcmp(ans, "exit") != 0)
			train(ans, "classify.net");
		return 0;
	}

 	struct fann *myFann = fann_create_from_file("classify.net");
	float input[3];
	for (i = 0; i < 3; i++)
		input[i] = (float) *argv[i+1]-'0';

 	float *output = fann_run(myFann, input);
	printf("%.2f\n", *output);
 	return 0;
}


