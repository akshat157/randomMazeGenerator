/********************************************************
 * 
 * Author: Akshat Malviya (@akshat157)
 * Date: Sunday, June 07
 * Desc: A random maze generator using backtracking!
 * 
*********************************************************/

#include <iostream>
#include <stack>
#include <vector>
#include <random>
using namespace std;

// Default values
int m = 4, n = 4;

void displayMaze(int M, int N, char** maze) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
                cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

// A utility function to get the index of cell with indices x, y;
int getIdx(int x, int y, vector < pair<int, pair<int, int> > > cell_list) {   
    for (int i = 0; i < cell_list.size(); i++)
    {
        if (cell_list[i].second.first == x && cell_list[i].second.second == y)
            return cell_list[i].first;
    }
    cout << "getIdx() couldn't find the index!" << endl;
    return -1;
}

void createMaze(int M, int N, char** maze) {

    vector < pair<int, pair<int, int> > > cell_list;
    vector <bool> visited(m*n, false);
    int nVisited = 0;
    int k = 0;

    for (int i = 1; i < M; i+=2) {
        for (int j = 1; j < N; j+=2) {
            cell_list.push_back(make_pair(k, make_pair(i, j)));
            k++;
        }
    }

    stack<pair<int, pair<int, int> > > m_stack;

    m_stack.push(cell_list[0]);

    visited[0] = true;
    nVisited++;
    
    random_device rdev;
    mt19937 rng(rdev());
    uniform_int_distribution<mt19937::result_type> dist20(1, 20);

    // Algo
    while(nVisited < m*n) {

        vector <int> neighbours;
        // North
        if (m_stack.top().second.first > 1) {
            if (maze[m_stack.top().second.first - 2][m_stack.top().second.second + 0] && 
                !visited[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(0);
            }
        }
        // East
        if (m_stack.top().second.second < N - 2) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second + 2] && 
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2, cell_list)]) { 
                neighbours.push_back(1);
            }
        }
        // South
        if (m_stack.top().second.first < M - 2) {
            if (maze[m_stack.top().second.first + 2][m_stack.top().second.second + 0] && 
                !visited[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0, cell_list)]) {
                neighbours.push_back(2);
            }
        }
        // West
        if (m_stack.top().second.second > 1) {
            if (maze[m_stack.top().second.first + 0][m_stack.top().second.second - 2] && 
                !visited[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2, cell_list)]) {
                neighbours.push_back(3);
            }
        }
        // Neighbours available?
        if (!neighbours.empty()) {
            // Choose a random direction
            int next_cell_dir = neighbours[dist20(rng) % neighbours.size()];
            // Create a path between this cell and neighbour
            switch (next_cell_dir) {
                case 0: // North
                    maze[m_stack.top().second.first - 1][m_stack.top().second.second + 0] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first - 2, m_stack.top().second.second + 0, cell_list)]);
                    break;
                case 1: // East
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second + 1] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second + 2, cell_list)]);
                    break;
                case 2: // South
                    maze[m_stack.top().second.first + 1][m_stack.top().second.second + 0] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 2, m_stack.top().second.second + 0, cell_list)]);                
                    break;
                case 3: // West
                    maze[m_stack.top().second.first + 0][m_stack.top().second.second - 1] = ' ';
                    m_stack.push(cell_list[getIdx(m_stack.top().second.first + 0, m_stack.top().second.second - 2, cell_list)]);               
                    break;
            }

            visited[m_stack.top().first] = true;
            nVisited++;
        }
        else {
            m_stack.pop();
        }
    }
}

int main(int argc, char const *argv[]) {
    cout << "Random Maze Generator!" << endl;
    cout << "Enter the order of maze you want (rows (> 1) x cols (> 1)): ";
    cin >> m >> n;
    while (m < 1 || n < 1) {
        cout << "Desired dimensions impossible. Re-enter pls." << endl;
        cin >> m >> n;
    }
    int M = 2*m+1;
    int N = 2*n+1;
    char **maze;
    maze = new char* [M];

    for (int i = 0; i < M; i++) {
        maze[i] = new char [N];
    }
    
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (!(i&1)||!(j&1))
                maze[i][j] = '#';
            else
                maze[i][j] = ' ';

        }
    }

    for (int i = 1; i < M; i+=2) {
        for (int j = 1; j < N; j+=2) {
            maze[i][j] = ' ';
        }

    }
    createMaze(M, N, maze);
    maze[0][1] = 'S';
    maze[2*m][2*n-1] = 'E';
    cout << "Here's the maze you asked for. Enjoy! :D" << endl;
    displayMaze(M, N, maze);
    
    return 0;
}
