#ifndef SHADOWLIST_H
#define SHADOWLIST_H
#include <QtCore>

namespace Ui {
class ShadowList;
}

class ShadowList : public QThread
{
private:
    int shadowMovesList[9];
    bool shadowUnavailable[9] = {false};

public:
    ShadowList();
    ~ShadowList();

    void run();
    int *getShadowMovesList();
};

#endif // SHADOWLIST_H
