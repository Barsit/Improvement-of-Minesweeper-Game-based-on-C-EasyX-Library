/*��Ŀ��飺ɨ����Ϸ�����ϰ���Ľ�
* ���ߣ���������������������
* ʱ�䣺2021��2��4��14:09:56
*
����Ҫ��:

��������������е�ɨ�״�����ο�����Ҳ�Կ���һ���µ�ɨ�ס�

����Ŀֻ����windows'������Ӧ�ó���Ҫ����win10 ���ܹ���������

��򿪳���,�˵���Ӧ��������ѡ��:��ʼ��Ϸ,����ս��,���а��趨��

�����趨�У�����������Ϸ�Ѷ�,�Լ��༭��ǰ���������

����ҿ��������а��в鿴���е�ɨ��������(�����Ѷ�ǰʮ�����ɣ� ��ʾ��ҵ�id, ip,ʱ��)

����Ϸ�Ѷȷ�Ϊ�򵥣���ͨ���������֣����Ѷȵ�ͼΪ8x8,�ں�10����;��ͨ�Ѷȵ�ͼΪ16x16,40����;�����Ѷ�16x30, 99����

�񱾻�ս��,�ڱ��ؼ�¼ͨ�ؼ�¼,��ҿ���ʱ�̲鿴�����ɼ���

* �������裺
* 1.��ͼ���ã�
* 2.���ƽ��棻
* 3.��������
* 4.���ף�
* 5.�ж���Ӯ��
* 6.������֡�
*/

#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"ws2_32.lib")


//��ҽṹ��
struct player
{
	char id[20] = "visitor";
	char time[20] = "000";
}now;

//���ݴ���ṹ��
struct  message
{
	char item[20];
	char time[20];
	char name[20];
	char ip[50];

}now2[30];


//������µĳ���
struct prompt
{
	int x;
	int y;
	int num[2][40];//����ÿ�С�ÿ���׵�����
}prompt;

//#define Row 8   //��
//#define Col 8   //��
#define Size 35//ͼƬ��С
int map[40][40];
//ͼƬ��������
IMAGE img[12];
//�ж���Ӯ��־
int flag = 0;
int mark1 = 8;
int mark2 = 8;
int Mine = 10;//�û��ж���Ϸģʽ
int sec=0;//��ʱ
int sec2 = 0;//��ȡ��ͣ�뻽�ѵ�ʱ���
int t1, t2, t3, t4;//ǧλ����λ��ʮλ����λ
HANDLE h1;
int get = 0;//����mouse_control����ֵ
SOCKET clientSocket;//�ͻ���socket
int count = 0;//����ͼ�ν��滻��
int mark = 0;//������ͣ�����ѱ��
time_t time1, time2;//��ȡ����ʱ��
time_t time3, time4;//��ͣ������ʱ��ȡ����ʱ��


int calculagraph(int Row, int Col);
void start();
void run(int Row, int Col, int Mine);
int Mouse_Control(int Row,int Col);
void Game_Draw(int Row, int Col);
void save(char filename[]);
void setting_menu();
void Prompt(int Row, int Col);


//���̼߳�ʱ
DWORD WINAPI work(LPVOID IParam)
{
	if (calculagraph(mark1, mark2) == 0)
		return 0;
}

