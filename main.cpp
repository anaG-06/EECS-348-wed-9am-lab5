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

    return 0;
}
