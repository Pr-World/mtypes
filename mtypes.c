#include "mtypes.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*

2/18/2022

Format specifier for lists:-

d = int [-]  = 0
ld = long int [_] = 1

f = float [.] = 2
lf = double [;] = 3
lF = long double [:] = 4

c = char  [^] = 5
s = string [$] = 6
*/

//* base 64 encode decode {

char base46_map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                     'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

void _mtypes_b64enc(char * cipher,char* plain) {
	
    char counts = 0;
    char buffer[3];
    _mtypes_null(cipher);
    int i = 0, c = 0;

    for(i = 0; plain[i] != '\0'; i++) {
        buffer[counts++] = plain[i];
        if(counts == 3) {
            cipher[c++] = base46_map[buffer[0] >> 2];
            cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            cipher[c++] = base46_map[((buffer[1] & 0x0f) << 2) + (buffer[2] >> 6)];
            cipher[c++] = base46_map[buffer[2] & 0x3f];
            counts = 0;
        }
    }

    if(counts > 0) {
        cipher[c++] = base46_map[buffer[0] >> 2];
        if(counts == 1) {
            cipher[c++] = base46_map[(buffer[0] & 0x03) << 4];
            cipher[c++] = '=';
        } else {                      // if counts == 2
            cipher[c++] = base46_map[((buffer[0] & 0x03) << 4) + (buffer[1] >> 4)];
            cipher[c++] = base46_map[(buffer[1] & 0x0f) << 2];
        }
        cipher[c++] = '=';
    }

    cipher[c] = '\0';   /* string padding character */
    return;
}

void _mtypes_b64dec(char * plain,char* cipher) {
	_mtypes_null(plain);
    char counts = 0;
    char buffer[4];
    int i = 0, p = 0;

    for(i = 0; cipher[i] != '\0'; i++) {
        char k;
        for(k = 0 ; k < 64 && base46_map[k] != cipher[i]; k++);
        buffer[counts++] = k;
        if(counts == 4) {
            plain[p++] = (buffer[0] << 2) + (buffer[1] >> 4);
            if(buffer[2] != 64)
                plain[p++] = (buffer[1] << 4) + (buffer[2] >> 2);
            if(buffer[3] != 64)
                plain[p++] = (buffer[2] << 6) + buffer[3];
            counts = 0;
        }
    }

    plain[p] = '\0';    /* string padding character */
    return;
}

//*}

void _mtypes_null(char * _Str){
	int i=0,j=strlen(_Str);
	for(i=0;i<j;i++){
		_Str[i] = '\0';
	}
}
//int 2 string
void _mtypes_int2str(int in,char * _Str)
{
	_mtypes_null(_Str);
	int x=0,x2=0,in2=in,len=0;
	
	if(in<0){
		_Str[0]='-';
		x2=1;
		in = -in;
	}
	
	while(1){in2/=10;len++;if(in2==0){break;}}
	in2=in;
	
	while(1)
	{
		_Str[x2] = '0'+(in%(int)pow(10,len-x))/(pow(10,len-x-1));
		x++;
		x2++;
		if(x==len){
			if(x2!=x){
				_Str[x2] = '\0';
			}
			return;
		}
	}
}

