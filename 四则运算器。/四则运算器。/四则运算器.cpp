#include<iostream>
#include<string>
#include<stdlib.h>
#include<ctime>
#include<deque>
#include<stack>
#include<fstream>
#include<windows.h>
using namespace std;
int N,R;
//��������
int **add;
int **mul;
string GetProgramDir();
string turnString(int a)
{
	char turnChar[10];
	sprintf(turnChar,"%d",a);
	return turnChar;
}
string charToString(char c)
{
	string t(&c);
	return t;
}
bool isNum(string c)//�ж��Ƿ�������
{
	char s=c[0];
	if((s=='+')||(s=='-')||(s=='/')||(s=='*')|| s=='(' || s==')') return false;
	return true;
}
bool isNotNum(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')')
		return true;
	return false;
}
//�ж��Ƿ�Ϊ����  
bool isPra(string c)   
{  
	char s=c[0];
    if(s=='('||s==')')   
        return true;   
    else   
        return false;  
}  
string addPra(string operCharToString,int Num[],deque<string>& coll1)
{
	string t="";
	bool first=false;
	bool second=false;
	bool third=false;
	if(rand()%2==1){
		first=true;
		t+='('+turnString(Num[0])+operCharToString[0]+turnString(Num[1])+')';
		coll1.push_back("(");
		coll1.push_back(turnString(Num[0]));
		coll1.push_back(charToString(operCharToString[0]));
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(")");
	}
	else{
		t+=turnString(Num[0])+operCharToString[0];
		coll1.push_back(turnString(Num[0]));
		coll1.push_back(charToString(operCharToString[0]));
	}
	if(rand()%2==1 && !first){
		second=true;
		t+='('+turnString(Num[1])+operCharToString[1]+turnString(Num[2])+')';
		coll1.push_back("(");
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(charToString(operCharToString[1]));
		coll1.push_back(turnString(Num[2]));
		coll1.push_back(")");
	}
	else if(first){
		t+=operCharToString[1];
		coll1.push_back(charToString(operCharToString[1]));
	}
	else{
		t+=turnString(Num[1])+operCharToString[1];
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(charToString(operCharToString[1]));
	}
	if(operCharToString.length()==3){
		if(rand()%2==1 && !second){
			t+='('+turnString(Num[2])+operCharToString[2]+turnString(Num[3])+')';
			coll1.push_back("(");
			coll1.push_back(turnString(Num[2]));
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
			coll1.push_back(")");
		}
		else if(!second){
			t+=turnString(Num[2])+operCharToString[2]+turnString(Num[3]);
			coll1.push_back(turnString(Num[2]));
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
		}
		else{
			t+=operCharToString[2]+turnString(Num[3]);
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
		}
	}
	else if(!second){
		t+=turnString(Num[2]);
		coll1.push_back(turnString(Num[2]));
	}
	return t;
}


