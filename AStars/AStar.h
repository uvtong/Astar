/***********************************************************************************/
/* ��ͼ�趨��0��ʾ��ͨ��1��ʾ�ϰ����ͼ��б���ƶ��� ��������б�����������֮һ���ϰ� 
/* ���򲻿�б���ƶ��������������ƶ��������ҷ������·�����֮һ���ϰ��򲻿��������ƶ���                              
/***********************************************************************************/
#pragma once
#include <memory>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <vector>


struct AstarPOINT
{
	int x, y;
};
typedef std::vector<AstarPOINT> PointList;
/*
Python lists have quite a bit more functionality than C++ vectors. vector_indexing_suite defines contains method among others, so your container class has to define operator==.
*/
inline bool operator == (const AstarPOINT& a, const AstarPOINT& b)
{
	return a.x == b.x && a.y == b.y;
}

typedef std::vector<int> IntList;
typedef std::vector<float> FloatList;
typedef std::vector<unsigned char> ByteList;

#define W_H_MOVE       10 //ˮƽ����ֱ�ƶ�һ��Ļ���
#define SLANTMOVE      14 //б���ƶ������ŶԽ����ƶ�����һ��Ļ���
#define MAXNODECOUNT   1024 //�����б��ɱ�������ڵ���



//���ڱ���ڵ���Ϣ
struct NodeInfo 
{
	int m_NodeID;        //�ڵ�ID
	bool m_InOpenList;   //�Ƿ��ڿ����б��У�trueΪ�ڿ����б��У�false���ڿ����б���
	bool m_InCloseList;  //�Ƿ��ڹر��б��У�true�ڹر��б���false���ڹر��б�
};

//���ڱ���ڵ�����
struct Node
{
	AstarPOINT m_Pos;             //�ڵ�����
	int m_ScoreF;        //�ڵ�·������
	int m_ScoreG;        //�ڵ㵽��ʼ���·������
	int m_FatherID;      //�ڵ�ĸ��ڵ�ID
	//bool m_InOpenList;   //�Ƿ��ڿ����б��У�trueΪ�ڿ����б��У�false���ڿ����б���
	//bool m_InCloseList;  //�Ƿ��ڹر��б��У�true�ڹر��б���false���ڹر��б�
};




class AStar
{
public:
	AStar();
	~AStar();

	void Init(IntList Map, int w, int h); //����

	//���ܣ�Ѱ·
	//������xBegin������ʼ��X���� yBegin������ʼ��Y����
	//      xEnd�����յ�X����     yEnd�����յ�Y����
	//����:
	void Find(int xBegin, int yBegin, int xEnd, int yEnd); 

	//���ܣ�Ϊ�ڵ������뿪���б����
	//������Point�����ڵ����� ScoreF�����ڵ�·������ 
	//      ScoreG�����ڵ㵽���·������ FatherID�����ڵ�ĸ��ڵ�ID
	//���أ�
	void OpenNote(AstarPOINT Point, int ScoreF, int ScoreG,int FatherID);

	//���ܣ�Ϊ�ڵ�������ر��б����
	//������ID����Ҫ����ǵĽڵ�ID
	//���أ�
	void CloseNote(int ID);
	
	//���ܣ��¼��뿪���б����޸�·�����ֺ�Զ���ѽ�������ʹ��Fֵ��С�Ľڵ��ID����ǰ��
	//������Index�����޸Ļ��¼���ڵ�ID��m_OpenList������
	//���أ�
	void HeapAheadSort(int Index);
	
	//���ܣ��ӿ����б���ȡ��Fֵ��С�ڵ��ID��Զ���ѽ�������ʹ��Fֵ��С�Ľڵ��ID����ǰ��
	//������
	//���أ�
	void HeapBackSort();

	//���ܣ��ж��ڵ��Ƿ��ڿ����б���
	//������Point����Ҫ�ж��ڵ�����
	//���أ�true�����ڿ����б� false��������
	bool IsInOpenList(AstarPOINT Point);

	//���ܣ��ж��ڵ��Ƿ��ڹر��б���
	//������Point����Ҫ�ж��ڵ�����
	//���أ�true�����ڿ����б� false��������
	bool IsInCloseList(AstarPOINT Point);
	
	//���ܣ���ýڵ����Χ��ͨ���ڵ�
	//������Point�����ڵ����� AroundNode�������ڱ�����Χ�ڵ�����
	//���أ�
	void GetAroundNode(AstarPOINT Point,PointList* AroundNode);

	//���ܣ����ĳID�ڵ���OpenList������
	//������ID����Ҫ�õ������Ľڵ�ID
	//���أ��ڵ�����ֵ
	int GetIndex(int ID);

	//���ܣ���·������������m_Path��
	//������Point����������� ID�����յ�ID
	//���أ�
	void  GetPath(AstarPOINT Point,int ID);

	//void Cout();

	PointList GetAstarPath()
	{
		return m_Path;
	}

	bool IsOpen(AstarPOINT Point)
	{
		return m_Map[Point.y][Point.x] == 0;
	}


	/*void Text()
	{
		for (int i = 0; i < m_H; i++)
		{
			for (int j = 0; j < m_W; j++)
			{
				std::cout<<m_Map[i][j]<<"  ";
			}
			std::cout<<std::endl;
		}
	}*/
	


private:
	int m_OpenList[MAXNODECOUNT];         //�����б���������Ż���������Žڵ��ID��Fֵ��С��������ǰ��
	int m_OpenCount;                      //�����б���ǰ�Ľڵ���Ŀ  
	int m_OpenID;                         //ÿ��Ϊ���뿪���б��Ľڵ����һ��Ψһ��ID
	Node* m_Node;                         //����ÿ������������б��Ľڵ㣬IDΪ������ֵ
	NodeInfo** m_NodeInfo;                //��ָ�����ڱ����ͼ�ڵ����Ϣ���ýڵ������������ɵõ��ڵ���Ϣ
	int** m_Map;                          //��ͼָ��  
	int m_W, m_H;                          //��ͼ����
	PointList m_Path;              //����·������
};