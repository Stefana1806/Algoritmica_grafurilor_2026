#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <fstream>


// Structura pentru noduri coada
struct Nod
{
    int val;
    Nod* urm;
};

// Coada pentru BFS
struct Coada
{
    Nod* prim;
    Nod* ultim;
};
struct Stiva
{
    Nod* prim;
    Nod* ultim;
};
Coada* coadaGoala()
{
    Coada* q = new Coada;
    q->prim = NULL;
    q->ultim = NULL;

    return q;
}

using namespace std;

void prim(int start);
int gaseste_nod(int x,int y);
int tempWindowCostOR();
void deseneaza_noduri();
int gaseste_nodOR(int x,int y);
void Algoritmica_grafurilor();
void creare_alg_neorientat();
void creeaza_meniu_principal();
void creare_alg_orientat();
void grafica_principala();
void click_nod();
void buton_algoritm();
void click_muchie_neor();
void mutare_nod();
void buton_alg_orientat();
void buton_back();
void undo();
void click_cost();
void deseneaza_cost_cu_muchie(int x1, int y1, int x2, int y2, int cost);
void deseneaza_cost_cu_muchieor(int x1, int y1, int x2, int y2, int cost);
void deseneaza_costuri();
int poate_plasa_nod(int x, int y);
int tempWindowCost();
void deseneaza_muchieOR(int x1, int y1, int x2, int y2);
void deseneaza_muchiiOR();
void click_muchieOR();
void click_costOR();
void mutare_nodOR();
void deseneaza_nod(int x, int y);
void deseneaza_nodOR(int x,int y);
void deseneaza_meniu();
void meniu_orientat();//deseneaza meniu pentru graf orientat
void pagina_noua();
void deseneaza_tot();
void deseneaza_totOR();
void deseneaza_muchii();
void deseneaza_muchie(int x1, int y1, int x2, int y2);
void bfs();
void dfs();
void vizualizeaza_nod(int val);
void afiseaza_mesaj(char* mesaj);
void afiseaza_int(int x);
void bfs_orientat();
void dfs_orientat();
void undo_orientat();
void creeazaFereastra(int x1, int y1, int x2, int y2, char* titlu);
void modif_meniu();
void culori_m();
void schimba_culoare();
void fonturi();
void schimba_font();
void outtextxy_centrat(int x1, int y1, int x2, int y2, char* text,int size_font);
bool este_graf_eulerian();
bool este_graf_hamiltonian();
void verifica_eulerian();
void verifica_hamiltonian();
bool hamiltonian_backtracking(int pos, int drum[], bool vizitat[]);
void insereazaCoada(Coada* q, int val);
bool esteCoadaGoala(Coada* q);
int citesteNodCoada(Coada* q);
void eliminaNodCoada(Coada* q);
void dijkstraOR(int s);
void dijkstra(int s);
int verif(int vizitat[], int n);
void bellmanFord();
void floydWarshall();
int temp_window_sursa();
void salveaza_graf_orientat();
void salveaza_graf();
void incarca_graf_orientat();
void incarca_graf();
void bellmanFordOR();
int temp_window_sursaOR();


int x,y,xc,yc,mouse_x,mouse_y;
int coordonate[101][3], raza=20, n=0, muchii[101][101],costuri[101][101], exista_cost[101][101];
int coordonateOR[101][3], nOR = 0, muchiiOR[101][101], costuriOR[101][101], exista_costOR[101][101];;
int vf=0,unod[10001][3],tipop[10001]= {0},nodm[1001][3],costn[10001][3];
int w = getmaxwidth(), h = getmaxheight();
int bw=w/5;// latimea butonului
int bh=h/10;// inaltimea butonului
int leftb=w/2-bw/2;
int rightb=w/2+bw/2;
int topb=(3*h)/4-bh/2;// josul ecranului, centrat
int bottomb=(3*h)/4+bh/2;
int Xtext = 190;
int Ytext = h - 295;
int textStep = 20;   // distanța între rânduri
int x1=50,x2=650,yy1=75,y2=475;
int culoare=MAGENTA,textculoare=WHITE;
int font=DEFAULT_FONT,marimef=0.8;
const int INF = INT_MAX / 2;
int paginaCurenta = 0;
int rezultatePePagina = 10;   // câte linii afișezi
int totalRezultate;           // câte rezultate ai în total
int totalPagini;



void deseneaza_nod(int x, int y)
{
    setcolor(textculoare);
    n++;
    coordonate[n][1] = x;
    coordonate[n][2] = y;

    vf++;
    unod[vf][1]=x;
    unod[vf][2]=y;
    tipop[vf]=2;
    char c[5];
    itoa(n, c, 10);

    circle(x, y, raza);
    outtextxy(x - 5, y - 5, c);
}

void deseneaza_muchie(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dist = sqrt(dx*dx + dy*dy);

    if(dist == 0)
        return; // evităm împărțirea la 0

    // Factor pentru a merge exact pe circumferința cercului
    double factor = raza / dist;

    // Calculăm punctul de plecare tangent la cercul nodului 1
    int xs = (int)(x1 + dx * factor);
    int ys = (int)(y1 + dy * factor);

    // Calculăm punctul de sosire tangent la cercul nodului 2
    int xe = (int)(x2 - dx * factor);
    int ye = (int)(y2 - dy * factor);

    line(xs, ys, xe, ye); // desenăm muchia
}

