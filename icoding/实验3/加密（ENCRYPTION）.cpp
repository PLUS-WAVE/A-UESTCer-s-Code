//已知的最古老的一种加密技术是凯撒加密（得名于 Julius caesar）。该方法把一条消息中的每个字母用字母表中固定距离之后的那个字母来替代。（如果越过了字母Z，会绕回到字母表的起始位置。例如，如果每个字母都用字母表中两个位置之后的字母代替，那么Y就被替换为A，Z就被替换为B。）
//
//编写程序用凯撒加密方法对消息进行加密。用户输入待加密的消息和移位计数（字母移动的位置数⽬）：
//Enter message to be encrypted : Go ahead, make my day.
//Enter shift amount(1 - 25) : 3
//Encrypted message : Jr dkhdg, pdnh pb gdb.
//
//
//注意, 当⽤户输⼊26与移位计数的差值时, 程序可以对消息进⾏解密 :
//
//
//	Enter message to be encrypted : Jr dkhdg, pdnh pb gdb.
//	Enter shift amount(1 - 25) : 23
//	Encrypted message : Go ahead, make my day
//
//
//	不是字母的那些字符不要改动。此外，加密时不要改变字母的大小写。
//
//
//	输出范例：
//
//
//	Enter message to be encrypted : Hello, world!
//	Enter shift amount(1 - 25) : 3
//	Encrypted message : Khoor, zruog!
//
//
//	Enter message to be encrypted : Khoor, zruog!
//	Enter shift amount(1 - 25) : 23
//	Encrypted message : Hello, world!


#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	char massage[50];
	int shift;
	printf("Enter message to be encrypted: ");
	gets(massage);
	printf("Enter shift amount (1-25): ");
	scanf("%d", &shift);
	for (int i = 0; i < 50; i++) {
		if (massage[i] >= 65 && massage[i] <= 90) {
			if (massage[i] + shift <= 90) {
				massage[i] = massage[i] + shift;
			}
			else {
				massage[i] = massage[i] + shift - 'Z' + 'A' - 1;
			}
		}
		else if (massage[i] >= 97 && massage[i] <= 122) {
			if (massage[i] + shift <= 122) {
				massage[i] = massage[i] + shift;
			}
			else {
				massage[i] = massage[i] + shift - 'z' + 'a' - 1;
			}
		}
	}
	printf("Encrypted message: ");
	printf("%s", massage);
	return 0;
}