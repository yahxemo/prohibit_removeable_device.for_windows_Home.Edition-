#pragma comment(lib,"user32.lib")
#include<stdio.h>
#include<Windows.h>

#define Address "SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\"


int RegFind()
{
	HKEY hkey;///param
	long regreturn;///get return values
	regreturn = RegOpenKeyExA(HKEY_LOCAL_MACHINE, Address, 0, KEY_ALL_ACCESS, &hkey);//openkey

	CheckOpen(regreturn);//check open

	DWORD dataType;///param
	DWORD dataSize;///
	unsigned char data[4];///
	memset(data, 0, 4);///
	regreturn = 0;///param

	regreturn = RegQueryValueExA(hkey, "Start", NULL, &dataType, data, &dataSize);	//research key value

	if (regreturn != ERROR_SUCCESS)
	{
		printf("		(查询键值失败)return key value failed\n");
		printf("		(返回值为)return value:%d\n\n", regreturn);
	}
	else printf("		(查询键值成功)return key value succeed\n\n");


	if (data[0] == 3)printf("				       (可移动设备为:可读状态)removeable device is: readable\n\n");
	else if (data[0] == 4)printf("				       (可移动设备为为:	为不可读状态)removeable device is:unreadable\n\n");
	else printf("(电脑设置异常)computer setting is failed\n\n");

	RegCloseKey(hkey);

	return data[0];
}

int InPut()
{
	int num;//receive input num

	while (1)
	{
		printf("开启可移动设备请按0,关闭可移动设备请按1\n\n\t\t顺便说一下,只输入数字\n\nopen removeable device press num:0,	close removeable device press num:1\n\t\t\tjust input a number\n\n");
		scanf_s("%d", &num);
		switch (num)
		{
		case 0:
			return 0;
		case 1:
			return 1;
		default:
			printf("(输入错误)input error\n\n");
			break;
		}
	}
}

int RegSet(int in)

{
	in = in + 3;
	HKEY hkey;///param
	long regreturn;///get return values
	regreturn = RegOpenKeyExA(HKEY_LOCAL_MACHINE, Address, 0, KEY_ALL_ACCESS, &hkey);//打开注册表

	CheckOpen(regreturn);//check open

	DWORD dataSize = sizeof(DWORD);///param
	unsigned char data[5];///
	memset(data, 0, 4);///
	data[0] = in;///param
	regreturn = RegSetValueExA(hkey, "Start", 0, REG_DWORD, (BYTE*)data, dataSize);

	if (regreturn != ERROR_SUCCESS)
	{
		printf("		(修改键值失败)set key value failed\n");
		printf("		(返回值为)return num:%d\n\n", regreturn);
	}
	else printf("		(修改键值成功)set key value succeed\n\n\n\n					it done	搞定!\n\n\n\n\n\n");

	RegCloseKey(hkey);
	return 0;
}

int CheckOpen(int regreturn)
{
	if (regreturn != ERROR_SUCCESS)//check the regedit key is open 
	{
		printf("	(出现异常)abnormal\n(返回代码为)error num:%d\n\n", regreturn);
	}
	else printf("	(打开注册表成功)open regedit success\n\n");
	return 0;
}

int main()
{
	printf("\t\t\t\t\t\t\t\t\t\t\t__amu__\n\n");
	RegFind();//find regedit key,and open
	int a=InPut();//input number
	RegSet(a);//set regedit key value
	system("pause");
	return 0;
}
