????  =?  ?    /?? \ ?*threea.res@@@?+include.res@?)deref.res@@?)break.res@@@@@@@?4line_before_last.res@?,iterator.res@@?+arraysz.res@@@?*format.res?
  -INCORRECT:diff token: "one %d two\n" VS "blah"
File "tests/format.c", line 2, column 9,  charpos = 23
    around = '"one %d two\n"', whole content =   printf("one %d two\n", 1);
File "tests/format.res", line 2, column 9,  charpos = 23
    around = '"blah"', whole content =   printf("blah", 1);

    diff (result(<) vs expected_result(>)) = 
    @@ -1,5 +1,5 @@
     int main () {
    -  printf("one %d two\n", 1);
    -  printf("one %d two %d three\n", 1, 2);
    +  printf("blah", 1);
    +  printf("blah", 1, 2);
       printf("one two three\n");
     }
@?-doublepos.res@@?(cr1a.res@?'spl.res@?5metastatement_for.res@@?,addfield.res@@@?+format2.res?	TPROBLEM
   exn = Yes_prepare_ocamlcocci.LinkFailure("/tmp/ocaml_cocci_6bd13a.cmxs")
@?2type_annotated.res@@?&ty.res@?-positionc.res@?)ptrar.res@@?+metahex.res?
  VINCORRECT:diff token: f VS }
File "tests/metahex.c", line 2, column 2,  charpos = 15
    around = 'f', whole content =   f(3);
File "tests/metahex.res", line 2, column 0,  charpos = 13
    around = '}', whole content = }

    diff (result(<) vs expected_result(>)) = 
    @@ -1,4 +1,2 @@
     int main() {
    -  f(3);
    -  g(0x03);
     }
@@@?7pb_distribute_type4.res@?)exitp.res?	pPROBLEM
   exn = Failure("Semantic patch uses python, but Coccinelle has been compiled without Python support")
