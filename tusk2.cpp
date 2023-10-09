#include <iostream>
#include <exception>
#include <vector>

using namespace std;

class Fishing : public exception {
public:
    const char* what() const noexcept override
    {
        return "Congratulatios! you found a fish!";
    }
};

class Booting : public exception {
public:
    const char* what() const noexcept override
    {
        return "Game over! you found a boot =(";
    }
};


class Fish {};

class Boot {};

class Field {
public:
    Fish* fish = nullptr;
    Boot* boot = nullptr;
};

int main() {
    srand(time(nullptr));
    Field sector[9];
    sector[rand() % 9].fish = new Fish();

    int bootCount = 0;
    while ( bootCount < 3)
    {
        int random = rand() % 9;
        if (sector[random].fish == nullptr &&
            sector[random].boot == nullptr)
        {
            sector[random].boot = new Boot();
            bootCount++;
        }   
    }

    int tries = 0;
    int respect = 0;
    while (true)
    {
        try {
            int choice;
            cout << "Input number (from 0 to 8): ";
            cin >> choice;
            if (choice >= 0 && choice < 9) respect++;
            else
            throw invalid_argument("WRONG NUMBER YOU NIGGER");
            try
            {
                if (sector[choice].fish != nullptr)
                {
                    delete sector[choice].fish;
                    throw Fishing();
                }
                else if (sector[choice].boot != nullptr)
                {
                    delete sector[choice].boot;
                    throw Booting();
                }
                else
                {
                    std::cout << "Try again!" << std::endl;
                }
            }
            catch (const Fishing& x)
            {
                cerr << x.what() << "Tries: " << tries << endl;
                break;
            }
            catch (const Booting& x)
            {
                cerr << x.what() << "Tries: " << tries << endl;
                break;
            }
        }
        catch (const invalid_argument& x)
        {
            cerr << x.what() << endl;
        }

        tries++;
    }
}