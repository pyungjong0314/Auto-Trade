#include <iostream>

#define Increase_Rate 1.0	// �ż� ���� ����
#define Decrease_Rate 1.0	// �ŵ� ���� ����
#define Loss_Rate 5.0		// �ս� ���� ����

using namespace std;

// ��Ʈ ���� ���� (���� �߰� ����)
double BTC_Standard_Price;	// ���� ����
double BTC_Current_Price;	// ���� ����
double BTC_Price_Rate;		// ���� ���� ��ȭ ����
double BTC_Buy_Price;		// �ż� ����
double BTC_Loss_Rate;		// ���� �ս� ����
double BTC_Sell_Price;		// �ŵ� ����

// ���� �ż� �Լ� (�ŰԺ����� ������ ������ �����ϸ� ������ ����.)
void Buy_Coin();
// �ŵ��� �Ϸ� �Ǳ� ������ ����ϴ� �Լ�
void Hold_Coin();
// ���� �ŵ� �Լ�
void Sell_Coin();

int main(void) {


	while (1) {
		cin >> BTC_Standard_Price; // ���� ���� �ʱ�ȭ (��� ����)
		cin >> BTC_Current_Price; // ���� ����
		// ���� ���� ���� ���� ���
		BTC_Price_Rate = (BTC_Current_Price - BTC_Standard_Price) / BTC_Standard_Price * 100;

		// ���� �������� �� ���� ���
		if (BTC_Price_Rate > Increase_Rate) {
			// ������ �����ϸ� ������ �ż�
			Buy_Coin();
			Hold_Coin();
		}

	}
}

void Buy_Coin() {
	cout << "Coin �ż�" << endl;

	// ������ �ż� ������ ������ ����
	BTC_Buy_Price;
}

void Hold_Coin() {
	while (1) {
		cin >> BTC_Standard_Price; // ���� ���� �ʱ�ȭ (��� ����)
		cin >> BTC_Current_Price; // ���� ����
		// ���� ���� ���� ���� ���
		BTC_Price_Rate = (BTC_Standard_Price - BTC_Current_Price) / BTC_Standard_Price * 100;
		// ���� �ս� ���� ���� ���
		BTC_Loss_Rate = (BTC_Buy_Price - BTC_Current_Price) / BTC_Buy_Price * 100;

		// ���� �϶����� �� ���� ��� 
		if (BTC_Price_Rate > Decrease_Rate) {
			// ���� �ŵ�
			Sell_Coin();

			// �Լ� ����
			break;
		}

		// ���� �ս����� ���� �ս��� ���� �� ���� ���
		if (BTC_Loss_Rate > Loss_Rate) {
			// ���� �ŵ�
			Sell_Coin();
			
			// �Լ� ����
			break;
		}
	}
}

void Sell_Coin() {
	cout << "Coin �ŵ�" << endl;

	// ������ �ŵ� ������ ������ ����
	BTC_Sell_Price;
	
	// ���ͷ� ���
	cout << "����" << endl;
}