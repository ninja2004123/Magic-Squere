#include <bits/stdc++.h>

#define MSUM 15
#define N 3

using namespace std;

// Function Prototypes
int formingMagicSquare(vector<vector<int>> s);
bool SolveMagicSquere(vector<vector<int>> &Squere, int row, int col);
bool isSafe(vector<vector<int>> &grid, int row, int col, int num);
bool IsSolved(vector<vector<int>> &grid);
vector<vector<int>> Mirrored(vector<vector<int>> Squere);




// Complete the formingMagicSquare function below.
int formingMagicSquare(vector<vector<int>> s) {
    vector<vector<vector<int>>> AllMagicSqueres;

    std::cout << endl << endl;


    // Calculates the 4 possible magic squeres(uses the rule that
    // the corner must have an even number)
    for (int i = 2; i < 10; i+=2){
        vector<vector<int>> Squere = {{i, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        if (SolveMagicSquere(Squere, 0, 1));
            AllMagicSqueres.push_back(Squere);

    }

    

    // Reverse All the Possabilities so it adds the mirror 
    // Magic squeres too
    for (int i = 0, n = AllMagicSqueres.size(); i < n; i++)
        AllMagicSqueres.push_back(Mirrored(AllMagicSqueres[i]));
    

    // Printes them(This is a debug for me to see if it worked)
    for (int i = 0; i < AllMagicSqueres.size(); i++){
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++)
                std::cout << AllMagicSqueres[i][j][k] << " ";
            std::cout << endl;
        }
        std::cout << endl;
    }


    // Compares the User Given Magic Squere to all of the existing ones
    int ans = 100;
    for (int k = 0; k < AllMagicSqueres.size(); k++){
        int tmp = 0;

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                tmp += abs(s[i][j] - AllMagicSqueres[k][i][j]);
         
        ans = min(ans, tmp);
    }


    cout << ans << endl;
    return ans;
}


bool SolveMagicSquere(vector<vector<int>> &Squere, int row, int col){
    // Break case
    if (row == N-1 && col == N)
        return IsSolved(Squere);    // This is also used to backtrace
    

    // moves to the next row
    if (col == N){
        row++;
        col = 0;
    }


    // Checks possible numbers a squere at (row, col) can have
    for (int i = 1; i < 10; i++){

        // if It's safe to put the number in
        if (isSafe(Squere, row, col, i)){
            
            Squere[row][col] = i;

            if (SolveMagicSquere(Squere, row, col+1))
                return true;
        }

        // Changes it's mistake if the number is not valid
        // We need this so the ifSafe can work properly
        Squere[row][col] = 0;
    }

    // Backtracing
    return false;
}


bool isSafe(vector<vector<int>> &grid, int row, int col, int num){
   
    // Checks if the sum of that row with that num is > then 15
    int SumOfRow = 0;
    for (int i = 0; i <= col; i++)
        SumOfRow += grid[row][i];

    if (SumOfRow + num > MSUM)
        return false;


    // Checks if the sum of the columns + the new number is > then 15 
    int SumOfCols = 0;
    for (int i = 0; i <= row; i++)
        SumOfCols += grid[i][col];

    if (SumOfCols + num > MSUM)
        return false;

    
    // Checks if the number is repeated
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == num)
                return false;


    return true;    
}



bool IsSolved(vector<vector<int>> &grid){
    
    // Checks if the all sums of rows and cols is = 15
    for (int i = 0; i < N; i++){
        int RowSum = 0;
        int ColSum = 0;
        
        for (int j = 0; j < N; j++){
            RowSum += grid[j][i];
            ColSum += grid[i][j];
        }

        if (RowSum != MSUM || ColSum != MSUM)
            return false;
    }


    // Checks if the sum of the \ diagonal is = 15
    int LeftToRightSum = 0;
    for (int i = 0, j = 0; i < N && j < N; i++, j++)
        LeftToRightSum += grid[i][j];

    if (LeftToRightSum != MSUM)
        return false;


    // Checks if the sum of the / diagonal is = 15
    int RightToLeftSum = 0;
    for (int i = N-1, j = 0; i >= 0 && j < N; i--, j++)
        RightToLeftSum += grid[i][j];

    if (RightToLeftSum != MSUM)
        return false;


    return true;
}



// Mirrors the given magic squere
vector<vector<int>> Mirrored(vector<vector<int>> Squere){
    swap(Squere[0][1], Squere[1][0]);
    swap(Squere[0][2], Squere[2][0]);
    swap(Squere[1][2], Squere[2][1]);


    return Squere;
}




int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);
    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> s[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = formingMagicSquare(s);

    fout << result << "\n";

    fout.close();

    return 0;
}

