//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *background;
        TImage *ball;
        TTimer *Timer_ball;
        TImage *paddleLeft;
        TImage *paddleRight;
        TTimer *leftUpPaddle;
        TTimer *leftDPaddle;
        TTimer *rightUpPaddle;
        TTimer *rightDPaddle;
        TLabel *pointLeft;
        TLabel *pointRight;
        TButton *nextRound;
        TButton *newGame;
        TLabel *result;
        TLabel *winText;
        TLabel *Label1;
        void __fastcall Timer_ballTimer(TObject *Sender);
        void __fastcall leftUpPaddleTimer(TObject *Sender);
        void __fastcall leftDPaddleTimer(TObject *Sender);
        void __fastcall rightUpPaddleTimer(TObject *Sender);
        void __fastcall rightDPaddleTimer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall newGameClick(TObject *Sender);
        void __fastcall nextRoundClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
