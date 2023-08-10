#pragma once
#include <iostream>
#include <map>
#include <algorithm>
#include "all.hpp"
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class order
{
public:
	order()
	{
		ifstream ifs(ORDER_FILE, ios::in);
		string date;  //ԤԼ����
		string place;  //ԤԼ������
		string name; //ԤԼ������
		string id;  //ԤԼ��ѧ��
		string time;  //ԤԼʱ���
		string status; //ԤԼ״̬
		this->m_size = 0;  //��ʼ��¼����
		while (ifs >> date && ifs >> time && ifs >> place && ifs >> name && ifs >> id && ifs >> status)
		{
// 			cout << date << endl;
// 			cout << time << endl;
// 			cout << place << endl;
// 			cout << name << endl;
// 			cout << id << endl;
// 			cout << status << endl;
			string key, value;
			map<string, string>m;
			int pos = date.find(":");  //������
			if (pos != -1)
			{
				key = date.substr(0, pos);
				value = date.substr(pos + 1, date.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = time.find(":");  //������
			if (pos != -1)
			{
				key = time.substr(0, pos);
				value = time.substr(pos + 1, time.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = place.find(":");  //������
			if (pos != -1)
			{
				key = place.substr(0, pos);
				value = place.substr(pos + 1, place.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = name.find(":");  //������
			if (pos != -1)
			{
				key = name.substr(0, pos);
				value = name.substr(pos + 1, name.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = id.find(":");  //������
			if (pos != -1)
			{
				key = id.substr(0, pos);
				value = id.substr(pos + 1, id.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = status.find(":");  //������
			if (pos != -1)
			{
				key = status.substr(0, pos);
				value = status.substr(pos + 1, status.size() - pos - 1);
				m.insert(make_pair(key, value));
			}

			//��Сmap�������뵽���map��
			this->m_order.insert(make_pair(this->m_size, m));
			this->m_size++;
		}
		ifs.close();
		/*�������map����*/
// 				for (map<int, map<string, string>>::iterator it = m_order.begin(); it != m_order.end(); it++)
// 				{
// 					cout << "����Ϊ�� " << it->first << " value = " << endl;
// 					for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
// 					{
// 						cout << " key = " << mit->first << " value = " << mit->second << " ";
// 					}
// 					cout << endl;
// 				}
	 }

	void updateOrder() //����ԤԼ��¼
	{
		if (this->m_size == 0)
			return;
		ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
		for (int i = 0; i < m_size; i++)
		{
			ofs << "����:" << this->m_order[i]["����"] << "  " << "ʱ���:" << this->m_order[i]["ʱ���"] << "  " << "������:" << this->m_order[i]["������"] << "  " << "ѧ������:" << this->m_order[i]["ѧ������"] << "\t" << "ѧ��ѧ��:" << this->m_order[i]["ѧ��ѧ��"] << "  " << "ԤԼ״̬:" << this->m_order[i]["ԤԼ״̬"] << endl;
		}
	}

	int m_size; //��¼ԤԼ����
	//int�Ǽ�¼������value�����е�һ��string���ĵ��е��������֣��ڶ���string��״̬
	map<int, map<string, string>>m_order;
};