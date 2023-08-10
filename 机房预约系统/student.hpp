#pragma once
#include <iostream>
#include <string>
#include "room.hpp"
#include "Identity.hpp"
#include "order.hpp"
#include <vector>
using namespace std;
class student:public Identity
{
public:
	
	student()
	{}
	student(int id, string name, string pwd)
	{
		this->m_id = id;
		this->m_Name = name;
		this->m_Pwd = pwd;
		this->initRoom();
	}
	//��ʾѧ����¼��Ľ���
	void operMenu()
	{
		cout << this->m_Name << " ͬѧ,��ã�" << endl;
		cout << "1. ԤԼ����    2. ��ѯԤԼ " << endl;
		cout << "3. ɾ��ԤԼ" << endl;
		cout << "0. �˳�" << endl;
	}
	void show_sOrder()
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
			if (this->m_id == atoi(ord.m_order[i]["ѧ��ѧ��"].c_str())) //����c���Խ�stringתΪint����
			{
				cout << "ԤԼ���ڣ���" << ord.m_order[i]["����"] << "  " << "ԤԼʱ��Σ�" << (ord.m_order[i]["ʱ���"] == "1" ? "����" : "����") << "  " << "ԤԼ�����ţ�" << ord.m_order[i]["������"] << "  ";
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

		}
		system("pause");
		system("cls");

	}
	
	void applyOrder()
	{
		cout << "ѡ�����ԤԼ���ڣ�" << endl;
		cout << "1.��һ      2.�ܶ�" << endl;
		cout << "3.����      4.����" << endl;
		cout << "5.����" << endl;
		int date, time, place;
		cin >> date;
		cout << "��ѡ��ʱ�䣺" << endl;
		cout << "1.����  2.����" << endl;
		cin >> time;
		cout << "��ѡ������ţ�" << endl;
		for (int i = 0; i < v3.size(); i++)
		{
			cout << v3[i].RoomId << " �Ż�������Ϊ��" << v3[i].RoomMax << endl;
		}
		cin >> place;
		cout << "ԤԼ�ɹ����ȴ���ˡ�" << endl;
		ofstream ofs(ORDER_FILE, ios::app);
		ofs << "����:" << date << "  " << "ʱ���:" << time << "  " << "������:" << place << "  " << "ѧ������:" << this->m_Name << "\t" << "ѧ��ѧ��:" << this->m_id << "  " << "ԤԼ״̬:" << 1 << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	void delete_sOrder()
	{
		order ord;
		if (ord.m_size == 0)
		{
			cout << "��ԤԼ��¼" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "����ȡ����ԤԼ���£�" << endl;
		vector<int>v;  //�������������е��±���
		int index = 1;
		for (int i = 0; i < ord.m_size; i++)
		{
			//���ж��Ƿ�����ѧ��
			if (this->m_id == atoi(ord.m_order[i]["ѧ��ѧ��"].c_str()))
			{
				if (ord.m_order[i]["ԤԼ״̬"] == "1" || ord.m_order[i]["ԤԼ״̬"] == "2")
				{
					v.push_back(i);
					cout << index++ << ". " << "ԤԼ���ڣ���" << ord.m_order[i]["����"] << "  ʱ��Σ�" << (ord.m_order[i]["ʱ���"] == "1" ? "����" : "����") << "  ������ţ�" << ord.m_order[i]["������"] << "  ";
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
	void initRoom()
	{
		v3.clear();
		ifstream ifs;
		ifs.open(COMPUTER_FILE, ios::in);
		while (ifs >> r.RoomId && ifs >> r.RoomMax)
		{
			v3.push_back(r);
		}
		ifs.close();
	}
	room r;
	~student(){}
	int m_id;
	vector<room>v3;
};