#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstddef> // for offsetof

using namespace std;

// �����ṹ����ÿ����Ա�����ơ�ƫ�ƺʹ�С
struct Field {
    string name;
    size_t offset;
    size_t size;
    char symbol; // ���ĸ��ַ�������ֶ�
};

// ���ӻ�����
void visualizeStructLayout(size_t structSize, const vector<Field>& fields) {
    vector<char> layout(structSize, 'P');  // Ĭ��ȫ���� padding��P��

    for (const auto& field : fields) {
        for (size_t i = 0; i < field.size; ++i) {
            if (field.offset + i < structSize)
                layout[field.offset + i] = field.symbol;
        }
    }

    // ��ӡͼ��
    cout << "Offset | ";
    for (size_t i = 0; i < structSize; ++i)
        cout << setw(2) << i << " ";
    cout << "\n--------+--------------------------\n";

    cout << "Field  | ";
    for (char ch : layout)
        cout << " " << ch << " ";
    cout << "\n\n";

    // ˵��
    for (const auto& field : fields)
        cout << field.symbol << " = " << field.name << " (" << field.size << " bytes at offset " << field.offset << ")\n";
    cout << "P = Padding\n";
}

struct MyStruct {
    char a;
    int b;
    short c;
};

int main() {
    vector<Field> fields = {
        {"a", offsetof(MyStruct, a), sizeof(char), 'A'},
        {"b", offsetof(MyStruct, b), sizeof(int),  'B'},
        {"c", offsetof(MyStruct, c), sizeof(short),'C'}
    };

    visualizeStructLayout(sizeof(MyStruct), fields);

	cin.get();
}