?(fnty.res@@?+varargs.res@?*test_s.res@?(loop.res@@@?;initializer_many_fields.res@?(rptr.res@@@?(hil1.res@?+minenum.res@@?-remstruct.res@@@?(cptr.res@?*ifdef2.res@@?*expopt.res@@?+nestone.res@@@?-video1bis.res@?-iterprint.res@@?.badtypedef.res@?/branchparen.res@?2addbeforeafter.res@@?*return.res@@@?+addelse.res@@?0double_lines.res@@?2minusdots_ver1.res@@@?+typedef.res@?)test6.res@@?1comment_brace.res@@?)test1.res@?+localid.res@@?)bigin.res@@@?*addif2.res@@?/gcc_min_max.res@@?0expopt3_ver1.res@?-ifreturn4.res@@?*braces.res@@@?(getc.res@@?(stmt.res@@@?+retval2.res@@?-list_test.res@?0metaruleelem.res@@@@@@?-wierdinit.res?
  Xseems incorrect, but only because of code that was not parsablediff token: dev_link_t VS struct
File "tests/wierdinit.c", line 4, column 1,  charpos = 27
    around = 'dev_link_t', whole content = 	dev_link_t *link;
File "tests/wierdinit.res", line 4, column 1,  charpos = 27
    around = 'struct', whole content = 	struct pcmcia_device *link;
?1pb_params_iso.res@@?+devlink.res@@?-ifdefmeta.res@?/longlongint.res@@?,ty_tyexp.res@@?'unl.res@@?(anon.res@@@?'ty1.res@?-inclifdef.res@?.introbrace.res@@@?(void.res@?)ktype.res@?/topdec_ver1.res@@?0strangeorder.res@?+expopt2.res@?,argument.res@@?(pmac.res@?.proto_ver1.res@@?*test12.res@@?&p9.res?
  ?INCORRECT:diff token: v0 VS v2
File <COCCIOUTPUTFILE>, line 1, column 10,  charpos = 10
    around = 'v0', whole content = int f(int v0, int v1, int x) {
File "tests/p9.res", line 1, column 10,  charpos = 10
    around = 'v2', whole content = int f(int v2, int v3, int x) {

    diff (result(<) vs expected_result(>)) = 
    @@ -1,3 +1,3 @@
    -int f(int v0, int v1, int x) {
    +int f(int v2, int v3, int x) {
       return x;
     }
@@?-starprint.res@?(delp.res@@?(stm8.res@@@?(stm3.res@@?,twomatch.res@@@@?.define_exp.res@?3gilles-question.res@@?(dbg1.res?
  ?INCORRECT:diff token: E VS (
File <COCCIOUTPUTFILE>, line 5, column 2,  charpos = 75
    around = 'E', whole content = 		E = NULL;("PCI");
File "tests/dbg1.res", line 4, column 5,  charpos = 72
    around = '(', whole content = 		DBG("PCI");

    diff (result(<) vs expected_result(>)) = 
    @@ -1,6 +1,6 @@
     
     static inline void alloc_resource(struct pci_dev *dev, int idx)
     {
    -		DBG
    -		E = NULL;("PCI");
    +		DBG("PCI");
    +		E = NULL;
     }
@?-gotobreak.res@@@?'ws2.res@?)const.res@?*signed.res@@@?*dropbr.res@@?,nameless.res@@?(tern.res@@?.justremove.res@?*badexp.res@?'com.res@?3return_implicit.res@@@@@?)type1.res@@?)proto.res@@?,comments.res@?1disjexpr_ver1.res@@?,multidec.res@?'opt.res@@@@@?0const_adding.res@?*retval.res@@?/constructor.res@@@?2typedef_double.res@?+condexp.res@@?.array_init.res@?8labels_metastatement.res@?(rets.res@@@?'dec.res@?3toplevel_struct.res@@@?*ifdef3.res@@?-type_ver1.res@@?(zero.res@@?+declinv.res?	DPROBLEM
   exn = Unix.Unix_error(20, "stat", "tests/declinv.cocci")
@@?*addtoo.res@?2struct_metavar.res@@?(four.res@@?-null_type.res@@@?,cst_null.res@?,cs_check.res@?*ktype2.res@@@@?)test7.res@?,constrem.res@@@?)test2.res@?-multitype.res@@?(defe.res@@?(cast.res@?,cast_iso.res@@?&fp.res@?(post.res@@@?0expopt3_ver2.res@@@@@@?/remove_call.res@?1bad_ptr_print.res@@@?'ip2.res@@@?'csw.res@@?(nest.res@@@@?1scope_problem.res?
  ?INCORRECT:diff token: } VS a
File <COCCIOUTPUTFILE>, line 4, column 2,  charpos = 42
    around = '}', whole content =   }
File "tests/scope_problem.res", line 4, column 4,  charpos = 44
    around = 'a', whole content =     a = 2;

    diff (result(<) vs expected_result(>)) = 
    @@ -1,7 +1,6 @@
     void main(int i) {
       if(1) {
         int a;
    +    a = 2;
       }
    -
    -
     }
?)endif.res@@?'lid.res@@?&of.res@@?(decl.res@?6optional_qualifier.res@@?+spacing.res@@@@?.ifdefmeta1.res@@?/topdec_ver2.res@@?+expopt3.res@?*strid2.res@@?*doundo.res@?.proto_ver2.res@@@?/macro_int16.res@@?1mini_null_ref.res@@?6incompatible_value.res@@?+compare.res@@@?0a_and_e_ver1.res@?,addtrace.res?	EPROBLEM
   exn = Unix.Unix_error(20, "stat", "tests/addtrace.cocci")
?(stm4.res@@@?*jloop1.res?	?PROBLEM
   exn = Failure("minus: parse error: \n = File \"tests/jloop1.cocci\", line 10, column 3,  charpos = 129\n    around = '...>', whole content =    ...>\n")
@?/protoassert.res@@?+fn_todo.res@@@@?,ifreturn.res@@?-same_expr.res@?(ifbr.res@@@?(mdec.res@@?.decl_split.res?
  jINCORRECT:diff token: int VS }
File "tests/decl_split.c", line 2, column 8,  charpos = 27
    around = 'int', whole content =         int x, y;
File "tests/decl_split.res", line 2, column 0,  charpos = 19
    around = '}', whole content = }

    diff (result(<) vs expected_result(>)) = 
    @@ -1,3 +1,2 @@
     int func(int i) { 
    -        int x, y;
     }
?*inhmet.res@?/multi_func1.res?	?PROBLEM
   exn = Failure("minus: parse error: \n = File \"tests/multi_func1.cocci\", line 12, column 2,  charpos = 102\n    around = 'fn2', whole content =   fn2(...) {\n")
@?*inline.res@?+ifields.res@@@?+destroy.res@@@@?'kmc.res@?)ifadd.res@@?+julia10.res@@?1disjexpr_ver2.res@@?*sizeof.res@@?*incdir.res?
  ?INCORRECT:diff token: x VS 12
File "tests/incdir.c", line 4, column 6,  charpos = 46
    around = 'x', whole content =   foo(x);
File "tests/incdir.res", line 4, column 6,  charpos = 46
    around = '12', whole content =   foo(12);

    diff (result(<) vs expected_result(>)) = 
    @@ -1,5 +1,5 @@
     #include "sub/incdir2.c"
     
     int main () {
    -  foo(x);
    +  foo(12);
     }
@?)cards.res@?(bug1.res@@?.decl_space.res@@?)endnl.res@?)stm10.res@?/test10_ver1.res@@@?.multichars.res@@@@?-minusdots.res@?*comadd.res@@?)exitc.res?	TPROBLEM
   exn = Yes_prepare_ocamlcocci.LinkFailure("/tmp/ocaml_cocci_650de7.cmxs")
@@?&62.res@?&sp.res@?*ifdef4.res@?+expnest.res@@?-type_ver2.res?	?INCORRECT:PB parsing only in generated-file
    diff (result(<) vs expected_result(>)) = 
    @@ -1,5 +1,5 @@
     int foo() {
    -  int[10] *x;
    +  int *x[10];
       return 0;
     }
     
?'ifd.res@?(type.res@?*incpos.res?	pPROBLEM
   exn = Failure("Semantic patch uses python, but Coccinelle has been compiled without Python support")
@?*switch.res@@?)debug.res@@?*regexp.res@@@?*protox.res@@?&hd.res@?-multivars.res@?*addaft.res@@?+deftodo.res@@?*double.res@@?+dowhile.res@?,isococci.res@@@?)test8.res@?)fnptr.res@@@?)test3.res@@?)bugon.res@?0doubleswitch.res@@?+badwhen.res@@@?+nestseq.res@@?-ifreturn6.res@@@?*static.res@@?.array_size.res@?'inc.res@@?1fix_flow_need.res@@?.end_commas.res@@?.distribute.res@@@@?)foura.res@@?.param_ver1.res@@?'exp.res@@@?1match_no_meta.res@@@?*proto2.res@?+isotest.res@@@@?.stm10_ver1.res@?)addif.res@@?+headers.res@@?.ifdefmeta2.res@@?*inhpos.res@@?(noty.res@@@?4metastatement_if.res@?,isotest2.res@@?-overshoot.res@?&na.res@?'tup.res@@@@?*posiso.res@@@?+constty.res@?(stm5.res@@@?0useless_cast.res@@?0param_to_exp.res?	IPROBLEM
   exn = Unix.Unix_error(20, "stat", "tests/param_to_exp.cocci")
@?*topdec.res@@?0multitypedef.res@@?,disjexpr.res@?-decl_star.res@@?+badzero.res@@?+kmalloc.res@?*fields.res@@?-dropparam.res@@?(rcu3.res@?*before.res@?0print_return.res@?'not.res@@?-longconst.res@?&kr.res@@?&ab.res@@?&km.res@@?-structfoo.res@?/multiremove.res@@?'max.res@?)ifend.res@@?,longlong.res@@?%a.res@?.neststruct.res@@@?)edots.res@?+incpos1.res?	pPROBLEM
   exn = Failure("Semantic patch uses python, but Coccinelle has been compiled without Python support")
@@?6pb_distribute_type.res?	?INCORRECT:PB parsing only in generated-file
    diff (result(<) vs expected_result(>)) = 
    @@ -10,6 +10,6 @@
     }
     
     int foo() {
    -  int[45] *x;
    +  int (*x)[45];
       return 0;
     }
@?1double_switch.res@@?*disjid.res@?'fun.res@@?&b1.res@?+sizeptr.res@?*nocast.res@@@?7pb_distribute_type2.res?
  /INCORRECT:PB parsing only in generated-file
    diff (result(<) vs expected_result(>)) = 
    @@ -1,5 +1,5 @@
     int foo() {
    -  int* x;
    +  int *x;
       return 0;
     }
     
    @@ -10,6 +10,6 @@
     }
     
     int foo() {
    -  int x[45]*;
    +  int (*x)[45];
       return 0;
     }
@?(rem1.res@?4pb_parsing_macro.res@?&ip.res@@?(tyex.res@@?+fortype.res@@@?&if.res@@?*ifdef5.res@@@@?,reserved.res@@@?)serio.res?
  INCORRECT:diff token: init_MUTEX VS mutex_init
File "tests/serio.c", line 7, column 1,  charpos = 130
    around = 'init_MUTEX', whole content = 	init_MUTEX(&serio->drv_sem);
File "tests/serio.res", line 7, column 1,  charpos = 130
    around = 'mutex_init', whole content = 	mutex_init(&serio->new_lock);

    diff (result(<) vs expected_result(>)) = 
    @@ -4,5 +4,5 @@
     
     static void serio_init_port(struct serio *serio)
     {
    -	init_MUTEX(&serio->drv_sem);
    +	mutex_init(&serio->new_lock);
     }
@?'arg.res@?,dc_close.res@?*memory.res@@?(enum.res@?6test_unsigned_meta.res@?+smallfn.res@?*remaft.res?	CPROBLEM
   exn = Unix.Unix_error(20, "stat", "tests/remaft.cocci")
@?(vpos.res@?-substruct.res@@?/three_types.res@@@?.edots_ver1.res@?-const1bis.res@@?*typeof.res@?)test9.res@@?.pragmatest.res@@?)test4.res@@@@@?,retmacro.res@?4optional_storage.res@@@?-find_long.res@?-param_end.res@?*symbol.res@?'dbg.res?
  ?INCORRECT:diff token: else VS (
File <COCCIOUTPUTFILE>, line 8, column 2,  charpos = 133
    around = 'else', whole content = 		else pr = NULL;("PCI");
File "tests/dbg.res", line 7, column 5,  charpos = 130
    around = '(', whole content = 		DBG("PCI");

    diff (result(<) vs expected_result(>)) = 
    @@ -4,6 +4,6 @@
     	struct resource *pr, *r = &dev->resource[idx];
     
     	if (pr)
    -		DBG
    -		else pr = NULL;("PCI");
    +		DBG("PCI");
    +	else pr = NULL;
     }
@@?,twoproto.res@?)param.res@@@?.switchdecl.res@?0sizeof_julia.res@@@?*string.res@@@?.formatlist.res@?+bigrepl.res@?6const_implicit_iso.res@@?*julia7.res@@?'cst.res@?.match_init.res@?)decl2.res@@?.whitespace.res@@@@?)macro.res@@?(ifzz.res@?/const_array.res@@?1double_assign.res@@?(incl.res@@@?.ifdefmeta3.res@?'ben.res@@?&nl.res@@@@@?)local.res@?/pragmatest1.res@?+regexp2.res@@?*test10.res@?)strid.res@@?-inherited.res@@?)orexp.res@@?,typedef3.res?
  rINCORRECT:diff token: link VS p_dev
