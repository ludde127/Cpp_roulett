#include <iostream>;
#include <ctime>;
#include <cstdlib>;

using namespace std;


int random() {
    return rand() % 36 +1;
}

void println(string to_print) {

    std::cout << to_print << std::endl;
}


int main() {
    srand (time(0));
    bool play = true;
    int bet;
    bool allowed_selection;
    int balance = 1000;
    string f_or_n;

    while (play) {
        if (allowed_selection) {
            println("Vill du spela igen (y/n): ");
            string play_again;
            cin >> play_again;
            if (play_again == "n") {
                break;
            }
        }

        allowed_selection = false;
        while (!allowed_selection) {
            println("");
            println("Du har " + std::to_string(balance));
            println("Välj en insats, 100, 300 eller 500 (kr): ");
            cin >> bet;
            balance -= bet;
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
                println("Vilken färg vill du satsa på? (rod/svart): ");
                cin >> color;
                allowed_selection = (color == "rod" ||color == "svart");
            }
            if (random()%2==0 && color == "svart" || random()%2==1 && color == "rod") {
                println("Vann med rätt färg");
                balance += bet*3;
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
                balance += bet * 11;
            } else {
                println("Gissade på fel siffra :C");
            }
        }
    }

    return 0;
}
