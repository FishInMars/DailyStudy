fun zip([]:string list,[]:int list):(string*int)list=[]
 | zip ([]:string list,L:int list):(string*int)list=[]
 | zip (L:string list,[]:int list):(string*int)list=[]
 | zip (str::SL,num::NL)=(str,num)::zip(SL,NL);

fun unzip([]:(string*int)list):((string list)*(int list))=([],[])
 | unzip ((str,num)::L)=let val (sl,nl)=unzip(L) in (str::sl,num::nl) end;
