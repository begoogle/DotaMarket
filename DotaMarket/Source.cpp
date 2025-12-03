#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <unordered_set>
//================= Staff ================

size_t userSize = 2;
size_t staffCount = 1;
std::string userStatus[3]{ "Супер Администратор", "Админ", "Работник" };
std::string* loginArr = new std::string[userSize]{ "admin", "user" };
std::string* passArr = new std::string[userSize]{ "admin", "user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0], userStatus[2] };
double* salesArr = new double[userSize] {0.0, 0.0};
unsigned int* userIdArr = new unsigned int[userSize] {1, 2};
unsigned int currentId = 0;
std::string currentStatus;

void ChangeAccounts();
void ShowUsers(int mode = 0);
void AddNewUsers();
void SetSpecialSymbols();
void ChangePass();
void DeleteUser();

//====================== Storage =========================

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
void ChangePrice();
void ChangeStorage();
void AddNewItem();
void ChangeName();
void DeleteItem();
//----------------Seals----------------------------------

size_t checkSize = 0;
int* idArrCheck;
std::string* nameArrCheck;
unsigned int* countArrCheck;
double* priceArrCheck;
double* totalPriceArrCheck;

double cashIncome = 0.0;
double bankIncome = 0.0;
double cash = 5000 + rand() % 3000;

void Selling();
void CheckArrPushback();
void PrintCheck(double& totalSum);
void StorageRaturner();

//===================== Служебные ======================
std::unordered_set<char> specialSymbols;
std::unordered_set<char> passSymbols;
bool isPassSetCreated = false;
bool isSetCreated = false;

void Start();
bool Login();
bool Logout();
void CreateStorage();
void Getline(std::string& str);
void Err();
bool CheckPass(const std::string& str);
void SetPassSymbols();
bool IsNumber(std::string& str);
void ShowSuperAdminMenu();
void ShowAdminMenu();
void ShowUserMenu();
void ShowsIncome();
bool CheckLogin(const std::string& str);
void Getline(std::string& str);

//======================== Мэйн ==============================

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	Start();

	delete[]loginArr;
	delete[]passArr;
	delete[]statusArr;
	delete[]userIdArr;
	if (isStorageCreate)
	{
		delete[]idArr;
		delete[]nameArr;
		delete[]countArr;
		delete[]priceArr;
	}

	return 0;
}

template<typename ArrType>
void FillArr(ArrType* dynamicArr, ArrType* staticArr, size_t arraySize)
{
	for (size_t i = 0; i < arraySize; i++)
	{
		dynamicArr[i] = staticArr[i];
	}
}

