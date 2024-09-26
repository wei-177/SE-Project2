#include "EquationGenerate.h"
#include "Calculate.h"
int main(int argc, char* argv[]){

	if (argc != 3 && argc != 5) {
		cout << "输入错误，程序结束" << endl;
		return -1;
	}
	bool opt[4] = { 0 };//分别检测是否有-n,-r,-e,-a
	for (int i = 1; i < argc; i += 2)
	{
		if (strcmp(argv[i], "-n") == 0)
			opt[0] = 1;
		else if (strcmp(argv[i], "-r") == 0)
			opt[1] = 1;
		else if (strcmp(argv[i], "-e") == 0)
			opt[2] = 1;
		else if (strcmp(argv[i], "-a") == 0)
			opt[3] = 1;
	}
	if (opt[0]) {
		countLimit = strtol(argv[2], NULL, 0);
		if (countLimit <= 0) {
			cout << "要求生成题目数量错误，程序结束" << endl;
			return 1;
		}
		if (opt[1]) {
			numLimit = strtol(argv[4], NULL, 0);
			if (numLimit <= 0) {
				cout << "要求生成数据范围错误，程序结束" << endl;
				return 2;
			}
		}
		else
			numLimit = 10;//默认为10
		srand(time(NULL));//随机数生成
		ofstream fileExample("Exercises.txt");
		ofstream fileAnswer("Answers.txt");
		int count = 1,timelimit = 1;
		unordered_set<string> vis;//记录重复算式
		while (count <= countLimit) {
			Node ans = getRandomEquation(vis);
			if (ans.checkeq == "") {
				timelimit++;
				if (timelimit >= 500)
				{
					fileExample.close();
					fileAnswer.close();
					cout << "随机生成时连续出现500次重复算式，当前数字限制可能不足以生成这么多不重复的算式" << endl;
					return 5;
				}
				continue;
			}
			timelimit = 0;
			fileExample << count << ".  " << ans.eq << "=" << endl;
			fileAnswer << count << ".  " << ans.fr.write() << endl;
			count++;
		}
		vis.clear();
		fileExample.close();
		fileAnswer.close();
		cout << "算式生成成功" << endl;
	}
	else if (opt[2] && opt[3])
	{
		if (strcmp(argv[1], "-a") == 0)
			swap(argv[2], argv[4]);
		ifstream fileExample(argv[2]);
		ifstream fileAnswer(argv[4]);
		if (fileExample.fail() || fileAnswer.fail()) {
			cout << "文件路径错误" << endl;
			return 3;
		}
		try {
			checkexample(fileExample, fileAnswer);
			cout << "答案比较完成" << endl;
		}
		catch (const char* msg) { // 捕获异常
			cout << msg << endl;
			fileExample.close();
			fileAnswer.close();
			return 4;
		}
		fileExample.close();
		fileAnswer.close();
	}
	else{
		cout << "输入操作符不正确，程序结束" << endl;
		return 5;
	}
	return 0;
}
