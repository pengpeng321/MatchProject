#include "stdafx.h"
#include "match.h"
#include "student.h"
#include "time.h"

#include <iostream>
#include <list>
#include <string>

void match::matched(student* stu, department* dep, std::list<int>* stuList, std::list<int>* depList, int stu_number, int dep_number)
{
	/*匹配时，采用部门挑选学生
	  设置权值如下：
		若学生填写的部门意愿包含此部门，则拿到此权值分数（7分）
		若学生的绩点越高，拿到此权值的比重越高（满分2分）
		若学生能参与部门常规活动的个数越多，拿到此权值的比重越高（共3分）
		若学生的兴趣爱好与部门希望拥有的兴趣爱好相同个数越多，拿到此权值的比重越高（共2分）
	  每个学生的权值从高到低排序，供部门挑选，挑选原则如下：
		某学生的权值大于等于7分才有资格进入此部门
		权值高的优先进入部门
		当纳新的人数达到部门最多纳新人数时，结束纳新
	 */
	int i,j,m,n,temp;								 //循环变量等
	double stu_dep[5000];							 //每个学生的权值
	double q;										 //某个学生临时权值

	int stu_dep_sort[5000];							 //对于每个部门，将学生权值排序
	int k;											 //stu_dep_sort数组的元素个数

	int sw, st, sa;									//学生 部门意愿数量/兴趣标签数量/有空时间数量
	int dt, da;										//部门 希望兴趣标签数量/活动时间数量
	
	stime stuTime[20],depTime[20];

	for (i = 0; i < dep_number; i++)
	{
		k = 0;
		dt = dep[i].getTag_number();
		da = dep[i].getTime_number();
		timeConvert(dep[i].getAvail_time(), da, depTime);
		for (j = 0; j < stu_number; j++)
		{
			/*计算对于每一个部门，计算每个学生的对应权值*/
			q = 0;
			sw = stu[j].getWill_number();
			st = stu[j].getTag_number();
			sa = stu[j].getTime_number();

			/*根据学生选择部门的意愿计算权值	*/
			for (m = 0; m < sw; m++)
			{
				if (*(stu[j].getDep_will() + m) == dep[i].getDep_no())
				{
					q += 7;						//计算权值（累加）
					break;
				}
			}

			/*根据学生的绩点来计算权值*/
			q += (stu[j].getScore() / 5.0) * 2;

			/*根据学生的有空时间段和部门活动时间段来计算权值*/
			//timeConvert()将用字符串表示的时间转换成用stime类表示
			timeConvert(stu[j].getAvail_time(), sa, stuTime);
			
			temp = 0;
			for (m = 0; m < da; m++)
			{
				/*对于每个部门的时间段循环学生有空时间*/
				for (n = 0; n < sa; n++)
				{
					if (stuTime[n].week != depTime[m].week)  continue;
					if (stuTime[n].start > depTime[m].start)	continue;
					if (stuTime[n].end < depTime[m].end)	continue;
					temp++;
					break;
				}
			}
			q += temp*1.0 / da * 2;			//计算权值（累加）

			/*根据学生的兴趣爱好和部门想要的兴趣tags来计算权值*/
			temp = 0;
			for (m = 0; m < dt; m++)
			{
				/*对于每个部门的兴趣要求段循环学生的兴趣*/
				for (n = 0; n < st; n++)
				{
					if (*(stu[j].getTags() + n) != *(dep[i].getTags() + m)) continue;
					temp++;
					break;
				}
			}
			q += temp*1.0 / dt * 2;			//计算权值（累加）

			/*将第x个学生计算后的权值保存在stu_dep[x]中*/
			stu_dep[j] = q;

			/*将学生的权值进行排序，权值大的学生的下标，优先排在数组stu_dep_sort的前面*/
			if (q < 7)continue;					//权值小于7，无需记录此学生
			stu_dep_sort[k] = j;
			for (n = k - 1; n > -1; n--)
			{
				if (stu_dep[stu_dep_sort[n + 1]] > stu_dep[stu_dep_sort[n]])
				{
					temp = stu_dep_sort[n + 1];
					stu_dep_sort[n + 1] = stu_dep_sort[n];
					stu_dep_sort[n] = temp;
				}
			}
			k++;
		}
		
		/*
		std::cout << "权值排序：" << std::endl;
		for (n = 0; n < k; n++)
		{
			std::cout <<n<<' '<< stu[stu_dep_sort[n]].getStu_name() << " " << stu_dep[stu_dep_sort[n]] << "	";
		}
		std::cout << std::endl;
		std::cout << std::endl;


		/*对于部门，在deplist中记录下纳入部门的学生在数组stu中的所在下标
		  对于学生，在stulist中记录下加入的部门在数组dep中的所在下标	*/

		for (n = 0; n < dep[i].getNumber_limit(); n++)
		{
			if (n >= j) break;									//达到部门可选人数，即 n > stu_dep_sort数组元素个数
			if (n >= k) break;								   //部门纳新人数达到最大值，不再纳新
			if (stuList[stu_dep_sort[n]].size() >= 5) continue; //学生加入的部门达到五个，不再加入
			depList[i].push_back(stu_dep_sort[n]);
			stuList[stu_dep_sort[n]].push_back(i);
		}
	}
}

void match::timeConvert(std::string* time, int number,stime* ansTime)
{
	//将活动时间表格*转换成 stime* 类（包括周几，开始时间，结束时间）
	int i, j, temp;
	for(i=0;i<number;i++)
	{
		j = 0;
		switch (time[i][j])
		{
		case 'm':
			j += 3;
			ansTime[i].week = 1; 
			break;
		case 't':
			if (time[i][j + 1] == 'u') { ansTime[i].week = 2; }
			else { ansTime[i].week = 4; }
			j += 4;
			break;
		case 'w':
			j += 3;
			ansTime[i].week = 3;
			break;
		case 'f':
			j += 3;
			ansTime[i].week = 5;
			break;
		case 's':
			if (time[i][j + 1] == 'a') { ansTime[i].week = 6; }
			else { ansTime[i].week = 7; }
			j += 3;
			break;
		default:exit(1);
		}
		temp = 0;
		temp = temp * 10 + (time[i][j++] - '0');
		temp = temp * 10 + (time[i][j++] - '0');
		ansTime[i].start = temp;
		j++;
		temp = 0;
		temp = temp * 10 + (time[i][j++] - '0');
		temp = temp * 10 + (time[i][j] - '0');
		ansTime[i].end = temp;
		//std::cout << ansTime[i].week << ' ' << ansTime[i].start << ' ' << ansTime[i].end << std::endl;
	}
	//std::cout << std::endl;
}

match::match()
{
}


match::~match()
{
}
