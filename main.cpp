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
        "\u274C", "\u274C", "\u274C", "\u274C",  // Red X         50% chance
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
    virtual ~SlotMachine()
    {
        // EXTREMELY Important, without this then I get a memory leak because delete machine only deletes the slot
        // machine object and nothing that comes with the derived objects like Reel a, b, and c
    };
    short addPoints;

    bool checkWin()
    {
        //for (auto it : reelResults)

        // return (reelResults[0] == reelResults[1] &&
        //         reelResults[1] == reelResults[2]);

        if (redXMatches.size() >= 3)
        {
            howBigWin = "red_x";
            return (true);
        }
        else if (exclamationMatches.size() >= 3)
        {
            howBigWin = "exclamation_mark";
            return (true);
        }
        else if (checkMarkMatches.size() >= 3)
        {
            howBigWin = "check_mark";
            return (true);
        }
        else if (sevenMatches.size() >= 3)
        {
            howBigWin = "7";
            return (true);
        }

        return(false);
    }
    void virtual payout() = 0; // Pure Virtual

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

        redXMatches.clear();
        exclamationMatches.clear();
        checkMarkMatches.clear();
        sevenMatches.clear();

        for (auto& it : allReels) // Reference it, DON'T let it make a copy of a deleted constructor
        { // Basically, always use auto&
            reelResults.push_back(it.spin());
        }

        for (auto& spin : reelResults)
        {
            if (spin == "\u274C")
            {
                redXMatches.push_back('0');
            }
            else if (spin == "\u2757")
            {
                exclamationMatches.push_back('0');
            }
            else if (spin == "\u2705")
            {
                checkMarkMatches.push_back('0');
            }
            else if (spin == "7")
            {
                sevenMatches.push_back('0');
            }
        }

        payout();
    }

    vector<string> reelResults;

    vector<char> redXMatches;
    vector<char> exclamationMatches;
    vector<char> checkMarkMatches;
    vector<char> sevenMatches;

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
        //SUPER cursed C++ way of adding things to a vector. Never do this again.

        allReels.reserve(5);
        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
    }

    void payout() override // I just think override sounds pretty cool
    {
        addPoints = 0;

        if (redXMatches.size() >= 3)
        {
            addPoints = 3;
        }
        else if (exclamationMatches.size() >= 3)
        {
            addPoints = 5;
        }
        else if (exclamationMatches.size() >= 3)
        {
            addPoints = 10;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 20;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 30;
        }
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

        allReels.reserve(5);
        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
        allReels.push_back(d);
    }

    void payout() override
    {
        addPoints = 0;

        if (redXMatches.size() >= 3)
        {
            addPoints = 5;
        }
        else if (exclamationMatches.size() >= 3)
        {
            addPoints = 10;
        }
        else if (exclamationMatches.size() >= 3)
        {
            addPoints = 15;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 30;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 50;
        }
    }

private:
    Reel a, b, c, d;
};

void gameLoop(SlotMachine* machine, long& credits)
{
    // Game Loop
    while (credits > 0)
    {
        machine->displayResults();

        if (machine->checkWin())
        {
            credits += machine -> addPoints;
        }
        else
        {
            credits -= 5;
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