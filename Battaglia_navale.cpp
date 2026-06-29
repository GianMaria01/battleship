// Battaglia_navale.cpp
// Questo progetto utilizza raylib (https://www.raylib.com).
// Raylib è distribuita sotto la licenza zlib/libpng (https://github.com/raysan5/raylib/blob/master/LICENSE).

#include <iostream>
#include <raylib.h>
#include <string>

struct 
{
    bool Is_Overlay = false;
    float Timer = 0.0f;
    const float durata = 2.0f;
    int cellaX = 0;
    int cellaY = 0;
    float salita = 0;
}anCambioTurno, anMiss;


struct strGiocatori
{
    std::string nome;
    bool hitbox[10][10] = {};
    bool attachiVS[10][10] = {};
    bool prewive[10][10] = {};
    bool Is_prewive=false;
    bool turno =false;
    Color colore;
    int DimNave = 1;
    int numColpiGiusti = 0;
    bool Is_Winner = false;
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
    const Vector2 PosTesto = {640,69};
    const std::string scritta ="Pass turn";
    const int DimTesto = 20;
}bottone_fineTurno;

struct 
{
    int NumTurno = 0;
    bool Is_SetHitbox = true;
    bool gameOver = false;
}info_gioco;

struct
{
    const int width = 1000;
    const int height = 600;
} schemro;

void setHitbox()
{

    // serve a selezionare il turno el giocatore
    if(!info_gioco.Is_SetHitbox) return;

    strGiocatori *giocatore = nullptr;
    if (blu.turno) giocatore = &blu;
    else if (rosso.turno) giocatore = &rosso;
    else if (!blu.turno && !rosso.turno)
    {
        info_gioco.Is_SetHitbox = false;
        anCambioTurno.Is_Overlay = true;
        return;
    } else if (!giocatore) return;
    
    int cellaX,cellaY;
    Vector2 posizioneCursore = GetMousePosition(), celleOffsetArry;

    // Pulsante del passo turno solo quando tutte le navi sono state schierate
    if(giocatore->DimNave>5){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if(CheckCollisionPointRec(posizioneCursore,bottone_fineTurno.Dimensione)) 
            {
                giocatore->turno=false;
                if(ColorIsEqual(giocatore->colore,blu.colore)) rosso.turno=true;
            }
        }
    }
    
    //Clic della griglia
    if(CheckCollisionPointRec(posizioneCursore,griglia.Dimensione))
    {
        //coordinate per arry della cella cliccata
        cellaX =(posizioneCursore.x / griglia.lCella)-griglia.offSetArry;
        cellaY =(posizioneCursore.y / griglia.lCella)-griglia.offSetArry;

        celleOffsetArry.x=(cellaX+griglia.offSetArry)*griglia.lCella;
        celleOffsetArry.y=(cellaY+griglia.offSetArry)*griglia.lCella;
        
        //Serve ad azzerere la prewive ogni volta altrimenti rimangono gli scarti di quando ci si passa semplicemente sopra
        for (int y = 0; y < 10; ++y)
            for (int x = 0; x < 10; ++x)
                giocatore->prewive[x][y] = false;
        
        //TODO: con l'aggiunta delle navi conforme predefinite mdoiificare 
        giocatore->Is_prewive = true;
        giocatore->prewive[cellaX][cellaY] = true;
        if(giocatore->Is_prewive && giocatore->prewive[cellaX][cellaY] && !giocatore->hitbox[cellaX][cellaY])   DrawRectangle(celleOffsetArry.x,celleOffsetArry.y,griglia.lCella,griglia.lCella,YELLOW);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            if (giocatore->hitbox[cellaX][cellaY]) 
            {
                giocatore->hitbox[cellaX][cellaY]=false;
                giocatore->DimNave--;
            }
            else
            {
                giocatore->hitbox[cellaX][cellaY] = giocatore->prewive[cellaX][cellaY];
                giocatore->DimNave++;
                giocatore->Is_prewive=false;
            }
        }
    }   
}

