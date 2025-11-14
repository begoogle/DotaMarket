#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

//================= Учетные записи ================

size_t userSize = 2;
std::string userStatus[3]{ "Супер администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "admin", "user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
std::string currentStatus;

//====================================================

//====================== Склад =========================

size_t storageSize = 0;
size_t maxItemSize = 299;
unsigned int* idArr = nullptr;
std::string* nameArr = nullptr;
double* priceArr = nullptr;
unsigned int* countArr = nullptr;
bool isStorageCreate = false;

void CreateStorage();
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemoveStorageItem();
void ChengePrice();

void ChangeStorage();
void AddNewItem();
void ChangeName();

//===================== Служебные ======================

void Start();
bool Login();
void CreateStorage();
void Getline(std::string& str);
void Err();
bool IsNumber(std::string& str);
void ShowSuperAgminMenu();
void Getline(std::string& str);

//======================== MAIN ==============================

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();

	delete[]loginArr, passArr, statusArr;

	return 0;
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize) {
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArr[i] = staticArr[i];
	}
}

bool IsNumber(std::string& str) {
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Неккорекный ввод\n";
		std::cout << "Ошибка размера числа: от 1 до 9 символов включительно\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Неккорекный ввод\n";
			std::cout << "Ошибка размера числа: введенные данные не являются числом\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

void Getline(std::string& str) {
	std::getline(std::cin, str, '\n');
}

void Start() {
	std::cout << "\n\n\n\t\t\t===| Добро пожаловать в Dota Market |===\n\n\n";

	std::string choose;

	if (Login())
	{
		system("cls");
		if (currentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Выберите тип склада.\n1 - Готовый\n2 - Новый\nВвод -> ";
				Getline(choose);
				if (choose == "1")
				{
					CreateStorage();
					ShowSuperAgminMenu();
					// ShowStorage();

					break;
				}
				else if (choose == "2")
				{
					// создание нового склада

					break;
				}
				else
				{
					Err();
				}
			}
		}
		else if (currentStatus == userStatus[1])
		{
			// готовый склад
		}
		else if (currentStatus == userStatus[2])
		{
			// готовый склад
		}
	}
	else
	{
		system("cls");
		std::cout << "\n\n\nЗавершение работы\n";
		Sleep(2000);
		system("cls");
	}
}

void Err() {
	std::cout << "Неккоретный ввод!\n";
	Sleep(1500);
	system("cls");
}

bool Login() {
	std::string login, pass;

	while (true)
	{
		std::cout << "Введите логин -> ";
		Getline(login);
		std::cout << "Введите пароль -> ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		/*if (login == loginArr[0] && pass == passArr[0])
		{
			std::cout << "Добро пожаловать, " << loginArr[0] << "\n\n";
			std::cout << "Ваш статус: " << statusArr[0] << "\n\n";
			currentStatus = statusArr[0];
			return true;
		}*/

		for (size_t i = 0; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				system("cls");
				std::cout << "Добро пожаловать, " << loginArr[i] << "\n\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}

void ShowSuperAgminMenu() {
	system("cls");

	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Измнить цену\n";
		std::cout << "6 - Редактиривать склад\n";
		std::cout << "7 - Редактиривать персонал\n";
		std::cout << "8 - Отчет о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод -> ";
		Getline(choose);

		if (choose == "1")
		{

		}
		else if (choose == "2")
		{
			ShowStorage();
		}
		else if (choose == "3")
		{
			AddStorageItem();
		}
		else if (choose == "4")
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ChengePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{

		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

		}
		else
		{
			Err();
		}
	}
}

void CreateStorage() {
	const size_t staticSize = 10;

	unsigned int id[staticSize]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::string name[staticSize]
	{
		"Arcana",
		"Ancient",
		"Seasonal",
		"Immortal",
		"Legendary",
		"Mythical",
		"Rare",
		"Uncommon",
		"Common",
		"Личности"
	};
	double price[staticSize]
	{
		3000, 5000, 10000, 1000, 500, 100, 50, 30, 10, 15000
	};
	unsigned int count[staticSize]{ 23, 24, 10, 30, 2, 15, 14, 26, 18, 8 };

	storageSize = staticSize;
	idArr = new unsigned int[storageSize];
	nameArr = new std::string[storageSize];
	countArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];
	isStorageCreate = true;

	FillArr(idArr, id, storageSize);
	FillArr(nameArr, name, storageSize);
	FillArr(countArr, count, storageSize);
	FillArr(priceArr, price, storageSize);

}

void ShowStorage(int mode) {
	if (mode == 0)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена\t" << "Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << priceArr[i] << "\t" << countArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << countArr[i] << "\n";
		}
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена\n.";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << priceArr[i] << "\n";
		}
	}
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
		}
	}

}