File <COCCIOUTPUTFILE>, line 7, column 29,  charpos = 137
    around = 'link', whole content = 	unsigned int iobase = info->link.io.BasePort1;
File "tests/typedef3.res", line 7, column 29,  charpos = 137
    around = 'p_dev', whole content = 	unsigned int iobase = info->p_dev->io.BasePort1;

    diff (result(<) vs expected_result(>)) = 
    @@ -4,7 +4,7 @@
     
     static void should_work(foo *info)
     {
    -	unsigned int iobase = info->link.io.BasePort1;
    +	unsigned int iobase = info->p_dev->io.BasePort1;
     }
     
     static void does_work(struct bluecard_info_t *info)
?*badpos.res?	?PROBLEM
   exn = Failure("rule starting on line 1: already tagged token:\nC code context\nFile \"tests/badpos.c\", line 5, column 30,  charpos = 139\n    around = 'reg_ptr', whole content = \t (int) -(((struct pt_regs *) reg_ptr)->orig_eax + 2));")
@?(stm6.res@@@?(stm1.res?	pPROBLEM
   exn = Failure("Semantic patch uses python, but Coccinelle has been compiled without Python support")
@@@?+partial.res@?)extra.res?	TPROBLEM
   exn = Yes_prepare_ocamlcocci.LinkFailure("/tmp/ocaml_cocci_0b2719.cmxs")
@?&ar.res@?+arparam.res@@@?)empty.res@?+oneline.res@@?/test11_ver1.res@@?+attradd.res@@?2inherited_ver1.res@?'eb1.res@@?&y2.res@@?-addbefore.res@@@?*xfield.res@?2struct_typedef.res@?'hex.res@@?)dropf.res@@?2comment_brace2.res@?)ifzer.res@@?'noa.res@@?3replace_typedef.res@?*notest.res@@?/initializer.res@?*retest.res@@?3bad_iso_example.res?
  ?INCORRECT:diff token: ( VS x
File "tests/bad_iso_example.c", line 2, column 6,  charpos = 19
    around = '(', whole content =   if ((x = 3)) return;
File "tests/bad_iso_example.res", line 2, column 6,  charpos = 19
    around = 'x', whole content =   if (x) return;

    diff (result(<) vs expected_result(>)) = 
    @@ -1,4 +1,4 @@
     int main() {
    -  if ((x = 3)) return;
    +  if (x) return;
     }
     
@@?.keep_comma.res@@?&b2.res@?)minfn.res@@@?0define_param.res@?7pb_distribute_type3.res?	?PROBLEM
   exn = Failure("line 7: index 53 53 already used\n")
