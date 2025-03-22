#include "editmanager.h"

EditManager EditManager::ins;

EditManager &EditManager::getIns()
{
    return ins;
}
