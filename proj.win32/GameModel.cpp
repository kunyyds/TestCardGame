#include "GameModel.h"






bool GameModel::matchPlayfieldCard(int index) {
    // ʾ���߼�������������Ƿ��п�ƥ����ƣ������ʵ�ʹ���ʵ�֣�
    if (index < 0 || index >= _playfield.size()) return false;
    // ... ����ƥ���߼� ...
    return true;
}

bool GameModel::matchStackCard() {
    // ʾ���߼�����鱸���ƶ��Ƿ��п�ƥ�����
    // ... ����ƥ���߼� ...
    return true;
}