(* Yoann Padioleau
 *
 * Copyright (C) 2010, University of Copenhagen DIKU and INRIA.
 * Copyright (C) 2007, 2008 Ecole des Mines de Nantes
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License (GPL)
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * file license.txt for more details.
 *)

open Common

module TH = Token_helpers
module TV = Token_views_c
module LP = Lexer_parser

module Stat = Parsing_stat

open Parser_c

open TV

(*****************************************************************************)
(* Some debugging functions  *)
(*****************************************************************************)

let pr2, pr2_once = Common.mk_pr2_wrappers Flag_parsing_c.verbose_parsing

let pr2_cpp s =
  if !Flag_parsing_c.debug_cpp
  then Common.pr2_once ("CPP-" ^ s)


let msg_gen cond is_known printer s =
  if cond
  then
    if not (!Flag_parsing_c.filter_msg)
    then printer s
    else
      if not (is_known s)
      then printer s

(* In the following, there are some harcoded names of types or macros
 * but they are not used by our heuristics! They are just here to
 * enable to detect false positive by printing only the typedef/macros
 * that we don't know yet. If we print everything, then we can easily
 * get lost with too much verbose tracing information. So those
 * functions "filter" some messages. So our heuristics are still good,
 * there is no more (or not that much) hardcoded linux stuff.
 *)

let is_known_typdef =
    (fun s ->
      (match s with
      | "u_char"   | "u_short"  | "u_int"  | "u_long"
      | "u8" | "u16" | "u32" | "u64"
      | "s8"  | "s16" | "s32" | "s64"
      | "__u8" | "__u16" | "__u32"  | "__u64"
        -> true

      | "acpi_handle"
      | "acpi_status"
        -> true

      | "FILE"
      | "DIR"
        -> true

      | s when s =~ ".*_t$" -> true
      | _ -> false
      )
    )

(* note: cannot use partial application with let msg_typedef =
 * because it would compute msg_typedef at compile time when
 * the flag debug_typedef is always false
 *)
let msg_typedef s ii n =
  incr Stat.nTypedefInfer;
  msg_gen (!Flag_parsing_c.debug_typedef)
    is_known_typdef
    (fun s ->
      pr2_cpp
	(Printf.sprintf "TYPEDEF: promoting:(%d) %s on line %d" n s
	   (Ast_c.line_of_info ii))
	(*(Printf.sprintf "TYPEDEF: promoting: %s on line %d" s
	   (Ast_c.line_of_info ii))*)
    )
    s

let msg_maybe_dangereous_typedef s =
  if not (is_known_typdef s)
  then
    pr2
      ("PB MAYBE: dangerous typedef inference, maybe not a typedef: " ^ s)



let msg_declare_macro s =
  incr Stat.nMacroDecl;
  msg_gen (!Flag_parsing_c.debug_cpp)
    (fun s ->
      (match s with
      | "DECLARE_MUTEX" | "DECLARE_COMPLETION"  | "DECLARE_RWSEM"
      | "DECLARE_WAITQUEUE" | "DECLARE_WAIT_QUEUE_HEAD"
      | "DEFINE_SPINLOCK" | "DEFINE_TIMER"
      | "DEVICE_ATTR" | "CLASS_DEVICE_ATTR" | "DRIVER_ATTR"
      | "SENSOR_DEVICE_ATTR"
      | "LIST_HEAD"
      | "DECLARE_WORK"  | "DECLARE_TASKLET"
      | "PORT_ATTR_RO" | "PORT_PMA_ATTR"
      | "DECLARE_BITMAP"

          -> true
 (*
      | s when s =~ "^DECLARE_.*" -> true
      | s when s =~ ".*_ATTR$" -> true
      | s when s =~ "^DEFINE_.*" -> true
 *)

      | _ -> false
      )
    )
    (fun s -> pr2_cpp ("MACRO: found declare-macro: " ^ s))
    s


let msg_foreach s =
  incr Stat.nIteratorHeuristic;
  pr2_cpp ("MACRO: found foreach: " ^ s)


(* ??
let msg_debug_macro s =
  pr2_cpp ("MACRO: found debug-macro: " ^ s)
*)


let msg_macro_noptvirg s =
  incr Stat.nMacroStmt;
  pr2_cpp ("MACRO: found macro with param noptvirg: " ^ s)

let msg_macro_toplevel_noptvirg s =
  incr Stat.nMacroStmt;
  pr2_cpp ("MACRO: found toplevel macro noptvirg: " ^ s)

let msg_macro_noptvirg_single s =
  incr Stat.nMacroStmt;
  pr2_cpp ("MACRO: found single-macro noptvirg: " ^ s)




let msg_macro_higher_order s =
  incr Stat.nMacroHigherOrder;
  msg_gen (!Flag_parsing_c.debug_cpp)
    (fun s ->
      (match s with
      | "DBGINFO"
      | "DBGPX"
      | "DFLOW"
        -> true
      | _ -> false
      )
    )
    (fun s -> pr2_cpp ("MACRO: found higher ordre macro : " ^ s))
    s


let msg_stringification s =
  incr Stat.nMacroString;
  msg_gen (!Flag_parsing_c.debug_cpp)
    (fun s ->
      (match s with
      | "REVISION"
      | "UTS_RELEASE"
      | "SIZE_STR"
      | "DMA_STR"
        -> true
      (* s when s =~ ".*STR.*" -> true  *)
      | _ -> false
      )
    )
    (fun s -> pr2_cpp ("MACRO: found string-macro " ^ s))
    s

let msg_stringification_params s =
  incr Stat.nMacroString;
  pr2_cpp ("MACRO: string-macro with params : " ^ s)



let msg_apply_known_macro s =
  incr Stat.nMacroExpand;
  pr2_cpp ("MACRO: found known macro = " ^ s)

let msg_apply_known_macro_hint s =
  incr Stat.nMacroHint;
  pr2_cpp ("MACRO: found known macro hint = " ^ s)




let msg_ifdef_bool_passing is_ifdef_positif =
  incr Stat.nIfdefZero; (* of Version ? *)
  if is_ifdef_positif
  then pr2_cpp "commenting parts of a #if 1 or #if LINUX_VERSION"
  else pr2_cpp "commenting a #if 0 or #if LINUX_VERSION or __cplusplus"


let msg_ifdef_mid_something () =
  incr Stat.nIfdefExprPassing;
  pr2_cpp "found ifdef-mid-something"

let msg_ifdef_funheaders () =
  incr Stat.nIfdefFunheader;
  ()

let msg_ifdef_cparen_else () =
  incr Stat.nIfdefPassing;
  pr2_cpp("found ifdef-cparen-else")


let msg_attribute s =
  incr Stat.nMacroAttribute;
  pr2_cpp("ATTR:" ^ s)



(*****************************************************************************)
(* The regexp and basic view definitions *)
(*****************************************************************************)

(* opti: better to built then once and for all, especially regexp_foreach *)

let regexp_macro = Str.regexp
  "^[A-Z_][A-Z_0-9]*$"

(* linuxext: *)
let regexp_annot = Str.regexp
  "^__.*$"

(* linuxext: *)
let regexp_declare = Str.regexp
  ".*DECLARE.*"

(* linuxext: *)
let regexp_foreach = Str.regexp_case_fold
  ".*\\(for_?each\\|for_?all\\|iterate\\|loop\\|walk\\|scan\\|each\\|for\\)"

let regexp_typedef = Str.regexp
  ".*_t$"

let false_typedef = [
  "printk";
  ]


let ok_typedef s = not (List.mem s false_typedef)

let not_annot s =
  not (s ==~ regexp_annot)
let is_macro s =
  s ==~ regexp_macro
let not_macro s =
  not (is_macro s)




(*****************************************************************************)
(* Helpers *)
(*****************************************************************************)

(* ------------------------------------------------------------------------- *)
(* the pair is the status of '()' and '{}', ex: (-1,0)
 * if too much ')' and good '{}'
 * could do for [] too ?
 * could do for ','   if encounter ',' at "toplevel", not inside () or {}
 * then if have ifdef, then certainly can lead to a problem.
 *)
let (count_open_close_stuff_ifdef_clause: TV.ifdef_grouped list -> (int * int))=
 fun xs ->
   let cnt_paren, cnt_brace = ref 0, ref 0 in
   xs +> TV.iter_token_ifdef (fun x ->
     (match x.tok with
     | x when TH.is_opar x  -> incr cnt_paren
     | TOBrace _ -> incr cnt_brace
     | x when TH.is_cpar x  -> decr cnt_paren
     | TCBrace _ -> decr cnt_brace
     | _ -> ()
     )
   );
   !cnt_paren, !cnt_brace


(* ------------------------------------------------------------------------- *)
let forLOOKAHEAD = 30


(* look if there is a '{' just after the closing ')', and handling the
 * possibility to have nested expressions inside nested parenthesis
 *
 * todo: use indentation instead of premier(statement) ?
 *)