?(tdnl.res@?/bad_typedef.res@?*lvalue.res@@?(rem2.res@@@@?'a3d.res@?&td.res@?&sw.res@?3delete_function.res@@?)boolr.res@?,oddifdef.res?
  ?INCORRECT:diff token: #else
 VS x
File <COCCIOUTPUTFILE>, line 10, column 0,  charpos = 114
    around = '#else
', whole content = #else
File "tests/oddifdef.res", line 10, column 2,  charpos = 116
    around = 'x', whole content =   x = 0;

    diff (result(<) vs expected_result(>)) = 
    @@ -7,8 +7,9 @@
         a = 5;
     
     #ifdef FOO
    +  x = 0;
     #else
    -
    +  x = 0;
     #endif
     }
     
    @@ -21,8 +22,9 @@
         a = 3;
     
     #ifdef FOO
    +  x = 0;
     #else
    -
    +  x = 0;
     #endif
     }
     
    @@ -35,7 +37,8 @@
     #endif
     
     #ifdef FOO
    +  x = 0;
     #else
    -
    +  x = 0;
     #endif
     }
@?2wierd_argument.res@?6toplevel_macrostmt.res@?)fnret.res@?*ifdef6.res@?*struct.res@@?,bitfield.res@@?*ifdef1.res@?.test5_ver1.res@@@@?-minstruct.res@?-bad_kfree.res@@?-null_bool.res?
  $INCORRECT:diff token: ) VS !=