//long int to string
void _mtypes_lint2str(long int in,char * _Str)
{
	_mtypes_null(_Str);
	int x=0,x2=0,in2=in,len=0;
	
	if(in<0){
		_Str[0]='-';
		x2=1;
		in = -in;
	}
	
	while(1){in2/=10;len++;if(in2==0){break;}}
	in2=in;
	
	while(1)
	{
		_Str[x2] = '0'+(in%(int)pow(10,len-x))/(pow(10,len-x-1));
		x++;
		x2++;
		if(x==len){
			if(x2!=x){
				_Str[x2] = '\0';
			}
			return;
		}
	}
}
//double / float to string
void _mtypes_d2str(double d,char * _Str)
{
	int dupto=0,x,y,intv=(int)(d),pointv=0,z;
	_mtypes_null(_Str);
	_mtypes_int2str(intv,_Str);
	y = strlen(_Str);
	if(d<0){
		d=-d;
	}
	for(x=0;x<6;x++){
		if(((int)(d*pow(10,x+1)))%10!=0){
			dupto=x+1;
		}
	}
	for(x=0;x<dupto;x++){
		pointv*=10;
		pointv+=(int)(d*pow(10,x+1))%10;
	}
	if(dupto==0){
		return;
	}
	_Str[y]='.';
	z=0;
	while(1)
	{
		if(pointv==0){
			break;
		}
		z*=10;
		z+=pointv%10;
		pointv/=10;
	}
	pointv=z;
	x=1;
	while(1)
	{
		if(pointv%10==0||pointv==0){
			return;
		}
		z = pointv%10;
		_Str[y+x] = '0'+z;
		 
		pointv/=10;
		x++;
	}
}
// long double to string
void _mtypes_ld2str(long double d,char * _Str)
{
	int dupto=0,x,y,intv=(int)(d),pointv=0,z;
	_mtypes_null(_Str);
	_mtypes_int2str(intv,_Str);
	y = strlen(_Str);
	if(d<0){
		d=-d;
	}
	for(x=0;x<6;x++){
		if(((int)(d*pow(10,x+1)))%10!=0){
			dupto=x+1;
		}
	}
	for(x=0;x<dupto;x++){
		pointv*=10;
		pointv+=(int)(d*pow(10,x+1))%10;
	}
	if(dupto==0){
		return;
	}
	_Str[y]='.';
	z=0;
	while(1)
	{
		if(pointv==0){
			break;
		}
		z*=10;
		z+=pointv%10;
		pointv/=10;
	}
	pointv=z;
	x=1;
	while(1)
	{
		if(pointv%10==0||pointv==0){
			return;
		}
		z = pointv%10;
		_Str[y+x] = '0'+z;
		 
		pointv/=10;
		x++;
	}
}

void sencode(char * _Src,char * _Dst){
	_mtypes_null(_Dst+0);
	_mtypes_b64enc(_Dst+0,_Src+0);
}

void sdecode(char * _Src,char * _Dst){
	_mtypes_null(_Dst+0);
	_mtypes_b64dec(_Dst+0,_Src+0);
}


/*

2/18/2022

Format specifier for lists:-

d = int [-]  = 0
ld = long int [_] = 1

f = float [.] = 2
lf = double [;] = 3
lF = long double [:] = 4

c = char  [^] = 5
s = string [$] = 6
*/

list lcreate(char * _Fm,...)
{
	va_list _va;
	list a;
	char tmps[100],tmps2[100];
	_mtypes_null(a._cstr);
	a._cstr[0] = '[';
	int x=0;
	char c;
	va_start(_va,_Fm);
	for(x=0;x<strlen(_Fm);x++)
	{
		c = _Fm[x];
		if(c=='d'){
			strcat(a._cstr,"-");
			_mtypes_int2str(va_arg(_va,int),tmps);
			sencode(tmps,tmps2);
			strcat(a._cstr,tmps2);
		}else if(c=='f'){
			strcat(a._cstr,".");
			_mtypes_d2str(va_arg(_va,double),tmps);
			sencode(tmps,tmps2);
			strcat(a._cstr,tmps2);
		}else if(c=='l'){
			x++;
			if(_Fm[x]=='f'){
				strcat(a._cstr,";");
				_mtypes_d2str(va_arg(_va,double),tmps);
				sencode(tmps,tmps2);
				strcat(a._cstr,tmps2);
			}else if(_Fm[x]=='F'){
				strcat(a._cstr,":");
				_mtypes_ld2str(va_arg(_va,double),tmps);
				sencode(tmps,tmps2);
				strcat(a._cstr,tmps2);
			}else if(_Fm[x]=='d'){
				_mtypes_lint2str(va_arg(_va,double),tmps);
				sencode(tmps,tmps2);
				strcat(a._cstr,tmps2);
			}else{
				list p;
				p._err = _MTYPES_UNKFMT;
				return p;
			}
		}else if(c=='c'){
			strcat(a._cstr,"^");
			_mtypes_null(tmps);
			tmps[0] = va_arg(_va,int);
			sencode(tmps,tmps2);
			strcat(a._cstr,tmps2);
		}else if(c=='s'){
			strcat(a._cstr,"$");
			sencode(va_arg(_va,char *),tmps2);
			strcat(a._cstr,tmps2);
		}else{
			list p;
			p._err = _MTYPES_UNKFMT;
			return p;
		}
		strcat(a._cstr,",");
	}
	a._cstr[strlen(a._cstr)-1] = ']'; 
	va_end(_va);
	return a;
}

