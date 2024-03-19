#include <iostream>

using namespace std;

union IP {
    unsigned int value;
    unsigned char adress[4];
};

union Color{
    unsigned int code;
    struct {
        unsigned char B, G, R, A;
    };
};

// В штрих-коде европейского стандарта EAN-13 13 десятичных цифр:
//      3 цифры - код страны,
//      4 цифры - код изготовителя,
//      5 цифр - код товара,
//      1 цифра - контрольная.
// Если хранить код, как строку, понадобится 14 байт.
// Если хранить код, как единое число, понадобится 8 байт (long long),
//      но неудобно разделять на составные элементы.
// В виде, написанном ниже, код займёт 8 байт (размер структуры
//      выравняется до кратного 4) но позволит удобно обращаться
//      к элементам кода.
union Barcode {
    struct {
        unsigned int Country : 10;      // 3 цифры 000..999 - достаточно 10 бит
        unsigned int Manufacturer : 14; // 4 цифры - достаточно 14 бит
        unsigned int Product : 17;      // 5 цифр - достаточно 17 бит
        unsigned int ControlNumber : 4; // 1 цифра - достаточно 4 бит
    };
};

int main(int argc, char *argv[])
{
    Color color;
    color.code = 0xD2691E; // Цвет "шоколадный"
    cout << "Chocolate color. Code: " << color.code << " or 0x" <<
        std::hex << color.code << " in hexadecimal." << endl << std::dec <<
        "Alpha component: " << (int)color.A << endl <<
        "Red component: " << (int)color.R << endl <<
        "Green component: " << (int)color.G << endl <<
        "Blue component: " << (int)color.B << endl;

    IP ip;
    ip.adress[0] = 192;
    ip.adress[1] = 168;
    ip.adress[2] = 0;
    ip.adress[3] = 1;
    cout << endl << "ip adress: " <<
        (int)ip.adress[0] << "." <<
        (int)ip.adress[1] << "." <<
        (int)ip.adress[2] << "." <<
        (int)ip.adress[3] << endl;
    cout << "It is stored as a number: " << ip.value << endl;

    Barcode bcode;
    bcode.Country = 460;
    bcode.Manufacturer = 7029;
    bcode.Product = 10840;
    bcode.ControlNumber = 1;
    cout << endl << "Barcode." << endl <<
        "Country: " << bcode.Country << endl <<
        "Manufacturer: " << bcode.Manufacturer << endl <<
        "Product: " << bcode.Product << endl <<
        "Control digit: " << bcode.ControlNumber << endl;

    return 0;
}
