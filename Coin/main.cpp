#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;



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
double UPBIT_BTC_Price;

// 코인 매수 함수 (매게변수에 구매할 코인을 선택하면 좋을것 같다.)
void Buy_Coin();
// 매도가 완료 되기 전까지 대기하는 함수
void Hold_Coin();
// 코인 매도 함수
void Sell_Coin();

long double get_binance_price(const std::string& code);
long double get_upbit_price(const std::string& code);
long double get_currency(const std::string& code);




int main() {
    BTC_Standard_Price = get_binance_price("BTC"); // 기준 가격 초기화 (방법 미정)

    while (1)
    {
        BTC_Current_Price = get_binance_price("BTC"); // 현재 가격
        BTC_Price_Rate = ((BTC_Current_Price - BTC_Standard_Price) / BTC_Standard_Price) * 100; // 코인 가격 변동 비율 계산

        UPBIT_BTC_Price = get_upbit_price("BTC"); // 업비트 현재 가격 
        long double currency = get_currency("USD"); // 달러 환율 가져오기
        bool price_diff = (BTC_Current_Price * currency) - UPBIT_BTC_Price; // (바이낸스 - 업비트) 시세차익

        BTC_Standard_Price = BTC_Current_Price; // 기준 가격 재지정



        // (바이낸스 > 가격증가율) && (바이낸스 > 업비트)   바이낸스의 시세가 업비트를 추월했음으로 매수
        if (BTC_Price_Rate > Increase_Rate && price_diff > 0) {
            // 조건을 만족하면 코인을 매수
            Buy_Coin();
            Hold_Coin();
        }

    }
    return 0;
}


void Buy_Coin() {
    cout << "Coin 매수" << endl;

    // UPBIT API를 이용한 매수
    // 코인을 매수 성공한 가격을 저장
    BTC_Buy_Price = 0;
}


void Hold_Coin() {
    while (1)
    {
        // 기준 가격 초기화 (방법 미정), 현재 가격 전역 변수에 저장됨
        BTC_Current_Price = get_binance_price("BTC"); // 현재 가격
        BTC_Price_Rate = ((BTC_Current_Price - BTC_Standard_Price) / BTC_Standard_Price) * 100; // 코인 가격 변동 비율 계산

        UPBIT_BTC_Price = get_upbit_price("BTC"); // 업비트 현재 가격 
        long double currency = get_currency("USD"); // 달러 환율 가져오기
        bool price_diff = (BTC_Current_Price * currency) - UPBIT_BTC_Price; // (바이낸스 - 업비트) 시세차익

        BTC_Standard_Price = BTC_Current_Price; // 기준 가격 재지정

        BTC_Loss_Rate = (BTC_Buy_Price - BTC_Current_Price) / BTC_Buy_Price * 100;



        if (BTC_Price_Rate < Decrease_Rate || price_diff < 0) {        // 코인 손실 변동 비율 계산   
            // - (바이낸스 < 감소율) && (바이낸스 < 업비트)  
            // - (음수이므로 더 낮은 값이 하락률이 높음!)
            // - 전액 매도
            break;
        }
    }
}

void Sell_Coin() {
    cout << "Coin 매도" << endl;

    // UPBIT API를 이용한 매도
    // 코인을 매도 성공한 가격을 저장
    BTC_Sell_Price = 0;

    // 손익률 계산
    cout << "손익" << endl;
}

long double get_binance_price(const std::string& code) {
    try {
        // URL for fetching the order book from Binance Exchange (BTC/USDT pair)
        string url = "https://api.binance.com/api/v3/ticker/price?symbol=" + code + "USDT";

        // Make the HTTP GET request using CPR
        auto response = cpr::Get(cpr::Url{ url });

        // Check if the request was successful
        if (response.status_code == 200) {
            // Parse the response body as JSON
            json data = json::parse(response.text);

            // Extract price from JSON
            long double price = stold(data["price"].get<string>());

            // Check if the price retrieval was successful
            if (price != -1.0) {
                //cout << "Price of BTCUSDT: " << price << endl;
            }
            else {
                //cout << "Faifled to retrieve price." << endl;
            }

            return price;
        }
        else {
            // Print error message if request failed
            cerr << "Error: Failed to fetch price. Status code: " << response.status_code << endl;
            return -1.0; // Return -1 to indicate failure
        }
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return -1.0; // Return -1 to indicate failure
    }
}

long double get_upbit_price(const std::string& code) {
    try {
        // URL for fetching ticker data from Upbit
        string url = "https://api.upbit.com/v1/ticker?markets=KRW-" + code;

        // Make the HTTP GET request using CPR
        auto response = cpr::Get(cpr::Url{ url });

        // Check if the request was successful
        if (response.status_code == 200) {
            // Parse the response body as JSON
            json data = json::parse(response.text);

            // Extract price from JSON
            long double upbit_price = data[0].at("opening_price");
            std::cout << upbit_price << std::endl;

            // Check if the price retrieval was successful
            if (upbit_price != -1.0) {
                //cout << "Price of KRW-" << code << ": " << upbit_price << endl;
            }
            else {
                //cout << "Failed to retrieve price." << endl;
            }

            return upbit_price;
        }
        else {
            // Print error message if request failed
            cerr << "Error: Failed to fetch price. Status code: " << response.status_code << endl;
            return -1.0; // Return -1 to indicate failure
        }
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return -1.0; // Return -1 to indicate failure
    }
}


long double get_currency(const std::string& code) {
    try {
        // URL for fetching ticker data from Upbit
        string url = "https://quotation-api-cdn.dunamu.com/v1/forex/recent?codes=FRX.KRW" + code;

        // Make the HTTP GET request using CPR
        auto response = cpr::Get(cpr::Url{ url });

        // Check if the request was successful
        if (response.status_code == 200) {
            // Parse the response body as JSON
            json data = json::parse(response.text);

            // Extract price from JSON
            long double currency = data[0].at("basePrice");

            return currency;
        }
        else {
            // Print error message if request failed
            cerr << "Error: Failed to fetch currency. Status code: " << response.status_code << endl;
            return -1.0; // Return -1 to indicate failure
        }
    }
    catch (const std::exception& e) {
        cerr << "Exception: " << e.what() << endl;
        return -1.0; // Return -1 to indicate failure
    }
}