//ͨ�Ŷ��߳�
int client()
{
	//����汾Э��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		//printf("��汾Э��ʧ��\n");
		return -1;//����ֵ-1
	}
	else
		//printf("����汾Э��ɹ�\n");
	//����socket
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == clientSocket)
	{
		//printf("����socketʧ��\n");
		WSACleanup();
		return -2;//����ֵ-2
	}
	else
	{
		//printf("����socket�ɹ�\n");

	}
	//��ȡЭ���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.0.105");
	addr.sin_port = htons(10086);//����ѡ10000����
	//���ӷ�����
	int c = connect(clientSocket, (sockaddr*)&addr, sizeof addr);
	if (SOCKET_ERROR == c)
	{
		//printf("���ӷ�����ʧ��\n");
		WSACleanup();
		return -3;//����ֵ-3
	}
	else
	{
		//printf("���ӷ������ɹ�\n");

	}
	//ͨ��
	int r;
	char recvBuff[1024 * 2];
	while (1)
	{
		r = recv(clientSocket, recvBuff, 1024 * 2 - 1, NULL);//���շ�������Ϣ
		if (r > 0)
		{
			recvBuff[r] = '\0';
			FILE* fp;
			fp = fopen("mcs.txt", "w");
			if (fp == NULL)
			{
				//printf("�ļ�mcs.txt�޷���!\n");
				exit(0);
			}
			else
			{
				//printf("%s", recvBuff);
				fprintf(fp, "%s", recvBuff);
			}
			fclose(fp);
			strcpy(recvBuff, "");
		}
	}
}

//��ʱ����
int calculagraph(int Row, int Col)
{
	int i;
	IMAGE number[10];//��ʱ��ͼƬ
	for (i = 0; i < 10; i++)
	{
		char file[50] = " ";
		sprintf(file, "./%d.jpg", i);
		loadimage(&number[i], file);
	}
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	time(&time1);
	
	while (1)
	{
		cleardevice();
		time(&time2);
		sec = time2 - time1-sec2;
		t1 = sec / 1000 % 10;
		t2 = sec / 100 % 10;
		t3 = sec / 10 % 10;
		t4 = sec % 10;
		putimage(0, Row * Size, &number[t1]);
		putimage(35, Row * Size, &number[t2]);
		putimage(70, Row * Size, &number[t3]);
		putimage(105, Row * Size, &number[t4]);
		settextcolor(RGB(0, 255, 0));
		Sleep(1000);
		FlushBatchDraw();
		if (get < 0)
			return 0;
	}
	EndBatchDraw();
}

//������µĳ���
void Prompt(int Row, int Col)
{
	int count = 0;//ͳ���С�������Ŀ
	char get1[50] = "";
	char get2[50] = "";//�����׵���Ŀ,���ӳ�һ���ַ���
	char get3[50] = "";
	char get4[50] = "";//�����׵���Ŀ
	BeginBatchDraw();
	setbkmode(TRANSPARENT);
	//��������
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (map[i][j] == 19 || map[i][j] == -1||map[i][j]==39)
			{
				count++;
			}
		}
		prompt.num[0][i] = count;
		count = 0;
	}
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (map[j][i] == 19 || map[j][i] == -1||map[j][i]==39)
			{
				count++;
			}
		}
		prompt.num[1][i] = count;
		count = 0;
	}
	for (int i = 0; i < Row; i++)
	{
		sprintf(get3, "%d", prompt.num[0][i]);
		strcat(get1, get3);
		strcat(get1, " ");
		sprintf(get4, "%d", prompt.num[1][i]);
		strcat(get2, get4);
		strcat(get2, " ");
	}
	prompt.x = Row * Size / 2+35;
	prompt.y = Col * Size;
	outtextxy(prompt.x, prompt.y, get1);
	outtextxy(prompt.x, prompt.y + 15, get2);
	FlushBatchDraw();
	EndBatchDraw();

 }

//��ʼ����Ϸ
void Init_Game(int Row, int Col, int Mine)
{
	
	//�������� alias ȡ���� repeat �ظ�����
	mciSendString("close BGM", 0, 0, 0);
	mciSendString("open ./all.mp3  alias BGM ", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	//�����������
	srand((unsigned)time(NULL));


	//��ʼ������
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			map[i][j] = 0;
		}
	}

	//0��ʾ�ո�-1��ʾ��
	for (int i = 0; i < Mine;)
	{
		int r = rand() % Row;
		int c = rand() % Col;
		//�����׵�����
		if (map[r][c] == 0)
		{
			map[r][c] = -1;
			i++;
		}

	}
	//����Χ�ո�+1
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (map[i][j] == -1)
			{
				//��������Χ
				for (int m = i - 1; m <= i + 1; m++)
				{
					for (int n = j - 1; n <= j + 1; n++)
					{
						if ((m >= 0 && m <= Row - 1 && n >= 0 && n <= Col - 1) && map[m][n] != -1)
						{
							map[m][n]++;
						}

					}
				}
			}
		}
	}

	int i;//ɨ�׽���ͼƬ������
	for (i = 0; i < 12; i++)
	{
		char file[50] = " ";
		sprintf(file, "./image/%d.jpg", i);
		loadimage(&img[i], file);
	}
	//���ܸ���
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			map[i][j] += 20;
		}
	}

}


