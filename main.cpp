#include <iostream>;
#include <ctime>;
#include <cstdlib>;
#include <locale.h>;

using namespace std;


int random() {
    return rand() % 36 +1;
}

void println(string to_print) {

    std::cout << to_print << std::endl;
}


int main() {
    setlocale(LC_ALL, "sv_SE");
    srand (time(0));
    bool play = true;
    bool allowed_selection = false;
    int guess;
    int bet;
    int balance = 1000;
    string f_or_n;
    while (play) {
        while (!allowed_selection) {
            println("");
            println("Du har " + std::to_string(balance));
            println("Välj en insats, 100, 300 eller 500 (kr): ");
            cin >> bet;
            allowed_selection = (bet == 100 || bet == 300 || bet == 500);
        }

        allowed_selection = false;
        while (!allowed_selection) {
            println("Vill du satsa på en färg eller på en siffra? (f/n)");
            cin >> f_or_n;
            allowed_selection = (f_or_n == "f" ||f_or_n == "n");
        }

        allowed_selection = false;
        if (f_or_n == "f") {
            string color;
            while (!allowed_selection) {
                println("Vilken färg vill du satsa på? (röd/svart): ");
                cin >> color;
                allowed_selection = (color == "röd" ||color == "svart");
            }
            if (random()%2==0 && color == "svart") {
                println("Vann med rätt färg");
            } else {
                println("Gissade på fel färg :C");
            }
        } else {
            string number;
            while (!allowed_selection) {
                println("Vilken siffra gissar du på?: ");
                cin >> number;
                allowed_selection = 0 <= std::stoi(number) && std::stoi(number) <= 36;
            }
            if (random()==std::stoi(number)) {
                println("Du vann med rätt gissade siffra!");
            } else {
                println("Gissade på fel siffra :C");
            }
        }
    }

    return 0;
}
