#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 20

typedef struct _Point
{
    int x;
    int y;
    int z;
}Point;

typedef struct _Student
{
    char Name[NAME_LEN];
    int  StuNum;
}Student;

int main()
{
    int length = 10;
    int width = 20;
    printf("length: %d, width: %d\n", length, width);

    Point pt;
    pt.x = 1;
    pt.y = 2;
    pt.z = 3;
    printf("px: %d, py: %d, pz: %d\n", 
		    pt.x,
		    pt.y,
		    pt.z);

    Student stu;
    memset(&stu, 0x00, sizeof(Student));
    
    memcpy(stu.Name, "04", 2);
    stu.StuNum = 10;

    printf("Info of Students: \n");
    printf("Name: %s\n", stu.Name);
    printf("StuNum: %d\n", stu.StuNum);
}
