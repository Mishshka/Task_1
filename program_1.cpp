#include "program_1.h"

int main() {
	// ������ ��������� ����/����� ����������
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//�����������
	cout << "\t\t\t\t�����������!\n\t������ ��������� ������� ��� ������ ���������� � ��������� � �� ������� ��� ������ �� ���.\n\t��� ������ ��������� ���������� ������� ����� \"Students\" � \"Passwords\" � ������� ����������.\n\t��� �� ���������� ��� ����� ������������� �������." << endl;

	//������ � �����������: �������� + �������� �����
    vector<string> requiredFolders = { "Students", "Passwords" };
    cout << "\n\t\t\t\t�������� ����������" << endl;
    for (const auto& folder : requiredFolders) {
        if (!fs::exists(folder)) {
            if (fs::create_directory(folder)) {
                cout << "\t����� '" << folder << "' ������� �������." << endl;
            }
            else {
                cout << "\t������ ��� �������� ����� '" << folder << "'" << endl;
            }
        }
        else {
            cout << "\t����� '" << folder << "' ��� ����������." << endl;
        }
    }

	return 0;

}


