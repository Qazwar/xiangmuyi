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
			//�˳�ϵͳ
			break;
		case 1:
			//��ԿЭ��
			cop.seckeyAgree();
			break;
		case 2:
			//��ԿЧ��
			cop.seckeyCheck();
			break;
		case 3:
			//��Կע��
			cop.seckeyWriteOff();
			break;
		case 4:
			//��Կ�鿴
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
	printf("\n  /*			1.��ԿЭ��										  ");
	printf("\n  /*			2.��ԿУ��										  ");
	printf("\n  /*			3.��Կע��										  ");
	printf("\n  /*			4.��Կ�鿴										  ");
	printf("\n  /*			0.�˳�ϵͳ										  ");
	printf("\n  /*************************************************************");
	printf("\n  /*************************************************************");
	printf("\n\n������ѡ��");
	scanf("%d", &nSel);
	while (getchar() != '\n');

	return nSel;
}