void deseneaza_muchii()
{
    setcolor(textculoare);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(muchii[i][j])
            {
                int x1 = coordonate[i][1];
                int y1 = coordonate[i][2];
                int x2 = coordonate[j][1];
                int y2 = coordonate[j][2];
                deseneaza_muchie(x1, y1, x2, y2);
            }
        }
    }
}
void click_nod()
{
    int ok = 0, x1, y1, meniuw=320+raza, meniuh=h-340+raza,meniuw2=w-160+raza;
    while(!ok )
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            if (poate_plasa_nod ( x1, y1 ) && meniuw < x1 && meniuh>y1 && meniuw2>x1)
            {
                deseneaza_nod( x1, y1 );
                ok = 1;
            }
        }
    }
}
void click_muchie_neor()
{
    int x1, y1, x2, y2;
    int nod1 = 0, nod2 = 0;

    while(!nod1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))//verifica sa se dea click pe un nod nu pe langa el
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            nod1 = gaseste_nod(x1, y1);
        }
    }
    x1 = coordonate[nod1][1];
    y1 = coordonate[nod1][2];

    // Redesenează totul înainte de a începe tragerea liniei
    cleardevice();
    deseneaza_tot();
    // Desenează linia temporară inițială
    setcolor(textculoare);
    int mx = mousex();
    int my = mousey();
    deseneaza_muchie(x1, y1, mx, my);

    int mx_old = mx, my_old = my;

    while(!nod2)
    {
        int mx = mousex();
        int my = mousey();

        // Dacă mouse-ul s-a mutat, actualizează linia temporară
        if(mx != mx_old || my != my_old)
        {
            // Șterge linia veche fără a afectă restul
            setcolor(culoare); // stergere linii
            deseneaza_muchie(x1, y1, mx_old, my_old);
            setcolor(textculoare);
            for(int i = 1; i <= n; i++)
            {
                // Verifică dacă linia veche trecea aproape de nod
                int dx_old = mx_old - coordonate[i][1];
                int dy_old = my_old - coordonate[i][2];
                int dist_old = dx_old*dx_old + dy_old*dy_old;
                // Dacă punctul final al liniei era aproape de nod, redesenează nodul
                if(dist_old < raza*raza * 9) // 3*raza pentru siguranță
                {
                    circle(coordonate[i][1], coordonate[i][2], raza);
                    char c[5];
                    itoa(i, c, 10);
                    outtextxy(coordonate[i][1] - 5, coordonate[i][2] - 5, c);
                }
            }
            // Desenează linia nouă
            setcolor(textculoare);
            deseneaza_muchie(x1, y1, mx, my);
            mx_old = mx;
            my_old = my;
        }
        if(ismouseclick(WM_LBUTTONDOWN)) // verifica ca la click sa fie nodul 2
        {
            getmouseclick(WM_LBUTTONDOWN, x2, y2);
            setcolor(culoare);
            deseneaza_muchie(x1, y1, x2, y2);
            setcolor(textculoare);

            // Redesenează nodurile care ar fi putut fi afectate
            setcolor(textculoare);
            for(int i = 1; i <= n; i++)
            {
                int dx = mx - coordonate[i][1];
                int dy = my - coordonate[i][2];
                int dist = dx*dx + dy*dy;
                if(dist < raza*raza * 9)
                {
                    circle(coordonate[i][1], coordonate[i][2], raza);
                    char c[5];
                    itoa(i, c, 10);
                    outtextxy(coordonate[i][1] - 5, coordonate[i][2] - 5, c);
                }
            }
            nod2 = gaseste_nod(x2, y2);
            if(nod1 == nod2)
            {
                cleardevice();
                deseneaza_tot();
                return;
            }
        }
    }
    x2 = coordonate[nod2][1];
    y2 = coordonate[nod2][2];

    muchii[nod1][nod2] = 1;
    muchii[nod2][nod1] = 1;

    vf++;
    tipop[vf]=1;
    nodm[vf][1]=nod1;
    nodm[vf][2]=nod2;

    cleardevice();
    deseneaza_tot();
}
void click_cost()
{
    int x1, y1, x2, y2;
    int nod1 = 0, nod2 = 0;

    while(!nod1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))//verifica sa se dea click pe un nod nu pe langa el
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            nod1 = gaseste_nod(x1, y1);
        }
    }
    while(!nod2)
    {
        if(ismouseclick(WM_LBUTTONDOWN)) // verifica ca la click sa fie nodul 2
        {
            getmouseclick(WM_LBUTTONDOWN, x2, y2);
            nod2 = gaseste_nod(x2, y2);
        }
    }
    if(nod1==nod2)
        return;

    vf++;
    if( muchii[nod1][nod2] && nod1 != nod2 )
    {
        int cost = tempWindowCost();
        costuri[nod1][nod2] = cost;
        costuri[nod2][nod1] = cost;
        exista_cost[nod1][nod2] = 1;
        exista_cost[nod2][nod1] = 1;

        tipop[vf]=3;
        costn[vf][1]=nod1;
        costn[vf][2]=nod2;
        cleardevice();
        deseneaza_tot();

    }
    else   if( muchii[nod1][nod2]== 0 && nod1 != nod2 )
    {
        int cost = tempWindowCost();
        costuri[nod1][nod2] = cost;
        costuri[nod2][nod1] = cost;
        muchii[nod1][nod2] = 1;
        muchii[nod2][nod1] = 1;
        exista_cost[nod1][nod2] = 1;
        exista_cost[nod2][nod1] = 1;

        tipop[vf]=3;
        costn[vf][1]=nod1;
        costn[vf][2]=nod2;
        cleardevice();
        deseneaza_tot();
    }
}
void deseneaza_cost_cu_muchieOR(int x1, int y1, int x2, int y2, int cost)
{
    setcolor(textculoare);
    deseneaza_muchieOR(x1, y1, x2, y2);
    int x_mijloc = (x1 + x2) / 2;
    int y_mijloc = (y1 + y2) / 2;
    // Creează un dreptunghi de fundal pentru cost
    setfillstyle(SOLID_FILL, culoare);
    setcolor(culoare);
    int latime_txt= textwidth("0000");
    int inaltime_txt = textheight("0");
    bar(x_mijloc - latime_txt/2 - 2,
        y_mijloc - inaltime_txt/2 - 2,
        x_mijloc + latime_txt/2 + 2,
        y_mijloc + inaltime_txt/2 + 2);
    setcolor(textculoare);
    char c[10];
    itoa(cost, c, 10);
    settextstyle(font, HORIZ_DIR, marimef);
    outtextxy(x_mijloc - textwidth(c)/2, y_mijloc - textheight(c)/2, c);
    settextstyle(font, HORIZ_DIR, 0);
}
void click_costOR()
{
    int x1, y1, x2, y2;
    int nod1 = 0, nod2 = 0;

    while(!nod1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x1,y1);
            nod1 = gaseste_nod(x1,y1);
        }
    }
    while(!nod2)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x2,y2);
            nod2 = gaseste_nod(x2,y2);
        }
    }

    if(nod1 == nod2)
        return;

    int cost = tempWindowCostOR();
    vf++;
    tipop[vf]=3;
    costn[vf][1]=nod1;
    costn[vf][2]=nod2;

    if(muchii[nod1][nod2])
    {
        // Există deja arc, doar actualizează costul
        costuri[nod1][nod2] = cost;
        exista_cost[nod1][nod2] = 1;
    }
    else
    {
        // Nu există arc, creează arc cu cost
        muchii[nod1][nod2] = 1;
        costuri[nod1][nod2] = cost;
        exista_cost[nod1][nod2] = 1;
    }
    cleardevice();
    deseneaza_totOR();
}
void deseneaza_costuriOR()
{
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(exista_cost[i][j] && i != j)
            {
                deseneaza_cost_cu_muchieOR(coordonate[i][1], coordonate[i][2],
                                           coordonate[j][1], coordonate[j][2],costuri[i][j]);
            }
        }
    }
}
void click_muchieOR()
{
    int x1, y1, x2, y2;
    int nod1 = 0, nod2 = 0;

    while(!nod1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))//verifica sa se dea click pe un nod nu pe langa el
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            nod1 = gaseste_nod(x1, y1);
        }
    }
    x1 = coordonate[nod1][1];
    y1 = coordonate[nod1][2];
    cleardevice();
    deseneaza_totOR();
    // Desenează linia temporară inițială
    setcolor(textculoare);
    int mx = mousex();
    int my = mousey();
    deseneaza_muchieOR(x1, y1, mx, my);

    int mx_old = mx, my_old = my;

    while(!nod2)
    {
        int mx = mousex();
        int my = mousey();

        // Dacă mouse-ul s-a mutat, actualizează linia temporară
        if(mx != mx_old || my != my_old)
        {
            // Șterge linia veche
            setcolor(culoare); // stergere linii
            deseneaza_muchieOR(x1, y1, mx_old, my_old);
            // Redesenează nodurile afectate
            setcolor(textculoare);
            for(int i = 1; i <= n; i++)
            {
                int dx_old = mx_old - coordonate[i][1];
                int dy_old = my_old - coordonate[i][2];
                int dist_old = dx_old*dx_old + dy_old*dy_old;
                if(dist_old < raza*raza * 9)
                {
                    circle(coordonate[i][1], coordonate[i][2], raza);
                    char c[5];
                    itoa(i, c, 10);
                    outtextxy(coordonate[i][1] - 5, coordonate[i][2] - 5, c);
                }
            }
            // Desenează linia nouă
            setcolor(textculoare);
            deseneaza_muchieOR(x1, y1, mx, my);
            mx_old = mx;
            my_old = my;
        }

        if(ismouseclick(WM_LBUTTONDOWN)) // verifica ca la click sa fie nodul 2
        {
            getmouseclick(WM_LBUTTONDOWN, x2, y2);
            setcolor(culoare);
            deseneaza_muchieOR(x1, y1, x2, y2);
            setcolor(textculoare);
            for(int i = 1; i <= n; i++)
            {
                int dx = mx - coordonate[i][1];
                int dy = my - coordonate[i][2];
                int dist = dx*dx + dy*dy;
                if(dist < raza*raza * 9)
                {
                    circle(coordonate[i][1], coordonate[i][2], raza);
                    char c[5];
                    itoa(i, c, 10);
                    outtextxy(coordonate[i][1] - 5, coordonate[i][2] - 5, c);
                }
            }

            nod2 = gaseste_nod(x2, y2);
            if(nod1 == nod2)
            {
                cleardevice();
                deseneaza_totOR();
                return;
            }
        }
    }

    vf++;
    tipop[vf]=1;
    nodm[vf][1]=nod1;
    nodm[vf][2]=nod2;
    x2 = coordonate[nod2][1];
    y2 = coordonate[nod2][2];

    muchii[nod1][nod2] = 1;
    cleardevice();
    deseneaza_totOR();

}
void deseneaza_muchiiOR()
{
    setcolor(textculoare);
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(muchii[i][j])
            {
                int x1 = coordonate[i][1];
                int y1 = coordonate[i][2];
                int x2 = coordonate[j][1];
                int y2 = coordonate[j][2];
                deseneaza_muchieOR(x1, y1, x2, y2);
            }
        }
    }
}
void deseneaza_muchieOR(int x1, int y1, int x2, int y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dist = sqrt(dx*dx + dy*dy);

    if (dist == 0)
        return;

    int xs = x1 + dx * raza / dist;
    int ys = y1 + dy * raza / dist;

    int xe = x2 - dx * raza / dist;
    int ye = y2 - dy * raza / dist;

    line(xs, ys, xe, ye);

    /* sageata */
    double ang = atan2(ye - ys, xe - xs);
    int L = 10;

    line(xe, ye,
         xe - L * cos(ang - M_PI / 6),
         ye - L * sin(ang - M_PI / 6));

    line(xe, ye,
         xe - L * cos(ang + M_PI / 6),
         ye - L * sin(ang + M_PI / 6));
}
int tempWindowCost()
{
    int pw = 300, ph = 150;//lungime latime
    int px = w/2 - pw/2;//pozitionare mijloc ecran
    int py = h/2 - ph/2;


    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    // fereastra
    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(WHITE);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Introdu cost:");
    //outtextxy(px+20, py+110, "[ ENTER = OK ]");

    char nr[10] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13)
            break;//enter
        if (c == 8 && lg > 0)//backspace
            nr[--lg] = 0;
        else if (c >= '0' && c <= '9' && lg < 9)
        {
            nr[lg++] = c;
            nr[lg] = 0;
        }


        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+60, px+pw-20, py+90);
        outtextxy(px+20, py+60, nr);//Desenează din nou ce s-a tastat,se face la fiecare tastă
    }

    // stergere fereastra
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_tot();

    return atoi(nr);
}
int tempWindowCostOR()
{
    int pw = 300, ph = 150;//lungime latime
    int px = w/2 - pw/2;//pozitionare mijloc ecran
    int py = h/2 - ph/2;


    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    //fereastra
    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(WHITE);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Introdu cost:");
    //outtextxy(px+20, py+110, "[ ENTER = OK ]");

    char nr[10] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13)
            break;//enter
        if (c == 8 && lg > 0)//backspace
            nr[--lg] = 0;
        else if (c >= '0' && c <= '9' && lg < 9)
        {
            nr[lg++] = c;
            nr[lg] = 0;
        }


        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+60, px+pw-20, py+90);
        outtextxy(px+20, py+60, nr);//Desenează din nou ce s-a tastat,se face la fiecare tastă
    }

    // stergere fereastra
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_totOR();

    return atoi(nr);
}
int poate_plasa_nod(int x, int y)
{
    for( int i = 1 ; i <= n ; i++)
    {
        int dx = x - coordonate[i][1];
        int dy = y - coordonate[i][2];
        if ( dx * dx + dy * dy < 40*40)
            return 0;
    }
    return 1;
}
void deseneaza_costuri()
{
    for(int i=1; i<n; i++)
    {
        for(int j = i + 1; j <= n; j++)
        {
            if(exista_cost[i][j] && i!=j)
            {
                if(i < j)
                    deseneaza_cost_cu_muchie(coordonate[i][1], coordonate[i][2], coordonate[j][1], coordonate[j][2], costuri[i][j]);
            }
        }
    }
}
void deseneaza_cost_cu_muchie(int x1, int y1, int x2, int y2, int cost)
{
    setcolor(textculoare);
    int x_mijloc = (x1 + x2) / 2;
    int y_mijloc = (y1 + y2) / 2;
    setfillstyle(SOLID_FILL,culoare);
    setcolor(culoare);
    int text_width = textwidth("0000");
    int text_height = textheight("0");
    bar(x_mijloc - text_width/2 - 2,
        y_mijloc - text_height/2 - 2,
        x_mijloc + text_width/2 + 2,
        y_mijloc + text_height/2 + 2);

    setcolor(textculoare);
    char c[10];
    itoa(cost, c, 10);
    settextstyle(font, HORIZ_DIR, marimef);
    outtextxy(x_mijloc - textwidth(c)/2, y_mijloc - textheight(c)/2, c);

    settextstyle(font, HORIZ_DIR,marimef);
}
void deseneaza_tot()
{
    setcolor(culoare);
    setfillstyle(SOLID_FILL, culoare);
    deseneaza_meniu();
    deseneaza_noduri();
    deseneaza_muchii();
    deseneaza_costuri();
}
void deseneaza_totOR()
{
    setcolor(culoare);
    setfillstyle(SOLID_FILL, culoare);
    meniu_orientat();
    deseneaza_noduri();
    deseneaza_muchiiOR();
    deseneaza_costuriOR();
}
void deseneaza_noduri()
{
    setcolor(textculoare);
    setfillstyle(SOLID_FILL, culoare);

    for(int i = 1; i <= n; i++)
    {
        int x = coordonate[i][1];
        int y = coordonate[i][2];

        //șterge zona nodului (fundal)
        bar(x - raza - 5, y - raza - 5,
            x + raza + 5, y + raza + 5);

        //redesenează nodul
        circle(x, y, raza);

        char c[5];
        itoa(i, c, 10);
        outtextxy(x - 5, y - 5, c);
    }
}

