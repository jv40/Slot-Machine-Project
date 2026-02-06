#include <iostream>
#include <random>
#include <vector>

using namespace std;

std::random_device r; // We seed this?
std::default_random_engine e1{r()}; // Making random engine seeded with random device r()

class Reel
{
public:
    //======================== Spin (a single reel) ==========================
    /*
     * PRE:     0 <= REEL_MIN < REEL_MAX
     * POST:    random number between REEL_MIN and REEL_MAX generated
     * RETURN:  reelCharChosen (the random character that was spun)
     */
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

    //======================== Generate Random Number ==========================
    /*
     * PRE:     0 <= minimum < maximum
     * POST:    random number between minimum and maximum generated
     * RETURN:  long randomNumber
     */
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
    short addPoints;

    //======================== Virtual Destructor ==========================
    /*
     * PRE:     SlotMachine object exists
     * POST:    each derived object and associated memory gets deleted
     * RETURN:  n/a
     */
    virtual ~SlotMachine()
    {
        // EXTREMELY Important, without this then I get a memory leak because delete machine only deletes the slot
        // machine object and nothing that comes with the derived objects like Reel a, b, and c
    }

    //======================== Check Win ==========================
    /*
     * PRE:     reelResults vector populated with spin results
     * POST:    determines if the player has won or not and which symbol the player has won with
     * RETURN:  bool (true if the player has won, false if the player has lost); howBigWin gets set to the winning symbol
     */
    bool checkWin()
    {
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

    //======================== Payout (Pure Virtual) ==========================
    /*
     * PRE:     derived class has to implement this
     * POST:    calculates payout based on the winning symbol and number of reels
     * RETURN:  addPoints is set to the amount of points that should be won for a given winning symbol
     */
    void virtual payout() = 0; // Pure Virtual

    //======================== Display Results ==========================
    /*
     * PRE:     allReels vector populated with Reel objects
     * POST:    spins all reels, displays results, shows win/loss message
     * RETURN:  n/a
     */
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
        cout << endl;
    }

protected:
    vector<Reel> allReels; //Vector of Reel objects to store a slot machine's reels
    vector<string> reelResults; //Vector of strings to store the symbols of each spin

    //The following are all vectors used to track how many of each symbol appear on a given reel
    vector<char> redXMatches;
    vector<char> exclamationMatches;
    vector<char> checkMarkMatches;
    vector<char> sevenMatches;

    string howBigWin; //Stores a string of what particular symbol got 3 or more matches on a given spin of a slot machine

    //======================== Spin Reels ==========================
    /*
     * PRE:     allReels vector populated with Reel objects
     * POST:    all reels spun, results stored, number of matching symbols calculated, payout calculated
     * RETURN:  n/a
     */
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
};


class ThreeReelSlotMachine: public SlotMachine
{
public:

    //======================== Three Reel Constructor ==========================
    /*
     * PRE:     n/a
     * POST:    ThreeReelSlotMachine created with 3 reels added to allReels vector
     * RETURN:  n/a
     */
    ThreeReelSlotMachine()
    {
        //allReels = {&a, &b, &c};
        //SUPER cursed C++ way of adding things to a vector. Never do this again.

        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
    }

    //======================== Payout (Three Reels) ==========================
    /*
     * PRE:     n/a
     * POST:    calculates payout based on the winning symbol and number of reels,
     *          addPoints is set to the amount of points that should be won for a given winning symbol
     * RETURN:  n/a
     */
    void payout() override // I just think override sounds pretty cool
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
            addPoints = 40;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 50;
        }
    }

private:
    Reel a, b, c; //Instantiate reels used for slot machine
};

class FourReelSlotMachine: public SlotMachine
{
public:

    //======================== Four Reel Constructor ==========================
    /*
     * PRE:     n/a
     * POST:    FourReelSlotMachine created with 4 reels added to allReels vector
     * RETURN:  n/a
     */
    FourReelSlotMachine()
    {
        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
        allReels.push_back(d);
    }

