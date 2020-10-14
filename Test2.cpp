// Test2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

void RemoveDups(char* str);
int main()
{
	// пример использования
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data); // "A B A"
}

void RemoveDups(char* str)
{
	if (str == nullptr)
	{
		return;
	}
	std::string result;
	char* previous_symbol = str;
	char* current_symbol = str+1;
	for (; *current_symbol != char(0); current_symbol++, previous_symbol++)
	{
		if (*previous_symbol == *current_symbol)
		{
			continue;
		}
		else
		{
			result += *previous_symbol;
		}
	}

	result += *previous_symbol;

	size_t source_string_length = current_symbol - str;

	memset(str, 0, source_string_length*sizeof(char));

	for (size_t counter = 0; counter < result.length(); counter++)
	{
		str[counter] = result.at(counter);
	}

	for (size_t counter = result.length(); counter < source_string_length; counter++)
	{
		str[counter] = char(0);
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