bool IsNumber(std::string& str)
{
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Ошибка! Неверный ввод!\n";
		std::cout << "Максимальная длина числа от 1 до 9 символов!\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Ошибка!! Неверный ввод!\n";
			std::cout << "Можно вводить только цифры!\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

void Getline(std::string& str)
{
	std::getline(std::cin, str, '\n');
}

void Selling()
{
	std::string chooseId, chooseCount, chooseMoney, choose;
	unsigned int id = 0, count = 0, index = -1;
	double money = 0.0, totalSum = 0.0;
	bool isFirst = false;
	checkSize = 0;

	while (true)
	{
		ShowStorage();

		std::cout << "Введите ID товара покупки или \"exit\" для завершения покупок: ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			system("cls");
			if (isFirst == false)
			{
				std::cout << "Выход без покупок\n";
				Sleep(1500);
				system("cls");
				break;
			}
			PrintCheck(totalSum);
			std::cout << "Подтвердить покупку\n1 - Да\n2 - Добавить еще товар\n3 - Отмена\nВвод: ";
			Getline(choose);
			if (choose == "1")
			{
				while (true)
				{
					system("cls");
					std::cout << "Выберите способ оплаты\n1 - Наличными\n2 - Безнал\nВвод: ";
					Getline(choose);
					if (choose == "1")
					{
						std::cout << "Введите кол-во налчиных: ";
						Getline(chooseMoney);
						if (IsNumber(chooseMoney))
						{
							money = std::stod(chooseMoney);
							if (money < totalSum)
							{
								std::cout << "Недостаточно средств!\n";
								Sleep(1500);
								continue;
							}
							else if (money - totalSum > cash)
							{
								std::cout << "Нет сдачи олух!!\nПовторите попытку!\n";
								Sleep(1500);
								continue;
							}
							else
							{
								std::cout << "Ваши: " << money << "\n";
								Sleep(300);
								std::cout << "Оплата прошла успешно. Сдача: " << money - totalSum << "рублей\n";
								Sleep(1000);
								cash += totalSum;
								cash -= money - totalSum;
								cashIncome += totalSum;
								salesArr[currentId] += totalSum;
								system("cls");
								break;
							}
						}
					}
					else if (choose == "2")
					{
						std::cout << "Приложите карту'\n\n";
						Sleep(1500);
						if (rand() % 10 <= 2)
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Sleep(500);
							}
							std::cout << "Соеденение не установлено. Повторите попытку\n";
							Sleep(1500);
							system("cls");
						}
						else
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Sleep(500);
							}
							std::cout << "Оплата прошла успешно\n\nСпасибо за покупку!\n";
							bankIncome += totalSum;
							salesArr[currentId] += totalSum;
							
							Sleep(1500);
							break;
						}
					}
					else if (choose == "sergo")
					{
						std::cout << "Серго оплатил вам чек. Всего доброго)))\n";
						Sleep(1500);
						system("cls");
						break;
					}
					else
					{
						Err();
						continue;
					}
				}
			}
			else if (choose == "2")
			{
				continue;
			}
			else if (choose == "3")
			{
				std::cout << "Отмена покупки!\n";
				StorageRaturner();
				Sleep(1500);
				system("cls");
				return;
			}
			else
			{
				Err();
				continue;
			}
			delete[]idArrCheck;
			delete[]nameArrCheck;
			delete[]countArrCheck;
			delete[]priceArrCheck;
			delete[]totalPriceArrCheck;
			idArrCheck = nullptr;
			nameArrCheck = nullptr;
			countArrCheck = nullptr;
			priceArrCheck = nullptr;
			totalPriceArrCheck = nullptr;
			system("cls");
			break; 
		}
		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			continue;
		}
		std::cout << "\nВведите кол-во товаров или \"exit\" для завершения покупок: ";
		Getline(chooseCount);
		if (chooseCount == "exit")
		{
			std::cout << "Отмена покупки товара: " << nameArr[id] << "\n\n";
			Sleep(1500);
			continue;
		}

		if (IsNumber(chooseCount))
		{
			count = std::stoi(chooseCount);
			if (count < 1 || count > countArr[id])
			{
				std::cout << "Ошибка кол-во!! Максимум: " << countArr[id] << "\n\n";
				Sleep(1500);
				continue;
			}
		}
		else
		{
			continue;
		}

		CheckArrPushback();

		if (isFirst == false)
		{
			isFirst = true;
		}
		index++;
		idArrCheck[index] = idArr[id];
		nameArrCheck[index] = nameArr[id];
		priceArrCheck[index] = priceArr[id];
		countArrCheck[index] = count;
		idArrCheck[index] = idArr[id];
		totalPriceArrCheck[index] = count * priceArr[id];
		countArr[id] -= count;
		totalSum += totalPriceArrCheck[index];

		std::cout << "Товар успешно добавлен в чек\n\n";

		Sleep(1000);
	}
}

void CheckArrPushback()
{
	checkSize++;
	int* idArrCheckTemp = new int [checkSize];
	std::string* nameArrCheckTemp = new std::string[checkSize];
	unsigned int* countArrCheckTemp = new unsigned int[checkSize];
	double* priceArrCheckTemp = new double[checkSize];
	double* totalPriceArrCheckTemp = new double[checkSize];

	FillArr(idArrCheckTemp, idArrCheck, checkSize - 1);
	FillArr(nameArrCheckTemp, nameArrCheck, checkSize - 1);
	FillArr(countArrCheckTemp, countArrCheck, checkSize - 1);
	FillArr(priceArrCheckTemp, priceArrCheck, checkSize - 1);
	FillArr(totalPriceArrCheckTemp, totalPriceArrCheck, checkSize - 1);

	std::swap(idArrCheckTemp, idArrCheck);
	std::swap(nameArrCheckTemp, nameArrCheck);
	std::swap(countArrCheckTemp, countArrCheck);
	std::swap(priceArrCheckTemp, priceArrCheck);
	std::swap(totalPriceArrCheckTemp, totalPriceArrCheck);

	delete[]idArrCheckTemp;
	delete[]nameArrCheckTemp;
	delete[]countArrCheckTemp;
	delete[]priceArrCheckTemp;
	delete[]totalPriceArrCheckTemp;

}

