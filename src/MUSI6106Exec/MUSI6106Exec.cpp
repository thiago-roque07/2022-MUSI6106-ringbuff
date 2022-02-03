
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
    
    static const int kBlockSize = 15;
    const int test1_InitLenght = 10;
    const int test1_EndLength = 50;

    const int test2_InitLenght = 18;
    const int test2_EndLength = 40;

    showClInfo();

    pCRingBuff = new CRingBuffer<float>(kBlockSize);
     
    cout << "-- test simple buffer write and read --" << endl;
    for (int i = 0; i < test1_InitLenght; i++)
    {
        pCRingBuff->putPostInc(1.F*i);
    }
 
    for (int i = test1_InitLenght; i < test1_EndLength; i++)
    {
        cout << i << "-";
        if (pCRingBuff->getNumValuesInBuffer() == test1_InitLenght) {
            cout << pCRingBuff->getNumValuesInBuffer() << "-"; // should be = test1_InitLenght
        }
        else { 
            cout << "Error Num Values in Buffer" << endl;
            cout << "expected value: " << test1_InitLenght << endl;
            cout << "received value : " << pCRingBuff->getNumValuesInBuffer();
            return -1;
        }
        
        float getVal = pCRingBuff->getPostInc();
        if (getVal == (i - test1_InitLenght)) {
            cout << getVal << "--" << pCRingBuff->getReadIdx();; // should be i-test1_InitLenght
        }
        else {
            cout << "Error Get Post Inc";
            return -1;
        }
        cout << endl;
        pCRingBuff->putPostInc(1.F * i);
    }
    cout << endl;

    /////////////////////////
    // Test reset function //
    pCRingBuff->reset();
    cout << "-- test reset function --" << endl;
    if (!(pCRingBuff->getWriteIdx()) || !(pCRingBuff->getReadIdx())) {
        cout << "write idx: " << pCRingBuff->getWriteIdx() << endl;
        cout << "read idx: " << pCRingBuff->getReadIdx() << endl;
    }
    else {
        cout << "Error on reset index" << endl;
        cout << "expected 0" << endl;
        cout << "received: " << pCRingBuff->getWriteIdx() << "for write index" << endl;
        cout << "received: " << pCRingBuff->getReadIdx() << "for read index" << endl;
    }

    for (int i = 0; i < kBlockSize; i++)
    {
        if (pCRingBuff->get(i)) {
            cout << "Error reseting buffer" << endl;
            return -1;
        }
    }
    cout << "buffer empty" << endl;
    cout << endl;

    // Tests for more complex write and read//
    cout << "-- test more complex write and read --" << endl;
    for (int i = 0; i < test2_InitLenght; i++)
    {
        cout << "variable: " << i << endl;
        cout << "index:" << pCRingBuff->getWriteIdx() << endl;
        pCRingBuff->putPostInc(1.F * i);

    }
    
    cout << endl;
    for (int i = test2_InitLenght; i < test2_EndLength; i++)
    {
        cout << i << "-";
        if (pCRingBuff->getNumValuesInBuffer() == (test2_InitLenght - kBlockSize)) {
            cout << pCRingBuff->getNumValuesInBuffer() << "-";
        }
        else {
            cout << "Error Num Values in Buffer" << endl;
            cout << "expected value: " << test2_InitLenght << endl;
            cout << "received value : " << pCRingBuff->getNumValuesInBuffer();
            return -1;
        }

        int getIdx = pCRingBuff->getReadIdx();
        float getVal = pCRingBuff->getPostInc();
        if (getVal == (i - test2_InitLenght + kBlockSize)) {
            cout << getVal << "--" << getIdx;
        }
        else {
            cout << "Error Get value from buffer" << endl;
            cout << "received value:" << getVal << endl;
            cout << "get index: " << getIdx;
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
