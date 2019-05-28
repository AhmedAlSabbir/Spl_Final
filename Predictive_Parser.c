#include<stdio.h>
#include<ctype.h>
#include<string.h>




int number,n=0;
int m=0;
char f[10];
int k;
char ck;
int e;
char firstCalculate[10][100];
void getfirst(char , int , int);
void follow(char c);
char followCalculate[10][100];
char Production[10][10], first[10];
void followfirst(char , int , int);

void getfirst(char c ,int q1 , int q2)
{
	int j;
	if(!(isupper(c))){
		first[n++]=c;
	}
	for(j=0;j<number;j++)
	{
		if(Production[j][0]==c)
		{
			if(Production[j][2]=='#'){
				if(Production[q1][q2] == '\0')
					first[n++]='#';
				else if(Production[q1][q2] != '\0' && (q1 != 0 || q2 != 0))
				{
					getfirst(Production[q1][q2], q1, (q2+1));
				}
				else
					first[n++]='#';
			}
			else if(!isupper(Production[j][2])){
				first[n++]=Production[j][2];
			}
			else {
				getfirst(Production[j][2], j, 3);
			}
		}
	}
}



void follow(char c)
{
	int i ,j;
	if(Production[0][0]==c){
 		f[m++]='$';
 	}
 	for(i=0;i<10;i++)
 	{
  		for(j=2;j<10;j++)
  		{
   			if(Production[i][j]==c)
   			{
    			if(Production[i][j+1]!='\0'){
					followfirst(Production[i][j+1],i,(j+2));
 				}
    			if(Production[i][j+1]=='\0'&&c!=Production[i][0]){
     				follow(Production[i][0]);
				}
   			}
  		}
 	}
}



