#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;


// Кратко опишу концепцию проекта. У тебя был класс NOTE, содержащий нужные поля. Но больеш в этом классе ничего не было, и по сути хуй знает для чего
// он был нужен. Теперь сделаем как: есть класс NOTE, в нем будут закрытые поля с данными, завернутыми ещё в ячеку, чтобы реализовать список, и открытые методы, с помощью которых можно будет взаимодействоать
// с полями. То есть условно говоря, можно будет это вынести в отдельный файл, подключить к другому проекту и оно будет работать. У тебя раньше все взаимодейтсивтия 
// были в обычных функциях. Это не то что бы плохо, просто это подход больше для языка С чем С++. Но у тут функции тоже останутся. Я сделаю функции, которые
// будут записаны в меню, они просто будут вызываться, а уже внутри функций будут создаватсья все переменные, будет запрашиватсья ввод, 
// выполняться необходимые проверки и потом передаваться в метод класса. Как-то так. Это как говорится после прочтения сжечь

vector<pair<string, string>> ALL_PEOPLE;    // Эти векторы нужны для проверки уникальности. структура pair позволяет хранить пару переменных
vector<string> ALL_NUMBERS;                 // Можно будет просто внести туда имя и фамилияю и потом сравнить, а не все по отдельности
string file = "notes.txt";

#pragma region CHECK

bool name_is_right(string name) {
    if (name.size() > 15 || name.size() < 2) { // проверяем чтобы имя не было слишком длинным и слишком коротким (или пустой строкой)
        cout << "Судя по учётным записям, самое длинное мужское имя в России — " << endl << 
            "Абдурахмангаджи(15 букв), женское — Вильгельмина(12 букв)." << endl << 
            "Самые короткие имена — двухбуквенные Ян, Ия и Ая." << endl;
        return false; // если слово не подходит по ращмеру возвращаем фолз
    }
    else {
        string trash = "01234567890!\"№;%:?*()_+=@#$^&<>[]{}"; // я суда не включил "-" потмоу что вдруг двойные фамилии типа мамин-сибиряк, хз
        for (int i = 0; i < name.size(); i++) {
            for (int j = 0; j < trash.size(); j++) {
                if (name[i] == trash[j]) {
                    cout << "Имя или фамилия содержит мусор!!!";
                    return false; // если слово содержит мусор, возвращаем фолз
                }
            }
        }

        for (int i = 0; i < name.size(); i++) {
            if (name[i] == ' ') {
                cout << "Имя или фамилия содержит пробел!!!";
                return false; // если слово содержит пробел, возвращаем фолз
            }
            
        }
    }
    return true; // только если все проверки пройдены и фолз ни разу не прокнулась, то возвращаем тру
}

bool number_is_right(string number) { // тут все по аналогии с именем
    if (number.size() != 11) { cout << "номер должен быть другого размера !!!" << endl; return false; }
    else {
        string trash = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnmЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮйцукенгшщзхъфывапролджэячсмитьбю!\"№;%:?*()_+=@#$^&<>[]{}";
        for (int i = 0; i < number.size(); i++) {
            for (int j = 0; j < trash.size(); j++) {
                if (number[i] == trash[j]) {
                    cout << "Номер телефона содержит мусор!!!" << endl;
                    return false;
                }
            }
        }

        for (int i = 0; i < number.size(); i++) {
            if (number[i] == ' ') {
                cout << "Номер телефона содержит пробел!!!";
                return false;
            }

        }

        if (number[0] != '8') { cout << "У вас какойто зарубеждный номер, таким здесь не рады >:0" << endl; return false; }
    }
    return true;
}

