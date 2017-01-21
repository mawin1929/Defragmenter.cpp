// Author Michael Win for Sean Davis' Class Fall 2015

//A simulation of how a hard drive organizes its sectors efficiently given block ID's
//The goal of this assignment was to convey an understanding of data structures by being given the freedom
//to choose which data structure to use as well as the ability to implement different given libraries.

#include "DefragRunner.h"
#include "QuadraticProbing.h"
#include "mynew.h"
#include "stdio.h"


int main()
{
    QuadraticHashTable<int> hashTable(-1, 500000);
    int size = diskDrive->directory[0].getSize();
    int cap = diskDrive->getNumFiles();
    int capacity = diskDrive->getCapacity();
    unsigned blockID = diskDrive->directory[dirID].getFirstBlockID();

    DiskBlock* blockPTR;
    DiskBlock* blockPTR2;

    int tempfound = 0;
    int fullsize = 0;
    int dirID = 0;
    int i = 2;


    for (int x = 0; x < capacity; x++) {
        blockPTR = diskDrive->readDiskBlock(blockID);
     

        if (blockPTR->getNext() == 1) { 
            blockID = blockPTR->getNext();

            if (dirID == 0) {
                diskDrive->directory[dirID].setFirstBlockID(2);
            }
            else {
                diskDrive->directory[dirID].setFirstBlockID(2 + fullsize);
            }

            size = diskDrive->directory[dirID].getSize();
            fullsize += size;
            dirID++;

            if (cap == dirID) {
                diskDrive->writeDiskBlock(blockPTR, i);
                diskDrive->FAT[i] = true;
                break;
            }
            blockID = diskDrive->directory[dirID].getFirstBlockID();

        } //read in next fileID, firstBlock,and size when necessary.

        else {
            blockID = blockPTR->getNext();
            blockPTR->setNext(i + 1);
        } //update Next ID
        diskDrive->writeDiskBlock(blockPTR, i);
        diskDrive->FAT[i] = true;

        if ((hashTable.find(blockID)) != -1) {

            while ((tempfound = hashTable.findNewPos(blockID)) != -1) {
                hashTable.remove(blockID);
                blockID = tempfound;
            }

            blockPTR->setNext(blockID);
            blockID = blockPTR->getNext();
        }
        hashTable.remove(blockID);
        delete blockPTR;
        i++;
    }
}
