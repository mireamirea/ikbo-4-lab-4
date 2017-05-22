#include "stdlib.h"
#include "stdio.h"
#include "fann.h"
#include "floatfann.h"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc,char **argv){
	int i;
	const unsigned int num_input = 3; //Количество входных сигналов
	const unsigned int num_output = 1; //Количество выходных сигналов
	const unsigned int num_layers = 3; //Количество слоев нейронной сети
	const unsigned int num_neurons_hidden = 3; //Коилчество нейронов в скрытом слое
	const float desired_error = (const float) 0.01; //Точность
	const unsigned int max_epochs = 1000; //Количество циклов прогонки(для обучения сети)
	fann_type *calc_out; //Выходной сигнал
	fann_type input[3]; //Входные сигналы

	// создание нейронной сети с именем ann
	struct fann *ann = fann_create_standard(num_layers, num_input,num_neurons_hidden, num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	//обучение
	//fann_train_on_file(ann, "training.txt", max_epochs,10, desired_error);

	//Выгрузка обученной нейронной сети
	ann = fann_create_from_file("func.net");
	
	//задание значений входным нейронам
	for (i = 0; i < 3; i++)
		if (argv[i + 1][0] == '0')
			input[i] = 0;
		else
			input[i] = 1;

	//Считаем значение выходного сигнала
	calc_out = fann_run(ann, input);

	//вывод результатов c выходного нейрона
	printf("%f\n", calc_out[0]);
	if (calc_out[0] > 0.5)
		printf("%d", 1);
	else
		printf("%d", 0);

	//сохранение обученной сети в файл
	//fann_save(ann, "func.net");
	
	//Удаляем структуру
	fann_destroy(ann);
	
	return 0;
}
