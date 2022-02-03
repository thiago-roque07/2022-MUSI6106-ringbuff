
#include <iostream>
#include <ctime>

#include "MUSI6106Config.h"

#include "RingBuffer.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
     CRingBuffer<float>* pCRingBuff = 0; 
    
    static const int kBlockSize = 7;
    const int testInitLenght = 10;
    const int testEndLength = 40;

    showClInfo();

    pCRingBuff = new CRingBuffer<float>(kBlockSize);
     
    for (int i = 0; i < testInitLenght; i++)
    {
        pCRingBuff->putPostInc(1.F*i);
    }
 
    for (int i = testInitLenght; i < testEndLength; i++)
    {
        cout << i << "-";
        if (pCRingBuff->getNumValuesInBuffer() == testInitLenght) {
            cout << pCRingBuff->getNumValuesInBuffer() << "-"; // should be = testInitLenght
        }
        else { 
            cout << "Error Num Values in Buffer";
            return -1;
        }
        
        float getVal = pCRingBuff->getPostInc();
        if (getVal == (i - testInitLenght)) {
            cout << getVal; // should be i-testInitLenght
        }
        else {
            cout << "Error Get Post Inc";
            return -1;
        }
        cout << endl;
        pCRingBuff->putPostInc(1.F * i);
    }
    cout << "test ended with no errors";
    //// all done
    return 0;

}


void     showClInfo()
{
    cout << "MUSI6106 Assignment Executable" << endl;
    cout << "(c) 2014-2022 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}