File <COCCIOUTPUTFILE>, line 2, column 8,  charpos = 22
    around = ')', whole content =   if (12) return;
File "tests/null_bool.res", line 2, column 9,  charpos = 23
    around = '!=', whole content =   if (12 != NULL) return;

    diff (result(<) vs expected_result(>)) = 
    @@ -1,6 +1,6 @@
     int main () {
    -  if (12) return;
    -  if (a && 12 && b) return;
    +  if (12 != NULL) return;
    +  if (a && 12 != NULL && b) return;
       if (12) return;
       if (a && 12 && b) return;
       x = x + 20;
@?+bugloop.res@@@?,str_init.res@?'top.res@?'fsh.res@?2pb_tag_symbols.res@@@@@?(skip.res@@?)test5.res@@?+ifdef6a.res@@?)test0.res@?(befS.res@@?=labels_metastatement_ver1.res@@?3parameters_dots.res@@?*spaces.res@?*addif1.res@@?*constx.res@@?-ifreturn3.res@@@@?,castdecl.res@?,sizestar.res@@@@?,after_if.res@@?0shared_brace.res@@@@@@?2metastatement2.res@@@?'sis.res@@?+a_and_e.res@?-fieldsmin.res@@@@?.ifdefmeta4.res?	GPROBLEM
   exn = Unix.Unix_error(20, "stat", "tests/ifdefmeta4.cocci")
@?,metaline.res@@@@?-multiplus.res@@?*insdef.res@?+regexp3.res@@?*test11.res@@@@?,minenum1.res@@?(stm7.res?	pPROBLEM
   exn = Failure("Semantic patch uses python, but Coccinelle has been compiled without Python support")
@?*tydisj.res@@?(stm2.res@@