//����̨����չʾ
void Show(int Row, int Col)
{

	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			printf("%2d  ", map[i][j]);
		}
		putchar('\n');
	}
	system("cls");//����̨����
}

//��ͼ
void Game_Draw(int Row, int Col)
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			if (map[i][j] < 0)
			{
				putimage(j * (Size), i * (Size), &img[9]);//jΪ�����꣬iΪ������
			}
			else if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * (Size), i * (Size), &img[map[i][j]]);
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28)
			{
				putimage(j * Size, i * Size, &img[10]);
			}
			else if (map[i][j] > 30)//���
			{
				putimage(j * Size, i * Size, &img[11]);
			}
		}
	}
	IMAGE stop;
	loadimage(&stop, "./stop.jpg");
	putimage(Col * Size / 2, Row * Size, &stop);

	
}


//������
int Mouse_Control(int Row,int Col)
{
	void Open_Null(int row, int col);
	if (MouseHit())//�ж���û��������
	{
		MOUSEMSG msg = GetMouseMsg();
		int row = msg.y / Size;//�����λ��ת��Ϊ�����±�
		int col = msg.x / Size;
		//�����Ϣ�ַ�
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN://������
			if (map[row][col] > 8)
			{
				mciSendString("close CLICK", 0, 0, 0);
				mciSendString("open ./click.wav  alias CLICK ", 0, 0, 0);
				mciSendString("play CLICK", 0, 0, 0);
				if (map[row][col] < 30)
				{
					map[row][col] -= 20;
				}
				if (map[row][col] > 30)
				{
					map[row][col] -= 20;
				}
				Open_Null(row, col);
				flag++;

			}
			if (msg.x >= Col * Size/2&& msg.x <= Col * Size / 2+35 && msg.y > Row * Size)
			{
				SuspendThread(h1);
				time(&time3);//��ͣʱ��ȡ����ʱ��
				mark = 1;
				while (mark == 1)
				{
					if (MouseHit())
					{
						MOUSEMSG msg2 = GetMouseMsg();
						switch (msg2.uMsg)
						{
						case WM_LBUTTONDOWN://������
							if (msg.x >= Col * Size / 2 && msg.x <= Col * Size / 2 + 35 && msg.y > Row * Size)
							{
								ResumeThread(h1);
								time(&time4);//����ʱ��ȡ����ʱ��
								sec2 += (time4 - time3);
								mark = 0;
							}
							break;
						case WM_RBUTTONDOWN:
							break;
						}
					}
					
				}
			}
			break;
		case WM_RBUTTONDOWN://����Ҽ�
			if (map[row][col] > 8 && map[row][col] <= 29)
			{
				mciSendString("close MARK", 0, 0, 0);
				mciSendString("open ./mark.mp3  alias MARK ", 0, 0, 0);
				mciSendString("play MARK", 0, 0, 0);
				map[row][col] += 20;
			}
			else if (map[row][col] > 30)
			{
				map[row][col] -= 20;
			}
			break;
		}

		return map[row][col];


	}
}