void disegnaHitbox()
{
    Vector2 celleOffsetArry;
    strGiocatori *giocatore = nullptr;
    if (blu.turno) giocatore = &blu;
    else if (rosso.turno) giocatore = &rosso;
    else if (!giocatore) return;

    for(int cellaY=0;cellaY<10;++cellaY)
    {
        for(int cellaX=0;cellaX<10;++cellaX)
        {
            celleOffsetArry.x=(cellaX+griglia.offSetArry)*griglia.lCella;
            celleOffsetArry.y=(cellaY+griglia.offSetArry)*griglia.lCella;

            if(giocatore->hitbox[cellaX][cellaY]) DrawRectangle(celleOffsetArry.x,celleOffsetArry.y,griglia.lCella,griglia.lCella,giocatore->colore);
        }
    }
    
}

void setUI()
{
    strGiocatori *giocatore = nullptr;
    if (blu.turno) giocatore = &blu;
    else if (rosso.turno) giocatore = &rosso;
    
    if (giocatore && giocatore->DimNave>5)
    {
        if(CheckCollisionPointRec(GetMousePosition(),bottone_fineTurno.Dimensione) && !IsMouseButtonDown(MOUSE_BUTTON_LEFT )) DrawRectangleRec(bottone_fineTurno.Dimensione, {204,204,204,255});
        else DrawRectangleRec(bottone_fineTurno.Dimensione, GRAY);
    } else DrawRectangleRec(bottone_fineTurno.Dimensione, {204,204,204,255});
    DrawText(bottone_fineTurno.scritta.c_str(),bottone_fineTurno.PosTesto.x,bottone_fineTurno.PosTesto.y,bottone_fineTurno.DimTesto,BLACK);
    //Disegna griglia
    for(int i=49;i<550;i+=griglia.lCella) DrawLine(i,49,i,549,BLACK);
    for(int i=49;i<550;i+=griglia.lCella) DrawLine(49,i,549,i,BLACK);
}

void Atacchi ()
{
    strGiocatori *giocatore = nullptr;
    strGiocatori *aversario = nullptr;

    if(!info_gioco.Is_SetHitbox)
    {
        if (info_gioco.NumTurno % 2)
        {
            giocatore = &rosso;
            aversario = &blu;
        }
        else 
        {
            giocatore = &blu;
            aversario = &rosso;
        }
        if(!giocatore || !aversario) return;
    } else return;
    

    // <------ Disegno griglia -------->

    for (int y = 0; y < 10; ++y)
    {
        for (int x = 0; x < 10; ++x)
        {
            if(giocatore->attachiVS[x][y])
            {
                Vector2 CellaUI;
                // TODO verificare che tutte le navi sono state colpite e dare a win al giocatore 
                CellaUI.x = griglia.Dimensione.x + x * griglia.lCella;
                CellaUI.y = griglia.Dimensione.y + y * griglia.lCella;

                if(aversario->hitbox[x][y]) DrawRectangle(CellaUI.x,CellaUI.y,griglia.lCella,griglia.lCella, GRAY);
                else DrawRectangle(CellaUI.x,CellaUI.y,griglia.lCella,griglia.lCella, SKYBLUE);
            }
        }
    }

    // <---------- Animazione cambio turno -------->
    if (anCambioTurno.Is_Overlay)
    {
        int PosTesX = (schemro.width / 2) - 150;

        anCambioTurno.Timer += GetFrameTime();

        // Disegna l'overlay per questo frame
        Color sfondo = giocatore->colore;
        sfondo.a = 180;  
        DrawRectangle(0, 0, schemro.width, schemro.height, sfondo);
        DrawText(("GO "+giocatore->nome+", attack").c_str(), PosTesX, (schemro.height / 2)-40 ,40, WHITE);
    }

    // Quando il timer scade, chiudi l'overlay
    if (anCambioTurno.Timer >= anCambioTurno.durata)
    {
        anCambioTurno.Is_Overlay = false;
        anCambioTurno.Timer = 0.0f;
    }

    // <-------Logica attachi-------->

    int cellaX, cellaY;

    if(!anCambioTurno.Is_Overlay && !anMiss.Is_Overlay)
    {    
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 posizioneMouse = GetMousePosition();
            if(CheckCollisionPointRec(posizioneMouse,griglia.Dimensione))
            {
                cellaX = (posizioneMouse.x - griglia.Dimensione.x) / griglia.lCella;
                cellaY = (posizioneMouse.y - griglia.Dimensione.y) / griglia.lCella;

                if (!giocatore->attachiVS[cellaX][cellaY])
                {
                    giocatore->attachiVS[cellaX][cellaY] = true;
                    
                    if(!aversario->hitbox[cellaX][cellaY])
                    {
                        anMiss.Is_Overlay = true;
                        anMiss.cellaX = cellaX;
                        anMiss.cellaY = cellaY;
                    } else ++giocatore->numColpiGiusti;
                    
                }
            }
        }

    if (giocatore->numColpiGiusti == 5) 
    {
        info_gioco.gameOver = true;
        giocatore->Is_Winner = true;
        return;
    }
    
    }

        // <---------- Animazione Miss --------->

    if(anMiss.Is_Overlay)
    {

        anMiss.Timer += GetFrameTime();

        anMiss.salita -= 0.02;

        Vector2 CellaUI;
        CellaUI.x = griglia.Dimensione.x + anMiss.cellaX * griglia.lCella;
        CellaUI.y = griglia.Dimensione.y + anMiss.cellaY * griglia.lCella;

        DrawText("Miss!", CellaUI.x, CellaUI.y  + anMiss.salita, 21, BLACK);
    }

    if(anMiss.Timer>anMiss.durata)
    {
        anMiss.Is_Overlay = false;
        anMiss.Timer = 0.0f;
        anMiss.salita = 0;

        ++info_gioco.NumTurno;
        anCambioTurno.Is_Overlay =true;
        return;
    }

}

