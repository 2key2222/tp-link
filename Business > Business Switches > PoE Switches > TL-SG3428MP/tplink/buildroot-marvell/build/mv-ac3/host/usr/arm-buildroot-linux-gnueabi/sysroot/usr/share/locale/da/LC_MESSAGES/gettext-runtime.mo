??    *      l  ;   ?      ?  B   ?  !  ?  ?    9   ?  M   9     ?  ,   ?  ,   ?  ,   ?  '   *	  -   R	      ?	  (   ?	  (   ?	     ?	     
     3
  ?   @
  e   8  :   ?    ?  ?  ?  ?  ?     e     z  *   ?  1   ?  &   ?            "   3  9   V  I   ?  ?   ?     x     ?     ?     ?     ?     ?     ?  ?  ?  @   ?  "  ?  ?    ;   ?  H        Y  /   u  5   ?  /   ?  (     0   4  $   e  &   ?  &   ?     ?     ?       ?     ]     1   t    ?  ?  ?  e  ?     !     !  9   +!  &   e!  -   ?!     ?!     ?!  $   ?!  ?    "  P   @"  w   ?"     	#     #     2#     M#     `#     q#  
   ?#           "   #               '   
                                             (                           &                 )   	       !      %           $                                           *         -V, --version               output version information and exit
   -d, --domain=TEXTDOMAIN   retrieve translated message from TEXTDOMAIN
  -e                        enable expansion of some escape sequences
  -E                        (ignored for compatibility)
  -h, --help                display this help and exit
  -V, --version             display version information and exit
  [TEXTDOMAIN]              retrieve translated message from TEXTDOMAIN
  MSGID MSGID-PLURAL        translate MSGID (singular) / MSGID-PLURAL (plural)
  COUNT                     choose singular/plural form based on this value
   -d, --domain=TEXTDOMAIN   retrieve translated messages from TEXTDOMAIN
  -e                        enable expansion of some escape sequences
  -E                        (ignored for compatibility)
  -h, --help                display this help and exit
  -n                        suppress trailing newline
  -V, --version             display version information and exit
  [TEXTDOMAIN] MSGID        retrieve translated message corresponding
                            to MSGID from TEXTDOMAIN
   -h, --help                  display this help and exit
   -v, --variables             output the variables occurring in SHELL-FORMAT
 %s: invalid option -- '%c'
 %s: option '%c%s' doesn't allow an argument
 %s: option '%s' is ambiguous; possibilities: %s: option '--%s' doesn't allow an argument
 %s: option '--%s' requires an argument
 %s: option '-W %s' doesn't allow an argument
 %s: option '-W %s' is ambiguous
 %s: option '-W %s' requires an argument
 %s: option requires an argument -- '%c'
 %s: unrecognized option '%c%s'
 %s: unrecognized option '--%s'
 Bruno Haible Copyright (C) %s Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 Display native language translation of a textual message whose grammatical
form depends on a number.
 Display native language translation of a textual message.
 If the TEXTDOMAIN parameter is not given, the domain is determined from the
environment variable TEXTDOMAIN.  If the message catalog is not found in the
regular directory, another location can be specified with the environment
variable TEXTDOMAINDIR.
Standard search directory: %s
 If the TEXTDOMAIN parameter is not given, the domain is determined from the
environment variable TEXTDOMAIN.  If the message catalog is not found in the
regular directory, another location can be specified with the environment
variable TEXTDOMAINDIR.
When used with the -s option the program behaves like the 'echo' command.
But it does not simply copy its arguments to stdout.  Instead those messages
found in the selected catalog are translated.
Standard search directory: %s
 In normal operation mode, standard input is copied to standard output,
with references to environment variables of the form $VARIABLE or ${VARIABLE}
being replaced with the corresponding values.  If a SHELL-FORMAT is given,
only those environment variables that are referenced in SHELL-FORMAT are
substituted; otherwise all environment variables references occurring in
standard input are substituted.
 Informative output:
 Operation mode:
 Report bugs to <bug-gnu-gettext@gnu.org>.
 Substitutes the values of environment variables.
 Try '%s --help' for more information.
 Ulrich Drepper Unknown system error Usage: %s [OPTION] [SHELL-FORMAT]
 Usage: %s [OPTION] [TEXTDOMAIN] MSGID MSGID-PLURAL COUNT
 Usage: %s [OPTION] [[TEXTDOMAIN] MSGID]
or:    %s [OPTION] -s [MSGID]...
 When --variables is used, standard input is ignored, and the output consists
of the environment variables that are referenced in SHELL-FORMAT, one per line.
 Written by %s.
 error while reading "%s" memory exhausted missing arguments standard input too many arguments write error Project-Id-Version: gettext-runtime 0.19.4-rc1
