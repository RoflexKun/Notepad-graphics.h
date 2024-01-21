#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
#include <bits/stdc++.h>
#include <graphics.h>
#include <winbgim.h>
#include <fstream>
#include <shlobj.h>
#include <conio.h>
#include <dos.h>
#pragma comment(lib,"Shell32")
#pragma comment(lib,"Ole32")
DEFINE_GUID(FOLDERID_Desktop, 0xB4BFCC3A, 0xDB2C, 0x424C, 0xB0, 0x29, 0x7F, 0xE9, 0x9B, 0x88, 0x88, 0xE1);

using namespace std;

//ofstream fout("test.txt");
int notepad,maxi,arrowCNT;
int scroll;
int deschidere_rez = 0;
struct text
{
    int color;
    int font;

} txt;
struct border
{
    int x;
    int y;
} brd;

struct themes
{
    int bkcolor;
    int lccolor;
    int textcolor;
} thm;

struct scrollbar
{
    int x1, x2;
    int y1, y2;
    int rsz = 10;
    int sz = 2;
} sbar;

bool language = 0;
vector <string> lines,linesfont;
vector <int> linescolor[25000000];
string s,ft,s1,ft1,line1;
int nr_linii, y_linii, x_scris, y_scris, spc;
bool okupdate=1,okstart,okopen=1;

bool pebuton_file(int x, int y)
{
    return x>= 0 && x<110 && y>=0 && y<=50;
}