void StorageRaturner()
{
	for (size_t i = 0; i < checkSize; i++)
	{
		countArr[idArrCheck[i] - 1] += countArrCheck[i];
	}


	delete[]idArrCheck;
	delete[]nameArrCheck;
	delete[]countArrCheck;
	delete[]priceArrCheck;
	delete[]totalPriceArrCheck;
	checkSize = 0;
	idArrCheck = nullptr;
	nameArrCheck = nullptr;
	countArrCheck = nullptr;
	priceArrCheck = nullptr;
	totalPriceArrCheck = nullptr;
}
void PrintCheck(double& totalSum)
{
	std::cout << "#\t" << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена за ед\t" << "Кол-во\t" << "Итого:\n";


	for (size_t i = 0; i < checkSize; i++)
	{
		std::cout << i + 1 << "\t" << idArrCheck[i] << "\t" << std::left << std::setw(25)
		<< nameArrCheck[i] << "\t" << priceArrCheck[i] << "\t\t" << countArrCheck[i] << "\t" << totalPriceArrCheck[i] << "\n";

	}
	std::cout << "\nитого к оплате: " << totalSum << "\n\n";


}

void Start()
{
	std::cout << "\n\n\n\t\t\tDota Market\n\n\n";

	std::string choose;

	if (Login())
	{
		system("cls");
		if (currentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Ваш выбор: \n1 - Готовый\n2 - Новый\nВвод: ";
				Getline(choose);
				if (choose == "1")
				{
					if (isStorageCreate == false)
					{
						CreateStorage();
					}
					system("cls");
					ShowSuperAdminMenu();
					break;
				}
				else if (choose == "2")
				{
					if (isStorageCreate == false)
					{

					}
					system("cls");
					ShowSuperAdminMenu();
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
			if (isStorageCreate == false)
			{
				CreateStorage();
			}
			ShowSuperAdminMenu();
		}
		else if (currentStatus == userStatus[2])
		{
			if (isStorageCreate == false)
			{
				CreateStorage();
			}
			ShowUserMenu();
		}
	}
	else
	{
		system("cls");
		std::cout << "Итоговая прибыль за сменуЖ " << cashIncome + bankIncome;
		std::cout << "\n\n\nЗавершение работы\n";
		Sleep(2000);
		system("cls");

	}
}

void Err()
{
	std::cout << "Ошибка!! Неверный ввод!\n";
	Sleep(1500);
	system("cls");
}

bool CheckPass(const std::string& str)
{
		if (str.size() < 8 || str.size() > 30)
		{
			std::cout << "Ошибка длины пароля\n";
			Sleep(1500);
			return false;
		}

		int numCount = 0, sumCount = 0;

		std::unordered_set<char> specialPassSym{ '!', '@', '#', '%', '$', '^', '&', '*', '(', ')', '_', '-', '=',
		'+', '/', '?', '|', ',','<', '>', '~', '`', ':', ';', '{', '}', '[', ']' };

		for (char sym : str)
		{
			if (!passSymbols.count(sym))
			{
				std::cout << "Неккоретный ввод\n ";
				Sleep(1500);
				return false;
			}

			if (std::isdigit(sym))
			{
				numCount++;
			}

			if (specialPassSym.count(sym))
			{
				sumCount++;
			}
		}

		if (numCount > 2 && sumCount > 2)
		{
			return true;
		}
		else
		{
			std::cout << "Минимум 3 символа и 3 цифры ";
			return false;
		}
	}

bool Login()
{
	std::string login, pass;

	while (true)
	{
		std::cout << "Введите логин: ";
		Getline(login);
		std::cout << "Введите пароль: ";
		Getline(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		for (size_t i = 0; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				system("cls");
				std::cout << "Добро пожаловать, " << loginArr[i] << "\n\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				currentId = userIdArr[i];
				return true;
			}
		}
		Err();
	}
}

bool Logout()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "Для подтверждения выхода из пользователя введите ваш пароль или \"exit\" для возврата в меню \n";
		Getline(choose);
		if (choose == "exit")
		{
			system("cls");
			return false;
		}
		else if (choose == passArr[currentId - 1] || choose == passArr[0])
		{
			system("cls");
			return true;
		}
		else
		{
			Err();
		}
	}
}

