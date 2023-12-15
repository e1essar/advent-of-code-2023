program day15_1;

var
  InputFile: Text;
  Line: string;
  i: Integer;
  OutputList: array of string;
  HashArray: array of Integer;
  HashSum: Integer;

function CalculateHash(const Element: string): Integer;
var
  k: Integer;
begin
  Result := 0;
  for k := 1 to Length(Element) do
  begin
    Result := (Result + Ord(Element[k])) * 17 mod 256;
  end;
end;

begin
  AssignFile(InputFile, 'day15.txt');
  Reset(InputFile);
  ReadLn(InputFile, Line);
  CloseFile(InputFile);

  while Length(Line) > 0 do
  begin
    i := Pos(',', Line);
    if i > 0 then
    begin
      SetLength(OutputList, Length(OutputList) + 1);
      OutputList[High(OutputList)] := Copy(Line, 1, i - 1);
      Delete(Line, 1, i);
    end
    else
    begin
      SetLength(OutputList, Length(OutputList) + 1);
      OutputList[High(OutputList)] := Line;
      Line := '';
    end;
  end;

  SetLength(HashArray, Length(OutputList));
  for i := Low(OutputList) to High(OutputList) do
  begin
    HashArray[i] := CalculateHash(OutputList[i]);
  end;

  HashSum := 0;
  for i := Low(HashArray) to High(HashArray) do
    HashSum := HashSum + HashArray[i];

  Writeln(HashSum);

  ReadLn;
end.