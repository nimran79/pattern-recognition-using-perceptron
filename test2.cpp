#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;


// This function reads a BMP file and converts it into a matrix
//Output: matrix and the length
unsigned char* ReadBMP(char* filename,int* length)
{
    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for(int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < width*3; j += 3)
        {
            // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;

         // this is used to show the matrix
         //   cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }
    }

    fclose(f);
    *length=height*width;
    return data;
}


int main(){
	unsigned char* data = new unsigned char[1000000]; // stores the bmp in a single line of array with data[i] is red data [i=1] green  ...
    int dataint;
    int length;
	data=ReadBMP("pic.bmp",&length);


    cout << length<<endl;

    // Convert the numbers into string . we will use only the Red pixel

    std::string data2write="";

    for(int i = 0; i < length; i=i+3){
        dataint=(int)data[i];
        std::stringstream ss;
        ss << dataint;
        std::string pixeldata = ss.str();

    data2write=data2write+" "+pixeldata;
    }

    //Display for debug
    cout<< data2write;



    // write the data into the txt file
    std::ofstream out("client.txt");
    out << data2write;
    out.close();


	return 0;
}
