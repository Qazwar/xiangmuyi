#include<iostream>
#include"ClientOP.h"

using namespace std;

int usage();
int main()
{
	ClientOP cop("client.json");

	int sel = 0;
	while (1)
	{
		sel=usage();
		switch(sel)
		{
		case 0:
			//退出系统
			break;
		case 1:
			//密钥协商
			cop.seckeyAgree();
			break;
		case 2:
			//密钥效验
			cop.seckeyCheck();
			break;
		case 3:
			//密钥注销
			cop.seckeyWriteOff();
			break;
		case 4:
			//密钥查看
			break;
		}
		if (sel == 0)
			break;
	}


	return 0;
}

int usage()
{
	int nSel = -1;
	printf("\n  /*************************************************************");
	printf("\n  /*************************************************************");
	printf("\n  /*			1.密钥协商										  ");
	printf("\n  /*			2.密钥校验										  ");
	printf("\n  /*			3.密钥注销										  ");
	printf("\n  /*			4.密钥查看										  ");
	printf("\n  /*			0.退出系统										  ");
	printf("\n  /*************************************************************");
	printf("\n  /*************************************************************");
	printf("\n\n》》》选择：");
	scanf("%d", &nSel);
	while (getchar() != '\n');

	return nSel;
}