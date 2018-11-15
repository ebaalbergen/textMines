#include "../include/game.h"

MinesGame::MinesGame(Vector2* gameSize, int_8 numberOfMines)
{
    this->gameSize = gameSize;
    this->numberOfMines = numberOfMines;
    
    // Set the arraySize to the number of cells in the game
    // and initiale the array for the playfield to an empty playfield
    this->arraySize = this->gameSize->x * this->gameSize->y;
    playField = new uint_8[arraySize];    
    printField = new uint_8[arraySize];
    
    // Initialise a counter to keep track of the number of fields still 
    // needed to finish the game
    numberOfFieldsLeft = arraySize - numberOfMines;
    
    //Set up the playfield
    setupPlayField();
}

bool MinesGame::nextGameStep()
{
    if(numberOfFieldsLeft<1)
    {
        std::cout << "You've won the game!"<<std::endl;
        printGame();
        return false;
    }
      
    printGame();
    
    // Get the response from the user
    std::string input;
    std::cout << std::endl;    
    
    getline(std::cin, input);
    
    // If the user want to close the program, do so now.
    if(input[0] == 'C')
    {
        std::cout << "Mines is being shut down!\n";
        return false;
    }
    
    // Get the coordinate of the user input
    Vector2 coordinate(1,2);
    try
    {
        coordinate = getCoordinate(input);
    } catch(char const* exception)
    {
        std::cout << exception << std::endl;
        return true;
    }
    
    // If the coordinate is outside the playfield, notify the user that the
    // input is invalid.
    if(not vectorInPlayField(coordinate))
    {
        std::cout << "The given input is invalid." << std::endl; 
        return true;
    }
    
    switch(input[0])
    {
        case '?':
        case 'F':
            setChar(coordinate, input[0]);
            return true;
        case 'D':
            return removeGround(coordinate);
    }
}

void MinesGame::setChar(Vector2 input, int_8 character)
{
    uint_16 location = input.y * gameSize->x + input.x;
    if(printField[location] == character)
        printField[location] = 'X';
    else if(printField[location] == 'X')
        printField[location] = character;
}

bool MinesGame::removeGround(Vector2 coordinate)
{
    uint_16 arrayIndex = coordinate.y * gameSize->x + coordinate.x;
    
    // Get the number in the field as a ascii-encoded uint_8
    uint_8 number = ((int_8)'0') + playField[arrayIndex];
    
    // If the field is not untouched, skip it.
    if(printField[arrayIndex] != 'X')
        return true;
    
    // If the field is save...
    if(number != '9')
    {
        if(printField[arrayIndex] == 'X')
            numberOfFieldsLeft--;
            
        printField[arrayIndex] = number == '0'? ' ': number;
        // If there is no mine in any of the neighbouring cells, remove also 
        // those cells.
        if(number == '0')
        {
            for(int_8 x = coordinate.x - 1; x <= coordinate.x + 1; x++)
            {
                for(int_8 y = coordinate.y - 1; y <= coordinate.y + 1; y++)
                {
                    Vector2 field = Vector2(x,y);
                    if(vectorInPlayField(field))
                        removeGround(field);
                }
            }
        }
        return true;
    }
    // You're dead.
    else
    {
        std::cout << "Game Over!" << std::endl;
        return false;
    }
}

Vector2 MinesGame::getCoordinate(std::string input)
{
    uint_8 xValue = 0, yValue = 0;
    bool commaSeen = false;
    
    for(int_8 c : input) 
    {
        // The point and comma will be handled seperatly.
        if(c != ',' && c != '.')
        {
            // let's test if the char is a number so we won't interpret bullshit.
            if (c == '1' ||
                c == '2' ||
                c == '3' ||
                c == '4' ||
                c == '5' ||
                c == '6' ||
                c == '7' ||
                c == '8' ||
                c == '9' ||
                c == '0')
            {
                // Shift the number and add the new number to the end
                if(commaSeen)
                {
                    yValue *= 10;
                    yValue += c-48;
                }
                else
                {
                    xValue *= 10;
                    xValue += c-48;
                }
            }
        } else
        {
            // Now use the other variable.
            commaSeen = true;
        }
    }
    
    // If one of the values is not set and the coordinate was not in a valid 
    // format return an exception.
    if (xValue == 0 || yValue == 0)
        throw "Invalid input!";
        
    return Vector2(xValue - 1, yValue - 1);
}

void MinesGame::setupPlayField()
{
    // Setup a completely new playingfield without bomb and with only crosses
    for(uint_16 i = 0; i < arraySize; i++)
    {
        playField[i] = 0;
        printField[i] = 'X';
    }

    // Set numberOfMines number of fields to 9 to indicate that those are bombs.
    for(uint_8 i = 0; i < numberOfMines; i++)
    {
        RandomGenerator random = RandomGenerator();
        //uint_16 location = i * 9;
        uint_16 location = random.getNumber(gameSize->y) * gameSize->x + random.getNumber(gameSize->x);

        // If there is allready a bomb on that location, let's try again!
        if(playField[location] == 9)
            i--;
        // If there isn't a bomb on the location, let's use the location!
        else
            playField[location] = 9;    
    }

    // Set all the other fields with the number corresponding to the number of
    // bombs around them.
    for(uint_8 yCor = 0; yCor < gameSize->y; yCor++)
    {
        for(uint_8 xCor = 0; xCor < gameSize->x; xCor++)
        {
            uint_16 location = yCor * gameSize->x + xCor;

            // If the field already has a bomb inside, jump to the next field
            if(playField[location] == 9)
                continue;

            uint_8 bombCount = 0;

            for(int_8 x = xCor - 1; x <= xCor + 1; x++)
            {
                for(int_8 y = yCor - 1; y <= yCor + 1; y++)
                {
                    uint_16 locationA = y * gameSize->x + x;
                    if(x < 0 || y < 0 || x >= gameSize->x || y >= gameSize->y)
                        continue;
                    if(playField[locationA] == 9)
                        bombCount++;
                }
            }

            playField[location] = bombCount;
        }
    }
}

void MinesGame::printGame()
{
    for(uint_8 yCor = 0; yCor < gameSize->y; yCor++)
    {
        for(uint_8 xCor = 0; xCor < gameSize->x; xCor++)
        {
            std::cout << printField[yCor*gameSize->x + xCor];
        }
        std::cout << std::endl;
    }
}

bool MinesGame::vectorInPlayField(Vector2 vector)
{
    return vector.x >= 0 && vector.y >= 0 && vector.x < gameSize->x && vector.y < gameSize->y;
}


