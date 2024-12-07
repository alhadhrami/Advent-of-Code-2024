// Example program
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>

enum Direction {
    Up, Right, Down, Left
};

std::vector<std::string> inputFromFile(std::string const & fileName);
int numberOfTurns(std::vector<std::string>& grid);
std::tuple<int, int> initialPosition(std::vector<std::string> const & grid);
Direction turn(Direction const currentDirection);

int main()
{
    std::string const fileName = "part1.txt";
    std::vector<std::string> grid = inputFromFile(fileName);
    auto const answer = numberOfTurns(grid);
    std::cout << "answer: " << answer << "\n";
    return 0;
}

std::vector<std::string> inputFromFile(std::string const & fileName)
{
    std::ifstream fin(fileName);
    if (!fin.is_open())
    {
        std::cout << "Problem in opening file \"" << fileName << "\"\n";
        exit(-1);
    }

    std::vector<std::string> input;

    while (fin)
    {
        std::string line;
        std::getline(fin, line);
        input.push_back(line);
    }

    return input;
}

int numberOfTurns(std::vector<std::string>& grid)
{
    auto const [initX, initY] = initialPosition(grid);
    
    Direction currentDirection = Direction::Up;
    int currentX = initX;
    int currentY = initY;
    grid[currentX][currentY] = 'X';
    int answer = 1;

    while (0 <= currentX && currentX < grid.size() && 0 <= currentY && currentY < grid.size())
    {
        int newX = currentX;
        int newY = currentY;
        switch(currentDirection)
        {
            case Direction::Up:--newX;break;
            case Direction::Left:--newY;break;
            case Direction::Down:++newX;break;
            case Direction::Right:++newY;break;
        }
        if (newX < 0 || newX >= grid.size() || newY < 0 || newY >= grid.size())
        {
            break;
        }
        if (grid[newX][newY] == '#')
        {
            currentDirection = turn(currentDirection);
            continue;
        }
        else if (grid[newX][newY] != 'X')
        {
            grid[newX][newY] = 'X';
            ++answer;
        }
        currentX = newX;
        currentY = newY;
    }
    return answer;
}

std::tuple<int, int> initialPosition(std::vector<std::string> const & grid)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[i].size(); ++j)
        {
            if (grid[i][j] == '^')
            {
                return std::make_tuple(i, j);
            }
        }
    }
    return std::make_tuple(-1, -1);
}

Direction turn(Direction const currentDirection)
{
    switch(currentDirection)
    {
        case Direction::Up: return Direction::Right;
        case Direction::Left: return Direction::Up;
        case Direction::Down: return Direction::Left;
        case Direction::Right: return Direction::Down;
    }
    exit(-1);
}    
