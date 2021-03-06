??    ?      ?  ?   L	      `  ?   a  Z   V  ~  ?  ?  0  ?    }  ?  ?   ;  m   ?  r   T  ?   ?  ?  ?  n  h  ?   ?  [   ?  `   -  N   ?  \   ?  k  :  |  ?$  p  #+  ?  ?-  @   G/  '  ?/    ?0     ?1     ?1  %   ?1  *   2     G2  6   [2     ?2  B   ?2  E   ?2  L   93     ?3     ?3  $   ?3  E   ?3  !   4     54     M4  0   c4     ?4      ?4  -   ?4     ?4     5  ,   75  !   d5     ?5      ?5     ?5     ?5      ?5     6     /6     O6     l6     ?6  -   ?6      ?6  %   ?6  #   7     ?7  0   T7  2   ?7  $   ?7     ?7  H   ?7     A8     Q8     d8     y8     ?8     ?8  =   ?8  D   ?8  $   ;9  (   `9  '   ?9  !   ?9  +   ?9  .   ?9     .:  B   H:  9   ?:  3   ?:     ?:  #   ;     7;     M;     m;     ?;     ?;     ?;  '   ?;  &   ?;     #<     <<  ,   T<  A   ?<     ?<     ?<     ?<  0   ?<  1   0=     b=  #   y=     ?=  %   ?=  #   ?=  <   >  &   B>  O   i>  ?   ?>  3   ??  X   ??  ,   1@     ^@  @   u@  (   ?@  )   ?@     	A  0   (A  ?   YA     B  =   -B     kB  ]   ?B  *   ?B  d   C     xC     ?C  "   ?C  '   ?C     ?C  ?   D  )   ?D     ?D     E     4E      GE     hE  7   E  .   ?E  /   ?E  ?   F  N  G  g   `H  ?  ?H  ?  ?K    ?P  &  ?R    ?T  ?   ?U  ?   ?V  ?   `W  C  IX  ?  ?Z  ?  ?\  M   ^  ?   d^  S   _  t   U_  ?  ?_  ?  ?f  ?  So  ?  ?r  k   ?u  ?  ?u  C  rw     ?x     ?x  0   ?x  f   y  '   }y  d   ?y  :   
z  V   Ez  k   ?z  a   {     j{     ~{  2   ?{  ?   ?{  .   T|  5   ?|  6   ?|  I   ?|  <   :}  <   w}  S   ?}  -   ~  3   6~  K   j~  G   ?~  -   ?~  -   ,  7   Z  0   ?  F   ?  0   
?  0   ;?  @   l?  <   ??  R   ??  f   =?  7   ??  C   ܁  K    ?  $   l?  ]   ??  F   ??  #   6?  6   Z?  ?   ??  #   G?  2   k?  2   ??  A   ф  6   ?  $   J?  Y   o?  V   Ʌ  :    ?  9   [?  <   ??  B   ҆  `   ?  K   v?  $     ?   ??  T   m?  T     -   ?  Y   E?  6   ??  0   ։  -   ?  1   5?  *   g?  *   ??  B   ??  F    ?  7   G?     ?  3   ??  e   ҋ  0   8?  $   i?  !   ??  B   ??  B   ??  0   6?  C   g?  0   ??  ?   ܍  $   ?  t   A?  A   ??  ~   ??  e  w?  D   ݐ  ?   "?  ,   ??  -   ??  D   ?  0   ^?  1   ??  &   ??  8   ??  ?   !?  (   ??  I   ?  "   _?  e   ??  3   ??  l   ?  %   ??  #   ??  .   ӕ  2   ?  '   5?  ?   ]?  -    ?     N?      m?     ??  (   ??     Η  Y   ??  A   C?  A   ??     \   +   %       6          3   R       ?      U   J   N   :   }   ?       Y   a   I   Z   ?   C           n   _      O   T       "   ?      ?   8   ?         ~   o   h   d          9   ?       M   ?      F       t          ,   v          u   B       5       b   V       ?          ?                         X      .       ?   l   ^   $       ?   -   G   !   <   W       H       r   S       1      y      z   @             g   ?   {   ?               [          )   *       /   #   P           ?       7           j   e   k   ?   4   q   A   
          ;              Q       ?   x       w   f      |   ]   &             0   '       ?   ?          i      K   	       >                     E   ?   s   (       D           =   L   c   2   p   m   `      ?    
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
Refreshes the specified patch, or the topmost patch by default.
Documentation that comes before the actual patch in the patch file is
retained.

