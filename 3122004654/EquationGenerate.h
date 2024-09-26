#pragma once
#include "Fraction.h"
#include <unordered_set>

struct Node {
	Fraction fr;
	string eq;
	string checkeq;
	string op;
	int l, r;//记录
	bool bracketadd;
	void swapkey(Node& x) {
		swap(fr, x.fr); swap(eq, x.eq);
		swap(checkeq, x.checkeq); swap(op, x.op);
		swap(bracketadd, x.bracketadd);
	}
};

string getRandomOperator() {
	int rd = rand() % 4;
	if (rd == 0) return "+";
	else if (rd == 1) return "-";
	else if (rd == 2) return "*";
	else return "÷";
}

Node getRandomEquation(unordered_set<string> &vis) {
	int siz = (rand() % operatorLimit + 1) * 2 + 1;
	vector <Node> List(siz);//用vector实现将链缩成点的过程
	vector <int> priority;//优先级
	List[0].fr.random_init(); List[0].checkeq = List[0].eq = List[0].fr.write();
	List[0].l = -1, List[0].r = 1; List[0].bracketadd = 0;
	for (int i = 1; i < siz; i += 2) {//节点数据初始化,使链呈现数字与运算符交替的结构(即是一条合法的无括号四则运算算式)
		List[i].l = i - 1; List[i].r = i + 1;
		List[i].op = getRandomOperator();
		List[i].checkeq = List[i].eq = List[i].op;
		List[i].bracketadd = false;
		priority.push_back(i);
		List[i + 1].l = i; List[i + 1].r = i + 2;
		List[i + 1].fr.random_init();
		List[i + 1].checkeq = List[i + 1].eq = List[i + 1].fr.write();
		List[i + 1].bracketadd = false;
	}

	random_shuffle(priority.begin(), priority.end());//随机排序以获得运算符的运算优先级
	for (auto id : priority)
	{
		/*
		该合并过程可以看作将链根据节点优先级缩成一个点
		初始每个节点对应分别一条合法的无括号四则运算算式的数字和运算符
		按优先级逐级操作链上的运算符节点，每次对一个运算符节点操作时，
		首先根据两个相邻数字节点的数据更新当前运算符节点从而得到新的数字节点，并根据运算符优先级判断是否添加括号。
		然后将两个相邻的数字节点从链中删除（该操作通过修改下标实现懒删除)
		此时可以看作链上的一个运算符节点和其相邻的数字节点合并成了新的数字节点。
		重复上述操作，将链上的所有节点合并完成，最终剩下的节点包含的四则运算式即是目标算式。
		查重字符串则是数字节点在合并中按字典序较小来进行合并且始终添加括号的结果(可确保有限次交换相同的字符串其查重字符串一样）
		*/
		int lid = List[id].l, rid = List[id].r;//获取进行运算元素的下标
		string lop = List[lid].l == -1 ? "#" : List[List[lid].l].op;//获取该运算符左边的运算符
		string rop = List[rid].r == siz ? "#" : List[List[rid].r].op;//获取该运算符右边的运算符
		List[id].fr = autoCal(List[lid].fr, List[id].op, List[rid].fr);
		if (List[id].fr < 0) {//合并节点值小于0，交换合并顺序并更新括号
			if ((List[lid].op == "-" || List[lid].op == "+") && List[lid].bracketadd == false) {
				List[lid].eq = '(' + List[lid].eq + ')';
				List[lid].bracketadd = true;
			}
			if ((List[rid].op == "-" || List[rid].op == "+") && List[rid].bracketadd == true) {
				List[rid].eq = List[rid].eq.substr(1, (int)List[rid].eq.size() - 2);
				List[rid].bracketadd = false;
			}
			List[lid].swapkey(List[rid]);//交换节点的关键值
			List[id].fr = autoCal(List[lid].fr, List[id].op, List[rid].fr);
			if (List[id].fr.error_check())//算式运算过程发生除0错误
				return { Fraction(),"","","",0,0 };
		}

		if (getPriority(lop) < getPriority(List[id].op) && getPriority(List[id].op) >= getPriority(rop))//根据优先级判断是否添加括号
			List[id].eq = List[lid].eq + List[id].eq + List[rid].eq;
		else
		{
			if (getPriority(lop) >= getPriority(List[lid].op) && getPriority(List[lid].op) >= getPriority(List[id].op) && List[lid].bracketadd == true) {
				List[lid].eq = List[lid].eq.substr(1, (int)List[lid].eq.size() - 2);//移除不需要的括号
				List[lid].bracketadd = false;
			}
			List[id].eq = '(' + List[lid].eq + List[id].eq + List[rid].eq + ')';
			List[id].bracketadd = true;
		}

		if ((List[id].op == "+" || List[id].op == "*") && List[lid].checkeq > List[rid].checkeq)//check全程加括号才能保证查重正确性
			List[id].checkeq = '(' + List[rid].checkeq + List[id].checkeq + List[lid].checkeq + ')';
		else
			List[id].checkeq = '(' + List[lid].checkeq + List[id].checkeq + List[rid].checkeq + ')';

		List[id].r = List[rid].r;
		List[id].l = List[lid].l;
		if (List[id].l != -1)  List[List[id].l].r = id;
		if (List[id].r != siz) List[List[id].r].l = id;
	}
	Node ans = List[priority.back()];
	if (vis.find(ans.checkeq) != vis.end())
		return { Fraction(),"","","",0,0 };
	vis.insert(ans.checkeq);
	return ans;
}
