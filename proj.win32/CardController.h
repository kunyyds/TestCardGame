#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

class CardModel;
class CardView;

class CardController {
private:
    CardModel* cardModel;  // ��ģ��
    CardView* cardView;    // ����ͼ

public:
    CardController(CardModel* m, CardView* v);
    void handleCardClick();  // �����Ƶ���¼�
    void updateCardView();   // ��������ͼ
};

#endif // __CARD_CONTROLLER_H__
