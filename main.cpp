#include <iostream>
#include <random>
using namespace std;

class Reel
{
public:
    virtual char spin()
    {
        char reelCharChosen = reelCharArray[randomNumberGenerator(REEL_MIN,REEL_MAX)];
        cout << reelCharChosen;
        return (reelCharChosen);
    }

private:
    char reelCharArray[10] = {'0','1','2','3','4','5','6','7','=', '@'};
    double REEL_MIN = 0;
    double REEL_MAX = 9;

    long randomNumberGenerator(double minimum, double maximum)
    {
        std::random_device r; // We seed this?
        std::default_random_engine e1(r()); // Making random engine seeded with random device r()

        std::uniform_int_distribution <long> prob(minimum,maximum);
        long randomNumber = prob(e1);
        return(randomNumber);
    }
};

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Reel A;
    A.spin();
    return 0;
}