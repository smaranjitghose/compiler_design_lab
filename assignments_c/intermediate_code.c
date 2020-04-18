#include <iostream.h>
#include <string.h>
#include <conio.h>

char reg[10][3] = {"R0", "R1", "R2", "R3", "R4", "R5"};
char stmt[10][10], code[15];
int nostmt = 0, i = 0, output[15];
void icode(char source[10], char dest[10], int out)
{
    strcat(code, source);
    strcat(code, " ");
    strcat(code, dest);
    output[i] = out;
    cout << code << endl;
    getch();
}

void main()
{
    clrscr();
    cout << " Enter the statements(END to end): \n";
    do
    {
        cin >> stmt[nostmt++];
    } while (strcmp(stmt[nostmt - 1], "END") != 0);
    nostmt = nostmt - 1;
    cout << "\n THE INTERMEDIATE CODE IS\n\n";
    for (i = 0; i < nostmt; i++)
    {
        strcpy(code, "");
        int rd = -1, rs = -1, k;
        for (int j = 0; j < i; j++)
        {
            if (stmt[j][0] == stmt[i][2])
                rs = output[j];
            if (stmt[j][0] == stmt[1][4])
                rd = output[j];
        }
        if (rs == -1)
        {
            strcpy(code, "MOV ");
            char temp[2] = {stmt[i][2], '\0'};
            icode(temp, reg[i], i);
        }
        if (stmt[i][3] == '+')
            strcpy(code, "ADD ");
        if (stmt[i][3] == '-')
            strcpy(code, "SUB ");
        if (stmt[i][3] == '*')
            strcpy(code, "MUL ");
        if (stmt[i][3] == '/')
            strcpy(code, "DIV ");
        if (rd == -1)
        {
            char temp[2] = {stmt[i][4], '\0'};
            if (rs != -1)
                k = output[rs];
            else
                k = i;
            icode(temp, reg[k], k);
        }
        if (rs != -1 && rd != -1)
        {
            int flag = 0;
            for (j = i; j < nostmt; j++)
                if (stmt[j][2] == stmt[i][2] || stmt[j][2] == stmt[i][4])
                    flag = 1;
            if (flag != 1)
                icode(reg[output[rs]], reg[output[rd]], output[rd]);
            if (flag == 1)
                icode(reg[output[rd]], reg[output[rs]], output[rs]);
        }
    }
    strcpy(code, "MOV ");
    char temp[2] = {stmt[i - 1][0], '\0'};
    icode(reg[output[i - 1]], temp, 0);
}