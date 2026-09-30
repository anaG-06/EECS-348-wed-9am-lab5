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

int print_matrix()
{
    return 0;
}

int add_matrix()
{
    return 0;
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
    
    int dim = stoi(fileRaw[0]);// initialize matrix dimensions
    
    //matrix1 and matrix2 implemented as 2d vectors
    vector <vector<int>> matrix1;
    vector <vector<int>> matrix2;
    
    vector <int> row;// used to create rows for matricies
    string element; //holds row element before converting to int
    int elementINT; //holds row element after converting to int

    //create matrix1 and matrix2
    // i starts at 1 bc line 0 has dim, ends at 

    for (int i = 1; i <= dim * 2; i++)
    {
        string temp = fileRaw.at(i).c_str();
        temp.insert(temp.begin(),'_'); //makes it so that there is one unwanted character in front of each wanted number, makes it easier to clean/get desired part of string
        cout << temp << "\n"; //test

        //create row
        for (int j = 0; j < temp.length()-2; j = j+3) //iterates by 3 in order to skip spaces, stops 2 chars before end to avoid out of bounds
        {
            // string element; //holds row element before converting to int

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
    }

    return 0;
}