bool date_is_right(int *DATE) { // тут я фулл твою проверку взял
    if (DATE[0] < 1 || DATE[0] > 31) {
        cout << "Столько дней небываит!!!" << endl;
        return false;
    }
    if (DATE[1] < 1 || DATE[1] > 12) {
        cout << "Столько месяцев небываит!!!" << endl;
        return false;
    }
    if ((DATE[1] == 4 || DATE[1] == 6 || DATE[1] == 9 || DATE[1] == 11) && DATE[0] > 30) {
        cout << "В этом месяце столько дней небываит!!!" << endl;
        return false;
    }
    if (DATE[1] == 2 && DATE[0] > 29) {
        cout << "Это же февраль..." << endl;
        return false;
    }
    if (DATE[1] == 2 && DATE[0] == 29)
    {
        if (DATE[2] % 100 == 0 && DATE[2] % 400 != 0) {
            cout << "Не та високосность!!!" << endl;
            return false;
        }
        else if (DATE[2] % 100 != 0 && DATE[2] % 4 != 0) {
            cout << "Не та високосность!!!" << endl;
            return false;
        }
    }
    if (DATE[2] < 1900) { cout << "Год слишком бородатый!!!" << endl; return false; }
    if (DATE[2] == 2023) {
        if (DATE[1] == 2) {
            if (DATE[0] > 13) { cout << "Завтра ещё никто не родился!!!" << endl; return false; }
        }
        else if (DATE[1] > 2) {
            cout << "Завтра ещё никто не родился!!!" << endl; return false;
        }
    } else if(DATE[2] > 2023) { cout << "Завтра ещё никто не родился!!!" << endl; return false; }
    return true;
}

#pragma endregion

