#pragma once
#include "Fraction.h"

string calculate(string eq) {//计算字符串形式的四则运算公式对应答案
    stack<string> opt;
    queue<pair<string, Fraction>> postOrder;
    size_t last = 0;
    for (size_t i = 0; i < eq.size(); i++) { //求后缀表达式
        if (eq[i] == '=') {//算式存在等于号，加载最后一个数字
            if (last != i)
                postOrder.push({ "",Fraction(stringToFraction(eq.substr(last,i - last))) });
            last = i + 1;
            continue;
        }
        else if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*') {
            if(last != i)
                postOrder.push({"",Fraction(stringToFraction(eq.substr(last,i - last))) });
            last = i + 1;
            while (!(opt.empty() || getPriority(eq.substr(i, 1)) > getPriority(opt.top()))) {
                postOrder.push({ opt.top(),Fraction() });
                opt.pop();
            }
            opt.push(eq.substr(i, 1));
        }
        else if (eq.substr(i, 2) == "÷") { 
            if (last != i)
                postOrder.push({ "",Fraction(stringToFraction(eq.substr(last,i - last))) });
            last = i + 2;
            while (!(opt.empty() || getPriority(eq.substr(i, 2)) > getPriority(opt.top()))) {
                postOrder.push({ opt.top(),Fraction() });
                opt.pop();
            }
            opt.push(eq.substr(i, 2));
        }
        else if (eq[i] == '(') {
            opt.push(eq.substr(i, 1));
            last++;
        }
        else if (eq[i] == ')'){
            if (last != i)
                postOrder.push({ "",Fraction(stringToFraction(eq.substr(last,i - last))) });
            last = i + 1;
            while (opt.top() != "(") {
                postOrder.push({ opt.top(),Fraction() });
                opt.pop();
            }
            opt.pop();
        }
    }
    if (last < eq.size())//算式不存在等于号时，加载最后一个数字
       postOrder.push({ "",Fraction(stringToFraction(eq.substr(last))) });
    while (!opt.empty()) {
        postOrder.push({ opt.top(),Fraction() });
        opt.pop();
    }
    stack<Fraction> st;
    while (!postOrder.empty())//根据后缀表达式完成答案的运算
    {
        if (postOrder.front().first != "") {
            Fraction fra1 = st.top(); st.pop();
            Fraction fra2 = st.top(); st.pop();
            st.push(autoCal(fra2, postOrder.front().first, fra1));
        }
        else {
            st.push(postOrder.front().second);
        }
        postOrder.pop();
    }
    return st.top().write();
}

void checkexample(ifstream &fileExample,ifstream &fileAnswer) {//逐行读取文件并将答案比较
    string example, answer;
    vector<int> correct, wrong;
    while (getline(fileExample, example)) {
        getline(fileAnswer, answer);
        size_t i = 1, j;
        for (; i < example.size(); i++) {
            if (example[i] == '.')
                j = i;
            else if (example[i - 1] == ' ' && example[i] != ' ')
                break;
        }
        string tmp = calculate(example.substr(i));
        if (calculate(example.substr(i)) == answer.substr(i))
            correct.push_back(stol(example.substr(0, j)));
        else
            wrong.push_back(stol(example.substr(0, j)));
    }
    ofstream fileGrade("Grade.txt");
    fileGrade << "Correct:" << correct.size() << "(";
    for (size_t i = 0; i < correct.size();i++) {
        fileGrade << correct[i];
        if (i + 1 != correct.size())
            fileGrade << ',';
    }
    fileGrade << ")\n";
    fileGrade << "Wrong:" << wrong.size() << "(";
    for (size_t i = 0; i < wrong.size(); i++) {
        fileGrade << wrong[i];
        if (i + 1 != wrong.size())
            fileGrade << ',';
    }
    fileGrade << ")\n";
    fileGrade.close();
}