void _mtypes_lgelem(list a,int elem,char * _Dst){
	_mtypes_null(_Dst+0);
	int b,c,d=0,e,f;
	for(b=0;b<strlen(a._cstr);b++){
		c = a._cstr[b];
		if(c=='$'||c=='^'||c=='-'||c=='_'||c=='.'||c==';'||c==':'){
			if(d==elem){
				for(e=1;e<strlen(a._cstr)-b;e++){
					if(a._cstr[b+e]==','||a._cstr[b+e]==']'){
						if(_Dst[strlen(_Dst)-1]!=a._cstr[b+e-1]){
							_Dst[strlen(_Dst)-1] = '\0';
						}
						break;
					}
					_Dst[e-1] = a._cstr[b+e];
				}
			}
			d++;
		}
	}
}
//type management - 2/20/2022
int lgtype(list a,int elem){
	int x,y,z=0;
	for(x=0;x<strlen(a._cstr);x++){
		y = a._cstr[x];
		if(y=='$'||y=='^'||y=='-'||y=='_'||y=='.'||y==';'||y==':'){
			if(z==elem){
				if(y=='-'){
					return 0;
				}else if(y=='_'){
					return 1;
				}else if(y=='.'){
					return 2;
				}else if(y==';'){
					return 3;
				}else if(y==':'){
					return 4;
				}else if(y=='^'){
					return 5;
				}else if(y=='$'){
					return 6;
				}else{
					return -1;
				}	
			}
			z++;
		}
	}
	return -1;
}

int lgvalint(list a,int elem){
	char smv[100],smv2[100];
	int b,ret=0,s=0;
	b = lgtype(a,elem);;
	if(b!=0){
		return 0;
	}
	_mtypes_lgelem(a,elem,smv);
	sdecode(smv,smv2);
	//now convert smv2 to int!
	if(smv2[0]=='-'){
		s=1;
	}
	for(b=s;b<strlen(smv2);b++){
		ret*=10;
		if(smv2[b]>'9'||smv2[b]<'0'){
			//not an int
			return 0;
		}
		ret+=(smv2[b]-'0');
	}
	if(s*-1){
		ret*=-1;
	}
	return ret;
}

char lgvalchar(list a,int elem){
	char smv[100],smv2[100],ret;
	int b,c,d;
	b = lgtype(a,elem);
	if(b!=5){
		return 0;
	}
	_mtypes_lgelem(a,elem,smv);
	sdecode(smv,smv2);
	return smv2[0];
}

char lgvallongint(list a,int elem){
	char smv[100],smv2[100];
	int b,s=0;
	long int ret=0;
	b = lgtype(a,elem);;
	if(b!=1){
		return 0;
	}
	_mtypes_lgelem(a,elem,smv);
	sdecode(smv,smv2);
	//now convert smv2 to int! - converted 2/22/2022
	if(smv2[0]=='-'){
		s=1;
	}
	for(b=s;b<strlen(smv2);b++){
		ret*=10;
		if(smv2[b]>'9'||smv2[b]<'0'){
			//not an int
			return 0;
		}
		ret+=(smv2[b]-'0');
	}
	if(s*-1){
		ret*=-1;
	}
	return ret;
}

double lgvalfdouble(list a,int elem){
	char smv[100],smv2[100];
	int b,c=0,s=0,fval=0,sval=0,p=0,l=0;
	double ret;
	b = lgtype(a,elem);
	if(b!=2&&b!=3){
		return 0.0;
	}
	_mtypes_lgelem(a,elem,smv);
	sdecode(smv,smv2);
	if(smv2[b]=='-'){
		s=1;
	}
	//weird error happening - fixed 2/23/2022
	
	for(b=s;b<strlen(smv2);b++){
		c = smv2[b];
		if(smv2[b]=='.'){
			p=1;
			continue;
		}
		if(p){
			l++;
			sval*=10;
			sval+=smv2[b]-'0';
		}else{
			fval*=10;
			fval+=smv2[b]-'0';
		}
	}
	ret = fval+(double)sval/pow(10,l);
	return ret;
}