let rec is_really_foreach xs =
  let rec is_foreach_aux = function
    | [] -> false, []
    | TCPar _::TOBrace _::xs -> true, xs
      (* the following attempts to handle the cases where there is a
	 single statement in the body of the loop.  undoubtedly more
	 cases are needed.
         todo: premier(statement) - suivant(funcall)
       *)
    | TCPar _::TIdent _::xs -> true, xs
    | TCPar _::Tif _::xs -> true, xs
    | TCPar _::Twhile _::xs -> true, xs
    | TCPar _::Tfor _::xs -> true, xs
    | TCPar _::Tswitch _::xs -> true, xs
    | TCPar _::Treturn _::xs -> true, xs


    | TCPar _::xs -> false, xs
    | TOPar _::xs ->
        let (_, xs') = is_foreach_aux xs in
        is_foreach_aux xs'
    | x::xs -> is_foreach_aux xs
  in
  is_foreach_aux xs +> fst


(* ------------------------------------------------------------------------- *)
let set_ifdef_token_parenthize_info cnt x =
    match x with
    | TIfdef (tag, _)
    | TIfdefelse (tag, _)
    | TIfdefelif (tag, _)
    | TEndif (tag, _)

    | TIfdefBool (_, tag, _)
    | TIfdefMisc (_, tag, _)
    | TIfdefVersion (_, tag, _) ->
	tag := Some cnt;

    | _ -> raise (Impossible 89)



let ifdef_paren_cnt = ref 0


let rec set_ifdef_parenthize_info xs =
  xs +> List.iter (function
  | NotIfdefLine xs -> ()
  | Ifdefbool (_, xxs, info_ifdef)
  | Ifdef (xxs, info_ifdef) ->

      incr ifdef_paren_cnt;
      let total_directives = List.length info_ifdef in

      info_ifdef +> List.iter (fun x ->
        set_ifdef_token_parenthize_info (!ifdef_paren_cnt, total_directives)
          x.tok);
      xxs +> List.iter set_ifdef_parenthize_info
  )


(*****************************************************************************)
(* The parsing hack for #define *)
(*****************************************************************************)

(* To parse macro definitions I need to do some tricks
 * as some information can be get only at the lexing level. For instance
 * the space after the name of the macro in '#define foo (x)' is meaningful
 * but the grammar can not get this information. So define_ident below
 * look at such space and generate a special TOpardefine. In a similar
 * way macro definitions can contain some antislash and newlines
 * and the grammar need to know where the macro ends (which is
 * a line-level and so low token-level information). Hence the
 * function 'define_line' below and the TDefEol.
 *
 * update: TDefEol is handled in a special way at different places,
 * a little bit like EOF, especially for error recovery, so this
 * is an important token that should not be retagged!
 *
 *
 * ugly hack, a better solution perhaps would be to erase TDefEOL
 * from the Ast and list of tokens in parse_c.
 *
 * note: I do a +1 somewhere, it's for the unparsing to correctly sync.
 *
 * note: can't replace mark_end_define by simply a fakeInfo(). The reason
 * is where is the \n TCommentSpace. Normally there is always a last token
 * to synchronize on, either EOF or the token of the next toplevel.
 * In the case of the #define we got in list of token
 * [TCommentSpace "\n"; TDefEOL] but if TDefEOL is a fakeinfo then we will
 * not synchronize on it and so we will not print the "\n".
 * A solution would be to put the TDefEOL before the "\n".
 * (jll: tried to do this, see the comment "Put end of line..." below)
 *
 * todo?: could put a ExpandedTok for that ?
 *)
let mark_end_define ii =
  let ii' =
    { Ast_c.pinfo = Ast_c.OriginTok { (Ast_c.parse_info_of_info ii) with
        Common.str = "";
        Common.charpos = Ast_c.pos_of_info ii + 1
      };
      cocci_tag = ref Ast_c.emptyAnnot;
      annots_tag = Token_annot.empty;
      comments_tag = ref Ast_c.emptyComments;
      danger = ref Ast_c.NoDanger;
    }
  in
  TDefEOL (ii')

(* put the TDefEOL at the good place *)
let rec define_line_1 acc xs =
  match xs with
  | [] -> List.rev acc
  | TDefine ii::xs ->
      let line = Ast_c.line_of_info ii in
      let acc = (TDefine ii) :: acc in
      define_line_2 acc line ii xs
  | TUndef ii::xs ->
      let line = Ast_c.line_of_info ii in
      let acc = (TUndef ii) :: acc in
      define_line_2 acc line ii xs
  | TPragma ii::xs ->
      let line = Ast_c.line_of_info ii in
      let acc = (TPragma ii) :: acc in
      define_line_2 acc line ii xs
  | TCppEscapedNewline ii::xs ->
      pr2 ("SUSPICIOUS: a \\ character appears outside of a #define at");
      pr2 (Ast_c.strloc_of_info ii);
      let acc = (TCommentSpace ii) :: acc in
      define_line_1 acc xs
  | x::xs -> define_line_1 (x::acc) xs

and define_line_2 acc line lastinfo xs =
  match xs with
  | [] ->
      (* should not happened, should meet EOF before *)
      pr2 "PB: WEIRD";
      List.rev (mark_end_define lastinfo::acc)
  | x::xs ->
      let line' = TH.line_of_tok x in
      let info = TH.info_of_tok x in

      (match x with
      | EOF ii ->
	  let acc = (mark_end_define lastinfo) :: acc in
	  let acc = (EOF ii) :: acc in
          define_line_1 acc xs
      | TCppEscapedNewline ii ->
          if (line' <> line) then pr2 "PB: WEIRD: not same line number";
	  let acc = (TCommentSpace ii) :: acc in
          define_line_2 acc (line+1) info xs
      | x ->
          if line' =|= line
          then define_line_2 (x::acc) (end_line_of_tok line' x) info xs
          else
	    (* Put end of line token before the newline.  A newline at least
	       must be there because the line changed and because we saw a
	       #define previously to get to this function at all *)
	    define_line_1
	      ((List.hd acc)::(mark_end_define lastinfo::(List.tl acc)))
	      (x::xs)
      )

(* for a comment, the end line is not the same as line_of_tok *)
and end_line_of_tok default = function
    (TComment _) as t ->
      let line_fragments =
	Str.split_delim (Str.regexp "\n") (TH.str_of_tok t) in
      (match List.rev line_fragments with
	_::front_fragments ->
	  (* no need for backslash at the end of these lines... *)
	  TH.line_of_tok t + (List.length front_fragments)
      |	_ -> failwith (Printf.sprintf "bad comment: %d" (TH.line_of_tok t)))
  |  t -> default

let rec define_ident acc xs =
  match xs with
  | [] -> List.rev acc
  | TUndef ii::xs ->
      let acc = TUndef ii :: acc in
      (match xs with
	TCommentSpace i1::TIdent (s,i2)::xs ->
	  let acc = (TCommentSpace i1) :: acc in
	  let acc = (TIdentDefine (s,i2)) :: acc in
          define_ident acc xs
      | _ ->
          pr2 "WEIRD: weird #define body";
          define_ident acc xs
      )
  | TDefine ii::xs ->
      let acc = TDefine ii :: acc in
      (match xs with
      | TCommentSpace i1::TIdent (s,i2)::TOPar (i3)::xs ->
          (* Change also the kind of TIdent to avoid bad interaction
           * with other parsing_hack tricks. For instant if keep TIdent then
           * the stringication algo can believe the TIdent is a string-macro.
           * So simpler to change the kind of the ident too.
           *)
          (* if TOParDefine sticked to the ident, then
           * it's a macro-function. Change token to avoid ambiguity
           * between #define foo(x)  and   #define foo   (x)
           *)
	  let acc = (TCommentSpace i1) :: acc in
	  let acc = (TIdentDefine (s,i2)) :: acc in
	  let acc = (TOParDefine i3) :: acc in
          define_ident acc xs

      | TCommentSpace i1::TIdent (s,i2)::xs ->
	  let acc = (TCommentSpace i1) :: acc in
	  let acc = (TIdentDefine (s,i2)) :: acc in
          define_ident acc xs

      (* bugfix: ident of macro (as well as params, cf below) can be tricky
       * note, do we need to subst in the body of the define ? no cos
       * here the issue is the name of the macro, as in #define inline,
       * so obviously the name of this macro will not be used in its
       * body (it would be a recursive macro, which is forbidden).
       *)

      | TCommentSpace i1::t::xs
	when TH.str_of_tok t ==~ Common.regexp_alpha
	->
          let s = TH.str_of_tok t in
          let ii = TH.info_of_tok t in
	  pr2 (spf "remapping: %s to an ident in macro name" s);
          let acc = (TCommentSpace i1) :: acc in
	  let acc = (TIdentDefine (s,ii)) :: acc in
          define_ident acc xs
          
      | TCommentSpace _::_::xs
      | xs ->
          pr2 "WEIRD: weird #define body";
          define_ident acc xs
      )
  | TPragma ii::xs ->
      let acc = TPragma ii :: acc in
      let rec loop acc = function
	  ((TDefEOL i1) as x) :: xs -> define_ident (x::acc) xs
	| TCommentSpace i1::TIdent (s,i2)::xs ->
	    let acc = (TCommentSpace i1) :: acc in
	    let acc = (TIdentDefine (s,i2)) :: acc in
            loop acc xs

      (* bugfix: ident of macro (as well as params, cf below) can be tricky
       * note, do we need to subst in the body of the define ? no cos
       * here the issue is the name of the macro, as in #define inline,
       * so obviously the name of this macro will not be used in its
       * body (it would be a recursive macro, which is forbidden).
       *)

	| TCommentSpace i1::t::xs
	  when TH.str_of_tok t ==~ Common.regexp_alpha
	  ->
            let s = TH.str_of_tok t in
            let ii = TH.info_of_tok t in
	    pr2 (spf "remapping: %s to an ident in pragma" s);
            let acc = (TCommentSpace i1) :: acc in
	    let acc = (TIdentDefine (s,ii)) :: acc in
            define_ident acc xs
          
	| xs ->
            pr2 "WEIRD: weird #pragma";
            define_ident acc xs in
      loop acc xs
  | x::xs ->
      let acc = x :: acc in
      define_ident acc xs



let fix_tokens_define2 xs =
  define_ident [] (define_line_1 [] xs)

let fix_tokens_define a =
  Common.profile_code "C parsing.fix_define" (fun () -> fix_tokens_define2 a)


(* ------------------------------------------------------------------------- *)
(* Other parsing hacks related to cpp, Include/Define hacks *)
(* ------------------------------------------------------------------------- *)

(* Sometimes I prefer to generate a single token for a list of things in the
 * lexer so that if I have to passed them, like for passing TInclude then
 * it's easy. Also if I don't do a single token, then I need to
 * parse the rest which may not need special stuff, like detecting
 * end of line which the parser is not really ready for. So for instance
 * could I parse a #include <a/b/c/xxx.h> as 2 or more tokens ? just
 * lex #include ? so then need recognize <a/b/c/xxx.h> as one token ?
 * but this kind of token is valid only after a #include and the
 * lexing and parsing rules are different for such tokens so not that
 * easy to parse such things in parser_c.mly. Hence the following hacks.
 *
 * less?: maybe could get rid of this like I get rid of some of fix_define.
 *)

(* helpers *)

(* used to generate new token from existing one *)
let new_info posadd str ii =
  { Ast_c.pinfo =
      Ast_c.OriginTok { (Ast_c.parse_info_of_info ii) with
        charpos = Ast_c.pos_of_info ii + posadd;
        str     = str;
        column = Ast_c.col_of_info ii + posadd;
      };
    (* must generate a new ref each time, otherwise share *)
    cocci_tag = ref Ast_c.emptyAnnot;
    annots_tag = Token_annot.empty;
    comments_tag = ref Ast_c.emptyComments;
    danger = ref Ast_c.NoDanger;
   }


let rec comment_until_defeol xs =
  match xs with
  | [] ->
      (* job not done in Cpp_token_c.define_parse ? *)
      failwith "cant find end of define token TDefEOL"
  | x::xs ->
      (match x with
      | Parser_c.TDefEOL i ->
          Parser_c.TCommentCpp (Token_c.CppDirective, TH.info_of_tok x)
          ::xs
      | _ ->
          let x' =
            (* bugfix: otherwise may lose a TComment token *)
            if TH.is_real_comment x
            then x
            else Parser_c.TCommentCpp (Token_c.CppPassingNormal (*good?*), TH.info_of_tok x)
          in
          x'::comment_until_defeol xs
      )

let drop_until_defeol xs =
  List.tl
    (Common.drop_until (function Parser_c.TDefEOL _ -> true | _ -> false) xs)



(* ------------------------------------------------------------------------- *)
(* returns a pair (replaced token, list of next tokens) *)
(* ------------------------------------------------------------------------- *)

let tokens_include (info, includes, filename, inifdef) =
  Parser_c.TIncludeStart (Ast_c.rewrap_str includes info, inifdef),
  [Parser_c.TIncludeFilename
      (filename, (new_info (String.length includes) filename info))
  ]




(*****************************************************************************)
(* CPP handling: macros, ifdefs, macros defs  *)
(*****************************************************************************)

(* ------------------------------------------------------------------------- *)
(* special skip_start skip_end handling *)
(* ------------------------------------------------------------------------- *)

(* note: after this normally the token list should not contain any more the
 * TCommentSkipTagStart and End tokens.
 *)
let rec commentize_skip_start_to_end xs =
  match xs with
  | [] -> ()
  | x::xs ->
      (match x with
      | {tok = TCommentSkipTagStart info} ->
          (try
            let (before, x2, after) =
              xs +> Common.split_when (function
              | {tok = TCommentSkipTagEnd _ } -> true
              | _ -> false
              )
            in
            let topass = x::x2::before in
            topass +> List.iter (fun tok ->
              TV.set_as_comment Token_c.CppPassingExplicit tok
            );
            commentize_skip_start_to_end after
          with Not_found ->
            failwith "could not find end of skip_start special comment"
          )
      | {tok = TCommentSkipTagEnd info} ->
            failwith "found skip_end comment but no skip_start"
      | _ ->
          commentize_skip_start_to_end xs
      )




(* ------------------------------------------------------------------------- *)
(* ifdef keeping/passing *)
(* ------------------------------------------------------------------------- *)

(* #if 0, #if 1,  #if LINUX_VERSION handling *)
let rec find_ifdef_bool xs =
  xs +> List.iter (function
  | NotIfdefLine _ -> ()
  | Ifdefbool (is_ifdef_positif, xxs, info_ifdef_stmt) ->

      msg_ifdef_bool_passing is_ifdef_positif;

      (match xxs with
      | [] -> raise (Impossible 90)
      | firstclause::xxs ->
          info_ifdef_stmt +>
	  List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));

          if is_ifdef_positif
          then xxs +> List.iter
            (iter_token_ifdef (TV.set_as_comment Token_c.CppPassingNormal))
          else begin
            firstclause +>
	    iter_token_ifdef (TV.set_as_comment Token_c.CppPassingNormal);
            (match List.rev xxs with
            (* keep only last *)
            | last::startxs ->
                startxs +> List.iter
                  (iter_token_ifdef (TV.set_as_comment Token_c.CppPassingNormal))
            | [] -> (* not #else *) ()
            );
          end
      );

  | Ifdef (xxs, info_ifdef_stmt) -> xxs +> List.iter find_ifdef_bool
  )



let thresholdIfdefSizeMid = 6

(* infer ifdef involving not-closed expressions/statements *)
let rec find_ifdef_mid xs =
  xs +> List.iter (function
  | NotIfdefLine _ -> ()
  | Ifdef (xxs, info_ifdef_stmt) ->
      (match xxs with
      | [] -> raise (Impossible 91)
      | [first] -> ()
      | first::second::rest ->
          (* don't analyse big ifdef *)
          if xxs +> List.for_all
            (fun xs -> List.length xs <= thresholdIfdefSizeMid) &&
            (* don't want nested ifdef *)
            xxs +> List.for_all (fun xs ->
              xs +> List.for_all
                (function NotIfdefLine _ -> true | _ -> false)
            )

          then
            let counts = xxs +> List.map count_open_close_stuff_ifdef_clause in
            let cnt1, cnt2 = List.hd counts in
            if cnt1 <> 0 || cnt2 <> 0 &&
               counts +> List.for_all (fun x -> x =*= (cnt1, cnt2))
              (*
                if counts +> List.exists (fun (cnt1, cnt2) ->
                cnt1 <> 0 || cnt2 <> 0
                )
              *)
            then begin
              msg_ifdef_mid_something();

              (* keep only first, treat the rest as comment *)
              info_ifdef_stmt +>
	      List.iter
		(TV.save_as_comment (function x -> Token_c.CppIfDirective x));
              (second::rest) +> List.iter
                (iter_token_ifdef (TV.set_as_comment Token_c.CppPassingCosWouldGetError));
            end

      );
      List.iter find_ifdef_mid xxs

  (* no need complex analysis for ifdefbool *)
  | Ifdefbool (_, xxs, info_ifdef_stmt) ->
      List.iter find_ifdef_mid xxs


  )


let thresholdFunheaderLimit = 4

(* ifdef defining alternate function header, type *)
let rec find_ifdef_funheaders = function
  | [] -> ()
  | NotIfdefLine _::xs -> find_ifdef_funheaders xs

  (* ifdef-funheader if ifdef with 2 lines and a '{' in next line *)
  | Ifdef
      ([(NotIfdefLine (({col = 0} as _xline1)::line1))::ifdefblock1;
        (NotIfdefLine (({col = 0} as xline2)::line2))::ifdefblock2
      ], info_ifdef_stmt
      )
    ::NotIfdefLine (({tok = TOBrace i; col = 0})::line3)
    ::xs
   when List.length ifdefblock1 <= thresholdFunheaderLimit &&
        List.length ifdefblock2 <= thresholdFunheaderLimit
    ->
      find_ifdef_funheaders xs;

      msg_ifdef_funheaders ();
      info_ifdef_stmt +>
      List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));
      let all_toks = [xline2] @ line2 in
      all_toks +> List.iter (TV.set_as_comment Token_c.CppPassingCosWouldGetError) ;
      ifdefblock2 +> iter_token_ifdef (TV.set_as_comment Token_c.CppPassingCosWouldGetError);

  (* ifdef with nested ifdef *)
  | Ifdef
      ([[NotIfdefLine (({col = 0} as _xline1)::line1)];
        [Ifdef
            ([[NotIfdefLine (({col = 0} as xline2)::line2)];
              [NotIfdefLine (({col = 0} as xline3)::line3)];
            ], info_ifdef_stmt2
            )
        ]
      ], info_ifdef_stmt
      )
    ::NotIfdefLine (({tok = TOBrace i; col = 0})::line4)
    ::xs
    ->
      find_ifdef_funheaders xs;

      msg_ifdef_funheaders ();
      info_ifdef_stmt  +>
      List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));
      info_ifdef_stmt2 +>
      List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));
      let all_toks = [xline2;xline3] @ line2 @ line3 in
      all_toks +> List.iter (TV.set_as_comment Token_c.CppPassingCosWouldGetError);

 (* ifdef with elseif *)
  | Ifdef
      ([[NotIfdefLine (({col = 0} as _xline1)::line1)];
        [NotIfdefLine (({col = 0} as xline2)::line2)];
        [NotIfdefLine (({col = 0} as xline3)::line3)];
      ], info_ifdef_stmt
      )
    ::NotIfdefLine (({tok = TOBrace i; col = 0})::line4)
    ::xs
    ->
      find_ifdef_funheaders xs;

      msg_ifdef_funheaders ();
      info_ifdef_stmt +>
      List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));
      let all_toks = [xline2;xline3] @ line2 @ line3 in
      all_toks +> List.iter (TV.set_as_comment Token_c.CppPassingCosWouldGetError)

  (* recurse *)
  | Ifdef (xxs,info_ifdef_stmt)::xs
  | Ifdefbool (_, xxs,info_ifdef_stmt)::xs ->
      List.iter find_ifdef_funheaders xxs;
      find_ifdef_funheaders xs



