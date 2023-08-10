#include <iostream>
#include "student.hpp"
#include "teacher.hpp"
#include <fstream>
#include "admin.hpp"
#include "all.hpp"
#include <vector>
using namespace std;
void studentMenu(Identity* &student1)
{
	while (true)
	{
		student1->operMenu();
		student* stu = (student*)student1; //将父类指针强转为子类指针 stu，利用指针 stu 调用子类里其他接口 (函数)
		int select;
		cin >> select;
		if (select == 1)
		{
			stu->applyOrder();
		}
		else if (select == 2)
		{
			stu->show_sOrder();
		}
		else if (select == 3)
		{
			stu->delete_sOrder();
		}
		else
		{
			delete stu;   //堆区内存清空
			cout << "注销账号！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void teacherMenu(Identity *& teacher1)
{
	while (true)
	{
		teacher1->operMenu();
		teacher* tea = (teacher*)teacher1; //将父类指针强转为子类指针 tea，利用指针 tea 调用子类里其他接口 (函数)
		int select;
		cin >> select;
		if (select == 1)
		{
			tea->show_Order();
		}
		else if (select == 2)
		{
			tea->validOrder();
		}
		else
		{
			delete tea;   //堆区内存清空
			cout << "注销账号！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}


void adminMenu(Identity *& admin1)  //形参定义了一个叫admin1的父类指针,实参传入可以改变父类指针里的属性
{
	while (true)
	{
		admin1->operMenu();  //父类指针指向父类中的函数，opermenu作为纯虚函数，在其他子类中有函数定义
		admin* ad = (admin*)admin1;  //将父类指针强转为子类指针 ad，利用指针 ad 调用子类里其他接口 (函数)
		int select = 0;
		//接收用户选择
		cin >> select;
		if (select == 1) //添加
		{
			ad->add();
		}
		else if (select == 2) //人员信息
		{
			ad->maninfo();
		}
		else if (select == 3)  //机房信息
		{
			ad->showInfo();
		}
		else if (select == 4)
		{
			ad->deleteAllOrder();
		}
		else if (select == 5)
		{
			ad->deleteOrder();
		}
		else
		{
			delete ad;   //堆区内存清空
			cout << "注销账号！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	

}

void LoginIn(string fileName, int type) //操作的txt， 选择的身份序号
{
	Identity * person = NULL;  // 多态：准备一个父类指针 指向 子类的对象
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	string name;
	int id;
	string pwd;
	
	if (type == 1)
	{
		cout << "请输入你的学号：";
		cin >> id;
		
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号：";
		cin >> id;
		
	}
	else
	{
		cout << "请输入你的账号：";
		cin >> name;
	}
	cout << "请输入你的密码：";
	cin >> pwd;
	if (type == 1) //学生身份
	{
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fpwd == pwd)
			{
				cout << fname << " 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new student(id, fname, pwd);  //学生类创建堆区
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) //老师身份
	{

		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fpwd == pwd)
			{
				cout << fname << " 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new teacher(id, fname, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else  //管理员
	{
		string fname;
		
		string fpwd;
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd)
			{
				cout  << "admin 登录成功！" << endl;
				system("pause");
				system("cls");
				person = new admin(name, pwd);
				adminMenu(person);
				return;
			}
		}
	}
	cout << "账号或密码错误，请重新输入! " << endl;
	system("pause");
	system("cls");
	return;
}

void showBigMenu()
{
	cout << "这里是机房预约系统！" << endl;
	cout << "请输入你的身份：" << endl;
	cout << "1.学生" << endl;
	cout << "2.老师" << endl;
	cout << "3.管理员" << endl;
	cout << "0.退出系统" << endl;
}
int main()
{
	int choose;
	while (true)
	{
		showBigMenu();
		cin >> choose;
		switch (choose)
		{
		case 1://学生
			LoginIn(STUDENT_FILE, 1);
			break;
		
		case 2://老师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
		{
			
			cout << "退出系统" << endl;
			system("pause");
			return 0; 
		}
			
		}
	}
	
	return 0;
}