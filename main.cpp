#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
bool checkhex(char j) {
    j = toupper(j);
    return !(j > 'F' or j < '0' or (j >= ':' and j < '@'));
}// проверка элемента на принадлежность 16ричной системе
bool mknfcheck(int j) {
    return j == '0' + '9' or j == '0' * 2 or j == '0' * 4 or j == '0' * 2 + '9' * 2 or j == '0' + 3 * '9' or j == '0' * 8 or j == '0' * 4 + '9' * 4;
}//проверяет  интервал подходит он или нет к mknf
string noname(string j[], int o) {
    string rez = "";
    string s;
    for (int i = 0; i < 4; i++) {
        s = "";

        for (int h = 0; h < o; h++) {
            s += j[h][i];


        }

        if (s == string(o, j[0][i])) {
            rez += j[0][i];
        }
        else {
            rez += " ";
        }
    }
    return rez;
}//проверяет какие переменные сохраняются на интервале
string log(string j) {
    string u = "";
    string s = "abcd";
    for (int i = 0; i < j.size(); i++) {

        if (j[i] == '1') {
            u = u + "!" + s[i] + "+";
        }
        else if (j[i] == '0') {
            u = u + s[i] + "+";
        }

    }
    u.erase(u.size() - 1, 1);
    return "(" + u + ")";
}//возвращает строку с буквами в зависимости от 0 и 1
bool stringtobool(char a) {
    return a == '1';
}// переводит 1 и 0 стринг в bool формат
string hextobin(string c) {
    map  <char, string> hex{ {'0',"0000"},{'1',"0001"},{'2',"0010"},{'3',"0011"},
                             {'4',"0100"},{'5',"0101"},{'6',"0110"},{'7',"0111"},
                             {'8',"1000"},{'9',"1001"},{'A',"1010"},{'B',"1011"},
                             {'C',"1100"},{'D' ,"1101"},{'E',"1110"},{'F',"1111"} };
    string j = "";
    for (auto g : c) {
        j += hex[toupper(g)];
    }
    return j;
}// переводит 16ричной вектор функции в двоичную форму
bool mdnfcheck(int j) {
    return j == '1' + '9' or j == '1' * 2 or j == '1' * 4 or j == '1' * 2 + '9' * 2 or j == '1' + '9' * 3 or j == '1' * 8 or j == '1' * 4 + '9' * 4;;
}// проверяет интервал, подходит ли он или нет k mdnf
string log0(string j) {
    string u = "";
    string s = "abcd";
    for (int i = 0; i < j.size(); i++) {

        if (j[i] == '0') {
            u = u + "!" + s[i];
        }
        else if (j[i] == '1') {
            u = u + s[i];
        }

    }
    return u;
}//возвращает строку с буквами в зависимости от 0 и 1