bool pebuton_style(int x, int y)
{
    return x>110 && x<250 && y>=0 && y<=50;
}
void startnotepad();
void update1(int scroll,bool okup);
void save();
void enter(char key, int &nr_linii)
{
    nr_linii++;
    if(nr_linii <= maxi)
    {
        ///nr_linii
        y_linii+=31;
        setfillstyle(SOLID_FILL, thm.bkcolor);
        bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
        y_scris+=31;
        x_scris = 43;
        char ch[10];
        sprintf(ch, "%d", nr_linii);
        settextstyle(8, 0, 1);
        setbkcolor(thm.lccolor);
        setcolor(thm.textcolor);
        outtextxy(5, y_linii+5, ch);
        ///linia de scris
        setcolor(thm.textcolor);
        line(x_scris, y_scris, x_scris, y_scris+23);
        if(okupdate)
        {
            if(nr_linii==maxi)
            {
                s+=s1;
                ft+=ft1;
                lines.push_back(s);
                linesfont.push_back(ft);
            }
            else
            {
                lines[nr_linii-1].clear();
                linesfont[nr_linii-1].clear();
                s+=s1;
                ft+=ft1;
                lines[nr_linii-1]+=s;
                linesfont[nr_linii-1]+=ft;
            }
            s.clear();
            ft.clear();
            s1.clear();
            ft.clear();
        }
    }
    else
    {
        maxi=max(maxi,nr_linii);
        if(y_linii+50 >= brd.y )
        {
            save();
            scroll++;
            update1(scroll,0);
        }
        else
        {
            y_linii+=31;
            char ch[10];
            sprintf(ch, "%d", nr_linii);
            settextstyle(8, 0, 1);
            setbkcolor(thm.lccolor);
            setcolor(thm.textcolor);
            outtextxy(5, y_linii+5, ch);
            setbkcolor(thm.bkcolor);
            char litera[2] = {key, '\0'};
            settextstyle(8, 0, 3);
            outtextxy(x_scris, y_scris, litera);
            x_scris = 43;
            y_scris+=31;
            ///linia de scris
            setcolor(thm.textcolor);
            line(x_scris, y_scris, x_scris, y_scris+23);
            if(okupdate)
            {
                if(nr_linii==maxi)
                {
                    s+=s1;
                    ft+=ft1;
                    lines.push_back(s);
                    linesfont.push_back(ft);
                }
                else
                {
                    lines[nr_linii-1].clear();
                    linesfont[nr_linii-1].clear();
                    s+=s1;
                    ft+=ft1;
                    lines[nr_linii-1]+=s;
                    linesfont[nr_linii-1]+=ft;
                }
                s.clear();
                ft.clear();
                s1.clear();
                ft.clear();
            }
        }
    }
}
bool okwrite=0,okpaste=1;
void write(char key);
void backspace()
{
    x_scris-=spc;
    if(x_scris < 43 && nr_linii > 1)
    {
        nr_linii--;
        setfillstyle(SOLID_FILL, thm.lccolor);
        bar(0,y_linii, 41, y_linii+31);
        setfillstyle(SOLID_FILL, thm.bkcolor);
        bar(41, y_linii, 100, y_linii+24);
        y_linii-=31;
        y_scris-=31;
        x_scris = ((brd.x - 43)/spc)*spc + 12 - spc;
        ///linia de scris
        setcolor(thm.textcolor);
        line(x_scris, y_scris, x_scris, y_scris+23);
        return;
    }
    else if(x_scris < 42 && nr_linii == 1 )
    {
        /*
        Daca nu este nimic scris si se apasa butonul de backspace
        O sa apara un window cu eroare
        */
        int eroare;
        if(language)
            eroare = initwindow(500, 200, "Eroare!!", 500, 250);
        else
            eroare = initwindow(500, 200, "Error!!", 500, 250);
        Beep(500, 300);
        setcurrentwindow(eroare);
        setfillstyle(SOLID_FILL, thm.lccolor);
        bar(0, 0, 500, 200);
        if(language)
        {
            settextstyle(8, 0, 2);
            setbkcolor(thm.lccolor);
            setcolor(thm.textcolor);
            outtextxy(110, 85, "Nu mai poti merge inapoi");
        }
        else
        {
            settextstyle(8, 0, 2);
            setbkcolor(thm.lccolor);
            setcolor(thm.textcolor);
            outtextxy(100, 85, "You can't go back further");
        }
        delay(2000);
        closegraph(eroare);
        setcurrentwindow(notepad);
        x_scris = 43;
        y_scris = 55;
        return;
    }
    else
    {
        setfillstyle(SOLID_FILL, thm.bkcolor);
        bar(x_scris, y_scris, x_scris+spc+2, y_scris+31);
        if(s1.size() && !okwrite)
        {
            okwrite=1;
            setfillstyle(SOLID_FILL, BLACK);
            int tempx_scris=x_scris;
            bar(x_scris, y_scris, brd.x - 33, y_scris+30);
            for(int i=0; i<=s1.size(); i++)
                write(s1[i]);
            x_scris=tempx_scris;
            okwrite=0;
        }
        ///linia de scris
        setcolor(thm.textcolor);
        line(x_scris, y_scris, x_scris, y_scris+23);
        s.pop_back();
        ft.pop_back();
        linescolor[nr_linii].erase(linescolor[nr_linii].begin()+linescolor[nr_linii].size()-1);
        return;
    }

}
void write(char key)
{
    if(1+s1.size()+s.size()>(brd.x - 99)/spc && !okwrite && s1[0]!=' ' && okpaste)
        return;
    int val = (brd.x - 43)/spc;
    arrowCNT=0;
    if(x_scris < brd.x - 56)
    {
        char litera[2] = {key, '\0'};
        setbkcolor(thm.bkcolor);
        setfillstyle(SOLID_FILL, thm.bkcolor);
        bar(x_scris, y_scris, x_scris+spc, y_scris + 30);
        settextstyle(txt.font, 0, 3);
        setcolor(txt.color);
        outtextxy(x_scris, y_scris, litera);
        setcolor(15);
        if(!okwrite)
        {
            s+=key;
            if(txt.font==10)
                ft+=to_string(1);
            else if(txt.font==11)
                ft+=to_string(7);
            else
                ft+=to_string(txt.font);
        }
        x_scris+=spc;
        if(s1[0]==' ')
        {
            s1.erase(s1.begin());
            ft1.erase(ft1.begin());
        }
        else if(s1.size() && !okwrite && okpaste)
        {
            okwrite=1;
            setfillstyle(SOLID_FILL, BLACK);
            int tempx_scris=x_scris;
            bar(x_scris, y_scris, brd.x - 33, y_scris+30);
            for(int i=0; i<=s1.size(); i++)
                write(s1[i]);
            x_scris=tempx_scris;
            okwrite=0;

        }

        ///linia de scris
        if(!okwrite)
        {
            setcolor(thm.textcolor);
            line(x_scris, y_scris, x_scris, y_scris+23);
        }
        linescolor[nr_linii].push_back(txt.color);

    }
    else if(x_scris > val*spc - 50)
    {
        linescolor[nr_linii].push_back(txt.color);
        /// Daca am ajuns la capatul liniei, vom trece pe linia urmatoare cu caracterul
        nr_linii++;
        maxi=max(maxi,nr_linii);
        if(y_scris > brd.y - 50)
        {
            scroll++;
            update1(scroll,0);

        }
        else
        {
            y_linii+=31;
            char ch[10];
            sprintf(ch, "%d", nr_linii);
            settextstyle(8, 0, 1);
            setbkcolor(thm.lccolor);
            setcolor(thm.textcolor);
            outtextxy(5, y_linii+5, ch);
            setbkcolor(BLACK);
            setfillstyle(SOLID_FILL, BLACK);
            bar(x_scris, y_scris, x_scris+4, y_scris+24);
            x_scris = 43;
            y_scris+=31;
            if(nr_linii==maxi)
            {
                s+=s1;
                ft+=ft1;
                lines.push_back(s);
                linesfont.push_back(ft);
            }
            else
            {
                lines[nr_linii-1].clear();
                linesfont[nr_linii-1].clear();
                s+=s1;
                ft+=ft1;
                lines[nr_linii-1]+=s;
                linesfont[nr_linii-1]+=ft;
            }
            s.clear();
            ft.clear();
            s1.clear();
            ft1.clear();
            char litera[2] = {key, '\0'};
            setbkcolor(thm.bkcolor);
            settextstyle(txt.font, 0, 3);
            setcolor(txt.color);
            outtextxy(x_scris, y_scris, litera);
            x_scris+=spc;
            ///linia de scris
            setcolor(thm.textcolor);
            line(x_scris, y_scris, x_scris, y_scris+23);
            setcolor(15);
            s+=key;
            if(txt.font==10)
                ft+=to_string(1);
            else if(txt.font==11)
                ft+=to_string(7);
            else
                ft+=to_string(txt.font);
        }
    }
}
void afisdefault(int filesizetext);
void check_file(text &txt)
{
    okpaste=0;
    FILE *fptr;
    fptr=fopen("text.txt","r");
    fseek(fptr,0,SEEK_END);
    int filesizetext=ftell(fptr);
    fclose(fptr);
    fptr=fopen("font.txt","r");
    fseek(fptr,0,SEEK_END);
    int filesizefont=ftell(fptr);
    fclose(fptr);
    int x,j;
    if(filesizetext!=filesizefont)
        afisdefault(filesizetext);
    else
    {
        string v,f,temp;
        ifstream fin("text.txt");
        ifstream ffont("font.txt");
        ifstream fcolor("color.txt");
        if(filesizetext>2)
        {
            while(getline(fin,v) && getline(ffont,f))
            {
                j=0;
                for(int i=0; i<v.size(); i++)
                {
                    fcolor>>x;
                    temp+=f[j++];
                    int c=stoi(temp);
                    if(c==1)
                        txt.font=10;
                    else if(c==7)
                        txt.font=11;
                    else
                        txt.font=c;
                    txt.color=x;
                    write(v[i]);
                    temp.clear();
                }
                enter(13,nr_linii);

            }
            ///nr_linii--;
            backspace();
            line1+=lines[0];
        }
    }
    okpaste=1;
}
void write_file()
{
    if(nr_linii==maxi && lines.size()!=maxi && s.size()+s1.size()!=0)
    {
        s+=s1;
        ft+=ft1;
        lines.push_back(s);
        linesfont.push_back(ft);
    }
    else
    {
        if(s.size()+s1.size()!=0)
        {
            lines[nr_linii-1].clear();
            linesfont[nr_linii-1].clear();
            s+=s1;
            ft+=ft1;
            lines[nr_linii-1]+=s;
            linesfont[nr_linii-1]+=ft;
        }
    }
    FILE *fptr;
    fptr=fopen("text.txt","w");
    fclose(fptr);
    fptr=fopen("font.txt","w");
    fclose(fptr);
    fptr=fopen("color.txt","w");
    fclose(fptr);
    ofstream fout("text.txt");
    ofstream fffont("font.txt");
    ofstream ffcolor("color.txt");
    for(auto it:lines)
        fout<<it<<'\n';
    for(auto it:linesfont)
        fffont<<it<<'\n';
    for(int i=1; i<=nr_linii; i++,ffcolor<<'\n')
        for(auto it:linescolor[i])
            ffcolor<<it<<" ";
    //lines.pop_back();
    //linesfont.pop_back();
}
void update1(int scroll,bool okup)
{
    okpaste=0;
    cleardevice();
    setfillstyle(SOLID_FILL, thm.bkcolor);
    bar(0, 0, brd.x, brd.y);
    setcolor(thm.textcolor);
    line(0,0, brd.x, 0);
    setcolor(thm.textcolor);
    line(0, 50, brd.x, 50);
    if(language)
    {
        setbkcolor(thm.bkcolor);
        settextstyle(8, 0, 3);
        outtextxy(0, 15, "Fisiere");
        line(110, 0, 110, 50);
        settextstyle(8, 0, 3);
        outtextxy(145, 15, "Stil");
        line(250, 0, 250, 50);
        line(250, 0, 250, 50);
        settextstyle(8, 0, 3);
        outtextxy(300, 15, "Teme");
    }
    else
    {
        setbkcolor(thm.bkcolor);
        settextstyle(8, 0, 5);
        outtextxy(0, 5, "File");
        line(110, 0, 110, 50);
        settextstyle(8, 0, 5);
        outtextxy(115, 5, "Style");
        line(250, 0, 250, 50);
        line(250, 0, 250, 50);
        settextstyle(8, 0, 5);
        outtextxy(255, 5, "Themes");
    }

    line(415, 0, 415, 50);
    setfillstyle(SOLID_FILL, 8);
    bar(brd.x - 30, 51, brd.x, brd.y);
    line(brd.x - 30, 81, brd.x, 81);
    line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
    setfillstyle(SOLID_FILL, 7);
    bar(brd.x - 26, 85, brd.x - 4, brd.y - 34);
    setfillstyle(SOLID_FILL,thm.lccolor);
    bar(0,51,41,brd.y);
    nr_linii = 1 + scroll;
    y_linii = 55;
    settextstyle(8, 0, 1);
    setbkcolor(thm.lccolor);
    char temp[10];
    sprintf(temp,"%d",nr_linii);
    outtextxy(5, y_linii+5, temp);
    outtextxy(5, y_linii+5, temp);
    setbkcolor(BLACK);
    x_scris = 43;
    y_scris = 55;
    okupdate=0;
    int i;
    if(!okup)
    {
        if(sbar.y2 == brd.y -34)
        {
            if(sbar.y2 - sbar.y1 > 30)
            {
                if(sbar.y2 - sbar.y1 < (brd.y - 50)/sbar.sz && sbar.rsz !=1)
                {
                    sbar.rsz/=2;
                    sbar.sz*=2;
                }
                setfillstyle(SOLID_FILL, 8);
                bar(brd.x - 30, 51, brd.x, brd.y);
                line(brd.x - 30, 81, brd.x, 81);
                line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
                sbar.y1 += sbar.rsz;
                setfillstyle(SOLID_FILL, 7);
                bar(sbar.x1, sbar.y1, sbar.x2, sbar.y2);
                setcolor(thm.textcolor);
                line(brd.x - 25, 75, brd.x - 15, 60);
                line(brd.x-5, 75, brd.x -15, 60);
                line(brd.x - 25, brd.y - 25, brd.x - 15, brd.y - 10);
                line(brd.x - 5, brd.y - 25, brd.x - 15, brd.y - 10);
            }
        }
        else if(sbar.y2 != brd.y - 34)
        {
            sbar.y1+=sbar.rsz;
            sbar.y2+=sbar.rsz;
            setfillstyle(SOLID_FILL, 8);
            bar(brd.x - 30, 51, brd.x, brd.y);
            line(brd.x - 30, 81, brd.x, 81);
            line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
            setfillstyle(SOLID_FILL, 7);
            bar(sbar.x1, sbar.y1, sbar.x2, sbar.y2);
            setcolor(thm.textcolor);
            line(brd.x - 25, 75, brd.x - 15, 60);
            line(brd.x-5, 75, brd.x -15, 60);
            line(brd.x - 25, brd.y - 25, brd.x - 15, brd.y - 10);
            line(brd.x - 5, brd.y - 25, brd.x - 15, brd.y - 10);
        }
    }
    else if(sbar.y1 > 85)
    {
        sbar.y1-=sbar.rsz;
        sbar.y2-=sbar.rsz;
        setfillstyle(SOLID_FILL, 8);
        bar(brd.x - 30, 51, brd.x, brd.y);
        line(brd.x - 30, 81, brd.x, 81);
        line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
        setfillstyle(SOLID_FILL, 7);
        bar(sbar.x1, sbar.y1, sbar.x2, sbar.y2);
        setcolor(thm.textcolor);
        line(brd.x - 25, 75, brd.x - 15, 60);
        line(brd.x-5, 75, brd.x -15, 60);
        line(brd.x - 25, brd.y - 25, brd.x - 15, brd.y - 10);
        line(brd.x - 5, brd.y - 25, brd.x - 15, brd.y - 10);
    }
    for(i=scroll; i<scroll+(brd.y - 50)/31-1 && i<lines.size(); i++)
    {
        for(int j=0; j<lines[i].size(); j++)
            write(lines[i][j]);
        enter(13, nr_linii);
    }
    for(int j=0; j<lines[i].size() && i<lines.size(); j++)
        write(lines[i][j]);
    s.clear();
    s1.clear();
    ft.clear();
    ft1.clear();
    okupdate=1;
    ///linia de scris
    setcolor(thm.textcolor);
    line(x_scris, y_scris, x_scris, y_scris+23);
    okpaste=1;
    return;
}
void update(int ok)
{
    write_file();
    //delay(1000);
    for(int i=0; i<lines.size(); i++)
        linescolor[i].clear();
    lines.clear();
    linesfont.clear();
    s.clear();
    s1.clear();
    ft.clear();
    ft1.clear();
    closegraph(notepad);
    notepad = initwindow(brd.x, brd.y, "Notepad", 125, 50);
    setfillstyle(SOLID_FILL, thm.bkcolor);
    bar(0, 0, brd.x, brd.y);
    setcolor(thm.textcolor);
    line(0,0, brd.x, 0);
    setcolor(thm.textcolor);
    line(0, 50, brd.x, 50);
    if(language)
    {
        setbkcolor(thm.bkcolor);
        settextstyle(8, 0, 3);
        outtextxy(0, 15, "Fisiere");
        line(110, 0, 110, 50);
        settextstyle(8, 0, 3);
        outtextxy(150, 15, "Stil");
        line(250, 0, 250, 50);
        line(250, 0, 250, 50);
        settextstyle(8, 0, 3);
        outtextxy(305, 15, "Teme");
    }
    else
    {
        setbkcolor(thm.bkcolor);
        settextstyle(8, 0, 5);
        outtextxy(0, 5, "File");
        line(110, 0, 110, 50);
        settextstyle(8, 0, 5);
        outtextxy(115, 5, "Style");
        line(250, 0, 250, 50);
        line(250, 0, 250, 50);
        settextstyle(8, 0, 5);
        outtextxy(255, 5, "Themes");
    }
    line(415, 0, 415, 50);
    setfillstyle(SOLID_FILL, 8);
    bar(brd.x - 30, 51, brd.x, brd.y);
    line(brd.x - 30, 81, brd.x, 81);
    line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
    setfillstyle(SOLID_FILL, 7);
    bar(brd.x - 26, 85, brd.x - 4, brd.y - 34);
    setfillstyle(SOLID_FILL,thm.lccolor);
    bar(0,51,41,brd.y);
    setcolor(thm.textcolor);
    line(brd.x - 25, 75, brd.x - 15, 60);
    line(brd.x-5, 75, brd.x -15, 60);
    line(brd.x - 25, brd.y - 25, brd.x - 15, brd.y - 10);
    line(brd.x - 5, brd.y - 25, brd.x - 15, brd.y - 10);
    nr_linii = 1;
    maxi=1;
    y_linii = 55;
    settextstyle(8, 0, 1);
    setbkcolor(thm.lccolor);
    outtextxy(5, y_linii+5, "1");
    setbkcolor(BLACK);
    x_scris = 43;
    y_scris = 55;
    if(ok==1)
    {
        FILE *fptr;
        fptr=fopen("text.txt","w");
        fclose(fptr);
        fptr=fopen("font.txt","w");
        fclose(fptr);
        fptr=fopen("color.txt","w");
        fclose(fptr);
        while(lines.size())
        {
            lines.pop_back();
            linesfont.pop_back();
        }
    }
    check_file(txt);
    ///linia de scris
    setcolor(thm.textcolor);
    line(x_scris, y_scris, x_scris, y_scris+23);
    return;
}
void copytoclipboard(int x1,int y1,int x2,int y2);
string copyfromcliboard();
void buton_style(text &txt, border &brd, int &spc, scrollbar &sbar);
void buton_file();
void buton_themes(themes &thm, text &txt);
void save();
void sameline();
void newline();
void open_file(string file_name);
void updatelines(string text,string font);
string findcaract();
int main()
{
    /*
    Construim windowul principal
    O bara sus ce o sa contina butoane
    Si o bara laterala unde vor fi afisate numarul de linii
    */
    startnotepad();
    int x1,y1,x2,y2;
    while(1)
    {
        short ctrlKeyState = GetAsyncKeyState(VK_CONTROL);
        /// verificam daca se face click, tinem minte coordonatele clickului si verficicam daca este pe unul dintre butoane sau nu
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(pebuton_file(x, y))
            {
                buton_file();
            }
            else if(pebuton_style(x, y))
            {
                buton_style(txt, brd, spc, sbar);
            }
            else if(x>=256 && x<=415 && y>=0 && y<=50)
            {
                buton_themes(thm, txt);
            }
            else if(x >= brd.x - 30 && x <= brd.x && y >= 51 && y<=81)
            {
                if(scroll>0)
                {
                    if(!arrowCNT)
                        save();
                    if(scroll==1)
                    {
                        lines[0].clear();
                        lines[0]+=line1;
                    }
                    scroll--;
                    update1(scroll,1);

                }
            }
            else if(x>=brd.x - 30 && x<=brd.x && y>=brd.y - 30 && y <=brd.y)
            {
                if(!arrowCNT)
                    save();
                system("CLS");
                for(auto it:lines)
                    cout<<it<<'\n';
                if(maxi>= (brd.y - 50)/31)
                {
                    scroll++;
                    update1(scroll,0);
                }
            }
            else if(x >=43 && x<=brd.x-31 && y>=51 && y<=(brd.y - brd.y%(((brd.y - 51)/31)*31) + 31))
            {
                int yt = (maxi-scroll)*31+46;
                if(y < yt)
                {
                    save();
                    setfillstyle(SOLID_FILL, thm.bkcolor);
                    bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
                    x_scris = ((x-43)/spc)*spc + 43 + spc;
                    y_scris = ((y-50)/31)*31 + 55;
                    y_linii = ((y-50)/31)*31 + 55;
                    nr_linii = ((y-50)/31) + 1 + scroll;
                    cout << "asta: " << nr_linii << '\n';
                    setcolor(thm.textcolor);
                    line(x_scris, y_scris, x_scris, y_scris+23);
                    newline();
                }
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }


        /*  kbhit() ne permite sa verificam daca o tasta a fost apasata si in functie de tasta
            fie o afisam, fie stergem un caracter sau mergem pe linia urmatoare
        */
        if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
        {
            if (GetAsyncKeyState('E') & 0x8000)
            {
                bool apasat = false;
                while (1)
                {
                    int xs1, ys1, xs2, ys2;
                    if (ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN, x1, y1);
                        apasat = true;
                    }

                    if (ismouseclick(WM_LBUTTONUP))
                    {

                        apasat = false;
                        getmouseclick(WM_LBUTTONUP, x2, y2);
                        if(ys2 > ys1)
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs2-6+spc, ys1-6, xs1-6, ys2-6+31);
                            }
                            else
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs1-6, ys1-6, xs2-6+spc, ys2-6+31);
                            }

                        }
                        else
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs2-6+spc, ys2-6, xs1-6, ys1+31);
                            }
                            else
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs1-6, ys2-6, xs2-6+spc, ys1-6+31);
                            }

                        }

                        cout<<"merge copy";
                        xs1 = x1 - x1%spc;
                        ys1 = y1 - y1%31;
                        xs2 = mousex() - mousex()%spc;
                        ys2 = mousey() - mousey()%31;
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(xs1-6, ys1-6, xs2-6+spc, ys2-6+31);
                        okwrite=1;
                        int temp = txt.color;
                        //txt.color = 14;
                        int tempyscris=y_scris;
                        int tempxscris=x_scris;
                        y_scris=ys1-7;
                        x_scris=xs1-6;
                        for(int i=y1/31-1+scroll-1; i<y2/31-1+scroll && i<lines.size(); i++)
                        {
                            for(int j=(x1-42)/spc+1-1; j<(x2-42)/spc+1 && j<lines[i].size(); j++)
                                write(lines[i][j]);
                            //text+=lines[i];
                            ///trecere la linia urmatoare
                            y_scris+=31;
                            x_scris=xs1-6;
                        }
                        okwrite=0;
                        y_scris=tempyscris;
                        x_scris=tempxscris;
                        copytoclipboard((x1-42)/spc+1,y1/31-1+scroll,(x2-42)/spc+1,y2/31-1+scroll);
                        //txt.color=temp;
                        break;
                    }
                    if (apasat)
                    {
                        if(ys2 > ys1)
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs2-6+spc, ys1-6, xs1-6, ys2-6+31);
                            }
                            else
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs1-6, ys1-6, xs2-6+spc, ys2-6+31);
                            }

                        }
                        else
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs2-6+spc, ys2-6, xs1-6, ys1-6+31);
                            }
                            else
                            {
                                setcolor(thm.bkcolor);
                                rectangle(xs1-6, ys2-6, xs2-6+spc, ys1-6+31);
                            }

                        }
                        xs1 = x1 - x1%spc;
                        ys1 = y1 - y1%31;
                        xs2 = mousex() - mousex()%spc;
                        ys2 = mousey() - mousey()%31;

                        if(ys2 > ys1)
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.textcolor);
                                rectangle(xs2-6+spc, ys1-6, xs1-6, ys2-6+31);
                            }
                            else
                            {
                                setcolor(thm.textcolor);
                                rectangle(xs1-6, ys1-6, xs2-6+spc, ys2-6+31);
                            }

                        }
                        else
                        {
                            if(xs2 < xs1)
                            {
                                setcolor(thm.textcolor);
                                rectangle(xs2-6+spc, ys2-6, xs1-6, ys1-6+31);
                            }
                            else
                            {
                                setcolor(thm.textcolor);
                                rectangle(xs1-6, ys2-6, xs2-6+spc, ys1-6+31);
                            }

                        }
                        x2=mousex();
                        y2=mousey();
                        cout<<x2<<" "<<y2<<'\n';
                        int xs11 = x1 - x1%spc;
                        int ys11 = y1 - y1%31;
                        int xs22 = mousex() - mousex()%spc;
                        int ys22 = mousey() - mousey()%31;
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(xs11-6, ys11-6, xs22-6+spc, ys22-6+31);
                        okwrite=1;
                        int temp = txt.color;
                        txt.color = 14;
                        int tempyscris=y_scris;
                        int tempxscris=x_scris;
                        y_scris=ys1-7;
                        x_scris=xs1-6;
                        for(int i=y1/31-1+scroll-1; i<y2/31-1+scroll && i<lines.size(); i++)
                        {
                            for(int j=(x1-42)/spc+1-1; j<(x2-42)/spc+1 && j<lines[i].size(); j++)
                                write(lines[i][j]);
                            //text+=lines[i];
                            ///trecere la linia urmatoare
                            y_scris+=31;
                            x_scris=xs1-6;
                        }
                        okwrite=0;
                        y_scris=tempyscris;
                        x_scris=tempxscris;
                        txt.color=temp;
                    }
                }
            }
            if (GetAsyncKeyState('F') & 0x8000)
            {
                system("CLS");
                auto findtext = findcaract();
                if(deschidere_rez)
                {
                    int resw;
                    if(language)
                        resw = initwindow(300, 300, "Rezultate", 500, 400);
                    else
                        resw = initwindow(300, 300, "Results", 500, 400);
                    setcurrentwindow(resw);
                    setfillstyle(SOLID_FILL, thm.lccolor);
                    bar(0, 0, 300, 300);
                    setcolor(thm.textcolor);
                    setbkcolor(thm.lccolor);
                    line(0, 270, 300, 270);
                    if(nr_linii==maxi && lines.size()!=maxi && s.size()+s1.size()!=0 && findtext.size()>0)
                    {
                        string temptext;
                        temptext+=s;
                        temptext+=s1;
                        int cntg = 0;
                        for(int i=0; i<maxi-1; i++)
                            if(lines[i].find(findtext)!=string::npos )
                                cntg++;
                        if(temptext.find(findtext)!=string::npos)
                            cntg++;
                        char ch[10];
                        sprintf(ch, "%d", cntg);
                        if(language)
                        {
                            settextstyle(8, 0, 2);
                            outtextxy(0, 10, "Au fost gasite");
                            settextstyle(10, 0, 2);
                            outtextxy(175, 10, ch);
                            settextstyle(8, 0, 2);
                            outtextxy(210, 10, "intrari");
                            outtextxy(100, 275, "Inchide");
                            if(cntg)
                                outtextxy(70, 50, "Pe liniile: ");
                        }
                        else
                        {
                            settextstyle(10, 0, 2);
                            outtextxy(20, 10, ch);
                            settextstyle(8, 0, 2);
                            outtextxy(60, 10, "entries were found");
                            outtextxy(120, 275, "Close");
                            if(cntg)
                                outtextxy(90, 50, "On lines: ");

                        }
                        int yl = 70, xl = 30;
                        for(int i=0; i<maxi-1; i++)
                            if(lines[i].find(findtext)!=string::npos )
                            {
                                char ch[10];
                                sprintf(ch, "%d", i+1);
                                int sp = 0;
                                if(strlen(ch) == 2)
                                    sp = 10;
                                else if(strlen(ch) == 3)
                                    sp = 25;
                                settextstyle(10, 0, 2);
                                outtextxy(xl, yl, ch);
                                settextstyle(8, 0, 2);
                                outtextxy(xl+15+sp, yl, ",");
                                xl+=30;
                                xl+=sp;
                                if(xl > 240)
                                {
                                    xl = 30;
                                    yl+=20;
                                }
                            }
                        if(temptext.find(findtext)!=string::npos)
                        {
                            char ch[10];
                            sprintf(ch, "%d", maxi);
                            int sp = 0;
                            if(strlen(ch) == 2)
                                sp = 10;
                            else if(strlen(ch) == 3)
                                sp = 25;
                            settextstyle(10, 0, 2);
                            outtextxy(xl, yl, ch);
                            settextstyle(8, 0, 2);
                            outtextxy(xl+15+sp, yl, ",");
                            xl+=30;
                            xl+=sp;
                            if(xl > 240)
                            {
                                xl = 30;
                                yl+=20;
                            }
                        }
                        setfillstyle(SOLID_FILL, thm.lccolor);
                        bar(xl-12, yl, xl+1, yl+21);
                    }
                    else if(findtext.size()>0)
                    {

                        int tempnr_linii=0;
                        string temptext;
                        if(s.size()+s1.size()!=0)
                        {
                            temptext+=s;
                            temptext+=s1;
                            tempnr_linii=nr_linii;
                        }
                        int cntg = 0;
                        for(int i=0; i<maxi; i++)
                            if(lines[i].find(findtext)!=string::npos || (i==tempnr_linii-1 && temptext.find(findtext)!=string::npos))
                                cntg++;
                        char ch[10];
                        sprintf(ch, "%d", cntg);
                        if(language)
                        {
                            settextstyle(8, 0, 2);
                            outtextxy(0, 10, "Au fost gasite");
                            settextstyle(10, 0, 2);
                            outtextxy(175, 10, ch);
                            settextstyle(8, 0, 2);
                            outtextxy(210, 10, "intrari");
                            outtextxy(100, 275, "Inchide");
                            if(cntg)
                                outtextxy(70, 50, "Pe liniile: ");
                        }
                        else
                        {
                            settextstyle(10, 0, 2);
                            outtextxy(20, 10, ch);
                            settextstyle(8, 0, 2);
                            outtextxy(60, 10, "entries were found");
                            outtextxy(120, 275, "Close");
                            if(cntg)
                                outtextxy(90, 50, "On lines: ");

                        }
                        int yl = 70, xl = 30;
                        for(int i=0; i<maxi; i++)
                            if(lines[i].find(findtext)!=string::npos || (i==tempnr_linii-1 && temptext.find(findtext)!=string::npos))
                            {
                                char ch[10];
                                sprintf(ch, "%d", i+1);
                                int sp = 0;
                                if(strlen(ch) == 2)
                                    sp = 10;
                                else if(strlen(ch) == 3)
                                    sp = 25;
                                settextstyle(10, 0, 2);
                                outtextxy(xl, yl, ch);
                                settextstyle(8, 0, 2);
                                outtextxy(xl+15+sp, yl, ",");
                                xl+=30;
                                xl+=sp;
                                if(xl > 240)
                                {
                                    xl = 30;
                                    yl+=20;
                                }
                            }
                        setfillstyle(SOLID_FILL, thm.lccolor);
                        bar(xl-12, yl, xl+1, yl+21);
                    }
                    int ok = 1;
                    while(1)
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            int x, y;
                            getmouseclick(WM_LBUTTONDOWN, x, y);
                            if(y>=270)
                            {
                                closegraph(resw);
                                setcurrentwindow(notepad);
                                ok =0;
                            }
                        }
                        if(!ok)
                            break;
                    }
                }

            }
            if (GetAsyncKeyState('V') & 0x8000)
            {
                okpaste=0;
                auto text =copyfromcliboard();
                int nr_spatii=0;
                for(int i=0; i<text.size(); i++)
                    if(s1[i]==' ')
                        nr_spatii++;
                    else
                        break;
                if(s.size()+text.size()+s1.size()<=(brd.x - 43 - 30)/spc || nr_spatii==text.size())
                    for(int i=0; i<text.size(); i++)
                        write(text[i]);
                else
                {
                    if(maxi==nr_linii)
                    {
                        text+=s1;
                        s1.clear();
                        for(int i=0; i<text.size(); i++)
                            write(text[i]);
                    }
                    else
                    {
                        for(int j=s.size(); j<(brd.x - 43 - 30)/spc-1 && text.size()!=0; j++)
                        {
                            write(text[0]);
                            text.erase(text.begin());
                        }
                        if(text.size()==0)
                            while(s1[0]==' ')
                            {
                                s1.erase(s1.begin());
                                ft1.erase(ft1.begin());
                            }
                        if(ft1.size()!=text.size()+s1.size())
                            while(ft1.size()!=(text.size()+s1.size()))
                                ft1.insert(ft1.begin(),ft[1]);
                        updatelines(text,"");
                    }
                }
                okpaste=1;
            }
            if (GetAsyncKeyState('C') & 0x8000)
                copytoclipboard(x1,y1,x2,y2);
            if (GetAsyncKeyState('N') & 0x8000)
            {
                update(1);
                delay(500);
            }
            if (GetAsyncKeyState('S') & 0x8000)
            {
                write_file();
                delay(500);
            }
            char key = getch();
            int ch = key;
            if(ch == 0)
            {
                key = getch();
                ch  = key;
                switch (ch)
                {
                case 72: /// sus
                {
                    if(scroll>0)
                    {
                        if(!arrowCNT)
                            save();
                        if(scroll==1)
                        {
                            lines[0].clear();
                            lines[0]+=line1;
                        }
                        scroll--;
                        update1(scroll,1);

                    }
                    break;
                }
                case 80: ///jos
                {
                    if(!arrowCNT)
                        save();
                    system("CLS");
                    for(auto it:lines)
                        cout<<it<<'\n';
                    if(maxi>= (brd.y - 50)/31)
                    {
                        scroll++;
                        update1(scroll,0);
                    }
                    break;
                }
                }
            }
        }
        if (kbhit())
        {
            char key = getch();
            int ch = key;
            if(ch == 0)
            {
                key = getch();
                ch  = key;
                switch (ch)
                {
                case 72: /// sus
                {
                    if(y_scris > 55)
                    {
                        save();
                        setfillstyle(SOLID_FILL, thm.bkcolor);
                        bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
                        y_scris-=31;
                        nr_linii = ((y_scris-50)/31) + 1 + scroll;
                        newline();
                        //cout<<s<<" "<<s1;
                        arrowCNT=spc;
                        ///linia de scris
                        setcolor(thm.textcolor);
                        line(x_scris, y_scris, x_scris, y_scris+23);
                        system("CLS");
                        for(auto it:lines)
                            cout<<it<<'\n';
                    }

                    break;
                }

                case 80: ///jos
                {
                    if(y_scris < (brd.y - brd.y%(((brd.y - 51)/31)*31)) && ((y_scris+31-50)/31) + 1 + scroll <= maxi)
                    {

                        save();
                        setfillstyle(SOLID_FILL, thm.bkcolor);
                        bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
                        y_scris+=31;
                        x_scris=x_scris+spc;
                        nr_linii = ((y_scris-50)/31) + 1 + scroll;
                        newline();
                        arrowCNT=spc;
                        ///linia de scris
                        setcolor(thm.textcolor);
                        line(x_scris-spc, y_scris, x_scris-spc, y_scris+23);
                        x_scris-=spc;
                    }
                    break;
                }
                case 75: ///stanga
                {
                    save();
                    if(x_scris > 44)
                    {
                        setfillstyle(SOLID_FILL, thm.bkcolor);
                        bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
                        x_scris-=spc;
                        ///linia de scris
                        setcolor(thm.textcolor);
                        line(x_scris-1, y_scris, x_scris-1, y_scris+23);
                    }
                    sameline();
                    break;
                }
                case 77: ///dreapta
                {
                    save();
                    if(x_scris < brd.x - 31)
                    {
                        setfillstyle(SOLID_FILL, thm.bkcolor);
                        bar(x_scris-1, y_scris, x_scris+1, y_scris+24);
                        x_scris+=spc;
                        ///linia de scris
                        setcolor(thm.textcolor);
                        line(x_scris, y_scris, x_scris, y_scris+23);
                    }

                    sameline();
                    break;
                }
                }
            }
            else if (key == 13)
            {
                enter(key, nr_linii);
            }
            else if(key == 8)
                backspace();
            else if(!ctrlKeyState)
                write(key);
        }
        /*system("CLS");
        for(auto it:lines)
            cout<<it<<'\n';*/
    }
    getch();
    closegraph();
    return 0;
}
void startnotepad()
{
    thm.textcolor = 13;
    thm.bkcolor = 0;
    thm.lccolor = 9;
    spc = 16;
    brd.x = 1280;
    brd.y = 720;
    notepad = initwindow(brd.x, brd.y, "Notepad", 125, 50);
    setfillstyle(SOLID_FILL, thm.bkcolor);
    bar(0, 0, brd.x, brd.y);
    setcolor(thm.textcolor);
    line(0,0, brd.x, 0);
    txt.font = 8;
    txt.color = 13;
    setcolor(thm.textcolor);
    line(0, 50, brd.x, 50);
    settextstyle(8, 0, 5);
    outtextxy(0, 5, "File");
    line(110, 0, 110, 50);
    settextstyle(8, 0, 5);
    outtextxy(115, 5, "Style");
    line(250, 0, 250, 50);
    settextstyle(8, 0, 5);
    outtextxy(255, 5, "Themes");
    line(415, 0, 415, 50);
    setfillstyle(SOLID_FILL,thm.lccolor);
    bar(0,51,41,brd.y);
    sbar.x1 = brd.x - 26;
    sbar.y1 = 85;
    sbar.x2 = brd.x - 4;
    sbar.y2 = brd.y - 34;
    setfillstyle(SOLID_FILL, 8);
    bar(brd.x - 30, 51, brd.x, brd.y);
    line(brd.x - 30, 81, brd.x, 81);
    line(brd.x - 30, brd.y - 30, brd.x, brd.y - 30);
    setfillstyle(SOLID_FILL, 7);
    bar(sbar.x1, sbar.y1, sbar.x2, sbar.y2);
    setcolor(thm.textcolor);
    line(brd.x - 25, 75, brd.x - 15, 60);
    line(brd.x-5, 75, brd.x -15, 60);
    line(brd.x - 25, brd.y - 25, brd.x - 15, brd.y - 10);
    line(brd.x - 5, brd.y - 25, brd.x - 15, brd.y - 10);
    nr_linii = 1;
    maxi=1;
    y_linii = 55;
    settextstyle(8, 0, 1);
    setbkcolor(9);
    outtextxy(5, y_linii+5, "1");
    setbkcolor(BLACK);
    x_scris = 43;
    y_scris = 55;
    if(okopen)
        check_file(txt);
    s1.clear();
    s.clear();
    ft.clear();
    ft1.clear();
    okstart=1;
    ///linia de scris
    setcolor(thm.textcolor);
    line(x_scris, y_scris, x_scris, y_scris+23);
}
void updatelines(string text,string font)
{
    text+=s1;
    font+=ft1;
    if(s.size()+s1.size()!=0)

    {
        lines[nr_linii-1].clear();
        linesfont[nr_linii-1].clear();
        //s+=s1;
        //ft+=ft1;
        lines[nr_linii-1]+=s;
        linesfont[nr_linii-1]+=ft;
    }
    string temptext,tempfont;
    temptext+=lines[lines.size()-1];
    tempfont+=linesfont[linesfont.size()-1];
    lines.push_back(temptext);
    linesfont.push_back(tempfont);
    for(int i=lines.size()-1; i>nr_linii; i--)
    {
        lines[i].clear();
        linesfont[i].clear();
        lines[i]+=lines[i-1];
        linesfont[i]+=linesfont[i-1];
    }
    lines[nr_linii].clear();
    linesfont[nr_linii].clear();
    for(int i=0; i<text.size(); i++)
    {
        lines[nr_linii]+=text[i];
        linesfont[nr_linii]+=font[i];
    }
    system("CLS");
    for(auto it:lines)
        cout<<it<<'\n';
    update1(scroll,0);
    //if(lines[nr_linii].size()!=0);

}
string copyfromcliboard()
{
    OpenClipboard(nullptr);
    HANDLE hData = GetClipboardData(CF_TEXT);

    char * pszText = static_cast<char*>( GlobalLock(hData) );
    string text( pszText );

    GlobalUnlock( hData );
    CloseClipboard();

    return text;
}
void copytoclipboard(int x1,int y1,int x2,int y2)
{
    string text;
    int l=lines.size();
    for(int i=y1-1; i<y2 && i<l; i++)
    {
        for(int j=x1-1; j<x2 && j<lines[i].size(); j++)
            text+=lines[i][j];
        //text+=lines[i];
        text+=' ';
    }
    if (!OpenClipboard(nullptr))
    {
        cout<< "Cannot open clipboard \n";
        return;
    }
    if (!OpenClipboard(nullptr))
    {
        cout<< "Cannot open clipboard \n";
        return;
    }
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (!hMem)
    {
        CloseClipboard();
        cout<< "Memory allocation failed \n";
        return;
    }

    memcpy(GlobalLock(hMem), text.c_str(), text.size() + 1);
    GlobalUnlock(hMem);

    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();

    GlobalFree(hMem);
}
void save()
{
    if(nr_linii==maxi && s.size()+s1.size()!=0)
    {
        lines.push_back(s);
        cout<<"aici "<<s<<" "<<s1<<'\n';
        linesfont.push_back(ft);
    }
    else
    {
        if(s.size()+s1.size()!=0)
        {
            lines[nr_linii-1].clear();
            linesfont[nr_linii-1].clear();
            s+=s1;
            ft+=ft1;
            cout<<s<<" "<<s1<<'\n';
            lines[nr_linii-1]+=s;
            linesfont[nr_linii-1]+=ft;
        }
    }
}
void sameline()
{
    s.clear();
    ft.clear();
    s1.clear();
    ft1.clear();
    s+=lines[nr_linii-1];
    ft+=linesfont[nr_linii-1];
    if(s.size()> x_scris / spc -2)
    {
        for(int i=x_scris / spc -2; i<s.size(); i++)
        {
            s1+=s[i];
            ft1+=ft[i];
        }
        s.erase(s.find(s1),s1.length());
        ft.erase(ft.find(ft1),ft1.length());;
    }
    else
    {
        s1.clear();
        ft1.clear();
        for(int i=s.size(); i<=x_scris / spc -2-1; i++)
        {
            s+=' ';
            ft+=to_string(txt.font);
            linescolor[nr_linii].push_back(txt.color);
        }
    }
    lines[nr_linii-1].clear();
    linesfont[nr_linii-1].clear();
}
void newline()
{
    s.clear();
    ft.clear();
    s1.clear();
    ft1.clear();
    if(nr_linii> lines.size())
    {
        for(int i=lines.size(); i<nr_linii; i++)
        {
            s.clear();
            lines.push_back(s);
            linesfont.push_back(s);
        }
        for(int i=1; i<=x_scris / spc -2; i++)
        {
            s+=' ';
            ft+=to_string(txt.font);
            linescolor[nr_linii].push_back(txt.color);
        }
    }
    else
    {
        ///cout<<nr_linii-1<<'\n';
        s+=lines[nr_linii-1];
        ft+=linesfont[nr_linii-1];
        if(s.size()> x_scris / spc -2)
        {
            for(int i=x_scris / spc -2; i<s.size(); i++)
            {
                s1+=s[i];
                ft1+=ft[i];
            }
            s.erase(s.find(s1),s1.length());
            ft.erase(ft.find(ft1),ft1.length());;
        }
        else
        {
            s1.clear();
            ft1.clear();
            for(int i=s.size(); i<=x_scris / spc -2-1; i++)
            {
                s+=' ';
                ft+=to_string(txt.font);
                linescolor[nr_linii].push_back(txt.color);
            }
        }
        lines[nr_linii-1].clear();
        linesfont[nr_linii-1].clear();
    }
    //cout<<s<<" "<<s1<<'\n';
}
void afisdefault(int filesizetext)
{
    ifstream fin("text.txt");
    if(filesizetext>2)
    {
        string v;
        while(getline(fin,v))
        {
            int l=v.size();
            for(int i=0; i<l; i++)
                write(v[i]);
            enter(13,nr_linii);
        }
        backspace();
        line1+=lines[0];
    }

}
void buton_themes(themes &thm, text &txt)
{
    int themesw;
    if(language)
        themesw = initwindow(200, 500, "Teme", 500, 250);
    else
        themesw = initwindow(200, 500, "Themes", 500, 250);
    setcurrentwindow(themesw);
    setfillstyle(SOLID_FILL, thm.lccolor);
    bar(0, 0, 200, 500);
    setcolor(thm.textcolor);
    line(0, 35, 200, 35);
    line(0, 135, 200, 135);
    line(0, 235, 200, 235);
    line(0, 335, 200, 335);
    line(0, 435, 200, 435);
    line(0, 470, 200, 470);
    if(language)
    {
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(35, 115, "Tema de baza");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(20, 215, "Tema intunecata");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(25, 315, "Tema luminoasa");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(30, 415, "Tema UAIC FII");
        settextstyle(8, 0, 1);
        outtextxy(5, 475, "Inchide Fereastra");
    }
    else
    {
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(30, 115, "Default Theme");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(45, 215, "Dark Theme");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(40, 315, "Light Theme");
        setbkcolor(thm.lccolor);
        settextstyle(10, 0, 1);
        outtextxy(25, 415, "UAIC FII Theme");
        settextstyle(8, 0, 1);
        outtextxy(30, 475, "Close Window");
    }
    for(int i=55; i<=355; i+=100)
        for(int j=20; j<=140; j+=60)
        {
            setcolor(thm.textcolor);
            rectangle(j, i, j+40, i+40);
            rectangle(j-1, i-1, j+41, i+41);
        }
    int vc[15] = {0};
    vc[0] = 0; ///thm.bkcolor
    vc[1] = 9; ///thm.lccolor
    vc[2] = 13; ///thm.textcolor

    vc[3] = 0;
    vc[4] = 8;
    vc[5] = 15;

    vc[6] = 15;
    vc[7] = 5;
    vc[8] = 0;

    vc[9] = 15;
    vc[10] = 11;
    vc[11] = 1;
    int cnt = 0;
    for(int i=55; i<=355; i+=100)
        for(int j=20; j<=140; j+=60)
        {
            setfillstyle(SOLID_FILL, vc[cnt]);
            bar(j+1, i+1, j+40, i+40);
            cnt++;
        }
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(y >=35 && y < 135)
            {
                ///write_file();
                ///delay(500);
                txt.color = vc[2];
                thm.bkcolor = vc[0];
                thm.lccolor = vc[1];
                thm.textcolor = vc[2];
                closegraph(themesw);
                update(0);
                setcurrentwindow(notepad);
                return;
            }
            else if(y > 135 && y < 235)
            {
                ///write_file();
                ///delay(500);
                txt.color = vc[5];
                thm.bkcolor = vc[3];
                thm.lccolor = vc[4];
                thm.textcolor = vc[5];
                closegraph(themesw);
                update(0);
                setcurrentwindow(notepad);
                return;
            }
            else if(y > 235 && y < 335)
            {
                ///write_file();
                ///delay(500);
                txt.color = vc[8];
                thm.bkcolor = vc[6];
                thm.lccolor = vc[7];
                thm.textcolor = vc[8];
                closegraph(themesw);
                update(0);
                setcurrentwindow(notepad);
                return;
            }
            else if(y > 335 && y < 435)
            {
                ///write_file();
                ///delay(500);
                txt.color = vc[11];
                thm.bkcolor = vc[9];
                thm.lccolor = vc[10];
                thm.textcolor = vc[11];
                closegraph(themesw);
                update(0);
                setcurrentwindow(notepad);
                return;
            }
            else if(y >=470 && y <=500)
            {
                closegraph(themesw);
                setcurrentwindow(notepad);
                return;
            }
        }

    }

}
std::filesystem::path get_desktop_path()
{
    wchar_t* p;
    if (S_OK != (HRESULT)(SHGetKnownFolderPath(FOLDERID_Desktop, 0, NULL, &p)))
    {
        return std::filesystem::path();
    }

    std::filesystem::path result = p;
    CoTaskMemFree(p);
    return result;
}
void save_file(string file_name)
{
    if(nr_linii==maxi && lines.size()!=maxi && s.size()+s1.size()!=0)
    {
        s+=s1;
        ft+=ft1;
        lines.push_back(s);
        linesfont.push_back(ft);
    }
    else
    {
        if(s.size()+s1.size()!=0)
        {
            lines[nr_linii-1].clear();
            linesfont[nr_linii-1].clear();
            s+=s1;
            ft+=ft1;
            lines[nr_linii-1]+=s;
            linesfont[nr_linii-1]+=ft;
        }
    }
    ofstream fout;
    filesystem::path path = get_desktop_path();
    string path_str= path.string();
    string createFile="";
    createFile= path_str + "/" + file_name + ".txt";
    fout.open(createFile.c_str());
    for(auto it:lines)
        fout<<it<<'\n';
    fout.close();

}
void open_file(string file_name)
{
    filesystem::path path = get_desktop_path();
    string path_str= path.string();
    string createFile="";
    createFile= path_str + "/" + file_name + ".txt";
    FILE *fptr;
    fptr=fopen(createFile.c_str(),"r");
    fseek(fptr,0,SEEK_END);
    int filesizetext=ftell(fptr);
    fclose(fptr);
    if(filesizetext>2)
    {
        closegraph(notepad);
        okopen=0;
        startnotepad();
        okopen=1;
        ifstream fin;
        /*filesystem::path path = get_desktop_path();
        string path_str= path.string();
        string createFile="";
        createFile= path_str + "/" + file_name + ".txt";
        cout<< createFile;*/
        fin.open(createFile.c_str());
        string v;
        while(getline(fin,v))
        {
            int l=v.size();
            for(int i=0; i<l; i++)
                write(v[i]);
            enter(13,nr_linii);
        }
        backspace();
        line1+=lines[0];
        fin.close();
    }
}
string findcaract()
{
    int findw;
    if(language)
        findw = initwindow(500, 300, "Cauta", 500, 425);
    else
        findw = initwindow(500, 300, "Find", 500, 425);
    setcurrentwindow(findw);
    setfillstyle(SOLID_FILL, thm.lccolor);
    bar(0, 0, 500, 300);
    setcolor(thm.textcolor);
    setbkcolor(thm.lccolor);
    line(0, 250, 500, 250);
    rectangle(40, 100, 460, 150);
    if(language)
    {
        settextstyle(8, 0, 3);
        outtextxy(160, 70, "Ce cautati?");
        outtextxy(85, 220, "Limita de 25 caractere");
        outtextxy(200, 265, "Inchide");
    }
    else
    {
        settextstyle(8, 0, 3);
        outtextxy(75, 70, "What are you searching?");
        outtextxy(85, 220, "Limit of 25 characters");
        outtextxy(210, 265, "Close");
    }
    bool okk = false;
    int xt = 45;
    string file_name;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x>=40 && x<=460 && y>=100 && y<=150)
            {
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(41, 101, 459, 149);
                int cnt = 0;

                setcolor(thm.textcolor);
                line(xt, 105, xt, 145);
                while(1)
                {
                    int okkk = 0;
                    if(kbhit())
                    {
                        char key = getch();
                        if(key!=8 && key!=13)
                        {
                            if(cnt!=25)
                            {
                                cnt++;
                                char litera[2] = {key, '\0'};
                                file_name+=litera;
                                settextstyle(8, 0, 3);
                                outtextxy(xt, 115, litera);
                                setfillstyle(SOLID_FILL, thm.lccolor);
                                bar(xt-1, 104, xt+1, 146);
                                xt+=16;
                                setcolor(thm.textcolor);
                                line(xt, 105, xt, 145);
                                cout << file_name << '\n';
                            }
                        }
                        else if(key == 13)
                        {
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(xt-1, 104, xt+1, 146);
                            setcurrentwindow(findw);
                            okkk = 1;
                            if(language)
                            {
                                settextstyle(8, 0, 3);
                                outtextxy(170, 165, "Se cauta");
                                delay(500);
                                outtextxy(295, 165, ".");
                                delay(500);
                                outtextxy(310, 165, ".");
                                delay(500);
                                outtextxy(325, 165, ".");
                                bar(0, 151, 500, 200);
                            }
                            else
                            {
                                settextstyle(8, 0, 3);
                                outtextxy(150, 165, "Searching");
                                delay(500);
                                outtextxy(290, 165, ".");
                                delay(500);
                                outtextxy(305, 165, ".");
                                delay(500);
                                outtextxy(320, 165, ".");
                                delay(500);
                                bar(0, 151, 500, 200);
                            }
                            deschidere_rez = 1;
                            closegraph(findw);
                            return file_name;

                        }
                        else if(key == 8)
                        {
                            if(cnt!=0)
                            {
                                cnt--;
                                setfillstyle(SOLID_FILL, thm.lccolor);
                                bar(xt, 115, xt-spc-1, 145);
                                setfillstyle(SOLID_FILL, thm.lccolor);
                                bar(xt-1, 104, xt+1, 146);
                                file_name.pop_back();
                                xt-=16;
                                setcolor(thm.textcolor);
                                line(xt, 105, xt, 145);
                            }
                        }
                    }
                    if(okkk)
                        break;
                }
            }
            else if(x>=0 && x<=500 && y>=250 && y<=300)
            {
                okk = true;
                closegraph(findw);
                setcurrentwindow(notepad);
                return "";
            }
        }
    }
    return file_name;
}
void buton_file()
{
    int filew;
    if(language)
        filew = initwindow(500, 500, "Fisiere", 500, 250);
    else
        filew = initwindow(500, 500, "File", 500, 250);

    setcurrentwindow(filew);
    setfillstyle(SOLID_FILL, thm.lccolor);
    bar(0, 0, 500, 500);
    setcolor(thm.textcolor);
    if(language)
    {
        setbkcolor(thm.lccolor);
        setcolor(thm.textcolor);
        settextstyle(8, 0, 3);
        outtextxy(170, 15, "Fisier nou");
        outtextxy(185, 65, "Salveaza");
        outtextxy(165, 115, "Salveaza ca");
        outtextxy(210, 215, "Limba");
        outtextxy(185, 165, "Deschide");
    }
    else
    {
        setbkcolor(thm.lccolor);
        setcolor(thm.textcolor);
        settextstyle(8, 0, 3);
        outtextxy(190, 15, "New File");
        outtextxy(220, 65, "Save");
        outtextxy(195, 115, "Save As");
        outtextxy(190, 215, "Language");
        outtextxy(220, 165, "Open");
    }

    line(0, 50, 500, 50);
    line(0, 100, 500, 100);
    line(0, 150, 500, 150);
    line(0, 200, 500, 200);
    line(0, 250, 500, 250);

    if(language)
    {
        rectangle(110, 300, 380, 350);
        outtextxy(120, 315, "Inchide Fereastra");
    }
    else
    {
        rectangle(150, 300, 350, 350);
        outtextxy(160, 315, "Close Window");
    }
    circle(30, 465, 25);
    settextstyle(10,0,4);
    outtextxy(20, 450, "i");
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(y>100 && y<=150)
            {
                int savsw;
                if(language)
                    savsw = initwindow(500, 300, "Salveaza ca", 500, 425);
                else
                    savsw = initwindow(500, 300, "Save as", 500, 425);
                setcurrentwindow(savsw);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 500, 300);
                setcolor(thm.textcolor);
                setbkcolor(thm.lccolor);
                line(0, 250, 500, 250);
                rectangle(40, 100, 460, 150);
                if(language)
                {
                    settextstyle(8, 0, 3);
                    outtextxy(20, 70, "Introdu numele fisierului text:");
                    outtextxy(85, 220, "Limita de 16 caractere");
                    outtextxy(200, 265, "Inchide");
                }
                else
                {
                    settextstyle(8, 0, 3);
                    outtextxy(95, 70, "Enter text file name:");
                    outtextxy(85, 220, "Limit of 16 characters");
                    outtextxy(210, 265, "Close");
                }
                bool okk = false;
                int xt = 45;
                string file_name;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(x>=40 && x<=460 && y>=100 && y<=150)
                        {
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(41, 101, 459, 149);
                            int cnt = 0;

                            setcolor(thm.textcolor);
                            line(xt, 105, xt, 145);
                            while(1)
                            {
                                int okkk = 0;
                                if(kbhit())
                                {
                                    char key = getch();
                                    if(key!=8 && key!=13)
                                    {
                                        if(cnt!=16)
                                        {
                                            cnt++;
                                            char litera[2] = {key, '\0'};
                                            file_name+=litera;
                                            settextstyle(8, 0, 3);
                                            outtextxy(xt, 115, litera);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt-1, 104, xt+1, 146);
                                            xt+=16;
                                            setcolor(thm.textcolor);
                                            line(xt, 105, xt, 145);
                                            cout << file_name << '\n';
                                        }
                                    }
                                    else if(key == 13)
                                    {
                                        setfillstyle(SOLID_FILL, thm.lccolor);
                                        bar(xt-1, 104, xt+1, 146);
                                        save_file(file_name);
                                        setcurrentwindow(savsw);
                                        okkk = 1;
                                        if(language)
                                        {
                                            settextstyle(8, 0, 3);
                                            outtextxy(70, 165, "Fisier salvat pe desktop");
                                            delay(1000);
                                            bar(0, 151, 500, 200);
                                        }
                                        else
                                        {
                                            settextstyle(8, 0, 3);
                                            outtextxy(95, 165, "File saved on desktop");
                                            delay(1000);
                                            bar(0, 151, 500, 200);
                                        }

                                    }
                                    else if(key == 8)
                                    {
                                        if(cnt!=0)
                                        {
                                            cnt--;
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt, 115, xt-spc-1, 145);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt-1, 104, xt+1, 146);
                                            file_name.pop_back();
                                            xt-=16;
                                            setcolor(thm.textcolor);
                                            line(xt, 105, xt, 145);
                                        }
                                    }
                                }
                                if(okkk)
                                    break;
                            }
                        }
                        else if(x>=0 && x<=500 && y>=250 && y<=300)
                        {
                            okk = true;
                            closegraph(savsw);
                            setcurrentwindow(filew);
                        }
                    }
                    if(okk)
                        break;
                }

            }
            else if(y > 200 && y <=250)
            {
                int lanw;
                if(language)
                    lanw = initwindow(200, 200, "Schimba limba",500, 475);
                else
                    lanw = initwindow(200, 200, "Change Language",500, 475);
                setcurrentwindow(lanw);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 200, 200);
                setcolor(thm.textcolor);
                settextstyle(8, 0, 4);
                setbkcolor(thm.lccolor);
                readimagefile("ro.jpg",20, 95, 70, 135);
                readimagefile("uk.jpg",130, 95, 180, 135);
                int ok = 1;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(x >=20 && x<=70 && y>=95 && y<=135)
                        {
                            write_file();
                            delay(500);
                            language = 1;
                            settextstyle(8, 0, 2);
                            outtextxy(10, 150, "Limba schimbata");
                            delay(500);
                            closegraph(lanw);
                            closegraph(filew);
                            update(0);
                            setcurrentwindow(notepad);
                            return;

                        }
                        else if(x >=130 && x<=180 && y>=95 && y<=135)
                        {
                            write_file();
                            delay(500);
                            language = 0;
                            settextstyle(8, 0, 2);
                            outtextxy(5, 150, "Language updated");
                            delay(500);
                            closegraph(lanw);
                            closegraph(filew);
                            update(0);
                            setcurrentwindow(notepad);
                            return;

                        }
                    }
                    if(!ok)
                        break;
                }
            }
            else if(x >=110 && x<=380 && y>=300 && y<=350)
            {
                if(language)
                {
                    if(x >=110 && x<=380 && y>=300 && y<=350)
                    {
                        closegraph(filew);
                        setcurrentwindow(notepad);
                        return;
                    }
                }
                else
                {
                    if(x >=150 && x<=350 && y>=300 && y<=350)
                    {
                        closegraph(filew);
                        setcurrentwindow(notepad);
                        return;
                    }
                }


            }
            else if(y>=0 && y<=50)
            {
                update(1);
                delay(500);
                closegraph(filew);
                setcurrentwindow(notepad);
                return;
            }
            else if(y>50 && y<=100)
            {
                write_file();
                delay(500);
                if(language)
                {
                    settextstyle(8, 0, 3);
                    outtextxy(100, 255, "Progresul s-a salvat");
                    delay(1000);
                    setfillstyle(SOLID_FILL, thm.lccolor);
                    bar(0, 251, 500, 300);
                }
                else
                {
                    settextstyle(8, 0, 3);
                    outtextxy(45, 255, "The progress has been saved");
                    delay(1000);
                    setfillstyle(SOLID_FILL, thm.lccolor);
                    bar(0, 251, 500, 300);
                }
            }
            else if(y>150 && y<=200)
            {
                int openw;
                if(language)
                    openw = initwindow(500, 300, "Deschide", 500, 475);
                else
                    openw = initwindow(500, 300, "Open", 500, 475);
                setcurrentwindow(openw);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 500, 300);
                setcolor(thm.textcolor);
                setbkcolor(thm.lccolor);
                line(0, 250, 500, 250);
                rectangle(40, 100, 460, 150);
                if(language)
                {
                    settextstyle(8, 0, 3);
                    outtextxy(20, 70, "Introdu numele fisierului text:");
                    outtextxy(85, 220, "Limita de 16 caractere");
                    outtextxy(200, 265, "Inchide");
                }
                else
                {
                    settextstyle(8, 0, 3);
                    outtextxy(95, 70, "Enter text file name:");
                    outtextxy(85, 220, "Limit of 16 characters");
                    outtextxy(210, 265, "Close");
                }
                bool okk = false;
                int xt = 45;
                string file_name;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(x>=40 && x<=460 && y>=100 && y<=150)
                        {
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(41, 101, 459, 149);
                            int cnt = 0;

                            setcolor(thm.textcolor);
                            line(xt, 105, xt, 145);
                            while(1)
                            {
                                int okkk = 0;
                                if(kbhit())
                                {
                                    char key = getch();
                                    if(key!=8 && key!=13)
                                    {
                                        if(cnt!=16)
                                        {
                                            cnt++;
                                            char litera[2] = {key, '\0'};
                                            file_name+=litera;
                                            settextstyle(8, 0, 3);
                                            outtextxy(xt, 115, litera);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt-1, 104, xt+1, 146);
                                            xt+=16;
                                            setcolor(thm.textcolor);
                                            line(xt, 105, xt, 145);
                                            cout << file_name << '\n';
                                        }
                                    }
                                    else if(key == 13)
                                    {
                                        setfillstyle(SOLID_FILL, thm.lccolor);
                                        bar(xt-1, 104, xt+1, 146);
                                        open_file(file_name);
                                        closegraph(openw);
                                        closegraph(filew);
                                        setcurrentwindow(notepad);
                                        return;

                                        setcurrentwindow(openw);
                                        okkk = 1;
                                        if(language)
                                        {
                                            settextstyle(8, 0, 3);
                                            outtextxy(145, 165, "Fisier deschis");
                                            delay(1000);
                                            bar(0, 151, 500, 200);
                                        }
                                        else
                                        {
                                            settextstyle(8, 0, 3);
                                            outtextxy(165, 165, "File opened");
                                            delay(1000);
                                            bar(0, 151, 500, 200);
                                        }
                                        closegraph(openw);
                                        closegraph(filew);
                                        setcurrentwindow(notepad);
                                        return;

                                    }
                                    else if(key == 8)
                                    {
                                        if(cnt!=0)
                                        {
                                            cnt--;
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt, 115, xt-spc-1, 145);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xt-1, 104, xt+1, 146);
                                            file_name.pop_back();
                                            xt-=16;
                                            setcolor(thm.textcolor);
                                            line(xt, 105, xt, 145);

                                        }
                                    }
                                }
                                if(okkk)
                                    break;
                            }
                        }
                        else if(x>=0 && x<=500 && y>=250 && y<=300)
                        {
                            okk = true;
                            closegraph(openw);
                            setcurrentwindow(filew);
                        }
                    }
                    if(okk)
                        break;
                }
            }
            else if(x>=5 && y>=440 && x<=55 && y<=490)
            {
                int helpw;
                if(language)
                    helpw = initwindow(500, 300, "Ajutor", 500, 400);
                else
                    helpw = initwindow(500, 300, "Help", 500, 400);
                setcurrentwindow(helpw);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 500, 300);
                setcolor(thm.textcolor);
                setbkcolor(thm.lccolor);
                line(0, 270, 500, 270);
                if(language)
                {
                    settextstyle(10, 0, 3);
                    outtextxy(40, 10, "Comenzi rapide de la tastatura");
                    settextstyle(8, 0, 2);
                    outtextxy(0, 70, "Ctrl+V = Lipire");
                    outtextxy(0, 90, "Ctrl+F = Cautare");
                    outtextxy(0, 110, "Ctrl+N = Fila noua");
                    outtextxy(0, 130, "Ctrl+S = Salvare rapida");
                    outtextxy(0, 150, "Ctrl+E = Selectie + Copiere");
                    outtextxy(0, 170, "Ctrl+Sageata sus = Scrolare in sus");
                    outtextxy(0, 190, "Ctrl+Sageata jos = Scrolare in jos");
                    outtextxy(205, 275, "Inchide");
                }
                else
                {
                    settextstyle(10, 0, 3);
                    outtextxy(115, 10, "Keyboard shortcuts");
                    settextstyle(8, 0, 2);
                    outtextxy(0, 70, "Ctrl+V = Paste");
                    outtextxy(0, 90, "Ctrl+F = Find");
                    outtextxy(0, 110, "Ctrl+N = New file");
                    outtextxy(0, 130, "Ctrl+S = Quick save");
                    outtextxy(0, 150, "Ctrl+E = Select + Copy");
                    outtextxy(0, 170, "Ctrl+Arrow Up = Scroll up");
                    outtextxy(0, 190, "Ctrl+Arrow Down = Scroll down");
                    outtextxy(215, 275, "Close");
                }
                int ok = 1;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(y>=270)
                        {
                            closegraph(helpw);
                            setcurrentwindow(filew);
                            ok = 0;
                        }
                    }
                    if(!ok)
                        break;
                }
            }
        }
    }
}


