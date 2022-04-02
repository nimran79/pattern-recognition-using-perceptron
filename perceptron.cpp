// perceptron model

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;


//NAVID:---------change ROWS and COLS acccording to the text file train0 and train1
const int ROWS = 2; // training_sample;
const int ROWS2=2*ROWS; //total training sample
const int COLS = 2; // total pixel
const int COLS2=COLS+1; // total pixel +1


// this function is used for debugging. ERASE THIS AFTER DEBUGGINH
void display_matrix(int a[][COLS2],int rows,int col){
int width = col, height = rows;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            std::cout << a[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    }


double * perceptron_engine(int xC1[][COLS],int xC2[][COLS]){
// xC1 load the matrix for zero
//xC2 load the matrix for 1

// augment
int zC1[ROWS][COLS2];
int zC2[ROWS][COLS2];


for(int i = 0; i < ROWS; i++){
    zC1[i][0]=1;
    zC2[i][0]=1;
    for(int j = 0; j < COLS; j++){
        zC1[i][j+1]=xC1[i][j];
        zC2[i][j+1]=xC2[i][j];
    }
}

// show for debug
//display_matrix(zC1,2,3);



// normalize
int yC1[ROWS][COLS2];
int yC2[ROWS][COLS2];


// yC1=-zC1;
// yC2=zC2;
// yC2=zC2;

for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS2; j++){
        yC1[i][j]=-zC1[i][j];
        yC2[i][j]=zC2[i][j];
    }
}


// y=[yC1 ; yC2];
int y[ROWS2][COLS2];

for(int i = 0; i < ROWS; i++){
    for(int j = 0; j < COLS2; j++){
        y[i][j]=yC1[i][j];
    }
}
for(int i = ROWS; i < ROWS2; i++){
    for(int j = 0; j < COLS2; j++){
        y[i][j]=yC2[i-ROWS][j];
    }
}

// for debug
//display_matrix(y,4,3);



// steepest desnet


// a=ones(vector_length+1,1);
double a[COLS2];

for(int j = 0; j < COLS2; j++){
        a[j]=1;
    }


double threshold=.1;
double n=.2;
int limit=100;
int yc[ROWS2][COLS2];
int yj[COLS2];
double AtimesB=0;
double grad_J[COLS2];
int yc_rows=0;
double sum;

for(int i = 0; i < limit; i++){

//    yc=zeros(1,vector_length+1); % set of missclassified vector
    for(int j = 0; j < ROWS2; j++){
            for(int k = 0; k < COLS2; k++){
                yc[j][k]=0;
            }
    }


    //calculate missclassified vectors

    for(int j = 0; j < ROWS2; j++){
        //yj=y[j];
        for(int k = 0; k < COLS2; k++){
            yj[k]=y[j][k];
        }

        //a'*yj'
        AtimesB=0;
         for(int k = 0; k < COLS2; k++){
            AtimesB=AtimesB+yj[k]*a[k];
        }



        if  (AtimesB < 0){
            // yc=[yc ;yj]; // add to the set
            for(int k = 0; k < COLS2; k++){
            yc[yc_rows][k]=yj[k];
            }
            yc_rows++;
        }

    }

     //calculate gradient

     // grad_J=-sum(yc);

     for(int k = 0; k < COLS2; k++){
            sum=0;
            for(int h = 0; h < yc_rows; h++){
                sum=sum+yc[h][k];
            }
            grad_J[k]=-sum;
    }

     // the criterion  (no need)
     //J=a'*grad_J';

     //update a
     for(int k = 0; k < COLS2; k++){
        a[k]=a[k]-n*grad_J[k];
     }


}
return a;


}




/*
%% linear discriminanat
a_final=a; % this is the core matrix for testing the new image

%% test the classifier


%test data
x1_new=test1(1,:);
x2_new=test1(2,:);

total_trial=size(x1_new,1)+size(x2_new,1);
total_trial_1=size(x1_new,1);
total_trial_2=size(x2_new,1);

total_error=0;

for i=1:total_trial_1

    z=x1_new(i,:);
    z=[1 z]; % augment
    z=z';
    figure;
    imshow((reshape(x1_new(i,:),28,28)'),[]); % show image that to be tested
    binary_decision=a_final'*z; % if this variable is +ve then it is a 1 , if -ve then the image is a zero.
    if (a_final'*z) > 0  % condition for C2 which is a misclassification
        total_error=total_error+1;
    end
end */



// returns 0 or 1 depending on the test data
int perceptron_decision(int test[COLS], double a[COLS2]){
    int augmented_test[COLS2];
    int binary_decision=0; // if this variable is +ve then it is a 1 , if -ve then the image is a zero.
    double AtimesB;
    augmented_test[0]=1;
    for(int j = 0; j < COLS; j++){
        augmented_test[j+1]=test[j];

    }

    AtimesB=0;
    for(int k = 0; k < COLS2; k++){
        AtimesB=AtimesB+augmented_test[k]*a[k];
    }

    if (AtimesB>0){
        binary_decision=1;
    }
    if (AtimesB<0){
        binary_decision=0;
    }

    return binary_decision;

}

int main(){
    int train0[ROWS][COLS]={{1,2},{6,4}}; //NAVID: ------read the train0 text file here
    int train1[ROWS][COLS]={{1,2},{6,4}}; //NAVID: -------read the train1 text file here
    double *final_a;
    int test[COLS]={1,2}; //NAVID: --------use the bmp to matrix function to read thee bmp picture here.
    int binary_decision;

    final_a=perceptron_engine(train0,train1);
    binary_decision=perceptron_decision(test,final_a);
    cout << endl;
    cout << "DETECTED NUMBER: " << binary_decision;

}
