//编程计算第一、第二、第三个月还贷后剩余的贷款金额。
//
//Enter amout of loan : 20000.00
//Enter interest rate : 6.0
//Enter monthly payment : 386.66
//
//Balance remaining after first payment : $19713.34
//Balance remaining after second payment : $19425.25
//Balance remaining after third payment : $19135.71
//
//提示：每个月的贷款余额减去还款金额后，还需要加上贷款余额与月利率的乘积。月利率的计算方法是把用户输入的利率转换成百分数再除以12。


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>;

int main() {
	float loan, rate, monthly_pay, monthly_rate;
	printf("Enter amout of loan: ");
	scanf("%g", &loan);
	printf("Enter interest rate: ");
	scanf("%g", &rate);
	printf("Enter monthly payment: ");
	scanf("%g", &monthly_pay);
	monthly_rate = rate / 100 / 12;
	float remaining1, remaining2, remaining3;
	remaining1 = loan * (monthly_rate + 1) - monthly_pay;
	remaining2 = remaining1 * (monthly_rate + 1) - monthly_pay;
	remaining3 = remaining2 * (monthly_rate + 1) - monthly_pay;
	printf("Balance remaining after first payment: $%.2f\nBalance remaining after second payment : $%.2f\nBalance remaining after third payment : $%.2f\n", remaining1, remaining2, remaining3);

	return 0;
}