Report-Msgid-Bugs-To: bug-gnu-gettext@gnu.org
POT-Creation-Date: 2015-09-11 12:23+0900
PO-Revision-Date: 2015-04-26 01:45+0200
Last-Translator: Keld Simonsen <keld@keldix.com>
Language-Team: Danish <dansk@dansk-gruppen.dk>
Language: da
MIME-Version: 1.0
Content-Type: text/plain; charset=iso-8859-1
Content-Transfer-Encoding: 8-bit
Plural-Forms: nplurals=2; plural=(n != 1);
X-Generator: Lokalize 1.0
   -V, --version               vis versionsinformation og afslut
   -d, --domain=TEKSTDOM?NE  hent oversatte tekster fra TEKSTDOM?NE
  -e                        aktiv?r fortolkning af visse escape-sekvenser
  -E                        (ignoreret af hensyn til kompatibilitet)
  -h, --help                vis denne hj?lp og afslut
  -V, --version             vis versionsinformation og afslut
  [TEKSTDOM?NE]             hent den oversatte tekst fra TEKSTDOM?NE
  TEKSTID TEKSTID-FLERTAL   overs?t TEKSTID (ental) / TEKSTID-FLERTAL (flertal)
  COUNT                     v?lg ental/flertalsform ud fra denne v?rdi
   -d, --domain=TEKSTDOM?NE  hent oversatte tekster fra TEKSTDOM?NE
  -e                        aktiv?r fortolkning af visse escape-sekvenser
  -E                        (ignoreret af hensyn til kompatibilitet)
  -h, --help                vis denne hj?lp og afslut
  -V, --version             vis versionsinformation og afslut
  [TEKSTDOM?NE] TEKSTID     hent den oversatte tekst svarende til
                            TEKSTID fra TEKSTDOM?NE
   -h, --help                     vis denne hj?lp og afslut
   -v, --variables             vis variablene der optr?der i SKAL-FORMAT
 %s: ugyldigt tilvalg -- %c
 %s: tilvalget `%c%s' tillader ikke et argument
 %s: tilvalget '%s' kan betyde flere ting, muligheder: %s: tilvalget '--%s' tillader ikke et argument
 %s: tilvalget `--%s' kr?ver et argument
 %s: tilvalget '-W %s' tillader ikke et argument
 %s: tilvalget '-W %s' er flertydigt
 %s: tilvalget `%s' kr?ver et argument
 %s: tilvalget '%c' kr?ver et argument
 %s: ukendt tilvalg `%c%s'
 %s: ukendt tilvalg `--%s'
 Bruno Haible Ophavsret ? %s Free Software Foundation, Inc.
Licens GPLv3+: GNU GPL version 3 eller senere <http://gnu.org/licenses/gpl.html>
Dette er frit programmel: du kan frit ?ndre og videredistribuere det.
Der er INGEN GARANTIER, s? vidt som lov foreskriver.
 Vis overs?ttelser i det lokale sprog af tekstbeskeder hvis grammatiske
form beror p? et tal.
 Vis ikke-engelsk overs?ttelse af en tekstbesked.
 Hvis TEKSTDOM?NE-parameteren ikke angives, bestemmes dom?net ud fra v?rdien af
milj?variablen TEXTDOMAIN. Hvis tekstkataloget ikke kan findes i det
s?dvanlige filkatalog, kan en anden placering angives vha milj?variablen
TEXTDOMAINDIR.
Standard-filkataloget for s?gning er: %s
 Hvis TEKSTDOM?NE-parameteren ikke angives, bestemmes dom?net ud fra v?rdien af
milj?variablen TEXTDOMAIN. Hvis tekstkataloget ikke kan findes i det
s?dvanlige filkatalog, kan en anden placering angives med milj?variablen
TEXTDOMAINDIR.
N?r tilvalget -s bruges, opf?rer programmet sig som 'echo'-kommandoen.
Men argumenterne bliver ikke blot kopieret til standard uddata. I stedet
overs?ttes de tekster der findes i det valgte tekstkatalog.
Standard-filkataloget for s?gning er: %s
 I normal k?rselstilstand kopieres standard-inddata til standard-uddata,
med referencer til milj?variable p? formen $VARIABLE eller ${VARIABLE}
erstattet med den tilsvarende v?rdi. Hvis et SKAL-FORMAT er angivet,
bliver kun de milj?variable som refereres i SKAL-FORMAT erstattet;
ellers erstates alle milj?variabelreferencer der optr?der i
standard-inddata.
 Informativt uddata:
 K?rselstilstand:
 Rapport?r fejl p? engelsk til <bug-gnu-gettext@gnu.org>.
 Erstatter v?rdierne af milj?variable.
 Pr?v '%s --help' for yderligere oplysninger.
 Ulrich Drepper Ukendt systemfejl Brug: %s [TILVALG] [SKAL-FORMAT]...
 Brug: %s [TILVALG] [TEKSTDOM?NE] TEKSTID TEKSTID-FLERTAL ANTAL
 Brug:  %s [TILVALG] [[TEKSTDOM?NE] TEKSTID]
eller: %s [TILVALG] -s [TEKSTID]...
 N?r --variables bruges, ignores inddata, og uddata best?r af
milj?variablene der optr?der i SKAL-FORMAT, ?n per linje.
 Skrevet af %s.
 fejl ved l?sning af '%s' ikke mere ledig hukommelse argumenter mangler standard-inddata For mange argumenter skrivefejl 