void mknf(string F) {


    //вспомогательная штука для заполнения массива
    string hexmas[16] = { {"0000"},{"0001"},{"0010"},{"0011"},
                          {"0100"},{"0101"},{"0110"},{"0111"},
                          {"1000"},{"1001"},{"1010"},{"1011"},
                          {"1100"},{"1101"},{"1110"},{"1111"} };
    vector<string> tableforsknf;//вектор для строчек, где функция false
    F = hextobin(F);// двоичный вектор функции
    map<string, string> table;// словарь (строка переменных, F(строки переменных))
    //заполнение вектора для sknf
    for (int i = 0; i < 16; i++) {
        table[hexmas[i]] = F[i];
        if (!stringtobool(F[i])) {
            tableforsknf.push_back(hexmas[i]);
        }
    }

    //вывод таблицы истинности
    cout << "____________" << endl;
    cout << "|a b c d |F| N" << endl;
    cout << "____________";
    for (int i = 0; i < 16; i++) {
        cout << "\n|";
        for (int j = 0; j < 4; j++) {
            cout << hexmas[i][j] << " ";
        }
        cout << "|";
        cout << table[hexmas[i]];
        cout << "|";
        cout << " " << i;
        cout << "\n____________";
    }
    //заполняем sknf
    string sknf = "";
    string temporary;
    int k = tableforsknf.size();
    for (int i = 0; i < k; i++) {
        temporary = log(tableforsknf[i]);
        sknf += temporary;
    }
    //выводим sknf
    cout << "\n\nF(sknf) = " << sknf << endl;


    string tableformknf[4];//  карта карно
    string mknf;//строка для заполнения mknf
    string binmknf[16] = { {"0000"},{"0001"},{"0011"},{"0010"},// шаблон карты карно
                           {"0100"},{"0101"},{"0111"},{"0110"},
                           {"1100"},{"1101"},{"1111"},{"1110"},
                           {"1000"},{"1001"},{"1011"},{"1010"} };

    //ПРОСТО ПЕЧАТЬ
    cout << "\n\nKarnaugh map" << endl;
    cout << "\n" << string(25, '_') << endl;
    cout << "ab\\cd| ";
    for (int i = 0; i < 4; i++) {
        cout << binmknf[i].substr(2, 2) << " | ";
    }
    cout << "\n" << string(25, '_');
    cout << endl;
    for (int j = 0; j < 4; j++) {
        cout << " " << binmknf[j * 4].substr(0, 2) << "  |";
        for (int i = 0; i < 4; i++) {
            cout << " " << table[binmknf[j * 4 + i]] << "  |";
        }
        cout << endl;

    }
    cout << string(25, '_');

    //заполнение карты карно
    int s;
    for (int i = 0; i < 4; i++) {
        temporary = "";
        k = i * 4;
        for (int j = k; j < k + 4; j++) {
            temporary += table[binmknf[j]];
        }
        tableformknf[i] = temporary;

    }
    int p = 0;
    for (auto j : F) {
        p += j;

    }
    if (p == '0' * 16) {
        for (int i = 0; i < 4; i++) {
            tableformknf[i] = "9999";
        }
        mknf += "0";
    }
    //проверка интервалов по 8
    string checkeight[8];
    for (int i = 0; i < 3; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformknf[i][j];
            s += tableformknf[i + 1][j];
        }
        if (mknfcheck(s)) {
            for (int c = 0; c < 8; c++) {
                checkeight[c] = binmknf[4 * i + c];
            }
            for (int j = 0; j < 4; j++) {
                tableformknf[i][j] = '9';
                tableformknf[i + 1][j] = '9';
            }
            mknf =  log(noname(checkeight, 8)) + mknf;

        }

    }

    for (int j = 0; j < 3; j++) {
        s = 0;
        for (int i = 0; i < 4; i++) {
            s += tableformknf[i][j];
            s += tableformknf[i][j + 1];
        }
        if (mknfcheck(s)) {
            for (int c = 0; c < 4; c++) {
                checkeight[c] = binmknf[4 * c + j];
            }
            for (int c = 4; c < 8; c++) {
                checkeight[c] = binmknf[4 * (c - 4) + j + 1];
            }
            for (int i = 0; i < 4; i++) {
                tableformknf[i][j] = '9';
                tableformknf[i][j + 1] = '9';
            }
            mknf =  log(noname(checkeight, 8)) + mknf;

        }

    }
    //проверка горизонтальных строчек
    for (int i = 0; i < 4; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformknf[i][j];
        }
        if (mknfcheck(s)) {
            tableformknf[i] = "9999";
            mknf = log(binmknf[i * 4].substr(0, 2)) + mknf;
        }

    }
    //проверка вертикальных строчек
    string u = "";
    for (int i = 0; i < 4; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformknf[j][i];

        }
        if (mknfcheck(s)) {
            u = "  " + binmknf[i].substr(2, 2);
            mknf = log(u) + mknf;
            for (int j = 0; j < 4; j++) {
                tableformknf[j][i] = '9';

            }

        }
    }

    //квадратики по 4 нуля
    string strok[4];
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            s = 0;
            s += tableformknf[i][j];
            s += tableformknf[i][j + 1];
            s += tableformknf[i + 1][j];
            s += tableformknf[i + 1][j + 1];
            if (s == '0' * 4) {
                strok[0] = binmknf[4 * i + j];
                strok[1] = binmknf[4 * i + j + 1];
                strok[2] = binmknf[4 * (i + 1) + j];
                strok[3] = binmknf[4 * (i + 1) + j + 1];
                tableformknf[i][j] = '9';
                tableformknf[i][j + 1] = '9';
                tableformknf[i + 1][j] = '9';
                tableformknf[i + 1][j + 1] = '9';
                mknf = log(noname(strok, 4)) + mknf;
            }


        }

    }


    // квадратики
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            s = 0;
            s += tableformknf[i][j];
            s += tableformknf[i][j + 1];
            s += tableformknf[i + 1][j];
            s += tableformknf[i + 1][j + 1];
            if (mknfcheck(s)) {
                strok[0] = binmknf[4 * i + j];
                strok[1] = binmknf[4 * i + j + 1];
                strok[2] = binmknf[4 * (i + 1) + j];
                strok[3] = binmknf[4 * (i + 1) + j + 1];
                tableformknf[i][j] = '9';
                tableformknf[i][j + 1] = '9';
                tableformknf[i + 1][j] = '9';
                tableformknf[i + 1][j + 1] = '9';
                mknf = log(noname(strok, 4)) + mknf;
            }


        }

    }
    //переходные интервалы 2x2
    for (int i = 0; i < 3; i++) {
        s = 0;
        s += tableformknf[i][0];
        s += tableformknf[i][3];
        s += tableformknf[i + 1][0];
        s += tableformknf[i + 1][3];
        if (mknfcheck(s)) {
            strok[0] = binmknf[4 * i + 0];
            strok[1] = binmknf[4 * i + 3 ];
            strok[2] = binmknf[4 * (i + 1) + 0];
            strok[3] = binmknf[4 * (i + 1) + 3];
            tableformknf[i][0] = '9';
            tableformknf[i][3] = '9';
            tableformknf[i + 1][0] = '9';
            tableformknf[i + 1][3] = '9';
            mknf = log(noname(strok, 4)) + mknf;
        }


    }

    for (int i = 0; i < 3; i++) {
        s = 0;
        s += tableformknf[0][i];
        s += tableformknf[3][i];
        s += tableformknf[0][i + 1];
        s += tableformknf[3][i + 1];
        if (mknfcheck(s)) {
            strok[0] = binmknf[0 + i];
            strok[1] = binmknf[0 + i + 1];
            strok[2] = binmknf[4 * (3) + i];
            strok[3] = binmknf[4 * (3) + i + 1];
            tableformknf[0][i] = '9';
            tableformknf[3][i] = '9';
            tableformknf[0][i + 1] = '9';
            tableformknf[3][i + 1] = '9';
            mknf = log(noname(strok, 4)) + mknf;
        }


    }


    // если остались интервалы по два нуля, то заменяем их
    string  strings[2];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (tableformknf[i][j] + tableformknf[i + 1][j] == '0' * 2) {
                strings[0] = binmknf[4 * i + j];
                strings[1] = binmknf[4 * (i + 1) + j];
                mknf = log(noname(strings, 2)) + mknf;
                tableformknf[i][j] = '9';
                tableformknf[i + 1][j] = '9';


            }

        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (tableformknf[i][j] + tableformknf[i][j + 1] == '0' * 2) {
                strings[0] = binmknf[4 * i + j];
                strings[1] = binmknf[4 * i + j + 1];
                mknf = log(noname(strings, 2)) + mknf;
                tableformknf[i][j] = '9';
                tableformknf[i][j + 1] = '9';


            }
        }
    }


    //интервал по два нуля
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            s = 0;
            s += tableformknf[i][j];
            s += tableformknf[i][j + 1];
            if (mknfcheck(s)) {
                strings[0] = binmknf[4 * i + j];
                strings[1] = binmknf[4 * i + j + 1];
                mknf = log(noname(strings, 2)) + mknf;
                tableformknf[i][j] = '9';
                tableformknf[i][j + 1] = '9';
            }
        }
    }
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            s = 0;
            s += tableformknf[i][j];
            s += tableformknf[i + 1][j];
            if (mknfcheck(s)) {
                strings[0] = binmknf[4 * i + j];
                strings[1] = binmknf[4 * (i + 1) + j];
                mknf = log(noname(strings, 2)) + mknf;
                tableformknf[i][j] = '9';
                tableformknf[i + 1][j] = '9';
            }
        }
    }


    // проверка переходных крайних интервала по два нуля по горизонтали
    for (int i = 0; i < 4; i++) {
        s = 0;
        s += tableformknf[i][0];
        s += tableformknf[i][3];
        if (mknfcheck(s)) {
            strings[0] = binmknf[4 * i + 0];
            strings[1] = binmknf[4 * i + 3];
            mknf = log(noname(strings, 2)) + mknf;
            tableformknf[i][0] = '9';
            tableformknf[i][3] = '9';

        }
    }

    // проверка переходных крайних интервала по два нуля по вертикали
    for (int i = 0; i < 4; i++) {
        s = 0;
        s += tableformknf[0][i];
        s += (tableformknf[3][i]);
        if (mknfcheck(s)) {
            strings[0] = binmknf[i];
            strings[1] = binmknf[4 * 3 + i];
            mknf = log(noname(strings, 2)) + mknf;
            tableformknf[0][i] = '9';
            tableformknf[3][i] = '9';

        }
    }
    // проверка вырожденных интервалов
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tableformknf[i][j] == '0') {
                mknf = log(binmknf[4 * i + j]) + mknf;
            }

        }
    }
    // вывод mknf
    cout << "\n\nF(mknf) = " << mknf << endl;

}//sknf/mknf
void mdnf(string F) {

    //вспомогательная штука для заполнения массива
    string hexmas[16] = { {"0000"},{"0001"},{"0010"},{"0011"},
                          {"0100"},{"0101"},{"0110"},{"0111"},
                          {"1000"},{"1001"},{"1010"},{"1011"},
                          {"1100"},{"1101"},{"1110"},{"1111"} };
    vector<string> tableforsdnf;//вектор для строчек, где функция true, которые нужны для mdnf
    F = hextobin(F);//вектор функции в двоичном представлении
    map<string, string> table;// словарь (строчка переменных, F(строчки переменных)
    //заполнение словаря
    for (int i = 0; i < 16; i++) {
        table[hexmas[i]] = F[i];
        if (stringtobool(F[i])) {
            tableforsdnf.push_back(hexmas[i]);
        }
    }
    //вывод таблицы
    cout << "____________" << endl;
    cout << "|a b c d |F| N" << endl;
    cout << "____________";
    for (int i = 0; i < 16; i++) {
        cout << "\n|";
        for (int j = 0; j < 4; j++) {
            cout << hexmas[i][j] << " ";
        }
        cout << "|";
        cout << table[hexmas[i]];
        cout << "|";
        cout << " " << i;
        cout << "\n____________";
    }
    // делаем формулу сднф
    string sdnf = "";
    string temporary;
    int k = tableforsdnf.size();
    for (int i = 0; i < k; i++) {
        temporary = log0(tableforsdnf[i]);
        if (i != k - 1) {

            sdnf += temporary + " +";
        }
        else {
            sdnf += temporary;

        }
    }
    //выводим
    cout << "\n\nF(sdnf) = " << sdnf << endl;
    string tableformdnf[4];//карта Карно
    string mdnf;
    string binmdnf[16] = { {"0000"},{"0001"},{"0011"},{"0010"},//шаблон для карты Карно
                           {"0100"},{"0101"},{"0111"},{"0110"},
                           {"1100"},{"1101"},{"1111"},{"1110"},
                           {"1000"},{"1001"},{"1011"},{"1010"} };


    //ПРОСТО ПЕЧАТЬ
    cout << "\n\nKarnaugh map" << endl;
    cout << "\n" << string(25, '_') << endl;
    cout << "ab\\cd| ";
    for (int i = 0; i < 4; i++) {
        cout << binmdnf[i].substr(2, 2) << " | ";
    }
    cout << "\n" << string(25, '_');
    cout << endl;
    for (int j = 0; j < 4; j++) {
        cout << " " << binmdnf[j * 4].substr(0, 2) << "  |";
        for (int i = 0; i < 4; i++) {
            cout << " " << table[binmdnf[j * 4 + i]] << "  |";
        }
        cout << endl;

    }
    cout << string(25, '_');


    // заполнение таблицы строками
    int s;
    for (int i = 0; i < 4; i++) {
        temporary = "";
        k = i * 4;
        for (int j = k; j < k + 4; j++) {
            temporary += table[binmdnf[j]];
        }
        tableformdnf[i] = temporary;

    }
    //проверка на интервал по 16
    int p = 0;
    for (auto j : F) {
        p += j;


    }
    if (p == '1' * 16) {
        for (int i = 0; i < 4; i++) {
            tableformdnf[i] = "9999";
        }
        mdnf = "1";
    }


    //проверка интервалов по 8
    string checkeight[8];
    for (int i = 0; i < 3; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformdnf[i][j];
            s += tableformdnf[i + 1][j];
        }
        if (mdnfcheck(s)) {
            for (int c = 0; c < 8; c++) {
                checkeight[c] = binmdnf[4 * i + c];
            }
            for (int j = 0; j < 4; j++) {
                tableformdnf[i][j] = '9';
                tableformdnf[i + 1][j] = '9';
            }
            mdnf = "+" + log0(noname(checkeight, 8)) + mdnf;

        }

    }

    for (int j = 0; j < 3; j++) {
        s = 0;
        for (int i = 0; i < 4; i++) {
            s += tableformdnf[i][j];
            s += tableformdnf[i][j + 1];
        }
        if (mdnfcheck(s)) {
            for (int c = 0; c < 4; c++) {
                checkeight[c] = binmdnf[4 * c + j];
            }
            for (int c = 4; c < 8; c++) {
                checkeight[c] = binmdnf[4 * (c - 4) + j + 1];
            }
            for (int i = 0; i < 4; i++) {
                tableformdnf[i][j] = '9';
                tableformdnf[i][j + 1] = '9';
            }
            mdnf = "+" + log0(noname(checkeight, 8)) + mdnf;

        }

    }

    //проверка горизонтальных строчек
    for (int i = 0; i < 4; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformdnf[i][j];
        }
        if (mdnfcheck(s)) {
            tableformdnf[i] = "9999";
            mdnf = "+" + log0(binmdnf[i * 4].substr(0, 2)) + mdnf;
        }

    }

    //проверка вертикальных строчек
    string u = "";
    for (int i = 0; i < 4; i++) {
        s = 0;
        for (int j = 0; j < 4; j++) {
            s += tableformdnf[j][i];

        }
        if (mdnfcheck(s)) {
            u = "  " + binmdnf[i].substr(2, 2);
            mdnf = "+" + log0(u) + mdnf;
            for (int j = 0; j < 4; j++) {
                tableformdnf[j][i] = '9';

            }

        }
    }
    // проверка квадратиков по 4 единицы
    string strok[4];
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            s = 0;
            s += tableformdnf[i][j];
            s += tableformdnf[i][j + 1];
            s += tableformdnf[i + 1][j];
            s += tableformdnf[i + 1][j + 1];
            if (s == '1' * 4) {
                strok[0] = binmdnf[4 * i + j];
                strok[1] = binmdnf[4 * i + j + 1];
                strok[2] = binmdnf[4 * (i + 1) + j];
                strok[3] = binmdnf[4 * (i + 1) + j + 1];
                tableformdnf[i][j] = '9';
                tableformdnf[i][j + 1] = '9';
                tableformdnf[i + 1][j] = '9';
                tableformdnf[i + 1][j + 1] = '9';
                mdnf = "+" + log0(noname(strok, 4)) + mdnf;
            }


        }

    }


    //проверка квадратиков
    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {
            s = 0;
            s += tableformdnf[i][j];
            s += tableformdnf[i][j + 1];
            s += tableformdnf[i + 1][j];
            s += tableformdnf[i + 1][j + 1];
            if (mdnfcheck(s)) {
                strok[0] = binmdnf[4 * i + j];
                strok[1] = binmdnf[4 * i + j + 1];
                strok[2] = binmdnf[4 * (i + 1) + j];
                strok[3] = binmdnf[4 * (i + 1) + j + 1];
                tableformdnf[i][j] = '9';
                tableformdnf[i][j + 1] = '9';
                tableformdnf[i + 1][j] = '9';
                tableformdnf[i + 1][j + 1] = '9';
                mdnf = "+" + log0(noname(strok, 4)) + mdnf;
            }


        }

    }
    for (int i = 0; i < 3; i++) {
        s = 0;
        s += tableformdnf[i][0];
        s += tableformdnf[i][3];
        s += tableformdnf[i + 1][0];
        s += tableformdnf[i + 1][3];
        if (mdnfcheck(s)) {
            strok[0] = binmdnf[4 * i + 0];
            strok[1] = binmdnf[4 * i + 3];
            strok[2] = binmdnf[4 * (i + 1) + 0];
            strok[3] = binmdnf[4 * (i + 1) + 3];
            tableformdnf[i][0] = '9';
            tableformdnf[i][3] = '9';
            tableformdnf[i + 1][0] = '9';
            tableformdnf[i + 1][3] = '9';
            mdnf = "+" + log0(noname(strok, 4)) + mdnf;
        }


    }

    for (int i = 0; i < 3; i++) {
        s = 0;
        s += tableformdnf[0][i];
        s += tableformdnf[3][i];
        s += tableformdnf[0][i + 1];
        s += tableformdnf[3][i + 1];
        if (mdnfcheck(s)) {
            strok[0] = binmdnf[0 + i];
            strok[1] = binmdnf[0 + i + 1];
            strok[2] = binmdnf[4 * (3) + i];
            strok[3] = binmdnf[4 * (3) + i + 1];
            tableformdnf[0][i] = '9';
            tableformdnf[3][i] = '9';
            tableformdnf[0][i + 1] = '9';
            tableformdnf[3][i + 1] = '9';
            mdnf = "+" + log0(noname(strok, 4)) + mdnf;
        }


        // если в таблице остались интервалы по  две единицы,то проверяем по двоечки с единицами

        string  strings[2];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (tableformdnf[i][j] + tableformdnf[i][j + 1] == '1' * 2) {
                    strings[0] = binmdnf[4 * i + j];
                    strings[1] = binmdnf[4 * i + j + 1];
                    mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                    tableformdnf[i][j] = '9';
                    tableformdnf[i][j + 1] = '9';
                }


            }
        }
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 3; i++) {
                if (tableformdnf[i][j] + tableformdnf[i + 1][j] == '1' * 2) {
                    strings[0] = binmdnf[4 * i + j];
                    strings[1] = binmdnf[4 * (i + 1) + j];
                    mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                    tableformdnf[i][j] = '9';
                    tableformdnf[i + 1][j] = '9';
                }
            }
        }




        //проверяем двоечки
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                s = 0;
                s += tableformdnf[i][j];
                s += tableformdnf[i][j + 1];
                if (mdnfcheck(s)) {
                    strings[0] = binmdnf[4 * i + j];
                    strings[1] = binmdnf[4 * i + j + 1];
                    mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                    tableformdnf[i][j] = '9';
                    tableformdnf[i][j + 1] = '9';
                }
            }
        }
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 3; i++) {
                s = 0;
                s += tableformdnf[i][j];
                s += tableformdnf[i + 1][j];
                if (mdnfcheck(s)) {
                    strings[0] = binmdnf[4 * i + j];
                    strings[1] = binmdnf[4 * (i + 1) + j];
                    mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                    tableformdnf[i][j] = '9';
                    tableformdnf[i + 1][j] = '9';
                }

            }
        }
        //проверка переходных крайних двоек по горизонтали
        for (int i = 0; i < 4; i++) {
            s = 0;
            s += tableformdnf[i][0];
            s += tableformdnf[i][3];
            if (mdnfcheck(s)) {
                strings[0] = binmdnf[4 * i + 0];
                strings[1] = binmdnf[4 * i + 3];
                mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                tableformdnf[i][0] = '9';
                tableformdnf[i][3] = '9';

            }
        }
        //проверка переходных крайних двоек по вертикали
        for (int i = 0; i < 4; i++) {
            s = 0;
            s += tableformdnf[0][i];
            s += (tableformdnf[3][i]);
            if (mdnfcheck(s)) {
                strings[0] = binmdnf[i];
                strings[1] = binmdnf[4 * 3 + i];
                mdnf = "+" + log0(noname(strings, 2)) + mdnf;
                tableformdnf[0][i] = '9';
                tableformdnf[3][i] = '9';

            }
        }
        //проверка вырожденных интервалов
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tableformdnf[i][j] == '1') {
                    mdnf = "+" + log0(binmdnf[4 * i + j]) + mdnf;
                }

            }
        }
        //убираем лишний плюсик
        if (mdnf.size() > 1) {
            mdnf.erase(0, 1);

        }


        //результат
        cout << "\n\nF(mdnf) = " << mdnf << endl;

    }
}//sdnf/mdnf
int main() {
    int n=1;
    while (n != 0) {
        cout << "Choose options";
        cout << "\n1 - start/continue";
        cout << "\n0 - Exit\n";
        cout << "Input number = ";
        while (!(cin >> n) or (n != 0 and n != 1)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nIncorrect input";
            cout << "\nTry again: ";

        }
        if (n == 0) {
            exit(0);
        }
        string F = "";
        cout << "\nF(hex)=";
        while (!(cin >> F) or F.size() != 4 or !(checkhex(F[0]) * checkhex(F[1]) * checkhex(F[2]) * checkhex(F[3]))) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Incorrect input\n" << "Try again : ";

        }
        cout << "Choose options";
        cout << "\n1 - sdnf/mdnf";
        cout << "\n2 - sknf/mknf";
        cout << "\nInput number = ";
        while (!(cin >> n) or (n != 1 and n != 2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nIncorrect input";
            cout << "\nTry again: ";

        }
        switch (n) {
            case 1:
                mdnf(F);
                break;
            case 2:
                mknf(F);
                break;
        }
    }

}