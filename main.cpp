//
//  main.cpp
//  lab13
//
//  Created by Alex on 02.12.2019.
//  Copyright © 2019 Alex. All rights reserved.
//

#include <iostream>
#include <locale.h>
#include <fstream>
#include <cctype>
#include <algorithm>


using namespace std ;

string convertToString(char* a, int size);
int fileCheck(char *fname, const char *); //проверка наличия файла
void addElement(char *fname) ; //добавление новых записей
void printHeadline() ; //вывод заголовка таблицы
void showBase(char *fname) ;//просмотр содержимого файла
void search(char *fname1, char *fname2); //поиск по ключу
void sortName(char *fname); //сортировка по строке
void sortType(char *fname); // сортировка по строке (тип самолета)
void sortFlights(char *fname); // сортировка по числу
const char PR_R[] = "r" ; //признак открытия файла на чтение
const char PR_S[] = "r+" ;  //признак открытия файла на чтение и запись
const char PR_W[] = "w" ; //признак открытия файла на запись
const char PR_A[] = "a" ; // признак открытия файла на добавление


#define FNAME_I "base.dat"
#define FNAME_R "search.dat"

typedef struct {
    char airline[15] ; //название воздушной линии
    char type[8] ; //тип самолета
    int amount; //количество рейсов
    float len; // налет тыс. км
    float perkilo; // пассажирооборот чел/км
} motion;


int main(int argc, const char * argv[]) {
    
    char fname_i[20] = FNAME_I ;
    char fname_r[20] = FNAME_R ;
    
    setlocale(LC_ALL, "RU");
    
    int choise;
    char otv;
    
    for( ; ;) {
        //Выбор вида действия с содержимым файла
        cout << "\nВид действия: " << endl;
        cout << " 1 - создание базы данных" << endl;
        cout << " 2 - добавление новых записей " << endl;
        cout << " 3 - сортировка по наименованию" << endl;
        cout << " 4 - сортировка по типу самолета" << endl;
        cout << " 5 - сортировка по количеству рейсов" << endl;
        cout << " 6 - поиск по названию воздушной линии"<<endl;
        cout << " 7 - просмотр базы данных" << endl;
        cout << " 8 - просмотр базы данных поиска" << endl;
        cout << " 9 - завершение задачи" << endl;
        cout << "Введите вид действия -> ";
    cin >> choise ;
    //действия в зависимости от выбора
        switch( choise ){
            case 1:
                if(fileCheck(fname_i, PR_R)){
                    cout << "База данных с именем "<< fname_i;
                    cout << " была создана раньше." << endl;
                    cout << " Создаём файл с новым именем? [Y/N] ";
                    cin >> otv ;
                    cin.get() ; //убираем символ '\n' из потока
                    if(otv == 'Y' || otv == 'y'){
                        cout << "Задайте имя создаваемого файла: ";
                        cin >> fname_i ;
                    }
                    else break;
                }
                if(!fileCheck(fname_i, PR_W)){
                    cout << "\n Ошибка открытия файла для записи" << endl;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break ;
                }
                
                cout << " Создаем базу " << fname_i << endl;
                addElement(fname_i);
                cout << "\n Создание файла закончено." << endl;
                if(fileCheck(fname_i, PR_R))
                    cout << " База данных готова к работе " << endl;
                else
                    cout << "\n База не создана" << endl;
                cout << " Для продолжения нажмите Enter-> ";
                getchar();
                break;
            
                
                
            case 2:
                if(fileCheck(fname_i, PR_R)){
                    cout << " База данных экскурсий с именем " << fname_i;
                    cout << " была создана раньше." << endl ;
                    cout << " Будем добавлять новые записи в неё? [Y/N] ";
                    cin >> otv;
                    cin.get();
                    
                    if(otv == 'N' || otv == 'n'){
                        cout << " Задайте имя файла другой базы: ";
                        cin >> fname_i ;
                        if(!fileCheck(fname_i, PR_R)){
                            cout << " Такая база данных не создавалась" << endl;
                            cout << " ДлCя продолжения нажмите Enter-> ";
                            getchar() ;
                            break ;
                        }
                    }
               }
               cout << " Добавляем записи в файл " << fname_i << endl;
               addElement(fname_i);
               cout << "\n Изменение файла закончено.";
               cout << " Для продолжения нажмите Enter-> ";
               getchar();
               break;
            
                
            case 3:
                if(!fileCheck(fname_i, PR_S)){
                    cout << "\n Ошибка открытия файла для чтения и записи" << endl;
                    cout << " Для продолжения нажмите Enter-> " ;
                    getchar() ;
                    break ;
                }
                sortName(fname_i);
                cout << "\n Сортировка закончена.";
                cout << " Для продолжения нажмите Enter-> ";
                getchar();
                    break;
                
                
                
            case 4:
                if(!fileCheck(fname_i, PR_S)){
                    cout << "\n Ошибка открытия файла для чтения и записи " << endl;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break;
                    }
                sortType(fname_i) ;
                cout << "\n Сортировка закончена." ;
                break;
             
            break;
                
            case 5:
                if(!fileCheck(fname_i, PR_S)){
                        cout << "\n Ошибка открытия файла для чтения и записи " << endl;
                        cout << " Для продолжения нажмите Enter-> ";
                        getchar();
                        break;
                    }
                    sortFlights(fname_i);
                    cout << "\n Сортировка закончена." ;
                    break;
                    
                break;
                
            case 6:
                if(!fileCheck(fname_i, PR_S)){
                    cout << "\n Ошибка открытия файла для чтения" << endl;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break;
                }
                if(!fileCheck(fname_r, PR_W)){
                    cout << "\n Ошибка открытия файла для записи" << endl;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break;
                }
                
                search(fname_i, fname_r);
                cout << "\n Поиск закончен.";
                break;
                
                
            case 7:
                if(!fileCheck(fname_i, PR_R)){
                    cout << "\n Ошибка открытия файла для чтения" << endl;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break ;
                
                }
                showBase(fname_i) ;
                break ;
                
                
                
            case 8:
                if(!fileCheck(fname_r, PR_R)){
                    cout << "\n Ошибка открытия файла для чтения" << endl ;
                    cout << " Для продолжения нажмите Enter-> ";
                    getchar();
                    break ;
                }
                showBase(fname_r) ;
                getchar();
                break;
                
                
            case 9: return 0;
                
            default:
                cout << "Ошибка ввода. Перезапустите программу\n";
                return 1;
                }
    }
    return 0;
}