class NOTE {    // основной класс нашей базы данных
private:        // поля с данными, они закрыты, как и подобает любым полям с данными
    struct node {   
        // это у нас "ячейка", как когда мы писали список. Потмоу что база данных будет представлять собой список, причем односвязный,
        // самый дефолтный. Поэтому операции все будут происходить как во 2 лабе по саоду. Класс NOTE как бы оболочка для списка, а все данные уже
        // хранятся внутри ячеек, то есть поля для них тоже делаем внутри ячейки.
        string name;    // имя (по английски)
        string surname; // фамилия (по английски)
        string number;  // номер (телефона) ((по английски)) (((там дальше всё тоже по английски будет)))
        int DATE[3];    // я сделаю дату в виде дд.мм.гггг 
        node* pNext;    // указатель на следующую ячейку
        node(string name, string surname, string number, int DATE[3], node* pNext = nullptr) {
            this->name = name; this->surname = surname; this->number = number;
            for (int i = 0; i < 3; i++) { this->DATE[i] = DATE[i]; }
            this->pNext = pNext;
            // в конструкторе ячейки заполняем все поля переданными данными (при создании ячейки). т.к. дата это массив, его заполняем через цикл
        }
    };
    node* HEAD;     // указатель на голову
    int SIZE;       // размер
    void DECONSTRUCTION(string buff) {
        if (buff != "") {
            int count = 0; for (int i = 0; i < buff.size(); ++i) { if (buff[i] == '|') ++count; }
            if (count == 3) {
                string name, surname, number, day, month, year; int DATE[3], i = 0;
                while (buff[i] != '|' && buff[i] != '\0') { name.push_back(buff[i]); ++i; } ++i;
                while (buff[i] != '|' && buff[i] != '\0') { surname.push_back(buff[i]); ++i; } ++i;
                while (buff[i] != '|' && buff[i] != '\0') { number.push_back(buff[i]); ++i; } ++i;
                while (buff[i] != '.' && buff[i] != '\0') { day.push_back(buff[i]); ++i; } ++i;
                while (buff[i] != '.' && buff[i] != '\0') { month.push_back(buff[i]); ++i; } ++i;
                while (buff[i] != '\0') { year.push_back(buff[i]); ++i; }
                // Мы получаем на вход строку, и надо разделить её на 4 части. С помощью | она разделена в файле, 
                // поэтому мы идем по строке пока не встретим этот символ, и записываем все сначала в переменную имя,
                // потмо в фамилию и номер. Когда дошли до даты, там мы начинаем идти до каждой точки и тоже пишем дату в строки
                // а уже потмо эти строки вносим в массив, потмоу что сразу в массик по 1 символу внести не получится
                DATE[0] = atoi(day.c_str());
                DATE[1] = atoi(month.c_str());
                DATE[2] = atoi(year.c_str());
                push_back(name, surname, number, DATE);
            }
            else { cout << "Неполные или поврежденный данные!!!" << endl; }
        }
        else { cout << "Пустая строка!!!" << endl; }
    }
    void swap(node* left, node* right) { // меняет местами 2 ячейки списка, посредством перепривязки указателей. нужно для пузырьковой сортировки
        if (left->pNext == HEAD && right->pNext->pNext == nullptr) {
            HEAD = right->pNext;
            HEAD->pNext = left->pNext;									// Если левый - голова, а правый - хвост
            left->pNext->pNext = nullptr;
        }
        else if (left->pNext == HEAD) {
            node temp = *right->pNext;
            HEAD = right->pNext;										// Если левый - голова
            HEAD->pNext = left->pNext;
            left->pNext->pNext = temp.pNext;
        }
        else if (right->pNext->pNext == nullptr) {
            node temp1 = *left, temp2 = *right;
            left->pNext->pNext = nullptr;								// Если правый - хвост
            left->pNext = temp2.pNext;
            left->pNext->pNext = temp1.pNext;
        }
        else {
            node temp1 = *left, temp2 = *right, temp3 = *right->pNext;
            left->pNext->pNext = temp3.pNext;							// Если всё остальное
            left->pNext = temp2.pNext;
            left->pNext->pNext = temp1.pNext;
        }
    }
public:         // методы. Они крутые, потмоу что сразу принадлежат к этому классу
    NOTE() { HEAD = nullptr; SIZE = 0; }
    ~NOTE() { clear(); } // чистка динамической памяти. В отчете напиши, что "реализовала очистку динамической памяти"
    bool push_back(string name, string surname, string number, int DATE[3]) { // функция будет возвращать фолз, если прокнулась ошибка
        name[0] = toupper(name[0]);                 // делаем у фамилии и имени 
        surname[0] = toupper(surname[0]);           // первую букву большой
        if (name[0] == 'я') { name[0] = 'Я'; }      // хз почему, но эта функция
        if (surname[0] == 'я') { surname[0] = 'Я'; }// не работает только с буквой "я"
        if (number[0] == '+' && number[1] == '7') { number[1] = '8'; number.erase(number.begin()); } // эта строчка превращает +7 в 8
        // Сейчас мы сделаем 1 миллиард проверок того, что мы ввели. И только если все проверки будут пройдены, данные внесутся.
        if (name_is_right(name)) { // проверяем имя, если норм, ием дальше
            if (name_is_right(surname)) { // проверяем фамилию, если норм, идем дальше
                if (number_is_right(number)) {
                    if (date_is_right(DATE)) {
                        // вот у нас пройдены все проверки и теперь мы проверим, нет ли у нас уже такого человека
                        if (std::find(ALL_PEOPLE.begin(), ALL_PEOPLE.end(), pair<string, string> {name, surname}) == ALL_PEOPLE.end()) {
                        // функция std::find работает по 3 параметрам (начало, конец, че ищем), и возвращает итератор на найденный элемент.
                        // если элемент не найден, она возвращает итератор на конец. То есть, если результат поиска равен концу, то продолжаем
                        // а если нет, значит такой чел найден и мы просим повторить ввод.
                            // теперь проверяем номера телефонов по той же схеме
                            if (std::find(ALL_NUMBERS.begin(), ALL_NUMBERS.end(), number) == ALL_NUMBERS.end()) {
                                // теперь мы вносим человека и его номер в эти векторы и в наш список. Наконецто.
                                ALL_PEOPLE.push_back(pair<string, string> {name, surname}); ALL_NUMBERS.push_back(number);
                                if (!SIZE) { // если список пустой, вносим в голову
                                    HEAD = new node(name, surname, number, DATE); ++SIZE;
                                    return true;
                                }
                                else { // если список не пустой, вносим в хвост
                                    node* current = HEAD;				// вспомогательный указатель, с помощью которого начиная с головы
                                    while (current->pNext != nullptr) {	// мы "бежим" по списку в цикле, пока не окажемся в хвосте
                                        current = current->pNext;
                                    }
                                    current->pNext = new node(name, surname, number, DATE); ++SIZE;
                                    return true;
                                }
                                // всё, теперь чел чилит в твоей записной книжке
                            }
                            else { cout << "Этот номер принадлежит другому человеку!!!" << endl; return false; }
                        }
                        else { cout << "Такой человек уже существует!!!" << endl; return false; }
                    }
                    else { cout << "Повторите ввод!!!" << endl; return false; }
                }
                else { cout << "Повторите ввод!!!" << endl; return false; }
            }
            else { cout << "Повторите ввод!!!" << endl; return false; }
        }
        else { cout << "Повторите ввод!!!" << endl; return false; }
    }
    bool rewrite(string name, string surname) {
        node* current = HEAD;
        while (current != nullptr) {
            if (current->name == name && current->surname == surname) {
                cout << "Выберите дефект, который хотите исправить:" << endl;
                cout << "1. Имя\n" << "2. Фамилия\n" << "3. Номер телефона\n" << "4. Дату рождения" << endl;
                string BUTTON;
                getline(cin, BUTTON);
                switch (atoi(BUTTON.c_str()))
                {
                case 1: {
                    string new_name;
                    while (true) {
                        cout << "Введите новое имя: "; getline(cin, new_name);
                        new_name[0] == 'я' ? new_name[0] = 'Я' : new_name[0] = toupper(new_name[0]);
                        // опять все те же проверки, но только для имени.
                        if (name_is_right(new_name)) {
                            if (std::find(ALL_PEOPLE.begin(), ALL_PEOPLE.end(), pair<string, string> {new_name, surname}) == ALL_PEOPLE.end()) {
                                ALL_PEOPLE.push_back(pair<string, string> {new_name, surname});
                                current->name = new_name;
                                return true;
                            }
                            else { cout << "Такой человек уже существует!!!" << endl;}
                        }
                        else { cout << "Повторите ввод!!!" << endl;}
                    }
                   
                }
                case 2: {
                    string new_surname;
                    while (true) {
                        cout << "Введите новую фамилию: "; getline(cin, new_surname);
                        new_surname[0] == 'я' ? new_surname[0] = 'Я' : new_surname[0] = toupper(new_surname[0]);
                        // опять все те же проверки, но только для фамилии.
                        if (name_is_right(new_surname)) {
                            if (std::find(ALL_PEOPLE.begin(), ALL_PEOPLE.end(), pair<string, string> {name, new_surname}) == ALL_PEOPLE.end()) {
                                ALL_PEOPLE.push_back(pair<string, string> {name, new_surname});
                                current->surname = new_surname;
                                return true;
                            }
                            else { cout << "Такой человек уже существует!!!" << endl;}
                        }
                        else { cout << "Повторите ввод!!!" << endl;}
                    }
                    
                }
                case 3: {
                    string new_number;
                    while (true) {
                        cout << "Введите новый номер телефона: "; getline(cin, new_number);
                        // опять все те же проверки, но только для номера.
                        if (number_is_right(new_number)) {
                            if (std::find(ALL_NUMBERS.begin(), ALL_NUMBERS.end(), new_number) == ALL_NUMBERS.end()) {
                                ALL_NUMBERS.push_back(new_number);
                                current->number = new_number;
                                return true;
                            }
                            else { cout << "Этот номер принадлежит другому человеку!!!" << endl;}
                        }
                        else { cout << "Повторите ввод!!!" << endl;}
                    }
                    
                }
                case 4: {
                    string temp; int DATE[3];
                    while (true) {
                        cout << "Введите дату рождения: "; getline(cin, temp);
                        DATE[0] = atoi(temp.c_str()); temp.clear();
                        cout << "Введите месяц рождения: "; getline(cin, temp);
                        DATE[1] = atoi(temp.c_str()); temp.clear();
                        cout << "Введите год рождения: "; getline(cin, temp);
                        DATE[2] = atoi(temp.c_str()); temp.clear();
                        if (date_is_right(DATE)) {
                            for (int i = 0; i < 3; i++) { current->DATE[i] = DATE[i]; }
                            return true;
                        }
                        else { cout << "Повторите ввод!!!" << endl;}
                    }
                   
                }
                default:
                    cout << "Других полей нема" << endl;
                    break;
                }
            }
            current = current->pNext;
        }
        cout << "Элемент не найден!!!" << endl;
        return false;
    }
    bool erase(string name, string surname) {
        int temp[3] = { 0,0,0 }; // Это просто болванка, которую нужно просто передать в конструктор, чтобы он корректно работал
        // т.к. список односвязный, мы не можем удалить текущий элемент, так как не сможем тогда привязять следующий к предыдущему. Поэтому мы идем до элемента
        // который предшествует нужному, и удаляем как бы следующий. а для этого нам нужен каррент, которуй будет указывать на голову. Собственно это он и есть:
        node* current = new node("", "", "", temp, HEAD);
        while (current->pNext != nullptr) {
            if (current->pNext->name == name && current->pNext->surname == surname) {
                if (std::find(ALL_PEOPLE.begin(), ALL_PEOPLE.end(), pair<string,string>{name, surname}) != ALL_PEOPLE.end())
                {
                    ALL_PEOPLE.erase(std::find(ALL_PEOPLE.begin(), ALL_PEOPLE.end(), pair<string, string>{name, surname}));
                }
                // удаляем элемент из коллекции сотрудников только если он там есть
                // такое условие нужно, чтобы метод не пытался удалить больше элементов, чем содержит коллекция
                if (current->pNext == HEAD) {
                    node* temp = HEAD;
                    HEAD = HEAD->pNext;
                    delete temp; --SIZE;
                    return true;
                }
                else {
                    node* temp = current->pNext;
                    current->pNext = current->pNext->pNext;
                    delete temp; --SIZE;
                    return true;
                }
                break;
            }
            current = current->pNext;
        }
        cout << "Элемент не найден!!!" << endl;
        return false;
    }
    void clear() { while (SIZE) { erase(HEAD->name,HEAD->surname); } } // метод очищает список
    void find(int month) {

        if (month < 1 || month > 12) { cout << "Такого месяца не бывает!!!" << endl; }
        else {
            // тут кароче просто перебор все ячеек и вывод их, как в функции print, то только если она удовлетворяет условию,
            // то есть если месяц тот, который нужен
            cout << " ---------------------------------------------------------------------------------" << endl;
            cout << "| " << "Фамилия";
            for (int i = 0; i < abs(int(20 - 7)); ++i) { cout << " "; }
            cout << "| " << "Имя";
            for (int i = 0; i < abs(int(20 - 3)); ++i) { cout << " "; }
            cout << "| " << "Номер телефона";
            for (int i = 0; i < abs(int(20 - 14)); ++i) { cout << " "; }
            cout << "| " << "Дата рождения" << " |" << endl;
            node* current = HEAD;
            while (current != nullptr) {
                if (current->DATE[1] == month) {
                    cout << "-----------------------------------------------------------------------------------" << endl;
                    cout << "| " << current->surname;
                    for (int i = 0; i < abs(int(20 - current->surname.size())); ++i) { cout << " "; }
                    cout << "| " << current->name;
                    for (int i = 0; i < abs(int(20 - current->name.size())); ++i) { cout << " "; }
                    cout << "| " << current->number;
                    for (int i = 0; i < abs(int(20 - current->number.size())); ++i) { cout << " "; }
                    cout << "| ";

                    current->DATE[0] < 10 ? cout << "0" : cout << "";       // это кароче чтобы вместо 2.2.2002 писалось 02.02.2002
                    cout << current->DATE[0] << ".";                        // тут тернарный оператор ? : он работает как иф елсе
                                                                            // и проверяет типа, если число меньше 10, то перед ним пишет 0
                    current->DATE[1] < 10 ? cout << "0" : cout << "";       // если нет, то ничего ен пишет
                    cout << current->DATE[1] << "." << current->DATE[2];    // а после пишет уже само число

                    for (int i = 0; i < 14 - 10; ++i) { cout << " "; }
                    cout << "|" << endl;
                   
                }
                current = current->pNext;
            }
            cout << " ---------------------------------------------------------------------------------" << endl;
        }
    }
    void print() { // тут кароче лучше просто спроси когда дойдешь до этого момента
        if (!SIZE) { cout << "Список пуст!!!" << endl;}
        else {
            cout << " ---------------------------------------------------------------------------------" << endl;
            cout << "| " << "Фамилия";
            for (int i = 0; i < abs(int(20 - 7)); ++i) { cout << " "; }
            cout << "| " << "Имя";
            for (int i = 0; i < abs(int(20 - 3)); ++i) { cout << " "; }
            cout << "| " << "Номер телефона";
            for (int i = 0; i < abs(int(20 - 14)); ++i) { cout << " "; }
            cout << "| " << "Дата рождения" << " |" << endl;
            node* current = HEAD;
            while (current != nullptr) {
                cout << "-----------------------------------------------------------------------------------" << endl;
                cout << "| " << current->surname;
                for (int i = 0; i < abs(int(20 - current->surname.size())); ++i) { cout << " "; }
                cout << "| " << current->name;
                for (int i = 0; i < abs(int(20 - current->name.size())); ++i) { cout << " "; }
                cout << "| " << current->number;
                for (int i = 0; i < abs(int(20 - current->number.size())); ++i) { cout << " "; }
                cout << "| "; 

                current->DATE[0] < 10 ? cout << "0" : cout << "";       // это кароче чтобы вместо 2.2.2002 писалось 02.02.2002
                cout << current->DATE[0] << ".";                        // тут тернарный оператор ? : он работает как иф елсе
                                                                        // и проверяет типа, если число меньше 10, то перед ним пишет 0
                current->DATE[1] < 10 ? cout << "0" : cout << "";       // если нет, то ничего ен пишет
                cout << current->DATE[1] << "." << current->DATE[2];    // а после пишет уже само число

                for (int i = 0; i < 14 - 10; ++i) { cout << " "; }
                cout << "|" << endl;
                current = current->pNext;
            }
            cout << " ---------------------------------------------------------------------------------" << endl;
        }
    }
    void read() {
        ifstream fin(file);
        if (!fin.is_open())
        {
            cout << "Ошибка открытия файла для чтения!!!" << endl; Sleep(300);
        }
        else {
            string buff; char symb;
            while (fin.get(symb)) {
                if (symb != '\n') { buff += symb; }
                else { DECONSTRUCTION(buff); buff = ""; }
            }
            if (buff != "") { DECONSTRUCTION(buff); }
            cout << "Файл успешно считан!" << endl;
        }
        fin.close();
    }
    void save() {
        ofstream fout(file);							// открываем файл, параметр ofstream::app позволяет дописывать данные. 
        if (!fout.is_open()) {
            cout << "Ошибка открытия файла для записи!!!" << endl; Sleep(300);
        }
        else {
            node* current = HEAD;
            while (current != nullptr) {
                fout << current->name << "|";					// почти как функция print() только 
                fout << current->surname << "|";				// транслируем не в консоль а в файл,
                fout << current->number << "|";	                // который передали в параметре
                for (int i = 0; i < 3; i++) 
                {
                    fout << current->DATE[i];
                    if (i != 2) { fout << "."; }
                }
                fout << "\n";
                current = current->pNext;
            }
            cout << "Файл успешно сохранён!" << endl;
        }
        fout.close();
    }
    void sort() {
        if (!SIZE) { cout << "Список пуст!!!" << endl; Sleep(300); }
        else { // тут обычная пузырьковая сортировка, только вместо чисел коды первой буквы в слове.
            for (int i = 0; i < SIZE; ++i) {
                int temp[3]{ 0,0,0 }; // тут штука такая же как в методе удаления
                node* current = new node("", "", "", temp, HEAD);
                while (true) {
                    if (current->pNext->pNext == nullptr) { break; }
                    if (-int(current->pNext->surname[0]) <= -int(current->pNext->pNext->surname[0]))
                    {
                        swap(current, current->pNext);
                    }
                    current = current->pNext;
                }
            }
        }
    }
    int size() { return SIZE; }
};

