#pragma once
#include <iostream>
#include "room.hpp"
#include "Identity.hpp"
#include "order.hpp"
#include <vector>
using namespace std;


class teacher:public Identity
{
public:
	teacher(){}
	teacher(int id, string name, string pwd)
	{
		this->m_id = id;
		this->m_Name = name;
		this->m_Pwd = pwd;
	}
	//��ʾ��ʦ��¼��Ľ���
	void operMenu()
	{
		cout << this->m_Name << " ��ʦ,��ã�" << endl;
		cout << "1. ��ѯԤԼ     2. ���ԤԼ" << endl;
		cout << "0. �˳�" << endl;
	}
	void show_Order()
	{
		order ord;
		if (ord.m_size == 0)
		{
			cout << "��ԤԼ��¼!" << endl;
			system("pause");
			system("cls");
			return;
		}
		for (int i = 0; i < ord.m_size; i++)
		{
			
			cout << "ԤԼ���ڣ���" << ord.m_order[i]["����"] << "  " << "ԤԼʱ��Σ�" << (ord.m_order[i]["ʱ���"] == "1" ? "����" : "����") << "  " << "ѧ������:" << ord.m_order[i]["ѧ������"] << "\t" << "ѧ��ѧ��:" << ord.m_order[i]["ѧ��ѧ��"] << "  " << "ԤԼ�����ţ�" << ord.m_order[i]["������"] << "  ";
				string status = "ԤԼ״̬: ";
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
		system("pause");
		system("cls");

	}
	void validOrder()
	{
		order ord;
		if (ord.m_size == 0)
		{
			cout << "��ԤԼ��¼��" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "����˵ļ�¼���£�" << endl;
		vector<int>v;  //�������������е��±���
		int index = 1;
		for (int i = 0; i < ord.m_size; i++)
		{

			if (ord.m_order[i]["ԤԼ״̬"] == "1")
			{
				v.push_back(i);
				cout << index++ << ". " << "ԤԼ���ڣ���" << ord.m_order[i]["����"] << "  ʱ��Σ�" << (ord.m_order[i]["ʱ���"] == "1" ? "����" : "����") << "  ������ţ�" << ord.m_order[i]["������"] << "  " << "ѧ������:" << ord.m_order[i]["ѧ������"] << "\t" << "ѧ��ѧ��:" << ord.m_order[i]["ѧ��ѧ��"] << "  ";
				string status = "ԤԼ״̬��";
				if (ord.m_order[i]["ԤԼ״̬"] == "1")
				{
					status += "�����";
				}
				cout << status << endl;
			}
		}
		cout << "������Ҫ��˵ļ�¼��" << endl;
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
					ord.m_order[v[select - 1]]["ԤԼ״̬"] = "2";
					ord.updateOrder();
					cout << "��˳ɹ���" << endl;
					break;
				}
			}
			cout << "���������������룺";
		}
		system("pause");
		system("cls");
	}
	~teacher(){}
	int m_id;
};