int verif(int vizitat[], int n)
{
    for(int i = 1; i <= n; i++)
        if (vizitat[i] == 0)
            return 0;
    return 1;
}
void dijkstra(int s)
{
    int vizitat[101], predecesor[101], distanta[101];
    int i, j;

    for(i = 1; i <= n; i++)
    {
        vizitat[i] = 0;
        distanta[i] = INF;
        predecesor[i] = -1;
    }

    vizitat[s] = 1;
    distanta[s] = 0;
    predecesor[s] = -1;

    for(i = 1; i <= n; i++)
    {
        if(i != s && muchii[s][i])
        {
            if(exista_cost[s][i])
                distanta[i] = costuri[s][i];
            else
                distanta[i] = 1;

            predecesor[i] = s;
        }
    }

    int vizitate = 1;
    while(vizitate < n)
    {
        int j_star = -1;
        int min_dist = INF;

        for(j = 1; j <= n; j++)
        {
            if(!vizitat[j] && distanta[j] < min_dist)
            {
                min_dist = distanta[j];
                j_star = j;
            }
        }

        if(j_star == -1)
            break;

        vizitat[j_star] = 1;
        vizitate++;

        for(j = 1; j <= n; j++)
        {
            if(!vizitat[j] && muchii[j_star][j])
            {
                int cost;
                if(exista_cost[j_star][j])
                    cost = costuri[j_star][j];
                else
                    cost = 1;

                if(distanta[j] > distanta[j_star] + cost)
                {
                    distanta[j] = distanta[j_star] + cost;
                    predecesor[j] = j_star;
                }
            }
        }
    }

    char text[500];
    char temp[50];

    sprintf(text, "Dijkstra - Sursa: %d", s);
    afiseaza_mesaj(text);

    strcpy(text, "Distante: ");

    for(i = 1; i <= n; i++)
    {
        if(i > 1)
            strcat(text, ", ");

        if(distanta[i] == INF)
            sprintf(temp, "%d:inf", i);
        else
            sprintf(temp, "%d:%d", i, distanta[i]);

        strcat(text, temp);
    }

    afiseaza_mesaj(text);
}
void dijkstraOR(int s)
{
    int vizitat[101], predecesor[101], distanta[101];
    int i, j;

    for(i = 1; i <= n; i++)
    {
        vizitat[i] = 0;
        distanta[i] = INF;
        predecesor[i] = -1;
    }

    vizitat[s] = 1;
    distanta[s] = 0;
    predecesor[s] = -1;

    for(i = 1; i <= n; i++)
    {
        if(i != s && muchii[s][i])
        {
            if(exista_cost[s][i])
                distanta[i] = costuri[s][i];
            else
                distanta[i] = 1;

            predecesor[i] = s;
        }
    }

    int vizitate = 1;
    while(vizitate < n)
    {
        int j_star = -1;
        int min_dist = INF;

        for(j = 1; j <= n; j++)
        {
            if(!vizitat[j] && distanta[j] < min_dist)
            {
                min_dist = distanta[j];
                j_star = j;
            }
        }

        if(j_star == -1)
            break;

        vizitat[j_star] = 1;
        vizitate++;

        for(j = 1; j <= n; j++)
        {
            if(!vizitat[j] && muchii[j_star][j])
            {
                int cost;
                if(exista_cost[j_star][j])
                    cost = costuri[j_star][j];
                else
                    cost = 1;

                if(distanta[j] > distanta[j_star] + cost)
                {
                    distanta[j] = distanta[j_star] + cost;
                    predecesor[j] = j_star;
                }
            }
        }
    }

    char text[500];
    char temp[50];

    sprintf(text, "Dijkstra - Sursa: %d", s);
    afiseaza_mesaj(text);


    strcpy(text, "Distante: ");

    for(i = 1; i <= n; i++)
    {
        if(i > 1)
            strcat(text, ", ");

        if(distanta[i] == INF)
            sprintf(temp, "%d:inf", i);
        else
            sprintf(temp, "%d:%d", i, distanta[i]);

        strcat(text, temp);
    }

    afiseaza_mesaj(text);
}


void creeaza_meniu_principal()
{
    setcolor(textculoare);
    setlinestyle(DASHED_LINE,1,1);
    setbkcolor(culoare);
    cleardevice();

    settextstyle(EUROPEAN_FONT, HORIZ_DIR,8);
    outtextxy(w/2-textwidth("Algoritmica")/2,h/4-(textheight("Algoritmica")+textheight("grafurilor")+10)/2,"Algoritmica");
    outtextxy(w/2-textwidth("grafurilor")/2,h/4-(textheight("Algoritmica")+textheight("grafurilor")+10)/2+10+textheight("Algoritmica"),"grafurilor ");

    settextstyle(TRIPLEX_FONT,0,2);//face primul buton, pentru grafuri neorientate

    rectangle(leftb-15,topb-25,rightb+15,bottomb);
    outtextxy(w/2-textwidth("GRAF NEORIENTAT")/2,(topb+bottomb-25)/2-textheight("G")/2,"GRAF NEORIENTAT");

    rectangle(leftb-15,topb-150,rightb+15,bottomb-125);//buton pentru grafuri orientate
    outtextxy(w/2-textwidth("GRAF ORIENTAT")/2,(topb+bottomb-275)/2-textheight("G")/2,"GRAF ORIENTAT");

    rectangle(75,0,280,75);
    outtextxy_centrat(75, 0, 280, 75, "Meniu",marimef);

    setlinestyle(USERBIT_LINE,0xFF00,1);
    line(75,0,75,h);
    line(0,75,w,75);
    line(w-75,0,w-75,h);
    line(0,h-75,w,h-75);

    setlinestyle(SOLID_LINE,1,1);
}
void creare_alg_neorientat()
{
    rectangle(190, 85, 310, 120);
    outtextxy_centrat(190, 85, 310, 120, "BFS", marimef);

    rectangle(190,40, 310, 75);
    outtextxy_centrat(190,40, 310, 75, "DFS", marimef);

    rectangle(190, 130, 310, 165);
    outtextxy_centrat(190, 130, 310, 165, "Prim", marimef);

    rectangle(190, 175,310, 210);
    outtextxy_centrat(190, 175,310, 210, "Dijkstra", marimef);

    rectangle(190, 220, 310, 255);
    outtextxy_centrat(190, 220, 310, 255, "Bellman", marimef);

    rectangle(190, 265, 310, 300);
    outtextxy_centrat(190, 265, 310, 300, "Floyd", marimef);

    rectangle(190,310, 310, 345);
    outtextxy_centrat(190,310, 310, 345, "Eulerian", marimef);

    rectangle(190, 355, 310, 390);
    outtextxy_centrat(190, 355, 310, 390, "Hamiltonian", marimef);
}