long double lgvallongdouble(list a,int elem){
	char smv[100],smv2[100];
	int b,c=0,s=0,fval=0,sval=0,p=0,l=0;
	long double ret;
	b = lgtype(a,elem);
	if(b!=2&&b!=3){
		return 0.0;
	}
	_mtypes_lgelem(a,elem,smv);
	sdecode(smv,smv2);
	if(smv2[b]=='-'){
		s=1;
	}
	//weird error happening - fixed 2/23/2022
	
	for(b=s;b<strlen(smv2);b++){
		c = smv2[b];
		if(smv2[b]=='.'){
			p=1;
			continue;
		}
		if(p){
			l++;
			sval*=10;
			sval+=smv2[b]-'0';
		}else{
			fval*=10;
			fval+=smv2[b]-'0';
		}
	}
	ret = (long double)fval+(long double)sval/pow(10,l);
	return ret;
}

void lgvalstring(list a,int elem,char * _Dst){
	_mtypes_null(_Dst);
	char smv[100],smv2[100];
	int b,c,d;
	b = lgtype(a,elem);
	if(b!=6){
		return;
	}
	_mtypes_lgelem(a,elem,smv+0);
	sdecode(smv,smv2);
	strncpy(_Dst+0,smv2+0,strlen(smv2));
}

/*

2/23/2022

Format specifier for lists:-

d = int [-]  = 0
ld = long int [_] = 1

f = float [.] = 2
lf = double [;] = 3
lF = long double [:] = 4

c = char  [^] = 5
s = string [$] = 6
*/

list lappend(list a,char * _Fm,...){
	va_list _va;
	va_start(_va,_Fm);
	list b;
	char smv[100],smv2[100],tmpv[10];
	int c,d;
	strcpy(b._cstr,a._cstr);
	b._cstr[strlen(b._cstr)-1] = '\0';
	printf("\nBCSTR:%s\n",b._cstr);
	strcat(b._cstr,",");
	for(c=0;c<strlen(_Fm);c++){
		d = _Fm[c];
		if(d=='d'){
			_mtypes_int2str(va_arg(_va,int),smv);
			sencode(smv,smv2);
			strcat(b._cstr,"-");
			strcat(b._cstr,smv2);
		}else if(d=='f'){
			_mtypes_d2str(va_arg(_va,double),smv);
			sencode(smv,smv2);
			strcat(b._cstr,".");
			strcat(b._cstr,smv2);
		}else if(d=='c'){
			_mtypes_null(tmpv);
			tmpv[0] = va_arg(_va,int);
			sencode(tmpv,smv2);
			strcat(b._cstr,"^");
			strcat(b._cstr,smv2);
		}else if(d=='s'){
			sencode(va_arg(_va,char *),smv2);
			strcat(b._cstr,"$");
			strcat(b._cstr,smv2);
		}else if(d=='l'){
			c++;
			d=_Fm[c];
			if(d=='d'){
				_mtypes_lint2str(va_arg(_va,long int),smv);
				sencode(smv,smv2);
				strcat(b._cstr,"_");
				strcat(b._cstr,smv2);
			}else if(d=='f'){
				_mtypes_d2str(va_arg(_va,double),smv);
				sencode(smv,smv2);
				strcat(b._cstr,";");
				strcat(b._cstr,smv2);
			}else if(d=='F'){
				_mtypes_ld2str(va_arg(_va,long double),smv);
				sencode(smv,smv2);
				strcat(b._cstr,":");
				strcat(b._cstr,smv2);
			}else{
				list p;
				p._err = _MTYPES_UNKFMT;
				return p;
			}
		}else{
			list p;
			p._err = _MTYPES_UNKFMT;
			return p;
		}
		if(c+1==strlen(_Fm)){
			strcat(b._cstr,"]");
		}else{
			strcat(b._cstr,",");
		}
	}
	va_end(_va);
	return b;
}

