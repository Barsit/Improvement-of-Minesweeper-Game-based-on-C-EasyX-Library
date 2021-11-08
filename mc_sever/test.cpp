 #include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32.lib")

SOCKADDR_IN cAddr = { 0 };//保存客服端信息
int len = sizeof cAddr;
SOCKET clientsocket[1024];
int count = 0;
char buff[1024] = { "  " };
//数据处理结构体
struct  message
{
	char item[20];
	char time[20];
	char name[20];
	char ip[50];

}now[11];

void save();//保存数据
void sort();//排序
void Send(int i);//修改的发送函数


//通信
int communicate(int idx)//idx代表是哪个线程
{
	int r;
	while (1)
	{
		r = recv(clientsocket[idx], buff, 1023, NULL);
		printf("%d\n",r);
		if (r==-1)//如果没有收到信息，返回值-1，关闭线程
		{
			return 0;
		}
		if (r > 0)
		{
			printf("通信开始\n");
			buff[r] = '\0';
			printf("%d:%s\n\n", idx, buff);
			strcat(buff, "    ");
			strcat(buff, inet_ntoa(cAddr.sin_addr));
			save();
			sort();
			//广播数据
			for (int i = 0; i < count; i++)
			{
				Send(i);
			}
			strcpy(buff, "");
		}
	}
}

//保存数据
void save()
{
	FILE* fp8, * fp16, * fp32;
	if (buff[0] == '8')
	{
		fp8 = fopen("mcs8.txt", "a");
		if (fp8 == NULL)
		{
			printf("文件mcs8.txt无法打开!\n");
			exit(0);
		}
		else
		{
			fprintf(fp8, "%s\n", buff);
			printf("数据已保存\n");
			fclose(fp8);
		}
	}

	if (buff[0] == '1')
	{
		fp16 = fopen("mcs16.txt", "a");
		if (fp16 == NULL)
		{
			printf("文件mcs16.txt无法打开!\n");
			exit(0);
		}
		else
		{
			fprintf(fp16, "%s\n", buff);
			printf("数据已保存\n");
			fclose(fp16);
		}
	}
	if (buff[0] == '3')
	{
		fp32 = fopen("mcs32.txt", "a");
		if (fp32 == NULL)
		{
			printf("文件mcs32.txt无法打开!\n");
			exit(0);
		}
		else
		{
			fprintf(fp32, "%s\n", buff);
			printf("数据已保存\n");
			fclose(fp32);
		}
	}
}

