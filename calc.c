//////////////////////////////////////
// File Name       : calc.c
// Creation Date   : 2016/5/1
//
// Copyright(c) 2016 banban All right reserved.
//////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_MAX 1024
#define NUM_MAX 21

int calc();
void _is_command_o(char *buf);
void _is_command(char *buf,char *buf2);
void char_to_num(char *buf);
void comand_a();
void comand_mc();
void comand_mm();
void comand_mp();
void comand_mr(char *buf);
void char_to_num_2(double m);
void comand_p();
void comand_c();
void comand_q();
void first_func();
void spell_check(char *buf);

char n1[5]={"(n)>"},n2[6]={"(n)>>"},o[5]={"(o)>"};
int flag=0, flag_o=0,spell=0;
int m_cnt=0,ope=0;				/*ope (+,-,*,/)=(1,2,3,4)*/
double NOW=0,TMP=0,TMP2=0;
double m1=0, m2=0, m3=0;		/*メモリー用*/

void first_func(){
	char buf[1]={"\0"};
	int buf_size;
	while(1){
		printf("Please Push C\n");
		buf_size = read(0,buf,2);
		//printf("test:%s\n",buf);
		if(*buf == 'c'|| *buf == 'C'){
			break;
		}else{
			printf("Error1: Incorrect input.\n");
		}
	}
}

void comand_c(){
	TMP=0;
	
	flag=0;
	flag_o=0;
	ope=0;
	m1=0,m2=0,m3=0;
}

void comand_p(){
	printf("NOW=%f\n",TMP);
	printf("Memory\n%f\n%f\n%f\n",m1,m2,m3);
}		

void char_to_num_2(double m){
	double sum=0;
	
	sum = m;
	switch(ope){
		case 1:
			TMP = TMP + sum ;
			break;
		case 2:
			TMP = TMP - sum ;
			break;
		case 3:
			TMP = TMP * sum ;
			break;
		case 4:
			TMP = TMP / sum ;
			break;
		default:
			printf("Error2: Fail to read a input.\n");
			break;
	}
		printf("read data:%-20.5f\n",TMP);
}

void comand_mr(char *buf){
	printf("test:mr\n");
	*buf++;
	switch(*buf){
		case '1':
			spell_check(buf);
			if(spell==0){
				char_to_num_2(m1);
				flag_o = 1;
				flag   = 1;
			}
			break;
		case '2':
			spell_check(buf);
			if(spell==0){
				char_to_num_2(m2);
				flag_o = 1;
				flag   = 1;
			}
			break;
		case '3':
			spell_check(buf);
			if(spell==0){
				char_to_num_2(m3);
				flag_o = 1;
				flag   = 1;
			}
			break;
		default:
			printf("Error3: Incorrect input.\n");
			break;
	}
}

void comand_mp(){
	if(TMP==0){
		printf("Error4:Couldn't memorize zero.\n");
	}else{
		switch(m_cnt){
			case 2:
				m3=TMP;
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			case 1:
				m2=TMP;
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			case 0:
				m1=TMP;
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			default:
				printf("Error5:Memorize up to 3\n");
				break;
		}
	}
}


void comand_mm(){
	if(TMP==0){
		printf("Error6:Couldn't memorize zero.\n");
	}else{
		switch(m_cnt){
			case 2:
				m3=TMP*(-1);
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			case 1:
				m2=TMP*(-1);
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			case 0:
				m1=TMP*(-1);
				TMP=0;
				m_cnt++;
				flag_o = 0;
				flag   = 0;
				break;
			default:
				printf("Error7:Memorize up to 3\n");
				break;
		}
	}
}

void comand_mc(){
	m1=0; m2=0; m3=0; m_cnt=0;
}

void comand_a(){
		printf("Answer is %-20.5f\n",TMP);
}

void char_to_num(char *buf){
	int dot=0,err_flag=0,minus=0;
	double sum=0,pt=0.1;

		for(;*buf != '\n'; *buf++){
			if(*buf=='-'){
				minus=1;
			}else if(*buf>='0' && *buf<='9'){
				sum = sum*10 + *buf-'0';
			}else if(*buf == '.'){
				dot = 1;
				break;
			}else{
				printf("Error8: Incorrect input.\n");
				err_flag=1;
				break;
			}
		}
	*buf++;
	if(dot == 1){
		for(;*buf != '\n';*buf++){
			if(*buf>='0' && *buf<='9'){
				sum = sum + pt*(*buf-'0');
				pt = pt * 0.1;
			}else{
				printf("Erro9: Incorrect input.\n");
				err_flag=1;
				break;
			}
		}
	}
	if(err_flag==0){
		if(minus==1) sum = sum*(-1);
		TMP = TMP + sum ;
		flag_o=1;
		flag=1;
	}else{
		err_flag=0;
	}
}

void comand_q(){
	flag =2;
}

void char_to_num_3(char *buf){
	int dot=0,err_flag=0,minus=0;
	double sum=0,pt=0.1;
	
		for(;*buf != '\n'; *buf++){
			if(*buf=='-'){
				minus =1;
			}else if(*buf>='0' && *buf<='9'){
				sum = sum*10 + *buf-'0';
			}else if(*buf == '.'){
				printf("test:dot\n");
				dot = 1;
				break;
			}else{
				printf("Error10: Incorrect input.\n");
				err_flag=1;
				break;
			}
		}
	*buf++;
	if(dot == 1){
		for(;*buf != '\n';*buf++){
			if(*buf>='0' && *buf<='9'){
				sum = sum + pt*(*buf-'0');
				pt = pt * 0.1;
			}else{
				printf("Erro11: Incorrect input.\n");
				err_flag=1;
				break;
			}
		}
	}
	if(err_flag==0){
		if(minus==1) sum=sum*(-1);
		switch(ope){
			case 1:
				TMP = TMP + sum ;
				break;
			case 2:
				TMP = TMP - sum ;
				break;
			case 3:
				TMP = TMP * sum ;
				break;
			case 4:
				if(sum==0){
					printf("Error12: Zero division.\n");
					break;
				}else{
					TMP = TMP / sum ;
					break;
				}
			default:
				printf("Error13: Fail to read a input.\n");
				break;
		}
			printf("Answer is %-20.5f\n",TMP);
	}
	if(err_flag==0){
		flag_o=1;
		flag=1;
	}else{
		err_flag=0;
	}
}

