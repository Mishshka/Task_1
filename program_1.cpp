#include "program_1.h"

int count_files(string folder_name) { //функция для подсчета числа файлов в папке
	int i = 0;
	for (auto& p : fs::directory_iterator(folder_name)) {
		i++;
	}
	return i;
}
string* get_filenames(string folder_name) { // функция для создания массива из названий файлов в папке
	int len = count_files(folder_name);
	string* list_names = new string[len];
	int i = 0;
	for (auto& p : fs::directory_iterator(folder_name)) {
		list_names[i] = fs::path(p).string();
		i++;
	}
	return list_names;
}
void write_stud(FILE* fout) {
	ClearScreen();
	printf("Для ввода информации о студентах, заполните поля ниже.\nНажмите\
 Enter для подтверждения ввода или введите '#'  для возвращения в меню без сохранения введенных данных.\nВ случае, когда информация для данного поля отсутствует введите '-'\n\
Введение '0' в поле 'номер по списку' равносильно введению '-'.\n\n");
	Stud st_in;
	char inp[size_c];
	bool ex = true;
	int a;
	int max_fam(0), max_num(0), max_gr(0);
	fseek(fout, 0, SEEK_END);
	while (ex) {
		int fl = -1; //проверка на правильность введеной информации
		// Ввод фамилии
		while (fl != 1) {
			printf("Введите Фамилию студента: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			if (ex == false) {
				fl = 1;
				break;
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(RUS_let + '-')) != string::npos) {
				printf("%*c\n", a + 27, '^');
				printf("\nОшибка\nПоле Фамилия может состоять только из букв русского алфавита и дефиса\nПовторите ввод\n");
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if ((inp[strlen(inp) - 1] == '-' and strlen(inp) > 1)) {
				printf("%*c\n", strlen(inp) + 26, '^');
				printf("\nОшибка\nБуквенная комбинация не может оканчиваться символом '-'.\nПовторите ввод\n");
				fl = -1;
			}
			else {
				if (inp[0] >= -33 and inp[0] <= -1) {
					inp[0] -= 32;
				}
				for (int l_c = 1; l_c < strlen(inp); l_c++) {
					if (inp[l_c] <= -33) inp[l_c] = inp[l_c] + 32;
					if (inp[l_c] >= -33 and inp[l_c - 1] == 45)
					{
						inp[l_c] -= 32;
					}
				}
				strncpy_s(st_in.family, inp, sizeof(st_in.family) - 1);
				if (strlen(st_in.family) > max_fam) {
					max_fam = strlen(st_in.family);
				}
				fl = 1;
			}
		}
		if (ex == false) {
			break;
		}
		fl = -1;
		// Ввод группы
		while (fl != 1) {
			printf("Введите группу студента: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			if (ex == false) {
				fl = 1;
				break;
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(RUS_let + num + '-')) != string::npos) {
				printf("%*c\n", a + 26, '^');
				printf("\nОшибка\nПоле Группа может состоять только из букв русского алфавита, цифр и дефиса\nПовторите ввод\n");
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if ((inp[strlen(inp) - 1] == '-' and strlen(inp) > 1)) {
				printf("\nОшибка\nПоле не должно заканчиваться символом '-'\nПовторите ввод\n");
				fl = -1;
			}
			else {
				strncpy_s(st_in.group, inp, sizeof(st_in.group) - 1);
				if (strlen(st_in.group) > max_gr) {
					max_gr = strlen(st_in.group);
				}
				fl = 1;
			}
		}
		if (ex == false) {
			break;
		}
		fl = 0;
		// Ввод номера по списку
		while (fl != 1) {
			printf("Введите номер по списку студента: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			if (ex == false) {
				fl = 1;
				break;
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(num + '-')) != string::npos) {
				printf("%*c\n", a + 35, '^');
				printf("\nОшибка\nДля записи номера по списку используйте либо только цифры, либо только символ \"-\"\nПовторите ввод\n");
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if (str.length() >= 4) {
				printf("\nОшибка\nНомер по списку должен быть меньше 1000\nПовторите ввод\n");
				fl = -1;
			}
			else {
				bool isn = true;
				if (str != "-") {
					for (int i = 0; i < str.length(); i++) {
						if (!(inp[i] >= '0' and inp[i] <= '9')) {
							isn = false;
						}
					}
					if (isn) {
						int inp_test = stoi(str);
						if (inp_test == 0) {
							memset(inp, '\0', sizeof(inp));
							inp[0] = '-';
						}
						
						else {
							if (inp_test > 0 and inp[0] == '0') {
								memset(inp, '\0', sizeof(inp));
								sprintf_s(inp, "%d", inp_test);
							}
							if (inp_test < 0) {
								inp_test *= -1;
								memset(inp, '\0', sizeof(inp));
								sprintf_s(inp, "%d", inp_test);
							}
						}
						strncpy_s(st_in.gr_ind, inp, sizeof(st_in.gr_ind) - 1);
						fl = 1;
					}
					else {
						printf("\nОшибка\nДля записи номера по списку используйте либо только цифры, либо только символ \"-\"\nПовторите ввод\n");
						fl = -1;
					}
				}
				else {
					strncpy_s(st_in.gr_ind, inp, sizeof(st_in.gr_ind) - 1);
					if (strlen(st_in.gr_ind) > max_num) {
						max_num = strlen(st_in.gr_ind);
					}
					fl = 1;
				}
			}
		}
		if (ex == false) {
			break;
		}
		fl = -1;
		//проверка на не пустой ввод
		if (st_in.family[0] == '-' and st_in.gr_ind[0] == '-' and st_in.group[0] == '-')
		{
			printf("Внимание! Вы ввели во все поля символ \"-\". Пожалуйста, повторите ввод, заполнив информацией хотя бы одно поле.\n\n");
		}
		else {
			// Подтверждение данных
			bool val_date = false;
			printf("\nПроверьте правильность вносимых данных:\n");
			printf("Фамилия: %s\n", st_in.family);
			printf("Группа: %s\n", st_in.group);
			printf("Номер по списку: %s\n", st_in.gr_ind);
			printf("\nДля подтверждения данных и продолжения записи нажмите Enter.\n");
			printf("Для изменения полей нажмите R.\n");
			printf("При нажатии на ESC будет осуществлено сохранение введенной информации и возврат в главное меню.\n");
			while (!val_date) {
				int ans = _getch();
				if (ans == 13) { // Enter - подтверждение
					fprintf(fout, "%s;%s;%s\n", st_in.family, st_in.group, st_in.gr_ind);
					fseek(fout, 0, SEEK_SET); // Возвращаемся в начало файла
					fprintf(fout, "%d;%d;%d\n", max_fam, max_gr, max_num);
					fseek(fout, 0, SEEK_END);
					printf("\nДанные успешно записаны!\n");
					printf("\nПродолжаем запись.\n");
					val_date = true;
				}
				else if (ans == 82 || ans == 114 || ans == 234 || ans == 202) { // R или r / К или к - перезапись
					printf("\nПерезапись данных...\n\n");
					val_date = true;
				}
				else if (ans == 27) { // ESC - выход
					fprintf(fout, "%s;%s;%s\n", st_in.family, st_in.group, st_in.gr_ind);
					fseek(fout, 0, SEEK_SET); // Возвращаемся в начало файла
					fprintf(fout, "%d;%d;%d\n", max_fam, max_gr, max_num);
					fseek(fout, 0, SEEK_END);
					printf("\nВозврат в меню...\n");
					ex = false;
					val_date = true;
				}
			}
			
		}
	}
}
void write_pas(FILE* fout) { // функция для заполнения файла с паролями
	ClearScreen();
	printf("Для ввода информации о паролях, заполните поля ниже.\nНажмите\
 Enter для подтверждения ввода или введите '#'  для возвращения в меню без сохранения введенных данных.\nВ случае, когда информация для данного поля отсутствует введите '-'\n\
Введение '0' в поле 'номер по списку' равносильно введению '-'.\n\n");
	Pass pas_in;
	char inp[size_c];
	bool ex = true;
	int a;
	int max_gr (0), max_pass(0), max_num(0);
	fseek(fout, 0, SEEK_END);
	while (ex) {
		int fl = -1; //проверка на правильность введеной информации
		// Ввод группы
		while (fl != 1) {
			printf("Введите группу студента: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			if (ex == false) {
				fl = 1;
				break;
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(RUS_let + num + '-')) != string::npos) {
				printf("%*c\n", a + 26, '^');
				printf("\nОшибка\nПоле Группа может состоять только из букв русского алфавита, цифр и дефиса\nПовторите ввод\n");
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if ((inp[strlen(inp) - 1] == '-' and strlen(inp) > 1)) {
				printf("\nОшибка\nПоле не должно заканчиваться символом '-'\nПовторите ввод\n");
				fl = -1;
			}
			else {
				strncpy_s(pas_in.group, inp, sizeof(pas_in.group) - 1);
				if (strlen(pas_in.group) > max_gr) {
					max_gr = strlen(pas_in.group);
				}
				fl = 1;
			}
		}
		if (ex == false) {
			break;
		}
		fl = -1;
		// Ввод номера по списку
		while (fl != 1) {
			printf("Введите номер студента по списку: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(num + '-')) != string::npos) {
				printf("%*c\n", a + 35, '^');
				printf("\nОшибка\nДля записи номера по списку используйте либо только цифры, либо только символ \"-\"\nПовторите ввод\n");
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if (str.length() >= 4) {
				printf("\nОшибка\nНомер по списку должен быть меньше 1000\nПовторите ввод\n");
				fl = -1;
			}
			else {
				bool isn = true;
				if (str != "-") {
					for (int i = 0; i < str.length(); i++) {
						if (!(inp[i] >= '0' and inp[i] <= '9')) {
							isn = false;
						}
					}
					if (isn) {
						int inp_test = stoi(str);
						if (inp_test == 0) {
							memset(inp, '\0', sizeof(inp));
							inp[0] = '-';
						}
						else {
							if (inp_test > 0 and inp[0] == '0') {
								memset(inp, '\0', sizeof(inp));
								sprintf_s(inp, "%d", inp_test);
							}
							if (inp_test < 0) {
								inp_test *= -1;
								memset(inp, '\0', sizeof(inp));
								sprintf_s(inp, "%d", inp_test);
							}
						}
						strncpy_s(pas_in.gr_ind, inp, sizeof(pas_in.gr_ind) - 1);
						fl = 1;
					}
					else {
						printf("\nОшибка\nДля записи номера по списку используйте либо только цифры, либо только символ \"-\"\nПовторите ввод\n");
						fl = -1;
					}
				}
				else {
					strncpy_s(pas_in.gr_ind, inp, sizeof(pas_in.gr_ind) - 1);
					if (strlen(pas_in.gr_ind) > max_num) {
						max_num = strlen(pas_in.gr_ind);
					}
					fl = 1;
				}
			}
		}
		if (ex == false) {
			break;
		}
		fl = -1;
		// Ввод пароля
		while (fl != 1) {
			printf("Введите пароль студента: ");
			fgets(inp, size_c, stdin);
			// Проверка на выход
			if (strlen(inp) == 2) {
				if (inp[0] == '#') {
					ex = false;
					break;
				}
			}
			// Проверка допустимых символов
			inp[strlen(inp) - 1] = '\0';
			string str(inp);
			if ((a = str.find_first_not_of(num + ENG_let + SPec)) != string::npos) {
				printf("%*c\n", a + 26, '^');
				printf("\nОшибка\nДля записи пароля используйте только буквы латинского алфавита, цифры или символы \"%s\"\nПовторите ввод\n",(SPec.c_str()));
				fl = -1;
			}
			else if (inp[0] == '\0' or inp[0] == '\n') {
				printf("\nОшибка\nПоле не должно быть пустым\nПовторите ввод\n");
				fl = -1;
			}
			else if (str.length() < 4 and str!="-") {
				printf("\nОшибка\nПароль должен быть больше 4 символов\nПовторите ввод\n");
				fl = -1;
			}
			else {
				strncpy_s(pas_in.password, inp, sizeof(pas_in.password) - 1);
				fl = 1;
				if (strlen(pas_in.password) > max_pass) {
					max_pass = strlen(pas_in.password);
				}
			}
		}
		if (ex == false) {
			break;
		}
		fl = -1;
		//проверка на пустоту
		if (pas_in.password[0] == '-' and pas_in.gr_ind[0] == '-' and pas_in.group[0] == '-')
		{
			printf("Внимание! Вы ввели во все поля символ \"-\". Пожалуйста, повторите ввод, заполнив информацией хотя бы одно поле.\n\n");
		}
		else{// Подтверждение данных
			bool val_date = false;
			printf("\nПроверьте правильность вносимых данных:\n");
			printf("Группа: %s\n", pas_in.group);
			printf("Номер по списку: %s\n", pas_in.gr_ind);
			printf("Пароль: %s\n", pas_in.password);
			printf("\nДля подтверждения данных и продолжения записи нажмите Enter.\n");
			printf("Для изменения полей нажмите R.\n");
			printf("При нажатии на ESC будет осуществлено сохранение введенной информации и возврат в главное меню.\n");
			while (!val_date) {
				int ans = _getch();
				if (ans == 13) { // Enter - подтверждение
					fprintf(fout, "%s;%s;%s\n", pas_in.group, pas_in.gr_ind, pas_in.password);
					fseek(fout, 0, SEEK_SET); // Возвращаемся в начало файла
					fprintf(fout, "%d;%d;%d\n", max_gr, max_num, max_pass);
					fseek(fout, 0, SEEK_END);
					printf("\nДанные успешно записаны!\n");
					printf("\nПродолжаем запись:\n");
					val_date = true;
				}
				else if (ans == 82 || ans == 114 || ans == 234 || ans == 202) { // R или r - перезапись
					printf("\nПерезапись данных...\n\n");
					val_date = true;
				}
				else if (ans == 27) { // ESC - выход
					fprintf(fout, "%s;%s;%s\n", pas_in.group, pas_in.gr_ind, pas_in.password);
					fseek(fout, 0, SEEK_SET); // Возвращаемся в начало файла
					fprintf(fout, "%d;%d;%d\n", max_gr, max_num, max_pass);
					fseek(fout, 0, SEEK_END);
					printf("\nВозврат в меню...\n");
					ex = false;
					val_date = true;
				}
			}
		}
		
	}
}
void write_to_file(string folder_name) {
	char bf[size_c];
	string file_name;
	ClearScreen();
	printf("Пожалуйста, введите название файла. Для этого используйте буквы латинского или русского алфавита, цифры, а также символы \"_ -\".\n");
	printf("Ваш файл будет автоматически сохранен с расширением txt, поэтому расширение писать не нужно.\nДля возврата введите пустую строку.\n");
	while (true) {
		// Получаем ввод от пользователя
		fgets(bf, sizeof(bf), stdin);
		bf[strcspn(bf, "\n")] = 0;
		file_name = bf;
		// Проверка на возврат (пустая строка)
		if (file_name.empty()) {
			printf("Возврат в меню...\n");
			return;
		}
		// Проверка допустимых символов
		int a;
		if ((a = file_name.find_first_not_of(ENG_let + num + "_-" + RUS_let)) != string::npos) {
			printf("%*c\n", a + 1, '^');
			printf("Ошибка: используйте только латиницу и кириллицу, а также комбинации цифры и символов \"_ -\". Попробуйте снова:\n");
			continue;
		}
		// Добавляем расширение 
		if (file_name.find(".") == string::npos) {
			file_name += ".txt";
		}
		// Проверка существования файла
		int len = count_files(folder_name);
		string* list_names = get_filenames(folder_name);
		bool file_exists = false;
		for (int i = 0; i < len; i++) {
			if ((folder_name + file_name) == list_names[i]) {
				file_exists = true;
				break;
			}
		}
		// Освобождаем память
		delete[] list_names;
		if (file_exists) {
			printf("Файл '%s' уже существует. Введите другое название:\n", file_name.c_str());
			continue;
		}
		break;
	}
	// Создаем и записываем файл
	string path = folder_name + file_name;
	FILE* fout = NULL;
	errno_t err = fopen_s(&fout, path.c_str(), "w+");
	if (err == 0 && fout != NULL) {
		printf("Создан файл: %s\n", path.c_str());
		if (folder_name == ".\\Students\\") {
			// Пишем первую строку
			fprintf(fout, "\n");
			write_stud(fout);
		}
		else if (folder_name == ".\\Passwords\\")
		{
			// Пишем первую строку
			fprintf(fout, "\n");
			write_pas(fout);
		}
		fclose(fout);
	}
	else {
		printf("Ошибка: не удалось создать файл '%s'\n", path.c_str());
	}
}
void add_to_file(string folder_name) {
	ClearScreen();
	printf("\nФайлы в папке '%s':\n", folder_name.c_str());
	printf("Загрузка списка файлов...");
	printf("\n\n");
	int length = count_files(folder_name);
	string* name_list = get_filenames(folder_name);
	if (length == 0) {
		printf("Файлы не обнаружены. Для создания нового файла нажмите любую клавишу.\n");
		_getch();
		write_to_file(folder_name);
		delete[] name_list;
		return;
	}
	int selected = 0;
	bool ex = false;
	int fl = -1;
	ClearScreen();
	printf("\t\t==== Выбор файла ====\n");
	printf("Папка: %s\n\n", folder_name.c_str());
	printf("Выберите файл для добавления данных (используйте стрелки вверх-вниз для выбора и Enter для подтверждения выбора):\n\n");
	//возврат в меню
	printf("%s0. Возврат в меню\n", (selected == 0 ? "~~> " : "  "));
	//Файлы
	for (int i = 0; i < length; i++) {
		string filename = fs::path(name_list[i]).filename().string();
		printf("%s%d. %s\n", (selected == i + 1 ? "~~>" : "  "), i + 1, filename.c_str());
	}
	while (!ex) {
		//обработка ввода		
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) {
				key = _getch();
				switch (key) {
				case 72:
					selected = (selected - 1) % (length + 1);
					break;
				case 80:
					selected = (selected + 1) % (length + 1);
					break;
				}
				if (selected < 0) selected = length;
				ClearScreen();
				printf("\t\t==== Выбор файла ====\n");
				printf("Папка: %s\n\n", folder_name.c_str());
				printf("Выберите файл для добавления данных (используйте стрелки вверх-вниз для выбора и Enter для подтверждения выбора):\n\n");
				//возврат в меню
				printf("%s0. Возврат в меню\n", (selected == 0 ? "~~> " : "  "));
				//Файлы
				for (int i = 0; i < length; i++) {
					string filename = fs::path(name_list[i]).filename().string();
					printf("%s%d. %s\n", (selected == i + 1 ? "~~>" : "  "), i + 1, filename.c_str());
				}
			}
			else if (key == 13) {
				if (selected == 0) {
					ex = true;
					break;
				}
				else {
					int file_ind = selected - 1;
					string filename = fs::path(name_list[file_ind]).filename().string();
					ClearScreen();
					printf("Открыт файл: %s\n", filename.c_str());
					printf("Режим добавления данных...");
					FILE* fout;
					errno_t err = fopen_s(&fout, name_list[file_ind].c_str(), "a+");
					if (err == 0 && fout != NULL) {
						if (folder_name == ".\\Students\\") {
							write_stud(fout);
						}
						else if (folder_name == ".\\Passwords\\") {
							write_pas(fout);
						}
						fclose(fout);
					}
					else {
						printf("Ошибка: не удалось открыть файл для записи.\n");
					}
					ex = true;
					break;
				}
			}
			else if (key == 27) {
				ex = true;
				break;
			}
		}
	}
	delete[] name_list;
}
void ClearScreen() {
	system("cls");
}
void ShowMenu(int selected) {
	ClearScreen();
	printf("\t\t==== Главное меню ====\nПожалуйста, выберете какую информацию Вы хотите записывать.\nДля выбора используйте клавиши вверх-вниз, для подтверждения выбора используйте клавишу Enter. Для выхода из программы нажмите Esc\n\n"); // истина стрелка ложь пробел
	printf("%s1. Запись информации о студентах\n", (selected == 0 ? "~~> " : "  "));
	printf("%s2. Запись информации о паролях\n", (selected == 1 ? "~~> " : "  "));
	printf("%s3. Выход\n", (selected == 2 ? "~~> " : "  "));
}
void ShowActive(int selected) {
	ClearScreen();
	printf("\t\t==== Меню выбора действий ====\nПожалуйста, выберете режим записи.\nДля выбора используйте клавиши вверх-вниз, для подтверждения выбора используйте клавишу Enter. Для возвращения в главное меню нажмите Esc.\n\n");
	printf("%s1. Запись информации в новый файл\n", (selected == 0 ? "~~> " : "  "));
	printf("%s2. Запись информации в существующий файл\n", (selected == 1 ? "~~> " : "  "));
	printf("%s3. Выход в главное меню\n", (selected == 2 ? "~~> " : "  "));
}
int main() {
	// делаем возможным ввод/вывод кириллицей
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//приветствие
	printf("\t\t\t\tЗдравствуйте!\n");
	printf("Данная программа поможет Вам внести информацию о студентах и их паролях для работы на ЭВМ.\nПри дальнейшей работе, пожалуйста, следуйте инструкциям, появляющимся на экране, спасибо!\n\n");
	system("pause");
	//работа с директорией: проверка + создание папок
	vector<string> requiredFolders = { "Students", "Passwords" };
	for (const auto& folder : requiredFolders) {
		if (!fs::exists(folder)) {
			if (!(fs::create_directory(folder))) {
				printf("Ошибка при создании папки '%s'\nПожалуйста, создайте ее вручную в вашем репозитории.", folder.c_str());
				system("pause");
			}
		}
	}
	int selected = 0;
	ShowMenu(selected);
	//главное меню
	bool mode_ex = false; //переменная, отвечающая за выход из цикла
	while (!mode_ex) {
		if (_kbhit()) {
			int key = _getch();
			if (key == 224) { // клавиши вверх/вниз
				key = _getch();
				switch (key) {
				case 72: //вверх
					selected = (selected - 1 + 3) % 3;
					ShowMenu(selected);
					break;
				case 80: //вниз
					selected = (selected + 1) % 3;
					ShowMenu(selected);
					break;
				}
			}
			else if (key == 13) { //клавиша enter
				switch (selected) {
				case 0: {
					printf("\nВы выбрали запись информации о студентах\n\n");
					int mode_w = 0;
					ShowActive(mode_w);
					bool submenu_exit = false;
					while (!submenu_exit) {
						if (_kbhit()) {
							int key_w = _getch();
							if (key_w == 224) { // клавиши вверх/вниз
								key_w = _getch();
								switch (key_w) {
								case 72: //вверх
									mode_w = (mode_w - 1 + 3) % 3;
									ShowActive(mode_w);
									break;
								case 80: //вниз
									mode_w = (mode_w + 1) % 3;
									ShowActive(mode_w);
									break;
								}
							}
							else if (key_w == 13) { // enter
								switch (mode_w) {
								case 0:
									printf("Вы выбрали режим записи в новый файл\n");
									write_to_file(".\\Students\\");
									system("pause");
									submenu_exit = true;
									break;
								case 1:
									printf("Вы выбрали режим записи в существующий файл\n");
									add_to_file(".\\Students\\");
									system("pause");
									submenu_exit = true;
									break;
								case 2:
									submenu_exit = true;
									break;
								}
							}
							else if (key_w == 27) { // ESC
								submenu_exit = true;
							}
						}
					}
					ShowMenu(selected);
					break;
				}
				case 1: {
					printf("\nВы выбрали запись информации о паролях\n\n");
					int mode_w = 0;
					ShowActive(mode_w);
					bool submenu_exit = false;
					while (!submenu_exit) {
						if (_kbhit()) {
							int key_w = _getch();
							if (key_w == 224) { // клавиши вверх/вниз
								key_w = _getch();
								switch (key_w) {
								case 72: //вверх
									mode_w = (mode_w - 1 + 3) % 3;
									ShowActive(mode_w);
									break;
								case 80: //вниз
									mode_w = (mode_w + 1) % 3;
									ShowActive(mode_w);
									break;
								}
							}
							else if (key_w == 13) { // enter
								switch (mode_w) {
								case 0:
									printf("Вы выбрали режим записи в новый файл\n");
									write_to_file(".\\Passwords\\");
									system("pause");
									submenu_exit = true;
									break;
								case 1:
									printf("Вы выбрали режим записи в существующий файл\n");
									add_to_file(".\\Passwords\\");
									system("pause");
									submenu_exit = true;
									break;
								case 2:
									submenu_exit = true;
									break;
								}
							}
							else if (key_w == 27) { // ESC
								submenu_exit = true;
							}
						}
					}
					ShowMenu(selected);
					break;
				}
				case 2:
					mode_ex = true;
					break;
				}
			}
			else if (key == 27) { //ESC
				mode_ex = true;
			}
		}
	}
	printf("\nВыход из программы... ");
	return 0;
}