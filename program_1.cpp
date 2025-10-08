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

void write_stud(ofstream* fout) {// функция для заполнения файла со студентами

}

void write_pas(ofstream* fout) { // функция для заполнения файла с паролями

}

void write_to_file(string folder_name) {
    char bf[256];
    string file_name;
    ofstream fout;

    ClearScreen();
    printf("Пожалуйста, введите название файла. Для этого используйте латинские буквы и цифры.\n");
    printf("Ваш файл будет сохранен в формате txt, расширение писать не нужно.\nДля возврата введите пустую строку.\n");

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
        if (file_name.find_first_not_of(ENG_let + num) != string::npos) {
            printf("Ошибка: используйте только латинские буквы и цифры. Попробуйте снова:\n");
            continue;
        }

        // Добавляем расширение если нужно
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
    fout.open(path);

    if (fout) {
        printf("Создан файл: %s\n", path.c_str());

        if (folder_name == ".\\Students\\")
            write_stud(&fout);
        else if (folder_name == ".\\Passwords\\")
            write_pas(&fout);

        fout.close();
        printf("Данные успешно записаны в файл.\n");
    }
    else {
        printf("Ошибка: не удалось создать файл '%s'\n", path.c_str());
    }
}

void add_to_file(string folder_name) {
    
    ClearScreen();
    
    printf("\nФайлы в папке '%s':\n", folder_name.c_str());

    printf("Загрузка списка файлов");
    for (int i = 0; i < 3; i++) {
        printf(".");
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    printf("\n\n");

    int length = count_files(folder_name);
    string* name_list = get_filenames(folder_name);

    if (length == 0) {
        printf("Файлы не обнаружены. Создание нового файла...\n");
        this_thread::sleep_for(chrono::seconds(1));
        write_to_file(folder_name);
        delete[] name_list;
        return;
    }
             
    int selected = 0;
    bool ex = true;
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
    while (ex) {
        
        
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
                    ofstream fout(name_list[file_ind], ios::app);
                    if (fout) {
                        if (folder_name == ".\\Students\\") {
                            write_stud(&fout);
                        }
                        else if (folder_name == ".\\Passwords\\") {
                            write_pas(&fout);
                        }

                        fout.close();
                        printf("\nДанные успешно добавлены в файл.\n");
                    }
                    else {
                        printf("Ошибка: не удалось открыть файл для записи.\n");
                    }

                    printf("\nНажмите любую клавишу для возврата в меню...");
                    _getch();
                    ex = true;
                    break;
                }
            }
            else if (key == 27) {
                ex = true;
                break;
            }
            if (selected != fl) {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                // Очищаем и перерисовываем строки выбора
                COORD pos = { 0, 5 };
                SetConsoleCursorPosition(hConsole, pos);

                // Возврат в меню
                printf("%s0. Возврат в меню", (selected == 0 ? "~~> " : "  "));
                // Очищаем остаток строки
                for (int i = 0; i < 19; i++) printf(" ");

                // Файлы
                for (int i = 0; i < length; i++) {
                    pos.Y = 6 + i;
                    SetConsoleCursorPosition(hConsole, pos);
                    string filename = fs::path(name_list[i]).filename().string();
                    printf("%s%d. %s", (selected == i + 1 ? "~~>" : "  "), i + 1, filename.c_str());
                    // Очищаем остаток строки
                    for (int j = 0; j < filename.length() + 5; j++) printf(" ");
                }

                // Очищаем возможные артефакты ниже меню
                pos.Y = 6 + length;
                SetConsoleCursorPosition(hConsole, pos);
                printf(" ");

                fl = selected;
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
    printf("\t\t==== Главное меню ====\nПожалуйста, выберете какую информацию Вы хотите записывать.\nДля выбора используйте клавиши вверх-вниз, для подтверждения выбора используйте клавишу Enter.\n\n");
    printf("%s1. Запись информации о студентах\n", (selected == 0 ? "~~> " : "  "));
    printf("%s2. Запись информации о паролях\n", (selected == 1 ? "~~> " : "  "));
    printf("%s3. Выход\n", (selected == 2 ? "~~> " : "  "));
}

void ShowActive(int selected) {
    ClearScreen();
    printf("\t\t==== Меню выбора действий ====\nПожалуйста, выберете режим записи.\nДля выбора используйте клавиши вверх-вниз, для подтверждения выбора используйте клавишу Enter.\n\n");
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