//�򿪿հ�
void Open_Null(int row, int col)
{
	if (map[row][col] == 0)
	{
		//�����հ���Χ
		for (int m = row - 1; m <= row + 1; m++)
		{
			for (int n = col - 1; n <= col + 1; n++)
			{
				if ((m >= 0 && m <= 29 && n >= 0 && n <= 29) &&//16*16 16*32�޷��򿪿ո���Χ�����ڴ��޸�
					(map[m][n] == 0 || map[m][n] != 19) &&
					map[m][n] > 8)//��Խ�硢�����ס�δ��
				{
					{
						if (map[m][n] < 30)
						{
							map[m][n] -= 20;
						}
						if (map[m][n] > 30)
						{
							map[m][n] -= 40;
						}
						Open_Null(m, n);
						flag++;
					}
				}
			}
		}

	}
}

void Judge(int row, int col, int Mine)
{
	void start();

	get = Mouse_Control(mark1,mark2);
	if (get== -1)
	{

		mciSendString("close BOMP", 0, 0, 0);
		mciSendString("open ./bomp.wav  alias BOMP ", 0, 0, 0);
		mciSendString("play BOMP", 0, 0, 0);
		for (int i = 0; i < row; i++)//��������
		{
			for (int j = 0; j < col; j++)
			{
				if (map[i][j] == 19)
				{
					map[i][j] -= 20;
				}
				if (map[i][j] == 39)
				{
					map[i][j] -= 40;
				}
			}
		}
		Game_Draw(row, col);

		int isok = MessageBox(GetHWnd(), "�����ˣ��Ƿ�����һ��", "��ʾ", MB_OKCANCEL);
		if (IDOK == isok)
		{
			flag = 0;
			t1 = 0;
			t2 = 0;
			t3 = 0;
			t4 = 0;
			run(mark1, mark2, Mine);
		
		}
		else
		{
			exit(789);
		}
		mciSendString("close BGM", 0, 0, 0);
	}
	if (flag == row * col - Mine)
	{
		get = -2;
		int isok = MessageBox(GetHWnd(), "��Ӯ�ˣ������ѱ��棬�Ƿ�����һ��", "��ʾ", MB_OKCANCEL);
		if (mark2==8)
		{
			char filename8[20] = "mc8.txt";
			save(filename8);
		}
		if (mark2 == 16)
		{
			char filename16[20] = "mc16.txt";
			save(filename16);

		}
		if (mark2 == 32)
		{
			char filename32[20] = "mc32.txt";
			save(filename32);

		}
		char buff[1024];
		memset(buff, 0, 1024);
		sprintf(buff, "%d", mark2);
		strcat(buff, "   ");
		strcat(buff, now.time);
		strcat(buff, "   ");
		strcat(buff, now.id);
		send(clientSocket, buff, strlen(buff), NULL);

		if (IDOK == isok)
		{
			flag = 0;
			t1 = 0;
			t2 = 0;
			t3 = 0;
			t4 = 0;
			run(mark1, mark2, Mine);
		}
		else
		{
			start();
		}
		mciSendString("close BGM", 0, 0, 0);
	}

}
void save(char filename[])
{
	FILE* fp;
	sprintf(now.time, "%d", sec);
	fp = fopen(filename, "a");
	if (fp == NULL)
	{
		printf("�ļ��޷���!\n");
		exit(0);
	}
	else
		fprintf(fp, "%s\t%s\n", now.id, now.time);
	fclose(fp);

}
void ShowGrade()
{
	cleardevice();
	initgraph(320, 480, NULL);
	FILE* fp8,*fp16,*fp32;
	int y=75;//����
	IMAGE grade;//�����ɼ�����
	loadimage(&grade, "./grade.jpg");
	BeginBatchDraw();
	putimage(0, 0, &grade);
	setbkmode(TRANSPARENT);

	fp8 = fopen("mc8.txt", "r");
	if (fp8 == NULL)
	{
		printf("�ļ��޷���!\n");
		exit(0);
	}
	outtextxy(10, y, "8*8");
	y += 20;
	while (!feof(fp8))
	{
		fscanf(fp8, "%s%s", now.id, now.time);//ȫ�����ַ�����ȡ���Ƿ���������
		outtextxy(35, y, now.id);
		outtextxy(200, y, now.time);
		y += 20;

	}
	fclose(fp8);

	fp16 = fopen("mc16.txt", "r");
	if (fp16 == NULL)
	{
		printf("�ļ��޷���!\n");
		exit(0);
	}
	outtextxy(10, y, "16*16");
	y += 20;
	while (!feof(fp16))
	{
		fscanf(fp16, "%s%s", now.id, now.time);//ȫ�����ַ�����ȡ���Ƿ���������
		outtextxy(35, y, now.id);
		outtextxy(200, y, now.time);
		y += 20;

	}
	fclose(fp16);

	fp32 = fopen("mc32.txt", "r");
	if (fp32 == NULL)
	{
		printf("�ļ��޷���!\n");
		exit(0);
	}
	outtextxy(10, y, "16*32");
	y += 20;
	while (!feof(fp32))
	{
		fscanf(fp32, "%s%s", now.id, now.time);//ȫ�����ַ�����ȡ���Ƿ���������
		outtextxy(35, y, now.id);
		outtextxy(200, y, now.time);
		y += 20;

	}
	FlushBatchDraw();
	fclose(fp32);


	while (1)
	{
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			printf("%d %d\n", msg.x, msg.y);
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 0 && msg.x <= 320 && msg.y >= 400 && msg.y <= 480)
				{
					start();
				}
				break;
			case WM_RBUTTONDOWN:
				break;
			}
		}
	}
	EndBatchDraw();
	getchar();
	closegraph();
}

