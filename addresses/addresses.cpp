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
	Address(const std::string& city, const std::string& street, const std::string& house, const int& appartment) :
		city(city), street(street), house(house), appartment(appartment)
	{}
		
	string get_output_address() {
		return (city + ", " + street + ", " + house + ", " + std::to_string(appartment));
	}
};

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

	Address** addressesList = new Address* [AddressesNumber];
	for (int i = 0; i < AddressesNumber; ++i) {
		string city_temp, street_temp, house_temp;
		int appartment_temp;
		if (!fin.eof()) {
			fin >> city_temp;
			fin >> street_temp;
			fin >> house_temp;
			fin >> appartment_temp;

			addressesList[i] = new Address(city_temp, street_temp, house_temp, appartment_temp);
		}
	}
	fin.close();

	ofstream fout("out.txt");
	if (!fout.is_open()) {
		std::cout << "Не удалось создать файл out.txt" << endl;
		return EXIT_FAILURE;
	}

	fout << AddressesNumber << endl;
	for (int i = AddressesNumber - 1; i >= 0; --i) {
		fout << addressesList[i]->get_output_address() << endl;
	}
	fout.close();
	
	for (int i = 0; i < AddressesNumber; ++i) {
		delete addressesList[i];
	}
	delete[] addressesList;
	
	return EXIT_SUCCESS;
}
