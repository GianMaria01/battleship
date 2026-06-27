#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>

struct strGiocatori
{
    bool hitbox[10][10] = {};
    bool attachiVS[10][10] = {};
    bool prewive[10][10] = {};
    bool Is_prewive=false;
    bool turno =false;
    Color colore;
}blu ,rosso;

struct
{
    const Rectangle Dimensione = {49,49,499,499};
    const int lCella = 50;
    const int lGriglia = 499;
    const int offSetArry = 1;
}griglia;

struct 
{
    const Rectangle Dimensione = {600,49,200,60};
    const char* testo = "hi" ;
}bottone_fineTurno;


void setHitbox(strGiocatori &giocatore)
{
    // Serve a far passare tutte e due i turni senza sovrasciverli
    if(blu.turno && ColorIsEqual(giocatore.colore,rosso.colore)) return;
    else if(rosso.turno && ColorIsEqual(giocatore.colore,blu.colore)) return;
    
    int cellaX,cellaY;
    Vector2 posizioneCursore = GetMousePosition(), celleOffsetArry;
    
    //Clic della griglia
    if(CheckCollisionPointRec(posizioneCursore,griglia.Dimensione))
    {
        //coordinate per arry della cella cliccata
        cellaX =(posizioneCursore.x / griglia.lCella)-griglia.offSetArry;
        cellaY =(posizioneCursore.y / griglia.lCella)-griglia.offSetArry;

        celleOffsetArry.x=(cellaX+griglia.offSetArry)*griglia.lCella;
        celleOffsetArry.y=(cellaY+1)*griglia.lCella;
        
        
            giocatore.Is_prewive = true;
            
            //Serve ad azzerere la prewive ogni volta altrimenti rimangono gli scarti di quando ci si passa semplicemente sopra
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    giocatore.prewive[x][y] = false;
            
            giocatore.prewive[cellaX][cellaY] = true;
        if(giocatore.Is_prewive && giocatore.prewive[cellaX][cellaY])   DrawRectangle(celleOffsetArry.x,celleOffsetArry.y,griglia.lCella,griglia.lCella,YELLOW);
        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) 
        {
            giocatore.hitbox[cellaX][cellaY] = giocatore.prewive[cellaX][cellaY];
            giocatore.turno=false;
            giocatore.Is_prewive=false;
        }
    }   
}

void disegnaHitbox(strGiocatori giocatore)
{
    Vector2 celleOffsetArry;

    for(int cellaY=0;cellaY<10;++cellaY)
    {
        for(int cellaX=0;cellaX<10;++cellaX)
        {
            celleOffsetArry.x=(cellaX+griglia.offSetArry)*griglia.lCella;
            celleOffsetArry.y=(cellaY+griglia.offSetArry)*griglia.lCella;

            if(giocatore.hitbox[cellaX][cellaY]) DrawRectangle(celleOffsetArry.x,celleOffsetArry.y,griglia.lCella,griglia.lCella,giocatore.colore);
        }
    }
    
}

void setUI()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // DEBUG DrawRectangle(49,49,499,499,YELLOW);
    DrawText(bottone_fineTurno.testo,bottone_fineTurno.Dimensione.x,bottone_fineTurno.Dimensione.y,10,BLACK);

    //Disegna griglia
    for(int i=49;i<550;i+=griglia.lCella) DrawLine(i,49,i,549,BLACK);
    for(int i=49;i<550;i+=griglia.lCella) DrawLine(49,i,549,i,BLACK);
}

int main()
{
    blu.colore = BLUE;
    blu.turno=true;
    rosso.colore = RED;


    InitWindow(1000,800,"Bataglia navale");
    SetWindowTitle("Bataglia navale");

    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        setHitbox(blu);
        setHitbox(rosso);

        disegnaHitbox(blu);
        disegnaHitbox(rosso);

        setUI();
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}