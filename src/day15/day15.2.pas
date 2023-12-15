program day15_2;

var
  InputFile: Text;
  Line: string;
  i, j, Sum: Integer;
  OutputList: array of string;
  NewList: array of string;
  New1List: array of string;
  New2List: array of string;
  New3List: array of string;
  NewNewList: array of string;
  HashArray: array of Integer;
  ResultArray: array[0..255] of array of string;

function CalculateHash(const Element: string): Integer;
var
  k: Integer;
begin
  Result := 0;
  for k := 1 to Length(Element)-2  do
  begin
    Result := (Result + Ord(Element[k])) * 17 mod 256;
  end;
end;

procedure FilterOutputList;
var
  i, j: Integer;
begin
  i := 0;
  while i < High(OutputList) do
  begin
    j := i + 1;
    while j <= High(OutputList) do
    begin
      if (Copy(OutputList[i], 1, Pos('=', OutputList[i]) - 1) = Copy(OutputList[j], 1, Pos('-', OutputList[j]) - 1)) and
   (Pos('=', OutputList[i]) > 0) and
   (Pos('-', OutputList[j]) > 0) then
      begin
        OutputList[i] := '';
        OutputList[j] := '';
      end;
      Inc(j);
    end;
    Inc(i);
  end;
end;

procedure RemoveEmptyElements(var Arr: array of string);
var
  i, j: Integer;
begin
  i := 0;
  while i <= High(Arr) do
  begin
    if Arr[i] = '' then
    begin
      for j := i to High(Arr) - 1 do
        Arr[j] := Arr[j + 1];
      SetLength(Arr, Length(Arr) - 1);
    end
    else
      Inc(i);
  end;
end;

procedure RemoveDuplicates(var Arr: array of string);
var
  i, j: Integer;
begin
  i := 0;
  while i <= High(Arr) do
  begin
    j := i - 1;
    while (j >= 0) and (Arr[j] <> Arr[i]) do
      Dec(j);

    if (j >= 0) then
    begin
      for j := i to High(Arr) - 1 do
        Arr[j] := Arr[j + 1];
      SetLength(Arr, Length(Arr) - 1);
    end
    else
      Inc(i);
  end;
end;

function UpdateNewList(var OutputList, NewList: array of string): Boolean;
var
  i, j: Integer;
begin
  Result := False;
  for i := 0 to High(OutputList) do
  begin
    if OutputList[i] <> '' then
    begin
      for j := 0 to High(NewList) do
      begin
        if Copy(OutputList[i], 1, Pos('=', OutputList[i])) = Copy(NewList[j], 1, Pos('=', NewList[j])) then
        begin
          NewList[j] := OutputList[i];
          Result := True; 
          Break;
        end;
      end;

      SetLength(NewList, Length(NewList) + 1);
      NewList[High(NewList)] := OutputList[i];
    end;
  end;
end;

procedure RemoveElementsWithHyphen(var Arr: array of string);
var
  i, j: Integer;
begin
  i := 0;
  while i <= High(Arr) do
  begin
    if Pos('-', Arr[i]) > 0 then
    begin
      for j := i to High(Arr) - 1 do
        Arr[j] := Arr[j + 1];
      SetLength(Arr, Length(Arr) - 1);
    end
    else
      Inc(i);
  end;
end;

begin
  AssignFile(InputFile, 'test15.txt');
  Reset(InputFile);

  while not EOF(InputFile) do
  begin
    ReadLn(InputFile, Line);

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
    end;
    
    FilterOutputList;
    RemoveElementsWithHyphen(OutputList);

    SetLength(NewList, 0); 
    UpdateNewList(OutputList, NewList);
    RemoveDuplicates(NewList);
    
    SetLength(NewNewList, 0);
    UpdateNewList(NewList, NewNewList);
    RemoveDuplicates(NewNewList);
    
    WriteLn('NewNewList:');
    for i := 0 to High(NewNewList) do
      WriteLn(NewNewList[i]);

    SetLength(HashArray, Length(NewNewList));
    for i := Low(NewNewList) to High(NewNewList) do
    begin
      HashArray[i] := CalculateHash(NewNewList[i]);

      if (Pos('=', NewNewList[i]) > 0) then
      begin
        j := Length(ResultArray[HashArray[i]]);
        SetLength(ResultArray[HashArray[i]], j + 1);
        ResultArray[HashArray[i]][j] := Copy(NewNewList[i], Pos('=', NewNewList[i]) + 1, Length(NewNewList[i]));
      end;
    end;
  
  Sum := 0;
  for i := 0 to High(ResultArray) do
    for j := 0 to High(ResultArray[i]) do
      Sum := Sum + (i + 1) * (j + 1) * StrToInt(ResultArray[i][j]);

  WriteLn(Sum);
  CloseFile(InputFile);
  ReadLn;
end.