void winner()
{
    if (!info_gioco.gameOver) return;
    
    strGiocatori *giocatore = nullptr;
    strGiocatori *aversario = nullptr;

    
    if (blu.Is_Winner)
    {
        giocatore = &blu;
        aversario = &rosso;
    } else
    {
        giocatore = &rosso;
        aversario =&blu;
    }
    if(!aversario || !giocatore) return;

    for (int y = 0; y < 10; ++y)
    {
        Vector2 CellaUI;
        for (int x = 0; x < 10; ++x)
        {
            
            CellaUI.x = griglia.Dimensione.x + x * griglia.lCella;
            CellaUI.y = griglia.Dimensione.y + y * griglia.lCella;
            if(aversario->hitbox[x][y]) DrawRectangle(CellaUI.x,CellaUI.y,griglia.lCella,griglia.lCella, GRAY);
            else DrawRectangle(CellaUI.x,CellaUI.y,griglia.lCella,griglia.lCella, SKYBLUE);
        }
    }

    int PosTesX = (schemro.width / 2) - 200;
    // Disegna l'overlay per questo frame
    Color sfondo = giocatore->colore;
    sfondo.a = 180;  
    DrawRectangle(0, 0, schemro.width, schemro.height, sfondo);

    // disegno corona
    DrawTriangle({500 , 100},{450 , 200},{550 , 200},YELLOW);
    DrawTriangle({400 , 100},{350 , 200},{450 , 200},YELLOW);
    DrawTriangle({600 , 100},{550 , 200},{650 , 200},YELLOW);
    DrawRectangle(350,200,300,100,YELLOW);

    DrawText(("The winner is "+giocatore->nome).c_str(), PosTesX, 400 ,40, WHITE);

    // Quando il timer scade, chiudi l'overlay
    if (anCambioTurno.Timer >= anCambioTurno.durata)
    {
        anCambioTurno.Is_Overlay = false;
        anCambioTurno.Timer = 0.0f;
    }
}

int main()
{
    blu.colore = BLUE;
    blu.turno=true;
    blu.nome = "blue";
    rosso.colore = RED;
    rosso.nome = "red";


    InitWindow(schemro.width,schemro.height,"Bataglia navale");
    SetWindowTitle("Bataglia navale");

    while(!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        setUI();

        // TODO creare If gameover per non far antrare più nelle funzioni 
        setHitbox();
        disegnaHitbox();

        Atacchi();

        winner();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