void ShowSuperAdminMenu()
{
	system("cls");

	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчёт о прибыли\n";
		std::cout << "0 - Выход из системы\n";
		std::cout << "Выбор: ";
		Getline(choose);

		if (choose == "1" && storageSize > 0)
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage();
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccounts();
		}
		else if (choose == "8")
		{
			ShowsIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
		}
		else
		{
			Err();
		}
	}
	system("cls");
}

void ShowAdminMenu()
{
	system("cls");

	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчёт о прибыли\n";
		std::cout << "0 - Выход из системы\n";
		std::cout << "Выбор: ";
		Getline(choose);

		if (choose == "1" && storageSize > 0)
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage();
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccounts();
		}
		else if (choose == "8")
		{
			ShowsIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
		}
		else
		{
			Err();
		}
	}
	system("cls");
}

void ShowUserMenu()
{
	system("cls");

	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "8 - Отчёт о прибыли\n";
		std::cout << "0 - Выйти со смены\n";
		std::cout << "Выбор: ";
		Getline(choose);

		if (choose == "1" && storageSize > 0)
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage();
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeAccounts();
		}
		else if (choose == "8")
		{
			ShowsIncome();
		}
		else if (choose == "0")
		{
			if (Logout() == true)
			{
				break;
			}
		}
		else
		{
			Err();
		}
	}
	system("cls");
}

void ShowsIncome()
{
	system("cls");
	std::cout << "Текущая прибыль за смену\n\n";
	std::cout << "Наличный расчет: " << cashIncome << "\n";
	std::cout << "Безналичный расчет: " << bankIncome << "\n";
	std::cout << "Итого: " << bankIncome + cashIncome << "\n";
	std::cout << "Сумма ваших продаж: " << salesArr[currentId] << "\n\n";

	system("pause");
	system("cls");

}
bool CheckLogin(const std::string& str)
{
	if (str.size() < 5 || str.size() >= 20)
	{
		std::cout << "Ошибка!! Неверная длина логина. От 5 до 20\n";
		Sleep(1500);
		return false;
	}
	for (char sym : str)
	{
		if (!specialSymbols.count(sym))
		{
			std::cout << "Запрещённый символ в логине!\n\n";
			Sleep(1500);
			return false;
		}
	}

	for (size_t i = 0; i < userSize; i++)
	{
		if (str == loginArr[i])
		{
			std::cout << "Это имя уже занято!";
			Sleep(1500);
			return false;
		}
	}

	return true;
}

bool CheckSymbols(const std::string& str)
{
	if (str.size() < 8 || str.size() > 20)
	{
		std::cout << "Ошибка длины пользователя!\n";
		Sleep(1500);
		return false;
	}

	int numCount = 0, symCount = 0;

	std::unordered_set<char> specialPassSymbols{ '~', ' ', '{', '}', '-', '<', '>', '%', '|', '?', ',', '*', '/'};

	for (char sym : str)
	{
		if (!passSymbols.count(sym))
		{
			std::cout << "Неверный ввод!\n";
			Sleep(1500);
			return false;
		}

		if (std::isdigit(sym))
		{
			numCount++;
		}

		if (specialPassSymbols.count(sym))
		{
			symCount++;
		}
	}

	if (numCount > 2 && symCount > 3)
	{
		return false;
	}
	else
	{
		std::cout << "Ошибка!! Должно быть минимум 3 символа и 3 цифры!\n";
		return false;
	}

}

// админ не может менять пароль другим админам

