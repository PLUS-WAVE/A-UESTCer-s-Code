//�����г��������ѭ�����Ա��û����������ʽ��ײ��ҳ�����Լ���ÿ�ε�Ӷ�𡣳������û�����Ľ��׶�Ϊ 0 ʱ��ֹ��
//
//���������
//
//Enter value of trade : 30000
//Commission��$166.00
//
//Enter value of trade : 20000
//Commission��$144.00
//Enter value of trade : 0


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<math.h>


int main(void)
{
	float commission, value = 1.0;
	while (value != 0) {
		printf("Enter value of trade: ");
		scanf("%f", &value);
		if (value != 0) {
			if (value < 2500.00f)
				commission = 30.00f + .017f * value;
			else if (value < 6250.00f)
				commission = 56.00f + .0066f * value;
			else if (value < 20000.00f)
				commission = 76.00f + .0034f * value;
			else if (value < 50000.00f)
				commission = 100.00f + .0022f * value;
			else if (value < 500000.00f)
				commission = 155.00f + .0011f * value;
			else
				commission = 255.00f + .0009f * value;

			if (commission < 39.00f)
				commission = 39.00f;

			printf("Commission: $%.2f\n\n", commission);
		}
		else
		{
			break;
		}
	}
	return 0;
}