void spell_check(char *buf){
	*buf++;
	if(*buf=='\n'){
		spell=0;
	}else{
		printf("Error: Fail to read a input.\n");
		spell=1;
	}
}

void _is_command(char *buf,char *buf2){
	switch(*buf){
		case 'q':
		case 'Q':
			spell_check(buf);
			if(spell==0) comand_q();
			break;
		case 'c':
		case 'C':
			spell_check(buf);
			if(spell==0) comand_c();
			break;
		case 'p':
		case 'P':
			spell_check(buf);
			if(spell==0) comand_p();
			break;
		case 'm':
		case 'M':
			*buf++;
			switch(*buf){
				case 'r':
				case 'R':
					comand_mr(buf2);
					break;
				case 'c':
				case 'C':
					spell_check(buf);
					if(spell==0) comand_mc();
					break;
				default:
					printf("Error14: Incorrect input.\n");
					break;
			}
			break;
		case 'a':
		case 'A':
			spell_check(buf);
			if(spell==0) comand_a();
			break;
		case '\n':
			break;
		default:
			printf("Error15: Incorrect input.\n");
			break;
	}
}

void _is_command_o(char *buf){
	switch(*buf){
		case 'q':
		case 'Q':
			spell_check(buf);
			if(spell==0) comand_q();
			break;
		case 'c':
		case 'C':
			spell_check(buf);
			if(spell==0) comand_c();
			break;
		case 'p':
		case 'P':
			spell_check(buf);
			if(spell==0){
				comand_p();
				break;
			}else{
				break;
			}
		case 'm':
		case 'M':
			*buf++;
			switch(*buf){
				case 'c':
				case 'C':
					spell_check(buf);
					if(spell==0) comand_mc();
					break;
				case 'p':
				case 'P':
					spell_check(buf);
					if(spell==0) comand_mp();
					break;
				case 'm':
				case 'M':
					spell_check(buf);
					if(spell==0) comand_mm();
					break;
				default:
					printf("Error16: Incorrect input.\n");
					break;
			}
			break;
		case 'a':
		case 'A':
			spell_check(buf);
			if(spell==0) comand_a();
			break;
		case '\n':
			break;
		default:
			printf("Error17: Incorrect input.\n");
			break;
	}
}

int calc(){
	int buf_size;
	char buf[BUF_MAX];
	while(1){
		/*第一項での処理*/
		while(flag_o==0 && flag==0){
			while(1){
				write(1,n1,5);		/*第一項目*/
				buf_size = read(0,buf,BUF_MAX);
				if(buf_size==-1){
					printf("Error20: Fail to read a input.\n");
				}
				if(buf_size < 0 || NUM_MAX < buf_size){		/*有効入力桁数範囲内かのチェック*/
					if(buf_size < 0){
						printf("Error20: Fail to read a input.\n");
					}else{
						printf("Error21:This input is too long.\n");
					}
				}else{
					buf[buf_size-1]='\n';
					break;
				}
			}
	
			if(*buf>='0' && *buf<='9'){
				char_to_num(buf);
			}else{
				_is_command(buf,buf+3);
			}
		}
	
		/*演算子での処理*/
		while(flag_o==1 && flag==1){
			while(1){
				write(1,o,5);		/*第二項目*/
				buf_size = read(0,buf,BUF_MAX);
				
				if(buf_size < 0 || NUM_MAX < buf_size){		/*有効入力桁数範囲内かのチェック*/
					if(buf_size < 0){
						printf("Error22: Fail to read a input.\n");
					}else{
						printf("Error23:This input is too long.\n");
					}
				}else{
					buf[buf_size-1]='\n';
					break;
				}
			}
			switch(*buf){
				case '+':
					spell_check(buf);
					if(spell==0){
						flag_o = 0;
						ope=1;
						break;
					}else{
						break;
					}
				case '-':
					spell_check(buf);
					if(spell==0){
					flag_o = 0;
					ope=2;
					}
					break;
				case '*':
					spell_check(buf);
					if(spell==0){
					flag_o = 0;
					ope=3;
					}
					break;
				case '/':
					spell_check(buf);
					if(spell==0){
					flag_o = 0;
					ope=4;
					}
					break;
				default:
					_is_command_o(buf);
					break;
			}
			
		}
		
		/*第三項での処理*/
		while(flag_o==0 && flag==1){
			while(1){
				write(1,n2,6);
				buf_size = read(0,buf,BUF_MAX);
				
				if(buf_size <= 0 || NUM_MAX <= buf_size){		/*有効入力桁数範囲内かのチェック*/
					if(buf_size < 0){
						printf("Error24: Fail to read a input.\n");
					}else{
						printf("Error25:This input is too long.\n");
						
					}
				}else{
					buf[buf_size-1]='\n';
					break;
				}
			}
			
			if(*buf>='0' && *buf<='9'|| *buf=='-'){
				char_to_num_3(buf);
				
			}else{
				_is_command(buf,buf+3);
			}
		}
		if(flag==2){
			return 0;
		}
	}
}
	
	
	
int main(){
	printf("Welcome\n");
	first_func();	/*最初のCの入力*/
	calc();
	
	return 0;
}
