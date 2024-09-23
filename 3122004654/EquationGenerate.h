#pragma once
#include "Fraction.h"
#include <unordered_set>
unordered_set<string> vis;//记录重复算式

struct Node {
	Fraction fr;
	string eq;
	string checkeq;
	string op;
	int l, r;
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

Node getRandomEquation() {
	int siz = (rand() % operatorLimit + 1) * 2 + 1;
	vector <Node> tree(siz);//关键数组
	vector <int> priority;//优先级
	tree[0].fr.random_init(); tree[0].checkeq = tree[0].eq = tree[0].fr.write();
	tree[0].l = -1, tree[0].r = 1; tree[0].bracketadd = 0;
	for (int i = 1; i < siz; i += 2) {
		tree[i].l = i - 1; tree[i].r = i + 1;
		tree[i].op = getRandomOperator();
		tree[i].checkeq = tree[i].eq = tree[i].op;
		tree[i].bracketadd = false;
		priority.push_back(i);
		tree[i + 1].l = i; tree[i + 1].r = i + 2;
		tree[i + 1].fr.random_init();
		tree[i + 1].checkeq = tree[i + 1].eq = tree[i + 1].fr.write();
		tree[i + 1].bracketadd = false;
	}

	random_shuffle(priority.begin(), priority.end());
	for (auto id : priority)//按优先级合并，有点乱
	{
		int lid = tree[id].l, rid = tree[id].r;//获取进行运算元素的下标
		string lop = tree[lid].l == -1 ? "#" : tree[tree[lid].l].op;//获取该运算符左边的运算符
		string rop = tree[rid].r == siz ? "#" : tree[tree[rid].r].op;
		tree[id].fr = autoCal(tree[lid].fr, tree[id].op, tree[rid].fr);
		if (tree[id].fr < 0) {
			if ((tree[lid].op == "-" || tree[lid].op == "+") && tree[lid].bracketadd == false) {
				tree[lid].eq = '(' + tree[lid].eq + ')';
				tree[lid].bracketadd = true;
			}
			if ((tree[rid].op == "-" || tree[rid].op == "+") && tree[rid].bracketadd == true) {
				tree[rid].eq = tree[rid].eq.substr(1, (int)tree[rid].eq.size() - 2);
				tree[rid].bracketadd = false;
			}
			tree[lid].swapkey(tree[rid]);//交换节点的关键值
			tree[id].fr = autoCal(tree[lid].fr, tree[id].op, tree[rid].fr);
			if (tree[id].fr.error_check())//算式运算过程发生除0错误
				return { Fraction(),"","","",0,0 };
		}

		if (getPriority(lop) < getPriority(tree[id].op) && getPriority(tree[id].op) >= getPriority(rop))
			tree[id].eq = tree[lid].eq + tree[id].eq + tree[rid].eq;
		else
		{
			if (getPriority(lop) >= getPriority(tree[lid].op) && getPriority(tree[lid].op) >= getPriority(tree[id].op) && tree[lid].bracketadd == true) {
				tree[lid].eq = tree[lid].eq.substr(1, (int)tree[lid].eq.size() - 2);
				tree[lid].bracketadd = false;
			}
			tree[id].eq = '(' + tree[lid].eq + tree[id].eq + tree[rid].eq + ')';
			tree[id].bracketadd = true;
		}

		if ((tree[id].op == "+" || tree[id].op == "*") && tree[lid].checkeq > tree[rid].checkeq)//check全程加括号才能保证查重正确性
			tree[id].checkeq = '(' + tree[rid].checkeq + tree[id].checkeq + tree[lid].checkeq + ')';
		else
			tree[id].checkeq = '(' + tree[lid].checkeq + tree[id].checkeq + tree[rid].checkeq + ')';

		tree[id].r = tree[rid].r;
		tree[id].l = tree[lid].l;
		if (tree[id].l != -1)  tree[tree[id].l].r = id;
		if (tree[id].r != siz) tree[tree[id].r].l = id;
	}
	Node ans = tree[priority.back()];
	if (vis.find(ans.checkeq) != vis.end())
		return { Fraction(),"","","",0,0 };
	vis.insert(ans.checkeq);
	return ans;
}