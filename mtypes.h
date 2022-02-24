#ifndef _MTYPES_H_INCL
#define _MTYPES_H_INCL

#ifndef va_start
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_copy __builtin_va_copy
#define va_arg __builtin_va_arg
#define va_list __builtin_va_list
#endif

#define _MTYPES_MXCHLIM 1000
#define _MTYPES_ERRTYP unsigned short int
#define _MTYPES_UNKFMT 1
#define _MTYPES_OVFLOW 2
#define _MTYPES_UNKELM 3

/*

2/18/2022

Format specifier for lists:-

d		= 	int			[-]	= 0
ld		= 	long int	[_]	= 1 -- no full support
						
f 		=	float		[.] = 2
lf		=	double		[;] = 3
lF		=	long double	[:] = 4 -- no full support

c 		= 	char  		[^] = 5
s 		= 	string 		[$] = 6
*/

typedef struct{
	char _cstr[_MTYPES_MXCHLIM];
	_MTYPES_ERRTYP _err;
}list;

//function declaration

//mtypes internal functions {
void _mtypes_b64enc(char * cipher,char* plain);
void _mtypes_b64dec(char * plain,char* cipher);
void _mtypes_null(char * _Str);
void _mtypes_int2str(int in,char * _Str);
void _mtypes_lint2str(long int in,char * _Str);
void _mtypes_d2str(double d,char * _Str);
void _mtypes_ld2str(long double d,char * _Dest);
void _mtypes_lgelem(list a,int elem,char * _Dst);
// }

// string encode/decode public functions {
void sencode(char * _Src,char * _Dst);
void sdecode(char * _Src,char * _Dst);
// }

//list control functions {
list lcreate(char * _Fm,...);
list lappend(list a,char * _Fm,...);
list lrepl(list a,int elem,char * _Fm,...);
list lpop(list a,int elem);
void lprint(list a);
int lgtype(list a,int elem);
int lglen(list a);
// }

//list value functions {
int lgvalint(list a,int elem);
double lgvalfdouble(list a,int elem);
char lgvalchar(list a,int elem);
void lgvalstring(list a,int elem,char * _Dst);
// }

#endif