void creare_alg_orientat()
{

    rectangle(190, 85, 310, 120);
    outtextxy_centrat(190, 85, 310, 120, "BFS", marimef);

    rectangle(190,40, 310, 75);
    outtextxy_centrat(190,40, 310, 75, "DFS", marimef);

    rectangle(190, 130, 310, 165);
    outtextxy_centrat(190, 130, 310, 165, "Dijkstra", marimef);

    rectangle(190, 175,310, 210);
    outtextxy_centrat(190, 175,310, 210, "Bellman", marimef);

    rectangle(190, 220, 310, 255);
    outtextxy_centrat(190, 220, 310, 255, "Floyd", marimef);
}
void buton_alg_orientat()
{
    creare_alg_orientat();
    bool continua = true;

    while(continua)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            // Verifică dacă s-a apăsat din nou pe butonul "Algoritmi" pentru a închide meniul
            if(x > 20 && x < 150 && y > 245 && y < 280)
            {
                continua = false;
            }
            else if(x > 190 && x < 310 && y > 85 && y < 120) // BFS
            {
                bfs_orientat();
            }
            else if(x > 190 && x < 310 && y > 40 && y < 75) // DFS
            {
                dfs_orientat();
            }
            else if(x > 190 && x < 310 && y > 130 && y < 165) // Dijkstra
            {
                afiseaza_mesaj("Selecteaza nodul sursa...");

                int x, y;
                int sursa = 0;
                while(sursa == 0)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        sursa = gaseste_nod(x, y);
                    }
                }

                if(sursa != 0)
                {
                    dijkstraOR(sursa);
                }
            }
            else if(x > 190 && x < 310 && y > 175 && y < 210) // Bellman
            {
                bellmanFordOR();
            }
            else if(x > 190 && x < 310 && y > 220 && y < 255) // Floyd
            {
                floydWarshall();
            }
        }

        delay(10);
    }

    // Șterge meniul de algoritmi complet și redesenează tot
    setfillstyle(SOLID_FILL, culoare);
    bar(185,35, 445, 400); // Șterge zona pentru graful orientat
    deseneaza_totOR();
}
void deseneaza_meniu()
{
    setcolor(textculoare);
    setlinestyle(DOTTED_LINE,1,1);
    line (175,0,175,h);
    line (w-170,0,w-170,h);
    line (0,h-330,w,h-330);
    outtextxy(180,h-325,"Afisare");
    line(175,h-300,w-170,h-300);

    setlinestyle(SOLID_LINE,0,1);
    settextstyle(font, HORIZ_DIR, marimef);

    rectangle(20,35, 150, 70);
    outtextxy_centrat(20, 35, 150, 70, "Nod",marimef);

    rectangle(20, 105, 150, 140);
    outtextxy_centrat(20, 105, 150, 140, "Muchie",marimef);

    rectangle(20,175,150,210);
    outtextxy_centrat(20, 175, 150, 210, "Cost",marimef);

    rectangle(20,245,150,280);
    outtextxy_centrat(20, 245, 150, 280, "Algoritmi",marimef);

    rectangle(w-160,100,w-20,145);
    outtextxy_centrat(w-160, 100, w-20, 145, "Mutare nod",marimef);

    rectangle(w-160,170,w-20,205);
    outtextxy_centrat(w-160, 170, w-20, 205, "Pagina noua",marimef);

    rectangle(w-160,240,w-20,275);
    outtextxy_centrat(w-160, 240, w-20, 275, "Undo",marimef);

    rectangle(w-160,310,w-20,345);
    outtextxy_centrat(w-160,310,w-20,345,"Save",marimef);

    rectangle(w-160,380,w-20,415);
    outtextxy_centrat(w-160,380,w-20,415,"Upload",marimef);

    settextstyle(font, HORIZ_DIR, marimef);

    rectangle(20,h-100,150,h-50);
    outtextxy_centrat(20, h-100, 150, h-50, "BACK",marimef);
}
void meniu_orientat()
{
    setcolor(textculoare);
    setlinestyle(DOTTED_LINE,1,1);
    line (175,0,175,h);
    line (w-170,0,w-170,h);
    line (0,h-330,w,h-330);
    outtextxy(180,h-325,"Afisare");
    line(175,h-300,w-170,h-300);

    setlinestyle(SOLID_LINE,0,1);
    settextstyle(font, HORIZ_DIR,marimef);

    rectangle(20,35, 150, 70);
    outtextxy_centrat(20, 35, 150, 70, "Nod",marimef);

    rectangle(20, 105, 150, 140);
    outtextxy_centrat(20, 105, 150, 140, "Arc",marimef);

    rectangle(20,175,150,210);
    outtextxy_centrat(20, 175, 150, 210, "Cost",marimef);

    rectangle(20,245,150,280);
    outtextxy_centrat(20, 245, 150, 280, "Algoritmi",marimef);

    rectangle(w-160,100,w-20,145);
    outtextxy_centrat(w-160, 100, w-20, 145, "Mutare nod",marimef);

    rectangle(w-160,170,w-20,205);
    outtextxy_centrat(w-160, 170, w-20, 205, "Pagina noua",marimef);

    rectangle(w-160,240,w-20,275);
    outtextxy_centrat(w-160, 240, w-20, 275, "Undo",marimef);

    rectangle(w-160,310,w-20,345);
    outtextxy_centrat(w-160,310,w-20,345,"Save",marimef);

    rectangle(w-160,380,w-20,415);
    outtextxy_centrat(w-160,380,w-20,415,"Upload",marimef);

    settextstyle(font, HORIZ_DIR,marimef);

    rectangle(20,h-100,150,h-50);
    outtextxy_centrat(20, h-100, 150, h-50, "BACK",marimef);
}
void creeazaFereastra(int x1, int yy1, int x2, int y2, char* titlu)
{
    setbkcolor(BLACK);
    //chenar
    setcolor(BLACK);
    rectangle(x1, yy1, x2, y2);
    rectangle(x1+2, yy1+2, x2-2, y2-2);

    //titlu
    setfillstyle(SOLID_FILL, BLACK);
    bar(x1+3, yy1+3, x2-3, yy1+25);

    // Text titlu
    setcolor(WHITE);
    outtextxy(x1+10, yy1+10, titlu);


    // Fundal fereastră
    setfillstyle(SOLID_FILL,BLACK);
    bar(x1+3, yy1+26, x2-3, y2-3);

    setcolor(WHITE);
    line(x1,yy1+30,x2,yy1+30);

    rectangle(x2-50,yy1,x2,yy1+30);
    outtextxy(x2-35,yy1+5,"X");

    rectangle(x1,yy1+50,x1+125,yy1+85);
    outtextxy(x1+15,yy1+60,"Culori");

    rectangle(x1,yy1+100,x1+125,yy1+135);
    outtextxy(x1+31,yy1+105,"Font");
}
void culori_m()
{
    settextstyle(DEFAULT_FONT,HORIZ_DIR,0);

    setcolor(WHITE);
    rectangle(x1+175,yy1+50,x1+235,yy1+85);
    setcolor(BLUE);
    outtextxy(x1+188,yy1+60,"BLUE");

    setcolor(WHITE);
    rectangle(x1+265,yy1+50,x1+325,yy1+85);
    setcolor(GREEN);
    outtextxy(x1+272,yy1+58,"GREEN");

    setcolor(WHITE);
    rectangle(x1+365,yy1+50,x1+425,yy1+85);
    setcolor(RED);
    outtextxy(x1+380,yy1+58,"RED");

    setcolor(WHITE);
    rectangle(x1+455,yy1+50,x1+532,yy1+85);
    setcolor(MAGENTA);
    outtextxy(x1+458,yy1+58,"MAGENTA");

    setcolor(WHITE);
    rectangle(x1+175,yy1+100,x1+275,yy1+135);
    setcolor(LIGHTGRAY);
    outtextxy(x1+179,yy1+110,"LIGHTGRAY");

    setcolor(WHITE);
    rectangle(x1+305,yy1+100,x1+405,yy1+135);
    setcolor(LIGHTBLUE);
    outtextxy(x1+308,yy1+110,"LIGHTBLUE");

    setcolor(WHITE);
    rectangle(x1+435,yy1+100,x1+539,yy1+135);
    setcolor(LIGHTGREEN);
    outtextxy(x1+438,yy1+110,"LIGHTGREEN");

    setcolor(WHITE);
    rectangle(x1+25,yy1+150,x1+125,yy1+180);
    setcolor(LIGHTRED);
    outtextxy(x1+31,yy1+157,"LIGHTRED");

    setcolor(WHITE);
    rectangle(x1+155,yy1+150,x1+285,yy1+180);
    setcolor(LIGHTMAGENTA);
    outtextxy(x1+161,yy1+157,"LIGHTMAGENTA");

    setcolor(WHITE);
    rectangle(x1+315,yy1+150,x1+415,yy1+180);
    setcolor(DARKGRAY);
    outtextxy(x1+323,yy1+157,"DARKGRAY");

    setcolor(WHITE);
    rectangle(x1+445,yy1+150,x1+520,yy1+180);
    setcolor(YELLOW);
    outtextxy(x1+452,yy1+157,"YELLOW");

    setcolor(WHITE);
    rectangle(x1+75,yy1+200,x1+135,yy1+230);
    outtextxy(x1+79,yy1+210,"WHITE");

    setcolor(WHITE);
    rectangle(x1+165,yy1+200,x1+225,yy1+230);
    outtextxy(x1+172,yy1+210,"BLACK");
}
void schimba_culoare()
{
    bool click=false;
    while(!click)
    {
        int x,y;
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(x>x1+175 && x<x1+235 && y>yy1+50 && y<yy1+85)
            {
                culoare=BLUE;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+265 && x<x1+325 && y>yy1+50 && y<yy1+85)
            {
                culoare=GREEN;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+365 && x<x1+425 && y>yy1+50 && y<yy1+85)
            {
                culoare=RED;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+455 && x<x1+532 && y>yy1+50 && y<yy1+85)
            {
                culoare=MAGENTA;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+275 && y>yy1+100 && y<yy1+135)
            {
                culoare=LIGHTGRAY;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+305 && x<x1+405 && y>yy1+100 && y<yy1+135)
            {
                culoare=LIGHTBLUE;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+435 && x<x1+539 && y>yy1+100 && y<yy1+135)
            {
                culoare=LIGHTGREEN;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+25 && x<x1+125 && y>yy1+150 && y<yy1+180)
            {
                culoare=LIGHTRED;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+155 && x<x1+285 && y>yy1+150 && y<yy1+180)
            {
                culoare=LIGHTMAGENTA;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+315 && x<x1+415 && y>yy1+150 && y<yy1+180)
            {
                culoare=DARKGRAY;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+445 && x<x1+520 && y>yy1+150 && y<yy1+180)
            {
                culoare=YELLOW;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+75 && x<x1+135 && y>yy1+200 && y<yy1+230)
            {
                culoare=WHITE;
                textculoare=BLACK;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+165 && x<x1+225 && y>yy1+200 && y<yy1+230)
            {
                culoare=BLACK;
                textculoare=WHITE;
                Algoritmica_grafurilor();
                click=true;
            }
            else if (x> x2-50 && y>yy1 && x<x2 && y<yy1+30)
            {
                Algoritmica_grafurilor();
                click=true;
            }
        }
    }
}
void incarca_graf()
{
    // Cerere nume fișier de la utilizator
    int pw = 400, ph = 200;
    int px = w/2 - pw/2;
    int py = h/2 - ph/2;

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(textculoare);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Nume fisier (fara .txt):");

    char nume_fisier[50] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13) // Enter
            break;
        if (c == 8 && lg > 0) // Backspace
            nume_fisier[--lg] = 0;
        else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '-') && lg < 45)
        {
            nume_fisier[lg++] = c;
            nume_fisier[lg] = 0;
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+70, px+pw-20, py+100);
        outtextxy(px+20, py+70, nume_fisier);
    }

    // Adaugă extensia .txt
    strcat(nume_fisier, ".txt");

    // Încărcare din fișier
    ifstream fin(nume_fisier);

    if (!fin)
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "Fisier inexistent!");
        delay(2000);

        // Șterge fereastra
        setfillstyle(SOLID_FILL, culoare);
        bar(px-5, py-5, px+pw+5, py+ph+5);
        deseneaza_tot();
        return;
    }

    // Resetează graful curent
    n = 0;
    vf = 0;
    for(int i = 0; i <= 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            muchii[i][j] = 0;
            costuri[i][j] = 0;
            exista_cost[i][j] = 0;
        }
        coordonate[i][1] = 0;
        coordonate[i][2] = 0;
    }

    // Citește numărul de noduri
    fin >> n;

    // Citește coordonatele nodurilor
    for(int i = 1; i <= n; i++)
    {
        fin >> coordonate[i][1] >> coordonate[i][2];

        // Adaugă în historicul de operații
        vf++;
        unod[vf][1] = coordonate[i][1];
        unod[vf][2] = coordonate[i][2];
        tipop[vf] = 2;
    }

    // Citește muchiile și costurile
    int nod1, nod2, cost;
    while(fin >> nod1 >> nod2 >> cost)
    {
        muchii[nod1][nod2] = 1;
        muchii[nod2][nod1] = 1;

        vf++;
        tipop[vf] = 1;
        nodm[vf][1] = nod1;
        nodm[vf][2] = nod2;

        if(cost > 0)
        {
            costuri[nod1][nod2] = cost;
            costuri[nod2][nod1] = cost;
            exista_cost[nod1][nod2] = 1;
            exista_cost[nod2][nod1] = 1;

            vf++;
            tipop[vf] = 3;
            costn[vf][1] = nod1;
            costn[vf][2] = nod2;
        }
    }

    fin.close();

    // Mesaj de succes
    setfillstyle(SOLID_FILL, BLACK);
    bar(px+20, py+120, px+pw-20, py+150);
    outtextxy(px+20, py+120, "Incarcat cu succes!");
    delay(2000);

    // Șterge fereastra și redesenează graful
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    cleardevice();
    deseneaza_tot();
}