void Leaderboard()
{
	int y1, y2, y3;
	int mark=0;//�ϰ���
	y1=y2=y3= 90;
	cleardevice();
	initgraph(640, 480, NULL);
	IMAGE lboard;
	loadimage(&lboard, "./lboard.jpg");
	putimage(0, 0, &lboard);
	setbkmode(TRANSPARENT);
	BeginBatchDraw();
	FILE* fp;
	fp = fopen("mcs.txt", "r");
	if (fp == NULL)
	{
		printf("�ļ�mcs.txt�޷���!\n");
		exit(0);
	}
	else
	{
		for(int i=0;i<30;i++)
		{
			fscanf(fp, "%s%s%s%s", now2[i].item, now2[i].time, now2[i].name, now2[i].ip);
			if (now2[i].item[0] == '8')
			{
				if (strcmp(now2[i].name, now.id) == 0)
				{
					settextcolor(RED);
					mark = 1;
				}
				else
				{
					settextcolor(WHITE);
				}
				outtextxy(1, y1, now2[i].time);
				outtextxy(25, y1, now2[i].name);
				outtextxy(95, y1, now2[i].ip);
				y1 += 20;
			}
			if (now2[i].item[0] == '1')
			{
				if (strcmp(now2[i].name, now.id) == 0)
				{
					settextcolor(RED);
					mark = 1;
				}
				else
				{
					settextcolor(WHITE);
					
				}
				outtextxy(201, y2, now2[i].time);
				outtextxy(230, y2, now2[i].name);
				outtextxy(295, y2, now2[i].ip);
				y2 += 20;
			}
			if (now2[i].item[0] == '3')
			{
				if (strcmp(now2[i].name, now.id) == 0)
				{
					settextcolor(RED);	
					mark = 1;
				}
				else
				{
					settextcolor(WHITE);
				}
				outtextxy(401, y3, now2[i].time);
				outtextxy(435, y3, now2[i].name);
				outtextxy(495, y3, now2[i].ip);
				y3 += 20;
			}
		}
		if (mark == 1)
		{
			outtextxy(250, 400, "�����ϰ�");
		}
		else
		{
			outtextxy(250, 400, "��δ�ϰ�");
		}
		FlushBatchDraw();
	}
	fclose(fp);

	while (1)
	{
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			printf("%d %d\n", msg.x, msg.y);
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 0 && msg.x <= 640 && msg.y >= 400 && msg.y <= 480)
				{
					start();
				}
				break;
			case WM_RBUTTONDOWN:
				break;
			}
		}
	}
	EndBatchDraw();
	getchar();
	closegraph();
}

