//
//  knn_predictprice.cpp
//  
//
//  Created by Dayuan Tan on 4/4/18.
//  data in all_stockschanges_5yr_apart.csv file is ordered by 'open prices changes; high prices changes; low prices changes; close prices changes; volume prices changes; name'
//  data in 9days_8changes_b4_predictedday.csv file is ordered by '8 open prices changes; 8 high prices changes; 8 low prices changes; 8 close prices changes; 8 volume prices changes; name;
//    9th day's open price, 9th day's high price, 9th day's low price, 9th day's close price, 9th day's volume'

#include <iostream>
#include <fstream>
#include <sstream> // for stringstream
#include <string>
#include <vector>
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
        cout << "distance: " << distance << endl;
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
    outFile << "date" << ',' << "name" << ',' << "predicted open price" << ',' << "predicted high price" << ',' << "predicted low price" << ',' << "predicted close price" << ',' << "predicted volume" << endl;  
        

    // read 8 days prices changes before the day we want to predict
    ifstream eightdayfin("9days_8changes_b4_predictedday.csv");
    string line;
    vector<float> eightdayopensflt;
    vector<float> eightdayhighsflt;
    vector<float> eightdaylowsflt;
    vector<float> eightdayclosesflt;
    vector<float> eightdayvolumesflt;
    cout << "hello: " << eightdayfin << endl;
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

        cout <<"eight days original strings："<< line << endl; //output whole line
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
            cout <<"eight days processed strings："<< eightdaynameset << "\n" << "eight days open changes set:" << eightdayopenset << "\n" << "eight days high changes set:" << eightdayhighset << "\n" << "eight days low changes set:" << eightdaylowset<< "\n" << "eight days close changes set:" << eightdaycloseset << "\n" << "eight days volume changes set:" << eightdayvolumeset << endl;
            cout <<"9th day's data: " << ninthdaydataset << "\n" << endl;
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
            ninthDayPredictedLowPricce = str2flt(ninthdaydatas[2]);
            ninthDayPredictedClosePricce = str2flt(ninthdaydatas[3]);
            ninthDayPredictedVolume = str2int(ninthdaydatas[4]);

            cout << "9th day open price : " << ninthDayPredictedOpenPricce <<endl;
            cout << "9th day high price : " << ninthDayPredictedHighPricce <<endl;
            cout << "9th day low price : " << ninthDayPredictedLowPricce <<endl;
            cout << "9th day close price : " << ninthDayPredictedClosePricce <<endl;
            cout << "9th day volume : " << ninthDayPredictedVolume <<endl;
        }
        vector<string>(ninthdaydatas).swap(ninthdaydatas);

        vector<string> eightdayopens;
        string eightdayopen;
        istringstream eightdayopenstrsteam(eightdayopenset);
        while (getline(eightdayopenstrsteam, eightdayopen, ','))
        {
            eightdayopens.push_back(eightdayopen);
        }
        if (eightdayopens.size() == 8)
        {
            for (int i=0;i<eightdayopens.size();i++)
            {
                eightdayopensflt.push_back( str2flt(eightdayopens[i]) );
            }
            cout << "eightdayopen change 1: " << eightdayopensflt[0] <<endl;
            cout << "eightdayopen change 2: " << eightdayopensflt[1] <<endl;
            cout << "eightdayopen change 3: " << eightdayopensflt[2] <<endl;
            cout << "eightdayopen change 4: " << eightdayopensflt[3] <<endl;
            cout << "eightdayopen change 5: " << eightdayopensflt[4] <<endl;
            cout << "eightdayopen change 6: " << eightdayopensflt[5] <<endl;
            cout << "eightdayopen change 7: " << eightdayopensflt[6] <<endl;
            cout << "eightdayopen change 8: " << eightdayopensflt[7] <<endl;
            cout << "\n\n" <<endl;
        }
        vector<string>(eightdayopens).swap(eightdayopens);

        vector<string> eightdayhighs;
        string eightdayhigh;
        istringstream eightdayhighstrsteam(eightdayhighset);
        while (getline(eightdayhighstrsteam, eightdayhigh, ','))
        {
            eightdayhighs.push_back(eightdayhigh);
        }
        if (eightdayhighs.size() == 8)
        {
            for (int i=0;i<eightdayhighs.size();i++)
            {
                eightdayhighsflt.push_back( str2flt(eightdayhighs[i]) );
            }
            cout << "eightdayhigh change 1: " << eightdayhighsflt[0] <<endl;
            cout << "eightdayhigh change 2: " << eightdayhighsflt[1] <<endl;
            cout << "eightdayhigh change 3: " << eightdayhighsflt[2] <<endl;
            cout << "eightdayhigh change 4: " << eightdayhighsflt[3] <<endl;
            cout << "eightdayhigh change 5: " << eightdayhighsflt[4] <<endl;
            cout << "eightdayhigh change 6: " << eightdayhighsflt[5] <<endl;
            cout << "eightdayhigh change 7: " << eightdayhighsflt[6] <<endl;
            cout << "eightdayhigh change 8: " << eightdayhighsflt[7] <<endl;
            cout << "\n\n" <<endl;
        }
        vector<string>(eightdayhighs).swap(eightdayhighs);

        vector<string> eightdaylows;
        string eightdaylow;
        istringstream eightdaylowstrsteam(eightdaylowset);
        while (getline(eightdaylowstrsteam, eightdaylow, ','))
        {
            eightdaylows.push_back(eightdaylow);
        }
        if (eightdaylows.size() == 8)
        {
            for (int i=0;i<eightdaylows.size();i++)
            {
                eightdaylowsflt.push_back( str2flt(eightdaylows[i]) );
            }
            cout << "eightdaylow change 1: " << eightdaylowsflt[0] <<endl;
            cout << "eightdaylow change 2: " << eightdaylowsflt[1] <<endl;
            cout << "eightdaylow change 3: " << eightdaylowsflt[2] <<endl;
            cout << "eightdaylow change 4: " << eightdaylowsflt[3] <<endl;
            cout << "eightdaylow change 5: " << eightdaylowsflt[4] <<endl;
            cout << "eightdaylow change 6: " << eightdaylowsflt[5] <<endl;
            cout << "eightdaylow change 7: " << eightdaylowsflt[6] <<endl;
            cout << "eightdaylow change 8: " << eightdaylowsflt[7] <<endl;
            cout << "\n\n" <<endl;
        }
        vector<string>(eightdaylows).swap(eightdaylows);

        vector<string> eightdaycloses;
        string eightdayclose;
        istringstream eightdayclosestrsteam(eightdaycloseset);
        while (getline(eightdayclosestrsteam, eightdayclose, ','))
        {
            eightdaycloses.push_back(eightdayclose);
        }
        if (eightdaycloses.size() == 8)
        {
            for (int i=0;i<eightdaycloses.size();i++)
            {
                eightdayclosesflt.push_back( str2flt(eightdaycloses[i]) );
            }
            cout << "eightdayclose change 1: " << eightdayclosesflt[0] <<endl;
            cout << "eightdayclose change 2: " << eightdayclosesflt[1] <<endl;
            cout << "eightdayclose change 3: " << eightdayclosesflt[2] <<endl;
            cout << "eightdayclose change 4: " << eightdayclosesflt[3] <<endl;
            cout << "eightdayclose change 5: " << eightdayclosesflt[4] <<endl;
            cout << "eightdayclose change 6: " << eightdayclosesflt[5] <<endl;
            cout << "eightdayclose change 7: " << eightdayclosesflt[6] <<endl;
            cout << "eightdayclose change 8: " << eightdayclosesflt[7] <<endl;
            cout << "\n\n" <<endl;
        }
        vector<string>(eightdaycloses).swap(eightdaycloses);

        vector<string> eightdayvolumes;
        string eightdayvolume;
        istringstream eightdayvolumestrsteam(eightdayvolumeset);
        while (getline(eightdayvolumestrsteam, eightdayvolume, ','))
        {
            eightdayvolumes.push_back(eightdayvolume);
        }
        if (eightdayvolumes.size() == 8)
        {
            for (int i=0;i<eightdayvolumes.size();i++)
            {
                eightdayvolumesflt.push_back( (float)str2flt(eightdayvolumes[i]) / (float)1000000 );
            }
            cout << "eightdayvolume change 1: " << eightdayvolumesflt[0] <<endl;
            cout << "eightdayvolume change 2: " << eightdayvolumesflt[1] <<endl;
            cout << "eightdayvolume change 3: " << eightdayvolumesflt[2] <<endl;
            cout << "eightdayvolume change 4: " << eightdayvolumesflt[3] <<endl;
            cout << "eightdayvolume change 5: " << eightdayvolumesflt[4] <<endl;
            cout << "eightdayvolume change 6: " << eightdayvolumesflt[5] <<endl;
            cout << "eightdayvolume change 7: " << eightdayvolumesflt[6] <<endl;
            cout << "eightdayvolume change 8: " << eightdayvolumesflt[7] <<endl;
            cout << "\n\n" <<endl;
        }
        vector<string>(eightdayvolumes).swap(eightdayvolumes);
    

        //----------------------iterate process history 9 price changes sets-----------

        ifstream fin("all_stockschanges_5yr_apart.csv"); //open filestream
        while (getline(fin, line))   //read a line by '\n'; stop when meet EOF
        {
            cout <<"original strings："<< line << endl; //output whole line
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
                cout <<"processed strings："<< nameset << "\n" << "open changes set:" << openset << "\n" << "high changes set:" << highset << "\n" << "low changes set:" << lowset<< "\n" << "close changes set:" << closeset << "\n" << "volume changes set:" << volumeset << "\n" << endl;
            }

            cout << "if: " << eightdaynameset << nameset << endl;
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
                    for (int i=0;i<opens.size();i++)
                    {
                        opensflt.push_back( str2flt(opens[i]) );
                    }
                    cout << "open change 1: " << opensflt[0] <<endl;
                    cout << "open change 2: " << opensflt[1] <<endl;
                    cout << "open change 3: " << opensflt[2] <<endl;
                    cout << "open change 4: " << opensflt[3] <<endl;
                    cout << "open change 5: " << opensflt[4] <<endl;
                    cout << "open change 6: " << opensflt[5] <<endl;
                    cout << "open change 7: " << opensflt[6] <<endl;
                    cout << "open change 8: " << opensflt[7] <<endl;
                    cout << "open change 9: " << opensflt[8] <<endl;
                    cout << "\n\n" <<endl;
                }
                vector<string>(opens).swap(opens);

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
                    for (int i=0;i<highs.size();i++)
                    {
                        highsflt.push_back( str2flt(highs[i]) );
                    }
                    cout << "high change 1: " << highsflt[0] <<endl;
                    cout << "high change 2: " << highsflt[1] <<endl;
                    cout << "high change 3: " << highsflt[2] <<endl;
                    cout << "high change 4: " << highsflt[3] <<endl;
                    cout << "high change 5: " << highsflt[4] <<endl;
                    cout << "high change 6: " << highsflt[5] <<endl;
                    cout << "high change 7: " << highsflt[6] <<endl;
                    cout << "high change 8: " << highsflt[7] <<endl;
                    cout << "high change 9: " << highsflt[8] <<endl;
                    cout << "\n\n" <<endl;
                }
                vector<string>(highs).swap(highs);

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
                    for (int i=0;i<lows.size();i++)
                    {
                        lowsflt.push_back( str2flt(lows[i]) );
                    }
                    cout << "low change 1: " << lowsflt[0] <<endl;
                    cout << "low change 2: " << lowsflt[1] <<endl;
                    cout << "low change 3: " << lowsflt[2] <<endl;
                    cout << "low change 4: " << lowsflt[3] <<endl;
                    cout << "low change 5: " << lowsflt[4] <<endl;
                    cout << "low change 6: " << lowsflt[5] <<endl;
                    cout << "low change 7: " << lowsflt[6] <<endl;
                    cout << "low change 8: " << lowsflt[7] <<endl;
                    cout << "low change 9: " << lowsflt[8] <<endl;
                    cout << "\n\n" <<endl;
                }
                vector<string>(lows).swap(lows);

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
                    for (int i=0;i<closes.size();i++)
                    {
                        closesflt.push_back( str2flt(closes[i]) );
                    }
                    cout << "close change 1: " << closesflt[0] <<endl;
                    cout << "close change 2: " << closesflt[1] <<endl;
                    cout << "close change 3: " << closesflt[2] <<endl;
                    cout << "close change 4: " << closesflt[3] <<endl;
                    cout << "close change 5: " << closesflt[4] <<endl;
                    cout << "close change 6: " << closesflt[5] <<endl;
                    cout << "close change 7: " << closesflt[6] <<endl;
                    cout << "close change 8: " << closesflt[7] <<endl;
                    cout << "close change 9: " << closesflt[8] <<endl;
                    cout << "\n\n" <<endl;
                }
                vector<string>(closes).swap(closes);

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
                    for (int i=0;i<volumes.size();i++)
                    {
                        volumesflt.push_back( (float)str2flt(volumes[i]) / (float)1000000);
                    }
                    cout << "volume change 1: " << volumesflt[0] <<endl;
                    cout << "volume change 2: " << volumesflt[1] <<endl;
                    cout << "volume change 3: " << volumesflt[2] <<endl;
                    cout << "volume change 4: " << volumesflt[3] <<endl;
                    cout << "volume change 5: " << volumesflt[4] <<endl;
                    cout << "volume change 6: " << volumesflt[5] <<endl;
                    cout << "volume change 7: " << volumesflt[6] <<endl;
                    cout << "volume change 8: " << volumesflt[7] <<endl;
                    cout << "volume change 9: " << volumesflt[8] <<endl;
                    cout << "\n\n" <<endl;
                }
                vector<string>(volumes).swap(volumes);
            

                //----------------------compute euclidean Distance-----------
                cout << "bf openDistanceMix: " << openDistanceMix << endl;
                cout << "bf highDistanceMix: " << highDistanceMix << endl;
                cout << "bf lowDistanceMix: " << lowDistanceMix << endl;
                cout << "bf closeDistanceMix: " << closeDistanceMix << endl;
                cout << "bf volumeDistanceMix: " << volumeDistanceMix << endl;
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
                cout << "af openDistanceMix: " << openDistanceMix << "  matchedopensflt: " << matchedopensflt[0] << endl;
                cout << "af highDistanceMix: " << highDistanceMix << "  matchedhighsflt: " << matchedhighsflt[0] << endl;
                cout << "af lowDistanceMix: " << lowDistanceMix << "  matchedlowsflt: " << matchedlowsflt[0] << endl;
                cout << "af closeDistanceMix: " << closeDistanceMix << "  matchedclosesflt: " << matchedclosesflt[0] << endl;
                cout << "af volumeDistanceMix: " << volumeDistanceMix << "  matchedvolumesflt: " << matchedvolumesflt[0] << endl;
            }else 
            {
                continue;
            }
        }
        fin.close();

        //----------------------print final matched 9 price changes set-----------
        cout << "\n\n-------------------\nfinal matched 9 prices changes set:" << endl;
        for (int i=0;i<=8;i++)
        {
            matchedvolumesfltInt.push_back( (int)(matchedvolumesflt[i] * 1000000) );
            cout << "final matchedopensflt: " << matchedopensflt[i] << " final matchedhighsflt: " << matchedhighsflt[i] << " final matchedlowsflt: " << matchedlowsflt[i] << " final matchedclosesflt: " << matchedclosesflt[i] << " final matchedvolumesfltInt: " << matchedvolumesfltInt[i] << "\n" << endl;
        }
        

        //----------------------get the predicted price on 10th day-----------
        cout << "9th day open price : " << ninthDayPredictedOpenPricce <<endl;
        cout << "9th day high price : " << ninthDayPredictedHighPricce <<endl;
        cout << "9th day low price : " << ninthDayPredictedLowPricce <<endl;
        cout << "9th day close price : " << ninthDayPredictedClosePricce <<endl;
        cout << "9th day volume : " << ninthDayPredictedVolume <<endl;
        float tenthDayPredictedOpenPricce = matchedopensflt[8] + ninthDayPredictedOpenPricce; // matched price change + 9th day's open price = 10th day's open price
        float tenthDayPredictedHighPricce = matchedhighsflt[8] + ninthDayPredictedHighPricce; // matched price change + 9th day's high price = 10th day's high price
        float tenthDayPredictedLowPricce = matchedlowsflt[8] + ninthDayPredictedLowPricce; // matched price change + 9th day's low price = 10th day's low price
        float tenthDayPredictedClosePricce = matchedclosesflt[8] + ninthDayPredictedClosePricce; // matched price change + 9th day's close price = 10th day's close price
        int tenthDayPredictedVolume = matchedvolumesfltInt[8] + ninthDayPredictedVolume; // matched volume change + 9th day's volume = 10th day's volume
        cout << "10th day's open price: " << tenthDayPredictedOpenPricce << endl;
        cout << "10th day's high price: " << tenthDayPredictedHighPricce << endl;
        cout << "10th day's low price: " << tenthDayPredictedLowPricce << endl;
        cout << "10th day's close price: " << tenthDayPredictedClosePricce << endl;
        cout << "10th day's volume: " << tenthDayPredictedVolume << endl;
        cout << "\n\n-------------------\n\n-------------------\n\n-------------------\n\n-------------------\n\n-------------------\n\n\n\n" << endl;
        
        cout << eightdaynameset << endl;
        outFile << "2-8-2018" << ',' << eightdaynameset << ',' << tenthDayPredictedOpenPricce << ',' << tenthDayPredictedHighPricce << ',' << tenthDayPredictedLowPricce << ',' << tenthDayPredictedClosePricce << ',' << tenthDayPredictedVolume << endl;  
        

    }

    eightdayfin.close();
    outFile.close(); 
    return 0;
}

