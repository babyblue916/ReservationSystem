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
	//显示老师登录后的界面
	void operMenu()
	{
		cout << this->m_Name << " 老师,你好！" << endl;
		cout << "1. 查询预约     2. 审核预约" << endl;
		cout << "0. 退出" << endl;
	}
	void show_Order()
	{
		order ord;
		if (ord.m_size == 0)
		{
			cout << "无预约记录!" << endl;
			system("pause");
			system("cls");
			return;
		}
		for (int i = 0; i < ord.m_size; i++)
		{
			
			cout << "预约日期：周" << ord.m_order[i]["日期"] << "  " << "预约时间段：" << (ord.m_order[i]["时间段"] == "1" ? "上午" : "下午") << "  " << "学生姓名:" << ord.m_order[i]["学生姓名"] << "\t" << "学生学号:" << ord.m_order[i]["学生学号"] << "  " << "预约机房号：" << ord.m_order[i]["机房号"] << "  ";
				string status = "预约状态: ";
				if (ord.m_order[i]["预约状态"] == "1")
				{
					status += "审核中";
				}
				else if (ord.m_order[i]["预约状态"] == "2")
				{
					status += "预约成功";
				}
				else if (ord.m_order[i]["预约状态"] == "-1")
				{
					status += "审核未通过";
				}
				else if (ord.m_order[i]["预约状态"] == "0")
				{
					status += "预约取消";
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
			cout << "无预约记录！" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "待审核的记录如下：" << endl;
		vector<int>v;  //存放在最大容器中的下标编号
		int index = 1;
		for (int i = 0; i < ord.m_size; i++)
		{

			if (ord.m_order[i]["预约状态"] == "1")
			{
				v.push_back(i);
				cout << index++ << ". " << "预约日期：周" << ord.m_order[i]["日期"] << "  时间段：" << (ord.m_order[i]["时间段"] == "1" ? "上午" : "下午") << "  机房编号：" << ord.m_order[i]["机房号"] << "  " << "学生姓名:" << ord.m_order[i]["学生姓名"] << "\t" << "学生学号:" << ord.m_order[i]["学生学号"] << "  ";
				string status = "预约状态：";
				if (ord.m_order[i]["预约状态"] == "1")
				{
					status += "审核中";
				}
				cout << status << endl;
			}
		}
		cout << "请输入要审核的记录：" << endl;
		cout << "输入0为取消操作。" << endl;
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
					ord.m_order[v[select - 1]]["预约状态"] = "2";
					ord.updateOrder();
					cout << "审核成功！" << endl;
					break;
				}
			}
			cout << "输入有误，重新输入：";
		}
		system("pause");
		system("cls");
	}
	~teacher(){}
	int m_id;
};