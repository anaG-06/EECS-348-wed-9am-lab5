/*
Date: 9.30.26
Author: Ana Gonzalez Yuil
Lab: 5
Sources:N/A
Description: matrix operations, reading from a file
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//moved to main
int read_file(string fileName)
//read file taking the filename with extension as input, outputs array holding two 2d vectors (the matricies)
{
    // struct {
    //     vector<int> matrixA = {};
    //     vector<int> matrixB = {};
    // } mat; //mat for matricies

    string line;
    ifstream myFile(fileName);

    if (myFile.is_open())
    {
        while ( getline(myFile,line) )
        {
            cout << line << endl;
        }
        myFile.close();
    }
    else cout << "Unable to open file";
    // return mat;
}

int print_matrix()
{

}

int add_matrix()
{

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
            // cout << line << endl;
            fileRaw.push_back(line); //push file contents into unorganized vector
        }
        myFile.close();
    }
    
    int dim = atoi(fileRaw[0].c_str());// initialize matrix dimensions, use to set matrix size
    vector <int> matrix1[dim];
    vector <int> matrix2[dim];
    
    //print matricies
    // cout << fileRaw[1][0] << "\n"; //test

    vector <int> row[dim];// used to create rows for matricies

    //create matrix1
    // i starts at 1 bc line 0 has dim

    for (int i = 1; i < dim; i++) //dont forget to atoi and c_str as you go after cleaning 
    {
        // row.push_back(fileRaw[i].c_str());
        string temp = fileRaw[i].c_str();
        temp.insert(temp.begin(),'_'); //makes it so that there is one unwanted character in front of each wanted number, makes it easier to clean/get desired part of string
        cout << temp << "\n"; //test
        cout << temp[1] + temp[2] << "\n"; //figure out how to concatenate chars <----------- HERE


        // for (int j = 0; j <= temp.length()-2; j++)
        // {
        //     cout << temp[j+1] + temp[j+2] << "\n";
        // }









        
    }
    
    

    return 0;
}