//��÷��ŵ�������  
int getPri(string c)   
{  
    switch(c[0])   
    {  
    case '+':  
    case '-':  
        return 0;   //����ǼӼ�������0  
        break;  
    case '*':  
    case '/':  
        return 1;   //����ǳ˳�������1  
        break;  
    case '(':  
    case ')':  
        return -1;  //��������Ϊ������ȼ���������Ų��ᱻ��������������������  
        break;  
     }  
}  
//�жϷ��ŵ�������  
void check(string c, stack<string>& coll2, deque<string>& coll3)   
{    
    if(coll2.empty())   
    {  
        coll2.push(c);  
        return;  
    }  
   
    if(isPra(c))   
    {  
        if(c=="(")   
            coll2.push(c);  
        else   
        {  
            //��������Ԫ��ֱ������������  
            while(coll2.top()!="(")   
            {    
                string ch = coll2.top();  
                coll3.push_back(ch);  
                coll2.pop();  
            }  
  
            //������������ʱ��������������coll3(��׺���ʽ�У�  
            coll2.pop();    
        }  
    }  
    else    //�����������  
    {  
        //ȡ��ջ��Ԫ�أ��뵱ǰ���Ž��������ԱȽ�  
        string sym = coll2.top();    
  
        //�Ƚ������ŵ�������  
        if(getPri(c)<=getPri(sym))    
        {  
            //���c�������Ա�ջ������С����ڣ�����ջ��Ԫ��  
            coll2.pop();  
            //������ѹ��coll3����׺���ʽ����  
            coll3.push_back(sym);  
            //�ݹ����check,�Ƚϵ�ǰ����c����һ��ջ�����ŵ�������  
            check(c,coll2,coll3);     
        }  
        else   
        {  
            //���c��ջ���������ȼ����ǽ�cѹ��coll2(������ջ����  
            coll2.push(c);    
        }  
    }     
}
//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3�� 
void allocate(deque<string>& coll1, stack<string>& coll2, deque<string>& coll3)   
{    

    while(!coll1.empty())   
    {  
        string c = coll1.front();
        coll1.pop_front();  
  
        if(isNum(c))  
        {  
            coll3.push_back(c);  
        }  
        else   
        {  
            //����check��������Բ�ͬ���������ͬ����  
            check(c,coll2,coll3);  
        }  
  
    }
	//��������������coll2��Ԫ��ȫ�������������׺���ʽ��  
    while(!coll2.empty())   
    {    
        string c = coll2.top();  
        coll3.push_back(c);  
        coll2.pop();  
    } 
}
bool isRepeat(int len, int op1,int op2,int opc)//�ж��ظ�      
{
	if(op1>=R||op2>=R)
		return false;
	if((add[op1][op2]==9)||(mul[op1][op2]==9))
		return true;
	if(opc==1)
	{
		switch (len)
		{
			//һ�������
			case 3:
				if((add[op1][op2]==1)||(add[op1][op2]==4)||(add[op1][op2]==6))
					return true;
				else
				{
					add[op1][op2]+=1;
					add[op2][op1]+=1;
					return false;
				}
			//���������
			case 5:
				if((add[op1][op2]==3)||(add[op1][op2]==4)||(add[op1][op2]==8))
					return true;
				else
				{
					add[op1][op2]+=3;
					add[op2][op1]+=3;
					return false;
				}
			//���������
			case 7:
				if((add[op1][op2]==5)||(add[op1][op2]==6)||(add[op1][op2]==8))
					return true;
				else
				{
					add[op1][op2]+=5;
					add[op2][op1]+=5;
					return false;
				}
		}
	}
	if(opc==2)
	{
		switch (len)
		{
			//һ�������
			case 3:
				if((mul[op1][op2]==1)||(mul[op1][op2]==4)||(mul[op1][op2]==6))
					return true;
				else
				{
					mul[op1][op2]+=1;
					mul[op2][op1]+=1;
					return false;
				}
			//���������
			case 5:
				if((mul[op1][op2]==3)||(mul[op1][op2]==4)||(mul[op1][op2]==8))
					return true;
				else
				{
					mul[op1][op2]+=3;
					mul[op2][op1]+=3;
					return false;
				}
			//���������
			case 7:
				if((mul[op1][op2]==5)||(mul[op1][op2]==6)||(mul[op1][op2]==8))
					return true;
				else
				{
					mul[op1][op2]+=5;
					mul[op2][op1]+=5;
					return false;
				}
		}
	}
}
bool calculate(deque<string>& coll3, stack<int>& coll4)//����   
{
	int len= coll3.size();
    while(!coll3.empty())   
    {  
        string c = coll3.front();
        coll3.pop_front();  
          
        //����ǲ�������ѹ��ջ��  
        if(isNum(c))   
        {  
            //��ȥ'0'�ó�ƫ��ֵ����Ϊ��ʵ��ֵ�����ֱ��ת����int��������ԣ���Ϊchar ת��Ϊint�������ֵ������'1'�ı���ֵΪ49  
            int op = atoi(c.c_str());      
            coll4.push(op);       
        }  
        else     //����ǲ���������ջ�е���Ԫ�ؽ��м���  
        {   
            int op1 = coll4.top();  
            coll4.pop();  
            int op2 = coll4.top();  
            coll4.pop();  
			switch(c[0])   
            {  
            case '+':
				if(isRepeat(len,op1,op2,1))
					return false;
                coll4.push(op2+op1);  
                break;  
            case '-': 
				if((op2-op1)<0)
					return false;
                coll4.push(op2-op1);  
                break;  
            case '*':
				if(isRepeat(len,op1,op2,2))
					return false;
                coll4.push(op2*op1);  
                break;  
            case '/': 
				if( op1==0 || op2%op1!=0 )
					return false;
                coll4.push(op2/op1);  //ע����op2(op)op1������op1(op)op2  
                break;  
            }  
        }
    }
	return true;
}
//��ȡִ���ļ�·��
string GetProgramDir()  
{   
    char exeFullPath[MAX_PATH]; // Full path
    string strPath = "";
    GetModuleFileName(NULL,exeFullPath,MAX_PATH);
    strPath=(string)exeFullPath;    // Get full path of the file
    int pos = strPath.find_last_of('\\', strPath.length());
	strPath=strPath.substr(0, pos);
	int t=1,j=0;
	string s="";
	for(int i=0;i<strPath.length();i++){
		if(strPath[i]=='\\'){
			s+=strPath.substr(j,t);
			s+="\\";
			t=0;
			j=i+1;
		}
		t++;
	}
	s+=strPath.substr(j,t);
	strPath=s;
	strPath+="\\";
	strPath+="\\";
    return strPath;  // Return the directory without the file name
}
void initCmd(int argc,char *argv[],string &n,string &r,string &e,string &a)//��ʼ���������
{
		for(int i=1;i<argc;i++)
		{
			string s(argv[i]);
			if(s=="-n")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						n=str;
					}
					if(n=="")
					{
						cout<<"������-n��ֵ��";
						return;
					}
				}
			}
			if(s=="-r")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						r=str;
					}
					if(r=="")
					{
						cout<<"������-r��ֵ";
						return;
					}
				}
			}
			if(s=="-e"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						e=str;
					}
					if(e=="")
					{
						cout<<"������-e��ֵ";
						return;
					}
				}
			}
			if(s=="-a")
			{
				if(i+1<argc)
				{
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a")
					{
						a=str;
					}
					if(a=="")
					{
						cout<<"������-a��ֵ��";
						return;
					}
				}
			}
		}
	}