void buton_style(text &txt, border &brd, int &x_scris, scrollbar &sbar)
{
    int stylew;
    if(language)
        stylew = initwindow(500, 500, "Stil", 500, 250);
    else
        stylew = initwindow(500, 500, "Style", 500, 250);
    setcurrentwindow(stylew);
    setfillstyle(SOLID_FILL, thm.lccolor);
    bar(0, 0, 500, 500);
    setcolor(thm.textcolor);
    if(language)
    {
        setbkcolor(thm.lccolor);
        settextstyle(8, 0, 3);
        outtextxy(160, 15, "Schimba Font");
        outtextxy(70, 65, "Schimba culoarea textului");
        outtextxy(75, 115, "Redimensionare fereastra");
    }
    else
    {
        setbkcolor(thm.lccolor);
        settextstyle(8, 0, 3);
        outtextxy(160, 15, "Change Font");
        outtextxy(120, 65, "Change Text Color");
        outtextxy(145, 115, "Resize Window");
    }
    line(0, 50, 500, 50);
    line(0, 100, 500, 100);
    line(0, 150, 500, 150);
    if(language)
    {
        rectangle(110, 300, 380, 350);
        outtextxy(120, 315, "Inchide Fereastra");
    }
    else
    {
        rectangle(150, 300, 350, 350);
        outtextxy(160, 315, "Close Window");
    }
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if(x>=150 && x<=350 && y>=300 && y<=350)
            {
                closegraph(stylew);
                setcurrentwindow(notepad);
                return;
            }
            else if(x>=0 && x<=500 && y>=0 && y<50)
            {
                int fontw;
                if(language)
                    fontw = initwindow(300, 270, "Meniu schimbare font", 500, 325);
                else
                    fontw = initwindow(300, 270, "Font Change Meniu", 500, 325);
                setfillstyle(SOLID_FILL, thm.lccolor);
                setcurrentwindow(fontw);
                bar(0, 0, 500, 500);
                setbkcolor(thm.lccolor);
                setcolor(thm.textcolor);
                for(int i=30; i<=240; i+=30)
                    line(0, i, 300, i);
                settextstyle(0, 0, 2);
                outtextxy(0, 7, "DEFAULT_FONT");
                settextstyle(6, 0, 2);
                outtextxy(0, 35, "SIMPLEX_FONT");
                settextstyle(2, 0, 2);
                outtextxy(0, 73, "SMALL_FONT");
                settextstyle(3, 0, 2);
                outtextxy(0, 93, "SANS_SERIF_FONT");
                settextstyle(10, 0, 2);
                outtextxy(0, 125, "BOLD_FONT");
                settextstyle(5, 0, 2);
                outtextxy(0, 157, "SCRIPT_FONT");
                settextstyle(8, 0, 2);
                outtextxy(0, 185, "COMPLEX_FONT");
                settextstyle(11, 0, 2);
                outtextxy(0, 217, "SECRET_FONT");
                if(language)
                {
                    settextstyle(8, 0, 1);
                    outtextxy(75, 247, "M-am razgandit");
                }
                else
                {
                    settextstyle(8, 0, 1);
                    outtextxy(5, 247, "Nevermind, changed my mind");
                }
                while(1)
                {
                    int ok = 1;
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(y>=0 && y<30)
                        {
                            spc = 27;
                            txt.font = 0;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>30 && y<60)
                        {
                            spc = 30;
                            txt.font = 6;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>60 && y<90)
                        {
                            spc = 5;
                            txt.font = 2;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>90 && y<120)
                        {
                            spc = 20;
                            txt.font = 3;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>120 && y<150)
                        {
                            spc = 16;
                            txt.font = 10;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>150 && y<180)
                        {
                            /// cauta pozitia ultimului caracter si de acolo incepe backspace
                            spc = 26;
                            txt.font = 5;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>180 && y<210)
                        {
                            spc = 16;
                            txt.font = 8;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>210 && y<240)
                        {
                            spc = 16;
                            txt.font = 11;
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                        else if(y>240 && y<=270)
                        {
                            closegraph(fontw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }

                    }
                    if(!ok)
                        break;
                }
            }
            else if(y > 50 && y < 100)
            {
                int colorw;
                if(language)
                    colorw = initwindow(360, 360, "Meniu schimbare culoare", 500, 375);
                else
                    colorw = initwindow(360, 360, "Color Change Menu", 500, 375);
                setcurrentwindow(colorw);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 360, 360);
                setbkcolor(thm.lccolor);
                setcolor(thm.textcolor);
                int cnt = 0;
                for(int y = 25; y<=265; y+=80)
                    for(int x = 40; x<=280; x+=80)
                    {
                        rectangle(x, y, x+40, y+40);
                        setfillstyle(SOLID_FILL, cnt);
                        bar(x+1, y+1, x+40, y+40);
                        cnt++;
                    }
                line(0, 330, 360, 330);
                if(language)
                {
                    settextstyle(8, 0, 1);
                    outtextxy(105, 335, "M-am razgandit");
                }
                else
                {
                    settextstyle(8, 0, 1);
                    outtextxy(35, 335, "Nevermind, changed my mind");
                }
                int ok = 1;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int xc, yc;
                        getmouseclick(WM_LBUTTONDOWN, xc, yc);
                        int cntc = 0;
                        for(int y = 40; y<=280; y+=80)
                            for(int x = 40; x<=280; x+=80)
                            {
                                if(xc >= x && xc <= x+40 && yc>=y && yc<=y+40)
                                {
                                    txt.color = cntc;
                                    closegraph(colorw);
                                    setcurrentwindow(stylew);
                                    ok = 0;
                                }
                                cntc++;
                            }
                        if(yc >=330 && yc <=360)
                        {
                            closegraph(colorw);
                            setcurrentwindow(stylew);
                            ok = 0;
                        }
                    }
                    if(!ok)
                        break;
                }

            }
            else if(y > 100 && y <= 150)
            {
                int resizew;
                if(language)
                    resizew = initwindow(200, 300, "Resize the main window", 500, 425);
                else
                    resizew = initwindow(200, 300, "Redimensioneaza", 500, 425);
                setfillstyle(SOLID_FILL, thm.lccolor);
                bar(0, 0, 200, 300);
                setbkcolor(thm.lccolor);
                setcolor(thm.textcolor);
                circle(30, 240, 18);
                settextstyle(10, 0, 3);
                outtextxy(23, 229, "i");
                int x1, x2;
                if(language)
                {
                    settextstyle(8, 0, 2);
                    outtextxy(20, 100, "Lungime: ");
                    rectangle(120, 100, 180, 120);
                    char ch[10];
                    sprintf(ch, "%d", brd.x);
                    settextstyle(8, 0, 1);
                    outtextxy(125, 102, ch);
                    x1 = 120;
                    x2 = 180;
                }
                else
                {
                    settextstyle(8, 0, 2);
                    outtextxy(20, 100, "Width: ");
                    rectangle(100, 100, 160, 120);
                    char ch[10];
                    sprintf(ch, "%d", brd.x);
                    settextstyle(8, 0, 1);
                    outtextxy(105, 102, ch);
                    x1 = 100;
                    x2 = 160;
                }
                if(language)
                {
                    settextstyle(8, 0, 2);
                    outtextxy(20, 160, "Latime: ");
                }
                else
                {
                    settextstyle(8, 0, 2);
                    outtextxy(20, 160, "Height: ");
                }
                rectangle(110, 160, 170, 180);
                char chh[10];
                sprintf(chh, "%d", brd.y);
                settextstyle(8, 0, 1);
                outtextxy(115, 162, chh);
                line(0, 270, 200, 270);
                if(language)
                {
                    settextstyle(8, 0, 1);
                    outtextxy(10, 275, "Inchide fereastra");
                }
                else
                {
                    settextstyle(8, 0, 1);
                    outtextxy(30, 275, "Close window");
                }

                int okkkk = 1;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int x, y;
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        if(x >=x1 && x <=x2 && y>=100 && y<=120)
                        {
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(x1+1, 100+1, x2, 120);
                            int xs = x1+5;
                            int ys = 102;
                            int cnt = 0;
                            string nr;
                            int ok = 1;
                            int val = -1;
                            setcolor(thm.textcolor);
                            line(xs, 105, xs, 115);
                            while(1)
                            {
                                if(kbhit())
                                {
                                    char key = getch();
                                    if(key >=48 && key <= 57)
                                    {
                                        cnt++;
                                        if(cnt == 5)
                                        {
                                            ok = 0;
                                            break;
                                        }
                                        else
                                        {
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xs-1, 104, xs+1, 116);
                                            nr+=key;
                                            char litera[2] = {key, '\0'};
                                            settextstyle(8, 0, 1);
                                            outtextxy(xs, ys, litera);
                                            xs+=11;
                                            setcolor(thm.textcolor);
                                            line(xs, 105, xs, 115);
                                        }
                                    }
                                    else if(key == 13)
                                    {

                                        val = stoi(nr);
                                        if(val > 1600 || val < 450)
                                        {
                                            if(language)
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(10, 130, "Valoare invalida!");
                                            }
                                            else
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(20, 130, "Invalid input!");
                                            }
                                            delay(1000);
                                            setcurrentwindow(resizew);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(0, 130, 300, 150);
                                        }
                                        else
                                        {
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xs-1, 104, xs+1, 116);
                                            if(language)
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(10, 130, "Lungime schimbata!");
                                            }
                                            else
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(20, 130, "Width updated!");
                                            }

                                            brd.x = val;
                                            sbar.x1 = brd.x - 26;
                                            sbar.y1 = 85;
                                            sbar.x2 = brd.x - 4;
                                            sbar.y2 = brd.y - 34;
                                            update(0);
                                            setcurrentwindow(resizew);
                                            delay(1000);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(0, 130, 300, 150);
                                            ok = 0;

                                        }
                                    }
                                    else if(key == 8 && cnt!=0)
                                    {
                                        setfillstyle(SOLID_FILL, thm.lccolor);
                                        bar(xs-1, 104, xs+1, 116);
                                        if(!nr.empty())
                                            nr.pop_back();
                                        setfillstyle(SOLID_FILL, thm.lccolor);
                                        bar(xs, ys, xs-11, ys+15);
                                        xs-=11;
                                        setcolor(thm.textcolor);
                                        line(xs, 105, xs, 115);
                                        cnt--;
                                    }
                                }

                                if(!ok)
                                    break;
                            }
                            if(!ok && val == -1)
                            {
                                val = stoi(nr);
                                if(val > 1600 || val < 450)
                                {
                                    if(language)
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(10, 130, "Valoare invalida!");
                                    }
                                    else
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(20, 130, "Invalid input!");
                                    }
                                    delay(1000);
                                    setcurrentwindow(resizew);
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(0, 130, 300, 150);
                                }
                                else
                                {
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(xs-1, 104, xs+1, 116);
                                    if(language)
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(10, 130, "Lungime schimbata!");
                                    }
                                    else
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(20, 130, "Width updated!");
                                    }
                                    brd.x = val;
                                    sbar.x1 = brd.x - 26;
                                    sbar.y1 = 85;
                                    sbar.x2 = brd.x - 4;
                                    sbar.y2 = brd.y - 34;
                                    update(0);
                                    setcurrentwindow(resizew);
                                    delay(1000);
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(0, 130, 300, 150);
                                    ok = 0;

                                }
                            }
                        }
                        else if(x >= 110 && x<=170 && y>=160 && y<=180)
                        {
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(110+1, 160+1, 170, 180);
                            int xs = 115;
                            int ys = 162;
                            int cnt = 0;
                            string nr;
                            int ok = 1;
                            int val = -1;
                            setcolor(thm.textcolor);
                            line(xs, 165, xs, 175);
                            while(1)
                            {
                                if(kbhit())
                                {
                                    char key = getch();
                                    if(key >=48 && key <= 57)
                                    {
                                        cnt++;
                                        if(cnt == 5)
                                        {
                                            ok = 0;
                                            break;
                                        }
                                        else
                                        {
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xs-1, 164, xs+1, 176);
                                            nr+=key;
                                            char litera[2] = {key, '\0'};
                                            settextstyle(8, 0, 1);
                                            outtextxy(xs, ys, litera);
                                            xs+=11;
                                            setcolor(thm.textcolor);
                                            line(xs, 165, xs, 175);
                                        }
                                    }
                                    else if(key == 13)
                                    {
                                        val = stoi(nr);
                                        if(val > 900 || val < 150)
                                        {
                                            if(language)
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(10, 190, "Valoare invalida!");
                                            }
                                            else
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(20, 190, "Invalid input!");
                                            }
                                            delay(1000);
                                            setcurrentwindow(resizew);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(0, 190, 300, 210);
                                        }
                                        else
                                        {
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(xs-1, 164, xs+1, 176);
                                            if(language)
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(10, 190, "Latime schimbata!");
                                            }
                                            else
                                            {
                                                settextstyle(8, 0, 1);
                                                outtextxy(20, 190, "Height updated!");
                                            }
                                            brd.y = val;
                                            sbar.x1 = brd.x - 26;
                                            sbar.y1 = 85;
                                            sbar.x2 = brd.x - 4;
                                            sbar.y2 = brd.y - 34;
                                            update(0);
                                            setcurrentwindow(resizew);
                                            delay(1000);
                                            setfillstyle(SOLID_FILL, thm.lccolor);
                                            bar(0, 190, 300, 210);
                                            ok = 0;
                                        }
                                    }
                                    else if(key == 8&& cnt!=0)
                                    {
                                        setfillstyle(SOLID_FILL, thm.lccolor);
                                        bar(xs-1, 164, xs+1, 176);
                                        if(!nr.empty())
                                            nr.pop_back();
                                        setfillstyle(SOLID_FILL, 9);
                                        bar(xs, ys, xs-11, ys+15);
                                        xs-=11;
                                        setcolor(thm.textcolor);
                                        line(xs, 165, xs, 175);
                                        cnt--;
                                    }
                                }

                                if(!ok)
                                    break;
                            }
                            if(!ok && val == -1)
                            {
                                val = stoi(nr);
                                if(val > 900 || val < 150)
                                {
                                    if(language)
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(10, 190, "Valoare invalida!");
                                    }
                                    else
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(20, 190, "Invalid input!");
                                    }
                                    delay(1000);
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(0, 190, 300, 210);
                                }
                                else
                                {
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(xs-1, 164, xs+1, 176);
                                    if(language)
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(10, 190, "Latime schimbata!");
                                    }
                                    else
                                    {
                                        settextstyle(8, 0, 1);
                                        outtextxy(20, 190, "Height updated!");
                                    }
                                    brd.y = val;
                                    sbar.x1 = brd.x - 26;
                                    sbar.y1 = 85;
                                    sbar.x2 = brd.x - 4;
                                    sbar.y2 = brd.y - 34;
                                    update(0);
                                    delay(1000);
                                    setfillstyle(SOLID_FILL, thm.lccolor);
                                    bar(0, 190, 300, 210);
                                    ok = 0;
                                }
                            }
                        }
                        else if(y >=270 && y <=300)
                        {
                            closegraph(resizew);
                            setcurrentwindow(stylew);
                            okkkk = 0;
                        }
                        else if(x>= 12 && x<=48 && y>=222 && y<=258)
                        {
                            int valw;
                            if(language)
                                valw = initwindow(300, 200, "Ajutor", 550, 300);
                            else
                                valw = initwindow(300, 200, "Help", 550, 300);
                            setcurrentwindow(valw);
                            setbkcolor(thm.lccolor);
                            setfillstyle(SOLID_FILL, thm.lccolor);
                            bar(0, 0, 500, 500);
                            setcolor(thm.textcolor);
                            line(0, 170, 300, 170);
                            if(language)
                            {
                                settextstyle(10, 0, 3);
                                outtextxy(65, 10, "Valori valide");
                                settextstyle(8, 0, 2);
                                outtextxy(0, 70, "Lungime: 450 - 1600");
                                outtextxy(0, 110, "Latime: 150 - 900");
                                outtextxy(105, 175, "Inchide");
                            }
                            else
                            {
                                settextstyle(10, 0, 3);
                                outtextxy(70, 10, "Valid inputs");
                                settextstyle(8, 0, 2);
                                outtextxy(0, 70, "Width: 450 - 1600");
                                outtextxy(0, 110, "Height: 150 - 900");
                                outtextxy(115, 175, "Close");
                            }
                            int ok = 1;
                            while(1)
                            {
                                if(ismouseclick(WM_LBUTTONDOWN))
                                {
                                    int x, y;
                                    getmouseclick(WM_LBUTTONDOWN, x, y);
                                    if(y>=170)
                                    {
                                        closegraph(valw);
                                        setcurrentwindow(resizew);
                                        ok = 0;
                                    }
                                }
                                if(!ok)
                                    break;
                            }
                        }
                    }
                    if(!okkkk)
                        break;
                }

            }
        }
    }
}
