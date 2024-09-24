#include "EquationGenerate.h"
#include "Calculate.h"

int main(int argc, char* argv[]){
	if (!(argc == 3 || argc == 5)) {
		cout << "�������,�������" << endl;
		system("pause");
		return 0;
	}
	bool opt[4] = { 0 };//�ֱ����Ƿ���-n,-r,-e,-a
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
			cout << "Ҫ��������Ŀ�������󣬳������" << endl;
			return 0;
		}
		if (opt[1]) {
			numLimit = strtol(argv[4], NULL, 0);
			if (numLimit <= 0) {
				cout << "Ҫ���������ݷ�Χ���󣬳������" << endl;
				return 0;
			}
		}
		else
			numLimit = 10;//Ĭ��Ϊ10
		srand(time(NULL));//���������
		ofstream fileExample("Exercises.txt");
		ofstream fileAnswer("Answers.txt");
		if (fileExample.fail() || fileAnswer.fail()) {
			cout << "�ļ�·������" << endl;
			return 0;
		}
		int count = 1;
		while (count <= countLimit) {
			Node ans = getRandomEquation();
			if (ans.checkeq == "") continue;
			fileExample << count << ".  " << ans.eq << "=" << endl;
			fileAnswer << count << ".  " << ans.fr.write() << endl;
			count++;
		}
		fileExample.close();
		fileAnswer.close();
		cout << "��ʽ���ɳɹ�" << endl;
	}
	else if (opt[2] && opt[3])
	{
		ifstream fileExample("Exercises.txt");
		ifstream fileAnswer("Answers.txt");
		if (fileExample.fail() || fileAnswer.fail()) {
			cout << "�ļ�·������" << endl;
			return 0;
		}
		checkexample(fileExample, fileAnswer);
		fileExample.close();
		fileAnswer.close();
		cout << "�𰸱Ƚ����" << endl;
	}
	else{
		cout << "�������������ȷ���������" << endl;
	}
	return 0;
}