    //======================== Payout (Four Reels) ==========================
    /*
     * PRE:     n/a
     * POST:    calculates payout based on the winning symbol and number of reels,
     *          addPoints is set to the amount of points that should be won for a given winning symbol
     * RETURN:  n/a
     */
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
            addPoints = 20;
        }
        else if (checkMarkMatches.size() >= 3)
        {
            addPoints = 30;
        }
        else if (sevenMatches.size() >= 3)
        {
            addPoints = 40;
        }
    }
    //It was at this point I realized I didn't calculate an actual "JACKPOT" amount...
    //I would basically just add a lot more to this if-else ladder to achieve the proper logic

private:
    Reel a, b, c, d; //Instantiate reels used for slot machine
};

class FiveReelSlotMachine: public SlotMachine
{
public:

    //======================== Five Reel Constructor ==========================
    /*
     * PRE:     n/a
     * POST:    FiveReelSlotMachine created with 5 reels added to allReels vector
     * RETURN:  n/a
     */
    FiveReelSlotMachine()
    {
        allReels.push_back(a);
        allReels.push_back(b);
        allReels.push_back(c);
        allReels.push_back(d);
        allReels.push_back(e);
    }

    //======================== Payout (Five Reels) ==========================
    /*
     * PRE:     n/a
     * POST:    calculates payout based on the winning symbol and number of reels,
     *          addPoints is set to the amount of points that should be won for a given winning symbol
     * RETURN:  n/a
     */
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
            addPoints = 20;
        }
        else if (sevenMatches.size() >= 3)
        {
            addPoints = 30;
        }
    }

private:
    Reel a, b, c, d, e; //Instantiate reels used for slot machine
};

//======================== Game Loop ==========================
/*
 * PRE:     SlotMachine pointer pointing to SlotMachine derived object, credits > 0, spinAgain = true
 * POST:    game played until credits run out or player chooses to stop, credits modified based on winning and losing,
 *          spinAgain modified through player input
 * RETURN:  n/a
 */
void gameLoop(SlotMachine* machine, long& credits, bool& spinAgain)
{
    string enteredString; //User-inputted string to store whether or not the user wants to play again

    // Game Loop
    while (credits > 0 && spinAgain == true)
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

        cout << "Credits: " << credits << endl << endl;
        cout << "Spin again? ('y' for yes, 'n' for no):";
        cin >> enteredString;
        if (not (enteredString == "y" || enteredString == "ye" || enteredString == "yes"))
        {
            spinAgain = false;
        }
        cout << "__________________________________" << endl << endl;
    }

    cout << "==================================" << endl;
    cout << "You've run out of credits!" << endl << "Restart the program to play again.";
}

//======================== Main ==========================
/*
 * PRE:     n/a
 * POST:    my code runs! you make a slot machine and set how many reels and how many credits you have, and you start
 *          gambling!
 * RETURN:  0
 */
int main()
{
    long credits = 0; //User-inputted amount of credits to be added to and detrimented based upon winnings during runtime
    string numberOfReels; //User-inputted amount of reels to create a slot machine with
    bool spinAgain = true; //User-inputted value of whether they want to continue playing or not

    cout << "How many credits do you have?: ";
    cin >> credits;
    cout << endl;
    cout << "How many reels would you like? (3,4,5)" << endl;
    cout << "Please input an integer value: ";
    cin >> numberOfReels;

    SlotMachine* machine = nullptr; //SlotMachine object pointer created before user prompt creates derived SlotMachine object

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
        case 5:
            machine = new FiveReelSlotMachine;
            cout << "You have chosen a Five Reel Slot Machine." << endl;
            break;
        default:
            machine = new ThreeReelSlotMachine;
            cout << "Invalid choice. Defaulting to Three Reels..." << endl;
            break;
    }

    cout << endl;

    gameLoop(machine, credits, spinAgain);

    delete machine; //Freeing up allocated memory to prevent memory leaks
    //I was lowkey plagued by memory leaks during this assignment

    return 0;
}