void incarca_graf_orientat()
{
    // Cerere nume fișier de la utilizator
    //creeaza fereastra de fisier
    int pw = 400, ph = 200;
    int px = w/2 - pw/2;
    int py = h/2 - ph/2;

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(textculoare);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Nume fisier (fara .txt):");

    char nume_fisier[50] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13) // Enter
            break;
        if (c == 8 && lg > 0) // Backspace
            nume_fisier[--lg] = 0;
        else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '-') && lg < 45)
        {
            nume_fisier[lg++] = c;
            nume_fisier[lg] = 0;
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+70, px+pw-20, py+100);
        outtextxy(px+20, py+70, nume_fisier);
    }

    strcat(nume_fisier, ".txt");

    ifstream fin(nume_fisier);

    if (!fin)
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "Fisier inexistent!");
        delay(2000);

        setfillstyle(SOLID_FILL, culoare);
        bar(px-5, py-5, px+pw+5, py+ph+5);
        deseneaza_totOR();
        return;
    }

    // Resetează graful
    n = 0;
    vf = 0;
    for(int i = 0; i <= 100; i++)
    {
        for(int j = 0; j <= 100; j++)
        {
            muchii[i][j] = 0;
            costuri[i][j] = 0;
            exista_cost[i][j] = 0;
        }
        coordonate[i][1] = 0;
        coordonate[i][2] = 0;
    }

    // Citește numărul de noduri
    fin >> n;

    // Citește coordonatele nodurilor
    for(int i = 1; i <= n; i++)
    {
        fin >> coordonate[i][1] >> coordonate[i][2];

        vf++;
        unod[vf][1] = coordonate[i][1];
        unod[vf][2] = coordonate[i][2];
        tipop[vf] = 2;
    }

    // Citește arcele și costurile (doar într-o direcție pentru graf orientat)
    int nod1, nod2, cost;
    while(fin >> nod1 >> nod2 >> cost)
    {
        muchii[nod1][nod2] = 1; // Doar într-o direcție!

        vf++;
        tipop[vf] = 1;
        nodm[vf][1] = nod1;
        nodm[vf][2] = nod2;

        if(cost > 0)
        {
            costuri[nod1][nod2] = cost;
            exista_cost[nod1][nod2] = 1;

            vf++;
            tipop[vf] = 3;
            costn[vf][1] = nod1;
            costn[vf][2] = nod2;
        }
    }

    fin.close();

    setfillstyle(SOLID_FILL, BLACK);
    bar(px+20, py+120, px+pw-20, py+150);
    outtextxy(px+20, py+120, "Incarcat cu succes!");
    delay(2000);

    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    cleardevice();
    deseneaza_totOR();
}
void salveaza_graf()
{
    // Cerere nume fișier de la utilizator
    int pw = 400, ph = 200;
    int px = w/2 - pw/2;
    int py = h/2 - ph/2;

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(textculoare);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Nume fisier (fara .txt):");

    char nume_fisier[50] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13) // Enter
            break;
        if (c == 8 && lg > 0) // Backspace
            nume_fisier[--lg] = 0;
        else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '-') && lg < 45)
        {
            nume_fisier[lg++] = c;
            nume_fisier[lg] = 0;
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+70, px+pw-20, py+100);
        outtextxy(px+20, py+70, nume_fisier);
    }

    // Adaugă extensia .txt
    strcat(nume_fisier, ".txt");

    // Salvare în fișier
    ofstream fout(nume_fisier);

    if (!fout)
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "EROARE la salvare!");
        delay(2000);
    }
    else
    {
        // Salvează numărul de noduri
        fout << n << endl;

        // Salvează coordonatele nodurilor
        for(int i = 1; i <= n; i++)
        {
            fout << coordonate[i][1] << " " << coordonate[i][2] << endl;
        }

        // Salvează muchiile și costurile
        for(int i = 1; i <= n; i++)
        {
            for(int j = i; j <= n; j++) // j = i pentru a evita duplicatele în grafuri neorientate
            {
                if(muchii[i][j])
                {
                    fout << i << " " << j << " ";
                    if(exista_cost[i][j])
                        fout << costuri[i][j] << endl;
                    else
                        fout << "0" << endl; // 0 = fără cost
                }
            }
        }

        fout.close();

        setfillstyle(SOLID_FILL,textculoare);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "Salvat cu succes!");
        delay(2000);
    }

    // Șterge fereastra
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_tot();
}

// Pentru graf orientat
void salveaza_graf_orientat()
{
    int pw = 400, ph = 200;
    int px = w/2 - pw/2;
    int py = h/2 - ph/2;

    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(textculoare);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Nume fisier (fara .txt):");

    char nume_fisier[50] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13)
            break;
        if (c == 8 && lg > 0)
            nume_fisier[--lg] = 0;
        else if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '-') && lg < 45)
        {
            nume_fisier[lg++] = c;
            nume_fisier[lg] = 0;
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+70, px+pw-20, py+100);
        outtextxy(px+20, py+70, nume_fisier);
    }

    strcat(nume_fisier, ".txt");

    ofstream fout(nume_fisier);

    if (!fout)
    {
        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "EROARE la salvare!");
        delay(2000);
    }
    else
    {
        fout << n << endl;

        for(int i = 1; i <= n; i++)
        {
            fout << coordonate[i][1] << " " << coordonate[i][2] << endl;
        }

        // Pentru graf orientat, salvează toate arcele (nu doar i <= j)
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(muchii[i][j])
                {
                    fout << i << " " << j << " ";
                    if(exista_cost[i][j])
                        fout << costuri[i][j] << endl;
                    else
                        fout << "0" << endl;
                }
            }
        }

        fout.close();

        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+120, px+pw-20, py+150);
        outtextxy(px+20, py+120, "Salvat cu succes!");
        delay(2000);
    }

    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_totOR();
}
void fonturi()
{
    setcolor(WHITE);

    rectangle(x1+175,yy1+50,x1+278,yy1+85);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    outtextxy(x1+178,yy1+61,"DEFAULT");

    rectangle(x1+308,yy1+50,x1+435,yy1+85);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
    outtextxy(x1+311,yy1+61,"TRIPLEX");

    rectangle(x1+175,yy1+100,x1+275,yy1+135);
    settextstyle(SMALL_FONT,HORIZ_DIR,8);
    outtextxy(x1+179,yy1+110,"SMALL");

    rectangle(x1+305,yy1+100,x1+435,yy1+135);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
    outtextxy(x1+308,yy1+110,"SANS_SERIF");

    rectangle(x1+175,yy1+150,x1+300,yy1+180);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,2);
    outtextxy(x1+178,yy1+157,"GOTHIC");

    rectangle(x1+330,yy1+150,x1+430,yy1+180);
    settextstyle(SCRIPT_FONT,HORIZ_DIR,2);
    outtextxy(x1+333,yy1+157,"SCRIPT");

    rectangle(x1+175,yy1+195,x1+310,yy1+225);
    settextstyle(SIMPLEX_FONT,HORIZ_DIR,2);
    outtextxy(x1+178,yy1+198,"SIMPLEX");

    rectangle(x1+340,yy1+195,x1+470,yy1+225);
    settextstyle(TRIPLEX_SCR_FONT,HORIZ_DIR,2);
    outtextxy(x1+342,yy1+198,"TRIPLEX");

    rectangle(x1+175,yy1+240,x1+275,yy1+270);
    settextstyle(COMPLEX_FONT,HORIZ_DIR,2);
    outtextxy(x1+182,yy1+242,"COMPLEX");

    rectangle(x1+305,yy1+240,x1+475,yy1+270);
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
    outtextxy(x1+308,yy1+242,"EUROPEAN");

    rectangle(x1+175,yy1+285,x1+275,yy1+315);
    settextstyle(BOLD_FONT,HORIZ_DIR,3);
    outtextxy(x1+196,yy1+287,"BOLD");
}
void schimba_font()
{
    bool click=false;
    while(!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(x>x1+175 && x<x1+278 && y>yy1+50 && y<yy1+85)
            {
                font=DEFAULT_FONT;
                marimef=0.6;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+308 && x<x1+435 && y>yy1+50 && y<yy1+85)
            {
                font=TRIPLEX_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+275 && y>yy1+100 && y<yy1+135)
            {
                font=SMALL_FONT;
                marimef=8;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+305 && x<x1+435 && y>yy1+100 && y<yy1+135)
            {
                font=SANS_SERIF_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+300 && y>yy1+150 && y<yy1+180)
            {
                font=GOTHIC_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+330 && x<x1+430 && y>yy1+150 && y<yy1+180)
            {
                font=SCRIPT_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+310 && y>yy1+195 && y<yy1+225)
            {
                font=SIMPLEX_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+340 && x<x1+470 && y>yy1+195 && y<yy1+225)
            {
                font=TRIPLEX_SCR_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+275 && y>yy1+240 && y<yy1+270)
            {
                font=COMPLEX_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+305 && x<x1+475 && y>yy1+240 && y<yy1+270)
            {
                font=EUROPEAN_FONT;
                marimef=1;
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1+175 && x<x1+275 && y>yy1+285 && y<yy1+315)
            {
                font=BOLD_FONT;
                marimef=2;
                Algoritmica_grafurilor();
                click=true;
            }
            else if (x> x2-50 && y>yy1 && x<x2 && y<yy1+30)
            {
                Algoritmica_grafurilor();
                click=true;
            }
        }
    }
}
void modif_meniu()
{
    creeazaFereastra(x1, yy1, x2, y2, "MENIU");
    bool click=false;
    while(!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            if(x>x2-50 && x<x2 && x>yy1 && x>yy1+30)
            {
                Algoritmica_grafurilor();
                click=true;
            }
            else if(x>x1 && x<x1+125 && y>yy1+50 && y<yy1+85)
            {
                culori_m();
                schimba_culoare();
            }
            else if(x>x1 && y>yy1+100 && x<x1+125 && y<yy1+135)
            {
                fonturi();
                schimba_font();
            }
        }
    }
}
void outtextxy_centrat(int x1, int y1, int x2, int y2, char* text,int size_font)
{
    settextstyle(font, HORIZ_DIR, size_font);

    // x1, y1, x2, y2-coordonatele dreptunghiului
    int centruX = (x1 + x2) / 2;
    int centruY = (y1 + y2) / 2;

    int textW = textwidth(text);
    int textH = textheight(text);

    outtextxy(centruX - textW / 2, centruY - textH / 2, text);
}
// Funcție pentru a verifica dacă graful este conex
bool este_conex()
{
    if(n == 0)
        return true;

    bool vizitat[101] = {false};
    Coada* q = coadaGoala();

    vizitat[1] = true;
    insereazaCoada(q, 1);
    int noduri_vizitate = 1;

    while(!esteCoadaGoala(q))
    {
        int curent = citesteNodCoada(q);
        eliminaNodCoada(q);

        for(int i = 1; i <= n; i++)
        {
            if((muchii[curent][i] || muchii[i][curent]) && !vizitat[i])
            {
                vizitat[i] = true;
                insereazaCoada(q, i);
                noduri_vizitate++;
            }
        }
    }

    return noduri_vizitate == n;
}