It is possible to refresh patches that are not on top.  If any patches
on top of the patch to refresh modify the same files, the script aborts
by default.  Patches can still be refreshed with -f.  In that case this
script will print a warning for each shadowed file, changes by more
recent patches will be ignored, and only changes in files that have not
been modified by any more recent patches will end up in the specified
patch.

-p n	Create a -p n style patch (-p0 or -p1 supported).

-p ab	Create a -p1 style patch, but use a/file and b/file as the
	original and new filenames instead of the default
	dir.orig/file and dir/file names.

-u, -U num, -c, -C num
	Create a unified diff (-u, -U) with num lines of context. Create
	a context diff (-c, -C) with num lines of context. The number of
	context lines defaults to 3.

-z[new_name]
	Create a new patch containing the changes instead of refreshing the
	topmost patch. If no new name is specified, \`-2' is added to the
	original patch name, etc. (See the fork command.)

--no-timestamps
	Do not include file timestamps in patch headers.

--no-index
	Do not output Index: lines.

--diffstat
	Add a diffstat section to the patch header, or replace the
	existing diffstat section.

-f	Enforce refreshing of a patch that is not on top.

--backup
	Create a backup copy of the old version of a patch as patch~.

--sort	Sort files by their name instead of preserving the original order.

--strip-trailing-whitespace
	Strip trailing whitespace at the end of lines.
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
 Appended text to header of patch %s\n Applied patch %s (forced; needs refresh)\n Applying patch %s\n Can only refresh the topmost patch with -z currently\n Cannot add symbolic link %s\n Cannot diff patches with -p%s, please specify -p0 or -p1 instead\n Cannot refresh patches with -p%s, please specify -p0 or -p1 instead\n Cannot use --strip-trailing-whitespace on a patch that has shadowed files.\n Commands are: Conversion failed\n Converting meta-data to version %s\n Could not determine the envelope sender address. Please use --sender. Delivery address `%s' is invalid
 Diff failed, aborting\n Directory %s exists\n Display name `%s' contains unpaired parentheses
 Failed to back up file %s\n Failed to backup patch file %s\n Failed to copy files to temporary directory\n Failed to create patch %s\n Failed to import patch %s\n Failed to insert patch %s into file series\n Failed to patch temporary files\n Failed to remove patch %s\n Failed to remove patch file %s\n File %s added to patch %s\n File %s exists\n File %s is already in patch %s\n File %s is located below %s\n File %s is not being modified\n File %s is not in patch %s\n File %s may be corrupted\n File %s modified by patch %s\n File series fully applied, ends at patch %s\n Fork of patch %s created as %s\n Fork of patch %s to patch %s failed\n Importing patch %s (stored as %s)\n Importing patch %s\n Interrupted by user; patch %s was not applied.\n Introduction has no subject header (saved as %s)\n Introduction has no subject header\n Introduction saved as %s\n More recent patches modify files in patch %s. Enforce refresh with -f.\n No next patch\n No patch removed\n No patches applied\n No patches in series\n Nothing in patch %s\n Now at patch %s\n Option \`-P' can only be used when importing a single patch\n Options \`--combine', \`--snapshot', and \`-z' cannot be combined.\n Patch %s already exists in series.\n Patch %s appears to be empty, removing\n Patch %s appears to be empty; applied\n Patch %s can be reverse-applied\n Patch %s does not apply (enforce with -f)\n Patch %s does not exist; applied empty patch\n Patch %s does not exist\n Patch %s does not remove cleanly (refresh it or enforce with -f)\n Patch %s exists already, please choose a different name\n Patch %s exists already, please choose a new name\n Patch %s exists already\n Patch %s exists. Replace with -f.\n Patch %s is applied\n Patch %s is currently applied\n Patch %s is not applied\n Patch %s is not in series\n Patch %s is now on top\n Patch %s is unchanged\n Patch %s needs to be refreshed first.\n Patch %s not applied before patch %s\n Patch %s renamed to %s\n Patch headers differ:\n Patches %s have duplicate subject headers.\n Please use -d {o|a|n} to specify which patch header(s) to keep.\n Refreshed patch %s\n Removed patch %s\n Removing patch %s\n Removing trailing whitespace from line %s of %s
 Removing trailing whitespace from lines %s of %s
 Renaming %s to %s: %s
 Renaming of patch %s to %s failed\n Replaced header of patch %s\n Replacing patch %s with new version\n SYNOPSIS: %s [-p num] [-n] [patch]
 The %%prep section of %s failed; results may be incomplete\n The -v option will show rpm's output\n The quilt meta-data in %s are already in the version %s format; nothing to do\n The quilt meta-data in this tree has version %s, but this version of quilt can only handle meta-data formats up to and including version %s. Please pop all the patches using the version of quilt used to push them before downgrading.\n The topmost patch %s needs to be refreshed first.\n The working tree was created by an older version of quilt. Please run 'quilt upgrade'.\n Unable to extract a subject header from %s\n Unpacking archive %s\n Usage: quilt [--trace[=verbose]] [--quiltrc=XX] command [-h] ... Usage: quilt add [-P patch] {file} ...\n Usage: quilt annotate [-P patch] {file}\n Usage: quilt applied [patch]\n Usage: quilt delete [-r] [--backup] [patch|-n]\n Usage: quilt diff [-p n|-p ab] [-u|-U num|-c|-C num] [--combine patch|-z] [-R] [-P patch] [--snapshot] [--diff=utility] [--no-timestamps] [--no-index] [--sort] [--color] [file ...]\n Usage: quilt edit file ...\n Usage: quilt files [-v] [-a] [-l] [--combine patch] [patch]\n Usage: quilt fork [new_name]\n Usage: quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [patch]\n Usage: quilt grep [-h|options] {pattern}\n Usage: quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [patch]\n Usage: quilt new {patchname}\n Usage: quilt next [patch]\n Usage: quilt patches [-v] {file}\n Usage: quilt pop [-afRqv] [num|patch]\n Usage: quilt previous [patch]\n Usage: quilt refresh [-p n|-p ab] [-u|-U num|-c|-C num] [-z[new_name]] [-f] [--no-timestamps] [--no-index] [--diffstat] [--sort] [--backup] [--strip-trailing-whitespace] [patch]\n Usage: quilt rename [-P patch] new_name\n Usage: quilt series [-v]\n Usage: quilt snapshot [-d]\n Usage: quilt top\n Usage: quilt unapplied [patch]\n Usage: quilt upgrade\n Warning: more recent patches modify files in patch %s\n Warning: trailing whitespace in line %s of %s
 Warning: trailing whitespace in lines %s of %s
 Project-Id-Version: quilt 0.33
PO-Revision-Date: 2007-02-01 14:48+0900
Last-Translator: Yasushi SHOJI <yashi@atmark-techno.com>
Language-Team: Quilt
Language: 
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
 
最上位または指定されたパッチにファイル(複数可)を追加する。ファイルは編
集する前にかならず追加する必要がある。指定したパッチより上のパッチで変
更されているファイルは追加することができない。

-P パッチ
	ファイルを追加するパッチ
 
最上位のパッチに指定されたファイルを追加後、\$EDITOR (%s) を使って編集。
 
最上位パッチをフォークする。パッチをフォークするとは同じ内容のコピーを別の名前で作成することで、新しい名前を元の方にかわって使用する。これはパッチを変更しなければならないが、元のバージョンも残さなければならない場合に便利である(例: 別シリーズでの使用や過程の保存) 。典型的なコマンドの順番としては、fork、edit、refreshとなる。

new_nameが指定されなかった場合、フォークしたパッチ名は現在のパッチ名の後に \`-2' が付く。すでにパッチ名が -番号で終っている場合、番号の値が1増える (例: patch.diff、patch-2.diff、patch-3.diff)。
 
dot(1)を使って適用されているパッチの依存関係のグラフを作成する。あるパッ
チが他のパッチに依存している状態とは、両方のパッチが同じファイルを変更
している場合や変更箇所が重なった(オプション --lines使用時)を指す。特に
示されないかぎり、グラフは現在最上位のパッチが依存するパッチすべてを含
む。

最上位パッチ以外のパッチ名が指定された場合は、指定されたパッチのグラフ
を作成する。グラフは指定されたパッチが依存するすべてのパッチと、指定さ
れたパッチに依存するすべてのパッチを含む。

--all	適用されているすべてのパッチとその依存関係のグラフを作成する。
(適用されていないパッチは含まない)

--reduce
	Transitive edgeを省略する。tred(1)を参照。

--lines[=行数]
	パッチが変更する行から依存関係を計算する。行数が指定されない場
	合は2行分のコンテキストが使用される。

--edge-labels=files
	グラフ内のエッジにパッチが変更するファイル名を付ける。

-T ps	直接ポストスクリプトファイルを生成する。
 
全コマンド共通オプション:

--trace
	コマンドをbashのトレースモード(-x)で実行。内部デバッグ用。

--quiltrc file
	~/.quiltrc (存在しない場合は /etc/quiltrc) の代りに読み込む
	コンフィギュレーションファイルのを指定。内容の詳細については
	PDFのドキュメントを参照。特別なファイル名 \"-\"を使うと、
	コンフィギュレーションファイルを読み込まない。

--version
	バージョン情報を出力して終了。 
Quiltによって管理されているパッチはメタ情報以外のソースコードを再帰的
にgrepする。ファイル名が与えられなかった場合はディレクトリ内すべてが対
象となる。オプションについては grep(1)のマニュアルページを参照。

-h	このヘルプを表示。二重ダッシュ記号 (--)を使うことにより、grepに
-hを渡すことができる。ダッシュ記号で始まる検索パターンは2つ目の二重ダッ
シュ記号の後に渡すことができる。
 
現在作業中のツリーを作成した quiltと同じバージョンの quiltで \`quilt
pop -a'を実行し、すべてのパッチをはずしてください。または、%s ディレク
トリを削除し、最初からパッチをあて直してください。\n 
適用されているパッチの一覧を表示します。指定されたパッチがある場合は、
seriesファイル内のパッチ一覧の中から指定されたパッチまでを表示します。
 
適用されていないパッチを表示。パッチが指定された場合は、指定されたパッ
チ以降で適用されていないパッチを表示。
 
パッチが変更した行に註釈を付けて表示。適応されるのは、あてられているパッ
チのみ。

-P パッチ
	最上位のパッチまで処理を行なわず、指定されたパッチで処理を終了
 
最上位または指定されたパッチのヘッダを出力または変更する。

-a, -r, -e
	パッチのヘッダに追加 (-a) またはヘッダを変更 (-r)、$EDITOR (%s)を
	使って編集 (-e)する。オプションが指定されなかった場合はパッチの
	ヘッダを出力する。

--strip-diffstat
	diffstatの出力をヘッダから削除する。

--strip-trailing-whitespace
	末尾の空白文字をヘッダから削除する。

--backup
	古いバージョンのパッチのバックアップコピーをパッチ~として作成する。
 
最上位パッチ、または指定されたパッチが変更を加えるファイルの一覧を表示
する。

-a	適用されているすべてのパッチが変更するファイルの一覧を表示

-l	パッチ名を追加表示

-v	詳細で見やすい表示。

--combine パッチ
	最上位パッチから指定されたパッチまでのパッチ一覧を作成。パッチ
	名に \`-' を指定すると、一番最初に適用されているパッチを指定した
	ことになる。

 
指定されたファイルに対し、変更を行なうパッチのリストを表示。 (適用されて
いないパッチが指定されたファイルに対して変更を及ぼすかどうかを調べるには
発見的方法 (a heuristic)が用いられる。この方法は適用されているパッチを
スキャンするより大幅に遅い。

-v	詳細で見やすい表示。
 
最上位または指定されたパッチの次のパッチ名を表示。
 
最上位のパッチの前のパッチ名を表示。パッチ名が指定されたときは、指定
されたパッチの前のパッチ名を表示。
 
現在適用されているパッチスタックの最上位パッチ名を表示
 
seriesファイルに登録されている、すべてのパッチを表示。

-v	詳細で見やすい表示。

 
最上位または指定されたパッチに、指定されたファイルの差分を作成する。
ファイルが指定されなかった場合は、変更されたファイルすべてが含まれる。

-p n	-p n スタイルのパッチを作成 (-p0 または -p1がサポートされている)

-p ab	-p1スタイルのパッチを作成。ただしデフォルトの dir.orig/fileと
	dir/fileという名前ではなく、a/fileとb/fileをそれぞれオリジナル
	と新しいファイル名とする。

-u, -U num, -c, -C num
	num行のコンテキストでunified diff (-u, -U) を作成。num行のコン
	テキストで context diff (-c, -C)を作成。デフォルトのコンテキス
	ト行数は 3行。

--no-timestamps
	パッチヘッダにタイムスタンプを含めない。

--no-index
	Index: の行を出力しない。

-z	最上位、または指定されたパッチに関連した変更を、標準出力に表示。

-R	reverse diffを作成。

-P パッチ
	指定されたパッチ用に diffを作成。(デフォルトでは最上位のパッチ。)

--combine パッチ
	このパッチと -Pで指定されたパッチの間すべてのパッチの差分を合
	せて一つのパッチを作成。\`-' というパッチ名は最初に適用された
	パッチを指定するするのと同じ意味がある。

--snapshot
	スナップショットとの差分を作成 (参照 \`quilt snapshot -h')。

--diff=utility
	指定された utilityを使って差分を生成。オリジナルのファイルと新
	しいファイルを引数として utilityに渡される。

--color[=always|auto|never]
	シンタックスの色付け指定。

--sort	順番を保持せず、名前順にファイルを並び換える。
 
指定されたパッチを作成し直す。これをリフレッシュすると呼ぶ。デフォルト
では最上位パッチのリフレッシュを行う。パッチの先頭に書かれているドキュ
メントは保持される。

スタックの一番上以外のパッチもリフレッシュすることができる。リフレッシュ
するパッチとその上に乗っているパッチが、同じファイルを変更している場合
はデフォルトで異常終了する。-fオプションを付けることでリフレッシュを強
制することができるが、影になったファイルごとに quiltは警告を出す。最近
のパッチによる変更は無視されるため、それ以外の変更だけが指定されたパッ
チに反映される。

-p n	-p n スタイルのパッチを作成 (-p0 または -p1がサポートされている)。

-p ab	-p1スタイルのパッチを作成。ただしデフォルトの dir.orig/fileと
	dir/fileという名前ではなく、a/fileとb/fileをそれぞれオリジナル
	と新しいファイル名とする。

-u, -U num, -c, -C num
	num行のコンテキストでunified diff (-u, -U) を作成。num行のコン
	テキストで context diff (-c, -C)を作成。デフォルトのコンテキス
	ト行数は 3行。

-z[新しい名前]
	一番上のパッチをリフレッシュせずに、新しいパッチを作成する。も
	し新しい名前が与えられない場合は、\`-2'が元のパッチ名に付加さ
	れる。(forkコマンド参照)

--no-timestamps
	パッチヘッダにタイムスタンプを含めない。

--no-index
	Index: の行を出力しない。

--diffstat
	diffstatのセクションをパッチの先頭部分に追加、または既存の 
	diffstatセクションを上書きする。

-f	スタックの一番上にないパッチのリフレッシュを強要する。

--backup
	バックアップ用のコピーとして古いバージョンのパッチをパッチ~の
	形で作成する。

--sort	順番を保持せず、名前順にファイルを並び換える。

--strip-trailing-whitespace
	末尾の空白文字を削除する。
 
適用されているパッチスタックからパッチをはずす。オプションが無い場合は
最上位パッチをはずす。数字が指定されたときは、指定された数のパッチをは
ずす。パッチ名が指定されたときは、指定されたパッチが最上位パッチになる
まで、その上に積まれているパッチをはずしていく。シェルのファイル名補完
機能を有効に使うために、パッチ名の前に patches/を付けて指定することも
可能。

-a	適用されている、すべてのパッチをはずす。

-f	問題があるパッチでも、処理を進める。バックアップファイルを使って、
	パッチが適用される前の状態に復旧する。

-R	必ずパッチが正常にはずせるか検証する (タイムスタンプのチェックに
	依存しない)

-q	表示を抑制。

-v	詳細に表示。
 
指定されたパッチ、または最上位のパッチをシリーズファイルから削除する。
パッチがすでに適用されている場合は、最初にパッチを外す。( 現状、最上位
のパッチしか削除することはできない。)

-n	最上位パッチや指定されたパッチではなく、最上位パッチの次のパッチを
	削除する。

-r	シリーズファイルからパッチを消すときに、patchesディレクトリからも
	削除する。

--backup
	パッチを削除せず、パッチ~に名前を変更します。オプション\`-r'が
	有効ではないときは無視される。
 
最上位または指定されたパッチの名前を変更する

-P patch
	名前を変更する patch
 
現在の作業状態のスナップショットを作成する。スナップショットを作成した
後、ツリーはいつものように変更することが可能。パッチを pushしたり pop
することができる。スナップショットへの diffは、\`quilt diff
--snapshot'とすることで生成できる。

-d	現在のスナップショットを削除。

 
作業ツリーにある古いバージョンのメタデータを新しいバージョンにアップグ
レードする。このコマンドは、quiltのメタデータフォーマットが変更された
場合のみ必要。変更が確認された場合、quiltから \`quilt upgrade'の実行が
要求される。
        quilt --version %s: 混乱しました
 パッチ %s のヘッダに追加しました\n パッチ %s を適用しました (強制適用したために、リフレッシュが必要です)\n パッチ %s を適用しています\n -zオプションがある場合、最上位パッチ以外のリフレッシュはできません\n シンボリックファイル %s は追加できません -p%s でパッチの差分はとれません。-p0か -p1を指定してください\n -p%s ではリフレッシュすることができません。-p0または -p1を指定してください\n --strip-trailing-whitespace は影になっているファイルがある場合は使えません コマンド一覧: 変更に失敗しました\n メタデータを version %s に変更中です\n エンベロープの送信者アドレスを確定できませんでした。--senderオプション
を使用してください。 配送先のアドレス `%s' が不正です
 差分に失敗しました。異常終了します\n ディレクトリ %s は、すでに存在します\n 表示用の名前 `%s' が対にならない括弧を含んでいます
 ファイル %s のバックアップに失敗しました\n ファイル %s のバックアップに失敗しました\n テンポラリディレクトリへのファイルコピーに失敗しました\n パッチ %s の作成に失敗しました\n パッチ %s の取り込みに失敗しました\n seriesファイルへのパッチ %s の書き込みに失敗しました\n テンポラリファイルへのパッチ適用に失敗しました\n パッチ %s の削除に失敗しました\n パッチ %s の削除に失敗しました\n ファイル %s をパッチ %s に追加しました\n ファイル %s は、すでに存在します\n ファイル %s は、すでにパッチ %s に含まれています\n ファイル %s は、%s 以下にあります\n ファイル %s は変更されていません\n ファイル %s は、パッチ %s に含まれていません\n ファイル %s は壊れている可能性があります\n ファイル %s は、パッチ %s によってすでに変更されています\n seriesファイルのパッチはすべて適用されています。最終パッチは %s です。\n パッチ %s の分岐で %s が作成されました\n パッチ %s からパッチ %s への分岐に失敗しました\n パッチ %s を取り込んでいます (%s として保存されます)\n パッチ %s を取り込みます\n ユーザによって中断されました。パッチ %s は適用されていません。\n 序文に件名がありません(%s として保存されました)\n 序文に件名がありません\n 序文は %s という名前で保存されました\n より最近のパッチがパッチ %s のファイルに変更を加えています。リフレッシュを実行する場合は -f オプションを使用してください。\n 次のパッチはありません\n 適用されているパッチはありません\n 適用されているパッチはありません\n シリーズに登録されているパッチがありません\n パッチ %s にはなにも含まれていません\n 現在位置はパッチ %s です\n オプション \`-P'は、パッチを一つだけ取り込むときのみ有効です\n オプション \`--combine'と \`--snapshot'、 \`-z'は同時に使えません。\n パッチ %s は、すでに seriesの中にあります\n パッチ %s は、空のようです。はずします\n パッチ %s は空のようですが、適用しました\n パッチ %s は、反転して適用することができます\n パッチ %s が適用できません (強制適用する場合は -fを付けてください)\n パッチ %s は存在しません。空のパッチを適用しました\n パッチ %s が存在しません\n パッチ %s を、正常にはずすことができません (リフレッシュするか -fを付
けてはずしてください)\n パッチ %s はすでに存在します。新しい名前を選んでください\n パッチ %s はすでに存在します。新しい名前を選んでください\n パッチ %s は、すでに存在します\n パッチ %s は、すでに存在します。-fで置き換えることができます\n パッチ %s は、すでに適用されています\n パッチ %s は現在適用されています\n パッチ %s は適用されていません\n パッチ %s は seriesの中にありません\n パッチ %s を最上位にしました\n パッチ %s に変更はありません\n 最初に、パッチ %s のリフレッシュが必要です。\n パッチ %s は、パッチ %s の前に適用されていません\n パッチ %s から %s へ名前を変更しました\n パッチヘッダの差異:\n パッチ %s の件名が重複しています。\n どのパッチヘッダを残すか、オプション -d {o|a|n}を使って指定してください パッチ %s をリフレッシュしました\n パッチ %s を削除しました\n パッチ %s をはずします\n %2$s の %1$s 行目末尾にある空白文字を削除します
 %2$s の %1$s 行目末尾にある空白文字を削除します
 %s から %s へ名前を変更しました: %s
 パッチ %s から %s への名前の変更に失敗しました\n パッチ %s のヘッダを変更しました\n パッチ %s を新しいバージョンに置き換えます\n 書式: %s [p num] [-n] [パッチ]
 %%prepセクションの解析に失敗しました。完全に作業が完了していない場合があります\n -vオプションを使って、rpmの出力を表示できます %s 内の quilt メタデータはすでに version %s フォーマットのため、処理する必要がありません。\n このツリー内にはバージョン %sの quiltメタデータが存在します。しかしこ
のバージョンの quiltでは、バージョン %s までのメタデータしかサポートし
ていません。ダウングレードする前に、pushしたバージョンの quiltを使って、
すべてのパッチを pop してください。\n 最上位パッチのリフレッシュが最初に必要です。\n 現在作業中のディレクトリは古いバージョンの quiltによって作られたものです。'quilt upgrade'を実行してください。\n %s から件名を取り出せません。\n アーカイブ %s を展開しています\n 使い方: quilt [--trace[=verbose]] [--quiltrc=XX] command [-h] ... 使い方: quilt add [-P パッチ] {file} ...\n 使い方: quilt annotate [-P パッチ] {file}\n 使い方: quilt applied [パッチ]\n 使い方: quilt delete [-r] [--backup] [パッチ|-n]\n 使い方: quilt diff [-p n|-p ab] [-u|-U 数|-c|-C 数] [--combine パッチ|-z] [-R] [-P パッチ] [--snapshot] [--diff=utility] [--no-timestamps] [--no-index] [--sort] [--color] [ファイル ...]\n 使い方: quilt edit ファイル ...\n 使い方: quilt files [-v] [-a] [-l] [--combine パッチ] [パッチ]\n 使い方: quilt fork [new_name]\n 使い方: quilt graph [--all] [--reduce] [--lines[=num]] [--edge-labels=files] [-T ps] [パッチ]\n 使い方: quilt grep [-h|options] {パターン}\n 使い方: quilt header [-a|-r|-e] [--backup] [--strip-diffstat] [--strip-trailing-whitespace] [パッチ]\n 使い方: quilt new {パッチ名}\n 使い方: quilt next [パッチ]\n 使い方: quilt patches [-v] {ファイル}\n 使い方: quilt pop [-afRqv] [数字|パッチ]\n 使い方: quilt previous [パッチ]\n 使い方: quilt refresh [-p n|-p ab] [-u|-U num|-c|-C num] [-z[新しい名前]] [-f] [--no-timestamps] [--no-index] [--diffstat] [--sort] [--backup] [--strip-trailing-whitespace] [パッチ]\n 使い方: quilt rename [-P patch] new_name\n 使い方: quilt series [-v]\n 使い方: quilt snapshot [-d]\n 使い方: quilt top\n 使い方: quilt unapplied [パッチ]\n 使い方: quilt upgrade\n 警告: 最近のパッチが、パッチ %s 内のファイルを変更しています\n 警告: %2$s の %1$s 行目末尾に空白文字があります
 警告: %2$s の %1$s 行目末尾に空白文字があります
 