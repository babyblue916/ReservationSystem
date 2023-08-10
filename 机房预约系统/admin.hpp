#pragma once
#include <iostream>
#include "room.hpp"
#include "Identity.hpp"
#include "all.hpp"
#include <fstream>
#include <vector>
#include "teacher.hpp"
#include "student.hpp"
#include <algorithm>
#include <string>
#include "order.hpp"

using namespace std;

class admin:public Identity
{
public:
	admin(){}
	//��ʼ������Ա��Ϣ
	admin(string name, string pwd)
	{
		this->m_Name = name;
		this->m_Pwd = pwd;
		this->initVector();  //��ʼ����ʦ��ѧ������
		this->initRoom();  //��ʼ����������
	}
	//��ʾ����Ա��¼��Ľ���
	void operMenu()
	{
		cout << "����Ա ��ã�" << endl;
		cout << "1. ����˺�      2. ��ѯ��Ϣ " << endl;
		cout << "3. ������Ϣ      4. ���ԤԼ" << endl;
		cout << "5. ɾ��ԤԼ      0. �˳�" << endl;
	}

	void showInfo()
	{
		cout << "�����ǿ��ŵĻ�����Ϣ��" << endl;
		for (vector<room>::iterator it = v3.begin(); it != v3.end(); it++)
		{
			cout << "������ţ�" << it->RoomId << "\t" << "����������" << it->RoomMax << "\t" << endl;
		}
		system("pause");
		system("cls");
	}
	void add()   //�����Ա��Ϣ
	{
		cout << "��ѡ��Ҫ��ӵ����ͣ�" << endl;
		cout << "1. ѧ��      2. ��ʦ" << endl;
		string filename;
		string tip;
		string errortip;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			filename = STUDENT_FILE;
			tip = "������ѧ�ţ�";
			errortip = "ѧ���ظ������������룺";
		}
		else if (select == 2)
		{
			filename = TEACHER_FILE;
			tip = "������ְ���ţ�";
			errortip = "ְ�����ظ������������룺";

		}
		int id;
		cout << tip;
		while (true)
		{
			cin >> id;
			bool ret = this->checkRepeat(id, select);   //�жϴ������˺��Ƿ��ظ�
			if (ret)
			{
				cout << errortip << endl;
			}
			else
				break;
		}
		string name;
		string pwd;
		cout << "������������";
		cin >> name;
		cout << "���������룺";
		cin >> pwd;
		ofstream ofs(filename, ios::out | ios::app);
		ofs << id << "  " << name << "  " << pwd << endl;
		cout << "��ӳɹ���" << endl;
		system("pause");
		system("cls");
		ofs.close();
		this->initVector();  //��ʼ���������Ƚ������ھɵ���Ϣ��գ�������ӵ���Ա��Ϣ��ʼ����������
	}
	void deleteOrder()
	{
		cout << "����ȡ����ԤԼ���£�" << endl;
		vector<int>v;  //�������������е��±���
		int index = 1;
		order ord;
		for (int i = 0; i < ord.m_size; i++)
		{
			
				if (ord.m_order[i]["ԤԼ״̬"] == "1" || ord.m_order[i]["ԤԼ״̬"] == "2")
				{
					v.push_back(i);
					cout << index++ << ". " << "ԤԼ���ڣ���" << ord.m_order[i]["����"] << "  ʱ��Σ�" << (ord.m_order[i]["ʱ���"] == "1" ? "����" : "����") << "  ������ţ�" << ord.m_order[i]["������"] << "  " << "ѧ������:" << ord.m_order[i]["ѧ������"] << "\t" << "ѧ��ѧ��:" << ord.m_order[i]["ѧ��ѧ��"] << "  ";
					string status = "ԤԼ״̬��";
					if (ord.m_order[i]["ԤԼ״̬"] == "1")
					{
						status += "�����";
					}
					else if (ord.m_order[i]["ԤԼ״̬"] == "2")
					{
						status += "ԤԼ�ɹ�";
					}
					else if (ord.m_order[i]["ԤԼ״̬"] == "-1")
					{
						status += "���δͨ��";
					}
					else if (ord.m_order[i]["ԤԼ״̬"] == "0")
					{
						status += "ԤԼȡ��";
					}
					cout << status << endl;
				}
		}

		if (v.size() == 0)
		{
			cout << "ԤԼ��¼Ϊ�㣡" << endl;
			system("pause");
			system("cls");
			return;
		}

		cout << "��ѡ��Ҫȡ����ԤԼ��" << endl;
		cout << "����0Ϊȡ��������" << endl;
		int select = 0;
		while (true)
		{
			cin >> select;
			if (select >= 0 && select <= v.size())
			{
				if (select == 0)
					break;
				else
				{
					ord.m_order[v[select - 1]]["ԤԼ״̬"] = "0";
					ord.updateOrder();
					cout << "ԤԼȡ���ɹ���" << endl;
					break;
				}
			}
			cout << "���������������룺";
		}
		system("pause");
		system("cls");
	
	}
	void deleteAllOrder()
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "����ɹ���" << endl;
		system("pause");
		system("cls");
	}
