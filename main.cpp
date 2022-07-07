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
        cin.ignore();
        cin >> answ;
        if (answ == answ1 || answ == answ2) { // Kolla om svaret är ett av de två tillåtna.
            ok_answ = true;
        }
    }
    return answ == answ1; // Om svaret är == första så ges true
}

int main() {
    srand (time(0));
    int bet; // Sparar insatsen för omgången
    int balance = 1000; // Variabel för att lagra pengarna som spelaren har kvar.
    while (true) {
        if (balance < 100) { // har man under 100kr så kan man inte satsa mer och har förlorat.
            println("Du kan inte spela mer du har bara" + std::to_string(balance));
            println("Du har förlorat...");
            break;
        }
        while (true) {
            // Skriver ut hur mycket pengar man har och fortsätter tills giltigt val har gjorts.
            println("");
            println("Du har " + std::to_string(balance));
            println("Välj en insats, 100, 300 eller 500 (kr): ");
            cin.ignore();
            cin >> bet;
            if ((bet == 100 || bet == 300 || bet == 500) && bet <= balance) {
                break;
            }
        }
        balance -= bet; // Dra bort insatsen från 'kontot'

        bool color_bet = binary_choice(("Vill du satsa på en färg eller på en siffra? (f/n)"),
                                         "f", "n");
        if (color_bet) {
            // Om man väljer färgs så får man också välja vilken
            bool color = binary_choice("Vilken färg vill du satsa på? (rod/svart): ",
                                         "rod", "svart");
            if (random()%2==0 && !color || random()%2==1 && color) { // Kolla om jämnheten är rätt för färgen
                println("Vann med rätt färg");
                balance += bet*3; // Lägg till 3 gånger pengarna för man har dragit insatsen redan.
            } else {
                println(("Gissade på fel färg, korrekt färg var " + std::string(!color ? "röd" : "svart")));
            }
        } else {
            string number;
            bool allowed_selection = false;
            while (!allowed_selection) { // Loopar tills man har valt en giltig siffra mellan 1 och 36
                println("Vilken siffra gissar du på?: ");
                cin.ignore();
                cin >> number;
                allowed_selection = 1 <= std::stoi(number) && std::stoi(number) <= 36;
            }
            if (random()==std::stoi(number)) {
                println("Du vann med rätt gissade siffra!");
                balance += bet * 11; // Lägg till 11 gånger pengarna för man har dragit insatsen redan.
            } else {
                println("Du gissade på fel siffra");
            }
        }
        if (!binary_choice("Vill du spela igen (y/n): ", "y", "n")) break;
    }
    return 0;
}
