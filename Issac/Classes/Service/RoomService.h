#ifndef _ROOMSERVICE_H_
#define _ROOMSERVICE_H_

#include "ViewModel/RoomViewModel.h"

class RoomService
{
public:
	static RoomService* getInstance();
	RoomViewModel getRoom(int roomID);
};

#endif // !_ROOMSERVICE_H_

