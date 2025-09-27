#include "program_1.h"

string choose_folder() {
    bool exit=false;
    string folder_name = "";
    printf("Пожалуйста, выберете какую информацию Вы хотите записать:\n 1 - запись в файл сведений о студентах\n 2 - запись в файл паролей\n ESC - вернуться в главное меню\n");
    do {
        int mode = getchar();
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        switch (mode)
        {
        case '1':
            folder_name = ".\\Students\\";
            exit = true;
            break;
        case '2':
            folder_name = ".\\Passwords\\";
            exit = true;
            break;
        case 27:
            folder_name = "";
            exit = true;
            break;
        default:
            printf("Неверный выбор. Попробуйте снова\n");
            exit = true;
            break;
        }

    } while (!exit);
    return folder_name;
}

int count_files(string folder_name) {
    int i = 0;
    for (auto& p : fs::directory_iterator(folder_name)) {
        i++;
    }
    return i;
}

string* get_filenames(string folder_name) {
    int len = count_files(folder_name);
    string* list_names = new string[len];
    int i = 0;
    for (auto& p : fs::directory_iterator(folder_name)) {
        list_names[i] = fs::path(p).string();
        i++;
    }
    return list_names;
}

void write_stud(ofstream* fout) {

}

void write_pas(ofstream* fout) {

}

void write_to_file(string folder_name) {
    char bf[256];
    string file_name;
    ofstream fout;
    bool exit = true;

    printf("Пожалуйста, введите название файла. Для этого используйте латинские буквы и цифры.\n");
    printf("Ваш файл будет сохранен в формате txt, расширение писать не нужно.\nДля возврата введите пустую строку.\n");
    
    //получаем строку из консоли
    fgets(bf, sizeof(bf), stdin);

    //если пусто, то удаляем
    bf[strcspn(bf, "\n")] = 0;
     
    file_name = bf;
    //начинаем цикл по работе с названием
    while (exit && file_name.length() > 0) {
        if (file_name.find_first_not_of(ENG_let + num) == string::npos) {
            exit = false;
        }
        else {
            printf("Ошибка создания файла. Пожалуйста, повторите ввод, используя только латинский алфавит и цифры.\n");
            fgets(bf, sizeof(bf), stdin);
            bf[strcspn(bf, "\n")] = 0;
            file_name = bf;
            continue;
        }

        if (file_name.find(".") == string::npos) {
            file_name += ".txt";
        }

        printf("\nназвание файла %s\n", file_name.c_str());
        int len = count_files(folder_name);
        string* list_names = get_filenames(folder_name);
        for (int i = 0; i < len; i++) {
            if ((folder_name + file_name) == list_names[i]) {
                printf("Файл с таким названием уже существует.\nНужно ввести другое название. Вернитесь назад, для этого введите пустую строку\n");
                fgets(bf, sizeof(bf), stdin);
                bf[strcspn(bf, "\n")] = 0;
                file_name = bf;
                exit = true;
                break;
            }   
            else {
                exit = false;
            }
        }
    }

    if (file_name.length() != 0) {
        string path = folder_name + file_name;
        fout.open(path);
        if (fout) {
            if (folder_name == ".\\Students\\")
                write_stud(&fout);
            if (folder_name == ".\\Passwords\\")
                write_pas(&fout);
            fout.close();
        }
        else {
            printf("Не удалось открыть файл. Пожалуйста, повторите попытку. Папка: %s\n", folder_name.c_str());
        }
    }
}

int main() {
	// делаем возможным ввод/вывод кириллицей
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    //приветствие
    printf("\t\t\t\tЗдравствуйте!\n");
    printf("Данная программа поможет Вам внести информацию о студентах и их паролях для работы на ЭВМ.\n");
    printf("Для работы программы необходимо наличие папок \"Students\" и \"Passwords\" в текущей директории.\n");
    printf("При их отсутствии они будут автоматически созданы.\n");

	//работа с директорией: проверка + создание папок
    vector<string> requiredFolders = { "Students", "Passwords" };
    printf("\n\t\t\t\tПроверка директории\n");

    for (const auto& folder : requiredFolders) {
        if (!fs::exists(folder)) {
            if (fs::create_directory(folder)) {
                printf("Папка '%s' создана успешно.\n", folder.c_str());
            }
            else {
                printf("Ошибка при создании папки '%s'\n", folder.c_str());
            }
        }
        else {
            printf("Папка '%s' уже существует.\n", folder.c_str());
        }
    }

    //главное меню
    printf("\nСейчас вы перешли в главное меню. Для дальнейшей работы выберете режим работы:\n 1 - запись в новый файл\n 2 - продолжить запись в существующий файл\n ESC - завершить работу\nДля выбора действия введите в консоль номер под которым расположено нужное действие.\nДля использования пункта ESC можно нажать соответсвующую кнопку на клавиатуре. \n\nВ ходе работы продолжайте следовать инструкциям, появляющимся в консоли, спасибо!\n\n\n");
    bool mode_ex = false; //переменная, отвечающая за выход из цикла
    char mode_n; // переменная для выбора режима
    do {
        string folder_name;
        mode_n = _getch();
        switch (mode_n) {
        case '1':
            printf("Вы выбрали запись в новый файл\n");
            folder_name = choose_folder();
            if(!folder_name.empty()) {
                write_to_file(folder_name);
            }
            printf("\nСейчас вы перешли в главное меню. Для дальнейшей работы выберете режим работы:\n 1 - запись в новый файл\n 2 - продолжить запись в существующий файл\n ESC - завершить работу\nДля выбора действия введите в консоль номер под которым расположено нужное действие.\nДля использования пункта ESC можно нажать соответсвующую кнопку на клавиатуре. \n\nВ ходе работы продолжайте следовать инструкциям, появляющимся в консоли, спасибо!\n\n\n");
            break;
        case '2':
            printf("Вы выбрали запись в существующий файл\n");
            
            break;
        case 27: 
            mode_ex = true;
            break;
        
        default:
            mode_ex = true;
            printf("Выбран неверный режим, пожалуйста, перезапустите программу.\n");
            this_thread::sleep_for(chrono::microseconds(10)); // дается время на ознакомление с сообщением о необходимости перезапуска
            break;
        }


    } while (!mode_ex);


	return 0;

}