int main(int argc,char *argv[])
{
	string cinStr[4];
	string n,r,e,a;
	initCmd(argc,argv,n,r,e,a);
	string programDir=GetProgramDir();
	if(n!="" && r!="")//���������Ŀ
	{
		/*DWORD start_time=GetTickCount();*/
		ofstream oufQuestion;
		ofstream oufAnswer;
		oufQuestion.open(programDir+"Exercises.txt");
		oufAnswer.open(programDir+"Answers.txt");
		N=atoi(n.c_str());
		R=atoi(r.c_str());
		string question[10000];//�����Ŀ
		string answer[10000];//��Ŵ�
		int Num[10000][4];//������֣�������ɣ�
		int operCharNumber[10000];//��Ŀ�а����������������������ɣ����Ϊ3������Ϊ1��
		char operate[10000][4];//�����
		add = new int *[R];
		mul = new int *[R];
		for(int i=0;i<R;i++)//��ʼ����������
		{
			add[i]=new int[R];
			mul[i]=new int[R];
			memset(add[i], 0, sizeof(int)*R);
			memset(mul[i], 0, sizeof(int)*R);
		}
		srand((unsigned)time(NULL));
		for(int i=0;i<N;i++)
		{
			string operCharToString="";
			operCharNumber[i]=(rand()%3)+1;
			for(int j=0;j<operCharNumber[i];j++)
			{
				switch((rand()%4)+1)
				{
					case 1:operate[i][j]='+';break;
					case 2:operate[i][j]='-';break;
					case 3:operate[i][j]='*';break;
					case 4:operate[i][j]='/';break;
				}
				operCharToString+=operate[i][j];
			}
			for(int j=0;j<=operCharNumber[i];j++)
			{
				Num[i][j]=rand()%R;
			}
			question[i]="";
			deque<string> coll1;  //ʢ����׺���ʽ  
			stack<string> coll2;  //ʢ�Ų�����  
			deque<string> coll3;    //ʢ�ź�׺���ʽ  
			stack<int>	coll4;  //�����׺���ʽ�ĸ�������
			if(operCharToString.length()>1)
				question[i]=addPra(operCharToString,Num[i],coll1);
			else
			{
				question[i]+=turnString(Num[i][0])+operate[i][0]+turnString(Num[i][0]);
				coll1.push_back(turnString(Num[i][0]));
				coll1.push_back(charToString(operate[i][0]));
				coll1.push_back(turnString(Num[i][0]));
			}
			 //��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��  
			allocate(coll1,coll2,coll3);   
			 //�����׺���ʽ  
			if(!calculate(coll3,coll4))
			{
				question[i]="";
				i--;
				continue;
			}
			else
			{
				oufQuestion<<i+1<<'.'<<question[i]<<"="<<'\n';
				oufAnswer<<i+1<<'.'<<coll4.top()<<'\n';
			}
		}
		cout<<"��Ŀ�������";
		oufQuestion.close();
		oufAnswer.close();
	}
	else if(e!="" && a!="")//�ж��û��������ļ�
	{
		fstream openQuestion;
		openQuestion.open(programDir+e,ios::in);
		if(!openQuestion.good())
		{
			cout<<e+"���ļ�ʧ��";
			return 0;
		}
		fstream openAnswer;
		openAnswer.open(programDir+a,ios::in);
		if(!openAnswer.good())
		{
			cout<<a+"���ļ�ʧ��";
			return 0;
		}
		// ������ռ䣬ע�� + 1
		string *strQuestion = new string[10000]; 
		string *strAnswer = new string[10000]; 
		//����
		int i=0;
		while(!openQuestion.eof())
		{
			char c[100];
			openQuestion.getline(c,100,'\n');
			strQuestion[i]=c;
			char c1[100];
			openAnswer.getline(c1,100,'\n');
			strAnswer[i]=c1;
			i++;
		}
		openQuestion.close();
		openAnswer.close();
		int correct[10000];
		int cor=0;
		int wrong[10000];
		int wro=0;
		for(int j=0;j<i;j++)
		{
			string question,answer;
			for(int k=0;k<strQuestion[j].length();k++)
			{
				if(strQuestion[j][k]=='.')
				{
					strQuestion[j]=strQuestion[j].substr(k+1);
					break;
				}
			}
			question=strQuestion[j];
			for(int k=0;k<strAnswer[j].length();k++)
			{
				if(strAnswer[j][k]=='.')
				{
					strAnswer[j]=strAnswer[j].substr(k+1);
					break;
				}
			}
			answer=strAnswer[j];
			deque<string> coll1;  //ʢ����׺���ʽ  
			stack<string> coll2;  //ʢ�Ų�����  
			deque<string> coll3;    //ʢ�ź�׺���ʽ  
			stack<int>	coll4;  //�����׺���ʽ�ĸ�������
			string s="";
			bool b=false;
			if(question!="")
			{
				for(int k=0;k!=question.length()-1;++k)   
				{  
					//��һ����ÿ���ַ�������ʹ��deque��Ϊdeque������ɾ����ӵ��ٶ����
					if(question[k]=='(')
					{
						coll1.push_back("(");
						continue;
					}
					if(isNotNum(question[k]))
					{
						if(s!="")
							coll1.push_back(s);
						string str=charToString(question[k]);
						coll1.push_back(str);
						s="";
						continue;
					}
					s+=question[k];
				}  
				if(question[question.length()-2]!=')')
					coll1.push_back(s);
				//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3�� 
				allocate(coll1,coll2,coll3);
				//�����׺���ʽ  
				calculate(coll3,coll4);
				if(coll4.top()==atoi(answer.c_str()))
				{
					correct[cor]=j+1;
					cor++;
				}
				else{
					wrong[wro]=j+1;
					wro++;
				}
			}
		}
		ofstream grade;
		grade.open(programDir+"Grade.txt");
		grade<<"Correct:"<<cor<<"(";
		for(int j=0;j<cor;j++)
		{
			grade<<correct[j];
			if(j!=cor-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade<<"Wrong:"<<wro<<"(";
		for(int j=0;j<wro;j++)
		{
			grade<<wrong[j];
			if(j!=wro-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade.close();
	}
	return 0;

}