#pragma region MENU_ITEMS

void ADD_NEW(NOTE &note) { // 1. Добавить новую запись
    string name, surname, number, temp;
    int DATE[3];
    do {
        cout << "Введите имя: "; getline(cin, name);
        cout << "Введите фамилию: "; getline(cin, surname);
        cout << "Введите номер телефона: "; getline(cin, number);
        cout << "Введите день рождения: "; getline(cin, temp);
        DATE[0] = atoi(temp.c_str()); temp.clear();
        cout << "Введите месяц рождения: "; getline(cin, temp);
        DATE[1] = atoi(temp.c_str()); temp.clear();
        cout << "Введите год рождения: "; getline(cin, temp);
        DATE[2] = atoi(temp.c_str()); temp.clear();
        // В цикле ду вайл заполняем поля все, чтобы если прокнется ошибка, метод пушбек вернул фолз, и цикл начался сначала, чтобы сразу был повторный ввод
        // в переменную темп записываются цифры, потмо с помощью atoi переводятся в тип int. Но у этой функции есть особенность - если она видит букву
        // она её превращает в 0. То есть если в дату ввести буквы, то прокнется ошибка как будто туда ввели 0. Другие функции просто крашут программу если видят
        // цифру, а это неоч
        
    } while (!note.push_back(name, surname, number, DATE));
   
}