// Funcție pentru a verifica dacă graful este eulerian
bool este_graf_eulerian()
{
    if(n == 0)
        return false;

    // Verifică conexitatea
    if(!este_conex())
    {
        afiseaza_mesaj("Graful nu este conex!");
        return false;
    }

    // Numără nodurile cu grad impar
    int noduri_grad_impar = 0;

    for(int i = 1; i <= n; i++)
    {
        int grad = 0;
        for(int j = 1; j <= n; j++)
        {
            if(muchii[i][j] || muchii[j][i])
                grad++;
        }

        if(grad % 2 == 1)
            noduri_grad_impar++;
    }

    // Graf eulerian: toate nodurile au grad par
    if(noduri_grad_impar == 0)
    {
        afiseaza_mesaj("Graf EULERIAN");
        afiseaza_mesaj("(Exista ciclu eulerian)");
        return true;
    }
    // Graf semi-eulerian: exact 2 noduri cu grad impar
    else if(noduri_grad_impar == 2)
    {
        afiseaza_mesaj("Graf SEMI-EULERIAN");
        afiseaza_mesaj("(Exista lant eulerian)");
        return false;
    }
    else
    {
        afiseaza_mesaj("Graf NON-EULERIAN");
        char text[50];
        sprintf(text, "(%d noduri grad impar)", noduri_grad_impar);
        afiseaza_mesaj(text);
        return false;
    }
}

// Backtracking pentru ciclul hamiltonian
bool hamiltonian_backtracking(int pos, int drum[], bool vizitat[])
{
    // Dacă am vizitat toate nodurile
    if(pos == n)
    {
        // Verifică dacă există muchie de la ultimul nod la primul (ciclu)
        if(muchii[drum[pos-1]][drum[0]] || muchii[drum[0]][drum[pos-1]])
            return true;
        return false;
    }

    // Încearcă toate nodurile nevizitate
    for(int i = 1; i <= n; i++)
    {
        if(!vizitat[i])
        {
            // Verifică dacă există muchie de la nodul anterior la nodul curent
            if(pos == 0 || muchii[drum[pos-1]][i] || muchii[i][drum[pos-1]])
            {
                drum[pos] = i;
                vizitat[i] = true;

                if(hamiltonian_backtracking(pos + 1, drum, vizitat))
                    return true;

                // Backtrack
                vizitat[i] = false;
            }
        }
    }

    return false;
}

// Funcție pentru a verifica dacă graful este hamiltonian
bool este_graf_hamiltonian()
{
    if(n == 0)
        return false;

    // Verifică conexitatea
    if(!este_conex())
    {
        afiseaza_mesaj("Graful nu este conex!");
        afiseaza_mesaj("Graf NON-HAMILTONIAN");
        return false;
    }

    // Pentru grafuri mici (n <= 10), folosește backtracking
    if(n <= 10)
    {
        int drum[101];
        bool vizitat[101] = {false};

        if(hamiltonian_backtracking(0, drum, vizitat))
        {
            afiseaza_mesaj("Graf HAMILTONIAN");
            afiseaza_mesaj("(Exista ciclu hamiltonian)");

            // Vizualizează ciclul
            for(int i = 0; i < n; i++)
            {
                vizualizeaza_nod(drum[i]);
            }
            vizualizeaza_nod(drum[0]); // Revine la primul nod

            return true;
        }
        else
        {
            afiseaza_mesaj("Graf NON-HAMILTONIAN");
            afiseaza_mesaj("(Nu exista ciclu hamiltonian)");
            return false;
        }
    }
    else
    {
        // Pentru grafuri mari, folosește condiția lui Dirac
        // Dacă fiecare nod are gradul >= n/2, atunci graful este hamiltonian
        bool posibil_hamiltonian = true;

        for(int i = 1; i <= n; i++)
        {
            int grad = 0;
            for(int j = 1; j <= n; j++)
            {
                if(muchii[i][j] || muchii[j][i])
                    grad++;
            }

            if(grad < n / 2)
            {
                posibil_hamiltonian = false;
                break;
            }
        }
        if(posibil_hamiltonian)
        {
            afiseaza_mesaj("PROBABIL Graf HAMILTONIAN");
            afiseaza_mesaj("(Teorema lui Dirac)");
            return true;
        }
        else
        {
            afiseaza_mesaj("Nu se poate determina");
            afiseaza_mesaj("(Graf prea mare pentru backtracking)");
            return false;
        }
    }
}
void verifica_eulerian()
{
    este_graf_eulerian();
}
void verifica_hamiltonian()
{
    este_graf_hamiltonian();
}
void pagina_noua()
{
    cleardevice();
    for(int i=1; i<=n; i++)
        coordonate[i][1]=coordonate[i][2]=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            muchii[i][j]=muchii[j][i]=0;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            exista_cost[i][j]=exista_cost[j][i]=0;
    n=0;
    deseneaza_meniu();
}
int gaseste_nod(int x,int y)//cauta ca unde se apasa click cu mouse-ul sa fie nod
{
    for(int i=1; i<=n; i++)
    {
        int dx=x-coordonate[i][1];
        int dy=y-coordonate[i][2];
        if(dx*dx+dy*dy<=raza*raza)
            return i;
    }
    return 0;
}

int gaseste_nodOR(int x, int y)
{
    for(int i = 1; i <= nOR; i++)
    {
        int dx = x - coordonateOR[i][1];
        int dy = y - coordonateOR[i][2];
        if(dx*dx + dy*dy <= raza*raza)
            return i;
    }
    return 0;
}

void mutare_nodOR()
{
    setcolor(textculoare);
    bool click=false;
    int nod1;
    while(!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            nod1=gaseste_nod(x,y);
            click=true;
        }
    }
    bool click2=false;
    int x,y;
    while(!click2)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,x,y);
            click2=true;
        }
    }
    coordonate[nod1][1]=x;
    coordonate[nod1][2]=y;
    cleardevice();
    deseneaza_totOR();
}
void undo_orientat()
{
    if(vf == 0)
        return;

    if(tipop[vf]==2)  // Dacă ultima operație a fost crearea unui nod
    {
        int nod1;
        nod1=gaseste_nod(unod[vf][1],unod[vf][2]);

        // Șterge toate arcele care pleacă sau sosesc în nodul respectiv
        for(int i=1; i<=n; i++)
        {
            muchii[i][nod1]=0;
            muchii[nod1][i]=0;
            exista_cost[i][nod1]=0;
            exista_cost[nod1][i]=0;
        }

        // Mută nodurile pentru a elimina nodul șters
        for(int i = nod1; i < n; i++)
        {
            coordonate[i][1] = coordonate[i+1][1];
            coordonate[i][2] = coordonate[i+1][2];
        }

        n--;
        vf--;
        cleardevice();
        deseneaza_totOR();
    }
    else if(tipop[vf]==1)  // Dacă ultima operație a fost arc
    {
        // Șterge arcul
        muchii[nodm[vf][1]][nodm[vf][2]]=0;
        exista_cost[nodm[vf][1]][nodm[vf][2]]=0;
        vf--;
        cleardevice();
        deseneaza_totOR();
    }
    else if(tipop[vf]==3)
    {
        int nod1 = costn[vf][1];
        int nod2 = costn[vf][2];
        exista_cost[nod1][nod2]=0;
        costuri[nod1][nod2]=0;
        vf--;
        cleardevice();
        deseneaza_totOR();
    }
}
void undo()
{
    if(tipop[vf]==2)//daca e nod
    {
        int nod1;
        outtextxy(200,150,"EROARE");
        nod1=gaseste_nod(unod[vf][1],unod[vf][2]);
        for(int i = nod1; i < n; i++)
        {
            coordonate[i][1] = coordonate[i+1][1];
            coordonate[i][2] = coordonate[i+1][2];
        }

        n--;
        for(int i=1; i<=n; i++)
            muchii[i][nod1]=0;
        vf--;
        cleardevice();
        deseneaza_tot();
    }
    if(tipop[vf]==1)//daca e muchie
    {
        outtextxy(200,150,"EROARE");
        muchii[nodm[vf][1]][nodm[vf][2]]=0;
        muchii[nodm[vf][2]][nodm[vf][1]]=0;
        vf--;
        cleardevice();
        deseneaza_tot();
    }
    else if(tipop[vf]==3)  // Ștergere cost (arcul rămâne)
    {
        int nod1 = costn[vf][1];
        int nod2 = costn[vf][2];
        exista_cost[nod1][nod2]=0;
        costuri[nod1][nod2]=0;
        vf--;
        cleardevice();
        deseneaza_tot();
    }
}
void mutare_nod()
{
    setcolor(textculoare);
    bool click=false;
    int nod1;
    while(!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x,y;
            getmouseclick(WM_LBUTTONDOWN,x,y);
            nod1=gaseste_nod(x,y);
            click=true;
        }
    }
    bool click2=false;
    int x,y;
    while(!click2)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            getmouseclick(WM_LBUTTONDOWN,x,y);
            click2=true;
        }
    }
    coordonate[nod1][1]=x;
    coordonate[nod1][2]=y;
    cleardevice();
    deseneaza_tot();
}
void buton_back()
{
    cleardevice();
    pagina_noua();
    creeaza_meniu_principal();
    Algoritmica_grafurilor();
}
void Algoritmica_grafurilor()
{
    creeaza_meniu_principal();
    int xs,ys,xe,ye;
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))//verifica daca este apasat butonul pentru grafuri neorientate
        {
            getmouseclick(WM_LBUTTONDOWN, xs, ys);// luam coordonatele clickului
            if(xs>75 && xs<280 && ys>0 && ys<75)
            {
                modif_meniu();
            }
            else if(xs>leftb-15 && xs<rightb+15 && ys>topb && ys<bottomb+50)//verificam sa se apese pe butonul de graf neorientat
            {
                cleardevice();
                deseneaza_tot();
                int x, y; // coordonatele click ului

                while(1)
                    if(ismouseclick(WM_LBUTTONDOWN))  //daca am facut click stanga
                    {

                        getmouseclick(WM_LBUTTONDOWN, x, y);  // luam coordonatele clickului
                        if(x > 20 && x < 150 && y > 35 && y < 70)  // click in buton Noduri
                            click_nod();
                        else if(x > 20 && x < 150 && y > 245 && y < 280)//pentru butonul de algoritm
                            buton_algoritm();
                        else if(x > 20 && x < 150 && y > 105 && y < 140)     // 20, 105, 120, 140
                            click_muchie_neor();
                        else if(x>w-160 && x<w-20 && y>100 && y<145)
                            mutare_nod();
                        else if(x>35 && x<115 && y>h-100 && y<h-50)
                            buton_back();
                        else if(x>w-160 && x<w-20 && y>170 && y<205)
                            pagina_noua();
                        else if(x>w-160 && x<w-20 && y>240 && y<275)
                            undo();
                        else if(x>20 && x<150 && y>175 && y<210)
                            click_cost();
                        else if(x>w-160 && x<w-20 && y>310 && y<345) // Buton Save
                            salveaza_graf();
                        else if(x>w-160 && x<w-20 && y>380 && y<415) // Buton Upload
                            incarca_graf();
                    }
                deseneaza_tot();
            }
            else if(xs>leftb-15 && xs<rightb+15 && ys>topb-150 && ys<bottomb-100)
            {
                cleardevice();
                deseneaza_totOR();
                int x,y;
                while(1)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN,x,y);
                        if(x>20 && x<150 && y>245 && y<280)//apasa pe butonul algoritm
                            buton_alg_orientat();
                        else if(x>35 && x<115 && y>h-100 && y<h-50)
                            buton_back();
                        else if(x>w-160 && x<w-20 && y>170 && y<205)
                            pagina_noua();
                        else  if(x > 20 && x < 150 && y > 35 && y < 70)  // click in buton Noduri
                            click_nod();
                        else if(x > 20 && x < 150 && y > 105 && y < 140 && n>=2)     // 20, 105, 120, 140
                            click_muchieOR();
                        else if(x>20 && x<150 && y>175 && y<210)
                            click_costOR();
                        else if(x>w-160 && x<w-20 && y>100 && y<145)
                            mutare_nodOR();
                        else if(x>w-160 && x<w-20 && y>240 && y<275)
                            undo_orientat();
                        else if(x>w-160 && x<w-20 && y>310 && y<345) // Buton Save
                            salveaza_graf_orientat();
                        else if(x>w-160 && x<w-20 && y>380 && y<415) // Buton Upload
                            incarca_graf_orientat();

                    }

                }
            }
        }
}
void prim(int start)
{
    // Dacă start este 0 sau invalid, cere utilizatorului să selecteze un nod
    if(start == 0 || start > n)
    {
        afiseaza_mesaj("Selecteaza nodul de start pentru Prim...");

        int x, y;
        int sursa = 0;
        while(sursa == 0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                sursa = gaseste_nod(x, y);
            }
        }

        if(sursa != 0)
            start = sursa;
        else
            return; // Dacă nu s-a selectat niciun nod valid, ieși
    }

    bool vizitat[101] = {false};
    int dist[101];
    int parinte[101];

    for(int i = 1; i <= n; i++)
    {
        dist[i] = 1000000000;
        parinte[i] = -1;
    }

    dist[start] = 0;

    char text[50];
    sprintf(text, "Prim - Start: Nod %d", start);
    afiseaza_mesaj(text);

    for(int pas = 1; pas <= n; pas++)
    {
        int nod_min = -1;
        int minim = 1000000000;

        for(int i = 1; i <= n; i++)
            if(!vizitat[i] && dist[i] < minim)
            {
                minim = dist[i];
                nod_min = i;
            }

        if(nod_min == -1)
            break;

        vizitat[nod_min] = true;
        vizualizeaza_nod(nod_min);

        for(int i = 1; i <= n; i++)
        {
            if(muchii[nod_min][i] && !vizitat[i] && exista_cost[nod_min][i])
            {
                if(costuri[nod_min][i] < dist[i])
                {
                    dist[i] = costuri[nod_min][i];
                    parinte[i] = nod_min;
                }
            }
        }
    }

    int cost_total = 0;
    setcolor(GREEN);

    for(int i = 1; i <= n; i++)
    {
        if(parinte[i] != -1)
        {
            deseneaza_muchie(coordonate[i][1], coordonate[i][2],
                             coordonate[parinte[i]][1], coordonate[parinte[i]][2]);
            delay(600);
            cost_total += costuri[i][parinte[i]];
        }
    }

    // Redesenează doar graful (fără cleardevice)
    setfillstyle(SOLID_FILL, culoare);
    bar(176, 0, w-171, h-331); // Șterge doar zona grafului

    setcolor(textculoare);
    deseneaza_noduri();
    deseneaza_muchii();
    deseneaza_costuri();
    creare_alg_neorientat();

    // Afișare cost total
    sprintf(text, "Cost total APM: %d", cost_total);
    afiseaza_mesaj(text);
}