//Добавление новых элементов в базу данных
void addElement(char *fname){
    char answer ;
    motion a ;
    FILE *base ;
    base = fopen(fname, PR_A);
    rewind(base) ;
    do {
        cout << "\n Название воздушной линии? " ;
        cin >> a.airline ;
        cout << " Тип самолета? " ;
        cin >> a.type ;
        cout << " Количество рейсов? " ;
        cin >> a.amount ;
        cout << " Налет (тыс. км)? " ;
        cin >> a.len ;
        cout << " Пассажирооборот (чел/км)  " ;
        cin >> a.perkilo ;
        fwrite(&a, sizeof(a), 1, base) ;
        cout << "\n Продолжать?[Y/N] ";
        cin >> answer ;
        cin.get() ;
        }
    while(answer == 'Y' || answer == 'y') ;
    fclose(base) ;
    }


//Вывод заголовка при просмотре исходного файла
void printHeadline(){
    cout<<"\n";
    for(int i = 0; i<88; i++){
        cout<<"-";
    }
    cout<<"\n";
    cout<<" Название воздушной линии | Тип самолета | Количество рейсов | Налет | Пассажирооборот ";
    for(int i = 0; i<88; i++){
        cout<<"-";
    }
}



void showBase(char *filename)
{
    int i ;
    motion a;
    FILE *base ;
    base = fopen(filename, PR_R) ;
    cout << "\n База данных" ;
   // zag1() ;
    
    cout<<"\n";
    for(int i = 0; i<88; i++){
        cout<<"-";
    }
    cout<<"\n";
    cout<<"| Название воздушной линии | Тип самолета | Количество рейсов | Налет | Пассажирооборот |\n";
    for(int i = 0; i<88; i++){
        cout<<"-";
    }
    
    rewind(base) ;
    while(fread(&a, sizeof(a), 1, base) > 0) {
    cout << "\n|" ;
    cout.width(26) ;
    cout << a.airline << "|" ;
    cout.width(14) ;
    cout << a.type << "|" ;
    cout.width(19) ;
    cout << a.amount<< "|" ;
    cout.width(7) ;
    cout << a.len<< "|" ;
    cout.width(17) ;
    cout << a.perkilo<< "|" ;
    }
        cout << "\n" ;
        for(i = 1; i <= 88; i++)
            cout << "-" ;
    fclose(base) ;
}

