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
	//显示学生登录后的界面
	void operMenu()
	{
		cout << this->m_Name << " 同学,你好！" << endl;
		cout << "1. 预约机房    2. 查询预约 " << endl;
		cout << "3. 删除预约" << endl;
		cout << "0. 退出" << endl;
	}
	void show_sOrder()
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
			if (this->m_id == atoi(ord.m_order[i]["学生学号"].c_str())) //利用c语言将string转为int类型
			{
				cout << "预约日期：周" << ord.m_order[i]["日期"] << "  " << "预约时间段：" << (ord.m_order[i]["时间段"] == "1" ? "上午" : "下午") << "  " << "预约机房号：" << ord.m_order[i]["机房号"] << "  ";
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

		}
		system("pause");
		system("cls");

	}
	
	void applyOrder()
	{
		cout << "选择机房预约日期：" << endl;
		cout << "1.周一      2.周二" << endl;
		cout << "3.周三      4.周四" << endl;
		cout << "5.周五" << endl;
		int date, time, place;
		cin >> date;
		cout << "请选择时间：" << endl;
		cout << "1.上午  2.下午" << endl;
		cin >> time;
		cout << "请选择机房号：" << endl;
		for (int i = 0; i < v3.size(); i++)
		{
			cout << v3[i].RoomId << " 号机房余量为：" << v3[i].RoomMax << endl;
		}
		cin >> place;
		cout << "预约成功，等待审核。" << endl;
		ofstream ofs(ORDER_FILE, ios::app);
		ofs << "日期:" << date << "  " << "时间段:" << time << "  " << "机房号:" << place << "  " << "学生姓名:" << this->m_Name << "\t" << "学生学号:" << this->m_id << "  " << "预约状态:" << 1 << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	void delete_sOrder()
	{
		order ord;
		if (ord.m_size == 0)
		{
			cout << "无预约记录" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "可以取消的预约如下：" << endl;
		vector<int>v;  //存放在最大容器中的下标编号
		int index = 1;
		for (int i = 0; i < ord.m_size; i++)
		{
			//先判断是否自身学号
			if (this->m_id == atoi(ord.m_order[i]["学生学号"].c_str()))
			{
				if (ord.m_order[i]["预约状态"] == "1" || ord.m_order[i]["预约状态"] == "2")
				{
					v.push_back(i);
					cout << index++ << ". " << "预约日期：周" << ord.m_order[i]["日期"] << "  时间段：" << (ord.m_order[i]["时间段"] == "1" ? "上午" : "下午") << "  机房编号：" << ord.m_order[i]["机房号"] << "  ";
					string status = "预约状态：";
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
			}
		}

		if (v.size() == 0)
		{
			cout << "预约记录为零！" << endl;
			system("pause");
			system("cls");
			return;
		}

		cout << "请选择要取消的预约：" << endl;
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
					ord.m_order[v[select - 1]]["预约状态"] = "0";
					ord.updateOrder();
					cout << "预约取消成功！" << endl;
					break;
				}
			}
			cout << "输入有误，重新输入：";
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