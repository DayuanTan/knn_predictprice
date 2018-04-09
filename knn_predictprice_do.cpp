//
//  knn_predictprice_do.cpp
//  
//
//  Created by Dayuan Tan on 4/4/18.
//  data in all_stockschanges_5yr.csv file is ordered by 'open prices changes; high prices changes; low prices changes; close prices changes; volume prices changes; name'
//  data in 9days_8changes_4predict.csv file is ordered by '8 open prices changes; 8 high prices changes; 8 low prices changes; 8 close prices changes; 8 volume prices changes; name;
//    9th day's open price, 9th day's high price, 9th day's low price, 9th day's close price, 9th day's volume'

#include <iostream>
#include <fstream>
#include <sstream> // for stringstream
#include <string>
#include <vector>
#include <tuple>
#include "math.h"

using namespace std; // must add this line for vector

float str2flt(string num){  
    float res;  
    stringstream stream(num);  
    stream>>res;  
    return res;  
} 
int str2int(string num){  
    int res;  
    stringstream stream(num);  
    stream>>res;  
    return res;  
} 
float compEuclideanDistFloat(vector<float> eightdayElem, vector<float> historyElem, float distanceMix){ //compute euclidean Distance
        float sum = 0;
        for (int i=0;i<=7;i++)
        {
            sum += ( eightdayElem[i] - historyElem[i] ) * ( eightdayElem[i] - historyElem[i] );
        }
        float distance = sqrt(sum);
        if (distance < distanceMix) 
        {
            distanceMix = distance;
        }
        return distanceMix;
}


