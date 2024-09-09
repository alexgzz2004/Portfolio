/* CSCI 200: Assignment 6: A6 - SFML: Maze Runner
 *
 * Author: Alejandro Gonzalez
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * The program uses data from external files to create and solve mazes
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

struct Cell {
    int row;
    int col;
};

void BFS(char** maze, int rows, int cols, int startRow, int startCol, vector<vector<bool>>& visited, RenderWindow& window, RectangleShape& box, int size) 
{
    //Creates queue q for pairs of rows and columns
    queue<pair<int, int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;
    //Allows for movement up and down
    int dr[] = {0, 0, 1, -1};
    //Allows for movement left to right
    int dc[] = {1, -1, 0, 0};
    while (!q.empty()) 
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        window.clear();
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                box.setPosition(j * size, i * size);
                //Checks if the end has been reached
                if (visited[i][j] && maze[i][j] == 'E'){
                    return;
                }
                if (maze[i][j] == '#') 
                {
                    box.setFillColor(Color::Black);
                } 
                else if (maze[i][j] == '.') 
                {
                    box.setFillColor(Color::White);
                } 
                else if (maze[i][j] == 'S') 
                {
                    box.setFillColor(Color::Green);
                } 
                else if (maze[i][j] == 'E') 
                {
                    box.setFillColor(Color::Red);
                }
                if (visited[i][j] && maze[i][j] != 'S' && maze[i][j] != 'E') 
                {
                    box.setFillColor(Color::Magenta); 
                }
                window.draw(box);
                
            }
            sleep(milliseconds(50));
        }
        
        window.display();
        
        for (int i = 0; i < 4; ++i) 
        {
            int nextRow = row + dr[i];
            int nextCol = col + dc[i];
            //Checks if cell can be explored
            if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols &&
                maze[nextRow][nextCol] != '#' && !visited[nextRow][nextCol]) 
            {
                q.push({nextRow, nextCol});
                visited[nextRow][nextCol] = true;
                if (maze[nextRow][nextCol] == 'E') 
                {
                    cout << "End reached!" << endl;
                    // Empty list of nodes to halt search
                    while (!q.empty()) 
                    {
                        q.pop();
                    }
                    break;
                }
            }
        }
    }
    
}

void DFS(char** maze, int rows, int cols, int startRow, int startCol, vector<vector<bool>>& visited, RenderWindow& window, RectangleShape& box, int size) 
{
    //Allows for movement up and down
    int dr[] = {0, 0, 1, -1};
    //Allows for movement left and right
    int dc[] = {1, -1, 0, 0};
    
    visited[startRow][startCol] = true;
    for (int i = 0; i < 4; ++i) 
    {
        //Changes row and column
        int newRow = startRow + dr[i];
        int newCol = startCol + dc[i];
        //Checks to if cell can be explored
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && maze[newRow][newCol] != '#' && !visited[newRow][newCol]) 
        {
            visited[newRow][newCol] = true;
            window.clear();
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    box.setPosition(j * size, i * size);
                    //Check to see if end has been reached
                    if (visited[i][j] && maze[i][j] == 'E')
                    {
                        return;
                    }
                    if (maze[i][j] == '#') 
                    {
                        box.setFillColor(Color::Black);
                    } 
                    else if (maze[i][j] == '.') 
                    {
                        box.setFillColor(Color::White);
                    } 
                    else if (maze[i][j] == 'S') 
                    {
                        box.setFillColor(Color::Green);
                    } 
                    else if (maze[i][j] == 'E') 
                    {
                        box.setFillColor(Color::Red);
                    }
                    if (visited[i][j] && maze[i][j] != 'S' && maze[i][j] != 'E') 
                    {
                        box.setFillColor(Color::Magenta); 
                    }
                    window.draw(box);
                }
            }
            window.display();
            sleep(milliseconds(100));
            DFS(maze, rows, cols, newRow, newCol, visited, window, box, size);
        }
    }
}

int main(){
    
    string filename;
    int choice;
    cout << "Enter a filename: "; cin >> filename;
    cout << "Would you like to use BFS or DFS (1 = BFS | 2 = DFS): "; cin >> choice;

    ifstream file(filename);
    if (!file.is_open()) 
    {
        cout << "File not found!" << endl;
        return EXIT_FAILURE;
    }

    //Initializes the size of maze
    int rows, cols;
    file >> rows >> cols;
    
    char** maze = new char*[rows];
    for (int i = 0; i < rows; i++) 
    {
        maze[i] = new char[cols];
        for (int j = 0; j < cols; j++) 
        {
            file >> maze[i][j];
        }
    }
    file.close();
   
   const int size = 15;
   const int width = cols * size;
   const int height = rows * size;

   //Open window based on maze 
   RenderWindow window(VideoMode(width, height), "Maze");
   RectangleShape box;
   box.setSize(Vector2f(size, size));

    int startRow, startCol;
    bool startFound = false;

    // Find the start position
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (maze[i][j] == 'S') 
            {
                startRow = i;
                startCol = j;
                startFound = true;
                break;
            }
        }
        if (startFound) 
        {
            break;
        }
    }
    if (!startFound) 
    {
        cout << "Start point not found in maze!" << endl;
        return EXIT_FAILURE;
    }

    //Vector of visited cells
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    while (window.isOpen())
    {
        //Close window with Q or escape
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Q || event.key.code == Keyboard::Escape)) 
            {
                window.close();
            }
        }
        
        //BFS or DFS search based on users choice
        if (choice ==1)
        {
            BFS(maze, rows, cols, startRow, startCol, visited, window, box, size);
        }
        else if (choice == 2)
        {
            DFS(maze, rows, cols, startRow, startCol, visited, window, box, size);
        }
        else
        {
            cout << "Invalid Number" << endl;
        }
        
    }
   
    for(int i = 0;i<rows;++i)
    {
        delete[] maze[i];
    }
    delete[] maze;
    return 0;
}