//��������
void run(int Row, int Col, int Mine)
{

	h1 = CreateThread(NULL, 0, work, NULL, 0, NULL);
	initgraph(Col * Size, Row * Size + 35, SHOWCONSOLE);//ͼƬ�޷������ڴ˽��
	Init_Game(Row, Col, Mine);
	BeginBatchDraw();

	while (1)
	{
		//Show(Row, Col);
		Game_Draw(Row, Col);
		Prompt(Row, Col);
		Judge(Row, Col, Mine);
		FlushBatchDraw();

	}
	EndBatchDraw();
	getchar();
	closegraph();
	
}


void setting_menu()
{
	cleardevice();
	char get1[10], get2[10], get3[10];//�����û��Զ���ģʽ
	void start();
	IMAGE Set;
	loadimage(&Set, "./BK.jpg");
	BeginBatchDraw();
	
	putimage(0, 0, &Set);
	FlushBatchDraw();
	while (1)
	{
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 200 && msg.x <= 235 && msg.y >= 20 && msg.y <= 135)
				{
					mark1 = 8;
					mark2 = 8;
					Mine = 10;
					start();
				}
				else if (msg.x >= 300 && msg.x <= 325 && msg.y >= 20 && msg.y <= 135)
				{
					mark1 = 16;
					mark2 = 16;
					Mine = 40;
					start();
				}
				else if (msg.x >= 375 && msg.x <= 410 && msg.y >= 20 && msg.y <= 135)
				{
					mark1 = 16;
					mark2 = 30;
					Mine = 99;
					start();
				}
				else if (msg.x >= 455 && msg.x <= 485 && msg.y >= 20 && msg.y <= 175)
				{
					InputBox(now.id, 100, "���������ƣ�");//�Ự������û�ID����
					start();

				}
				else if (msg.x > 0 && msg.y > 450)
				{
					InputBox(get1, 100, "����������(<=32)��");
					InputBox(get2, 100, "�������ݸ���(<=32)��");
					InputBox(get3, 100, "�������׵�������");
					if (atoi(get1) * atoi(get2) > atoi(get3)&& atoi(get1)<=32&& atoi(get2)<=32)
					{
						mark1 = atoi(get1);
						mark2 = atoi(get2);
						Mine = atoi(get3);
					}
					start();
				}
				break;

			case WM_RBUTTONDOWN:
				break;
			}
		}
	}
	EndBatchDraw();
}

void start()
{
	IMAGE BK;//����ͼƬ
	initgraph(640, 480, NULL);
	loadimage(&BK, "./start.jpg");
	cleardevice();
	BeginBatchDraw();
	putimage(0, 0, &BK);
	outtextxy(2, 0, "ID:");
	outtextxy(20, 0, now.id);

	while (1)
	{
		FlushBatchDraw();
		if (MouseHit)
		{
			MOUSEMSG msg = GetMouseMsg();
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 35 && msg.x <= 180 && msg.y >= 30 && msg.y <= 60)
				{
                    run(mark1, mark2, Mine);
				}
				else if (msg.x >= 35 && msg.x <= 180 && msg.y >= 90 && msg.y <= 120)
				{
					ShowGrade();
				}
				else if (msg.x >= 35 && msg.x <= 180 && msg.y >= 150 && msg.y <= 180)
				{
					Leaderboard();
				}
				else if (msg.x >= 35 && msg.x <= 130 && msg.y >= 200 && msg.y <= 230)
				{
					setting_menu();
				}
				break;
			case WM_RBUTTONDOWN:
				break;

			}

		}
		
	}
	EndBatchDraw();
	getchar();
	closegraph();
}

int main()
{
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client, NULL, NULL, NULL);//���̳߳�������
	start();
	return 0;

}