void afiseaza_mesaj(char* mesaj)
{
    setcolor(textculoare);
    outtextxy(Xtext, Ytext, mesaj);
    Ytext += textStep;

    // Verifică dacă s-a ajuns la limita inferioară a zonei de afișare
    if(Ytext > h - 50)
    {
        // Resetează poziția de afișare
        Ytext = h - 295;

        // Șterge zona de afișare
        setfillstyle(SOLID_FILL, culoare);
        bar(176, h-330, w-171, h); // Șterge doar zona de afișare

        // Redesenează linia de delimitare
        setcolor(textculoare);
        setlinestyle(DOTTED_LINE,1,1);
        line(0, h-330, w, h-330);
        outtextxy(180, h-325, "Afisare");
        line(175, h-300, w-170, h-300);
        setlinestyle(SOLID_LINE,0,1);

        // Afișează mesajul curent pe prima linie după resetare
        outtextxy(Xtext, Ytext, mesaj);
        Ytext += textStep;
    }
}
void buton_algoritm()
{
    creare_alg_neorientat();
    bool continua = true;

    while(continua)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(x > 20 && x < 150 && y > 245 && y < 280)
            {
                continua = false;
            }
            else if(x > 190 && x < 310 && y > 85 && y < 120) // BFS
            {
                bfs();
            }
            else if(x > 190 && x < 310 && y > 40 && y < 75) // DFS
            {
                dfs();
            }
            else if(x > 190 && x < 310 && y > 130 && y < 165) // Prim
            {
                prim(0);
            }
            else if(x > 190 && x < 310 && y > 175 && y < 210) // Dijkstra
            {
                afiseaza_mesaj("Selecteaza nodul sursa...");

                int x, y;
                int sursa = 0;
                while(sursa == 0)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        getmouseclick(WM_LBUTTONDOWN, x, y);
                        sursa = gaseste_nod(x, y);
                    }
                }

                if(sursa != 0)
                {
                    dijkstra(sursa);
                }
            }
            else if(x > 190 && x < 310 && y > 220 && y < 255) // Bellman
            {
                bellmanFord();
            }
            else if(x > 190 && x < 310 && y > 265 && y < 300) // Floyd
            {
                floydWarshall();
            }
            else if(x > 190 && x < 310 && y > 310 && y < 345) // Eulerian
            {
                verifica_eulerian();
            }
            else if(x > 190 && x < 310 && y > 355 && y < 390) // Hamiltonian
            {
                verifica_hamiltonian();
            }
        }
        delay(10);
    }

    setfillstyle(SOLID_FILL, culoare);
    bar(185,35, 445, 400);
    deseneaza_tot();
}
void afiseaza_int(int x)
{
    char text[20];
    sprintf(text, "%d", x);
    afiseaza_mesaj(text);
}


bool esteCoadaGoala(Coada* q)
{
    if(q->prim == NULL)
        return true;
    return false;
}

void insereazaCoada(Coada* q, int val)
{
    Nod* n = new Nod;
    n->val = val;
    n->urm = NULL;

    if(!esteCoadaGoala(q))
        q->ultim->urm = n;
    q->ultim = n;


    if(esteCoadaGoala(q))
        q->prim = n;
}

int citesteNodCoada(Coada* q)
{
    if(!esteCoadaGoala(q))
        return q->prim->val;
    return -1;
}

// Elimina prima valoare din coada
void eliminaNodCoada(Coada* q)
{
    if(!esteCoadaGoala(q))
    {
        q->prim = q->prim->urm;
        if(q->prim == NULL)
            q->ultim = NULL;
    }
    else
    {
        char text[50];
        sprintf(text,"Coada este goala!");
        outtextxy(195,h-340,text);
    }
}

