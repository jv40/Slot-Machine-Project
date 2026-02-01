#include <iostream>
#include <random>
using namespace std;

class Reel
{
public:
    virtual string spin()
    {
        string reelCharChosen = reelChars[randomNumberGenerator(REEL_MIN,REEL_MAX)];
        cout << reelCharChosen;
        return (reelCharChosen);
    }

private:
    string reelChars[10] = {
        "\u274C", "\u274C", "\u274C", "\u274C",  // 50% chance
        "\u2757", "\u2757", "\u2757",               // 30% chance
        "\u2705", "\u2705",                            // 20% chance
        "7"                                               // 10% chance
    };
    double REEL_MIN = 0;
    double REEL_MAX = 9;

    std::random_device r; // We seed this?
    std::default_random_engine e1{r()}; // Making random engine seeded with random device r()

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
    bool virtual checkWin();
};

class ThreeReelSlotMachine: public SlotMachine
{
public:
    bool checkWin() override
    {
        //
    }

private:
    //
};

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Reel A;
    A.spin();
    return 0;
}