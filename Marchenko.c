#include "fann.h"
#include <stdio.h>
#include <string.h>

int i;
char ans[30];
void train(char *, char *);

int main(int argc, char* argv[])
{
	if (argc < 4)
		return 1;
	if (fopen("classify.net", "r") == NULL) {
		printf("can't found train file\nwould you like to train?\n");
		printf("input filename or 'exit'\n");
		scanf("%s", ans);
		if (strcmp(ans, "exit") != 0)
			train(ans, "classify.net");
		return 0;
	}

 	struct fann *myFann = fann_create_from_file("classify.net");
	float input[3];
	for (i = 1; i <= 3; i++)
		input[i-1] = (float) *argv[i]-'0';

 	float *output = fann_run(myFann, input);
	printf("%.lf\n", *output);
 	return 0;
}

void train(char *fromwhere, char *towhere) {
	struct fann *myFann = fann_create_standard(2, 3, 1);
	fann_train_on_file(myFann, fromwhere, 200, 1, 0.01);
	fann_save(myFann, towhere);
	printf("finish\n");
	fann_destroy(myFann);
}
