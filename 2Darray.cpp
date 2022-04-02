// Create & Connect file stream, Read the data and store them into 2D Arrays

// C++ constants
const int ROWS = 100;
const int COLS = 785;

/* Check the Row and Col number please */

/****************************************************************************************
     Function: readData
*****************************************************************************************
  Description: Reads pixel data from text file and stores in a 2D array
****************************************************************************************/
void readData(int pixel[][COLS], int ROWS)
{
    //Create and Connect file stream
    ifstream infile;
    infile.open("Train0.txt"); // Open the file

    // Check if the file has been opened successfully
    if (!infile)
    {
        cout << "Error opening the data file!" << endl;
        exit(102);  // You need cstdlib.h for this 
    }

    for (int r = 0; r < ROWS; r++ )
    {
        for (int c = 0; c < COLS; c++)
        {
            infile >> pixel[r][c];

            //Input Validation : Check if the pixel values are negative
            if (pixel[r][c] < 0)
            {
                pixel[r][c] = 0;
                cout << " ERROR in the File!!!" << endl ;
            }

        }

    }

    // Close the file
    infile.close();
}