void AddStorageItem() {
	std::string chooseId, chooseCount, choose;
	unsigned int id = 0, count = 0;

	while (true)
	{
		system("cls");
		ShowStorage(1);
		std::cout << "Введите ID товара или \"exit\" для выхода -> ";
		Getline(chooseId);

		if (chooseId == "exit")
		{
			std::cout << "Отмена перации пополнения склада!\n";
			Sleep(1500);
			system("cls");
			break;
		}

		std::cout << "Введите кол-во товара для пополнения -> ";
		Getline(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > maxItemSize)
			{
				std::cout << "Неккоретный ID или кол-во\nМаксвимальное кол-во - " << maxItemSize;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << " -----> " << countArr[id] + count << "\n\n";
				std::cout << "Подтверить?\n Да - 1\t Нет - 2\nВвод -> ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] += count;
					std::cout << "Товар успешно поплнен!\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции!\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void RemoveStorageItem() {
	std::string chooseId, chooseCount, choose;
	unsigned int id = 0, count = 0;

	while (true)
	{
		system("cls");
		ShowStorage(1);
		std::cout << "Введите ID товара или \"exit\" для выхода -> ";
		Getline(chooseId);

		if (chooseId == "exit")
		{
			std::cout << "Отмена перации списания склада!\n";
			Sleep(1500);
			system("cls");
			break;
		}

		std::cout << "Введите кол-во товара для списания -> ";
		Getline(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Неккоретный ID или кол-во\nМаксвимальное кол-во - " << maxItemSize;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << " -----> " << countArr[id] - count << "\n\n";
				std::cout << "Подтверить?\n Да - 1\t Нет - 2\nВвод -> ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Товар успешно списанан!\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции!\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void ChengePrice() {
	std::string chooseId, choosePrice, choose;
	unsigned int id = 0;
	double newPrice;

	while (true)
	{
		system("cls");
		ShowStorage(2);
		std::cout << "Введите ID товара или \"exit\" для выхода -> ";
		Getline(chooseId);

		if (chooseId == "exit")
		{
			std::cout << "Отмена перации изменения цены!\n";
			Sleep(1500);
			system("cls");
			break;
		}

		std::cout << "Введите новую цену для товара -> ";
		Getline(choosePrice);


		if (IsNumber(chooseId) && IsNumber(choosePrice))
		{
			id = std::stoi(chooseId) - 1;
			newPrice = std::stod(choosePrice);

			if (id < 0 || id > storageSize - 1 || newPrice < 0 || newPrice > 499999)
			{
				std::cout << "Неккоретный ID или цена\nМаксвимальное цена - " << 499999;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << priceArr[id] << " -----> " << countArr[id] - newPrice << "\n\n";
				std::cout << "Подтверить?\n Да - 1\t Нет - 2\nВвод -> ";
				Getline(choose);
				if (choose == "1")
				{
					priceArr[id] = newPrice;
					std::cout << "Цена успешно изменена!\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции!\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void ChangeStorage() {
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить название товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - Выход из редактора склада\n";
		std::cout << "Ввод >> ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2")
		{
			ChangeName();
		}
		else if (choose == "4")
		{

		}
		else if (choose == "0")
		{
			system("cls");
			break;
		}
		else
		{
			Err();
		}
	}
}

void AddNewItem()
{
	std::string newName, newPrice, newCount, choose;
	double price = 0.0, count = 0.0;
	bool exit = true;
	while (true)
	{
		while (true)
		{
			system("cls");
			std::cout << "Добавление нового товара!\n\nВведите \"exit\" для прекращения операции\n\n";
			std::cout << "Введите названипе нового товара: ";
			Getline(newName);

			if (newName == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (newName.size() <= 0 || newName.size() >= 15)
			{
				std::cout << "максимальная длина названия 13 символов\n";
				Sleep(1500);
			}
			else
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "Введите Кол-во нового товара: ";
			Getline(newCount);

			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > maxItemSize)
				{
					std::cout << "Ошибка максимального размера товара. Не более" << maxItemSize << "ед.\n\n";
				}
				else
				{
					break;
				}
			}
		}
		while (exit)
		{
			std::cout << "Введите цену нового товара: ";
			Getline(newPrice);
			 
			if (newPrice == "exit")
			{
				std::cout << "Операция добавления товара прервана!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newPrice))
			{
				price = std::stod(newPrice);
				if (price > 99999)
				{
					std::cout << "Ошибка максимального цены товара. Не более" << 99999 << "ед.\n\n";
				}
				else
				{
					break;
				}
			}
			
		}
		if (exit)
		{
			std::cout << "Новый товар:" << newName << "\nКол-во: " << count << "\nЦена: " << price << "\n\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод >> ";
			Getline(choose);

			if (choose == "1")
			{
				storageSize++;
				unsigned int* idArrTemp = new unsigned int[storageSize];
				std::string* nameArrTemp = new std::string[storageSize];
				unsigned int* countArrTemp = new unsigned int[storageSize];
				double* priceArrTemp = new double[storageSize];

				FillArr(idArrTemp, idArr, storageSize - 1);
				FillArr(nameArrTemp, nameArr, storageSize - 1);
				FillArr(countArrTemp, countArr, storageSize - 1);
				FillArr(priceArrTemp, priceArr, storageSize - 1);

				idArrTemp[storageSize - 1] = storageSize;
				nameArrTemp[storageSize - 1] = newName;
				priceArrTemp[storageSize - 1] = price;
				countArrTemp[storageSize - 1] = count;

				std::swap(idArr, idArrTemp);
				std::swap(nameArr, nameArrTemp);
				std::swap(countArr, countArrTemp);
				std::swap(priceArr, priceArrTemp);

				delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
				std::cout << "Идет подготовка... \n";
				Sleep(2000);
				std::cout << "Товар успешно добавлен!\n\n";
				Sleep(1500);
			}
			else if (choose == "2")
			{
				std::cout << "Отмена\n\n";
				Sleep(1500);
			}
			else
			{
				Err();
			}
		}
		if (exit == false)
		{
			break;
		}
	}
}
void ChangeName()
{
	std::string chooseId, newName, choose;
	unsigned int id = 0;
		while (true)
		{
			system("cls");
			ShowStorage(3);
			std::cout << "Введите ID товара или \"exit\" для выхода: ";
			Getline(chooseId);

			if (chooseId == "exit")
			{
				std::cout << "Операция смены названия прервана!\n\n";
				Sleep(1500);
				break;
			}

			std::cout << "Введите название нового товара: ";
			Getline(newName);

			if (newName.size() <= 0 || newName.size() >= 50 || newName == "exit")
			{
				std::cout << "Ошибка.Максимальная длина названия 50 сим.\n";
				Sleep(1500);
			}
			else if(IsNumber(chooseId))
			{
				id = std::stoi(chooseId);
				std::cout << "\n" << std::left << std::setw(25) << nameArr[id] << " -----> " << newName << "\n\n";
				std::cout << "Подтверить?\n Да - 1\t Нет - 2\nВвод -> ";
				Getline(choose);
				//прода тут...
			}
		}
}
//-------------------

