/**
 * FILE: students_tools.h
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */
#ifndef ASP_A_BAERISWYL_PASSUELLO_TOOLS_H_
#define ASP_A_BAERISWYL_PASSUELLO_TOOLS_H_

// booleans
#define BYTE  char
#define FALSE ((BYTE)0)
#define TRUE  (!FALSE)
#define TO_BOOL(x) (!(!x))

// size pre-computing
#define BIT_SIZE(a)   (sizeof(a) * 8)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

// relational operators
#define EQ(a,b) ((a) == (b))
#define NE(a,b) ((a) != (b))
#define LT(a,b) ((a) < (b))
#define GT(a,b) LT(b,a)
#define LE(a,b) ((a) <= (b))
#define GE(a,b) LE(b,a)

// few math utils
#define CMP(a,b) (LT(a,b) - GT(a,b))
#define SGN(a)   CMP(0,a)
#define ABS(a)   (LT(a,0) ? -(a) : (a))
#define MIN(a,b) (LT(a,b) ? (a) : (b))
#define MAX(a,b) (GT(a,b) ? (a) : (b))

// interval check
#define IN(x,a,b) (LE(a,x) && LE(x,b))

// bit manipulations
#define LSL(x,n) ((x) << (n))
#define ASR(x,n) ((x) >> (n))

#define BIT(n)         LSL(1ul,n)
#define BIT_SET(x,n)   ((x) |  BIT(n))
#define BIT_CLR(x,n)   ((x) & ~BIT(n))
#define BIT_TGL(x,n)   ((x) ^  BIT(n))
#define BIT_TST(x,n)   (ASR(x,n) & 1ul)
#define BIT_CHG(x,n,b) (BIT_CLR(x,n) | LSL(b,n))

// preprocessor utils
#define STR(...)    #__VA_ARGS__
#define CAT(a,...)  a##__VA_ARGS__
#define XPAND(...)  __VA_ARGS__
#define XSTR(...)   STR(__VA_ARGS__)
#define XCAT(a,...) CAT(a,__VA_ARGS__)

#define PROC(a)        do{a}while(0)

// char manipulations
#define ISDIGIT(c)  IN(c,'0','9')
#define ISLOWER(c)  IN(c,'a','z')
#define ISUPPER(c)  IN(c,'A','Z')
#define ISALPHA(c)  (ISUPPER(c) || ISLOWER(c))
#define ISALNUM(c)  (ISUPPER(c) || ISLOWER(c) || ISDIGIT(c))

#define ISXDIGIT(c) (ISDIGIT(c) || IN(c,'A','F') || IN(c,'a','f'))

#define TOUPPER(c)  (ISLOWER(c) ? (c) - 32 : (c))
#define TOLOWER(c)  (ISUPPER(c) ? (c) + 32 : (c))

// algorithms
#define XWAP(a,b) ((a)^=(b),(b)^=(a),(a)^=(b))

// modelisation
#define PAIR_STRUCT(Keytype,Valtype) struct Pair_##Keytype##_##Valtype { Keytype first; Valtype second; }

#define COORD_2D_STRUCT(Type) struct Coord_##Type { type x, y; }
#define COORD_2D_ADD(r,c1,c2) ((r).x = (c1).x + (c2).x, (r).y = (c1).y + (c2).y)
#define COORD_2D_SUB(r,c1,c2) ((r).x = (c1).x - (c2).x, (r).y = (c1).y - (c2).y)

#define COORD_2D_POLAR_STRUCT(Type)  struct Polar_##Type { type a, rho; }
#define COORD_2D_POLAR_MUL(r,c1,c2) ((r).a = (c1).a + (c2).a, (r).rho = (c1).rho * (c2).rho)
#define COORD_2D_POLAR_DIV(r,c1,c2) ((r).a = (c1).a - (c2).a, (r).rho = (c1).rho / (c2).rho)

#define BUS_SIGNAL(bitsize) struct Bus_##bitsize { uint##bitsize##_t last, now; }

#endif /* ASP_A_BAERISWYL_PASSUELLO_TOOLS_H_ */
