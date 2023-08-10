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
	//初始化管理员信息
	admin(string name, string pwd)
	{
		this->m_Name = name;
		this->m_Pwd = pwd;
		this->initVector();  //初始化老师，学生容器
		this->initRoom();  //初始化机房容器
	}
	//显示管理员登录后的界面
	void operMenu()
	{
		cout << "管理员 你好！" << endl;
		cout << "1. 添加账号      2. 查询信息 " << endl;
		cout << "3. 机房信息      4. 清空预约" << endl;
		cout << "5. 删除预约      0. 退出" << endl;
	}

	void showInfo()
	{
		cout << "以下是开放的机房信息：" << endl;
		for (vector<room>::iterator it = v3.begin(); it != v3.end(); it++)
		{
			cout << "机房编号：" << it->RoomId << "\t" << "机房容量：" << it->RoomMax << "\t" << endl;
		}
		system("pause");
		system("cls");
	}
	void add()   //添加人员信息
	{
		cout << "请选择要添加的类型：" << endl;
		cout << "1. 学生      2. 老师" << endl;
		string filename;
		string tip;
		string errortip;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			filename = STUDENT_FILE;
			tip = "请输入学号：";
			errortip = "学号重复，请重新输入：";
		}
		else if (select == 2)
		{
			filename = TEACHER_FILE;
			tip = "请输入职工号：";
			errortip = "职工号重复，请重新输入：";

		}
		int id;
		cout << tip;
		while (true)
		{
			cin >> id;
			bool ret = this->checkRepeat(id, select);   //判断创建的账号是否重复
			if (ret)
			{
				cout << errortip << endl;
			}
			else
				break;
		}
		string name;
		string pwd;
		cout << "请输入姓名：";
		cin >> name;
		cout << "请输入密码：";
		cin >> pwd;
		ofstream ofs(filename, ios::out | ios::app);
		ofs << id << "  " << name << "  " << pwd << endl;
		cout << "添加成功！" << endl;
		system("pause");
		system("cls");
		ofs.close();
		this->initVector();  //初始化容器，先将容器内旧的信息清空，将新添加的人员信息初始化到容器内
	}
	void deleteOrder()
	{
		cout << "可以取消的预约如下：" << endl;
		vector<int>v;  //存放在最大容器中的下标编号
		int index = 1;
		order ord;
		for (int i = 0; i < ord.m_size; i++)
		{
			
				if (ord.m_order[i]["预约状态"] == "1" || ord.m_order[i]["预约状态"] == "2")
				{
					v.push_back(i);
					cout << index++ << ". " << "预约日期：周" << ord.m_order[i]["日期"] << "  时间段：" << (ord.m_order[i]["时间段"] == "1" ? "上午" : "下午") << "  机房编号：" << ord.m_order[i]["机房号"] << "  " << "学生姓名:" << ord.m_order[i]["学生姓名"] << "\t" << "学生学号:" << ord.m_order[i]["学生学号"] << "  ";
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
	void deleteAllOrder()
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "清除成功！" << endl;
		system("pause");
		system("cls");
	}
// 	void printStudent(student &s)
// 	{
// 		cout << "学号：" << s.m_id << " ,姓名: " << s.m_Name << " ,密码：" << s.m_Pwd << endl;
// 	}
// 	void printTeacher(teacher &t)
// 	{
// 		cout << "职工号：" << t.m_id << " ,姓名: " << t.m_Name << " ,密码：" << t.m_Pwd << endl;
// 	}
	void maninfo()
	{
		cout << "请选择你要查看的人员信息：" << endl;
		cout << "1. 学生        2. 老师" << endl;
		int choose;
		cin >> choose;
		if (choose == 1)
		{
			cout << "系统内学生信息如下：" << endl;
			for (vector<student>::iterator it = v1.begin(); it != v1.end(); it++)
			{
				cout << "学号：" << it->m_id << "\t" << "姓名: " << it->m_Name << "\t" << "密码：" << it->m_Pwd << endl;
			}
		}
		else if (choose == 2)
		{
			cout << "系统内老师信息如下：" << endl;
			for (vector<teacher>::iterator it = v2.begin(); it != v2.end(); it++)
			{
				cout << "职工号：" << it->m_id << "\t" << "姓名: " << it->m_Name << "\t" << "密码：" << it->m_Pwd << endl;
			}
		}
		else
		{
			cout << "输入错误！" << endl;
			system("pause");
			system("cls");
			return;
		}
		system("pause");
		system("cls");
	}

	void initVector()  //打开保存学生和老师信息的txt文本，将文本内的内容全部存到v1(学生)，v2(老师) 里。
	{
		ifstream ifs;
		ifs.open(STUDENT_FILE, ios::in);
		if (!ifs.is_open())  //检测student.txt文本是否存在
		{
			cout << "文件不存在！" << endl;
			return;
		}
		v1.clear();  //将容器内老数据清空
		v2.clear();  //同上

		student s;   //建立学生类的对象
		while (ifs >> s.m_id && ifs >> s.m_Name && ifs >> s.m_Pwd)
		{
			v1.push_back(s);
		}
		cout << "当前学生数量为：" << v1.size() << endl;
		ifs.close();

		teacher t;  //建立老师类的对象
		ifs.open(TEACHER_FILE, ios::in);
		while (ifs >> t.m_id && ifs >> t.m_Name && ifs >> t.m_Pwd)
		{
			v2.push_back(t);
		}
		cout << "当前老师数量为：" << v2.size() << endl;
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

	bool checkRepeat(int id, int type)  //判断创建账号输入的学号或者职工号是否重复
	{
		if (type == 1)  //学生
		{
			//遍历v1数组,如果v1内的m_id与输入的id相同，则返回true代表重复
			for (vector<student>::iterator it = v1.begin(); it != v1.end(); it++)
			{
				if (id == it->m_id)
					return true;
			}
		}
		else if (type == 2)  //老师
		{
			//遍历v2数组,如果v2内的m_id与输入的id相同，则返回true代表重复
			for (vector<teacher>::iterator it = v2.begin(); it != v2.end(); it++)
			{
				if (id == it->m_id)
					return true;
			}
		}
	}


	
	~admin(){}  //析构
	vector<room>v3;
	vector<student>v1;  //存放学生信息的容器
	vector<teacher>v2;  //存放老师信息的容器
}; 
