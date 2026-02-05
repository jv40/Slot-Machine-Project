#include <iostream>
#include <random>
#include <vector>

using namespace std;


std::random_device r; // We seed this?
std::default_random_engine e1{r()}; // Making random engine seeded with random device r()

class Reel
{
public:
    virtual string spin()
    {
        string reelCharChosen = reelChars[randomNumberGenerator(REEL_MIN,REEL_MAX)];
        //cout << reelCharChosen;
        return (reelCharChosen);
    }

private:
    string reelChars[10] = {
        "\u274C", "\u274C", "\u274C", "\u274C",  // X Mark        50% chance
        "\u2757", "\u2757", "\u2757",               // Exclamation   30% chance
        "\u2705", "\u2705",                            // Check Mark    20% chance
        "7"                                               // 7             10% chance
    };
    double REEL_MIN = 0;
    double REEL_MAX = 9;

    long randomNumberGenerator(double minimum, double maximum)
    {
        std::uniform_int_distribution <long> prob(minimum,maximum);
        long randomNumber = prob(e1);
        return(randomNumber);
    }
};

//Can use reel public functions but is not a reel
//Use #include reel when putting it in its own .h file
class SlotMachine
{
public:
    bool virtual checkWin() = 0; //Pure Virtual

    //void virtual displayResults() = 0;
    void displayResults()
    {
        spinReels();
        for (string& spin : reelResults)
        {
            cout << spin << " ";
        }

        cout << endl;
        if (checkWin() == true)
        {
            cout << "You Win!";
        }
        else
        {
            cout << "L, you Lost Man";
        }
    }

protected:
    vector<Reel> allReels;

    void spinReels()
    {
        reelResults.clear();
        for (auto it : allReels) // Reference it, DON'T let it make a copy of a deleted constructor
        { // Basically, always use auto&
            reelResults.push_back(it.spin());
        }
    }

    vector<string> reelResults;
    vector<string> checkingResults;
    string howBigWin;
private:
    //void virtual spinReels() = 0;
};


class ThreeReelSlotMachine: public SlotMachine
{
public:
    ThreeReelSlotMachine()
    {
        //allReels = {&a, &b, &c};

        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
    }

    bool checkWin() override
    {
        //for (auto it : reelResults)

        return (reelResults[0] == reelResults[1] &&
                reelResults[1] == reelResults[2]);
    }

private:
    Reel a, b, c;
    // vector<string> reelResults;
    // vector<Reel*> allReels = {&a, &b, &c};

};

class FourReelSlotMachine: public SlotMachine
{
public:
    FourReelSlotMachine()
    {
        //allReels = {&a, &b, &c, &d};

        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
        allReels.push_back(d);
    }

    bool checkWin() override
    {
        return (reelResults[0] == reelResults[1] &&
                reelResults[1] == reelResults[2] &&
                reelResults[2] == reelResults[3]);
    }

private:
    Reel a, b, c, d;
};

void gameLoop(SlotMachine* machine, long& credits)
{
    // Game Loop
    while (credits >= 0)
    {
        machine->displayResults();

        if (machine->checkWin())
        {
            credits += 10;
        }
        else
        {
            credits -= 1;
            //cout << "\nYou lose. -1 credit" << endl;
        }
    }
}

int main()
{
    long credits = 0;
    string numberOfReels;

    cout << "How many credits do you have?: ";
    cin >> credits;
    cout << endl;
    cout << "How many reels would you like? (3,4,5)" << endl;
    cout << "Please input an integer value: ";
    cin >> numberOfReels;

    SlotMachine* machine = nullptr;

    switch (stoi(numberOfReels))
    {
        case 3:
            machine = new ThreeReelSlotMachine;
            cout << "You have chosen a Three Reel Slot Machine." << endl;
            break;
        case 4:
            machine = new FourReelSlotMachine;
            cout << "You have chosen a Four Reel Slot Machine." << endl;
            break;



        default:
            machine = new ThreeReelSlotMachine;
            cout << "Invalid choice. Defaulting to Three Reels..." << endl;
            break;
    }

    cout << endl;

    gameLoop(machine, credits);

    delete machine;

    return 0;
}