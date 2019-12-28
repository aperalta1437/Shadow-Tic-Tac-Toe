/*
 * This class was created with the purpose of initializing the movements within the shadow board.
 * NOTE: The initialization of such object is executed on a different thread due to the time it takes to create.
 */

#include "shadowlist.h"

ShadowList::ShadowList()
{
}

ShadowList::~ShadowList() {

}

void ShadowList::run()
{
    int index;

    for(int shadowBoxNum = 0; shadowBoxNum < 9; shadowBoxNum++) {
        do {
            srand(time(0));
            index = (rand() % (8 - 0 + 1)) + 0;

        }while(shadowUnavailable[index]);
        shadowMovesList[index] = shadowBoxNum;
        shadowUnavailable[index] = true;

    }
}

int *ShadowList::getShadowMovesList()
{
    return shadowMovesList;
}
