??    ?      ?  ?   L	      `  ?   a  Z   V  ~  ?  ?  0  ?    }  ?  ?   ;  m   ?  r   T  ?   ?  ?  ?  n  h  ?   ?  [   ?  `   -  N   ?  \   ?  k  :  p  ?$  ?  '  @   ?(  '  )    3*     O+     f+  %   y+  *   ?+     ?+     ?+  B   ?+  E   ?,  L   ?,     ?,     ?,  $   ?,  E   -  !   _-     ?-     ?-  0   ?-     ?-      ?-  -   .     K.     g.  ,   ?.  !   ?.     ?.      ?.     /     ./     J/     `/      q/     ?/     ?/     ?/     ?/     0  -   '0      U0  %   v0  #   ?0     ?0  0   ?0  2   1  $   91     ^1  H   y1     ?1     ?1     ?1     ?1     2     '2  =   92  D   w2  $   ?2  (   ?2  '   
3  !   23  +   T3  .   ?3     ?3  B   ?3  9   4  3   F4     z4  #   ?4     ?4     ?4     ?4     5     $5     =5  '   U5  &   }5     ?5     ?5  ,   ?5  A   6     D6     Y6     l6  0   ?6  1   ?6     ?6  #   ?6     7  %   <7  #   b7  <   ?7  &   ?7  O   ?7  ?   :8  3   %9  X   Y9  /   ?9  ,   ?9     :  @   &:  (   g:  )   ?:     ?:  0   ?:  ?   
;     ?;  =   ?;     <  ]   ;<  *   ?<  d   ?<     )=     H=  "   d=  '   ?=     ?=  )   ?=     ?=     >     1>      D>     e>  7   |>  .   ?>  /   ?>    ?  C  $@  _   hA  9  ?A    E  ?  I  ?  ?J  ?   ?L  t   WM  p   ?M    =N  ?  NO  ?  8Q  :  ?R  ?   T  ?   ?T  R   LU  \   ?U  n  ?U  ?  k\  ?  N_  F   5a  W  |a  {  ?b     Pd     hd  0   ~d  8   ?d     ?d  ,   ?d  U   )e  Z   e  e   ?e     @f     Uf  +   nf  C   ?f  +   ?f     
g     'g     Ag  1   ag  9   ?g  A   ?g  !   h  #   1h  3   Uh  0   ?h  #   ?h  #   ?h  %   i  (   (i     Qi     li  )   ?i  *   ?i  "   ?i  +   ?i  &   'j  +   Nj  ?   zj  )   ?j     ?j  )   k     -k  B   Bk  F   ?k  2   ?k  )   ?k  d   )l     ?l     ?l     ?l     ?l     ?l  &   m  L   9m  N   ?m  (   ?m  !   ?m  -    n  +   Nn  I   zn  0   ?n     ?n  O   o  <   `o  :   ?o     ?o  4   ?o      'p  '   Hp      pp  %   ?p  &   ?p     ?p  /   ?p  *   "q     Mq  &   fq  *   ?q  K   ?q     r     r     +r  6   ;r  5   rr     ?r  #   ?r     ?r  3   s  $   ;s  L   `s  +   ?s  I   ?s    #t  9   3u  `   mu  4   ?u  0   v     4v  B   Iv  ,   ?v  -   ?v     ?v  1   w  ?   9w  "   ?w  >   x  "   Yx  ^   |x  )   ?x  e   y  "   ky     ?y  &   ?y  (   ?y  %   ?y  -   !z     Oz     kz     ?z  !   ?z     ?z  C   ?z  2   {  1   N{     \   )   #       6          1   R       ?      U   J   {   :   ~   ?       Y   a   I   3   ?   C           n   _      O   T           ?      ?   8   ?         w   o   h   d   ?      9   ?       M   ?      F       t          *   v   N       u   B       4       b   V       ?         ?                         X      ,   5      l   ^   "       ?   +   G      <   W       H       r   S       /      z          @             g   ?   |                   [          '   (       -       P           ?       7           j   e   k   ?   2   q   A   
       !   ;              Q       ?   y       x   f      }   ]   $             .   %       ?   ?          i      K   	       >              Z   ?   E   ?   s   &       D           =   L   c   0   p   m   `      ?    
Add one or more files to the topmost or named patch.  Files must be
added to the patch before being modified.  Files that are modified by
patches already applied on top of the specified patch cannot be added.

-P patch
	Patch to add files to.
 
Edit the specified file(s) in \$EDITOR (%s) after adding it (them) to
the topmost patch.
 
Fork the topmost patch.  Forking a patch means creating a verbatim copy
of it under a new name, and use that new name instead of the original
one in the current series.  This is useful when a patch has to be
modified, but the original version of it should be preserved, e.g.
because it is used in another series, or for the history.  A typical
sequence of commands would be: fork, edit, refresh.

If new_name is missing, the name of the forked patch will be the current
patch name, followed by \`-2'.  If the patch name already ends in a
dash-and-number, the number is further incremented (e.g., patch.diff,
patch-2.diff, patch-3.diff).
 
Generate a dot(1) directed graph showing the dependencies between
applied patches. A patch depends on another patch if both touch the same
file or, with the --lines option, if their modifications overlap. Unless
otherwise specified, the graph includes all patches that the topmost
patch depends on.
When a patch name is specified, instead of the topmost patch, create a
graph for the specified patch. The graph will include all other patches
that this patch depends on, as well as all patches that depend on this
patch.

--all	Generate a graph including all applied patches and their
	dependencies. (Unapplied patches are not included.)

--reduce
	Eliminate transitive edges from the graph.

--lines[=num]
	Compute dependencies by looking at the lines the patches modify.
	Unless a different num is specified, two lines of context are
	included.

--edge-labels=files
	Label graph edges with the file names that the adjacent patches
	modify.

-T ps	Directly produce a PostScript output file.
 
Global options:

--trace
	Runs the command in bash trace mode (-x). For internal debugging.

--quiltrc file
	Use the specified configuration file instead of ~/.quiltrc (or
	/etc/quilt.quiltrc if ~/.quiltrc does not exist).  See the pdf
	documentation for details about its possible contents.  The
	special value \"-\" causes quilt not to read any configuration
	file.

--version
	Print the version number and exit immediately. 
Grep through the source files, recursively, skipping patches and quilt
meta-information. If no filename argument is given, the whole source
tree is searched. Please see the grep(1) manual page for options.

-h	Print this help. The grep -h option can be passed after a
	double-dash (--). Search expressions that start with a dash
	can be passed after a second double-dash (-- --).
 
Please remove all patches using \`quilt pop -a' from the quilt version used to create this working tree, or remove the %s directory and apply the patches from scratch.\n 
Print a list of applied patches, or all patches up to and including the
specified patch in the file series.
 
Print a list of patches that are not applied, or all patches that follow
the specified patch in the series file.
 
Print an annotated listing of the specified file showing which
patches modify which lines. Only applied patches are included.

-P patch
	Stop checking for changes at the specified rather than the
	topmost patch.
 
Print or change the header of the topmost or specified patch.

-a, -r, -e
	Append to (-a) or replace (-r) the exiting patch header, or
	edit (-e) the header in \$EDITOR (%s). If none of these options is
	given, print the patch header.

--strip-diffstat
	Strip diffstat output from the header.

--strip-trailing-whitespace
	Strip trailing whitespace at the end of lines of the header.

--backup
	Create a backup copy of the old version of a patch as patch~.
 
Print the list of files that the topmost or specified patch changes.

-a	List all files in all applied patches.

-l	Add patch name to output.

-v	Verbose, more user friendly output.

--combine patch
	Create a listing for all patches between this patch and
	the topmost or specified patch. A patch name of \`-' is
	equivalent to specifying the first applied patch.

 
Print the list of patches that modify the specified file. (Uses a
heuristic to determine which files are modified by unapplied patches.
Note that this heuristic is much slower than scanning applied patches.)

-v	Verbose, more user friendly output.
 
Print the name of the next patch after the specified or topmost patch in
the series file.
 
Print the name of the previous patch before the specified or topmost
patch in the series file.
 
Print the name of the topmost patch on the current stack of applied
patches.
 
Print the names of all patches in the series file.

-v	Verbose, more user friendly output.
 
Produces a diff of the specified file(s) in the topmost or specified
patch.  If no files are specified, all files that are modified are
included.

-p n	Create a -p n style patch (-p0 or -p1 are supported).

-p ab	Create a -p1 style patch, but use a/file and b/file as the
	original and new filenames instead of the default
	dir.orig/file and dir/file names.

-u, -U num, -c, -C num
	Create a unified diff (-u, -U) with num lines of context. Create
	a context diff (-c, -C) with num lines of context. The number of
	context lines defaults to 3.

--no-timestamps
	Do not include file timestamps in patch headers.

--no-index
	Do not output Index: lines.

-z	Write to standard output the changes that have been made
	relative to the topmost or specified patch.

-R	Create a reverse diff.

-P patch
	Create a diff for the specified patch.  (Defaults to the topmost
	patch.)

--combine patch
	Create a combined diff for all patches between this patch and
	the patch specified with -P. A patch name of \`-' is equivalent
	to specifying the first applied patch.

--snapshot
	Diff against snapshot (see \`quilt snapshot -h').

--diff=utility
	Use the specified utility for generating the diff. The utility
	is invoked with the original and new file name as arguments.

--color[=always|auto|never]
	Use syntax coloring.

--sort	Sort files by their name instead of preserving the original order.
 
Remove patch(es) from the stack of applied patches.  Without options,
the topmost patch is removed.  When a number is specified, remove the
specified number of patches.  When a patch name is specified, remove
patches until the specified patch end up on top of the stack.  Patch
names may include the patches/ prefix, which means that filename
completion can be used.

-a	Remove all applied patches.

-f	Force remove. The state before the patch(es) were applied will
	be restored from backup files.

-R	Always verify if the patch removes cleanly; don't rely on
	timestamp checks.

-q	Quiet operation.

-v	Verbose operation.
 
Remove the specified or topmost patch from the series file.  If the
patch is applied, quilt will attempt to remove it first. (Only the
topmost patch can be removed right now.)

-n	Delete the next patch after topmost, rather than the specified
	or topmost patch.

-r	Remove the deleted patch file from the patches directory as well.

--backup
	Rename the patch file to patch~ rather than deleting it.
	Ignored if not used with \`-r'.
 
Rename the topmost or named patch.

-P patch
	Patch to rename.
 
Take a snapshot of the current working state.  After taking the snapshot,
the tree can be modified in the usual ways, including pushing and
popping patches.  A diff against the tree at the moment of the
snapshot can be generated with \`quilt diff --snapshot'.

-d	Only remove current snapshot.
 
Upgrade the meta-data in a working tree from an old version of quilt to the
current version. This command is only needed when the quilt meta-data format
has changed, and the working tree still contains old-format meta-data. In that
case, quilt will request to run \`quilt upgrade'.
        quilt --version %s: I'm confused.
 Appended text to header of patch %s\n Applied patch %s (forced; needs refresh)\n Applying patch %s\n Cannot add symbolic link %s\n Cannot diff patches with -p%s, please specify -p0 or -p1 instead\n Cannot refresh patches with -p%s, please specify -p0 or -p1 instead\n Cannot use --strip-trailing-whitespace on a patch that has shadowed files.\n Commands are: Conversion failed\n Converting meta-data to version %s\n Could not determine the envelope sender address. Please use --sender. Delivery address `%s' is invalid
 Diff failed, aborting\n Directory %s exists\n Display name `%s' contains unpaired parentheses
 Failed to back up file %s\n Failed to backup patch file %s\n Failed to copy files to temporary directory\n Failed to create patch %s\n Failed to import patch %s\n Failed to insert patch %s into file series\n Failed to patch temporary files\n Failed to remove patch %s\n Failed to remove patch file %s\n Failed to rename %s to %s: %s
 File %s added to patch %s\n File %s disappeared!
 File %s exists\n File %s is already in patch %s\n File %s is located below %s\n File %s is not being modified\n File %s is not in patch %s\n File %s may be corrupted\n File %s modified by patch %s\n File series fully applied, ends at patch %s\n Fork of patch %s created as %s\n Fork of patch %s to patch %s failed\n Importing patch %s (stored as %s)\n Importing patch %s\n Interrupted by user; patch %s was not applied.\n Introduction has no subject header (saved as %s)\n Introduction has no subject header\n Introduction saved as %s\n More recent patches modify files in patch %s. Enforce refresh with -f.\n No next patch\n No patch removed\n No patches applied\n No patches in series\n Nothing in patch %s\n Now at patch %s\n Option \`-P' can only be used when importing a single patch\n Options \`--combine', \`--snapshot', and \`-z' cannot be combined.\n Patch %s already exists in series.\n Patch %s appears to be empty, removing\n Patch %s appears to be empty; applied\n Patch %s can be reverse-applied\n Patch %s does not apply (enforce with -f)\n Patch %s does not exist; applied empty patch\n Patch %s does not exist\n Patch %s does not remove cleanly (refresh it or enforce with -f)\n Patch %s exists already, please choose a different name\n Patch %s exists already, please choose a new name\n Patch %s exists already\n Patch %s exists. Replace with -f.\n Patch %s is applied\n Patch %s is currently applied\n Patch %s is not applied\n Patch %s is not in series\n Patch %s is now on top\n Patch %s is unchanged\n Patch %s needs to be refreshed first.\n Patch %s not applied before patch %s\n Patch %s renamed to %s\n Patch headers differ:\n Patches %s have duplicate subject headers.\n Please use -d {o|a|n} to specify which patch header(s) to keep.\n Refreshed patch %s\n Removed patch %s\n Removing patch %s\n Removing trailing whitespace from line %s of %s
 Removing trailing whitespace from lines %s of %s
 Renaming %s to %s: %s
 Renaming of patch %s to %s failed\n Replaced header of patch %s\n Replacing patch %s with new version\n SYNOPSIS: %s [-p num] [-n] [patch]
 The %%prep section of %s failed; results may be incomplete\n The -v option will show rpm's output\n The quilt meta-data in %s are already in the version %s format; nothing to do\n The quilt meta-data in this tree has version %s, but this version of quilt can only handle meta-data formats up to and including version %s. Please pop all the patches using the version of quilt used to push them before downgrading.\n The topmost patch %s needs to be refreshed first.\n The working tree was created by an older version of quilt. Please run 'quilt upgrade'.\n USAGE: %s {-s|-u} section file [< replacement]
 Unable to extract a subject header from %s\n Unpacking archive %s\n Usage: quilt [--trace[=verbose]] [--quiltrc=XX] command [-h] ... Usage: quilt add [-P patch] {file} ...\n Usage: quilt annotate [-P patch] {file}\n Usage: quilt applied [patch]\n Usage: quilt delete [-r] [--backup] [patch|-n]\n Usage: quilt diff [-p n|-p ab] [-u|-U num|-c|-C num] [--combine patch|-z] [-R] [-P patch] [--snapshot] [--diff=utility] [--no-timestamps] [--no-index] [--sort] [--color] [file ...]\n Usage: quilt edit file ...\n Usage: quilt files [-v] [-a] [-l] [--combine patch] [patch]\n Usage: quilt fork [new_name]\n Usage: quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [patch]\n Usage: quilt grep [-h|options] {pattern}\n Usage: quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [patch]\n Usage: quilt new {patchname}\n Usage: quilt next [patch]\n Usage: quilt patches [-v] {file}\n Usage: quilt pop [-afRqv] [num|patch]\n Usage: quilt previous [patch]\n Usage: quilt rename [-P patch] new_name\n Usage: quilt series [-v]\n Usage: quilt snapshot [-d]\n Usage: quilt top\n Usage: quilt unapplied [patch]\n Usage: quilt upgrade\n Warning: more recent patches modify files in patch %s\n Warning: trailing whitespace in line %s of %s
 Warning: trailing whitespace in lines %s of %s
 Project-Id-Version: quilt 0.43
PO-Revision-Date: 2006-01-04 17:30+0100
Last-Translator: Jean Delvare <khali@linux-fr.org>
Language-Team: French <traduc@traduc.org>
Language: fr
MIME-Version: 1.0
Content-Type: text/plain; charset=ISO-8859-1
Content-Transfer-Encoding: 8bit
 
Ajoute un ou plusieurs fichiers au patch indiqu? ou ? celui au sommet.
Les fichiers doivent ?tre ajout?s au patch avant toute modification.
Les fichiers modifi?s par d'autres patches ? la fois plus haut dans la pile
et d?j? appliqu?s ne peuvent pas ?tre ajout?s.

-P patch
	Patch auquel les fichiers doivent ?tre ajout?s.
 
?dite le(s) fichier(s) sp?cifi?s au sein de \$EDITOR (%s) apr?s addition 
au patch du sommet.
 
Cr?e un embranchement (?fork?) au niveau du patch au sommet. Cr?er un
embranchement signifie cr?er une copie ? l'identique d'un patch sous un
nouveau nom, et utiliser ce nouveau nom au lieu du nom d'origine dans la
s?rie courante. C'est utile lorsqu'un patch doit ?tre modifi? mais que
la version originale doit ?galement ?tre pr?serv?e, par exemple parce
qu'elle est utilis?e dans une autre s?rie, ou pour conserver
l'historique d'un patch. Une s?quence de commandes classique serait :
fork (cr?er un embranchement), edit (?diter le patch), refresh
(rafra?chir le patch).

Si nouveau_nom n'est pas pr?cis?, le nouveau nom du patch sera le nom
actuel suivi de \`-2'. Si le nom du patch se termine d?j? par un
tiret suivi d'un nombre, ce nombre est augment? ? la place (par
exemple : patch.diff, patch-2.diff, patch-3.diff).
 
G?n?re un graphe orient? compatible dot(1), qui repr?sente les
d?pendances entre les patches appliqu?s. Un patch d?pend d'un autre patch
si les deux modifient un m?me fichier, ou, avec l'option --lines, si
leurs modifications se recouvrent. Par d?faut, le graphe inclut tous les
patches dont le patch au sommet d?pend.
Si le nom d'un patch est sp?cifi?, le graphe est cr?? pour celui-ci au
lieu du patch au sommet. Le graphe inclura alors tous les patches qui
en d?pendent, ainsi que tous les patches dont lui-m?me d?pend.

--all	G?n?re un graphe incluant tous les patches appliqu?s et
	leurs d?pendances. (Les patches non-appliqu?s ne sont pas
	inclus.)

--reduce
	Elimine les arcs transitifs du graphe.

--lines[=num]
	G?n?re les d?pendances en regardant les lignes modifi?es par
	les patches. A moins qu'une valeur diff?rente ne soit sp?cifi?e,
	deux lignes de contexte sont incluses.
--edge-labels=files
	Etiquette les arcs avec le nom des fichiers modifi?s par les
	patches adjacents.

-T ps	Produit directement un fichier PostScript.
 
Options globales :

--trace
	Lance la commande en mode trace de bash (-x). Pour le debug interne.

--quiltrc fichier
	Utilise le fichier de configuration sp?cifi? au lieu de ~/.quiltrc
	(ou /etc/quilt.quiltrc si ~/.quiltrc n'existe pas). Voir la
	documentation pdf pour plus de d?tails sur son contenu potentiel.
La valeur sp?ciale \"-\" sp?cifie ? quilt de ne lire aucun fichier
de configuration.

--version
	Affiche le num?ro de version et sort imm?diatement. 
Recherche r?cursivement un motif dans les fichiers source, en omettant
les patches et les meta-informations de quilt. Si aucun fichier n'est
pr?cis?, recherche dans tout l'arbre des sources. Voir la page de manuel
de grep(1) pour les options.

-h	Affiche cette aide. L'option -h de grep peut ?tre pass?e
	apr?s un double tiret (--). Les motifs qui commencent par un
	tiret peuvent ?tre pass?es apr?s un second double tiret
	(-- --).
 
Veuillez retirer tous les patchs en utilisant ? quilt pop -a ? avec la 
version utilis?e pour cr?er cet arbre de travail, ou effacez le r?pertoire
%s et r?appliquez compl?tement vos patchs.\n 
Affiche la liste des patches appliqu?s, ou la liste de tous les patches
jusqu'? celui pass? en param?tre (inclus).
 
Affiche la liste de tous les patches non appliqu?s, ou de tous les patches
suivant celui indiqu? en param?tre.
 
Affiche une version annot?e du fichier sp?cifi?, montrant quel
patch modifie chaque ligne. Seuls les patches appliqu?s sont
pris en compte.

-P patch
	Annote le fichier tel qu'il se trouve apr?s application du patch
	sp?cifi? plut?t que d'aller jusqu'au patch au sommet.
 
Affiche ou modifie l'en-t?te du patch au sommet ou sp?cifi?.

-a, -r, -e
	Ajoute ? la fin de (-a) ou remplace (-r) l'en-t?te existant, ou
	?dite (-e) l'en-t?te en utilisant \$EDITOR (%s). Si aucune de
	ces options n'est utilis?e, affiche l'en-t?te actuel du patch.

--strip-diffstat
	Omet la partie diffstat de l'en-t?te.

--strip-trailing-whitespace
	Supprime les espaces de fin de ligne de l'en-t?te.

--backup
	Cr?e une sauvegarde de la version originale du patch en tant
	que patch~.
 
Affiche la liste des fichiers que le patch au sommet (ou celui sp?cif?)
modifie.

-a	Liste tous les fichiers de tous les patches actuellement appliqu?s.

-l	Affiche ?galement le nom du patch.

-v	Affichage verbeux, plus simple ? lire.

--combine patch
	Affiche la liste pour tous les patches entre ce patch et le patch au
	sommet (ou le patch sp?cifi?). Le nom de fichier ? - ? correspond au
	premier patch appliqu?.
 
Affiche la liste des patches modifiant le fichier sp?cifi?. 

Une heuristique est utilis?e pour d?terminer quels fichiers sont 
modifi?s par les patches n'?tant pas appliqu?s. Veuillez noter que 
cette heuristique est bien plus lente que l'?tude des patches 
appliqu?s.

-v	Affichage verbeux, plus simple ? lire.
 
Affiche le nom du patch apr?s celui sp?cifi? (ou apr?s celui au sommet)
dans le fichier de s?rie.

-n	Affiche le nom de fichier au lieu du nom de patch.
 
Affiche le nom du patch avant celui sp?cifi? (ou apr?s celui au sommet)
dans le fichier de s?rie.

-n	Affiche le nom de fichier au lieu du nom de patch.
 
Affiche le nom du patch au sommet de la pile des patches actuellement
appliqu?s.
 
Affiche le nom de tous les patches de la s?rie.

-v	Affichage verbeux, plus simple ? lire.
 
Produit un diff du ou des fichiers sp?cifi?s par le patch sp?cifi? (ou ?
d?faut, par le patch au sommet). Si aucun fichier n'est indiqu?, tous les
fichiers modifi?s par ce patch sont inclus.

-p n	Cr?e un patch au style -p n (-p0 et -p1 sont possibles).

-p ab	Cr?e un patch au style -p 1, mais utilise a/fichier et b/fichier
	comme noms de l'ancien et du nouveau fichier, au lieu des noms par
	d?faut rep.orig/fichier et rep/fichier.

-u, -U num, -c, -C num
	Cr?e un diff unifi? (-u, -U) ayant num lignes de contexte. 
	Cr?e un diff contextuel (-c, -C) ayant num lignes de contexte. 
	Par d?faut, les diffs ont 3 lignes de contexte.

--no-timestamps
	Omet les tampons (?timestamps?) dans les ent?tes de patch.

--no-index
	Omet les lignes Index:.

-z	Affiche sur la sortie standard les changements effectu?s par rapport
	au patch sp?cifi? (ou celui au sommet ? d?faut).

-R	Cr?e un diff inverse.

-P patch
	Cr?e un diff pour ce patch (par d?faut, le patch au sommet)

--combine patch
	Cr?e un patch combin? pour tous les patches entre celui sp?cifi?
	ici et celui sp?cifi? avec l'argument -P. Utiliser ?-? comme nom
	de patch est ?quivalent ? sp?cifier le premier patch appliqu?.

--snapshot
	Cr?e un diff ? partir de l'instantan? (voir ?quilt snapshot -h?).

--diff=utilitaire
	Utilise le programme sp?cifi? pour g?n?rer le diff. Ce programme
	est invoqu? avec le nom du fichier originel et celui du nouveau 
	fichier comme arguments.

--color[=always|auto|never]
	Colorise la syntaxe toujours (?always?), de mani?re automatique
	(?auto?) ou jamais (?never?).

--sort	Trie les fichiers par leur nom au lieu de pr?server leur ordre
	d'origine.
 
Retire un ou plusieurs patches de la pile. Si aucun argument n'est 
sp?cifi?, le patch au sommet est retir?. Si un nombre est pass? en
argument, cela indique la quantit? de patchs ? retirer. Si un nom 
de patch est sp?cifi?, il est retir? ainsi que tous ceux plac?s avant
lui dans la s?rie. Le nom des patchs peut contenir le pr?fix patches/
de fa?on ? pouvoir profiter de la compl?tion sur le nom de fichier.

-a	Retire tous les patches de la s?rie.

-f	Force l'action. L'?tat avant que les patches ne soient retir?s
	sera restor? depuis les fichiers de sauvegarde.

-R	V?rifie que le patch s'enl?ve proprement ; ne se base pas sur
	les horaires de derni?re modification des fichiers.

-q	Op?re silencieusement.

-v	Op?re verbeusement.
 
Efface le patch sp?cifi? (ou celui au sommet de la pile) de la s?rie 
actuelle. Si le patch est appliqu?, quilt tentera de le retirer avant.
(Seul le patch au sommet peut ?tre retir? pour l'instant).

-n	Efface le patch qui suit celui qui est au sommet, au lieu du
	patch sp?cifi? ou de celui qui est au sommet.

-r	Supprime ?galement le patch enlev? du r?pertoire patches.

--backup
	Renomme le fichier en patch~ au lieu de le supprimer.
	Ignor? si \`-r' n'est pas ?galement utilis?.
 
Renomme le patch au sommet ou sp?cifi?.

-P patch
	Patch ? renommer.
 
Prend un instantan? de l'?tat courant du r?pertoire de travail. Apr?s cela, 
il reste possible de travailler normalement avec quilt en poussant et en 
retirant des patches. Un diff?rentiel entre l'arbre au moment de l'instantan? 
et son ?tat courant peut ?tre g?n?r? avec ?quilt diff --snapshot?.

-d	Supprime l'instantan? actuel et termine.
 
Convertit les m?ta-donn?es contenues dans un arbre de travail d'une 
ancienne version de quilt ? la version actuelle. Cette commande n'est
n?cessaire que lorsque le format de ces m?ta-donn?es change lors d'une
mise ? jour de quilt, mais que l'arbre de travail contient des donn?es
? l'ancien format. Dans ce cas, quilt vous demandera d'utiliser
? quilt upgrade ? explicitement.
         quilt --version %s : Je suis confus.
 Texte ajout? ? la fin de l'en-t?te du patch %s\n %s a ?t? appliqu? (forc? ; vous devriez le rafra?chir)\n Application de %s\n Impossible d'ajouter le lien symbolique %s\n Impossible de cr?er des patches avec -p%s. Veuillez sp?cifier -p0 ou -p1 ? la place\n Impossible de rafra?chir des patchs avec -p%s. Veuillez sp?cifier -p0 ou -p1 ? la place.\n Impossible d'utiliser --strip-trailing-whitespace sur un patch dont
certains fichiers sont masqu?s.\n Les commandes sont : ?chec de la conversion\n Conversion des m?ta-donn?es au format v%s\n Impossible de d?terminer l'adresse d'exp?diteur. Utilisez --sender. L'adresse de destination `%s' est invalide
 Le diff a ?chou?. Abandon.\n Le r?pertoire %s existe\n Le nom `%s' est mal parenth?s?
 Impossible de faire une copie de s?curit? de %s\n Impossible de faire une copie de s?curit? du fichier %s\n Impossible de copier les fichiers dans le r?pertoire temporaire\n Impossible de cr?er le patch %s\n Impossible d'importer le patch %s\n Impossible d'inserer %s dans le fichier de s?rie.\n Impossible de patcher les fichiers temporaires\n Impossible de retirer le patch %s\n Impossible de retirer le patch %s\n Impossible de renommer %s en %s : %s
 Le fichier %s a ?t? ajout? au patch %s\n Le fichier %s a disparu !
 Le fichier %s existe\n Le fichier %s est d?j? dans le patch %s\n Le fichier %s est situ? en dessous de %s\n Le fichier %s n'est pas modifi?.\n Le fichier %s n'est pas dans le patch %s.\n Le fichier %s est peut-?tre corrompu\n Le fichier %s est modifi? par le patch %s\n La s?rie est compl?tement appliqu?e. Le dernier patch est %s.\n Le fork de %s a ?t? cr?? en tant que %s\n Le fork de %s en %s a ?chou?\n Import du patch %s (enregistr? dans %s)\n Import du patch %s\n Interrompu par l'utilisateur ; le patch %s n'a pas ?t? appliqu?.\n L'introduction n'a pas de ligne de sujet (sauvegard? en tant que %s)\n L'introduction ne contient pas de ligne de sujet\n Introduction sauvegard?e en tant que %s\n Des fichiers plus r?cents modifient les m?mes fichiers que %s.
Forcez le rafra?chissement avec -f.\n Pas de patch suivant\n Aucun patch retir?\n Aucun patch n'est appliqu?\n Aucun patch dans la s?rie\n Le patch %s ne contient rien\n Le patch %s est maintenant au sommet\n L'option ? -P ? ne peut ?tre utilis? que lors de l'import d'un seul patch.\n Les options ?--combine?, ?--snapshot? et ?-z? ne peuvent pas ?tre combin?es.\n Le patch %s existe d?j? dans la s?rie.\n Le patch %s semble vide, enlev?\n Le patch %s semble vide. Il a ?t? appliqu?.\n Le patch %s peut ?tre appliqu? ? l'envers\n Le patch %s ne s'applique pas proprement (forcez l'application avec -f)\n Le patch %s n'existe pas ; patch vide appliqu?\n Le patch %s n'existe pas\n Le patch %s ne se retire pas proprement (rafraichissez le, ou forcez avec -f)\n Le patch %s existe d?j?, veuillez choisir un nom diff?rent\n Le patch %s existe d?j?, veuillez choisir un nouveau nom\n Le patch %s existe d?j?\n Le patch %s existe. Utilisez -f pour le remplacer.\n Le patch %s n'est pas appliqu?\n Le patch %s est actuellement appliqu?\n Le patch %s n'est pas appliqu?\n Le patch %s n'est pas dans la s?rie\n Le patch %s est maintenant au sommet\n Patch %s inchang?\n Le patch %s doit ?tre rafraichi au pr?alable.\n Le patch %s n'est pas appliqu? avant %s\n. Patch %s renomm? en %s\n Les en-t?tes des patches diff?rent :\n Les patches %s ont des sujets dupliqu?s.\n Veuillez utiliser -d {o|a|n} pour sp?cifier quel(s) en-t?te(s) conserver.\n Patch %s rafra?chi\n Patch %s retir?\n Retrait de %s\n Suppression des espaces ? la fin de la ligne %s de %s
 Suppression des espaces ? la fin des lignes %s de %s
 En renommant %s en %s : %s
 Le renommage de %s en %s a ?chou?\n En-t?te du patch %s remplac?\n Remplacement du patch %s avec la nouvelle version\n SYNOPSIS : %s [-p num] [-n] [patch]
 La section %%prep de %s a ?chou? ; les r?sultats sont peut-?tre incomplets\n L'option -v montre les affichages de rpm\\n Les m?ta-donn?es de quilt dans %s sont d?j? au format %s ; rien ? faire\n Les m?ta-donn?es de quilt dans cet arbre de travail sont au format 
v%s, mais cette version de quilt ne peut traiter que jusqu'au 
format %s (inclus). Veuillez retirer vos patches avec la version 
utilis?e pour les appliquer avant d'installer une version plus ancienne.\n Le patch au sommet %s doit ?tre rafraichi au pr?alable.\n Votre arbre a ?t? cr?? par une vieille version de quilt. Veuillez 
utiliser ? quilt upgrade ?.\n USAGE : %s {-s|-u} section fichier [< remplacement]
 Impossible d'extraire une ligne de sujet de %s\n D?sarchivage de %s\n Usage : quilt [--trace[=verbose]] [--quiltrc=XX] commande [-h] ... Usage : quilt add [-P patch] {fichier} ...\n Usage : quilt annotate [-P patch] {fichier}\n Usage : quilt applied [patch]\n Usage : quilt delete [-r] [--backup] [patch|-n]\n Usage : quilt diff [-p n|-p ab] [-u|-U num|-c|-C num] [--combine patch|-z] [-R] [-P patch] [--snapshot] [--diff=utilitaire] [--no-timestamps] [--no-index] [--sort] [--color] [fichier ...]\n Usage : quilt edit {fichier} ...\n Usage : quilt files [-v] [-a] [-l] [--combine patch] [patch]\n Usage : quilt fork [nouveau_nom]\n Usage : quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [patch]\n Usage : quilt grep [-h|options] {motif}\n Usage : quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [patch]\n Usage : quilt new {nom_de_patch}\n Usage : quilt next [patch]\n Usage : quilt patches [-v] {fichier}\n Usage : quilt pop [-afRqv] [num|patch]\n Usage : quilt previous [-n] [patch]\n Usage : quilt rename [-P patch] nouveau_nom\n Usage : quilt series [-v]\n Usage : quilt snapshot [-d]\n Usage : quilt top\n Usage : quilt unapplied [patch]\n Usage : quilt upgrade\n Attention: un patch plus recent modifie des fichiers communs ? %s\n Attention : espaces ? la fin de la ligne %s de %s
 Attention : espaces ? la fin des lignes %s de %s
 