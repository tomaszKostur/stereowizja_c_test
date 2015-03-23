#include <iostream>
#include <opencv2/opencv.hpp>

int sprawdz_dopasowanie(cv::Mat mask,int mask_position, cv::Mat rows2mask)
{
    int minimum = 0xffff;
    int place = 0;
    for(int i=0; i < rows2mask.cols - mask.cols ; ++i)
    {
        cv::Mat temp;
        cv::absdiff(mask,rows2mask(cv::Rect(i,0,mask.cols,mask.rows)),temp);
        int suma = (int)cv::sum(temp)[0];
        if(minimum >= suma)
        {
            minimum = suma;
            place = i;
        }
    }
    int dispar = mask_position - place;
    return dispar;
}

void disparitionMap(cv::Mat left, cv::Mat right, cv::Mat disp_Map, int mask_size)
{
    int mask_offset = (mask_size-1)/2;

    for(int i=mask_offset; i<left.rows-mask_offset-1; ++i )
    {
        for(int j=mask_offset; j<left.cols-mask_offset-1; ++j)
        {
            cv::Mat mask = left(cv::Rect(j-mask_offset,i-mask_offset,mask_size,mask_size));
            int mask_position = j;
            cv::Mat rows2mask = right(cv::Rect(0,i-mask_offset,right.cols,mask_size));
            disp_Map.row(i).col(j) = sprawdz_dopasowanie(mask,mask_position,rows2mask);
        }
    }
}

void szybkiTestNormalizacji()
{
    cv::Mat test=(cv::Mat_<double>(3,3) << -3,-2,-1,0,1,2,3,4,5);
    std::cout<<test<<"\n\n";
    cv::normalize(test,test,255,0,cv::NORM_MINMAX);
    std::cout<<test<<"\n\n";
}

void szybki_test_podmacierzy()
{
    cv::Mat test=(cv::Mat_<double>(5,5) << -3,-2,-1,0,1,2,3,4,5,1,2,3,4,5,6,7,8,9,8,7,6,5,4,3);
    std::cout<<test<<std::endl<<"\n";
    cv::Mat test2 = test(cv::Rect(2,1,3,2));
    std::cout<<test2<<"\n\n";
}

int main()
{
    cv::Mat left,right,result;
    left = cv::imread("/home/tomek/polibuda/magisterka/test_L.png");
    right = cv::imread("/home/tomek/polibuda/magisterka/test_R.png");
    result = cv::Mat::zeros(left.size(),CV_8UC1);

    disparitionMap(left,right,result,5);
    cv::normalize(result,result,255,0,cv::NORM_MINMAX);
    cv::imshow("window",result);
    cv::waitKey();
//    szybki_test_podmacierzy();


    return 0;
}

