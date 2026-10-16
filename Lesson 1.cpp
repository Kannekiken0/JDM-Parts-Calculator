#include <iostream>
#include <string>
#include <vector>

// Структура для представления автозапчасти
struct Part {
    std::string name;
    float price;
    int quantity;

    // Конструктор для быстрого создания объекта
    Part(std::string n, float p, int q) : name(n), price(p), quantity(q) {}
};

// Конвертация USD в JPY
float convertoJPY(float price) {
    return price * 150;
}

// Расчёт скидки в зависимости от суммы в иенах
int calculateDiscount(float totalJpy) {
    if (totalJpy >= 100000) {
        return 20;
    }
    else if (totalJpy >= 50000) {
        return 10;
    }
    else {
        return 0;
    }
}

// Печать чека и содержимого корзины (передача по const reference для оптимизации)
void printReceipt(const std::vector<Part>& cart) {
    std::cout << "\n================ Корзина ================\n";
    for (int i = 0; i < cart.size(); i++) {
        std::cout << i + 1 << ". " << cart[i].name
            << " | Цена: $" << cart[i].price
            << " | Кол-во: " << cart[i].quantity << " шт.\n";
    }
    std::cout << "=========================================\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::string parts;
    float price;
    int quantity;
    int discountPercent = 0;
    int choice = 1;

    std::vector<Part> cart;

    while (choice == 1) {
        std::cout << "Введите название детали: ";
        std::cin >> parts;

        std::cout << "Введите цену ($)USD: ";
        std::cin >> price;

        std::cout << "Введите количество: ";
        std::cin >> quantity;

        // Создаём и сразу добавляем деталь в корзину в одну строчку!
        cart.push_back(Part(parts, price, quantity));

        float Jpy = convertoJPY(price);
        float sumusd = price * quantity;
        float sumjpy = Jpy * quantity;
        float totalprice = sumjpy;
        discountPercent = calculateDiscount(totalprice);
        float finalPrice = totalprice * (1 - discountPercent / 100.0);

        std::cout << "Товар: " << parts << "\n"
            << "Итого в USD: $" << sumusd << "\n"
            << "Итого в JPY: ¥" << sumjpy << "\n"
            << "Цена со скидкой: " << finalPrice << "\n";

        std::cout << "\nХотите посчитать еще одну деталь? (1 - Да, 0 - Выход): ";
        std::cin >> choice;
    }

    printReceipt(cart);

    return 0;
}