void ChangePass()
{
	std::string choose, newPass1, newPass2;
	int userNumber = 0;
	int isAdmin = 0;

	while (true)
	{
		if (currentStatus == userStatus[0])
		{
			ShowUsers(1);
			isAdmin = 0;
		}
		else
		{
			ShowUsers();
			isAdmin = 1;
		}
		system("cls");
		std::cout << "Введите номер пользователя или \"exit\" для выхода: ";
		Getline(choose);

		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}

		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);

			if (userNumber < isAdmin || userNumber > userSize - 1)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
				break;
			}

			if (currentStatus == userStatus[1] && statusArr[userNumber] == userStatus[1])
			{
				std::cout << "Нельзя менять пароли администраторам!\n";
				Sleep(1500);
				break;
			}

			for (size_t i = isAdmin; i < userSize; i++)
			{
				if (i == userNumber)
				{
					std::cout << "Введите новый пароль для пользователя " << loginArr[i] << "\n\n";
					Getline(newPass1);
					std::cout << "Подтвердите пароль для пользователя " << loginArr[i] << "\n\n";
					Getline(newPass2);

					if (CheckPass(newPass1) && CheckPass(newPass2) && newPass1 == newPass2)
					{
						passArr[i] = newPass1;
						std::cout << "Успешная смена пароля!\n";
						Sleep(1500);
						break;
					}
					else
					{
						std::cout << "Повторите попытку\n\n";
						Sleep(1500);
						i--;
					}
				}
			}
		}
	}
}

void ChangeAccounts()
{
	std::string choose;
	if (isSetCreated == false)
	{
		SetSpecialSymbols();
	}

	if (isPassSetCreated == false)
	{
		SetPassSymbols();
	}

	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить нового пользователя\n";
		std::cout << "2 - Показать пользователей\n";
		std::cout << "3 - Изменить пароль пользователя\n";
		std::cout << "4 - Удалить пользователя\n";
		std::cout << "0 - Выход\n";
		std::cout << "Выбор: ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewUsers();
		}
		else if (choose == "2" && userSize > 1)
		{
			ShowUsers(0);
		}
		else if (choose == "3" && userSize > 1)
		{
			ChangePass();
		}
		else if (choose == "4" && userSize > 1)
		{

		}
		else if (choose == "0")
		{
			if (userSize < 1)
			{
				std::cout << "Нет доступных пользователей\n\n";
			}
			system("cls");
			break;
		}
		else
		{
			Err();
		}
	}
}

void ShowUsers(int mode)
{
	if (mode == 0)
	{
		system("cls");
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 1; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i] << "\t\t\t" << statusArr[i] << "\n";
		}
		Sleep(2000);
	}
	else if (mode == 1)
	{
		system("cls");
		std::cout << "№\t" << std::left << std::setw(12) << "Логин\t\t" << "Пароль\t\t\t" << "Роль\n";
		for (size_t i = 0; i < userSize; i++)
		{
			std::cout << i << "\t" << std::left << std::setw(8) << loginArr[i] << "\t\t" << passArr[i] << "\t\t\t" << statusArr[i] << "\n";
		}
		Sleep(2000);
	}

}

