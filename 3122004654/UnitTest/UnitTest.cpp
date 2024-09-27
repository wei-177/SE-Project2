#include "pch.h"
#include "CppUnitTest.h"
#include"../main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			char* argv[5] = { "main.exe","-n","10000","-r","100" };
			Assert::AreEqual(main(5, argv), 0);
		}
		TEST_METHOD(TestMethod2)
		{
			char* argv[3] = { "main.exe","-n","10000" };
			Assert::AreEqual(main(3, argv), 0);
		}
		TEST_METHOD(TestMethod3)
		{
			char* argv[3] = { "main.exe","-n","-10000" };
			Assert::AreEqual(main(3, argv), 1);
		}
		TEST_METHOD(TestMethod4)
		{
			char* argv[5] = { "main.exe","-e","10000","-a","100" };
			Assert::AreEqual(main(5, argv), 3);
		}
		TEST_METHOD(TestMethod5)
		{
			char* argv[4] = { "main.exe","-e","10000","-a" };
			Assert::AreEqual(main(4, argv), -1);
		}
		TEST_METHOD(TestMethod6)
		{
			char* argv[5] = { "main.exe","-e","Exercises.txt","-a","Answers.txt" };
			Assert::AreEqual(main(5, argv), 0);
		}
		TEST_METHOD(TestMethod7)
		{
			Assert::AreEqual(getPriority("+"), 1);
			Assert::AreEqual(getPriority("-"), 1);
			Assert::AreEqual(getPriority("*"), 2);
			Assert::AreEqual(getPriority("¡Â"), 2);
			Assert::AreEqual(getPriority("#"), 0);
		}
		TEST_METHOD(TestMethod8)
		{
			string eq = "1.  3'5/7+(1*6'2/3-6)=";
			string str = "1.  4'8/21";
			Assert::IsTrue(str.compare(calculate(eq)));
		}
		TEST_METHOD(TestMethod9)
		{
			Fraction x(100, 10), y(-50, 10);
			string op1 = "+";
			string op2 = "-";
			string op3 = "*";
			string op4 = "¡Â";
			string ans = "15";
			Assert::IsTrue(ans.compare(autoCal(x, op1, y).write()));
			ans = "5";
			Assert::IsTrue(ans.compare(autoCal(x, op2, y).write()));
			ans = "50";
			Assert::IsTrue(ans.compare(autoCal(x, op3, y).write()));
			ans = "2";
			Assert::IsTrue(ans.compare(autoCal(x, op4, y).write()));

		}
		TEST_METHOD(TestMethod10)
		{
			string eq = "1'1/10";
			string str = "101/10";
			Assert::IsTrue(str.compare(stringToFraction(eq).write()));
		}
		TEST_METHOD(TestMethod11)
		{
			char* argv[5] = { "main.exe","-n","10000","-r","0" };
			Assert::AreEqual(main(5, argv), 2);
		}
		TEST_METHOD(TestMethod12)
		{
			char* argv[5] = { "main.exe","-n","100000","-r","2" };
			Assert::AreEqual(main(5, argv), 5);
		}
		TEST_METHOD(TestMethod13)
		{
			char* argv[5] = { "main.exe","-a","Exercises.txt","-e","Answers.txt" };
			ofstream fileExample("Exercises.txt");
			ofstream fileAnswer("Answers.txt");
			fileExample << "1.  " << "1+1" << "=" << endl;
			fileExample << "2.  " << "10+1" << "=" << endl;
			fileExample << "3.  " << "1+15" << "=" << endl;
			fileAnswer << "1.  " << "0" << endl;
			fileAnswer << "2.  " << "5" << endl;
			fileAnswer << "3.  " << "8" << endl;
			Assert::AreEqual(main(5, argv), 0);
		}
		TEST_METHOD(TestMethod14)
		{
			char* argv[5] = { "main.exe","-x","Exercises.txt","-t","Answers.txt" };
			Assert::AreEqual(main(5, argv), 7);
		}
		TEST_METHOD(TestMethod15)
		{
			char* argv[5] = { "main.exe","-e","Exercises.txt","-a","Answers.txt" };
			ofstream fileExample("Exercises.txt");
			fileExample << "%#%$" << "=" << endl;
			Assert::AreEqual(main(5, argv),6);
		}
	};
}