//排序保存
void sort()
{
	FILE* fp8, * fp16, * fp32;
	message temp;
	int s1 = 0, s2 = 0;//暂时存储now.time类型转换值
	if (buff[0] == '8')
	{
		fp8 = fopen("mcs8.txt", "r");
		if (fp8 == NULL)
		{
			printf("文件mcs8.txt无法打开!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)
			{
				fscanf(fp8, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("读取%d次\n", i+1);
			}
		}
		fclose(fp8);

		printf("读取完成，开始排序\n");
		s1=atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//排序
		{
			s2 = atoi(now[i].time);
			printf("s2:%d\n", s2);
			if (s1 < s2)
			{
				temp = now[10];
				now[10] = now[i];
				now[i] = temp;	
				break;
			}
		}

		printf("排序完成，开始保存\n");
		//储存
		fp8 = fopen("mcs8.txt", "w");
		if (fp8 == NULL)
		{
			printf("文件mcs8.txt无法打开!\n");
			exit(0);
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				fprintf(fp8, "%s\t%s\t%s\t%s\n", now[i].item,now[i].time,now[i].name,now[i].ip);
			}
		}
		fclose(fp8);
	}

	if (buff[0] == '1')
	{
		fp16 = fopen("mcs16.txt", "r");
		if (fp16 == NULL)
		{
			printf("文件mcs16.txt无法打开!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)
			{
				fscanf(fp16, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("读取%d次", i+1);
			}
		}
		fclose(fp16);
		s1 = atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//排序
		{
			s2 = atoi(now[i].time);
			printf("s2:%d\n", s2);
			if (s1 < s2)
			{
				temp = now[10];
				now[0] = now[i];
				now[i] = temp;
			}
		}
		//储存
		fp16 = fopen("mcs16.txt", "w");
		if (fp16 == NULL)
		{
			printf("文件mcs16.txt无法打开!\n");
			exit(0);
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				fprintf(fp16, "%s\t%s\t%s\t%s\n", now[i].item, now[i].time, now[i].name, now[i].ip);
			}
		}
		fclose(fp16);
	}

	if (buff[0] == '3')
	{
		fp32 = fopen("mcs32.txt", "r");
		if (fp32 == NULL)
		{
			printf("文件mcs32.txt无法打开!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)//读取
			{
				fscanf(fp32, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("读取%d次", i + 1);
			}
		}
		fclose(fp32);

		s1 = atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//排序
		{
			s2 = atoi(now[i].time);
			printf("s2:%d\n", s2);
			if (s1 < s2)
			{
				temp = now[10];
				now[0] = now[i];
				now[i] = temp;
			}
		}
		//储存
		fp32 = fopen("mcs32.txt", "w");
		if (fp32 == NULL)
		{
			printf("文件mcs32.txt无法打开!\n");
			exit(0);
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				fprintf(fp32, "%s\t%s\t%s\t%s\n", now[i].item, now[i].time, now[i].name, now[i].ip);
			}
		}
		fclose(fp32);
	}

}

//修改的发消息函数
void Send(int i)
{
	char tp[20];
	message temp;//暂时储存文件读取
	char sendbuff[1024*2]="";
	FILE* fp8, * fp16, * fp32;
	fp8 = fopen("mcs8.txt", "r");
	if (fp8 == NULL)
	{
		printf("文件mcs8.txt无法打开!\n");
		exit(0);
	}
	fp16 = fopen("mcs16.txt", "r");
	if (fp16 == NULL)
	{
		printf("文件mcs16.txt无法打开!\n");
		exit(0);
	}
	fp32 = fopen("mcs32.txt", "r");
	if (fp32 == NULL)
	{
		printf("文件mcs32.txt无法打开!\n");
		exit(0);
	}
	for(int i=0;i<10;i++)
	{
		fscanf(fp8, "%s%s%s%s", temp.item, temp.time, temp.name, temp.ip);
		strcat(sendbuff, temp.item);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.time);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.name);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.ip);
		strcat(sendbuff, "\n");
	}
	strcat(sendbuff, "\n");
	//printf("%d\n", strlen(sendbuff));

	for (int i = 0; i < 10; i++)
	{
		fscanf(fp16, "%s%s%s%s", temp.item, temp.time, temp.name, temp.ip);
		strcat(sendbuff, temp.item);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.time);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.name);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.ip);
		strcat(sendbuff, "\n");
	}
	strcat(sendbuff, "\n");
	//printf("%d\n", strlen(sendbuff));

	for (int i = 0; i < 10; i++)
	{
		fscanf(fp32, "%s%s%s%s", temp.item, temp.time, temp.name, temp.ip);
		strcat(sendbuff, temp.item);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.time);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.name);
		strcat(sendbuff, "    ");
		strcat(sendbuff, temp.ip);
		strcat(sendbuff, "\n");
	}
	sendbuff[strlen(sendbuff) + 1] = '\0';

	fclose(fp8);
	fclose(fp16);
	fclose(fp32);
	printf("%s\n", sendbuff);
	printf("here");
	//发送
	send(clientsocket[i], sendbuff, strlen(sendbuff), NULL);
}

int main()
{
	//请求版本协议
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("请版本协议失败\n");
		return -1;//返回值-1
	}
	else
		printf("请求版本协议成功\n");
	//创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket)
	{
		printf("创建socket失败\n");
		WSACleanup();
		return -2;//返回值-2
	}
	else
	{
		printf("创建socket成功\n");

	}
	//创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
	addr.sin_port = htons(10086);//参数选10000左右
	//绑定
	int r = bind(serverSocket, (sockaddr*) & addr, sizeof addr);
	if (SOCKET_ERROR == r)
	{
		printf("绑定失败\n");
		WSACleanup();
		return -3;//返回值-3
	}
	else
	{
		printf("绑定成功\n");
	}
	//监听
	r = listen(serverSocket, 10);
	if (SOCKET_ERROR == r)
	{
		printf("监听失败\n");
		WSACleanup();
		return -4;//返回值-4
	}
	else
	{
		printf("监听成功\n");
	}
	//等待客户端连接
	while (1)
	{
		clientsocket[count] = accept(serverSocket, (sockaddr*)&cAddr, &len);
		if (SOCKET_ERROR == clientsocket[count])
		{
			printf("服务器宕机\n");
			closesocket(serverSocket);
			WSACleanup();
			return -5;//返回值-5
		}
	
	printf("有客户端连接服务器：%s!\n", inet_ntoa(cAddr.sin_addr));//inet_ntoa>将整形IP转换成字符串型
	CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)communicate, (char*)count,NULL, NULL);
	count++;

	}
	
	return 0;
}