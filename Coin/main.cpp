#include <iostream>

#define Increase_Rate 1.0	// 매수 기준 비율
#define Decrease_Rate 1.0	// 매도 기준 비율
#define Loss_Rate 5.0		// 손실 기준 비율

using namespace std;

// 비트 코인 가격 (코인 추가 가능)
double BTC_Standard_Price;	// 기준 가격
double BTC_Current_Price;	// 현재 가격
double BTC_Price_Rate;		// 현재 가격 변화 비율
double BTC_Buy_Price;		// 매수 가격
double BTC_Loss_Rate;		// 현재 손실 비율
double BTC_Sell_Price;		// 매도 가격

// 코인 매수 함수 (매게변수에 구매할 코인을 선택하면 좋을것 같다.)
void Buy_Coin();
// 매도가 완료 되기 전까지 대기하는 함수
void Hold_Coin();
// 코인 매도 함수
void Sell_Coin();

int main(void) {


	while (1) {
		cin >> BTC_Standard_Price; // 기준 가격 초기화 (방법 미정)
		cin >> BTC_Current_Price; // 현재 가격
		// 코인 가격 변동 비율 계산
		BTC_Price_Rate = (BTC_Current_Price - BTC_Standard_Price) / BTC_Standard_Price * 100;

		// 가격 증가율이 더 높은 경우
		if (BTC_Price_Rate > Increase_Rate) {
			// 조건을 만족하면 코인을 매수
			Buy_Coin();
			Hold_Coin();
		}

	}
}

void Buy_Coin() {
	cout << "Coin 매수" << endl;

	// 코인을 매수 성공한 가격을 저장
	BTC_Buy_Price;
}

void Hold_Coin() {
	while (1) {
		cin >> BTC_Standard_Price; // 기준 가격 초기화 (방법 미정)
		cin >> BTC_Current_Price; // 현재 가격
		// 코인 가격 변동 비율 계산
		BTC_Price_Rate = (BTC_Standard_Price - BTC_Current_Price) / BTC_Standard_Price * 100;
		// 코인 손실 변동 비율 계산
		BTC_Loss_Rate = (BTC_Buy_Price - BTC_Current_Price) / BTC_Buy_Price * 100;

		// 가격 하락률이 더 높은 경우 
		if (BTC_Price_Rate > Decrease_Rate) {
			// 코인 매도
			Sell_Coin();

			// 함수 종료
			break;
		}

		// 가격 손실율이 기준 손실율 보다 더 높은 경우
		if (BTC_Loss_Rate > Loss_Rate) {
			// 코인 매도
			Sell_Coin();
			
			// 함수 종료
			break;
		}
	}
}

void Sell_Coin() {
	cout << "Coin 매도" << endl;

	// 코인을 매도 성공한 가격을 저장
	BTC_Sell_Price;
	
	// 손익률 계산
	cout << "손익" << endl;
}