void AddNewUsers()
{
	std::string newLogin, newPass, newRole, choose;
	bool exit = true;
	while (true)
	{
		while (true)
		{
			system("cls");
			std::cout << "Введите логин нового пользователя или \"exit\" для выхода: ";
			Getline(newLogin);

			if (newLogin == "exit")
			{
				std::cout << "Добавление нового пользователя отменено!\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (CheckLogin(newLogin))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые символы: a-z, A-Z, 0-9\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "Введите пароль нового пользователя или \"exit\" для выхода: ";
			Getline(newPass);

			if (newPass == "exit")
			{
				std::cout << "Добавление нового пользователя отменено!\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (CheckPass(newPass))
			{
				break;
			}
			else
			{
				std::cout << "Допустимые символы: a-z, A-Z, 0-9\n";
				Sleep(1500);
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "1 - Администратор, 2 - Сотрудник\n";
			std::cout << "Введите роль для нового пользователя или \"exit\" для выхода: ";
			Getline(choose);

			if (choose == "exit")
			{
				std::cout << "Добавление нового пользователя отменено!\n";
				Sleep(1500);
				exit = false;
				break;
			}

			if (choose == "1")
			{
				newRole = userStatus[1];
				break;
			}
			else if (choose == "2")
			{
				newRole = userStatus[2];
				break;
			}
			else
			{
				Err();
			}

		}

		while (exit)
		{
			system("cls");
			std::cout << "Пользователь: " << newLogin << "\n";
			std::cout << "Пароль: " << newPass << "\n";
			std::cout << "Роль: " << newRole << "\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			Getline(choose);
			
			if (choose == "1")
			{
				userSize++;
				if (newRole == userStatus[2])
				{
					staffCount++;
				}
				std::string* loginArrTemp = new std::string[userSize];
				std::string* passArrTemp = new std::string[userSize];
				std::string* statusArrTemp = new std::string[userSize];
				double* salesArrTemp = new double[userSize];
				unsigned int* userIdArrTemp = new unsigned int[userSize];

				FillArr(loginArrTemp, loginArr, userSize - 1);
				FillArr(passArrTemp, passArr, userSize - 1);
				FillArr(statusArrTemp, statusArr, userSize - 1);
				FillArr(salesArrTemp, salesArr, userSize - 1);
				FillArr(userIdArrTemp, userIdArr, userSize - 1);

				loginArrTemp[userSize - 1] = newLogin;
				passArrTemp[userSize - 1] = newPass;
				statusArrTemp[userSize - 1] = newRole;
				salesArrTemp[userSize - 1] = 0.0;
				userIdArr[userSize - 1] = userSize;

				std::swap(loginArrTemp, loginArr);
				std::swap(passArrTemp, passArr);
				std::swap(statusArrTemp, statusArr);
				std::swap(salesArrTemp, salesArr);
				std::swap(userIdArrTemp, userIdArr);

				delete[] loginArrTemp;
				delete[]passArrTemp;
				delete[]statusArrTemp;
				delete[]salesArrTemp;
				delete[]userIdArrTemp;

				std::cout << "Идёт обработка... \n";
				Sleep(2000);
				std::cout << "Пользователь успешно добавлен!\n\n";
				Sleep(1500);

			}
			else if (choose == "2")
			{
				std::cout << "Отмена операции!\n";
				Sleep(1500);
				break;
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

void SetSpecialSymbols()
{
	for (char i = '0'; i <= '9'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'A'; i <= 'Z'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		specialSymbols.insert(i);
	}
	isSetCreated = true;
}

void SetPassSymbols()
{
	for (char i = '!'; i <= '&'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '('; i <= '+'; i++)
	{
		passSymbols.insert(i);
	}
	for (char i = '.'; i <= '~'; i++)
	{
		passSymbols.insert(i);
	}
	isPassSetCreated = true;
}

void CreateStorage()
{
	const size_t staticSize = 10;

	unsigned int id[staticSize]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::string name[staticSize]
	{
		"Arcane", "Seasonal", "Ancient", "Immortal", "Legendary", "Mythical",
		"Rare", "Uncommon", "Common",
		"Буст ммр"
	};
	double price[staticSize]
	{
		2000, 3500, 1800, 1000, 500, 300, 150, 100, 50, 10000
	};
	unsigned int count[staticSize]{ 100, 20, 30, 341, 551, 635, 1023, 6301, 10913, 20};

	if (isStorageCreate)
	{
		delete[]idArr;
		delete[]nameArr;
		delete[]countArr;
		delete[]priceArr;
	}

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

void ShowStorage(int mode)
{
	if (mode == 0)
	{
		system("cls");
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
		system("pause");
		system("cls");
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" << "Цена\n.";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\t" << priceArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\n";
		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << "\t" << std::left << std::setw(25) << nameArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}

}

void AddStorageItem()
{
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
			std::cout << "Операция добавления отменена!\n";
			Sleep(1500);
			system("cls");
			break;
		}

		std::cout << "Введите кол-во товара для добавления -> ";
		Getline(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > maxItemSize)
			{
				std::cout << "Неверный ID или кол-во\nМаксимальное кол-во - " << maxItemSize;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << " -----> " << countArr[id] + count << "\n\n";
				std::cout << "Подтвердить?\n Да - 1\t Нет - 2\nВыбор -> ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] += count;
					std::cout << "Товар успешно добавлен!\n\n";
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

void ChangeStorage()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить название товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - Назад в главное меню\n";
		std::cout << "Выбор >> ";
		Getline(choose);
		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ChangeName();
		}
		else if (choose == "3" && storageSize > 0)
		{
			DeleteItem();
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

void RemoveStorageItem()
{
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
			std::cout << "Операция удаления отменена!\n";
			Sleep(1500);
			system("cls");
			break;
		}

		std::cout << "Введите кол-во товара для удаления -> ";
		Getline(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Неверный ID или кол-во\nМаксимальное кол-во - " << maxItemSize;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << countArr[id] << " -----> " << countArr[id] - count << "\n\n";
				std::cout << "Подтвердить?\n Да - 1\t Нет - 2\nВыбор -> ";
				Getline(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Товар успешно удален!\n\n";
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

void ChangePrice()
{
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
			std::cout << "Операция изменения цены отменена!\n";
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
				std::cout << "Неверный ID или цена\nМаксимальная цена - " << 499999;
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] << "\t" << priceArr[id] << " -----> " << newPrice << "\n\n";
				std::cout << "Подтвердить?\n Да - 1\t Нет - 2\nВыбор -> ";
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
			std::cout << "Добавление нового товара!\n\nВведите \"exit\" для отмены операции\n\n";
			std::cout << "Введите название нового товара: ";
			Getline(newName);

			if (newName == "exit")
			{
				std::cout << "Операция добавления товара отменена!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (newName.size() <= 0 || newName.size() >= 15)
			{
				std::cout << "Неверная длина названия максимум 13 символов\n";
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
			std::cout << "Введите количество нового товара: ";
			Getline(newCount);

			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара отменена!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > maxItemSize)
				{
					std::cout << "Превышено максимальное количество товара. Не более" << maxItemSize << "шт.\n\n";
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
				std::cout << "Операция добавления товара отменена!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (IsNumber(newPrice))
			{
				price = std::stod(newPrice);
				if (price > 99999)
				{
					std::cout << "Превышена максимальная цена товара. Не более" << 99999 << "руб.\n\n";
				}
				else
				{
					break;
				}
			}

		}
		if (exit)
		{
			std::cout << "Новый товар:" << newName << "\nКоличество: " << count << "\nЦена: " << price << "\n\n";
			std::cout << "Подтвердить?\nДа - 1\nНет - 2\nВыбор >> ";
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

				delete[]idArrTemp;
				delete[]nameArrTemp;
				delete[]countArrTemp;
				delete[]priceArrTemp;
				std::cout << "Идет обработка... \n";
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
			std::cout << "Операция изменения названия отменена!\n\n";
			Sleep(1500);
			break;
		}

		std::cout << "Введите новое название товара: ";
		Getline(newName);

		if (newName.size() <= 0 || newName.size() >= 50 || newName == "exit")
		{
			std::cout << "Ошибка.Максимальная длина названия 50 символов.\n";
			Sleep(1500);
		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;

			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Неверный ID!\n";
				Sleep(1500);
			}
			else
			{
				id = std::stoi(chooseId) - 1;
				std::cout << "\n" << std::left << std::setw(25) << nameArr[id] << " -----> " << newName << "\n\n";
				std::cout << "Подтвердить?\n Да - 1\t Нет - 2\nВыбор -> ";
				Getline(choose);
				if (choose == "1")
				{
					nameArr[id];
					std::cout << "Название товара успешно изменено\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена\n";
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

void DeleteUser()
{
	std::string chooseNumber, choose, checkPass;

	int userNumber = 0;
	int isAdmin = 0;

	while (true)
	{
		if (currentStatus == userStatus[0])
		{
			if (userSize < 2)
			{
				std::cout << "Нет пользователей для удаления!\n";
				Sleep(1500);
				return;
			}
			ShowUsers();
			isAdmin = 1;
		}
		else if (currentStatus == userStatus[1])
		{
			if (staffCount < 1)
			{
				std::cout << "Нет пользователей для удаления!\n";
				Sleep(1500);
				return;
			}
		}
		ShowUsers();
		isAdmin = 1;

		std::cout << "Введите номер пользователя для удаления или \"exit\" для выхода: ";
		Getline(choose);

		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}

		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);

			if (userNumber < isAdmin || userNumber > userSize - 1)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
			}

			for (size_t i = isAdmin; i < userSize; i++)
			{
				if (i == userNumber)
				{
					system("cls");

					if (currentStatus == userStatus[1] && statusArr[userNumber] != userStatus[2])
					{
						std::cout << "Нельзя удалять администратора\n";
						Sleep(1500);
						break;
					}
					std::cout << "Удалить пользователя " << loginArr[i] << "\n\n";
					std::cout << "Для подтверждения введите пароль G.A. или \"exit\" для выхода: ";
					Getline(checkPass);

					if (checkPass == "exit")
					{
						std::cout << "Отмена удаления пользователя " << loginArr[i] << "\n\n";
						Sleep(1500);
						break;
					}
					else if (checkPass == passArr[0])
					{
						userSize--;
						if (statusArr[userNumber] == userStatus[2])
						{
							staffCount--;
						}
						std::string* loginArrTemp = new std::string[userSize];
						std::string* passArrTemp = new std::string[userSize];
						std::string* statusArrTemp = new std::string[userSize];
						double* salesArrTemp = new double[userSize];
						unsigned int* userIdArrTemp = new unsigned int[userSize];

						for (size_t i = 0, c = 0; i < storageSize; i++, c++)
						{
							if (userNumber == c)
							{
								c++;
							}
							passArrTemp[i] = passArr[c];
							statusArrTemp[i] = statusArr[c];
							loginArrTemp[i] = loginArr[c];
							salesArrTemp[i] = salesArr[c];
							userIdArrTemp[i] = userIdArr[c];

						}

						std::swap(loginArrTemp, loginArr);
						std::swap(passArrTemp, passArr);
						std::swap(statusArrTemp, statusArr);
						std::swap(salesArrTemp, salesArr);
						std::swap(userIdArrTemp, userIdArr);

						delete[] loginArrTemp;
						delete[]passArrTemp;
						delete[]statusArrTemp;
						delete[]salesArrTemp;
						delete[]userIdArrTemp;

						std::cout << "Идёт обработка... \n";
						Sleep(2000);
						std::cout << "Пользователь успешно удалён!\n\n";
						Sleep(1500);
					}
					else
					{
						std::cout << "Неверный пароль!\n\n";
						Sleep(1500);
						i--;
					}
				}
			}
		}
		else
		{
			Err();
		}

	}

}

void DeleteItem()
{
	std::string chooseId, choose;
	unsigned int id = 0;

	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара для удаления или \"exit\" для выхода ";
		Getline(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Операция удаления товара отменена!\n\n";
			Sleep(1500);
			break;
		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Неверный ID\n";
				Sleep(1500);
			}
			else
			{
				std::cout << "Удалить товар " << nameArr[id] << "\n\n";
				std::cout << "Подтвердить?\nДа - 1\nНет - 2\nВыбор:";
				Getline(choose);

				if (choose == "1")
				{
					storageSize--;
					unsigned int* idArrTemp = new unsigned int[storageSize];
					std::string* nameArrTemp = new std::string[storageSize];
					unsigned int* countArrTemp = new unsigned int[storageSize];
					double* priceArrTemp = new double[storageSize];
					for (size_t i = 0, c = 0; i < storageSize; i++, c++)
					{
						if (id == c)
						{
							c++;
						}
						idArrTemp[i] = i + 1;
						nameArrTemp[i] = nameArr[c];
						countArrTemp[i] = countArr[c];
						priceArrTemp[i] = priceArr[c];

					}
					std::swap(idArr, idArrTemp);
					std::swap(nameArr, nameArrTemp);
					std::swap(countArr, countArrTemp);
					std::swap(priceArr, priceArrTemp);

					delete[]idArrTemp;
					delete[]nameArrTemp;
					delete[]countArrTemp;
					delete[]priceArrTemp;
					std::cout << "Идёт обработка... \n";
					Sleep(2000);
					std::cout << "Товар успешно удален!\n\n";
					Sleep(1500);
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена операции удаления";
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