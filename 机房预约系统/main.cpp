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
		student* stu = (student*)student1; //������ָ��ǿתΪ����ָ�� stu������ָ�� stu ���������������ӿ� (����)
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
			delete stu;   //�����ڴ����
			cout << "ע���˺ţ�" << endl;
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
		teacher* tea = (teacher*)teacher1; //������ָ��ǿתΪ����ָ�� tea������ָ�� tea ���������������ӿ� (����)
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
			delete tea;   //�����ڴ����
			cout << "ע���˺ţ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}


void adminMenu(Identity *& admin1)  //�βζ�����һ����admin1�ĸ���ָ��,ʵ�δ�����Ըı丸��ָ���������
{
	while (true)
	{
		admin1->operMenu();  //����ָ��ָ�����еĺ�����opermenu��Ϊ���麯�����������������к�������
		admin* ad = (admin*)admin1;  //������ָ��ǿתΪ����ָ�� ad������ָ�� ad ���������������ӿ� (����)
		int select = 0;
		//�����û�ѡ��
		cin >> select;
		if (select == 1) //���
		{
			ad->add();
		}
		else if (select == 2) //��Ա��Ϣ
		{
			ad->maninfo();
		}
		else if (select == 3)  //������Ϣ
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
			delete ad;   //�����ڴ����
			cout << "ע���˺ţ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	

}

void LoginIn(string fileName, int type) //������txt�� ѡ���������
{
	Identity * person = NULL;  // ��̬��׼��һ������ָ�� ָ�� ����Ķ���
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	string name;
	int id;
	string pwd;
	
	if (type == 1)
	{
		cout << "���������ѧ�ţ�";
		cin >> id;
		
	}
	else if (type == 2)
	{
		cout << "���������ְ���ţ�";
		cin >> id;
		
	}
	else
	{
		cout << "����������˺ţ�";
		cin >> name;
	}
	cout << "������������룺";
	cin >> pwd;
	if (type == 1) //ѧ�����
	{
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fpwd == pwd)
			{
				cout << fname << " ��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new student(id, fname, pwd);  //ѧ���ഴ������
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == 2) //��ʦ���
	{

		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fpwd == pwd)
			{
				cout << fname << " ��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new teacher(id, fname, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else  //����Ա
	{
		string fname;
		
		string fpwd;
		while (ifs >> fname && ifs >> fpwd)
		{
			if (fname == name && fpwd == pwd)
			{
				cout  << "admin ��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new admin(name, pwd);
				adminMenu(person);
				return;
			}
		}
	}
	cout << "�˺Ż������������������! " << endl;
	system("pause");
	system("cls");
	return;
}

void showBigMenu()
{
	cout << "�����ǻ���ԤԼϵͳ��" << endl;
	cout << "�����������ݣ�" << endl;
	cout << "1.ѧ��" << endl;
	cout << "2.��ʦ" << endl;
	cout << "3.����Ա" << endl;
	cout << "0.�˳�ϵͳ" << endl;
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
		case 1://ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		
		case 2://��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3://����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
		{
			
			cout << "�˳�ϵͳ" << endl;
			system("pause");
			return 0; 
		}
			
		}
	}
	
	return 0;
}