(* ?? *)
let rec adjust_inifdef_include xs =
  xs +> List.iter (function
  | NotIfdefLine _ -> ()
  | Ifdef (xxs, info_ifdef_stmt) | Ifdefbool (_, xxs, info_ifdef_stmt) ->
      xxs +> List.iter (iter_token_ifdef (fun tokext ->
        match tokext.tok with
        | Parser_c.TInclude (s1, s2, inifdef_ref, ii) ->
            inifdef_ref := true;
        | _ -> ()
      ));
  )







let rec find_ifdef_cparen_else xs =
  let rec aux xs =
  xs +> List.iter (function
  | NotIfdefLine _ -> ()
  | Ifdef (xxs, info_ifdef_stmt) ->
      (match xxs with
      | [] -> raise (Impossible 92)
      | [first] -> ()
      | first::second::rest ->

         (* found a closing ')' just after the #else *)

          (* Too bad ocaml does not support better list pattern matching
           * a la Prolog-III where can match the end of lists.
           *)
          let condition =
            if List.length first = 0 then false
            else
              let last_line = Common.last first in
              match last_line with
              | NotIfdefLine xs ->
                  if List.length xs = 0 then false
                  else
                    let last_tok = Common.last xs in
                    TH.is_cpar last_tok.tok
              | Ifdef _ | Ifdefbool _ -> false
          in
          if condition then begin
            msg_ifdef_cparen_else();

            (* keep only first, treat the rest as comment *)
            info_ifdef_stmt +>
	    List.iter (TV.save_as_comment (fun x -> Token_c.CppIfDirective x));
            (second::rest) +> List.iter
              (iter_token_ifdef (TV.set_as_comment Token_c.CppPassingCosWouldGetError));
          end

      );
      List.iter aux xxs

  (* no need complex analysis for ifdefbool *)
  | Ifdefbool (_, xxs, info_ifdef_stmt) ->
      List.iter aux xxs
  )
  in aux xs


(* ------------------------------------------------------------------------- *)
(* cpp-builtin part2, macro, using standard.h or other defs *)
(* ------------------------------------------------------------------------- *)

(* now in cpp_token_c.ml *)

(* ------------------------------------------------------------------------- *)
(* stringification *)
(* ------------------------------------------------------------------------- *)

let rec find_string_macro_paren xs =
  match xs with
  | [] -> ()
  | Parenthised(xxs, info_parens)::xs ->
      xxs +> List.iter (fun xs ->
        if xs +> List.exists
          (function PToken({tok = (TString _| TMacroString _)}) -> true | _ -> false) &&
          xs +> List.for_all
          (function PToken({tok = (TString _| TMacroString _)}) | PToken({tok = TIdent _}) ->
            true | _ -> false)
        then
          xs +> List.iter (fun tok ->
            match tok with
            | PToken({tok = TIdent (s,_)} as id) ->

                msg_stringification s;
                id.tok <- TMacroString (s, TH.info_of_tok id.tok);
            | _ -> ()
          )
        else
          find_string_macro_paren xs
      );
      find_string_macro_paren xs
  | PToken(tok)::xs ->
      find_string_macro_paren xs


(* ------------------------------------------------------------------------- *)
(* format strings *)
(* ------------------------------------------------------------------------- *)

(* can't just expand all strings, because string followed by another string
will turn into a MultiString. *)
let fix_tokens_strings toks =
  let comments x = TH.is_comment x in
  let strings_and_comments =
    function TString _ -> true | TIdent _ -> true | x -> TH.is_comment x in
  let can_be_string =
    function TString _ -> true | TIdent _ -> true | x -> false in
  let rec skip acc fn = function
      x :: xs when fn x -> skip (x :: acc) fn xs
    | xs -> (List.rev acc, xs)
  and out_strings = function
      [] -> []
    | a :: rest ->
	if can_be_string a
	then
	  let (front,rest) = skip [] comments rest in
	  (match rest with
	    b :: rest when can_be_string b ->
	      let (front2,rest) = skip [] strings_and_comments rest in
	      a :: front @ b :: front2 @ out_strings rest
	  | _ ->
	      (match a with
		TString(str_isW,info) ->
		  (Parse_string_c.parse_string str_isW info) @ front @
		  out_strings rest
	      |	_ ->  a :: front @ out_strings rest))
	else a :: out_strings rest in
  out_strings toks

(* ------------------------------------------------------------------------- *)
(* macro2 *)
(* ------------------------------------------------------------------------- *)

(* don't forget to recurse in each case *)
let rec find_macro_paren xs =
  match xs with
  | [] -> ()

  (* attribute *)
  | PToken ({tok = Tattribute _} as id)
    ::Parenthised (xxs,info_parens)
    ::xs
     ->
      pr2_cpp ("MACRO: __attribute detected ");
      [Parenthised (xxs, info_parens)] +>
        iter_token_paren (TV.set_as_comment Token_c.CppAttr);
      TV.set_as_comment Token_c.CppAttr id;
      find_macro_paren xs

  | PToken ({tok = TattributeNoarg _} as id)
    ::xs
     ->
      pr2_cpp ("MACRO: __attributenoarg detected ");
      TV.set_as_comment Token_c.CppAttr id;
      find_macro_paren xs

(*
  (* attribute cpp, __xxx id *)
  | PToken ({tok = TIdent (s,i1)} as id)
    ::PToken ({tok = TIdent (s2, i2)} as id2)
    ::xs when s ==~ regexp_annot
     ->
      msg_attribute s;
      id.tok <- TMacroAttr (s, i1);
      find_macro_paren ((PToken id2)::xs); (* recurse also on id2 ? *)

  (* attribute cpp, id __xxx *)
  | PToken ({tok = TIdent (s,i1)} as _id)
    ::PToken ({tok = TIdent (s2, i2)} as id2)
    ::xs when s2 ==~ regexp_annot && (not (s ==~ regexp_typedef))
     ->
      msg_attribute s2;
      id2.tok <- TMacroAttr (s2, i2);
      find_macro_paren xs

  | PToken ({tok = (Tstatic _ | Textern _)} as tok1)
    ::PToken ({tok = TIdent (s,i1)} as attr)
    ::xs when s ==~ regexp_annot
    ->
      pr2_cpp ("storage attribute: " ^ s);
      attr.tok <- TMacroAttrStorage (s,i1);
      (* recurse, may have other storage attributes *)
      find_macro_paren (PToken (tok1)::xs)

*)

  (* storage attribute *)
  | PToken ({tok = (Tstatic _ | Textern _)} as tok1)
    ::PToken ({tok = TMacroAttr (s,i1)} as attr)::xs
    ->
      pr2_cpp ("storage attribute: " ^ s);
      attr.tok <- TMacroAttrStorage (s,i1);
      (* recurse, may have other storage attributes *)
      find_macro_paren (PToken (tok1)::xs)


  (* stringification
   *
   * the order of the matching clause is important
   *
   *)

  (* string macro with params, before case *)
  | PToken ({tok = (TString _| TMacroString _)})::PToken ({tok = TIdent (s,_)} as id)
    ::Parenthised (xxs, info_parens)
    ::xs ->

      msg_stringification_params s;
      id.tok <- TMacroString (s, TH.info_of_tok id.tok);
      [Parenthised (xxs, info_parens)] +>
        iter_token_paren (TV.set_as_comment Token_c.CppMacro);
      find_macro_paren xs

  (* after case *)
  | PToken ({tok = TIdent (s,_)} as id)
    ::Parenthised (xxs, info_parens)
    ::PToken ({tok = (TString _ | TMacroString _)})
    ::xs ->

      msg_stringification_params s;
      id.tok <- TMacroString (s, TH.info_of_tok id.tok);
      [Parenthised (xxs, info_parens)] +>
        iter_token_paren (TV.set_as_comment Token_c.CppMacro);
      find_macro_paren xs


  (* for the case where the string is not inside a funcall, but
   * for instance in an initializer.
   *)

  (* string macro variable, before case *)
  | PToken ({tok = (TString _ | TMacroString _)})::PToken ({tok = TIdent (s,_)} as id)
      ::xs when not !Flag.c_plus_plus ->

      msg_stringification s;
      id.tok <- TMacroString (s, TH.info_of_tok id.tok);
      find_macro_paren xs

  (* after case *)
  | PToken ({tok = TIdent (s,_)} as id)
      ::PToken ({tok = (TString _ | TMacroString _)})
      ::xs ->

      msg_stringification s;
      id.tok <- TMacroString (s, TH.info_of_tok id.tok);
      find_macro_paren xs





  (* recurse *)
  | (PToken x)::xs -> find_macro_paren xs
  | (Parenthised (xxs, info_parens))::xs ->
      xxs +> List.iter find_macro_paren;
      find_macro_paren xs





(* don't forget to recurse in each case *)
let rec find_macro_lineparen xs =
  match xs with
  | [] -> ()

  (* linuxext: ex: static [const] DEVICE_ATTR(); *)
  | (Line
        (
          [PToken ({tok = Tstatic _});
           PToken ({tok = TIdent (s,_)} as macro);
           Parenthised (xxs,info_parens);
           PToken ({tok = TPtVirg _});
          ]
        ))
    ::xs
    when (s ==~ regexp_macro) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      find_macro_lineparen (xs)

  (* the static const case *)
  | (Line
        (
          [PToken ({tok = Tstatic _});
           PToken ({tok = Tconst _} as const);
           PToken ({tok = TIdent (s,_)} as macro);
           Parenthised (xxs,info_parens);
           PToken ({tok = TPtVirg _});
          ]
            (*as line1*)

        ))
    ::xs
    when (s ==~ regexp_macro) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      (* need retag this const, otherwise ambiguity in grammar
         21: shift/reduce conflict (shift 121, reduce 137) on Tconst
  	 decl2 : Tstatic . TMacroDecl TOPar argument_list TCPar ...
	 decl2 : Tstatic . Tconst TMacroDecl TOPar argument_list TCPar ...
	 storage_class_spec : Tstatic .  (137)
      *)
      const.tok <- TMacroDeclConst (TH.info_of_tok const.tok);

      find_macro_lineparen (xs)


  (* same but without trailing ';'
   *
   * I do not put the final ';' because it can be on a multiline and
   * because of the way mk_line is coded, we will not have access to
   * this ';' on the next line, even if next to the ')' *)
  | (Line
        ([PToken ({tok = Tstatic _});
          PToken ({tok = TIdent (s,_)} as macro);
          Parenthised (xxs,info_parens);
        ]
        ))
    ::xs
    when s ==~ regexp_macro ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      find_macro_lineparen (xs)


  (* on multiple lines *)
  | (Line
        (
          (PToken ({tok = Tstatic _})::[]
          )))
    ::(Line
          (
            [PToken ({tok = TIdent (s,_)} as macro);
             Parenthised (xxs,info_parens);
             PToken ({tok = TPtVirg _});
            ]
          )
        )
    ::xs
    when (s ==~ regexp_macro) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      find_macro_lineparen (xs)


  | (Line (* initializer case *)
        (
          PToken ({tok = Tstatic _}) ::
           PToken ({tok = TIdent (s,_)} as macro) ::
           Parenthised (xxs,info_parens) ::
           PToken ({tok = TEq _}) :: rest
        ))
    ::xs
    when (s ==~ regexp_macro) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      (* continue with the rest of the line *)
      find_macro_lineparen ((Line(rest))::xs)


  | (Line (* multi-line initializer case *)
        (
          (PToken ({tok = Tstatic _})::[]
          )))
    ::(Line
        (
          PToken ({tok = Tstatic _}) ::
           PToken ({tok = TIdent (s,_)} as macro) ::
           Parenthised (xxs,info_parens) ::
           PToken ({tok = TEq _}) :: rest
        ))
    ::xs
    when (s ==~ regexp_macro) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      (* continue with the rest of the line *)
      find_macro_lineparen ((Line(rest))::xs)


  (* linuxext: ex: DECLARE_BITMAP();
   *
   * Here I use regexp_declare and not regexp_macro because
   * Sometimes it can be a FunCallMacro such as DEBUG(foo());
   * Here we don't have the preceding 'static' so only way to
   * not have positive is to restrict to .*DECLARE.* macros.
   *
   * but there is a grammar rule for that, so don't need this case anymore
   * unless the parameter of the DECLARE_xxx are weird and can not be mapped
   * on a argument_list
   *)

  | (Line
        ([PToken ({tok = TIdent (s,_)} as macro);
          Parenthised (xxs,info_parens);
          PToken ({tok = TPtVirg _});
        ]
        ))
    ::xs
    when (s ==~ regexp_declare) ->

      msg_declare_macro s;
      let info = TH.info_of_tok macro.tok in
      macro.tok <- TMacroDecl (Ast_c.str_of_info info, info);

      find_macro_lineparen (xs)


  (* toplevel macros.
   * module_init(xxx)
   *
   * Could also transform the TIdent in a TMacroTop but can have false
   * positive, so easier to just change the TCPar and so just solve
   * the end-of-stream pb of ocamlyacc
   *)
  | (Line
        ([PToken ({tok = TIdent (s,ii); col = col1; where = ctx} as _macro);
          Parenthised (xxs,info_parens);
        ] as _line1
        ))
    ::xs when col1 =|= 0
    ->
      let condition =
        (* to reduce number of false positive *)
        (match xs with
        | (Line (PToken ({col = col2 } as other)::restline2))::_ ->
            TH.is_eof other.tok || (col2 =|= 0 &&
             (match other.tok with
             | TOBrace _ -> false (* otherwise would match funcdecl *)
             | TCBrace _ when ctx <> InFunction -> false
             | TPtVirg _
             | TDotDot _
               -> false
             | tok when TH.is_binary_operator tok -> false

             | _ -> true
             )
            )
        | _ -> false
        )
      in
      if condition
      then begin

          msg_macro_toplevel_noptvirg s;
          (* just to avoid the end-of-stream pb of ocamlyacc  *)
          let tcpar = Common.last info_parens in
          tcpar.tok <- TCParEOL (TH.info_of_tok tcpar.tok);

          (*macro.tok <- TMacroTop (s, TH.info_of_tok macro.tok);*)

        end;

       find_macro_lineparen (xs)



  (* macro with parameters
   * ex: DEBUG()
   *     return x;
   *)
  | (Line
        ([PToken ({tok = TIdent (s,ii); col = col1; where = ctx} as macro);
          Parenthised (xxs,info_parens);
        ] as _line1
        ))
    ::(Line
          (PToken ({col = col2 } as other)::restline2
          ) as line2)
    ::xs
    (* when s ==~ regexp_macro *)
    ->
      (* This can give a false positive for K&R functions if the function
         name is in the same column as the first parameter declaration. *)
      let condition =
        (col1 =|= col2 &&
            (match other.tok with
            | TOBrace _ -> false (* otherwise would match funcdecl *)
            | TCBrace _ when ctx <> InFunction -> false
            | TPtVirg _
            | TDotDot _
                -> false
            | tok when TH.is_binary_operator tok -> false

            | _ -> true
            )
        )
        ||
        (col2 <= col1 &&
              (match other.tok, restline2 with
              | TCBrace _, _ when ctx =*= InFunction -> true
              | Treturn _, _ -> true
              | Tif _, _ -> true
              | Telse _, _ -> true

              (* case of label, usually put in first line *)
              | TIdent _, (PToken ({tok = TDotDot _}))::_ ->
                  true


              | _ -> false
              )
          )

      in

      if condition
      then
        if col1 =|= 0 then ()
        else begin
          msg_macro_noptvirg s;
          macro.tok <- TMacroStmt (s, TH.info_of_tok macro.tok);
          [Parenthised (xxs, info_parens)] +>
            iter_token_paren (TV.set_as_comment Token_c.CppMacro);
        end;

      find_macro_lineparen (line2::xs)

  (* linuxext:? single macro
   * ex: LOCK
   *     foo();
   *     UNLOCK
   *
   * todo: factorize code with previous rule ?
   *)
  | (Line
        ([PToken ({tok = TIdent (s,ii); col = col1; where = ctx} as macro);
        ] as _line1
        ))
    ::(Line
          (PToken ({col = col2 } as other)::restline2
          ) as line2)
    ::xs ->
    (* when s ==~ regexp_macro *)

      let condition =
        (col1 =|= col2 &&
            col1 <> 0 && (* otherwise can match typedef of fundecl*)
            (match other.tok with
            | TPtVirg _ -> false
            | TOr _ -> false
            | TCBrace _ when ctx <> InFunction -> false
            | tok when TH.is_binary_operator tok -> false

            | _ -> true
            )) ||
          (col2 <= col1 &&
              (match other.tok with
              | TCBrace _ when ctx =*= InFunction -> true
              | Treturn _ -> true
              | Tif _ -> true
              | Telse _ -> true
              | _ -> false
              ))
      in

      if condition
      then begin
        msg_macro_noptvirg_single s;
        macro.tok <- TMacroStmt (s, TH.info_of_tok macro.tok);
      end;
      find_macro_lineparen (line2::xs)

  | x::xs ->
      find_macro_lineparen xs



(* ------------------------------------------------------------------------- *)
(* define tobrace init *)
(* ------------------------------------------------------------------------- *)

let rec find_define_init_brace_paren xs =
 let rec aux xs =
  match xs with
  | [] -> ()

  (* mainly for firefox *)
  | (PToken {tok = TDefine _})
    ::(PToken {tok = TIdentDefine (s,_)})
    ::(PToken ({tok = TOBrace i1} as tokbrace))
    ::(PToken tok2)
    ::(PToken tok3)
    ::xs ->
      let is_init =
        match tok2.tok, tok3.tok with
        | TInt _, TComma _ -> true
        | TString _, TComma _ -> true
        | TIdent _, TComma _ -> true
        | _ -> false

      in
      if is_init
      then begin
        pr2_cpp("found define initializer: " ^s);
        tokbrace.tok <- TOBraceDefineInit i1;
      end;

      aux xs

  (* mainly for linux, especially in sound/ *)
  | (PToken {tok = TDefine _})
    ::(PToken {tok = TIdentDefine (s,_)})
    ::(Parenthised(xxx, info_parens))
    ::(PToken ({tok = TOBrace i1} as tokbrace))
    ::(PToken tok2)
    ::(PToken tok3)
    ::xs ->
      let is_init =
        match tok2.tok, tok3.tok with
        | TInt _, TComma _ -> true
        | TDot _, TIdent _ -> true
        | TIdent _, TComma _ -> true
        | _ -> false

      in
      if is_init
      then begin
        pr2_cpp("found define initializer with param: " ^ s);
        tokbrace.tok <- TOBraceDefineInit i1;
      end;

      aux xs



  (* recurse *)
  | (PToken x)::xs -> aux xs
  | (Parenthised (xxs, info_parens))::xs ->
      (* not need for tobrace init:
       *  xxs +> List.iter aux;
       *)
      aux xs
 in
 aux xs


(* ------------------------------------------------------------------------- *)
(* action *)
(* ------------------------------------------------------------------------- *)

(* obsolete now with macro expansion ? get some regression if comment.
 * todo: if do bad decision here, then it can influence other phases
 * and make it hard to parse. So maybe when have a parse error, should
 * undo some of the guess those heuristics have done, and restore
 * the original token value.
 *)

let rec find_actions = function
  | [] -> ()

  | PToken ({tok = TIdent (s,ii)})
    ::Parenthised (xxs,info_parens)
    ::xs ->
      find_actions xs;
      xxs +> List.iter find_actions;
      let modified = find_actions_params xxs in
      if modified
      then msg_macro_higher_order s

  | x::xs ->
      find_actions xs

and find_actions_params xxs =
  xxs +> List.fold_left (fun acc xs ->
    let toks = tokens_of_paren xs in
    if toks +> List.exists (fun x -> TH.is_statement x.tok)
      (* undo:  && List.length toks > 1
       * good for sparse, not good for linux
       *)
    then begin
      xs +> iter_token_paren (fun x ->
        if TH.is_eof x.tok
        then
          (* certainly because paren detection had a pb because of
           * some ifdef-exp. Do similar additional checking than
           * what is done in TV.set_as_comment.
           *)
          pr2 "PB: weird, I try to tag an EOF token as an action"
        else
          (* cf tests-bis/no_cpar_macro.c *)
          if TH.is_eom x.tok
          then
            pr2 "PB: weird, I try to tag an EOM token as an action"
          else
            x.tok <- TAction (TH.info_of_tok x.tok);
      );
      true (* modified *)
    end
    else acc
  ) false



(* ------------------------------------------------------------------------- *)
(* main fix cpp function *)
(* ------------------------------------------------------------------------- *)

let filter_cpp_stuff xs =
  List.filter
    (function x ->
      (match x.tok with
        | tok when TH.is_comment tok -> false
        (* don't want drop the define, or if drop, have to drop
         * also its body otherwise the line heuristics may be lost
         * by not finding the TDefine in column 0 but by finding
         * a TDefineIdent in a column > 0
         *)
        | Parser_c.TDefine _ -> true
        | tok when TH.is_cpp_instruction tok -> false
        | _ -> true
        ))
    xs

let insert_virtual_positions l =
  let strlen x = String.length (Ast_c.str_of_info x) in
  let rec loop prev offset acc = function
      [] -> List.rev acc
    | x::xs ->
	let ii = TH.info_of_tok x in
	let inject pi =
	  TH.visitor_info_of_tok (function ii -> Ast_c.rewrap_pinfo pi ii) x in
	match Ast_c.pinfo_of_info ii with
	  Ast_c.OriginTok pi ->
	    let prev = Ast_c.parse_info_of_info ii in
	    loop prev (strlen ii) (x::acc) xs
	| Ast_c.ExpandedTok (pi,_) ->
            let x' = inject (Ast_c.ExpandedTok (pi,(prev,offset))) in
	    loop prev (offset + (strlen ii)) (x'::acc) xs
	| Ast_c.FakeTok (s,_) ->
            let x' = inject (Ast_c.FakeTok (s,(prev,offset))) in
	    loop prev (offset + (strlen ii)) (x'::acc) xs
	| Ast_c.AbstractLineTok _ -> failwith "abstract not expected" in
  let rec skip_fake = function
    | [] -> []
    | x::xs ->
	let ii = TH.info_of_tok x in
	match Ast_c.pinfo_of_info ii with
	| Ast_c.OriginTok pi ->
	    let prev = Ast_c.parse_info_of_info ii in
            let res = loop prev (strlen ii) [] xs  in
            x::res
	| _ -> x::skip_fake xs in
  skip_fake l

(* ------------------------------------------------------------------------- *)

let fix_tokens_cpp2 ~macro_defs tokens =
  let tokens2 = ref (tokens +> Common.acc_map TV.mk_token_extended) in

  begin
    (* the order is important, if you put the action heuristic first,
     * then because of ifdef, can have not closed paren
     * and so may believe that higher order macro
     * and it will eat too much tokens. So important to do
     * first the ifdef.
     *
     * I recompute multiple times cleaner cos the mutable
     * can have be changed and so may have more comments
     * in the token original list.
     *
     *)

    commentize_skip_start_to_end !tokens2;

    (* ifdef *)
    let cleaner = !tokens2 +> List.filter (fun x ->
      (* is_comment will also filter the TCommentCpp created in
       * commentize_skip_start_to_end *)
      not (TH.is_comment x.tok) (* could filter also #define/#include *)
    ) in
    let ifdef_grouped = TV.mk_ifdef cleaner in
    set_ifdef_parenthize_info ifdef_grouped;

    find_ifdef_funheaders ifdef_grouped;
    find_ifdef_bool       ifdef_grouped;
    find_ifdef_mid        ifdef_grouped;
    (* change order ? maybe cparen_else heuristic make some of the funheaders
     * heuristics irrelevant ?
     *)
    find_ifdef_cparen_else        ifdef_grouped;
    adjust_inifdef_include ifdef_grouped;


    (* macro 1 *)
    let cleaner = !tokens2 +> filter_cpp_stuff in

    let paren_grouped = TV.mk_parenthised  cleaner in
    Cpp_token_c.apply_macro_defs
      ~msg_apply_known_macro
      ~msg_apply_known_macro_hint
      macro_defs paren_grouped;
    (* because the before field is used by apply_macro_defs *)
    tokens2 := TV.rebuild_tokens_extented !tokens2;

    (* tagging contextual info (InFunc, InStruct, etc). Better to do
     * that after the "ifdef-simplification" phase.
     *)
    let cleaner = !tokens2 +> List.filter (fun x ->
      not (TH.is_comment x.tok) (* could filter also #define/#include *)
    ) in

    let brace_grouped = TV.mk_braceised cleaner in
    set_context_tag   brace_grouped;

    (* macro *)
    let cleaner = !tokens2 +> filter_cpp_stuff in

    let paren_grouped      = TV.mk_parenthised  cleaner in
    let line_paren_grouped = TV.mk_line_parenthised paren_grouped in
    find_define_init_brace_paren paren_grouped;
    find_string_macro_paren paren_grouped;
    find_macro_lineparen    line_paren_grouped;
    find_macro_paren        paren_grouped;


    (* obsolete: actions ? not yet *)
    let cleaner = !tokens2 +> filter_cpp_stuff in
    let paren_grouped = TV.mk_parenthised  cleaner in
    find_actions  paren_grouped;



    insert_virtual_positions (!tokens2 +> Common.acc_map (fun x -> x.tok))
  end

let time_hack1 ~macro_defs a =
  Common.profile_code_exclusif "HACK" (fun () -> fix_tokens_cpp2 ~macro_defs a)

let fix_tokens_cpp ~macro_defs a =
  Common.profile_code "C parsing.fix_cpp" (fun () -> time_hack1 ~macro_defs a)



let can_be_on_top_level tl =
  match tl with
  | Tstruct _
  | Ttypedef _
  | TDefine _ 
  | TIfdef _
  | TIfdefelse _
  | TIfdefelif _
  | TIfdefBool _
  | TIfdefMisc _
  | TIfdefVersion _
  | TEndif _ -> true
  | _ -> false


(*****************************************************************************)
(* Lexing with lookahead *)
(*****************************************************************************)

(* Why using yet another parsing_hack technique ? The fix_xxx where do
 * some pre-processing on the full list of tokens is not enough ?
 * No cos sometimes we need more contextual info, and even if
 * set_context() tries to give some contextual info, it's not completely
 * accurate so the following code give yet another alternative, yet another
 * chance to transform some tokens.
 *
 * todo?: maybe could try to get rid of this technique. Maybe a better
 * set_context() would make possible to move this code using a fix_xx
 * technique.
 *
 * LALR(k) trick. We can do stuff by adding cases in lexer_c.mll, but
 * it is more general to do it via my LALR(k) tech. Because here we can
 * transform some token give some context information. So sometimes it
 * makes sense to transform a token in one context, sometimes not, and
 * lex can not provide us this context information. Note that the order
 * in the pattern matching in lookahead is important. Do not cut/paste.
 *
 * Note that in next there is only "clean" tokens, there is no comment
 * or space tokens. This is done by the caller.
 *
 *)

open Lexer_parser (* for the fields of lexer_hint type *)

let not_struct_enum = function
  | (Parser_c.Tstruct _ | Parser_c.Tunion _ | Parser_c.Tenum _)::_ -> false
  | _ -> true

let pointer ?(followed_by=fun _ -> true) 
    ?(followed_by_more=fun _ -> true) ts = 
  let rec loop ts = 
    match ts with
    | TMul _ :: rest -> loop rest
    | TAnd _ :: rest when !Flag.c_plus_plus -> loop rest
    | t :: ts' -> followed_by t && followed_by_more ts' 
    | [] -> failwith "unexpected end of token stream" in
  match ts with
  | TMul _ :: rest -> loop rest
  | TAnd _ :: rest when !Flag.c_plus_plus -> loop rest
  | _ -> false

let ident = function
    TIdent _ -> true
  | _ -> false

let is_type = function
  | TypedefIdent _ 
  | Tvoid _
  | Tchar _
  | Tfloat _
  | Tdouble _

  | Tsize_t _
  | Tssize_t _
  | Tptrdiff_t _
      
  | Tint _
  | Tlong _
  | Tshort _ -> true
  | _ -> false

let is_cparen = function (TCPar _) -> true | _ -> false
let is_oparen = function (TOPar _) -> true | _ -> false

let rec not_has_type_before f xs =
  match xs with
  | [] -> raise (Impossible 666)
  | x :: xs ->
      if f x then
	true
      else if is_type x then
	false
      else
	not_has_type_before f xs

(* This function is inefficient, because it will look over a K&R header,
or function prototype multiple times.  At least when we see a , and are in a
parameter list, we know we will eventually see a close paren, and it
should come fairly soon. *)
let k_and_r l =
  let l1 = drop_until is_cparen l in
  match l1 with
    (TCPar _) :: (TOCro _) :: _ -> false
  | (TCPar _) :: _ -> true
  | _ -> false

(* (a)(b) is ambiguous, because (a) could be a function name or a cast.
At this point, we just see an ident for a; we don't know if it is eg a local
variable.  This function sees at least if b is the only argument, ie there
are no commas at top level *)
let paren_before_comma l =
  let rec loop level = function
      [] -> false
    | (TComma _)::_ when level = 1 -> false
    | (TCPar _)::_ when level = 1 -> true
    | (TCPar _)::rest -> loop (level-1) rest
    | (TOPar _)::rest -> loop (level+1) rest
    | x::rest -> loop level rest in
  loop 0 l

let lookahead2 ~pass next before =
  match (next, before) with
      
  (* c++ hacks *)
  (* yy xx(   and in function *)
  | TOPar i1::_,              TIdent(s,i2)::TypedefIdent _::_
      when !Flag.c_plus_plus && (LP.current_context () = (LP.InFunction)) ->
        pr2_cpp("constructed_object: "  ^s);
        TOParCplusplusInit i1
  | TOPar i1::_,              TIdent(s,i2)::ptr
      when !Flag.c_plus_plus 
	  && pointer ~followed_by:(function TypedefIdent _ -> true | _ -> false) ptr
	  && (LP.current_context () = (LP.InFunction)) ->
        pr2_cpp("constructed_object: "  ^s);
        TOParCplusplusInit i1
  | TypedefIdent(s,i)::TOPar i1::_,_
      when !Flag.c_plus_plus && (LP.current_context () = (LP.InFunction)) ->
	TIdent(s,i)

  (*-------------------------------------------------------------*)
  (* typedef inference, parse_typedef_fix3 *)
  (*-------------------------------------------------------------*)
  (* xx xx *)
  | (TIdent(s,i1)::TIdent(s2,i2)::_ , _) when not_struct_enum before && s =$= s2
      && ok_typedef s
      (* (take_safe 1 !passed_tok <> [TOPar]) ->  *)
    ->
      (* parse_typedef_fix3:
       *    acpi_object		acpi_object;
       * etait mal pars??, car pas le temps d'appeler dt()  dans le type_spec.
       * Le parser en interne a deja appel?? le prochain token pour pouvoir
       * decider des choses.
       *  => special case in lexer_heuristic, again
       *)
      if !Flag_parsing_c.debug_typedef
      then pr2 ("TYPEDEF: disable typedef cos special case: " ^ s);


      LP.disable_typedef();
      msg_typedef s i1 1; LP.add_typedef_root s;
      TypedefIdent (s, i1)

	(* christia *)

	(* delete[] *)
  | (TOCro i1 :: _, Tdelete _ :: _) 
    when !Flag.c_plus_plus ->
      TCommentCpp (Token_c.CppDirective, i1)
	(* delete[] *)
  | (TCCro i1 :: _, Tdelete _ :: _) 
    when !Flag.c_plus_plus ->
      TCommentCpp (Token_c.CppDirective, i1)

	(* extern "_" tt *)
  | ((TString ((s, _), i1) | TMacroString (s, i1)) :: _ , Textern _ :: _) 
    when !Flag.c_plus_plus ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* ) const { *)
  | (Tconst i1 :: TOBrace _ :: _ , TCPar _ :: _) 
    when !Flag.c_plus_plus ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* xx const tt *)
  | (TIdent (s, i1)::(Tconst _|Tvolatile _|Trestrict _)::type_::_  , _) 
    when not_struct_enum before
	&& is_type type_ ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* xx struct *)
  | (TIdent (s, i1)::Tstruct _::_  , _) 
    when not_struct_enum before ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* xx tt *)
  | (TIdent (s, i1)::type_::_  , _) 
    when not_struct_enum before
	&& is_type type_ ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* tt xx yy *)
  | (TIdent (s, i1)::TIdent (s2, i2)::_  , seen::_) 
    when not_struct_enum before
	&& is_type seen ->
	  if is_macro s2 then
	    TIdent (s, i1)
	  else
	    TCommentCpp (Token_c.CppDirective, i1)

  | (TIdent (s2, i2)::_  , TIdent (s, i1)::seen::_) 
    when not_struct_enum before
	&& is_macro s2 && is_type seen ->
	  TCommentCpp (Token_c.CppDirective, i2)

	(* tt xx * *)
  | (TIdent (s, i1)::ptr  , seen::_) 
    when not_struct_enum before
	&& pointer ptr && is_type seen ->
	  TCommentCpp (Token_c.CppDirective, i1)

	(* tt * xx yy *)
  | (TIdent (s, i1)::TIdent(s2, i2)::_  , ptr) 
    when not_struct_enum before
	&& pointer ptr ->
	  if is_macro s2 then
	    TIdent (s, i1)
	  else
	    TCommentCpp (Token_c.CppDirective, i1)

	(* tt * xx yy *)
  | (TIdent(s2, i2)::_  , TIdent (s, i1)::ptr) 
    when not_struct_enum before
	&& is_macro s2 && pointer ptr ->
	  TCommentCpp (Token_c.CppDirective, i2)

        (* exception to next rule *)
  | (TIdent(s2, i2)::TOPar _ :: _ , TIdent(s, i1)::seen::_) 
    when not_struct_enum before
	&& is_macro s2 && is_type seen ->
	  TIdent(s2, i2)
	(* tt xx yy *)
  | (TIdent(s2, i2)::_  , TIdent(s, i1)::seen::_) 
    when not_struct_enum before
	&& is_macro s2 && is_type seen ->
	  TCommentCpp (Token_c.CppDirective, i2)

  (*  xx * yy      AND  in paramdecl *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before && (LP.current_context() =*= LP.InParameter)
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false) ptr
	&& ok_typedef s ->
      msg_typedef s i1 14; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* xx MM ( *)
  | (TIdent (s, i1)::TIdent (s2, i2)::TOPar _::_  , type_::_) when not_struct_enum before
      && ok_typedef s && is_macro s2 && is_type type_
        ->
	  TIdent (s, i1)
  (* xx yy *)
  | (TIdent (s, i1)::TIdent (s2, i2)::_  , _) when not_struct_enum before
      && ok_typedef s
        ->
         (* && not_annot s2 BUT lead to false positive*)
      msg_typedef s i1 2; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* xx inline *)
  | (TIdent (s, i1)::Tinline i2::_  , _) when not_struct_enum before
      && ok_typedef s
      ->

      msg_typedef s i1 3; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* [,(] xx [,)] AND param decl *)
  | (TIdent (s, i1)::(((TComma _|TCPar _)::_) as rest) ,
     ((TComma _ |TOPar _)::_ as bef))
    when not_struct_enum before && (LP.current_context() =*= LP.InParameter)
      && k_and_r rest 
      && not_has_type_before is_cparen rest 
      && not_has_type_before is_oparen bef
      ->

	TKRParam(s,i1)

  | (TIdent (s, i1)::((TComma _|TCPar _)::_) , (TComma _ |TOPar _)::_ )
    when not_struct_enum before && (LP.current_context() =*= LP.InParameter)
      && ok_typedef s
      ->

	msg_typedef s i1 4; LP.add_typedef_root s;
	TypedefIdent (s, i1)

  (* xx* [,)] *)
  (* specialcase:  [,(] xx* [,)] *)
  | (TIdent (s, i1)::ptr , (*(TComma _|TOPar _)::*)_ )
    when pointer ~followed_by:(function TComma _ |TCPar _ -> true | _ -> false) ptr
	&& not_struct_enum before
        (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      && ok_typedef s
    ->

      msg_typedef s i1 5; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* xx** [,)] *)
  (* specialcase:  [,(] xx** [,)] *)
  | (TIdent (s, i1)::TMul _::TMul _::(TComma _|TCPar _)::_ , (*(TComma _|TOPar _)::*)_ )
    when not_struct_enum before
      (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      && ok_typedef s
    ->

      msg_typedef s i1 6; LP.add_typedef_root s;
      TypedefIdent (s, i1)



  (* xx const *   USELESS because of next rule ? *)
  | (TIdent (s, i1)::(Tconst _|Tvolatile _|Trestrict _)::TMul _::_ , _ )
      when not_struct_enum before
      (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      && ok_typedef s
      ->

      msg_typedef s i1 7; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* xx const *)
  | (TIdent (s, i1)::(Tconst _|Tvolatile _|Trestrict _)::_ , _ )
      when not_struct_enum before
      && ok_typedef s
      (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      ->

      msg_typedef s i1 8; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* xx * const *)
  | (TIdent (s, i1)::ptr , _ )
      when pointer ~followed_by:(function Tconst _ | Tvolatile _ | Trestrict _ -> true | _ -> false) ptr
	  && not_struct_enum before
	  && ok_typedef s
      ->

      (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)

      msg_typedef s i1 9; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* ( const xx)  *)
  | (TIdent (s, i1)::TCPar _::_,  (Tconst _ | Tvolatile _|Trestrict _)::TOPar _::_) when
      ok_typedef s ->

      msg_typedef s i1 10; LP.add_typedef_root s;
      TypedefIdent (s, i1)



  (* ( xx ) [sizeof, ~] *)
  | (TIdent (s, i1)::TCPar _::(Tsizeof _|TTilde _)::_ ,     TOPar _::_ )
    when not_struct_enum before
      && ok_typedef s
    ->

      msg_typedef s i1 11; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* [(,] xx [   AND parameterdeclaration *)
  | (TIdent (s, i1)::TOCro _::_, (TComma _ |TOPar _)::_)
      when (LP.current_context() =*= LP.InParameter)
      && ok_typedef s
     ->

      msg_typedef s i1 12; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*------------------------------------------------------------*)
  (* if 'x*y' maybe an expr, maybe just a classic multiplication *)
  (* but if have a '=', or ','   I think not *)
  (*------------------------------------------------------------*)

  (* static xx * yy  *)
  | (TIdent (s, i1)::ptr ,
     (Tregister _|Tstatic _  |Tvolatile _|Tconst _|Trestrict _)::_) when
      pointer ~followed_by:(function TIdent _ -> true | _ -> false) ptr
	 && ok_typedef s
        ->

      msg_typedef s i1 13; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  TODO  xx * yy ; AND in start of compound element  *)


  (*  xx * yy,      AND  in paramdecl *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before && (LP.current_context() =*= LP.InParameter)
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TComma _ :: _ -> true | _ -> false) ptr
	&& ok_typedef s
      ->

      msg_typedef s i1 14; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (*  xx * yy ;     AND in Toplevel, except when have = before  *)
  | (TIdent (s, i1)::TMul _::TIdent (s2, i2)::TPtVirg _::_ , TEq _::_) ->
      TIdent (s, i1)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TPtVirg _ :: _ -> true | _ -> false) ptr
	&& (LP.is_top_or_struct (LP.current_context ()))
      ->

      msg_typedef s i1 15; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  xx * yy ,     AND in Toplevel  *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before && (LP.current_context () =*= LP.InTopLevel)
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TComma _ :: _ -> true | _ -> false) ptr
      ->

      msg_typedef s i1 16; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  xx * yy (     AND in Toplevel  *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before
	&& (LP.is_top_or_struct (LP.current_context ()))
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TOPar _ :: _ -> true | _ -> false) ptr
      ->

      msg_typedef s i1 17; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* xx * yy [ *)
  (* todo? enough ? cos in struct def we can have some expression ! *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before 
	&& (LP.is_top_or_struct (LP.current_context ()))
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TOCro _ :: _ -> true | _ -> false) ptr
      ->

      msg_typedef s i1 18;  LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* u16: 10; in struct *)
  | (TIdent (s, i1)::TDotDot _::_ , (TOBrace _ | TPtVirg _)::_)
    when       (LP.is_top_or_struct (LP.current_context ()))
      && ok_typedef s
      ->

      msg_typedef s i1 19;  LP.add_typedef_root s;
      TypedefIdent (s, i1)


    (*  why need TOPar condition as stated in preceding rule ? really needed ? *)
    (*   YES cos at toplevel can have some expression !! for instance when *)
    (*   enter in the dimension of an array *)
    (*
      | (TIdent s::TMul::TIdent s2::_ , _)
      when (take_safe 1 !passed_tok <> [Tstruct] &&
      (take_safe 1 !passed_tok <> [Tenum]))
      &&
      !LP._lexer_hint = Some LP.Toplevel ->
      msg_typedef s 20; LP.add_typedef_root s;
      TypedefIdent s
     *)

  (*  xx * yy =  *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TEq _ :: _ -> true | _ -> false) ptr
      ->

      msg_typedef s i1 21; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (*  xx * yy)      AND in paramdecl *)
  | (TIdent (s, i1)::ptr , _)
    when not_struct_enum before && (LP.current_context () =*= LP.InParameter)
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TCPar _ :: _ -> true | _ -> false) ptr
        ->

      msg_typedef s i1 22; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (*  xx * yy; *) (* wrong ? *)
  | (TIdent (s, i1)::ptr ,
     (TOBrace _| TPtVirg _)::_) when not_struct_enum before
	&& ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TPtVirg _ :: _ -> true | _ -> false) ptr
        ->

      msg_typedef s i1 23;  LP.add_typedef_root s;
      msg_maybe_dangereous_typedef s;
      TypedefIdent (s, i1)


  (*  xx * yy,  and ';' before xx *) (* wrong ? *)
  | (TIdent (s, i1)::ptr ,
     (TOBrace _| TPtVirg _)::_) when
      ok_typedef s 
	&& pointer ~followed_by:(function TIdent _ -> true | _ -> false)
              ~followed_by_more:(function TComma _ :: _ -> true | _ -> false) ptr
    ->

      msg_typedef s i1 24; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (* xx_t * yy *)
  | (TIdent (s, i1)::ptr , _)
      when s ==~ regexp_typedef && not_struct_enum before
        (* struct user_info_t sometimes *)
	&& ok_typedef s 
        && pointer ~followed_by:(function TIdent _ -> true | _ -> false) ptr
        ->

      msg_typedef s i1 25; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  xx ** yy *)  (* wrong ? *)
  | (TIdent (s, i1)::TMul _::TMul _::TIdent (s2, i2)::_ , _)
    when not_struct_enum before
	&& (LP.current_context() =*= LP.InParameter)
	&& ok_typedef s
    ->

      msg_typedef s i1 26; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  xx ** yy *)  (* wrong ? *)
  | (TIdent (s, i1)::TMul _::TMul _::TIdent (s2, i2)::_ , (TOBrace _ | TPtVirg _)::_)
    when not_struct_enum before
        (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
	&& ok_typedef s
	(* christia : this code catches 'a * *b' which is wrong 
	 *)
    ->

      msg_typedef s i1 26; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* xx *** yy *)
  | (TIdent (s, i1)::TMul _::TMul _::TMul _::TIdent (s2, i2)::_ , _)
    when not_struct_enum before
      && ok_typedef s
        (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      ->

      msg_typedef s i1 27; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (*  xx ** ) *)
  | (TIdent (s, i1)::TMul _::TMul _::TCPar _::_ , _)
    when not_struct_enum before
        (* && !LP._lexer_hint = Some LP.ParameterDeclaration *)
      && ok_typedef s
      ->

      msg_typedef s i1 28; LP.add_typedef_root s;
      TypedefIdent (s, i1)



  (* ----------------------------------- *)
  (* old: why not do like for other rules and start with TIdent ?
   * why do TOPar :: TIdent :: ..., _  and not TIdent :: ...,  TOPAr::_ ?
   * new: prefer now start with TIdent because otherwise the add_typedef_root
   * may have no effect if in second pass or if have disable the add_typedef.
   *)

  (*  (xx) yy *)
  | (TIdent (s, i1)::TCPar i2::(TIdent (_,i3)|TInt (_,i3))::_ ,
    (TOPar info)::x::_)
    when not (TH.is_stuff_taking_parenthized x) (* &&
      Ast_c.line_of_info i2 =|= Ast_c.line_of_info i3 - why useful?
      *)
      && ok_typedef s
      && not (ident x) (* possible K&R declaration *)
      ->

      msg_typedef s i1 29; LP.add_typedef_root s;
      (*TOPar info*)
      TypedefIdent (s, i1)


  (* (xx) (    yy)
   * but false positif: typedef int (xxx_t)(...), so do specialisation below.
   *)
  (*
  | (TIdent (s, i1)::TCPar _::TOPar _::_ , (TOPar info)::x::_)
    when not (TH.is_stuff_taking_parenthized x)
      && ok_typedef s
        ->
      msg_typedef s 30; LP.add_typedef_root s;
      (* TOPar info *)
      TypedefIdent (s, i1)
  *)
  (* special case:  = (xx) (    yy) *)
  | (TIdent (s, i1)::TCPar _::((TOPar _::_) as rest) ,
    (TOPar info)::(TEq _ |TEqEq _)::_)
    when ok_typedef s && paren_before_comma rest
        ->

      msg_typedef s i1 31; LP.add_typedef_root s;
      (* TOPar info *)
      TypedefIdent (s, i1)


  (*  (xx * ) yy *)
  | (TIdent (s, i1)::ptr, (TOPar info)::_)
    when ok_typedef s 
	&& pointer ~followed_by:(function TCPar _ -> true | _ -> false)
              ~followed_by_more:(function TIdent _ :: _ -> true | _ -> false) ptr
        ->

      msg_typedef s i1 32; LP.add_typedef_root s;
      (*TOPar info*)
      TypedefIdent (s,i1)


  (* (xx){ ... }  constructor *)
  | (TIdent (s, i1)::TCPar _::TOBrace _::_ , TOPar _::x::_)
      when (*s ==~ regexp_typedef && *) not (TH.is_stuff_taking_parenthized x)
      && ok_typedef s
        ->

      msg_typedef s i1 33; LP.add_typedef_root s;
      TypedefIdent (s, i1)


        (* can have sizeof on expression
           | (Tsizeof::TOPar::TIdent s::TCPar::_,   _) ->
           msg_typedef s; LP.add_typedef_root s;
           Tsizeof
         *)


  (* ----------------------------------- *)
  (* x ( *y )(params),  function pointer *)
  | (TIdent (s, i1)::TOPar _::TMul _::TIdent _::TCPar _::TOPar _::_,  _)
      when not_struct_enum before
      && ok_typedef s
        ->

      msg_typedef s i1 34; LP.add_typedef_root s;
      TypedefIdent (s, i1)

  (* x* ( *y )(params),  function pointer 2 *)
  | (TIdent (s, i1)::TMul _::TOPar _::TMul _::TIdent _::TCPar _::TOPar _::_,  _)
      when not_struct_enum before
      && ok_typedef s
        ->

      msg_typedef s i1 35; LP.add_typedef_root s;
      TypedefIdent (s, i1)


  (*-------------------------------------------------------------*)
  (* CPP *)
  (*-------------------------------------------------------------*)
  | ((TIfdef (_,ii) |TIfdefelse (_,ii) |TIfdefelif (_,ii) |TEndif (_,ii) |
      TIfdefBool (_,_,ii)|TIfdefMisc(_,_,ii)|TIfdefVersion(_,_,ii))
        as x)
    ::_, _
      ->

      (*
      if not !Flag_parsing_c.ifdef_to_if
      then TCommentCpp (Ast_c.CppIfDirective, ii)
      else
      *)
      (* not !LP._lexer_hint.toplevel *)
      if !Flag_parsing_c.ifdef_directive_passing
        || (pass >= 2)
      then begin

        if (LP.current_context () =*= LP.InInitializer)
        then begin
          pr2_cpp "In Initializer passing"; (* cheat: don't count in stat *)
          incr Stat.nIfdefInitializer;
        end else begin
          pr2_cpp("IFDEF: or related inside function. I treat it as comment");
          incr Stat.nIfdefPassing;
        end;
	let x =
	  match x with
	    TIfdef _ | TIfdefMisc _ | TIfdefVersion _ -> Token_c.IfDef
	  | TIfdefBool _ -> Token_c.IfDef0
	  | TIfdefelse _ | TIfdefelif _ -> Token_c.Else
	  | TEndif _ -> Token_c.Endif
	  | _ -> Token_c.Other in (* not possible here *)
        TCommentCpp (Token_c.CppIfDirective x, ii)
      end
      else x

  | (TUndef (ii) as x)::_, _
      ->
        if (pass >= 2)
        then begin
          pr2_cpp("UNDEF: I treat it as comment");
          TCommentCpp (Token_c.CppDirective, ii)
        end
        else x

  | (TCppDirectiveOther (ii) as x)::_, _
      ->
        if (pass >= 2)
        then begin
          pr2_cpp ("OTHER directive: I treat it as comment");
          TCommentCpp (Token_c.CppDirective, ii)
        end
        else x

   (* If ident contain a for_each, then certainly a macro. But to be
    * sure should look if there is a '{' after the ')', but it requires
    * to count the '('. Because this can be expensive, we do that only
    * when the token contains "for_each".
    *)
  | (TIdent (s, i1)::TOPar _::rest, _)
     when not (LP.current_context () =*= LP.InTopLevel)
      (* otherwise a function such as static void loopback_enable(int i) {
       * will be considered as a loop
       *)
        ->

      if s ==~ regexp_foreach &&
        is_really_foreach (Common.take_safe forLOOKAHEAD rest)

      then begin
        msg_foreach s;
        TMacroIterator (s, i1)
      end
      else TIdent (s, i1)

(*  (* christia: here insert support for macros on top level *)
  | TIdent (s, ii) :: tl :: _, _ when
    can_be_on_top_level tl && LP.current_context () = InTopLevel ->
      pr2_cpp ("'" ^ s ^ "' looks like a macro, I treat it as comment");
      TCommentCpp (Token_c.CppDirective, ii)
*)      
    
(*-------------------------------------------------------------*)
 | v::xs, _ -> v
 | _ -> raise (Impossible 93)

let lookahead ~pass a b =
  Common.profile_code "C parsing.lookahead" (fun () -> lookahead2 ~pass a b)