list lrepl(list a,int elem,char * _Fm,...){
	va_list _va;
	va_start(_va,_Fm);
	char tmps[100],tmps2[100];
	list rt;
	int b,c,d=-1,e;
	for(b=1;b<strlen(a._cstr);b++){
		c = a._cstr[b];
		if(d==elem){
			for(e=b;e<strlen(a._cstr);e++){
				if(a._cstr[e]==','||a._cstr[e]==']'){
					break;
				}
			}
			if(elem==0){
				_mtypes_null(rt._cstr);
				strcpy(rt._cstr,"[");
			}else{
				_mtypes_null(rt._cstr);
				strncpy(rt._cstr,a._cstr,b);
			}
			if(_Fm[0]=='d'){
				_mtypes_int2str(va_arg(_va,int),tmps);
				strcat(rt._cstr,"-");
				sencode(tmps,tmps2);
			}else if(_Fm[0]=='f'){
				_mtypes_d2str(va_arg(_va,double),tmps);
				strcat(rt._cstr,".");
				sencode(tmps,tmps2);
			}else if(_Fm[0]=='c'){
				_mtypes_null(tmps);
				tmps[0] = va_arg(_va,int);
				strcat(rt._cstr,"^");
				sencode(tmps,tmps2);
			}else if(_Fm[0]=='s'){
				_mtypes_null(tmps);
				strcat(rt._cstr,"$");
				sencode(va_arg(_va,char *),tmps2);
			}else if(_Fm[0]=='l'){
				if(_Fm[1]=='d'){
					strcat(rt._cstr,"_");
					_mtypes_lint2str(va_arg(_va,long int),tmps);
					sencode(tmps,tmps2);
				}else if(_Fm[1]=='f'){
					strcat(rt._cstr,";");
					_mtypes_d2str(va_arg(_va,double),tmps);
					sencode(tmps,tmps2);
				}else if(_Fm[2]=='F'){
					strcat(rt._cstr,":");
					_mtypes_ld2str(va_arg(_va,long double),tmps);
					sencode(tmps,tmps2);
				}else{
					list kl;
					kl._err = _MTYPES_UNKFMT;
					return kl;
				}
			}else{
				list kl;
				kl._err = _MTYPES_UNKFMT;
				return kl;
			}
			if(elem==0){
				strcat(rt._cstr,tmps2);
				strcat(rt._cstr,",");
				strcat(rt._cstr,a._cstr+e+1);
				return rt;
			}else{
				strcat(rt._cstr,tmps2);
				strcat(rt._cstr,",");
				strcat(rt._cstr,a._cstr+e+1);
				return rt;
			}
		}
		if(c=='$'||c=='^'||c=='-'||c=='_'||c=='.'||c==';'||c==':'){
			d++;
		}
	}
	va_end(_va);
}

int lglen(list a){
	int x,y,len=0;
	for(x=0;x<strlen(a._cstr);x++)	{
		y = a._cstr[x];
		if(y=='$'||y=='^'||y=='-'||y=='_'||y=='.'||y==';'||y==':'){
			len++;
		}
	}
	return len;
}

list lpop(list a,int elem){
	int l=lglen(a);
	list b;
	if(elem>l){
		b._err = _MTYPES_UNKELM;
		return b;
	}
	int x,y,z=-1,v;
	for(x=0;x<strlen(a._cstr);x++){
		y = a._cstr[x];
		if(z==elem){
			for(z=x+1;z<strlen(a._cstr);z++){
				if(a._cstr[z]==','||a._cstr[z]==']'){
					break;
				}
			}
			_mtypes_null(b._cstr);
			if(elem==l-1){
				strncpy(b._cstr,a._cstr,x-2);
				a._cstr[strlen(a._cstr)-1] = '\0';
				strcat(b._cstr,"]");
			}else{
				strncpy(b._cstr,a._cstr,x-1);
				strcat(b._cstr,a._cstr+z+1);
			}
			return b;
		}
		if(y=='$'||y=='^'||y=='-'||y=='_'||y=='.'||y==';'||y==':'){
			z++;
		}
	}
}

void lprint(list a){
	int b,c;
	char smv[100],smv2[100];
	printf("[");
	for(b=0;b<lglen(a);b++){
		_mtypes_lgelem(a,b,smv);
		sdecode(smv,smv2);
		c = lgtype(a,b);
		if(c==5){
			printf("'%s'",smv2);
		}else if(c==6){
			printf("\"%s\"",smv2);
		}else{
			printf("%s",smv2);
		}
		printf(",");
	}
	printf("\b]");
}
