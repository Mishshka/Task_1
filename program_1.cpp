#include "program_1.h"

int main() {
	// делаем возможным ввод/вывод кириллицей
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//приветствие
	cout << "\t\t\t\tЗдраствуйте!\n\tДанная программа поможет Вам внести информацию о студентах и их паролях для работы на ЭВМ.\n\tДля работы программы необходимо наличие папок \"Students\" и \"Passwords\" в текущей директории.\n\tПри их отсутствии они будут автоматически созданы." << endl;

	//работа с директорией: проверка + создание папок
    vector<string> requiredFolders = { "Students", "Passwords" };
    cout << "\n\t\t\t\tПроверка директории" << endl;
    for (const auto& folder : requiredFolders) {
        if (!fs::exists(folder)) {
            if (fs::create_directory(folder)) {
                cout << "\tПапка '" << folder << "' создана успешно." << endl;
            }
            else {
                cout << "\tОшибка при создании папки '" << folder << "'" << endl;
            }
        }
        else {
            cout << "\tПапка '" << folder << "' уже существует." << endl;
        }
    }

	return 0;

}


