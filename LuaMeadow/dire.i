%module direwolf;

%{
#include "DWMediator.h"
#include "DWController.h"
%}

%rename(Mediator) DWMediator;

class DWMediator
{
public:
    DWMediator();
    ~DWMediator();
    void release();
    void printType();
    void move(int x, int y);
};

%rename(Controller) DWController;
class DWController
{
public:
    DWController();
    ~DWController();
    void release();
    void registerView(DWMediator *mediator);
};