// 	void printStudent(student &s)
// 	{
// 		cout << "ѧ�ţ�" << s.m_id << " ,����: " << s.m_Name << " ,���룺" << s.m_Pwd << endl;
// 	}
// 	void printTeacher(teacher &t)
// 	{
// 		cout << "ְ���ţ�" << t.m_id << " ,����: " << t.m_Name << " ,���룺" << t.m_Pwd << endl;
// 	}
	void maninfo()
	{
		cout << "��ѡ����Ҫ�鿴����Ա��Ϣ��" << endl;
		cout << "1. ѧ��        2. ��ʦ" << endl;
		int choose;
		cin >> choose;
		if (choose == 1)
		{
			cout << "ϵͳ��ѧ����Ϣ���£�" << endl;
			for (vector<student>::iterator it = v1.begin(); it != v1.end(); it++)
			{
				cout << "ѧ�ţ�" << it->m_id << "\t" << "����: " << it->m_Name << "\t" << "���룺" << it->m_Pwd << endl;
			}
		}
		else if (choose == 2)
		{
			cout << "ϵͳ����ʦ��Ϣ���£�" << endl;
			for (vector<teacher>::iterator it = v2.begin(); it != v2.end(); it++)
			{
				cout << "ְ���ţ�" << it->m_id << "\t" << "����: " << it->m_Name << "\t" << "���룺" << it->m_Pwd << endl;
			}
		}
		else
		{
			cout << "�������" << endl;
			system("pause");
			system("cls");
			return;
		}
		system("pause");
		system("cls");
	}

	void initVector()  //�򿪱���ѧ������ʦ��Ϣ��txt�ı������ı��ڵ�����ȫ���浽v1(ѧ��)��v2(��ʦ) �
	{
		ifstream ifs;
		ifs.open(STUDENT_FILE, ios::in);
		if (!ifs.is_open())  //���student.txt�ı��Ƿ����
		{
			cout << "�ļ������ڣ�" << endl;
			return;
		}
		v1.clear();  //�����������������
		v2.clear();  //ͬ��

		student s;   //����ѧ����Ķ���
		while (ifs >> s.m_id && ifs >> s.m_Name && ifs >> s.m_Pwd)
		{
			v1.push_back(s);
		}
		cout << "��ǰѧ������Ϊ��" << v1.size() << endl;
		ifs.close();

		teacher t;  //������ʦ��Ķ���
		ifs.open(TEACHER_FILE, ios::in);
		while (ifs >> t.m_id && ifs >> t.m_Name && ifs >> t.m_Pwd)
		{
			v2.push_back(t);
		}
		cout << "��ǰ��ʦ����Ϊ��" << v2.size() << endl;
		ifs.close();
	}

	void initRoom()
	{
		v3.clear();
		ifstream ifs;
		ifs.open(COMPUTER_FILE, ios::in);
		room r;
		while (ifs >> r.RoomId && ifs >> r.RoomMax)
		{
			v3.push_back(r);
		}
		ifs.close();
	}

	bool checkRepeat(int id, int type)  //�жϴ����˺������ѧ�Ż���ְ�����Ƿ��ظ�
	{
		if (type == 1)  //ѧ��
		{
			//����v1����,���v1�ڵ�m_id�������id��ͬ���򷵻�true�����ظ�
			for (vector<student>::iterator it = v1.begin(); it != v1.end(); it++)
			{
				if (id == it->m_id)
					return true;
			}
		}
		else if (type == 2)  //��ʦ
		{
			//����v2����,���v2�ڵ�m_id�������id��ͬ���򷵻�true�����ظ�
			for (vector<teacher>::iterator it = v2.begin(); it != v2.end(); it++)
			{
				if (id == it->m_id)
					return true;
			}
		}
	}


	
	~admin(){}  //����
	vector<room>v3;
	vector<student>v1;  //���ѧ����Ϣ������
	vector<teacher>v2;  //�����ʦ��Ϣ������
}; 
