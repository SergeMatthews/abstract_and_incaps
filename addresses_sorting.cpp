#include <iostream>
#include <string>
#include <fstream>
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;


class Address
{
private:
	string city{};
	string street{};
	string house{};
	int appartment{};
public:
	Address(ifstream& fin) {
		fin >> city >> street >> house >> appartment;
	}
	void get_output_address(ofstream& fout) {
		fout << (city + ", " + street + ", " + house + ", " + std::to_string(appartment)) << endl;
	}
	string get_city() {
		return city;
	}
};

void InsertionSort(Address** arr, int size);

int main()
{
	setlocale(LC_ALL, "RU");

	ifstream fin("in.txt");
	if (!fin.is_open()) {
		std::cout << "Не удалось открыть файл in.txt" << endl;
		return EXIT_FAILURE;
	}
	int AddressesNumber{};
	fin >> AddressesNumber;

	Address** addressesList = new Address * [AddressesNumber];
	for (int i = 0; i < AddressesNumber; ++i) {
		addressesList[i] = new Address(fin);
	}
	fin.close();

	InsertionSort(addressesList, AddressesNumber);

	ofstream fout("out.txt");
	if (!fout.is_open()) {
		std::cout << "Не удалось создать файл out.txt" << endl;
		return EXIT_FAILURE;
	}

	fout << AddressesNumber << endl;
	for (int i = AddressesNumber - 1; i >= 0; --i) {
		addressesList[i]->get_output_address(fout);
	}
	fout.close();

	for (int i = 0; i < AddressesNumber; ++i) {
		delete addressesList[i];
	}
	delete[] addressesList;

	return EXIT_SUCCESS;
}

void InsertionSort(Address** arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		Address* key = arr[i];
		int j = i - 1;

		while (j >= 0 && (arr[j]->get_city().compare(key->get_city())) < 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}	
}

