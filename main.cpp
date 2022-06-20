#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int random() {
    return rand() % 36 +1;
}

void println(string to_print) {
    std::cout << to_print << std::endl;
}

bool binary_choice(string question, string answ1, string answ2) {
    // Returns true if the first answ is chosen else false.
    bool ok_answ = false;
    string answ;
    while (!ok_answ) {
        println(question);
        cin >> answ;
        if (answ == answ1 || answ == answ2) {
            ok_answ = true;
        }
    }
    return answ == answ1;
}

int main() {
    srand (time(0));
    bool play = true;
    int bet;
    bool allowed_selection;
    int balance = 1000;
    while (play) {
        if (balance < 100) {
            println("Du kan inte spela mer du har bara" + std::to_string(balance));
            println("Du har förlorat...");
            break;
        }
        while (true) {
            println("");
            println("Du har " + std::to_string(balance));
            println("Välj en insats, 100, 300 eller 500 (kr): ");
            cin >> bet;
            if ((bet == 100 || bet == 300 || bet == 500) && bet <= balance) {
                break;
            }
        }
        balance -= bet;

        bool color_bet = binary_choice(("Vill du satsa på en färg eller på en siffra? (f/n)"), "f", "n");
        if (color_bet) {
            bool color = binary_choice("Vilken färg vill du satsa på? (rod/svart): ", "rod", "svart");
            if (random()%2==0 && !color || random()%2==1 && color) {
                println("Vann med rätt färg");
                balance += bet*3;
            } else {
                println(("Gissade på fel färg, korrekt färg var " + std::string(!color ? "röd" : "svart")));
            }
        } else {
            string number;
            allowed_selection = false;
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
        if (!binary_choice("Vill du spela igen (y/n): ", "y", "n")) break;
    }
    return 0;
}
