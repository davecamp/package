CreateBank.bbBank( size%=0 ):"bbCreateBank"
FreeBank( bank.bbBank ):"bbFreeBank"
BankSize%( bank.bbBank ):"bbBankSize"
ResizeBank( bank.bbBank,size% ):"bbResizeBank"
CopyBank( src_bank.bbBank,src_offset%,dest_bank.bbBank,dest_offset%,count% ):"bbCopyBank"
PeekByte%( bank.bbBank,offset% ):"bbPeekByte"
PeekShort%( bank.bbBank,offset% ):"bbPeekShort"
PeekInt%( bank.bbBank,offset% ):"bbPeekInt"
PeekFloat#( bank.bbBank,offset% ):"bbPeekFloat"
PokeByte( bank.bbBank,offset%,value% ):"bbPokeByte"
PokeShort( bank.bbBank,offset%,value% ):"bbPokeShort"
PokeInt( bank.bbBank,offset%,value% ):"bbPokeInt"
PokeFloat( bank.bbBank,offset%,value# ):"bbPokeFloat"
ReadBytes%( bank.bbBank,file.BBStream,offset%,count% ):"bbReadBytes"
WriteBytes%( bank.bbBank,file.BBStream,offset%,count% ):"bbWriteBytes"
