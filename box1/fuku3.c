/* $B:#2s$O<B:]$K(BGenBank$B$N%U%!%$%k$r%/%i%9$rMQ$$$FA`:n$7$F$_$^$7$g$&!#(B
   $B$b$&(BGenBank$B%U%!%$%k$r07$&$s$G$9$h!#(B

   $B<!$N%W%m%0%i%`$rBG$A$3$s$GAv$i$;$F$_$h$&!#(B
*/

#include <iostream.h>
#include <string.h>
#include <stdio.h>

class GBFile {
 private:
  FILE *_fp;    // $B$3$N%/%i%9$G;H$o$l$k%U%!%$%k$X$N%]%$%s%?(B

 public:
  GBFile(char *);
  ~GBFile();
  void get_next_CDS();

};

 GBFile::GBFile(char *filename){  // $B%/%i%99=C[(B
   if((_fp = fopen(filename, "r")) == NULL){
     cerr << "File " << '"' << filename << '"' << " not found.";
     exit(1);
   }
 }

 GBFile::~GBFile(){ // $B%/%i%9$,L58z$K$J$k$HF1;~$K%U%!%$%k%/%m!<%:(B
   fclose(_fp);
 }

 void GBFile::get_next_CDS(){  // $B<!$N(BCDS$B$N9T$r8+$D$1$k(B
   static char line[200];
   while(fgets(line, 200, _fp) != NULL){
     if(strncmp(&line[5], "CDS", 3) == 0){
       cout << line;
       break;
     }
   }
 }

void main(int argc, char *argv[]){

  GBFile gb(argv[1]);   // <--- (a)
  
  gb.get_next_CDS();
  gb.get_next_CDS();
  gb.get_next_CDS();


} // <--- (b)

/* $B%W%m%0%i%`$N3F9T$N0UL#$OJ,$+$j$^$9$+!)(B

(a)$B$NDj5A$HF1;~$K%/%i%99=C[$,8F$P$l$^$9!#$D$^$j%U%!%$%k$,%*!<%W%s(B
$B$5$l$k$N$G$9!#(B

(b)$B$N$H$3$m$K%W%m%0%i%`$NN.$l$,$/$k$H(B($B$D$^$j%W%m%0%i%`=*N;;~(B)
~GBFile()$B$,8F$P$l$^$9!#(B

gb.get_next_CDS()$B$G(B(a)$B$N$H$3$m$G;XDj$5$l$?%U%!%$%k$N<!$N(BCDS$B$N9T$rC5$7!"(B
$BI=<($7$^$9!#(B

$B2]Bj#1!'$3$N%W%m%0%i%`$N%/%i%9$K(BDEFINITION$B$N9T$rC5$7!"I=<($9$k(B
get_definition$B$rIU$12C$($^$7$g$&!#(B

$B2]Bj#2!'$3$N%W%m%0%i%`$N%/%i%9(BGBFile$B$N(Bprivate$B$K(Bint _cds_start[10000];
$B$H(Bint _cds_end[10000];int _ncds$B$r2C$(!"FI$_9~$s$@(BCDS$B$N3+;O0LCV!"=*N;0LCV!"(B
$B:#$^$G$KFI$_9~$s$@(BCDS$B$N?t$r=q$-9~$`%W%m%0%i%`$r(Bget_next_cds$B$KDI2C$7$^$7$g$&!#(B