int fileCheck(char *filename, const char *w){
    if((fopen(filename, w)) == NULL) return 0;
    return 1;
}


void sortName(char *filename){
    int i ;
    int fl ;
    string s1 = "", s2 = "";
    motion p, a;
    FILE *base ;
    base = fopen(filename, PR_S) ; //открываем файл на чтение и запись
    do{
        rewind(base) ;
        fl = 0 ;
        for(i =0; fread(&a, sizeof(a), 1, base) > 0; i +=sizeof(a), fseek(base, i, SEEK_SET)){
            if(fread(&p, sizeof(a), 1, base) > 0){
                // переводим строки в одинаковый регистр для правильного сравнения
                s1 = convertToString(a.airline, 15);
                s2 = convertToString(p.airline, 15);
                transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
                transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
                if(strncmp(s1.c_str(), s2.c_str(), 15) > 0) {
                    fseek(base, i, SEEK_SET) ;
                    fwrite(&p, sizeof(a), 1, base);
                    fwrite(&a, sizeof(a), 1, base);
                    fl = 1;
                
                }
            }
            
        }
    }
    while(fl);
    fclose(base) ;
}


string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}


void sortFlights(char *fname){
    int i ;
    int fl ;
    motion p, a;
    FILE *baza ;
    baza = fopen(fname, PR_S) ;
    do{
        rewind(baza);
        fl = 0;
        for(i =0; fread(&a, sizeof(a), 1, baza) > 0; i += sizeof(a), fseek(baza, i, SEEK_SET)){
            if(fread(&p, sizeof(a), 1, baza) > 0){
                if(a.amount > p.amount){
                    fseek(baza, i, SEEK_SET) ; //позиция i от НАЧАЛА файла
                    fwrite(&p, sizeof(a), 1, baza) ; fwrite(&a, sizeof(a), 1, baza) ; fl = 1 ;
                }
                
            }
        }
    }
    while(fl);
    fclose(baza) ;
}
void sortType(char *fname){
    int i ;
    int fl ;
    string s1 = "", s2 = "";
    motion p, a;
    FILE *base ;
    base = fopen(fname, PR_S) ; //открываем файл на чтение и запись
    do{
        rewind(base) ;
        fl = 0 ;
        for(i =0; fread(&a, sizeof(a), 1, base) > 0; i +=sizeof(a), fseek(base, i, SEEK_SET)){
            if(fread(&p, sizeof(a), 1, base) > 0){
                // переводим строки в одинаковый регистр для правильного сравнения
                s1 = convertToString(a.type, 15);
                s2 = convertToString(p.type, 15);
                transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
                transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
                if(strncmp(s1.c_str(), s2.c_str(), 15) > 0) {
                    fseek(base, i, SEEK_SET) ; //позиция i от НАЧАЛА файла
                    fwrite(&p, sizeof(a), 1, base);
                    fwrite(&a, sizeof(a), 1, base);
                    fl = 1;
                
                }
            }
            
        }
    }
    while(fl);
    fclose(base) ;
}


void search(char *fname1, char *fname2){
    char line[15] ;
     motion a;
     FILE *in, *out ;
    in = fopen(fname1, PR_R) ;
    out = fopen(fname2, PR_W) ;
    cout << "\n Название воздушной линии? " ;
    cin >> line ;
    rewind(in) ;
    while(fread(&a, sizeof(a), 1, in) > 0){
        
        if(strncmp(a.airline, line, 15) == 0){
            fwrite(&a, sizeof(a), 1, out);
        }
    }
    fclose(out) ;
    fclose(in) ;
}
