/*
Date: 9.30.26
Author: Ana Gonzalez Yuil
Lab: 5
Sources:https://www.geeksforgeeks.org/python/python-program-multiply-two-matrices/, used for inspiration for matrix mult
Description: matrix operations, reading from a file
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// prints matrix using nested for loop. matrix is passed by value (uses a copy), assumes matrix is n x n
int print_matrix(vector<vector<int>> m)
{
    int dim = m.size(); //matrix dimensions
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {   
            cout << m.at(i).at(j) << "  ";
        }
        cout << "\n";
    }

    return 0;
}

// adds two matricies, matricies are passed by value (copy), assumes matricies are nxn, returns sum matrix
vector<vector<int>> add_matrix(vector<vector<int>> matA,vector<vector<int>> matB)
{
    vector<vector<int>> result; //output
    vector<int> row;
    int dim = matA.size();//matrix dimensions
    int matA_num;
    int matB_num;

    for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {   
                matA_num = matA.at(i).at(j); //element ij in matrixA
                matB_num = matB.at(i).at(j); //element ij in matrixB

                row.push_back(matA_num + matB_num); //sum and ad to temp row
            }

            result.push_back(row);
            row.clear(); // clear row for reuse
        }


    return result;
}

// multiplies two matricies, matrix is passed by value, assumes nxn, returns product matrix
vector<vector<int>> mult_matrix(vector<vector<int>> matA,vector<vector<int>> matB)
{
    vector<vector<int>> result;
    vector<int> row;
    int element = 0;

    int dim = matA.size();
    int matA_num;
    int matB_num;
    int temp_num;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            for (int k = 0; k < dim; k++)
            {
                matA_num = matA.at(i).at(k);
                matB_num = matB.at(k).at(j);

                temp_num = matA_num * matB_num;
                element += temp_num;

            }
            row.push_back(element);
            element = 0;
        }
        result.push_back(row);
        row.clear();
    }

    return result;
}

//sums the primary and secondary diagonals of a matrix, nxn, return vector containing primary and secondary
vector<int> sum_diagonal(vector<vector<int>> m)
{
    vector<int> output; //holds main and secondary diagonal
    int main =0 ; //main diagonal
    int secondary=0; // secondary diagonal
    int dim = m.size(); //dimensions

    for (int i = 0; i < dim; i++)
    {
        main += m.at(i).at(i);
        secondary += m.at(i).at(dim-1-i);
    }
    output.push_back(main);
    output.push_back(secondary);
    return output;
}

//swaps two rows of a matrix, matrix is passed by reference, returns bool to determine if matrix is printed
bool swap_rows(vector<vector<int>> &m, int rowA, int rowB)
{
    int dim = m.size() - 1; //-1 for indexing 
    rowA --;
    rowB --;

    if (rowA < 0 || rowA > dim || rowB < 0 || rowB > dim)
    {
        cout << "Selected row(s) out of bounds.\n";
        return false;
    }
    else{
        m.at(rowA).swap(m.at(rowB));
        return true;
    }
}

//swaps two columns of matrix, matrix is passed by reference, returns bool to determine if matrix is printed
bool swap_cols(vector<vector<int>> &m, int colA, int colB)
{
    int tempA = 0; //holds element to be swapped
    int tempB = 0; //holds element to be swapped

    int dim = m.size() - 1; //-1 for indexing 
    colA --;
    colB --;

    if (colA < 0 || colA > dim || colB < 0 || colB > dim)
    {
        cout << "Selected column(s) out of bounds.\n";
        return false;
    }
    else{
        for (int i = 0; i < dim+1; i++)
        {
            tempA = m.at(i).at(colA); //gets elements of colA
            tempB = m.at(i).at(colB); //gets elements of colB

            m.at(i).at(colA) = tempB;
            m.at(i).at(colB) = tempA;

        }
        return true;
    }
}

//updates a matrix element, matrix is passed by reference, returns bool to determine if matrix is printed
bool update_element(vector<vector<int>> &m, int row, int col, int value)
{
    int dim = m.size() -1;
    row --;
    col--;
    if (row < 0 || row > dim || col < 0 || col > dim)
    {
        cout << "Selected coordinates out of bounds.\n";
        return false;
    }
    else{
        m.at(row).at(col) = value;
        return true;
    }

}


int main()
{
    vector <string> fileRaw;
    
    //prompt user for filename
    string userFile;
    cout << "Enter input filename: ";
    cin >> userFile;
    
    string line;
    ifstream myFile(userFile);
    
    //open and read file
    if (myFile.is_open())
    {
        while ( getline(myFile,line) )
        {
            fileRaw.push_back(line); //push file contents into unorganized vector
        }
        myFile.close();
    }
    else
    {
        cout << "unable to open file.";
    }
    
    int dim = stoi(fileRaw[0]);// initialize matrix dimensions
    
    //matrix1 and matrix2 implemented as 2d vectors
    vector <vector<int>> matrix1;
    vector <vector<int>> matrix2;
    cout << "\n";
    vector <int> row;// used to create rows for matricies
    string element; //holds row element before converting to int
    int elementINT; //holds row element after converting to int

    //create matrix1 and matrix2
    // (probably doesnt work with negative values)
    for (int i = 1; i <= dim * 2; i++)
    {
        string temp = fileRaw.at(i).c_str(); //hold row of text
        temp.insert(temp.begin(),'_'); //makes it so that there is one unwanted character in front of each wanted number, makes it easier to clean/get desired part of string
        // cout << temp << "\n"; //test

        //create row
        for (int j = 0; j < temp.length()-2; j = j+3) //iterates by 3 in order to skip spaces, stops 2 chars before end to avoid out of bounds
        {
            if (temp.at(j+1) == '0') //if number only has single digit, dont take zero in front
            {
                element += temp.at(j+2);
            }
            else{// else take 2 digit number 
                element += temp.at(j+1);
                element += temp.at(j+2);
            }

            // cout << element << "\n"; //test

            elementINT = stoi(element);

            row.push_back(elementINT);

            element.clear();//clears element for reuse
            
        }

        // // testing
        // cout << "row is: ";
        // for (int k =0; k < dim; k++)
        // {
        // cout << row.at(k) << " ";
        // }
        // cout << "\n";

        //push onto matrix1 or matrix2 depending on line
        if (i <= dim)
        {
            matrix1.push_back(row);
        }
        else 
        {
            matrix2.push_back(row);
        }
        
        row.clear(); //clears row for reuse
    } //END FOR LOOP

    //printing matricies
    cout << "Matrix A: \n";
    print_matrix(matrix1);
    cout << "\nMatrix B: \n";
    print_matrix(matrix2);

    //adding matricies
    vector<vector<int>> sum = add_matrix(matrix1,matrix2);
    cout << "\nA + B:\n";
    print_matrix(sum);

    //multiply matricies
    vector<vector<int>> product = mult_matrix(matrix1,matrix2);
    cout << "\nA * B:\n";
    print_matrix(product);

    //add diagonals
    vector<int> diags = sum_diagonal(matrix1);
    cout << "\nDiagonal sums for Matrix A:\n";
    cout << "Main diagonal sum: " << diags.at(0)<< "\n";
    cout << "Main diagonal sum: " << diags.at(1)<< "\n";

    //swap rows------------------------------------
    int rowa;
    int rowb;

    cout << "First row to swap (starting at 1): ";
    cin >> rowa;
    cout << "Second row to swap (starting at 1): ";
    cin >> rowb;

    
    if (swap_rows(matrix1,rowa,rowb) == 1) // if swap_rows is not true, the rows given were out of bounds, and no matrix changes happen
    {
        cout << "\nRows " << rowa << " and " << rowb << " swapped:\n";
        print_matrix(matrix1);
    }

    //swap cols--------------------------------
    int cola;
    int colb;

    cout << "First column to swap (starting at 1): ";
    cin >> cola;
    cout << "Second column to swap (starting at 1): ";
    cin >> colb;
    
    if (swap_cols(matrix1,cola,colb) == 1) // if swap_cols is not true, the cols given were out of bounds, and no matrix changes happen
    {
        cout << "\nColumns " << cola << " and " << colb << " swapped:\n";
        print_matrix(matrix1);
    }

    //update element----------------
    int r; //row
    int c; //col
    int user_val;

    cout << "Enter a row (starting at 1): ";
    cin >> r;
    cout << "Enter a column (starting at 1): ";
    cin >> c;
    cout << "Enter a value: ";
    cin >> user_val;

    if (update_element(matrix1,r,c,user_val) == 1)
    {
        cout << "Matrix updated at ["<<r<<","<<c<<"]\n";
        print_matrix(matrix1);
    }
    


    return 0;
}