void followfirst(char c, int c1 , int c2)
{
    int k;
    if(!(isupper(c)))
		f[m++]=c;
	else{
		int i=0,j=1;
		for(i=0;i<number;i++)
		{
			if(firstCalculate[i][0] == c)
				break;
		}
		while(firstCalculate[i][j] != '!')
		{
			if(firstCalculate[i][j] != '#'){
				f[m++] = firstCalculate[i][j];
			}
			else{
				if(Production[c1][c2] == '\0'){
					follow(Production[c1][0]);
				}
				else{
					followfirst(Production[c1][c2],c1,c2+1);
				}
			}
			j++;
		}
	}

	//change

}
int main(int argc,char **argv)
{
	int jm=0;
	int km=0;
	int i,choice;
	char c,ch;
	printf("how many Productions do you want to input?");
	scanf("%d",&number);
	printf("\nEnter %d Productions:\n\n",number);
	for(i=0;i<number;i++)
	{
		scanf("%s%c",Production[i],&ch);
	}
	int myKey;
	char complete[number];
	int ptr = -1;
	for(k=0;k<number;k++){
		for(myKey=0;myKey<100;myKey++){
			firstCalculate[k][myKey] = '!';
		}
	}
	int myPoint1 = 0,myPoint2,load;
	for(k=0;k<number;k++)
	{
		c=Production[k][0];
		myPoint2 = 0;
		load = 0;
		for(myKey = 0; myKey <= ptr; myKey++)
			if(c == complete[myKey])
				load = 1;
		if (load == 1)
			continue;
		getfirst(c,0,0);
		ptr+=1;
		complete[ptr] = c;
		printf("\n First(%c)= { ",c);
		firstCalculate[myPoint1][myPoint2++] = c;
		for(i=0+jm;i<n;i++){
			int var = 0,flag = 0;
  			for(var=0;var<myPoint2;var++){
  				if (first[i] == firstCalculate[myPoint1][var]){
  					flag = 1;
  					break;
				}
			}
			if(flag == 0){
  		 		printf("%c, ",first[i]);
  				firstCalculate[myPoint1][myPoint2++] = first[i];
			}
		}
		printf("}\n");
		jm=n;
		myPoint1++;
	}
	printf("\n");
	printf("-----------------------------------------------\n\n");
	char completee[number];
	ptr = -1;
	for(k=0;k<number;k++){
		for(myKey=0;myKey<100;myKey++){
			followCalculate[k][myKey] = '!';
		}
	}
	myPoint1 = 0;
	int Anothervar = 0;
	for(e=0;e<number;e++)
  	{
		ck=Production[e][0];
		myPoint2 = 0;
		load = 0;
		for(myKey = 0; myKey <= ptr; myKey++)
			if(ck == completee[myKey])
				load = 1;
		if (load == 1)
			continue;
  		Anothervar += 1;
		follow(ck);
  		ptr+=1;
		completee[ptr] = ck;
  		printf(" Follow(%c) = { ",ck);
  		followCalculate[myPoint1][myPoint2++] = ck;
  		for(i=0+km;i<m;i++){
  			int var = 0,flag = 0;
  			for(var=0;var<myPoint2;var++){
  				if (f[i] == followCalculate[myPoint1][var]){
  					flag = 1;
  					break;
				}
			}
			if(flag == 0){
  		 		printf("%c, ",f[i]);
  				followCalculate[myPoint1][myPoint2++] = f[i];
  			}
  		}
  		printf(" }\n\n");
		km=m;
		myPoint1++;
	}
	char MyTemp[10];
	for(k=0;k<10;k++){
		MyTemp[k] = '!';
	}
	int ap,varNew,sid = 0;
	for(k=0;k<number;k++){
		for(myKey=0;myKey<number;myKey++){
			if(!isupper(Production[k][myKey]) && Production[k][myKey]!= '#' && Production[k][myKey] != '=' && Production[k][myKey] != '\0'){
				varNew = 0;
				for(ap = 0;ap < sid; ap++){
					if(Production[k][myKey] == MyTemp[ap]){
						varNew = 1;
						break;
					}
				}
				if(varNew == 0){
					MyTemp[sid] = Production[k][myKey];
					sid ++;
				}
			}
		}
	}
	MyTemp[sid] = '$';
	sid++;
	printf("\n\t\t\t\t\t\t\t Predictive Parsing myTable for the given grammar :-");
	printf("\n\t\t\t=====================================================================================================================\n");
	printf("\t\t\t\t|\t");
	for(ap = 0;ap < sid; ap++){
		printf("%c\t\t",MyTemp[ap]);
	}
	printf("\n\t\t\t=====================================================================================================================\n");
	char first_Production[number][sid];
	for(ap=0;ap<number;ap++){
		int myDes = 0;
		k = 2;
		int ct = 0;
		char myTemp[100];
		while(Production[ap][k] != '\0'){
			if(!isupper(Production[ap][k])){
				myTemp[ct++] = Production[ap][k];
				myTemp[ct++] = '_';
				myTemp[ct++] = '\0';
				k++;
				break;
			}
			else{
				int newVarr=0;
				int rev = 0;
				for(newVarr=0;newVarr<number;newVarr++){
					if(firstCalculate[newVarr][0] == Production[ap][k]){
						for(rev=1;rev<100;rev++){
							if(firstCalculate[newVarr][rev] != '!'){
								myTemp[ct++] = firstCalculate[newVarr][rev];
							}
							else
								break;
						}
					break;
					}
				}
				myTemp[ct++] = '_';
			}
			k++;
		}
		int newVarr = 0,rev;
		for(rev = 0;rev<ct;rev++){
			if(myTemp[rev] == '#'){
				newVarr = 1;
			}
			else if(myTemp[rev] == '_'){
				if(newVarr == 1){
					newVarr = 0;
				}
				else
					break;
			}
			else{
				first_Production[ap][myDes++] = myTemp[rev];
			}
		}
	}
	char myTable[Anothervar][sid+1];
	ptr = -1;
	for(ap = 0; ap < Anothervar ; ap++){
		for(myKey = 0; myKey < (sid + 1) ; myKey++){
			myTable[ap][myKey] = '!';
		}
	}
	for(ap = 0; ap < number ; ap++){
		ck = Production[ap][0];
		load = 0;
		for(myKey = 0; myKey <= ptr; myKey++)
			if(ck == myTable[myKey][0])
				load = 1;
		if (load == 1)
			continue;
		else{
			ptr = ptr + 1;
			myTable[ptr][0] = ck;
		}
	}
	for(ap = 0; ap < number ; ap++){
		int rev = 0;
		while(first_Production[ap][rev] != '\0'){
			int to,ni=0;
			for(to=0;to<sid;to++){
				if(first_Production[ap][rev] == MyTemp[to]){
					ni = 1;
				}
			}
			if(ni == 1){
				char xz = Production[ap][0];
				int let=0;
				while(myTable[let][0] != xz){
					let = let + 1;
				}
				int vz=0;
				while(MyTemp[vz] != first_Production[ap][rev]){
					vz = vz + 1;
				}
				myTable[let][vz+1] = (char)(ap + 65);
			}
			rev++;
		}
	}
	for(k=0;k<sid;k++){
		for(myKey=0;myKey<100;myKey++){
			if(firstCalculate[k][myKey] == '!'){
				break;
			}
			else if(firstCalculate[k][myKey] == '#'){
				int fz = 1;
				while(followCalculate[k][fz] != '!'){
					char xz = Production[k][0];
					int let=0;
					while(myTable[let][0] != xz){
						let = let + 1;
					}
					int vz=0;
					while(MyTemp[vz] != followCalculate[k][fz]){
						vz = vz + 1;
					}
					myTable[k][vz+1] = '#';
					fz++;
				}
				break;
			}
		}
	}
	for(ap = 0; ap < Anothervar ; ap++){
		printf("\t\t\t   %c\t|\t",myTable[ap][0]);
		for(myKey = 1; myKey < (sid + 1) ; myKey++){
			if(myTable[ap][myKey] == '!')
				printf("\t\t");
			else if(myTable[ap][myKey] == '#')
				printf("%c=#\t\t",myTable[ap][0]);
			else{
				int mum = (int)(myTable[ap][myKey]);
				mum -= 65;
				printf("%s\t\t",Production[mum]);
			}
		}
		printf("\n");
		printf("\t\t\t---------------------------------------------------------------------------------------------------------------------");
		printf("\n");
	}
	int j;
	printf("\n\nEnter a string: ");
	char input[100];
	scanf("%s%c",input,&ch);
	printf("\n\t\t\t\t\t===========================================================================\n");
	printf("\t\t\t\t\t\tStack\t\t\tInput\t\t\tAction");
	printf("\n\t\t\t\t\t===========================================================================\n");
	int i_ptr = 0,s_ptr = 1;
	char stack[100];
	stack[0] = '$';
	stack[1] = myTable[0][0];
	while(s_ptr != -1){
		printf("\t\t\t\t\t\t");
		int myVariable = 0;
		for(myVariable=0;myVariable<=s_ptr;myVariable++){
			printf("%c",stack[myVariable]);
		}
		printf("\t\t\t");
		myVariable = i_ptr;
		while(input[myVariable] != '\0'){
			printf("%c",input[myVariable]);
			myVariable++;
		}
		printf("\t\t\t");
		char her = input[i_ptr];
		char him = stack[s_ptr];
		s_ptr--;
		if(!isupper(him)){
			if(her == him){
				i_ptr++;
				printf("pop action\n");
			}
			else{
				printf("\nstring is not accepted by the parser\n");
				exit(0);
			}
		}
		else{
			for(i=0;i<sid;i++){
				if(MyTemp[i] == her)
					break;
			}
			char produ[100];
			for(j=0;j<Anothervar;j++){
				if(him == myTable[j][0]){
					if (myTable[j][i+1] == '#'){
						printf("%c=#\n",myTable[j][0]);
						produ[0] = '#';
						produ[1] = '\0';
					}
					else if(myTable[j][i+1] != '!'){
						int mum = (int)(myTable[j][i+1]);
						mum -= 65;
						strcpy(produ,Production[mum]);
						printf("%s\n",produ);
					}
					else{
						printf("\nstring is not accepted by the parser\n");
						exit(0);
					}
				}
			}
			int le = strlen(produ);
			le = le - 1;
			if(le == 0){
				continue;
			}
			for(j=le;j>=2;j--){
				s_ptr++;
				stack[s_ptr] = produ[j];
			}
		}
	}
	printf("\n\t\t\t=======================================================================================================================\n");
	if (input[i_ptr] == '\0'){
		printf("\t\t\t\t\t\t\t\tstring is accepted\n");
	}
	else
		printf("\n\t\t\t\t\t\t\t\tstring is not accepted\n");
	printf("\t\t\t=======================================================================================================================\n");
}



