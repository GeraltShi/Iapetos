#include "RoomViewModel.h"

RoomViewModel RoomViewModel::createRoomViewModel(int roomType)
{
	RoomViewModel room1;
	room1.init(roomType);
	return room1;
}

void RoomViewModel::init(int roomType)
{
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 7; j++)
			room_map[i][j] = 0;

	//������0��ʾ�յأ�1��ʾСʯͷ��2��ʾ��ʯͷ��3��ʾ���
	//4~19��ʾ����ĸ������,20~30item
	//���ɼ��ַ���֮һ,����ʯͷ
	int barrierType = rand() % 3;
	if (barrierType == 0) {
		//û��ʯͷ
	}
	if (barrierType == 1) {
		//0,0,0,0,0,0,0,0,0,0,0,0,0
		//0,0,0,0,0,0,0,0,0,0,0,0,0
		//0,0,0,0,0,0,1,0,0,0,0,0,0
		//0,0,1,1,1,1,1,1,1,1,1,0,0
		//0,0,0,0,0,0,1,0,0,0,0,0,0
		//0,0,0,0,0,0,0,0,0,0,0,0,0
		//0,0,0,0,0,0,0,0,0,0,0,0,0		
		for (int i = 2; i <= 10; i++)
			room_map[i][3] = 1;
		for (int i = 2; i <= 4; i++)
			room_map[6][i] = 1;
	}
	if (barrierType == 2) {
		//0,0,0,0,0,0,0,0,0,0,0,0,0
		//0,0,0,2,2,0,0,0,2,2,0,0,0
		//0,0,0,2,2,0,0,0,2,2,0,0,0
		//0,0,0,0,0,0,0,0,0,0,0,0,0
		//0,0,0,2,2,0,0,0,2,2,0,0,0
		//0,0,0,2,2,0,0,0,2,2,0,0,0
		//0,0,0,0,0,0,0,0,0,0,0,0,0	
		room_map[3][1] = 2;
		room_map[4][1] = 2;
		room_map[3][2] = 2;
		room_map[4][2] = 2;
		room_map[3][4] = 2;
		room_map[4][4] = 2;
		room_map[3][5] = 2;
		room_map[4][5] = 2;
		room_map[8][1] = 2;
		room_map[9][1] = 2;
		room_map[8][2] = 2;
		room_map[9][2] = 2;
		room_map[8][4] = 2;
		room_map[9][4] = 2;
		room_map[8][5] = 2;
		room_map[9][5] = 2;
	}

	//����roomType�������
	//Fatty:4
	if (roomType == 1) {
		int Fatty_num = rand() % 4 + 2;
		int posX = rand() % 13, posY = rand() % 7;
		while (room_map[posX][posY] != 0) {
			posX = rand() % 13; 
			posY = rand() % 7;
		}
		room_map[posX][posY] = 4;
	}
}