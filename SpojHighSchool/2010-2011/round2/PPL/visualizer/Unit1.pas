unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, Math;

type
  TForm1 = class(TForm)
    Timer1: TTimer;
    Label1: TLabel;
    Image1: TImage;
    procedure FormClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.FormClick(Sender: TObject);
begin
	form1.Timer1.Interval:=10;
	form1.Timer1.Enabled:=true;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
	form1.Height:=900;
	form1.Width:=800;
	form1.Left:=50;
	form1.Top:=50;
	form1.image1.Height:=800;
4	form1.image1.Width:=800;
	form1.image1.Left:=0;
	form1.image1.Top:=0;
  form1.Image1.Canvas.Create;
	form1.Timer1.Interval:=1000;
	form1.Timer1.Enabled:=true;
  form1.Canvas.Create;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var x,y,x1,y1:real;
  	minx,maxx,miny,maxy:real;
    coef:real;
    cnt,i:integer;
    const colors:array[0..2] of TColor=($000000,$00FF00,$0000FF);
    const wds:array[0..2] of integer=(1,2,3);
begin
  minx:=1 shl 29;maxx:=-1 shl 29;
  miny:=1 shl 29;maxy:=-1 shl 29;
  for i:=0 to 2 do
  begin
    reset(input,'picture'+inttostr(i)+'.txt');
    while not eof(input) do
    begin
      read(x,y);
      if x > maxx then
        maxx:=x;
      if y > maxy then
        maxy:=y;
      if x < minx then
        minx:=x;
      if y < miny then
        miny:=y;
    end;
    System.close(input);
  end;
  coef:=min(700/(maxx-minx),700/(maxy-miny));
  for cnt:=0 to 2 do
  begin
    reset(input,'picture'+inttostr(cnt)+'.txt');
	  form1.Image1.Canvas.Brush.Color:=colors[cnt];
	  form1.Image1.Canvas.Pen.Color:=colors[cnt];
	  form1.Image1.Canvas.Pen.Width:=wds[cnt];
	  while not eof(input) do
	  begin
    	read(x,y);
	    read(x1,y1);
	    x:=x-minx;
	    y:=y-miny;
	    x1:=x1-minx;
	    y1:=y1-miny;
	    if (x<>x1) or (y<>y1) then
	    begin
	        form1.Image1.Canvas.MoveTo(trunc(x*coef)+50,form1.image1.height-trunc(y*coef)-50);
    	    form1.Image1.Canvas.LineTo(trunc(x1*coef)+50,form1.image1.height-trunc(y1*coef)-50);
    	end;
      end;
      System.Close(input);
  end;
  form1.Label1.Top:=800;
  form1.Label1.Left:=350;
  form1.Font.Size:=18;
  reset(input,'picturev.txt');
  read(i);
  form1.Label1.Caption:='Score: '+inttostr(i);
  System.Close(input);
  form1.Timer1.Enabled:=false;
end;

end.
