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
		string date;  //预约日期
		string place;  //预约机房号
		string name; //预约人姓名
		string id;  //预约人学号
		string time;  //预约时间段
		string status; //预约状态
		this->m_size = 0;  //开始记录条数
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
			int pos = date.find(":");  //返回四
			if (pos != -1)
			{
				key = date.substr(0, pos);
				value = date.substr(pos + 1, date.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = time.find(":");  //返回四
			if (pos != -1)
			{
				key = time.substr(0, pos);
				value = time.substr(pos + 1, time.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = place.find(":");  //返回四
			if (pos != -1)
			{
				key = place.substr(0, pos);
				value = place.substr(pos + 1, place.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = name.find(":");  //返回四
			if (pos != -1)
			{
				key = name.substr(0, pos);
				value = name.substr(pos + 1, name.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = id.find(":");  //返回四
			if (pos != -1)
			{
				key = id.substr(0, pos);
				value = id.substr(pos + 1, id.size() - pos - 1);
				m.insert(make_pair(key, value));
			}
			pos = status.find(":");  //返回四
			if (pos != -1)
			{
				key = status.substr(0, pos);
				value = status.substr(pos + 1, status.size() - pos - 1);
				m.insert(make_pair(key, value));
			}

			//将小map容器放入到大的map中
			this->m_order.insert(make_pair(this->m_size, m));
			this->m_size++;
		}
		ifs.close();
		/*测试最大map容器*/
// 				for (map<int, map<string, string>>::iterator it = m_order.begin(); it != m_order.end(); it++)
// 				{
// 					cout << "条数为： " << it->first << " value = " << endl;
// 					for (map<string, string>::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
// 					{
// 						cout << " key = " << mit->first << " value = " << mit->second << " ";
// 					}
// 					cout << endl;
// 				}
	 }

	void updateOrder() //更新预约记录
	{
		if (this->m_size == 0)
			return;
		ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
		for (int i = 0; i < m_size; i++)
		{
			ofs << "日期:" << this->m_order[i]["日期"] << "  " << "时间段:" << this->m_order[i]["时间段"] << "  " << "机房号:" << this->m_order[i]["机房号"] << "  " << "学生姓名:" << this->m_order[i]["学生姓名"] << "\t" << "学生学号:" << this->m_order[i]["学生学号"] << "  " << "预约状态:" << this->m_order[i]["预约状态"] << endl;
		}
	}

	int m_size; //记录预约条数
	//int是记录条数，value部分中第一个string是文档中的描述文字，第二个string是状态
	map<int, map<string, string>>m_order;
};