#include <iostream>
#include "fann.h"
#include "floatfann.h"

using std::cout;
using std::cin;
using std::endl;
int main()
{
	int flag=10;
	const unsigned int num_input = 3;
	const unsigned int num_output = 1;
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 4;
	const float desired_error = (const float) 0.0001;
	const unsigned int max_epochs = 2000;
	const unsigned int epochs_between_reports = 2;
	fann_type *calc_out;
	fann_type input[3];
	struct fann *ann=0;
	char name[500];
	FILE *f;
	while (flag)
	{
		cout<<"Chose action:\n1 - teach neural network\n2 - load neural network\n3 - save neural network\n4 - run neural network\n0 - exit\n";
		cin >> flag;
		fflush(stdin);
		switch (flag)
		{
		case 1:
			if (ann) fann_destroy(ann);
			ann = fann_create_standard(num_layers, num_input, num_neurons_hidden, num_output);
			fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
			fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);
			cout<<"Enter name of training file\n";
			cin >> name;
			cout << endl;
			while ((f=fopen(name,"r"))==0)
			{
				system("CLS");
				cout << "Enter correct name of training file\n";
				cin >> name;
				cout << endl;
				fflush(stdin);
			}
			fclose(f);
			fann_train_on_file(ann, name, max_epochs, epochs_between_reports, desired_error);
			cout << "Training completed." << endl;
			system("PAUSE");
			system("CLS");
			flag = 10;
			break;
		case 2:
			if (ann) fann_destroy(ann);
			cout << "Enter name of file with network\n";
			cin >> name;
			cout << endl;
			fflush(stdin);
			while ((f = fopen(name, "r")) == 0)
			{
				printf("Enter name of file with network\n");
				cin >> name;
				cout << endl;
				fflush(stdin);
			}
			fclose(f);
			ann = fann_create_from_file(name);
			flag = 10;
			system("CLS");
			cout << "Loaded." << endl;
			break;
		case 3:
			system("CLS");
			if (!ann)
			{
				cout<<"No network loaded!\n";
				break;
			}
			cout<<"Enter name of file to save in\n";
			cin >> name;
			cout << endl;
			fflush(stdin);
			fann_save(ann,name);
			flag = 10;
			break;
		case 4:
			system("CLS");
			if (!ann)
			{
				cout<<"No network loaded!\n";
				break;
			}
			cout<<"Enter data:\n";
			cin >> input[0] >> input[1] >> input[2];
			cout << endl;
			calc_out = fann_run(ann, input);
			printf("Result of (%.0f,%.0f,%.0f) is %.0f\n", input[0], input[1], input[2], fabs(calc_out[0]));
			flag = 10;
			break;
		case 0:
			system("CLS");
			return 0;
		default:
			system("CLS");
			cout << "Unknown command\n";
			flag = 10;
			break;
		}
	}
	return 0;
}