void EDIT_CURRENT(NOTE& note) { // 2. Редактировать запись
    if (!note.size()) { cout << "Список пуст!!!" << endl; }
    else {
        string name, surname;
        do {
            cout << "Введите имя дефектного человека: "; getline(cin, name);
            cout << "Введите фамилию дефектного человека: "; getline(cin, surname);
            name[0] = toupper(name[0]);                 // делаем у фамилии и имени 
            surname[0] = toupper(surname[0]);           // первую букву большой
            if (name[0] == 'я') { name[0] = 'Я'; }      // хз почему, но эта функция
            if (surname[0] == 'я') { surname[0] = 'Я'; }// не работает только с буквой "я"

        } while (!note.rewrite(name, surname));
    }
}

void DELETE_CURRENT(NOTE& note) { // 3. Удалить запись
    if (!note.size()) { cout << "Список пуст!!!" << endl; }
    else {
        string name, surname;
        do {
            cout << "Введите имя ненужного человека: "; getline(cin, name);
            cout << "Введите фамилию ненужного человека: "; getline(cin, surname);
            name[0] = toupper(name[0]);                 // делаем у фамилии и имени 
            surname[0] = toupper(surname[0]);           // первую букву большой
            if (name[0] == 'я') { name[0] = 'Я'; }      // хз почему, но эта функция
            if (surname[0] == 'я') { surname[0] = 'Я'; }// не работает только с буквой "я"

        } while (!note.erase(name, surname));
    }
}

