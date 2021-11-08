 #include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#pragma comment(lib,"ws2_32.lib")

SOCKADDR_IN cAddr = { 0 };//����ͷ�����Ϣ
int len = sizeof cAddr;
SOCKET clientsocket[1024];
int count = 0;
char buff[1024] = { "  " };
//���ݴ���ṹ��
struct  message
{
	char item[20];
	char time[20];
	char name[20];
	char ip[50];

}now[11];

void save();//��������
void sort();//����
void Send(int i);//�޸ĵķ��ͺ���


//ͨ��
int communicate(int idx)//idx�������ĸ��߳�
{
	int r;
	while (1)
	{
		r = recv(clientsocket[idx], buff, 1023, NULL);
		printf("%d\n",r);
		if (r==-1)//���û���յ���Ϣ������ֵ-1���ر��߳�
		{
			return 0;
		}
		if (r > 0)
		{
			printf("ͨ�ſ�ʼ\n");
			buff[r] = '\0';
			printf("%d:%s\n\n", idx, buff);
			strcat(buff, "    ");
			strcat(buff, inet_ntoa(cAddr.sin_addr));
			save();
			sort();
			//�㲥����
			for (int i = 0; i < count; i++)
			{
				Send(i);
			}
			strcpy(buff, "");
		}
	}
}

//��������
void save()
{
	FILE* fp8, * fp16, * fp32;
	if (buff[0] == '8')
	{
		fp8 = fopen("mcs8.txt", "a");
		if (fp8 == NULL)
		{
			printf("�ļ�mcs8.txt�޷���!\n");
			exit(0);
		}
		else
		{
			fprintf(fp8, "%s\n", buff);
			printf("�����ѱ���\n");
			fclose(fp8);
		}
	}

	if (buff[0] == '1')
	{
		fp16 = fopen("mcs16.txt", "a");
		if (fp16 == NULL)
		{
			printf("�ļ�mcs16.txt�޷���!\n");
			exit(0);
		}
		else
		{
			fprintf(fp16, "%s\n", buff);
			printf("�����ѱ���\n");
			fclose(fp16);
		}
	}
	if (buff[0] == '3')
	{
		fp32 = fopen("mcs32.txt", "a");
		if (fp32 == NULL)
		{
			printf("�ļ�mcs32.txt�޷���!\n");
			exit(0);
		}
		else
		{
			fprintf(fp32, "%s\n", buff);
			printf("�����ѱ���\n");
			fclose(fp32);
		}
	}
}

//���򱣴�
void sort()
{
	FILE* fp8, * fp16, * fp32;
	message temp;
	int s1 = 0, s2 = 0;//��ʱ�洢now.time����ת��ֵ
	if (buff[0] == '8')
	{
		fp8 = fopen("mcs8.txt", "r");
		if (fp8 == NULL)
		{
			printf("�ļ�mcs8.txt�޷���!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)
			{
				fscanf(fp8, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("��ȡ%d��\n", i+1);
			}
		}
		fclose(fp8);

		printf("��ȡ��ɣ���ʼ����\n");
		s1=atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//����
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

		printf("������ɣ���ʼ����\n");
		//����
		fp8 = fopen("mcs8.txt", "w");
		if (fp8 == NULL)
		{
			printf("�ļ�mcs8.txt�޷���!\n");
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
			printf("�ļ�mcs16.txt�޷���!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)
			{
				fscanf(fp16, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("��ȡ%d��", i+1);
			}
		}
		fclose(fp16);
		s1 = atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//����
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
		//����
		fp16 = fopen("mcs16.txt", "w");
		if (fp16 == NULL)
		{
			printf("�ļ�mcs16.txt�޷���!\n");
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
			printf("�ļ�mcs32.txt�޷���!\n");
			exit(0);
		}
		else
		{
			int i = 0;
			for (int i = 0; i < 11; i++)//��ȡ
			{
				fscanf(fp32, "%s%s%s%s", now[i].item, now[i].time, now[i].name, now[i].ip);
				printf("��ȡ%d��", i + 1);
			}
		}
		fclose(fp32);

		s1 = atoi(now[10].time);
		printf("s1:%d\n", s1);
		for (int i = 0; i < 10; i++)//����
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
		//����
		fp32 = fopen("mcs32.txt", "w");
		if (fp32 == NULL)
		{
			printf("�ļ�mcs32.txt�޷���!\n");
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

//�޸ĵķ���Ϣ����
void Send(int i)
{
	char tp[20];
	message temp;//��ʱ�����ļ���ȡ
	char sendbuff[1024*2]="";
	FILE* fp8, * fp16, * fp32;
	fp8 = fopen("mcs8.txt", "r");
	if (fp8 == NULL)
	{
		printf("�ļ�mcs8.txt�޷���!\n");
		exit(0);
	}
	fp16 = fopen("mcs16.txt", "r");
	if (fp16 == NULL)
	{
		printf("�ļ�mcs16.txt�޷���!\n");
		exit(0);
	}
	fp32 = fopen("mcs32.txt", "r");
	if (fp32 == NULL)
	{
		printf("�ļ�mcs32.txt�޷���!\n");
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
	//����
	send(clientsocket[i], sendbuff, strlen(sendbuff), NULL);
}

int main()
{
	//����汾Э��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("��汾Э��ʧ��\n");
		return -1;//����ֵ-1
	}
	else
		printf("����汾Э��ɹ�\n");
	//����socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == serverSocket)
	{
		printf("����socketʧ��\n");
		WSACleanup();
		return -2;//����ֵ-2
	}
	else
	{
		printf("����socket�ɹ�\n");

	}
	//����Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
	addr.sin_port = htons(10086);//����ѡ10000����
	//��
	int r = bind(serverSocket, (sockaddr*) & addr, sizeof addr);
	if (SOCKET_ERROR == r)
	{
		printf("��ʧ��\n");
		WSACleanup();
		return -3;//����ֵ-3
	}
	else
	{
		printf("�󶨳ɹ�\n");
	}
	//����
	r = listen(serverSocket, 10);
	if (SOCKET_ERROR == r)
	{
		printf("����ʧ��\n");
		WSACleanup();
		return -4;//����ֵ-4
	}
	else
	{
		printf("�����ɹ�\n");
	}
	//�ȴ��ͻ�������
	while (1)
	{
		clientsocket[count] = accept(serverSocket, (sockaddr*)&cAddr, &len);
		if (SOCKET_ERROR == clientsocket[count])
		{
			printf("������崻�\n");
			closesocket(serverSocket);
			WSACleanup();
			return -5;//����ֵ-5
		}
	
	printf("�пͻ������ӷ�������%s!\n", inet_ntoa(cAddr.sin_addr));//inet_ntoa>������IPת�����ַ�����
	CreateThread(NULL, NULL,(LPTHREAD_START_ROUTINE)communicate, (char*)count,NULL, NULL);
	count++;

	}
	
	return 0;
}