// Coloreaza un nod in turcoaz pentru 1.5 secunde
void vizualizeaza_nod(int val)
{
    int x = coordonate[val][1];
    int y = coordonate[val][2];

    // ștergere zonă
    setfillstyle(SOLID_FILL, culoare);
    bar(x - raza - 5, y - raza - 5,
        x + raza + 5, y + raza + 5);

    setcolor(CYAN);
    char c[5];
    itoa(val, c, 10);
    circle(x, y, raza);
    outtextxy(x - 5, y - 5, c);

    delay(800);

    // ștergere din nou
    setfillstyle(SOLID_FILL, culoare);
    bar(x - raza - 5, y - raza - 5,
        x + raza + 5, y + raza + 5);

    setcolor(textculoare);
    circle(x, y, raza);
    outtextxy(x - 5, y - 5, c);

}
int temp_window_sursa()
{
    int pw = 300, ph = 150;//lungime latime
    int px = w/2 - pw/2;//pozitionare mijloc ecran
    int py = h/2 - ph/2;


    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    // fereastra
    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(WHITE);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Introdu sursa:");
    //outtextxy(px+20, py+110, "[ ENTER = OK ]");

    char nr[10] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13)
            break;//enter
        if (c == 8 && lg > 0)//backspace
            nr[--lg] = 0;
        else if (c >= '0' && c <= '9' && lg < 9)
        {
            nr[lg++] = c;
            nr[lg] = 0;
        }


        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+60, px+pw-20, py+90);
        outtextxy(px+20, py+60, nr);//Desenează din nou ce s-a tastat,se face la fiecare tastă
    }

    // stergere fereastra
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_tot();

    return atoi(nr);
}
void bellmanFord()
{
    int sursa = temp_window_sursa();
    bool primul = true;

    int distanta[n+1];
    for(int i = 1; i <= n; i++)
        distanta[i] = INF;
    distanta[sursa] = 0;

    for(int cnt = 1; cnt < n; cnt++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(i!=j && muchii[i][j])
                {
                    int cost;
                    if(!exista_cost[i][j])
                        cost = 1;
                    else
                        cost = costuri[i][j];

                    if(distanta[i] != INF && ((distanta[i] + cost) < distanta[j]))
                    {
                        distanta[j] = distanta[i] + cost;
                    }
                }

    char rezultat[500] = "Bellman-Ford: ";
    char text[20];

    for(int i = 1; i <= n; i++)
    {
        if(i > 1)
            strcat(rezultat, ", ");

        if(distanta[i] != INF)
            sprintf(text, "%d", distanta[i]);
        else
            sprintf(text, "-1");

        strcat(rezultat, text);
    }

    afiseaza_mesaj(rezultat);
}
int temp_window_sursaOR()
{
    int pw = 300, ph = 150;//lungime latime
    int px = w/2 - pw/2;//pozitionare mijloc ecran
    int py = h/2 - ph/2;


    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(px-5, py-5, px+pw+5, py+ph+5);

    // fereastra
    setfillstyle(SOLID_FILL, BLACK);
    bar(px, py, px+pw, py+ph);

    setcolor(WHITE);
    rectangle(px, py, px+pw, py+ph);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(px+20, py+20, "Introdu sursa:");
    //outtextxy(px+20, py+110, "[ ENTER = OK ]");

    char nr[10] = "";
    int lg = 0;

    while (true)
    {
        char c = getch();

        if (c == 13)
            break;//enter
        if (c == 8 && lg > 0)//backspace
            nr[--lg] = 0;
        else if (c >= '0' && c <= '9' && lg < 9)
        {
            nr[lg++] = c;
            nr[lg] = 0;
        }


        setfillstyle(SOLID_FILL, BLACK);
        bar(px+20, py+60, px+pw-20, py+90);
        outtextxy(px+20, py+60, nr);//Desenează din nou ce s-a tastat,se face la fiecare tastă
    }

    // stergere fereastra
    setfillstyle(SOLID_FILL, culoare);
    bar(px-5, py-5, px+pw+5, py+ph+5);
    deseneaza_totOR();

    return atoi(nr);
}
void bellmanFordOR()
{
    int sursa = temp_window_sursaOR();
    bool primul = true;

    int distanta[n+1];
    for(int i = 1; i <= n; i++)
        distanta[i] = INF;
    distanta[sursa] = 0;

    for(int cnt = 1; cnt < n; cnt++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                if(i!=j && muchii[i][j])
                {
                    int cost;
                    if(!exista_cost[i][j])
                        cost = 1;
                    else
                        cost = costuri[i][j];

                    if(distanta[i] != INF && ((distanta[i] + cost) < distanta[j]))
                    {
                        distanta[j] = distanta[i] + cost;
                    }
                }

    char rezultat[500] = "Bellman-Ford: ";
    char text[20];

    for(int i = 1; i <= n; i++)
    {
        if(i > 1)
            strcat(rezultat, ", ");

        if(distanta[i] != INF)
            sprintf(text, "%d", distanta[i]);
        else
            sprintf(text, "-1");

        strcat(rezultat, text);
    }

    afiseaza_mesaj(rezultat);
}
void floydWarshall()
{
    bool primul = true;

    int distanta[n+1][n+1];
    for(int i = 1; i <= n ; i++)
        for(int j = 1; j <= n; j++)
        {
            if(exista_cost[i][j])
                distanta[i][j] = costuri[i][j];
            else
                distanta[i][j] = INF;
            if(i==j)
                distanta[i][j] = 0;
        }

    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                if(i != j)
                    if(distanta[i][k] != INF && distanta[k][j]!=INF)
                        if(distanta[i][j] > distanta[i][k] + distanta[k][j])
                            distanta[i][j] = distanta[i][k] + distanta[k][j];
            }

    for(int i = 1; i <= n; i++)
    {
        char rezultat[500] = "";
        char text[20];

        sprintf(text, "Nod %d: ", i);
        strcat(rezultat, text);

        for(int j = 1; j <= n; j++)
        {
            if(j > 1)
                strcat(rezultat, ", ");

            if(distanta[i][j] != INF)
                sprintf(text, "%d", distanta[i][j]);
            else
                sprintf(text, "-1");

            strcat(rezultat, text);
        }
        afiseaza_mesaj(rezultat);
    }
}
Stiva* stivaGoala()
{
    Stiva* s = new Stiva;
    s->prim = NULL;
    s->ultim = NULL;

    return s;
};

bool esteStivaGoala(Stiva* s)
{
    if(s->prim == NULL)
        return true;
    return false;
}

void pushStiva(Stiva* s, int val)
{
    Nod* n = new Nod;
    n->val = val;
    n->urm = NULL;

    if(esteStivaGoala(s))
    {
        s->ultim = n;
    }

    n->urm = s->prim;
    s->prim = n;
}
int citesteNodStiva(Stiva* s)
{
    if(!esteStivaGoala(s))
        return s->prim->val;
    return -1;
}

void eliminaNodStiva(Stiva* s)
{
    if(!esteStivaGoala(s))
    {
        s->prim = s->prim->urm;
        if(s->prim == NULL)
            s->ultim = NULL;
    }
    else
    {
        char text[50];
        sprintf(text,"Stiva este goala!");
        outtextxy(195,h-340,text);
    }
}
// Parcurgere BFS cu suport vizual
void bfs()
{
    int sursa = temp_window_sursa();
    bool primul = true;
    bool vizitat[101] = {false};

    Coada* q = coadaGoala();

    vizitat[sursa] = true;
    insereazaCoada(q, sursa);
    afiseaza_mesaj("BFS: ");

    while(!esteCoadaGoala(q))
    {
        int curent = citesteNodCoada(q), urmCompConexa = 0;
        eliminaNodCoada(q);

        vizualizeaza_nod(curent);
        char text[10];
        if (!primul)
        {
            outtextxy(Xtext, Ytext, ",");
            Xtext += 15;
        }
        sprintf(text, "%d", curent);
        outtextxy(Xtext, Ytext, text);
        Xtext += 20;

        primul = false;

        for(int i = 1; i <= n; i++)
            if((muchii[curent][i]) && !vizitat[i])
            {
                insereazaCoada(q, i);
                vizitat[i] = true;
            }
            else if(!vizitat[i] && !urmCompConexa)
            {
                urmCompConexa = i;
            }

        if(esteCoadaGoala(q) && urmCompConexa)
        {
            vizitat[urmCompConexa] = true;
            insereazaCoada(q, urmCompConexa);
            Xtext = 190;
            Ytext += textStep;
            primul = true;
        }
    }
    Ytext += textStep;
    Xtext = 190;  // Resetează X pentru următoarele mesaje
}

//bfs orientat
void bfs_orientat()
{
    int sursa = temp_window_sursaOR();
    bool primul = true;
    bool vizitat[101] = {false};

    Coada* q = coadaGoala();

    vizitat[sursa] = true;
    insereazaCoada(q, sursa);
    afiseaza_mesaj("BFS: ");

    while(!esteCoadaGoala(q))
    {
        int curent = citesteNodCoada(q), urmCompConexa = 0;
        eliminaNodCoada(q);

        vizualizeaza_nod(curent);
        char text[10];
        if (!primul)
        {
            outtextxy(Xtext, Ytext, ",");
            Xtext += 15;
        }
        sprintf(text, "%d", curent);
        outtextxy(Xtext, Ytext, text);
        Xtext += 20;

        primul = false;

        for(int i = 1; i <= n; i++)
            if((muchii[curent][i]) && !vizitat[i])
            {
                insereazaCoada(q, i);
                vizitat[i] = true;
            }
            else if(!vizitat[i] && !urmCompConexa)
            {
                urmCompConexa = i;
            }

        if(esteCoadaGoala(q) && urmCompConexa)
        {
            vizitat[urmCompConexa] = true;
            insereazaCoada(q, urmCompConexa);
            Xtext = 190;
            Ytext += textStep;
            primul = true;
        }
    }
    Ytext += textStep;
    Xtext = 190;  // Resetează X pentru următoarele mesaje
}

// Parcurgere DFS cu suport vizual
void dfs()
{
    int sursa = temp_window_sursa();
    afiseaza_mesaj("DFS: ");
    bool primul = true;
    bool vizitat[101] = {false};
    Stiva *s = stivaGoala();

    pushStiva(s, sursa);

    int urmCompConexa = 0;

    while(!esteStivaGoala(s))
    {
        int curent = citesteNodStiva(s);
        eliminaNodStiva(s);

        if(vizitat[curent])
        {
            if(esteStivaGoala(s) && urmCompConexa)
            {
                curent = urmCompConexa;
                primul = true;
            }
            else
                continue;
        }

        vizualizeaza_nod(curent);

        char text[10];
        if (!primul)
        {
            outtextxy(Xtext, Ytext, ",");
            Xtext += 15;
        }
        sprintf(text, "%d", curent);
        outtextxy(Xtext, Ytext, text);
        Xtext += 20;
        primul = false;

        vizitat[curent] = true;
        urmCompConexa = 0;
        for(int i = n; i > 0; i--)
            if((muchii[curent][i]) && !vizitat[i])
                pushStiva(s, i);
            else if(!vizitat[i])
                urmCompConexa = i;

        if(esteStivaGoala(s) && urmCompConexa)
        {
            vizitat[urmCompConexa] = true;
            pushStiva(s, urmCompConexa);
            Xtext = 190;
            Ytext += textStep;
            primul = true;
        }
    }
    Ytext += textStep;
    Xtext = 190;  // Resetează X pentru următoarele mesaje
}

// DFS pentru graf orientat:
void dfs_orientat()
{
    int sursa = temp_window_sursaOR();
    afiseaza_mesaj("DFS: ");
    bool primul = true;
    bool vizitat[101] = {false};
    Stiva *s = stivaGoala();

    pushStiva(s, sursa);

    int urmCompConexa = 0;

    while(!esteStivaGoala(s))
    {
        int curent = citesteNodStiva(s);
        eliminaNodStiva(s);

        if(vizitat[curent])
        {
            if(esteStivaGoala(s) && urmCompConexa)
            {
                curent = urmCompConexa;
                primul = true;
            }
            else
                continue;
        }

        vizualizeaza_nod(curent);

        char text[10];
        if (!primul)
        {
            outtextxy(Xtext, Ytext, ",");
            Xtext += 15;
        }
        sprintf(text, "%d", curent);
        outtextxy(Xtext, Ytext, text);
        Xtext += 20;
        primul = false;

        vizitat[curent] = true;
        urmCompConexa = 0;
        for(int i = n; i > 0; i--)
            if((muchii[curent][i]) && !vizitat[i])
                pushStiva(s, i);
            else if(!vizitat[i])
                urmCompConexa = i;

        if(esteStivaGoala(s) && urmCompConexa)
        {
            vizitat[urmCompConexa] = true;
            pushStiva(s, urmCompConexa);
            Xtext = 190;
            Ytext += textStep;
            primul = true;
        }
    }
    Ytext += textStep;
    Xtext = 190;  // Resetează X pentru următoarele mesaje
}
int main()
{
    initwindow(w, h, "Algoritmica grafurilor"); // fereastra mare
    Algoritmica_grafurilor();
    getch();
    closegraph();
    return 0;
}