void FIND_POPLE(NOTE& note) {
    if (!note.size()) { cout << "Список пуст!!!" << endl; }
    else {
        string month;
        cout << "Введите порядковый номер месяца: "; getline(cin, month);
        note.find(atoi(month.c_str()));
    }
}

#pragma endregion

int main() {
    srand(time(0));
    setlocale(0, "RUSSIAN");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    NOTE note;
    string BUTTON;
    while (true) {
        cout << "1. Добавить новую запись" << endl
             << "2. Редактировать запись" << endl
             << "3. Удалить запись" << endl
             << "4. Поиск контактов по месяцу рождения" << endl
             << "5. Распечатать все записи" << endl
             << "6. Загрузить из файла" << endl
             << "7. Сохранить в файл" << endl
             << "8. Сортировать по алфавиту" << endl
             << "9. Очистить весь список" << endl
             << "0. Выход" << endl;
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));    // это нужно чтобы очищать буфер ввода
        getline(cin, BUTTON);
        switch (atoi(BUTTON.c_str()))
        {
        case 1: ADD_NEW(note); break;           // 1. Добавить новую запись
        case 2: EDIT_CURRENT(note); break;      // 2. Редактировать запись
        case 3: DELETE_CURRENT(note); break;    // 3. Удалить запись
        case 4: FIND_POPLE(note); break;        // 4. Поиск контактов по месяцу рождения
        case 5: note.print(); break;            // 5. Распечатать все записи
        case 6: note.read(); break;             // 6. Загрузить из файла
        case 7: note.save(); break;             // 7. Сохранить в файл
        case 8: note.sort(); break;             // 8. Сортировать по алфавиту
        case 9: note.clear(); break;            // 9. Очистить весь список
        case 0: return 0;                       // 0. Выход
        default:
            cout << "Такого пункта меню не существует в объективной реальности!!!" << endl;
            break;
        }
    }
}