int main()
{
    // predicted_price.csv is used for store predicted price
    ofstream outFile("predicted_price.csv");
    outFile << "date" << ',' << "predicted open price" << ',' << "predicted high price" << ',' << "predicted low price" << ',' << "predicted close price" << ',' << "predicted volume" << endl;  
        

    // read 8 days prices changes before the day we want to predict
    ifstream eightdayfin("9days_8changes_4predict.csv");
    string line;
    vector<float> eightdayopensflt;
    vector<float> eightdayhighsflt;
    vector<float> eightdaylowsflt;
    vector<float> eightdayclosesflt;
    vector<float> eightdayvolumesflt;
    while (getline(eightdayfin, line))   
    {
        float openDistanceMix = 100000000000.0;
        float highDistanceMix = 100000000000.0;
        float lowDistanceMix = 100000000000.0;
        float closeDistanceMix = 100000000000.0;
        float volumeDistanceMix = 100000000000.0;
        vector<float> matchedopensflt;
        vector<float> matchedhighsflt;
        vector<float> matchedlowsflt;
        vector<float> matchedclosesflt;
        vector<float> matchedvolumesflt;
        vector<int> matchedvolumesfltInt;

        istringstream sin(line); //read whole line into stringstream 'sin'
        vector<string> fields; 
        string field; //declare a string variable 
        string eightdayopenset; //declare
        string eightdayhighset; 
        string eightdaylowset; 
        string eightdaycloseset;
        string eightdayvolumeset;
        string eightdaynameset;
        string ninthdaydataset;
        float ninthDayPredictedOpenPricce; 
        float ninthDayPredictedHighPricce; 
        float ninthDayPredictedLowPricce; 
        float ninthDayPredictedClosePricce; 
        int ninthDayPredictedVolume;
        while (getline(sin, field, ';')) //put chars of stringstream 'sin' into string 'filed', seperate by ';' 
        {
            fields.push_back(field); //append just read string into 'filed'
        }
        if (fields.size() == 7)
        {
            eightdayopenset = fields[0]; //assign
            eightdayhighset = fields[1]; 
            eightdaylowset = fields[2]; 
            eightdaycloseset = fields[3];
            eightdayvolumeset = fields[4];
            eightdaynameset = fields[5];
            ninthdaydataset = fields[6]; // 9th day's data, just the day before predicted day. 
        }

        vector<string> ninthdaydatas;
        string ninthdaydata;
        istringstream ninthdaydatasteam(ninthdaydataset);
        while (getline(ninthdaydatasteam, ninthdaydata, ','))
        {
            ninthdaydatas.push_back(ninthdaydata);
        }
        if (ninthdaydatas.size() == 5) // 9th day's open price, 9th day's high price, 9th day's low price, 9th day's close price, 9th day's volume
        {
            ninthDayPredictedOpenPricce = str2flt(ninthdaydatas[0]);
            ninthDayPredictedHighPricce = str2flt(ninthdaydatas[1]);
            ninthDayPredictedLowPricce = str2flt(ninthdaydatas[0]);
            ninthDayPredictedClosePricce = str2flt(ninthdaydatas[1]);
            ninthDayPredictedVolume = str2int(ninthdaydatas[0]);

        }


        vector<string> eightdayopens;
        string eightdayopen;
        istringstream eightdayopenstrsteam(eightdayopenset);
        while (getline(eightdayopenstrsteam, eightdayopen, ','))
        {
            eightdayopens.push_back(eightdayopen);
        }
        //vector<float> eightdayopensflt;
        if (eightdayopens.size() == 8)
        {
            for (int i=0;i<=eightdayopens.size();i++)
            {
                eightdayopensflt.push_back( str2flt(eightdayopens[i]) );
            }
        }

        vector<string> eightdayhighs;
        string eightdayhigh;
        istringstream eightdayhighstrsteam(eightdayhighset);
        while (getline(eightdayhighstrsteam, eightdayhigh, ','))
        {
            eightdayhighs.push_back(eightdayhigh);
        }
        //vector<float> eightdayhighsflt;
        if (eightdayhighs.size() == 8)
        {
            for (int i=0;i<=eightdayhighs.size();i++)
            {
                eightdayhighsflt.push_back( str2flt(eightdayhighs[i]) );
            }
        }

        vector<string> eightdaylows;
        string eightdaylow;
        istringstream eightdaylowstrsteam(eightdaylowset);
        while (getline(eightdaylowstrsteam, eightdaylow, ','))
        {
            eightdaylows.push_back(eightdaylow);
        }
        //vector<float> eightdaylowsflt;
        if (eightdaylows.size() == 8)
        {
            for (int i=0;i<=eightdaylows.size();i++)
            {
                eightdaylowsflt.push_back( str2flt(eightdaylows[i]) );
            }
        }

        vector<string> eightdaycloses;
        string eightdayclose;
        istringstream eightdayclosestrsteam(eightdaycloseset);
        while (getline(eightdayclosestrsteam, eightdayclose, ','))
        {
            eightdaycloses.push_back(eightdayclose);
        }
        //vector<float> eightdayclosesflt;
        if (eightdaycloses.size() == 8)
        {
            for (int i=0;i<=eightdaycloses.size();i++)
            {
                eightdayclosesflt.push_back( str2flt(eightdaycloses[i]) );
            }
        }

        vector<string> eightdayvolumes;
        string eightdayvolume;
        istringstream eightdayvolumestrsteam(eightdayvolumeset);
        while (getline(eightdayvolumestrsteam, eightdayvolume, ','))
        {
            eightdayvolumes.push_back(eightdayvolume);
        }
        //vector<int> eightdayvolumesflt;
        if (eightdayvolumes.size() == 8)
        {
            for (int i=0;i<=eightdayvolumes.size();i++)
            {
                eightdayvolumesflt.push_back( (float)str2flt(eightdayvolumes[i]) / (float)1000000 );
            }
        }
    

        //----------------------iterate process history 9 price changes sets-----------

        ifstream fin("all_stockschanges_5yr.csv"); //open filestream
        //string line;
        while (getline(fin, line))   //read a line by '\n'; stop when meet EOF
        {
            istringstream sin(line); //read whole line into stringstream 'sin'
            vector<string> fields; 
            string field; //declare a string variable 
            string openset; //declare
            string highset; 
            string lowset; 
            string closeset;
            string volumeset;
            string nameset;
            while (getline(sin, field, ';')) //put chars of stringstream 'sin' into string 'filed', seperate by ';' 
            {
                fields.push_back(field); //append just read string into 'filed'
            }
            if (fields.size() == 6)
            {
                openset = fields[0]; //assign
                highset = fields[1]; 
                lowset = fields[2]; 
                closeset = fields[3];
                volumeset = fields[4];
                nameset = fields[5];
            }

            if (nameset == eightdaynameset)
            { 
                vector<string> opens;
                string open;
                istringstream openstrsteam(openset);
                while (getline(openstrsteam, open, ','))
                {
                    opens.push_back(open);
                }
                vector<float> opensflt;
                if (opens.size() == 9)
                {
                    for (int i=0;i<=opens.size();i++)
                    {
                        opensflt.push_back( str2flt(opens[i]) );
                    }
                }

                vector<string> highs;
                string high;
                istringstream highstrsteam(highset);
                while (getline(highstrsteam, high, ','))
                {
                    highs.push_back(high);
                }
                vector<float> highsflt;
                if (highs.size() == 9)
                {
                    for (int i=0;i<=highs.size();i++)
                    {
                        highsflt.push_back( str2flt(highs[i]) );
                    }
                }

                vector<string> lows;
                string low;
                istringstream lowstrsteam(lowset);
                while (getline(lowstrsteam, low, ','))
                {
                    lows.push_back(low);
                }
                vector<float> lowsflt;
                if (lows.size() == 9)
                {
                    for (int i=0;i<=lows.size();i++)
                    {
                        lowsflt.push_back( str2flt(lows[i]) );
                    }
                }

                vector<string> closes;
                string close;
                istringstream closestrsteam(closeset);
                while (getline(closestrsteam, close, ','))
                {
                    closes.push_back(close);
                }
                vector<float> closesflt;
                if (closes.size() == 9)
                {
                    for (int i=0;i<=closes.size();i++)
                    {
                        closesflt.push_back( str2flt(closes[i]) );
                    }
                }

                vector<string> volumes;
                string volume;
                istringstream volumestrsteam(volumeset);
                while (getline(volumestrsteam, volume, ','))
                {
                    volumes.push_back(volume);
                }
                vector<float> volumesflt;
                if (volumes.size() == 9)
                {
                    for (int i=0;i<=volumes.size();i++)
                    {
                        volumesflt.push_back( (float)str2flt(volumes[i]) / (float)1000000);
                    }
                }
            

                //----------------------compute euclidean Distance-----------
                float openDistanceMix2 = compEuclideanDistFloat(eightdayopensflt,opensflt,openDistanceMix);
                if (openDistanceMix2 != openDistanceMix) 
                {
                    openDistanceMix = openDistanceMix2;
                    matchedopensflt = opensflt;
                }
                float highDistanceMix2 = compEuclideanDistFloat(eightdayhighsflt,highsflt,highDistanceMix);
                if (highDistanceMix2 != highDistanceMix) 
                {
                    highDistanceMix = highDistanceMix2;
                    matchedhighsflt = highsflt;
                }
                float lowDistanceMix2 = compEuclideanDistFloat(eightdaylowsflt,lowsflt,lowDistanceMix);
                if (lowDistanceMix2 != lowDistanceMix) 
                {
                    lowDistanceMix = lowDistanceMix2;
                    matchedlowsflt = lowsflt;
                }
                float closeDistanceMix2 = compEuclideanDistFloat(eightdayclosesflt,closesflt,closeDistanceMix);
                if (closeDistanceMix2 != closeDistanceMix) 
                {
                    closeDistanceMix = closeDistanceMix2;
                    matchedclosesflt = closesflt;
                }
                float volumeDistanceMix2 = compEuclideanDistFloat(eightdayvolumesflt,volumesflt,volumeDistanceMix);
                if (volumeDistanceMix2 != volumeDistanceMix) 
                {
                    volumeDistanceMix = volumeDistanceMix2;
                    matchedvolumesflt = volumesflt;
                }
            }else 
            {
                continue;
            }
        }


        //----------------------print final matched 9 price changes set-----------
        for (int i=0;i<=8;i++)
        {
            matchedvolumesfltInt.push_back( (int)(matchedvolumesflt[i] * 1000000) );
        }
        

        //----------------------get the predicted price on 10th day-----------
        float tenthDayPredictedOpenPricce = matchedopensflt[8] + ninthDayPredictedOpenPricce; // matched price change + 9th day's open price = 10th day's open price
        float tenthDayPredictedHighPricce = matchedhighsflt[8] + ninthDayPredictedHighPricce; // matched price change + 9th day's high price = 10th day's high price
        float tenthDayPredictedLowPricce = matchedlowsflt[8] + ninthDayPredictedLowPricce; // matched price change + 9th day's low price = 10th day's low price
        float tenthDayPredictedClosePricce = matchedclosesflt[8] + ninthDayPredictedClosePricce; // matched price change + 9th day's close price = 10th day's close price
        int tenthDayPredictedVolume = matchedvolumesfltInt[8] + ninthDayPredictedVolume; // matched volume change + 9th day's volume = 10th day's volume
    
        outFile << "2-8-2018" << ',' << tenthDayPredictedOpenPricce << ',' << tenthDayPredictedHighPricce << ',' << tenthDayPredictedLowPricce << ',' << tenthDayPredictedClosePricce << ',' << tenthDayPredictedVolume << endl;  
        

    }

    outFile.close(); 
    return EXIT_SUCCESS;
}

