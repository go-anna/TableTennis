
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

        int x = -8;
        int y = -8;
        int speed = 0;
        int pointsLeft = 0;
        int pointsRight = 0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        Application->MessageBox( "Witaj w grze Tenis sto³owy.\n\n"
        "Lewy gracz steruje wciskaj¹c klawisze A oraz Z.\n"
        "Prawy gracz steruje wciskaj¹c strza³ki do góry i w dó³.\n\n"
        "Dla urozmaicenia zabawy:\n"
        "Kiedy odbijesz pi³kê na œrosku paletki to pi³ka przyœpiesza i zmienia k¹t odbicia.\n"
        "Im d³u¿ej odbijasz, tym pi³ka szybciej przemieszcza siê.\n\n"
        "Mo¿esz dowolnie zmieniaæ pole gry.\n\n"
        "¯yczê samych wygranych!",MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer_ballTimer(TObject *Sender)
{

        newGame->Visible = false;
        nextRound->Visible = false;

        ball->Left += x;
        ball->Top += y;

        //bounce a ball from a top wall
        if (ball->Top + 5 <= background->Top) y = -y;

        //bounce a ball from a bottom wall
        if ((ball->Top + ball->Height + 5) >= background->Height) y = -y;

        //bounce from left paddle
        if (ball->Top > paddleLeft->Top - ball->Height/2 &&
            ball->Top + ball->Height < paddleLeft->Top + paddleLeft->Height + ball->Height/2 &&
            ball->Left < paddleLeft->Left + paddleLeft->Width)
            {
                if (x<0) x = -x;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
                if (ball->Top > paddleLeft->Top + 30 &&
                    ball->Top + ball->Height < paddleLeft->Top + paddleLeft->Height -30)
                    {

                        x *= 1.2;
                        y *= 1.2;
                    }

                speed++;
            }

        //bounce from right paddle
        if (ball->Top > paddleRight->Top - ball->Height/2 &&
            ball->Top + ball->Height < paddleRight->Top + paddleRight->Height + ball->Height/2 &&
            ball->Left + ball->Width > paddleRight->Left)
            {
                if (x>0) x = -x;
                sndPlaySound("snd/hit.wav", SND_ASYNC);
                if (ball->Top > paddleRight->Top + 30 &&
                    ball->Top + ball->Height < paddleRight->Top + paddleRight->Height -30)
                    {

                       x *= 1.2;
                       y *= 1.2;
                    }
                speed++;

            }

        //point for right user
        if (ball->Left < paddleLeft->Left + paddleLeft->Width - 10 )
        {
                sndPlaySound("snd/cheering1.wav", SND_ASYNC);
                pointsRight++;
                pointLeft->Caption = pointsRight;
                newGame->Enabled = true;
                newGame->Visible = true;
                if(pointsRight == 5)
                {
                        winText->Visible = true;
                        pointsRight =0;
                        pointsLeft =0;
                        nextRound->Enabled = false;
                }else if(pointsLeft < 5 && pointsRight <5)
                {
                        nextRound->Enabled = true;
                        nextRound->Visible = true;
                }
        }

        //point for left user
        if (ball->Left + ball->Width > paddleRight->Left + 10 )
        {
                sndPlaySound("snd/cheering1.wav", SND_ASYNC);
                pointsLeft++;
                pointRight->Caption = pointsLeft;
                newGame->Enabled = true;
                newGame->Visible = true;
                if(pointsLeft == 5)
                {
                        winText->Visible = true;
                        pointsRight =0;
                        pointsLeft =0;
                        nextRound->Enabled = false;
                } else if(pointsRight < 5 && pointsLeft <5)
                {
                        nextRound->Enabled = true;
                        nextRound->Visible = true;
                }
        }

        if ((ball->Left < paddleLeft->Left + paddleLeft->Width - 10) ||
        (ball->Left + ball->Width > paddleRight->Left + 10 ))
        {
                Timer_ball->Enabled = false;
                ball->Visible = false;
                nextRound->Visible = true;
                newGame->Visible = true;
                pointLeft->Left = background->Width / 2 - pointLeft->Width / 2 +30;
                pointRight->Left = background->Width / 2 - pointRight->Width / 2-30;
                result->Left = background->Width / 2 - result->Width / 2;
                ball->Left = background->Width / 2;
        }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::leftUpPaddleTimer(TObject *Sender)
{
        if (paddleLeft->Top > 10) paddleLeft->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::leftDPaddleTimer(TObject *Sender)
{
        if (paddleLeft->Top + paddleLeft->Height < background->Height -10 ) paddleLeft->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightUpPaddleTimer(TObject *Sender)
{
        if (paddleRight->Top > 10) paddleRight->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rightDPaddleTimer(TObject *Sender)
{
        if (paddleRight->Top + paddleRight->Height < background->Height -10 ) paddleRight->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41) leftUpPaddle->Enabled = true;
        if (Key == 0x5A) leftDPaddle->Enabled = true;
        if (Key == VK_UP) rightUpPaddle->Enabled = true;
        if (Key == VK_DOWN) rightDPaddle->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if (Key == 0x41) leftUpPaddle->Enabled = false;
        if (Key == 0x5A) leftDPaddle->Enabled = false;
        if (Key == VK_UP) rightUpPaddle->Enabled = false;
        if (Key == VK_DOWN) rightDPaddle->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::newGameClick(TObject *Sender)
{
        speed = 0;
        pointsLeft = 0;
        pointsRight = 0;
        pointRight->Caption = IntToStr(pointsRight);
        pointLeft->Caption = IntToStr(pointsLeft);
        paddleLeft -> Top = Form1 ->background -> Height / 2 - Form1 ->paddleLeft -> Height / 2;
        paddleRight -> Top = Form1 ->background -> Height / 2 - Form1 ->paddleRight -> Height / 2;
        x = -8;
        y = -8;
        Timer_ball->Enabled = true;
        ball->Visible = true;
        pointRight->Visible = true;
        pointLeft->Visible = true;
        Label1->Visible = true;
        winText->Visible = false;

}

//---------------------------------------------------------------------------


void __fastcall TForm1::nextRoundClick(TObject *Sender)
{
        speed = 0;
        x = -x;
        ball->Visible = true;
        Timer_ball->Enabled = true;

}
//---------------------------------------------------------------------------


