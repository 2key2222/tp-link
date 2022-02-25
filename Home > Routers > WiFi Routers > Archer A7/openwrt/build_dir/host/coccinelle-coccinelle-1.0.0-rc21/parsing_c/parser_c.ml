type token =
  | TUnknown of (Ast_c.info)
  | TCommentSpace of (Ast_c.info)
  | TCommentNewline of (Ast_c.info)
  | TComment of (Ast_c.info)
  | TInt of ((string * (Ast_c.sign * Ast_c.base)) * Ast_c.info)
  | TFloat of ((string * Ast_c.floatType) * Ast_c.info)
  | TChar of ((string * Ast_c.isWchar) * Ast_c.info)
  | TString of ((string * Ast_c.isWchar) * Ast_c.info)
  | TQuote of ((string * Ast_c.isWchar) * Ast_c.info)
  | TPct of (Ast_c.info)
  | TFormat of (string * Ast_c.info)
  | TSubString of (string * Ast_c.info)
  | TDecimal of ((string * string (*n*) * string (*p*)) * Ast_c.info)
  | TIdent of (string * Ast_c.info)
  | TKRParam of (string * Ast_c.info)
  | Tconstructorname of (string * Ast_c.info)
  | TypedefIdent of (string * Ast_c.info)
  | TOPar of (Ast_c.info)
  | TCPar of (Ast_c.info)
  | TOBrace of (Ast_c.info)
  | TCBrace of (Ast_c.info)
  | TOCro of (Ast_c.info)
  | TCCro of (Ast_c.info)
  | TDot of (Ast_c.info)
  | TComma of (Ast_c.info)
  | TPtrOp of (Ast_c.info)
  | TInc of (Ast_c.info)
  | TDec of (Ast_c.info)
  | TAssign of (Ast_c.assignOp * Ast_c.info)
  | TEq of (Ast_c.info)
  | TWhy of (Ast_c.info)
  | TTilde of (Ast_c.info)
  | TBang of (Ast_c.info)
  | TEllipsis of (Ast_c.info)
  | TDotDot of (Ast_c.info)
  | TPtVirg of (Ast_c.info)
  | TOrLog of (Ast_c.info)
  | TAndLog of (Ast_c.info)
  | TOr of (Ast_c.info)
  | TXor of (Ast_c.info)
  | TAnd of (Ast_c.info)
  | TEqEq of (Ast_c.info)
  | TNotEq of (Ast_c.info)
  | TInf of (Ast_c.info)
  | TSup of (Ast_c.info)
  | TInfEq of (Ast_c.info)
  | TSupEq of (Ast_c.info)
  | TShl of (Ast_c.info)
  | TShr of (Ast_c.info)
  | TPlus of (Ast_c.info)
  | TMinus of (Ast_c.info)
  | TMul of (Ast_c.info)
  | TDiv of (Ast_c.info)
  | TMod of (Ast_c.info)
  | TMax of (Ast_c.info)
  | TMin of (Ast_c.info)
  | Tchar of (Ast_c.info)
  | Tshort of (Ast_c.info)
  | Tint of (Ast_c.info)
  | Tdouble of (Ast_c.info)
  | Tfloat of (Ast_c.info)
  | Tlong of (Ast_c.info)
  | Tunsigned of (Ast_c.info)
  | Tsigned of (Ast_c.info)
  | Tvoid of (Ast_c.info)
  | Tsize_t of (Ast_c.info)
  | Tssize_t of (Ast_c.info)
  | Tptrdiff_t of (Ast_c.info)
  | Tauto of (Ast_c.info)
  | Tregister of (Ast_c.info)
  | Textern of (Ast_c.info)
  | Tstatic of (Ast_c.info)
  | Ttypedef of (Ast_c.info)
  | Tconst of (Ast_c.info)
  | Tvolatile of (Ast_c.info)
  | Tstruct of (Ast_c.info)
  | Tunion of (Ast_c.info)
  | Tenum of (Ast_c.info)
  | Tdecimal of (Ast_c.info)
  | Texec of (Ast_c.info)
  | Tbreak of (Ast_c.info)
  | Telse of (Ast_c.info)
  | Tswitch of (Ast_c.info)
  | Tcase of (Ast_c.info)
  | Tcontinue of (Ast_c.info)
  | Tfor of (Ast_c.info)
  | Tdo of (Ast_c.info)
  | Tif of (Ast_c.info)
  | Twhile of (Ast_c.info)
  | Treturn of (Ast_c.info)
  | Tgoto of (Ast_c.info)
  | Tdefault of (Ast_c.info)
  | Tsizeof of (Ast_c.info)
  | Tnew of (Ast_c.info)
  | Tdelete of (Ast_c.info)
  | TOParCplusplusInit of (Ast_c.info)
  | Tnamespace of (Ast_c.info)
  | Trestrict of (Ast_c.info)
  | Tasm of (Ast_c.info)
  | Tattribute of (Ast_c.info)
  | TattributeNoarg of (Ast_c.info)
  | Tinline of (Ast_c.info)
  | Ttypeof of (Ast_c.info)
  | TDefine of (Ast_c.info)
  | TDefParamVariadic of ((string * Ast_c.info))
  | TCppEscapedNewline of (Ast_c.info)
  | TCppConcatOp of (Ast_c.info)
  | TOParDefine of (Ast_c.info)
  | TOBraceDefineInit of (Ast_c.info)
  | TIdentDefine of ((string * Ast_c.info))
  | TDefEOL of (Ast_c.info)
  | TInclude of ((string * string * bool ref * Ast_c.info))
  | TIncludeStart of ((Ast_c.info * bool ref))
  | TIncludeFilename of ((string * Ast_c.info))
  | TIfdef of (((int * int) option ref * Ast_c.info))
  | TIfdefelse of (((int * int) option ref * Ast_c.info))
  | TIfdefelif of (((int * int) option ref * Ast_c.info))
  | TEndif of (((int * int) option ref * Ast_c.info))
  | TIfdefBool of ((bool * (int * int) option ref * Ast_c.info))
  | TIfdefMisc of ((bool * (int * int) option ref * Ast_c.info))
  | TIfdefVersion of ((bool * (int * int) option ref * Ast_c.info))
  | TUndef of (Ast_c.info)
  | TPragma of (Ast_c.info)
  | TCppDirectiveOther of (Ast_c.info)
  | TMacroAttr of ((string * Ast_c.info))
  | TMacroStmt of ((string * Ast_c.info))
  | TMacroIdentBuilder of ((string * Ast_c.info))
  | TMacroString of ((string * Ast_c.info))
  | TMacroDecl of ((string * Ast_c.info))
  | TMacroDeclConst of (Ast_c.info)
  | TMacroIterator of ((string * Ast_c.info))
  | TMacroAttrStorage of ((string * Ast_c.info))
  | TCommentSkipTagStart of (Ast_c.info)
  | TCommentSkipTagEnd of (Ast_c.info)
  | TCParEOL of (Ast_c.info)
  | TAction of (Ast_c.info)
  | TCommentMisc of (Ast_c.info)
  | TCommentCpp of ((Token_c.cppcommentkind * Ast_c.info))
  | EOF of (Ast_c.info)

open Parsing;;
let _ = parse_error;;
# 2 "parser_c.mly"
(* Yoann Padioleau
 *
 * Copyright (C) 2002, 2006, 2007, 2008, 2009 Yoann Padioleau
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

open Ast_c

module LP = Lexer_parser
open Lexer_parser (* for the fields *)

open Semantic_c (* Semantic exn *)
module T = Token_c

(*****************************************************************************)
(* Wrappers *)
(*****************************************************************************)
let warning s v =
  if !Flag_parsing_c.verbose_parsing
  then Common.warning ("PARSING: " ^ s) v
  else v

let pr2, pr2_once = Common.mk_pr2_wrappers Flag_parsing_c.verbose_parsing

(*****************************************************************************)
(* Parse helpers functions *)
(*****************************************************************************)

(*-------------------------------------------------------------------------- *)
(* Type related *)
(*-------------------------------------------------------------------------- *)

type shortLong      = Short  | Long | LongLong

type decl = {
  storageD: storagebis wrap;
  typeD: ((sign option) * (shortLong option) * (typeCbis option)) wrap;
  qualifD: typeQualifierbis wrap;
  inlineD: bool             wrap;
  (* note: have a full_info: parse_info list; to remember ordering
   * between storage, qualifier, type ? well this info is already in
   * the Ast_c.info, just have to sort them to get good order *)
}

let nullDecl = {
  storageD = NoSto, [];
  typeD = (None, None, None), [];
  qualifD = nullQualif;
  inlineD = false, [];
}
let fake_pi = Common.fake_parse_info

let addStorageD  = function
  | ((x,ii), ({storageD = (NoSto,[])} as v)) -> { v with storageD = (x, [ii]) }
  | ((x,ii), ({storageD = (y, ii2)} as v)) ->
      if x =*= y then warning "duplicate storage classes" v
      else raise (Semantic ("multiple storage classes", fake_pi))

let addInlineD  = function
  | ((true,ii), ({inlineD = (false,[])} as v)) -> { v with inlineD=(true,[ii])}
  | ((true,ii), ({inlineD = (true, ii2)} as v)) -> warning "duplicate inline" v
  | _ -> raise (Impossible 86)


let addTypeD     = function
  | ((Left3 Signed,ii)   ,({typeD = ((Some Signed,  b,c),ii2)} as v)) ->
      warning "duplicate 'signed'"   v
  | ((Left3 UnSigned,ii) ,({typeD = ((Some UnSigned,b,c),ii2)} as v)) ->
      warning "duplicate 'unsigned'" v
  | ((Left3 _,ii),        ({typeD = ((Some _,b,c),ii2)} as _v)) ->
      raise (Semantic ("both signed and unsigned specified", fake_pi))
  | ((Left3 x,ii),        ({typeD = ((None,b,c),ii2)} as v))   ->
      {v with typeD = (Some x,b,c),ii ++ ii2}

  | ((Middle3 Short,ii),  ({typeD = ((a,Some Short,c),ii2)} as v)) ->
      warning "duplicate 'short'" v


  (* gccext: long long allowed *)
  | ((Middle3 Long,ii),   ({typeD = ((a,Some Long ,c),ii2)} as v)) ->
      { v with typeD = (a, Some LongLong, c),ii++ii2 }
  | ((Middle3 Long,ii),   ({typeD = ((a,Some LongLong ,c),ii2)} as v)) ->
      warning "triplicate 'long'" v


  | ((Middle3 _,ii),      ({typeD = ((a,Some _,c),ii2)} as _v)) ->
      raise (Semantic ("both long and short specified", fake_pi))
  | ((Middle3 x,ii),      ({typeD = ((a,None,c),ii2)} as v))  ->
      {v with typeD = (a, Some x,c),ii++ii2}

  | ((Right3 t,ii),       ({typeD = ((a,b,Some x),ii2)} as _v)) ->
      raise (Semantic ((Printf.sprintf "two or more data types: t %s ii %s\ntypeD %s ii2 %s\n" (Dumper.dump t) (Dumper.dump ii) (Dumper.dump x) (Dumper.dump ii2)), fake_pi))
  | ((Right3 t,ii),       ({typeD = ((a,b,None),ii2)} as v))   ->
      {v with typeD = (a,b, Some t),ii++ii2}


let addQualif = function
  | ({const=true},   ({const=true} as x)) ->   warning "duplicate 'const'" x
  | ({volatile=true},({volatile=true} as x))-> warning "duplicate 'volatile'" x
  | ({const=true},    v) -> {v with const=true}
  | ({volatile=true}, v) -> {v with volatile=true}
  | _ ->
      internal_error "there is no noconst or novolatile keyword"

let addQualifD ((qu,ii), ({qualifD = (v,ii2)} as x)) =
  { x with qualifD = (addQualif (qu, v),ii::ii2) }


(*-------------------------------------------------------------------------- *)
(* Declaration/Function related *)
(*-------------------------------------------------------------------------- *)


(* stdC: type section, basic integer types (and ritchie)
 * To understand the code, just look at the result (right part of the PM)
 * and go back.
 *)
let (fixDeclSpecForDecl: decl -> (fullType * (storage wrap)))  = function
 {storageD = (st,iist);
  qualifD = (qu,iiq);
  typeD = (ty,iit);
  inlineD = (inline,iinl);
  } ->
   let ty',iit' =
   (match ty with
 | (None,None,None)       ->
     (* generate fake_info, otherwise type_annotater can crash in
      * offset.
      *)
     warning "type defaults to 'int'" (defaultInt, [fakeInfo fake_pi])
 | (None, None, Some t)   -> (t, iit)

 | (Some sign,   None, (None| Some (BaseType (IntType (Si (_,CInt))))))  ->
     BaseType(IntType (Si (sign, CInt))), iit
 | ((None|Some Signed),Some x,(None|Some(BaseType(IntType (Si (_,CInt)))))) ->
     BaseType(IntType (Si (Signed, [Short,CShort; Long, CLong; LongLong, CLongLong] +> List.assoc x))), iit
 | (Some UnSigned, Some x, (None| Some (BaseType (IntType (Si (_,CInt))))))->
     BaseType(IntType (Si (UnSigned, [Short,CShort; Long, CLong; LongLong, CLongLong] +> List.assoc x))), iit
 | (Some sign,   None, (Some (BaseType (IntType CChar))))   ->
     BaseType(IntType (Si (sign, CChar2))), iit
 | (None, Some Long,(Some(BaseType(FloatType CDouble))))    ->
     BaseType (FloatType (CLongDouble)), iit

 | (Some _,_, Some _) ->
     (*mine*)
     raise (Semantic ("signed, unsigned valid only for char and int", fake_pi))
 | (_,Some _,(Some(BaseType(FloatType (CFloat|CLongDouble))))) ->
     raise (Semantic ("long or short specified with floating type", fake_pi))
 | (_,Some Short,(Some(BaseType(FloatType CDouble)))) ->
     raise (Semantic ("the only valid combination is long double", fake_pi))

 | (_, Some _, Some _) ->
     (* mine *)
     raise (Semantic ("long, short valid only for int or float", fake_pi))

     (* if do short uint i, then gcc say parse error, strange ? it is
      * not a parse error, it is just that we dont allow with typedef
      * either short/long or signed/unsigned. In fact, with
      * parse_typedef_fix2 (with et() and dt()) now I say too parse
      * error so this code is executed only when do short struct
      * {....} and never with a typedef cos now we parse short uint i
      * as short ident ident => parse error (cos after first short i
      * pass in dt() mode) *)

   )
   in
   ((qu, iiq),
   (ty', iit'))
     ,((st, inline),iist++iinl)


let fixDeclSpecForParam = function ({storageD = (st,iist)} as r) ->
  let ((qu,ty) as v,_st) = fixDeclSpecForDecl r in
  match st with
  | (Sto Register) -> (v, true), iist
  | NoSto -> (v, false), iist
  | _ ->
      raise
        (Semantic ("storage class specified for parameter of function",
                  fake_pi))

let fixDeclSpecForMacro = function ({storageD = (st,iist)} as r) ->
  let ((qu,ty) as v,_st) = fixDeclSpecForDecl r in
  match st with
  | NoSto -> v
  | _ ->
      raise
        (Semantic ("storage class specified for macro type decl",
                  fake_pi))


let fixDeclSpecForFuncDef x =
  let (returnType,storage) = fixDeclSpecForDecl x in
  (match fst (unwrap storage) with
  | StoTypedef ->
      raise (Semantic ("function definition declared 'typedef'", fake_pi))
  | _ -> (returnType, storage)
  )


(* parameter: (this is the context where we give parameter only when
 * in func DEFINITION not in funct DECLARATION) We must have a name.
 * This function ensure that we give only parameterTypeDecl with well
 * formed Classic constructor todo?: do we accept other declaration
 * in ? so I must add them to the compound of the deffunc. I dont
 * have to handle typedef pb here cos C forbid to do VF f { ... }
 * with VF a typedef of func cos here we dont see the name of the
 * argument (in the typedef)
 *)
let (fixOldCDecl: fullType -> fullType) = fun ty ->
  match Ast_c.unwrap_typeC ty with
  | FunctionType (fullt, (params, (b, iib))) ->

      (* stdC: If the prototype declaration declares a parameter for a
       * function that you are defining (it is part of a function
       * definition), then you must write a name within the declarator.
       * Otherwise, you can omit the name. *)
      (match params with
      | [{p_namei = None; p_type = ty2},_] ->
          (match Ast_c.unwrap_typeC ty2 with
          | BaseType Void ->
              ty
          | _ ->
              pr2_once ("SEMANTIC:parameter name omitted, but I continue");
              ty
          )

      | params ->
          (params +> List.iter (fun (param,_) ->
            match param with
            | {p_namei = None} ->
              (* if majuscule, then certainly macro-parameter *)
                pr2_once ("SEMANTIC:parameter name omitted, but I continue");
	    | _ -> ()
          ));
          ty
      )

        (* todo? can we declare prototype in the decl or structdef,
           ... => length <> but good kan meme *)
  | _ ->
      (* gcc say parse error but dont see why *)
      raise (Semantic ("seems this is not a function", fake_pi))


let fixFunc (typ, compound, old_style_opt) =
  let (cp,iicp) = compound in

  let (name, ty,   (st,iist),  attrs) = typ in

  let (qu, tybis) = ty in

  match Ast_c.unwrap_typeC ty with
  | FunctionType (fullt, (params,abool)) ->
      let iifunc = Ast_c.get_ii_typeC_take_care tybis in

      let iistart = Ast_c.fakeInfo () in
      assert (qu =*= nullQualif);

      (match params with
      | [{p_namei= None; p_type = ty2}, _] ->
          (match Ast_c.unwrap_typeC ty2 with
          | BaseType Void ->  ()
          | _ ->
                (* failwith "internal errror: fixOldCDecl not good" *)
              ()
          )
      | params ->
          params +> List.iter (function
          | ({p_namei = Some s}, _) -> ()
	  | _ -> ()
                (* failwith "internal errror: fixOldCDecl not good" *)
          )
      );
      (* bugfix: cf tests_c/function_pointer4.c.
       * Apparemment en C on peut syntaxiquement ecrire ca:
       *
       *   void a(int)(int x);
       * mais apres gcc gueule au niveau semantique avec:
       *   xxx.c:1: error: 'a' declared as function returning a function
       * Je ne faisais pas cette verif. Sur du code comme
       *   void METH(foo)(int x) { ...} , le parser croit (a tort) que foo
       * est un typedef, et donc c'est parsé comme l'exemple precedent,
       * ce qui ensuite confuse l'unparser qui n'est pas habitué
       * a avoir dans le returnType un FunctionType et qui donc
       * pr_elem les ii dans le mauvais sens ce qui genere au final
       * une exception. Hence this fix to at least detect the error
       * at parsing time (not unparsing time).
       *)
      (match Ast_c.unwrap_typeC fullt with
      | FunctionType _ ->
          let s = Ast_c.str_of_name name in
          let iis = Ast_c.info_of_name name in
          pr2 (spf "WEIRD: %s declared as function returning a function." s);
          pr2 (spf "This is probably because of a macro. Extend standard.h");
          raise (Semantic (spf "error: %s " s, Ast_c.parse_info_of_info iis))
      | _ -> ()
      );

      (* it must be nullQualif,cos parser construct only this*)
      {f_name = name;
       f_type = (fullt, (params, abool));
       f_storage = st;
       f_body = cp;
       f_attr = attrs;
       f_old_c_style = old_style_opt;
      },
      (iifunc++iicp++[iistart]++iist)
  | _ ->
      raise
        (Semantic
            ("you are trying to do a function definition but you dont give " ^
             "any parameter", fake_pi))


(*-------------------------------------------------------------------------- *)
(* parse_typedef_fix2 *)
(*-------------------------------------------------------------------------- *)

let dt s () =
  if !Flag_parsing_c.debug_etdt then pr2 ("<" ^ s);
  LP.disable_typedef ()

let et s () =
  if !Flag_parsing_c.debug_etdt then pr2 (">" ^ s);
  LP.enable_typedef ()


let fix_add_params_ident x =
  let (s, ty, st, _attrs) = x in
  match Ast_c.unwrap_typeC ty with
  | FunctionType (fullt, (params, bool)) ->

      (match params with
      | [{p_namei=None; p_type=ty2}, _] ->
          (match Ast_c.unwrap_typeC ty2 with
          | BaseType Void -> ()
          | _ ->
              (* failwith "internal errror: fixOldCDecl not good" *)
              ()
          )
      | params ->
          params +> List.iter (function
          | ({p_namei= Some name}, _) ->
              LP.add_ident (Ast_c.str_of_name s)
	  | _ ->
              ()
                (* failwith "internal errror: fixOldCDecl not good" *)
          )
      )
  | _ -> ()



(*-------------------------------------------------------------------------- *)
(* shortcuts *)
(*-------------------------------------------------------------------------- *)

let mk_e e ii = Ast_c.mk_e e ii

let mk_string_wrap (s,info) = (s, [info])

# 517 "parser_c.ml"
let yytransl_const = [|
    0|]

let yytransl_block = [|
  257 (* TUnknown *);
  258 (* TCommentSpace *);
  259 (* TCommentNewline *);
  260 (* TComment *);
  261 (* TInt *);
  262 (* TFloat *);
  263 (* TChar *);
  264 (* TString *);
  265 (* TQuote *);
  266 (* TPct *);
  267 (* TFormat *);
  268 (* TSubString *);
  269 (* TDecimal *);
  270 (* TIdent *);
  271 (* TKRParam *);
  272 (* Tconstructorname *);
  273 (* TypedefIdent *);
  274 (* TOPar *);
  275 (* TCPar *);
  276 (* TOBrace *);
  277 (* TCBrace *);
  278 (* TOCro *);
  279 (* TCCro *);
  280 (* TDot *);
  281 (* TComma *);
  282 (* TPtrOp *);
  283 (* TInc *);
  284 (* TDec *);
  285 (* TAssign *);
  286 (* TEq *);
  287 (* TWhy *);
  288 (* TTilde *);
  289 (* TBang *);
  290 (* TEllipsis *);
  291 (* TDotDot *);
  292 (* TPtVirg *);
  293 (* TOrLog *);
  294 (* TAndLog *);
  295 (* TOr *);
  296 (* TXor *);
  297 (* TAnd *);
  298 (* TEqEq *);
  299 (* TNotEq *);
  300 (* TInf *);
  301 (* TSup *);
  302 (* TInfEq *);
  303 (* TSupEq *);
  304 (* TShl *);
  305 (* TShr *);
  306 (* TPlus *);
  307 (* TMinus *);
  308 (* TMul *);
  309 (* TDiv *);
  310 (* TMod *);
  311 (* TMax *);
  312 (* TMin *);
  313 (* Tchar *);
  314 (* Tshort *);
  315 (* Tint *);
  316 (* Tdouble *);
  317 (* Tfloat *);
  318 (* Tlong *);
  319 (* Tunsigned *);
  320 (* Tsigned *);
  321 (* Tvoid *);
  322 (* Tsize_t *);
  323 (* Tssize_t *);
  324 (* Tptrdiff_t *);
  325 (* Tauto *);
  326 (* Tregister *);
  327 (* Textern *);
  328 (* Tstatic *);
  329 (* Ttypedef *);
  330 (* Tconst *);
  331 (* Tvolatile *);
  332 (* Tstruct *);
  333 (* Tunion *);
  334 (* Tenum *);
  335 (* Tdecimal *);
  336 (* Texec *);
  337 (* Tbreak *);
  338 (* Telse *);
  339 (* Tswitch *);
  340 (* Tcase *);
  341 (* Tcontinue *);
  342 (* Tfor *);
  343 (* Tdo *);
  344 (* Tif *);
  345 (* Twhile *);
  346 (* Treturn *);
  347 (* Tgoto *);
  348 (* Tdefault *);
  349 (* Tsizeof *);
  350 (* Tnew *);
  351 (* Tdelete *);
  352 (* TOParCplusplusInit *);
  353 (* Tnamespace *);
  354 (* Trestrict *);
  355 (* Tasm *);
  356 (* Tattribute *);
  357 (* TattributeNoarg *);
  358 (* Tinline *);
  359 (* Ttypeof *);
  360 (* TDefine *);
  361 (* TDefParamVariadic *);
  362 (* TCppEscapedNewline *);
  363 (* TCppConcatOp *);
  364 (* TOParDefine *);
  365 (* TOBraceDefineInit *);
  366 (* TIdentDefine *);
  367 (* TDefEOL *);
  368 (* TInclude *);
  369 (* TIncludeStart *);
  370 (* TIncludeFilename *);
  371 (* TIfdef *);
  372 (* TIfdefelse *);
  373 (* TIfdefelif *);
  374 (* TEndif *);
  375 (* TIfdefBool *);
  376 (* TIfdefMisc *);
  377 (* TIfdefVersion *);
  378 (* TUndef *);
  379 (* TPragma *);
  380 (* TCppDirectiveOther *);
  381 (* TMacroAttr *);
  382 (* TMacroStmt *);
  383 (* TMacroIdentBuilder *);
  384 (* TMacroString *);
  385 (* TMacroDecl *);
  386 (* TMacroDeclConst *);
  387 (* TMacroIterator *);
  388 (* TMacroAttrStorage *);
  389 (* TCommentSkipTagStart *);
  390 (* TCommentSkipTagEnd *);
  391 (* TCParEOL *);
  392 (* TAction *);
  393 (* TCommentMisc *);
  394 (* TCommentCpp *);
    0 (* EOF *);
    0|]

let yylhs = "\255\255\
\001\000\006\000\006\000\006\000\008\000\008\000\009\000\010\000\
\010\000\012\000\012\000\012\000\011\000\011\000\011\000\013\000\
\013\000\004\000\004\000\015\000\015\000\015\000\016\000\016\000\
\018\000\018\000\018\000\018\000\018\000\018\000\018\000\018\000\
\018\000\018\000\018\000\018\000\018\000\018\000\018\000\018\000\
\018\000\018\000\018\000\018\000\018\000\017\000\017\000\020\000\
\020\000\020\000\020\000\020\000\020\000\020\000\020\000\020\000\
\025\000\025\000\025\000\025\000\025\000\025\000\024\000\024\000\
\024\000\024\000\024\000\024\000\024\000\023\000\023\000\023\000\
\023\000\023\000\023\000\023\000\023\000\023\000\023\000\028\000\
\028\000\028\000\028\000\028\000\028\000\028\000\028\000\028\000\
\028\000\028\000\031\000\031\000\035\000\035\000\036\000\037\000\
\037\000\037\000\040\000\040\000\040\000\039\000\041\000\044\000\
\021\000\022\000\003\000\045\000\045\000\045\000\045\000\045\000\
\045\000\045\000\045\000\045\000\045\000\046\000\046\000\046\000\
\046\000\053\000\053\000\055\000\055\000\055\000\034\000\057\000\
\057\000\059\000\059\000\059\000\060\000\060\000\060\000\060\000\
\060\000\047\000\047\000\048\000\048\000\048\000\049\000\049\000\
\049\000\049\000\049\000\049\000\049\000\049\000\050\000\050\000\
\050\000\050\000\050\000\050\000\032\000\032\000\051\000\051\000\
\065\000\067\000\067\000\067\000\067\000\067\000\052\000\052\000\
\052\000\052\000\069\000\069\000\069\000\069\000\070\000\070\000\
\068\000\071\000\071\000\071\000\071\000\071\000\071\000\071\000\
\071\000\071\000\071\000\071\000\071\000\071\000\071\000\071\000\
\071\000\071\000\071\000\071\000\071\000\071\000\071\000\071\000\
\071\000\071\000\071\000\071\000\071\000\071\000\071\000\071\000\
\071\000\071\000\071\000\072\000\072\000\072\000\072\000\072\000\
\072\000\072\000\072\000\072\000\072\000\072\000\072\000\072\000\
\072\000\072\000\072\000\072\000\072\000\072\000\027\000\075\000\
\075\000\075\000\076\000\076\000\077\000\078\000\078\000\079\000\
\079\000\080\000\080\000\080\000\080\000\082\000\082\000\081\000\
\081\000\081\000\081\000\081\000\081\000\084\000\085\000\089\000\
\089\000\089\000\090\000\090\000\090\000\090\000\090\000\090\000\
\090\000\090\000\090\000\088\000\088\000\092\000\092\000\092\000\
\092\000\038\000\038\000\094\000\094\000\094\000\095\000\095\000\
\097\000\097\000\097\000\097\000\098\000\083\000\083\000\005\000\
\005\000\099\000\099\000\100\000\100\000\100\000\100\000\100\000\
\100\000\100\000\100\000\105\000\105\000\105\000\105\000\105\000\
\105\000\105\000\105\000\107\000\107\000\107\000\107\000\107\000\
\106\000\106\000\054\000\093\000\109\000\109\000\109\000\103\000\
\111\000\110\000\110\000\110\000\110\000\112\000\112\000\104\000\
\104\000\104\000\029\000\029\000\116\000\116\000\116\000\116\000\
\116\000\118\000\118\000\118\000\114\000\114\000\119\000\119\000\
\119\000\124\000\124\000\124\000\124\000\125\000\125\000\125\000\
\125\000\125\000\126\000\126\000\128\000\128\000\128\000\129\000\
\129\000\129\000\073\000\120\000\132\000\130\000\131\000\122\000\
\122\000\074\000\074\000\074\000\137\000\137\000\138\000\061\000\
\140\000\140\000\141\000\141\000\139\000\139\000\139\000\142\000\
\143\000\143\000\145\000\145\000\144\000\144\000\144\000\062\000\
\062\000\062\000\062\000\062\000\062\000\147\000\147\000\147\000\
\146\000\146\000\146\000\146\000\146\000\146\000\146\000\146\000\
\146\000\146\000\146\000\146\000\146\000\150\000\150\000\150\000\
\150\000\150\000\063\000\063\000\063\000\063\000\063\000\063\000\
\063\000\151\000\151\000\151\000\007\000\007\000\002\000\002\000\
\002\000\002\000\002\000\002\000\002\000\002\000\056\000\058\000\
\134\000\136\000\113\000\115\000\121\000\123\000\086\000\087\000\
\033\000\033\000\064\000\064\000\066\000\066\000\026\000\026\000\
\102\000\102\000\148\000\148\000\133\000\133\000\127\000\127\000\
\135\000\135\000\101\000\101\000\091\000\091\000\042\000\042\000\
\043\000\043\000\014\000\014\000\014\000\117\000\117\000\152\000\
\152\000\108\000\108\000\096\000\030\000\030\000\149\000\149\000\
\019\000\019\000\000\000\000\000\000\000\000\000\000\000"

let yylen = "\002\000\
\002\000\000\000\002\000\006\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\003\000\002\000\004\000\001\000\
\003\000\001\000\003\000\001\000\003\000\003\000\001\000\005\000\
\001\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\003\000\003\000\003\000\
\003\000\003\000\003\000\003\000\003\000\001\000\004\000\001\000\
\002\000\002\000\002\000\002\000\004\000\002\000\005\000\002\000\
\004\000\003\000\004\000\003\000\001\000\004\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\004\000\004\000\
\003\000\003\000\003\000\002\000\002\000\005\000\007\000\001\000\
\001\000\001\000\001\000\003\000\001\000\001\000\003\000\001\000\
\002\000\003\000\000\000\002\000\002\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\002\000\005\000\006\000\001\000\004\000\003\000\004\000\006\000\
\003\000\001\000\001\000\002\000\003\000\002\000\003\000\000\000\
\001\000\001\000\001\000\002\000\001\000\001\000\001\000\001\000\
\001\000\001\000\002\000\005\000\007\000\005\000\005\000\007\000\
\006\000\007\000\006\000\007\000\005\000\004\000\002\000\001\000\
\001\000\001\000\002\000\003\000\001\000\001\000\002\000\001\000\
\002\000\001\000\004\000\007\000\001\000\000\000\000\000\004\000\
\003\000\002\000\000\000\003\000\003\000\004\000\000\000\003\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\006\000\004\000\001\000\004\000\004\000\001\000\001\000\
\001\000\001\000\003\000\001\000\001\000\001\000\001\000\002\000\
\001\000\001\000\002\000\002\000\003\000\001\000\001\000\001\000\
\003\000\003\000\004\000\003\000\004\000\001\000\001\000\001\000\
\001\000\002\000\003\000\002\000\003\000\003\000\004\000\002\000\
\003\000\003\000\004\000\001\000\003\000\001\000\002\000\002\000\
\001\000\001\000\002\000\001\000\002\000\002\000\001\000\002\000\
\001\000\001\000\002\000\002\000\001\000\001\000\002\000\001\000\
\002\000\001\000\002\000\002\000\003\000\005\000\006\000\007\000\
\007\000\008\000\009\000\001\000\001\000\001\000\001\000\002\000\
\002\000\002\000\002\000\001\000\001\000\001\000\001\000\001\000\
\001\000\002\000\001\000\001\000\001\000\003\000\004\000\001\000\
\001\000\001\000\002\000\002\000\002\000\004\000\005\000\001\000\
\004\000\002\000\001\000\003\000\001\000\004\000\002\000\003\000\
\003\000\002\000\003\000\005\000\001\000\000\000\005\000\004\000\
\002\000\001\000\001\000\002\000\002\000\001\000\001\000\005\000\
\001\000\001\000\003\000\002\000\001\000\002\000\003\000\001\000\
\002\000\002\000\001\000\001\000\001\000\001\000\001\000\001\000\
\000\000\005\000\006\000\002\000\001\000\003\000\001\000\001\000\
\001\000\002\000\001\000\002\000\002\000\003\000\003\000\001\000\
\002\000\001\000\003\000\004\000\001\000\002\000\002\000\002\000\
\004\000\007\000\003\000\004\000\001\000\003\000\002\000\001\000\
\001\000\001\000\001\000\001\000\002\000\002\000\001\000\005\000\
\006\000\004\000\005\000\001\000\000\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\005\000\004\000\002\000\001\000\001\000\005\000\001\000\
\001\000\001\000\001\000\005\000\001\000\001\000\001\000\001\000\
\001\000\001\000\001\000\001\000\001\000\001\000\001\000\001\000\
\001\000\002\000\001\000\002\000\001\000\003\000\001\000\003\000\
\001\000\003\000\001\000\002\000\001\000\002\000\001\000\003\000\
\001\000\003\000\001\000\003\000\001\000\003\000\001\000\002\000\
\000\000\002\000\000\000\001\000\003\000\001\000\002\000\001\000\
\002\000\001\000\002\000\001\000\001\000\000\000\001\000\000\000\
\001\000\000\000\002\000\002\000\002\000\002\000\002\000"

let yydefred = "\000\000\
\002\000\000\000\000\000\000\000\000\000\000\000\235\001\000\000\
\007\000\000\000\228\000\181\001\213\000\220\000\214\000\216\000\
\215\000\221\000\223\000\222\000\212\000\217\000\218\000\219\000\
\054\001\055\001\053\001\000\000\056\001\232\000\233\000\000\000\
\000\000\000\000\000\000\000\000\234\000\000\000\000\000\000\000\
\000\000\000\000\163\001\164\001\165\001\166\001\167\001\168\001\
\169\001\000\000\000\000\141\001\000\000\182\001\236\001\176\001\
\000\000\000\000\174\001\173\001\177\001\179\001\231\000\224\000\
\225\000\000\000\000\000\059\001\060\001\000\000\000\000\107\001\
\000\000\108\001\120\001\000\000\128\001\130\001\178\001\081\000\
\082\000\085\000\000\000\000\000\086\000\000\000\011\000\000\000\
\183\001\000\000\000\000\067\000\068\000\138\000\069\000\063\000\
\065\000\066\000\064\000\000\000\153\000\000\000\000\000\152\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\116\000\000\000\000\000\000\000\
\237\001\000\000\080\000\000\000\000\000\018\000\020\000\000\000\
\000\000\046\000\000\000\000\000\000\000\070\000\000\000\109\000\
\107\000\108\000\110\000\111\000\112\000\000\000\000\000\000\000\
\000\000\009\000\239\001\000\000\000\000\029\001\000\000\000\000\
\001\000\003\000\191\001\000\000\000\000\000\000\000\000\236\000\
\224\001\092\001\000\000\093\001\005\000\006\000\185\001\000\000\
\000\000\000\000\000\000\000\000\052\001\051\001\000\000\000\000\
\136\001\000\000\000\000\000\000\000\000\172\001\049\001\050\001\
\000\000\036\001\247\000\246\000\248\000\000\000\000\000\000\000\
\000\000\000\000\000\000\065\001\000\000\211\001\129\001\048\001\
\237\000\226\001\000\000\189\001\000\000\000\000\125\001\121\001\
\123\001\000\000\000\000\000\000\000\000\094\000\000\000\000\000\
\000\000\000\000\000\000\049\000\000\000\050\000\000\000\000\000\
\104\000\025\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\012\000\151\000\000\000\052\000\000\000\000\000\
\000\000\000\000\000\000\061\000\056\000\000\000\000\000\014\000\
\000\000\000\000\000\000\139\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\076\000\077\000\051\000\157\000\158\000\193\001\000\000\
\113\000\000\000\000\000\000\000\134\000\000\000\133\000\131\000\
\000\000\129\000\000\000\135\000\136\000\137\000\027\001\028\001\
\000\000\000\000\000\000\000\000\034\001\000\000\000\000\033\001\
\000\000\014\001\192\001\213\001\131\001\000\000\000\000\018\001\
\000\000\000\000\000\000\000\000\000\000\225\001\000\000\119\001\
\000\000\209\001\000\000\000\000\002\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\156\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\139\001\000\000\203\001\
\000\000\000\000\000\000\099\000\100\000\201\001\101\000\103\000\
\000\000\000\000\000\000\000\000\000\000\067\001\000\000\254\000\
\000\000\000\000\239\000\238\000\030\001\243\000\000\000\000\000\
\000\000\037\001\064\001\000\000\000\000\227\001\000\000\095\001\
\000\000\097\001\098\001\000\000\000\000\109\001\094\001\205\001\
\000\000\000\000\000\000\127\001\122\001\126\001\124\001\095\000\
\093\000\084\000\092\000\016\000\000\000\087\000\090\000\000\000\
\000\000\209\000\204\000\205\000\202\000\203\000\208\000\185\000\
\186\000\188\000\187\000\206\000\207\000\000\000\196\000\195\000\
\200\000\201\000\199\000\189\000\190\000\194\000\193\000\192\000\
\191\000\198\000\197\000\178\000\179\000\180\000\181\000\182\000\
\184\000\183\000\211\000\210\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\123\000\
\121\000\122\000\000\000\000\000\000\000\000\000\096\000\000\000\
\199\001\097\000\098\000\102\000\000\000\000\000\000\000\158\001\
\159\001\161\001\162\001\160\001\000\000\220\001\000\000\000\000\
\019\000\118\000\021\000\022\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\026\000\027\000\030\000\
\029\000\028\000\106\000\000\000\073\000\000\000\000\000\074\000\
\075\000\194\001\000\000\000\000\000\000\184\001\127\000\132\000\
\008\001\000\000\004\001\000\000\000\000\000\000\000\000\000\000\
\035\001\002\000\132\001\000\000\000\000\000\000\000\000\023\001\
\015\001\016\001\000\000\019\001\000\000\000\000\235\000\000\000\
\000\000\000\000\000\000\227\000\000\000\000\000\000\000\000\000\
\195\001\000\000\230\000\229\000\000\000\000\000\000\000\000\000\
\000\000\187\001\000\000\000\000\000\000\077\001\000\000\000\000\
\075\001\000\000\222\001\150\001\149\001\137\001\143\001\000\000\
\140\001\204\001\218\001\000\000\000\000\000\000\171\001\249\000\
\000\000\000\000\255\000\000\000\250\000\252\000\000\000\031\001\
\245\000\212\001\000\000\072\001\062\001\000\000\000\000\000\000\
\110\001\100\001\000\000\000\000\000\000\207\001\000\000\000\000\
\190\001\088\001\206\001\069\001\068\001\000\000\000\000\000\000\
\000\000\000\000\117\000\170\000\000\000\000\000\119\000\000\000\
\000\000\000\000\000\000\000\000\000\000\058\000\000\000\060\000\
\000\000\216\001\000\000\000\000\000\000\000\000\000\000\015\000\
\000\000\150\000\000\000\000\000\000\000\047\000\072\000\071\000\
\000\000\003\001\005\001\009\001\006\001\000\000\010\001\000\000\
\000\000\013\001\214\001\022\001\021\001\024\001\000\000\000\000\
\000\000\210\001\186\001\114\001\118\001\000\000\175\001\000\000\
\000\000\165\000\000\000\197\001\196\001\180\001\000\000\000\000\
\000\000\000\000\000\000\082\001\000\000\000\000\000\000\188\001\
\000\000\079\001\000\000\223\001\142\001\038\001\000\000\202\001\
\170\001\000\000\000\000\251\000\253\000\063\001\000\000\074\001\
\087\001\000\000\106\001\105\001\000\000\099\001\000\000\111\001\
\102\001\017\000\000\000\169\000\000\000\000\000\000\000\000\000\
\142\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\143\000\057\000\059\000\000\000\200\001\062\000\114\000\000\000\
\221\001\149\000\024\000\078\000\000\000\007\001\011\001\004\000\
\039\001\000\000\000\000\115\001\226\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\083\001\000\000\081\001\076\001\
\000\000\000\000\080\001\000\000\070\001\000\000\000\000\000\000\
\208\001\103\001\176\000\000\000\000\000\000\000\168\000\120\000\
\145\000\000\000\147\000\000\000\000\000\000\000\115\000\000\000\
\000\000\000\000\040\001\000\000\177\000\000\000\000\000\198\001\
\000\000\000\000\138\001\000\000\231\001\152\001\078\001\041\001\
\071\001\073\001\096\001\000\000\172\000\173\000\146\000\148\000\
\144\000\141\000\079\000\042\001\000\000\163\000\000\000\000\000\
\084\001\174\000\043\001\000\000\000\000\164\000"

let yydgoto = "\006\000\
\007\000\055\000\200\001\122\000\147\000\008\000\154\000\053\002\
\129\001\123\000\146\000\125\000\149\001\221\001\126\000\127\000\
\128\000\129\000\230\001\130\000\131\000\252\001\132\000\133\000\
\243\000\208\001\058\000\134\000\055\002\017\003\215\000\135\000\
\078\001\136\000\216\000\145\001\209\001\101\001\211\001\102\001\
\103\001\212\001\104\001\200\002\137\000\138\000\139\000\140\000\
\141\000\142\000\079\001\189\001\201\001\202\001\040\001\143\000\
\041\001\007\002\042\001\043\001\060\000\045\001\046\001\040\002\
\041\002\163\002\164\002\022\003\208\002\105\002\190\001\063\000\
\064\000\065\000\066\000\161\000\202\000\117\001\190\000\191\000\
\192\000\193\000\119\001\113\001\077\002\052\001\061\001\062\001\
\010\002\054\001\063\001\064\001\065\001\025\002\026\002\066\001\
\150\000\151\000\056\001\068\000\195\000\105\001\125\001\085\002\
\069\000\070\000\071\000\203\000\196\000\197\000\198\000\110\001\
\056\002\034\002\178\002\057\002\058\002\059\002\072\000\073\000\
\206\000\133\001\098\002\074\000\134\001\135\001\093\002\094\002\
\095\002\096\002\201\002\136\001\137\001\169\000\073\001\156\002\
\074\001\075\001\075\000\211\000\212\000\076\000\077\000\199\000\
\078\000\093\001\097\001\098\001\030\003\222\001\079\000\163\000"

let yysindex = "\041\003\
\000\000\172\009\021\017\124\020\130\020\000\000\000\000\245\009\
\000\000\017\255\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\068\000\000\000\000\000\000\000\235\254\
\235\254\251\000\066\255\082\255\000\000\092\255\224\005\112\255\
\027\255\053\255\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\040\255\127\255\000\000\165\255\000\000\000\000\000\000\
\146\255\224\005\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\224\005\047\004\000\000\000\000\224\005\147\255\000\000\
\041\001\000\000\000\000\022\025\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\041\000\000\000\156\255\000\000\188\018\
\000\000\124\020\124\020\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\025\000\000\000\054\000\124\020\000\000\
\059\000\021\017\110\000\129\000\124\020\022\255\104\000\124\020\
\084\010\124\020\013\255\149\000\000\000\153\000\000\000\161\000\
\000\000\230\255\000\000\000\000\172\000\000\000\000\000\186\000\
\139\004\000\000\130\020\034\002\124\020\000\000\011\255\000\000\
\000\000\000\000\000\000\000\000\000\000\181\000\045\016\156\255\
\221\000\000\000\000\000\130\020\130\020\000\000\239\255\220\000\
\000\000\000\000\000\000\236\025\225\000\124\000\232\000\000\000\
\000\000\000\000\235\254\000\000\000\000\000\000\000\000\246\000\
\015\255\124\020\255\000\011\255\000\000\000\000\201\017\178\013\
\000\000\179\000\006\255\223\012\223\012\000\000\000\000\000\000\
\079\000\000\000\000\000\000\000\000\000\198\255\043\000\091\255\
\217\001\079\000\013\000\000\000\253\254\000\000\000\000\000\000\
\000\000\000\000\147\255\000\000\046\001\168\025\000\000\000\000\
\000\000\047\004\095\025\231\000\035\001\000\000\045\001\041\000\
\054\001\027\000\066\001\000\000\130\020\000\000\085\028\124\020\
\000\000\000\000\244\000\118\017\004\001\124\020\124\020\221\000\
\156\255\124\020\000\000\000\000\172\016\000\000\130\020\077\001\
\092\001\072\013\097\001\000\000\000\000\011\255\096\001\000\000\
\144\000\210\010\124\020\000\000\172\016\124\020\124\020\124\020\
\124\020\124\020\124\020\124\020\124\020\124\020\124\020\124\020\
\124\020\124\020\124\020\124\020\124\020\124\020\124\020\124\020\
\124\020\124\020\124\020\124\020\112\001\059\011\124\020\015\255\
\015\255\000\000\000\000\000\000\000\000\000\000\000\000\011\255\
\000\000\000\000\124\020\080\001\000\000\109\001\000\000\000\000\
\134\001\000\000\045\016\000\000\000\000\000\000\000\000\000\000\
\132\001\239\018\142\000\119\026\000\000\158\000\031\001\000\000\
\137\001\000\000\000\000\000\000\000\000\149\001\153\001\000\000\
\052\005\079\027\223\012\164\001\172\001\000\000\015\255\000\000\
\170\001\000\000\189\001\118\000\000\000\020\255\204\001\222\001\
\232\001\021\017\036\255\144\000\148\018\000\000\000\000\230\255\
\000\000\045\016\000\000\238\001\143\001\000\000\164\011\000\000\
\151\001\154\001\130\001\000\000\000\000\000\000\000\000\000\000\
\177\000\023\255\003\002\044\255\000\000\000\000\091\255\000\000\
\023\019\236\025\000\000\000\000\000\000\000\000\217\001\000\000\
\243\001\000\000\000\000\223\012\074\019\000\000\168\025\000\000\
\011\002\000\000\000\000\046\004\009\002\000\000\000\000\000\000\
\168\025\198\255\079\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\186\001\000\000\000\000\112\001\
\016\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\008\255\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\014\002\085\028\219\000\124\020\
\172\016\147\019\147\019\031\002\022\001\026\001\221\000\000\000\
\000\000\000\000\112\001\013\012\118\012\171\001\000\000\048\001\
\000\000\000\000\000\000\000\000\124\020\036\002\011\255\000\000\
\000\000\000\000\000\000\000\000\057\001\000\000\021\017\062\001\
\000\000\000\000\000\000\000\000\221\000\018\002\091\007\081\008\
\227\008\229\007\120\005\111\004\111\004\144\003\144\003\144\003\
\144\003\045\002\045\002\066\002\066\002\000\000\000\000\000\000\
\000\000\000\000\000\000\198\019\000\000\075\001\031\000\000\000\
\000\000\000\000\030\001\172\016\172\016\000\000\000\000\000\000\
\000\000\038\002\000\000\040\002\158\000\149\001\238\019\236\025\
\000\000\000\000\000\000\050\026\018\001\235\254\218\000\000\000\
\000\000\000\000\034\001\000\000\083\001\223\012\000\000\170\001\
\015\255\043\002\124\020\000\000\124\020\164\023\233\000\030\002\
\000\000\032\002\000\000\000\000\233\001\011\255\051\002\123\001\
\156\255\000\000\124\020\145\255\035\002\000\000\046\002\057\018\
\000\000\005\001\000\000\000\000\000\000\000\000\000\000\128\001\
\000\000\000\000\000\000\122\001\223\012\037\002\000\000\000\000\
\011\255\057\002\000\000\054\002\000\000\000\000\149\001\000\000\
\000\000\000\000\140\001\000\000\000\000\057\018\009\002\223\012\
\000\000\000\000\235\254\079\000\060\000\000\000\044\002\124\020\
\000\000\000\000\000\000\000\000\000\000\064\002\061\002\069\002\
\085\028\209\000\000\000\000\000\021\017\049\002\000\000\033\020\
\073\020\124\020\021\017\021\017\061\002\000\000\145\001\000\000\
\150\001\000\000\019\017\223\012\098\000\052\002\071\002\000\000\
\144\000\000\000\021\017\124\020\097\018\000\000\000\000\000\000\
\172\016\000\000\000\000\000\000\000\000\062\002\000\000\149\001\
\237\023\000\000\000\000\000\000\000\000\000\000\176\001\161\001\
\043\002\000\000\000\000\000\000\000\000\073\002\000\000\075\002\
\025\000\000\000\077\002\000\000\000\000\000\000\086\002\087\002\
\011\255\049\014\081\000\000\000\148\018\148\018\084\002\000\000\
\046\002\000\000\148\018\000\000\000\000\000\000\074\019\000\000\
\000\000\089\002\011\255\000\000\000\000\000\000\046\002\000\000\
\000\000\201\001\000\000\000\000\203\001\000\000\124\020\000\000\
\000\000\000\000\016\002\000\000\124\020\096\002\102\002\085\028\
\000\000\172\016\021\017\205\001\021\017\209\001\252\001\042\002\
\000\000\000\000\000\000\097\001\000\000\000\000\000\000\099\002\
\000\000\000\000\000\000\000\000\100\002\000\000\000\000\000\000\
\000\000\074\019\206\001\000\000\000\000\124\020\129\002\233\000\
\124\020\052\002\181\002\090\002\000\000\124\020\000\000\000\000\
\179\002\184\002\000\000\170\002\000\000\188\002\184\002\173\002\
\000\000\000\000\000\000\121\000\209\000\209\000\000\000\000\000\
\000\000\021\017\000\000\021\017\174\002\021\017\000\000\148\018\
\190\002\176\002\000\000\074\019\000\000\194\002\206\002\000\000\
\000\002\099\002\000\000\192\002\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\209\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\185\002\000\000\199\002\174\002\
\000\000\000\000\000\000\124\020\207\002\000\000"

let yyrindex = "\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\016\023\000\000\000\000\000\000\060\001\
\110\001\000\000\000\000\000\000\000\000\000\000\115\021\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\202\021\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\234\021\000\000\000\000\000\000\249\021\043\021\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\089\004\219\002\000\000\023\027\000\000\142\027\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\193\002\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\204\004\000\000\
\000\000\000\000\000\000\062\027\000\000\000\000\000\000\234\006\
\169\001\000\000\000\000\208\005\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\209\002\120\002\
\232\003\000\000\000\000\059\010\085\010\000\000\017\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\207\020\000\000\000\000\000\000\000\000\103\003\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\123\002\
\000\000\000\000\000\000\001\002\033\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\055\024\000\000\089\022\
\118\001\000\000\000\000\000\000\077\000\000\000\000\000\000\000\
\000\000\000\000\130\021\000\000\225\003\214\002\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\219\002\
\000\000\000\000\000\000\000\000\000\000\000\000\200\002\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\201\002\
\245\004\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\169\005\000\000\054\006\000\000\000\000\000\000\000\000\000\000\
\008\002\000\000\000\000\000\000\000\000\000\000\000\000\203\002\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\091\005\
\000\000\093\023\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\035\255\000\000\000\000\000\000\000\000\000\000\
\188\026\000\000\018\000\000\000\000\000\046\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\220\002\000\000\
\034\255\000\000\001\002\000\000\000\000\000\000\000\000\000\000\
\225\002\000\000\168\000\000\000\000\000\221\002\000\000\000\000\
\000\000\000\000\000\000\008\002\000\000\000\000\176\014\130\002\
\047\015\000\000\174\015\136\002\000\000\000\000\000\000\000\000\
\000\000\137\002\033\255\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\130\024\000\000\180\022\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\080\003\205\024\
\000\000\000\000\000\000\001\002\000\000\000\000\214\002\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\229\002\045\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\240\002\000\000\000\000\000\000\
\229\027\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\200\002\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\215\002\000\000\
\000\000\000\000\000\000\000\000\000\000\013\002\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\217\002\000\000\212\001\117\000\
\162\001\050\005\092\002\150\008\175\008\221\007\043\008\072\008\
\121\008\158\007\190\007\017\007\056\007\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\064\255\073\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\057\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\188\026\046\255\195\255\000\000\
\000\000\000\000\000\000\000\000\000\000\001\002\000\000\225\002\
\232\002\000\000\000\000\000\000\000\000\000\000\184\000\237\002\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\137\028\000\000\000\000\000\000\000\000\000\000\225\002\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\033\255\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\002\
\000\000\000\000\063\000\000\000\000\000\000\000\078\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\200\002\029\028\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\092\006\000\000\000\000\000\000\
\000\000\000\000\000\000\001\002\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\102\255\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\245\000\
\000\000\000\000\135\255\000\000\000\000\000\000\000\000\000\000\
\000\000\123\002\000\000\000\000\000\000\232\002\000\000\000\000\
\225\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\225\002\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\229\027\000\000\000\000\000\000\000\000\200\002\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\030\009\
\000\000\000\000\000\000\195\006\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\251\002\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\184\000\
\000\000\210\002\000\000\000\000\000\000\000\000\000\000\000\000\
\212\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\029\028\029\028\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\043\003\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\213\002\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\029\028\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\216\002\
\000\000\000\000\000\000\000\000\000\000\000\000"

let yygindex = "\000\000\
\000\000\000\000\002\000\009\000\097\000\209\254\067\004\224\255\
\255\255\195\000\253\255\244\255\000\000\242\002\157\255\173\255\
\186\255\165\006\000\000\020\001\093\001\179\254\000\000\000\000\
\207\001\070\255\136\000\000\000\005\254\000\000\113\003\131\255\
\196\003\036\000\000\000\000\000\000\000\230\009\000\000\221\253\
\000\000\126\002\234\002\176\255\000\000\000\000\065\255\000\000\
\000\000\000\000\061\255\111\254\029\255\004\000\000\000\000\000\
\000\000\000\000\071\255\084\255\129\255\058\000\038\000\000\000\
\039\002\000\000\094\001\029\001\100\253\138\001\000\000\000\000\
\000\000\000\000\091\009\183\003\145\003\228\002\135\000\080\000\
\072\255\000\000\000\000\000\000\017\002\015\000\237\254\225\254\
\191\255\219\254\000\000\030\003\001\000\000\000\000\000\035\000\
\000\000\177\255\000\000\000\000\000\000\086\255\238\253\198\253\
\062\000\000\000\000\000\000\000\000\000\000\000\235\002\000\000\
\139\254\239\253\236\253\155\253\000\000\053\002\000\000\000\000\
\152\003\233\002\023\002\000\000\000\000\000\000\000\000\173\001\
\000\000\020\002\160\001\231\002\000\000\204\003\047\003\226\001\
\094\002\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\215\001\000\000\000\000\000\000\002\002\000\000\000\000"

let yytablesize = 7617
let yytable = "\124\000\
\057\000\168\000\067\000\090\001\121\000\059\000\111\001\086\002\
\067\000\031\001\106\001\059\000\145\000\013\002\153\002\044\001\
\032\001\000\001\029\001\225\000\014\002\144\000\227\000\095\001\
\156\000\226\001\123\001\029\001\233\000\038\002\246\000\087\000\
\226\000\184\002\155\000\233\000\194\001\175\002\087\000\062\000\
\205\000\070\002\019\002\245\000\108\002\001\001\031\001\069\002\
\091\001\183\002\214\001\217\001\017\001\046\002\039\002\130\000\
\002\001\217\001\017\001\061\000\177\002\073\002\028\001\224\001\
\020\001\192\002\162\000\164\000\047\001\048\001\020\001\247\002\
\248\002\234\000\103\002\081\001\210\000\251\002\159\000\208\000\
\100\001\100\001\079\002\170\000\126\000\053\001\225\000\247\000\
\221\002\076\001\191\002\254\001\124\001\124\000\078\002\171\000\
\218\000\236\000\223\000\226\000\174\000\194\000\124\000\160\000\
\037\003\038\003\235\000\229\000\155\000\172\000\047\002\207\000\
\112\001\008\002\116\000\096\001\044\000\232\000\074\002\183\000\
\031\001\116\000\125\000\219\000\252\002\117\002\132\001\184\000\
\116\000\175\000\038\001\200\000\234\002\209\000\118\000\050\003\
\176\000\229\002\030\001\124\000\148\000\118\000\207\001\067\000\
\037\001\130\000\039\001\030\001\118\000\178\000\207\001\225\001\
\029\002\161\000\227\001\228\001\072\001\071\002\165\000\250\002\
\060\002\166\000\002\002\181\000\064\002\235\000\177\000\217\001\
\017\001\161\000\248\002\044\001\124\000\255\002\126\000\018\003\
\092\001\087\001\207\001\089\001\020\001\182\000\180\000\124\000\
\088\001\055\001\226\000\226\000\226\000\226\000\226\000\226\000\
\226\000\226\000\226\000\226\000\226\000\226\000\226\000\226\000\
\226\000\226\000\226\000\226\000\226\000\226\000\114\001\225\000\
\002\002\083\002\003\002\210\000\125\000\000\001\141\001\204\002\
\020\003\045\003\044\001\000\001\226\000\111\002\225\000\100\001\
\109\001\012\002\145\002\021\001\210\000\031\003\051\001\195\001\
\191\001\124\000\034\003\226\000\179\000\210\000\197\001\198\001\
\144\002\013\002\199\001\131\001\139\001\017\002\140\001\142\001\
\244\000\124\000\140\002\207\001\143\002\210\000\251\000\024\002\
\049\001\054\002\112\002\113\002\050\001\189\000\217\000\130\001\
\229\001\252\000\148\000\000\002\001\002\143\001\226\000\080\001\
\118\001\119\002\121\002\127\002\235\000\235\000\201\000\187\000\
\100\001\084\002\061\002\148\000\148\000\225\000\038\001\255\001\
\076\002\226\001\188\000\032\001\000\001\121\001\009\000\124\000\
\108\001\159\000\226\000\067\000\037\001\150\001\039\001\132\001\
\122\001\000\001\213\000\251\000\214\000\136\002\148\000\251\000\
\144\000\132\001\072\001\189\002\185\000\152\001\007\003\107\001\
\001\001\086\002\160\000\235\000\016\002\066\001\001\001\224\000\
\120\001\000\001\066\001\002\001\228\000\038\001\124\000\203\001\
\066\001\002\001\159\000\045\002\197\002\148\000\124\000\104\001\
\138\001\031\001\067\000\037\001\144\000\039\001\111\001\198\002\
\185\000\104\001\104\001\027\002\148\000\061\001\101\001\245\002\
\207\001\207\001\168\002\160\000\225\000\220\000\222\000\110\002\
\061\001\101\001\246\002\152\002\086\002\242\000\148\000\187\000\
\222\002\226\000\251\000\189\000\231\002\114\001\194\000\230\000\
\051\001\189\000\188\000\238\000\189\000\186\002\051\001\044\000\
\036\002\044\000\237\000\044\000\066\001\044\000\037\002\036\003\
\023\002\251\000\231\000\044\000\189\000\116\000\044\000\044\000\
\044\000\044\000\044\000\139\001\001\001\216\001\086\002\049\001\
\217\001\042\000\248\000\050\001\131\001\111\002\092\002\002\001\
\023\000\118\000\249\000\023\002\100\002\194\002\131\001\155\000\
\031\001\218\001\250\000\015\002\001\001\134\002\221\000\221\000\
\130\001\116\000\100\001\225\000\117\001\124\000\142\002\002\001\
\117\001\210\000\130\001\068\002\157\000\158\000\081\002\022\002\
\226\000\069\002\166\000\031\001\239\000\118\000\253\000\225\000\
\166\000\225\000\157\002\045\000\158\002\219\001\254\000\255\000\
\033\001\150\002\166\000\124\000\226\000\125\002\226\000\225\000\
\130\002\100\001\171\002\044\000\054\002\243\002\205\002\144\000\
\206\002\057\001\207\002\021\002\226\000\109\002\008\003\050\001\
\160\002\226\000\067\001\251\000\100\001\251\000\009\000\254\002\
\220\001\069\001\089\000\044\000\068\001\090\001\161\002\138\001\
\124\000\124\000\054\002\189\000\210\000\210\000\148\000\162\000\
\165\000\167\000\091\002\166\000\225\000\162\000\167\000\226\000\
\148\000\101\002\077\001\172\002\072\001\192\001\193\001\162\000\
\100\001\226\000\051\002\016\002\052\002\235\000\189\000\144\000\
\227\002\094\001\179\002\021\002\009\002\162\002\067\000\050\001\
\115\002\059\000\091\001\031\001\116\002\144\001\251\000\144\000\
\049\001\054\002\251\000\021\002\050\001\146\001\165\000\050\001\
\148\002\166\000\187\000\189\000\204\000\031\001\226\000\192\001\
\137\002\204\000\123\002\148\001\116\000\188\000\189\000\187\000\
\124\002\090\001\187\000\128\002\090\001\189\000\041\000\090\001\
\131\002\129\002\188\000\084\002\151\001\188\000\124\002\042\000\
\118\000\054\002\054\002\041\000\196\001\135\002\204\001\054\002\
\050\000\051\000\052\000\124\002\023\002\151\002\226\000\226\000\
\106\002\124\000\023\002\069\002\226\000\205\001\209\002\124\000\
\124\000\215\001\004\002\225\000\216\002\217\002\213\001\008\000\
\212\002\214\002\215\002\091\001\116\000\195\002\091\001\124\000\
\226\000\091\001\251\001\242\000\226\002\124\000\084\002\242\000\
\242\000\210\000\021\003\242\000\116\000\170\002\242\000\005\002\
\118\000\067\000\181\002\129\002\059\000\049\001\009\002\123\001\
\124\002\050\001\006\002\107\001\018\002\182\002\190\002\239\002\
\118\000\149\002\225\000\218\002\069\002\028\003\124\000\059\001\
\219\002\124\002\092\001\087\001\187\000\089\001\124\002\226\000\
\084\002\020\002\088\001\235\002\042\000\030\002\042\000\188\000\
\042\000\069\002\042\000\023\000\054\002\023\000\031\002\023\000\
\042\000\023\000\033\002\042\000\042\000\042\000\042\000\042\000\
\042\000\226\000\023\000\023\000\023\000\123\001\124\000\124\000\
\021\003\124\000\210\000\233\002\009\003\004\003\011\003\189\000\
\144\000\189\000\035\002\000\003\185\000\189\000\042\002\010\003\
\242\000\069\002\196\002\012\003\242\000\251\000\045\000\092\002\
\045\000\251\000\045\000\123\001\045\000\089\002\162\002\013\000\
\043\002\019\003\045\000\187\000\242\000\045\000\045\000\045\000\
\045\000\025\003\044\002\144\000\242\000\062\002\188\000\021\002\
\144\000\187\000\244\000\050\001\185\000\065\002\124\000\066\002\
\124\000\099\001\124\000\039\003\188\000\040\003\013\003\042\003\
\042\000\186\000\048\003\217\001\251\000\072\002\187\000\023\000\
\251\000\217\001\219\001\187\000\088\002\097\002\189\000\215\001\
\219\001\188\000\030\000\031\000\102\002\215\001\188\000\104\002\
\042\000\001\000\002\000\003\000\004\000\005\000\159\000\023\000\
\114\002\107\002\206\001\022\001\132\002\116\000\126\002\023\001\
\138\002\024\001\037\000\025\001\026\001\027\001\139\002\155\002\
\039\002\167\002\045\000\166\002\169\002\173\002\174\002\160\000\
\185\002\118\000\187\002\091\002\075\002\202\002\089\002\244\000\
\133\002\159\000\203\002\210\002\230\002\115\001\159\000\223\002\
\116\000\224\002\045\000\237\002\238\002\116\000\014\001\015\001\
\016\001\017\001\018\001\019\001\020\001\240\002\116\001\241\002\
\249\002\242\002\160\000\253\002\118\000\005\003\041\000\160\000\
\041\000\118\000\041\000\006\003\041\000\016\001\017\001\018\001\
\019\001\020\001\041\000\014\003\016\003\041\000\041\000\041\000\
\041\000\041\000\041\000\041\000\041\000\008\000\015\003\189\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\023\003\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\026\003\
\027\003\008\000\041\000\029\003\176\002\032\003\033\003\008\000\
\035\003\041\003\043\003\044\003\046\003\047\003\049\003\008\000\
\052\003\008\000\008\000\008\000\051\003\008\000\008\000\008\000\
\089\001\054\003\041\000\091\000\154\000\128\000\008\000\238\001\
\008\000\157\001\113\001\167\000\155\000\234\001\012\001\160\000\
\145\001\008\000\008\000\008\000\008\000\086\001\148\001\144\001\
\008\000\112\001\156\000\233\001\085\001\013\000\008\000\159\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\230\001\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\013\000\
\013\000\013\000\013\000\013\000\013\000\013\000\013\000\229\001\
\154\001\013\000\232\001\155\001\056\000\048\002\153\001\013\000\
\147\001\220\002\032\001\122\002\067\002\024\003\165\002\013\000\
\053\003\013\000\013\000\013\000\003\003\013\000\013\000\013\000\
\083\000\070\001\080\002\126\001\188\002\244\000\013\000\028\002\
\013\000\244\000\244\000\082\002\127\001\244\000\002\003\087\002\
\244\000\013\000\013\000\013\000\013\000\193\002\180\002\099\002\
\013\000\001\003\199\002\071\001\116\001\032\002\013\000\116\001\
\116\001\116\001\236\002\116\001\116\001\116\001\154\002\116\001\
\244\002\000\000\225\002\116\001\116\001\116\001\000\000\000\000\
\116\001\116\001\116\001\116\001\116\001\116\001\116\001\116\001\
\116\001\116\001\116\001\116\001\116\001\116\001\116\001\116\001\
\116\001\116\001\116\001\116\001\116\001\116\001\116\001\116\001\
\116\001\116\001\116\001\116\001\116\001\116\001\116\001\116\001\
\116\001\116\001\116\001\116\001\116\001\116\001\116\001\116\001\
\116\001\116\001\116\001\116\001\116\001\116\001\000\000\000\000\
\000\000\000\000\244\000\000\000\000\000\000\000\244\000\012\001\
\013\001\014\001\015\001\016\001\017\001\018\001\019\001\020\001\
\116\001\000\000\116\001\088\000\116\001\116\001\244\000\000\000\
\000\000\116\001\000\000\000\000\000\000\116\001\244\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\116\001\000\000\116\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\116\001\089\001\000\000\
\000\000\089\001\089\001\089\001\010\000\089\001\089\001\089\001\
\000\000\089\001\000\000\000\000\000\000\089\001\089\001\089\001\
\000\000\000\000\089\001\089\001\089\001\089\001\089\001\089\001\
\089\001\089\001\089\001\089\001\089\001\089\001\089\001\089\001\
\089\001\089\001\089\001\089\001\089\001\089\001\089\001\089\001\
\089\001\089\001\089\001\089\001\089\001\089\001\089\001\089\001\
\089\001\089\001\089\001\089\001\089\001\089\001\089\001\089\001\
\089\001\089\001\089\001\089\001\089\001\089\001\089\001\089\001\
\000\000\043\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\144\000\144\000\000\000\000\000\185\000\
\185\000\000\000\089\001\000\000\089\001\000\000\089\001\089\001\
\000\000\000\000\000\000\089\001\000\000\000\000\000\000\089\001\
\089\002\090\002\186\000\000\000\000\000\000\000\187\000\187\000\
\000\000\000\000\089\000\000\000\000\000\089\001\000\000\089\001\
\157\000\188\000\188\000\000\000\000\000\000\000\000\000\089\001\
\000\000\000\000\083\000\083\000\000\000\083\000\083\000\083\000\
\083\000\083\000\083\000\083\000\083\000\083\000\083\000\083\000\
\000\000\000\000\083\000\083\000\083\000\083\000\083\000\083\000\
\083\000\083\000\083\000\083\000\083\000\083\000\083\000\083\000\
\083\000\083\000\083\000\083\000\083\000\083\000\083\000\083\000\
\083\000\159\000\159\000\000\000\000\000\000\000\000\000\000\000\
\116\000\116\000\008\001\009\001\010\001\011\001\012\001\013\001\
\014\001\015\001\016\001\017\001\018\001\019\001\020\001\000\000\
\228\000\000\001\160\000\160\000\118\000\118\000\000\000\001\001\
\002\001\003\001\004\001\005\001\006\001\007\001\008\001\009\001\
\010\001\011\001\012\001\013\001\014\001\015\001\016\001\017\001\
\018\001\019\001\020\001\000\000\000\000\000\000\000\000\083\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\048\000\
\000\000\000\000\000\000\158\000\000\000\000\000\000\000\000\000\
\157\000\000\000\000\000\000\000\000\000\088\000\088\000\083\000\
\088\000\088\000\088\000\088\000\088\000\088\000\088\000\088\000\
\088\000\088\000\088\000\000\000\000\000\088\000\088\000\088\000\
\088\000\088\000\088\000\088\000\088\000\088\000\088\000\088\000\
\088\000\088\000\088\000\088\000\088\000\088\000\088\000\088\000\
\088\000\088\000\088\000\088\000\000\000\000\000\010\000\010\000\
\000\000\010\000\010\000\010\000\010\000\010\000\010\000\010\000\
\010\000\010\000\010\000\010\000\000\000\000\000\010\000\010\000\
\010\000\010\000\010\000\010\000\010\000\010\000\010\000\010\000\
\010\000\010\000\010\000\010\000\010\000\010\000\010\000\010\000\
\010\000\010\000\010\000\010\000\010\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\054\000\000\000\000\000\
\000\000\000\000\088\000\000\000\000\000\000\000\000\000\000\000\
\000\000\144\000\000\000\000\000\043\000\021\002\043\000\000\000\
\043\000\050\001\043\000\158\000\000\000\000\000\000\000\000\000\
\043\000\000\000\088\000\043\000\043\000\043\000\043\000\043\000\
\043\000\043\000\000\000\053\000\187\000\000\000\000\000\000\000\
\000\000\000\000\000\000\010\000\000\000\000\000\000\000\188\000\
\000\000\000\000\000\000\000\000\089\000\089\000\000\000\089\000\
\089\000\089\000\089\000\089\000\089\000\089\000\089\000\089\000\
\089\000\089\000\000\000\010\000\089\000\089\000\089\000\089\000\
\089\000\089\000\089\000\089\000\089\000\089\000\089\000\089\000\
\089\000\089\000\089\000\089\000\089\000\089\000\089\000\089\000\
\089\000\089\000\089\000\000\000\000\000\000\000\000\000\159\000\
\000\000\000\000\000\000\000\000\000\000\000\000\116\000\000\000\
\043\000\006\001\007\001\008\001\009\001\010\001\011\001\012\001\
\013\001\014\001\015\001\016\001\017\001\018\001\019\001\020\001\
\160\000\000\000\118\000\000\000\000\000\000\000\000\000\000\000\
\043\000\000\000\000\000\228\000\000\000\228\000\228\000\228\000\
\000\000\228\000\055\000\000\000\000\000\228\000\228\000\228\000\
\000\000\089\000\228\000\228\000\228\000\228\000\228\000\228\000\
\228\000\228\000\228\000\228\000\228\000\228\000\228\000\228\000\
\228\000\228\000\228\000\228\000\228\000\228\000\228\000\228\000\
\228\000\089\000\048\000\000\000\048\000\000\000\048\000\000\000\
\048\000\025\000\000\000\000\000\048\000\048\000\048\000\000\000\
\011\000\048\000\048\000\048\000\048\000\048\000\048\000\048\000\
\048\000\048\000\048\000\048\000\048\000\048\000\048\000\048\000\
\048\000\048\000\048\000\048\000\048\000\048\000\048\000\048\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\031\000\000\000\000\000\000\000\000\000\000\000\000\000\228\000\
\013\000\014\000\015\000\016\000\017\000\018\000\019\000\020\000\
\021\000\022\000\023\000\024\000\025\000\026\000\027\000\173\000\
\029\000\030\000\031\000\032\000\033\000\034\000\035\000\228\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\032\000\
\000\000\000\000\000\000\000\000\000\000\000\000\048\000\000\000\
\000\000\037\000\000\000\000\000\000\000\039\000\040\000\000\000\
\054\000\000\000\054\000\000\000\054\000\000\000\054\000\000\000\
\000\000\000\000\054\000\054\000\054\000\000\000\048\000\054\000\
\054\000\054\000\054\000\054\000\054\000\054\000\054\000\054\000\
\054\000\054\000\054\000\054\000\054\000\054\000\054\000\054\000\
\054\000\054\000\054\000\054\000\054\000\054\000\053\000\000\000\
\053\000\000\000\053\000\000\000\053\000\000\000\000\000\000\000\
\053\000\053\000\053\000\000\000\000\000\053\000\053\000\053\000\
\053\000\053\000\053\000\053\000\053\000\053\000\053\000\053\000\
\053\000\053\000\053\000\053\000\053\000\053\000\053\000\053\000\
\053\000\053\000\053\000\053\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\033\000\000\000\000\000\
\000\000\000\000\000\000\000\000\054\000\231\001\232\001\233\001\
\234\001\235\001\236\001\237\001\238\001\239\001\240\001\241\001\
\242\001\243\001\244\001\245\001\246\001\247\001\248\001\249\001\
\250\001\000\000\000\000\000\000\054\000\034\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\053\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\055\000\000\000\055\000\
\000\000\055\000\000\000\055\000\035\000\000\000\000\000\055\000\
\055\000\055\000\053\000\000\000\055\000\055\000\055\000\055\000\
\055\000\055\000\055\000\055\000\055\000\055\000\055\000\055\000\
\055\000\055\000\055\000\055\000\055\000\055\000\055\000\055\000\
\055\000\055\000\055\000\000\000\025\000\000\000\025\000\000\000\
\025\000\000\000\025\000\000\000\000\000\000\000\000\000\000\000\
\025\000\000\000\000\000\025\000\025\000\025\000\025\000\025\000\
\025\000\025\000\025\000\025\000\025\000\025\000\025\000\025\000\
\025\000\025\000\025\000\025\000\025\000\025\000\025\000\025\000\
\025\000\025\000\000\000\031\000\000\000\031\000\000\000\031\000\
\000\000\031\000\036\000\000\000\000\000\000\000\000\000\031\000\
\000\000\055\000\031\000\031\000\031\000\031\000\031\000\031\000\
\031\000\031\000\031\000\031\000\031\000\031\000\031\000\031\000\
\031\000\031\000\031\000\031\000\000\000\000\000\000\000\037\000\
\000\000\055\000\032\000\000\000\032\000\000\000\032\000\000\000\
\032\000\000\000\000\000\000\000\000\000\000\000\032\000\000\000\
\025\000\032\000\032\000\032\000\032\000\032\000\032\000\032\000\
\032\000\032\000\032\000\032\000\032\000\032\000\032\000\032\000\
\032\000\032\000\032\000\000\000\000\000\000\000\000\000\000\000\
\025\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\038\000\000\000\000\000\000\000\000\000\000\000\000\000\031\000\
\002\001\003\001\004\001\005\001\006\001\007\001\008\001\009\001\
\010\001\011\001\012\001\013\001\014\001\015\001\016\001\017\001\
\018\001\019\001\020\001\000\000\000\000\039\000\000\000\031\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\032\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\040\000\000\000\
\033\000\000\000\033\000\000\000\033\000\000\000\033\000\000\000\
\000\000\000\000\000\000\000\000\033\000\000\000\032\000\033\000\
\033\000\033\000\033\000\033\000\033\000\033\000\033\000\033\000\
\033\000\033\000\033\000\033\000\033\000\033\000\033\000\000\000\
\034\000\000\000\034\000\000\000\034\000\000\000\034\000\000\000\
\000\000\000\000\000\000\000\000\034\000\000\000\000\000\034\000\
\034\000\034\000\034\000\034\000\034\000\034\000\034\000\034\000\
\034\000\034\000\034\000\034\000\034\000\034\000\034\000\035\000\
\000\000\035\000\000\000\035\000\000\000\035\000\000\000\000\000\
\000\000\000\000\000\000\035\000\000\000\000\000\035\000\035\000\
\035\000\035\000\035\000\035\000\035\000\035\000\035\000\035\000\
\035\000\035\000\035\000\035\000\033\000\005\001\006\001\007\001\
\008\001\009\001\010\001\011\001\012\001\013\001\014\001\015\001\
\016\001\017\001\018\001\019\001\020\001\140\000\000\000\000\000\
\000\000\000\000\000\000\000\000\033\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\034\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\036\000\000\000\036\000\
\000\000\036\000\000\000\036\000\034\000\000\000\000\000\000\000\
\000\000\036\000\000\000\035\000\036\000\036\000\036\000\036\000\
\036\000\036\000\036\000\036\000\036\000\036\000\036\000\036\000\
\036\000\036\000\037\000\000\000\037\000\000\000\037\000\149\000\
\037\000\000\000\000\000\035\000\000\000\000\000\037\000\000\000\
\000\000\037\000\037\000\037\000\037\000\037\000\037\000\037\000\
\037\000\037\000\037\000\037\000\037\000\037\000\037\000\003\001\
\004\001\005\001\006\001\007\001\008\001\009\001\010\001\011\001\
\012\001\013\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\000\000\000\000\038\000\000\000\038\000\000\000\038\000\
\000\000\038\000\000\000\000\000\000\000\000\000\000\000\038\000\
\000\000\036\000\038\000\038\000\038\000\038\000\038\000\038\000\
\038\000\038\000\038\000\038\000\038\000\038\000\038\000\038\000\
\039\000\000\000\039\000\054\000\039\000\000\000\039\000\000\000\
\000\000\036\000\000\000\000\000\039\000\000\000\037\000\039\000\
\039\000\039\000\039\000\039\000\039\000\039\000\039\000\039\000\
\039\000\040\000\000\000\040\000\000\000\040\000\000\000\040\000\
\000\000\000\000\000\000\000\000\000\000\040\000\037\000\000\000\
\040\000\040\000\040\000\040\000\040\000\040\000\040\000\040\000\
\040\000\040\000\000\000\000\000\000\000\149\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\038\000\
\000\000\000\000\000\000\000\000\000\000\000\000\149\000\149\000\
\000\000\000\000\000\000\000\000\153\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\038\000\
\000\000\000\000\000\000\000\000\039\000\000\000\000\000\000\000\
\000\000\149\000\004\001\005\001\006\001\007\001\008\001\009\001\
\010\001\011\001\012\001\013\001\014\001\015\001\016\001\017\001\
\018\001\019\001\020\001\116\001\039\000\040\000\000\000\000\000\
\000\000\000\000\140\000\140\000\140\000\140\000\140\000\000\000\
\149\000\000\000\140\000\140\000\000\000\140\000\140\000\140\000\
\000\000\140\000\140\000\000\000\000\000\040\000\000\000\149\000\
\140\000\140\000\025\001\000\000\000\000\140\000\140\000\000\000\
\000\000\140\000\000\000\140\000\000\000\000\000\140\000\000\000\
\000\000\149\000\000\000\000\000\000\000\000\000\000\000\140\000\
\140\000\140\000\000\000\000\000\026\001\000\000\140\000\140\000\
\140\000\140\000\140\000\140\000\140\000\140\000\140\000\140\000\
\140\000\140\000\140\000\140\000\140\000\140\000\140\000\140\000\
\140\000\140\000\140\000\140\000\140\000\140\000\140\000\000\000\
\140\000\140\000\140\000\140\000\140\000\140\000\140\000\140\000\
\140\000\140\000\140\000\140\000\140\000\000\000\000\000\140\000\
\140\000\060\001\000\000\140\000\140\000\140\000\000\000\000\000\
\140\000\000\000\000\000\000\000\140\000\000\000\140\000\000\000\
\140\000\140\000\140\000\140\000\140\000\140\000\140\000\140\000\
\140\000\140\000\000\000\140\000\140\000\140\000\140\000\000\000\
\140\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\009\000\000\000\010\000\011\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\012\000\
\000\000\116\001\000\000\000\000\000\000\000\000\000\000\210\001\
\000\000\149\000\000\000\000\000\000\000\000\000\000\000\210\001\
\000\000\000\000\000\000\149\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\025\000\026\000\027\000\028\000\029\000\030\000\031\000\032\000\
\033\000\034\000\035\000\210\001\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\010\000\011\000\000\000\000\000\
\000\000\000\000\000\000\000\000\036\000\037\000\038\000\000\000\
\000\000\039\000\040\000\041\000\000\000\000\000\000\000\000\000\
\000\000\060\001\000\000\000\000\042\000\000\000\043\000\044\000\
\045\000\046\000\047\000\048\000\049\000\050\000\051\000\052\000\
\000\000\000\000\000\000\000\000\053\000\013\000\014\000\015\000\
\016\000\017\000\018\000\019\000\020\000\021\000\022\000\023\000\
\024\000\025\000\026\000\027\000\028\000\029\000\030\000\031\000\
\032\000\033\000\034\000\035\000\210\001\000\000\000\000\000\000\
\025\001\000\000\000\000\000\000\025\001\025\001\000\000\000\000\
\025\001\000\000\000\000\000\000\000\000\152\000\037\000\060\001\
\000\000\000\000\039\000\040\000\000\000\025\001\025\001\000\000\
\000\000\240\000\026\001\025\001\241\000\242\000\026\001\026\001\
\000\000\000\000\026\001\000\000\000\000\000\000\025\001\000\000\
\000\000\000\000\000\000\000\000\000\000\053\000\000\000\026\001\
\026\001\000\000\000\000\000\000\000\000\026\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\026\001\000\000\000\000\000\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\000\000\000\000\000\000\000\000\000\000\000\000\025\001\032\000\
\033\000\034\000\035\000\000\000\000\000\025\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\210\001\210\001\000\000\000\000\000\000\000\000\025\001\
\026\001\025\001\040\000\000\000\000\000\000\000\000\000\026\001\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\026\001\000\000\026\001\000\000\000\000\080\000\081\000\
\082\000\083\000\084\000\000\000\000\000\000\000\085\000\144\000\
\058\001\000\000\011\000\088\000\223\001\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\090\000\091\000\000\000\000\000\
\000\000\092\000\093\000\000\000\000\000\060\001\000\000\095\000\
\000\000\147\002\096\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\097\000\098\000\099\000\000\000\000\000\
\000\000\000\000\013\000\014\000\015\000\016\000\017\000\018\000\
\019\000\020\000\021\000\022\000\023\000\024\000\025\000\026\000\
\027\000\173\000\029\000\030\000\031\000\032\000\033\000\034\000\
\035\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\112\000\113\000\
\114\000\000\000\000\000\037\000\000\000\159\000\000\000\039\000\
\040\000\000\000\000\000\000\000\116\000\000\000\000\000\080\000\
\081\000\082\000\083\000\084\000\000\000\000\000\000\000\085\000\
\144\000\058\001\000\000\011\000\088\000\253\001\160\000\000\000\
\118\000\119\000\000\000\000\000\000\000\090\000\091\000\000\000\
\000\000\206\001\092\000\093\000\000\000\000\000\000\000\000\000\
\095\000\000\000\000\000\096\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\097\000\098\000\099\000\000\000\
\000\000\000\000\000\000\013\000\014\000\015\000\016\000\017\000\
\018\000\019\000\020\000\021\000\022\000\023\000\024\000\025\000\
\026\000\027\000\173\000\029\000\030\000\031\000\032\000\033\000\
\034\000\035\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\112\000\
\113\000\114\000\000\000\000\000\037\000\000\000\159\000\000\000\
\039\000\040\000\000\000\000\000\000\000\116\000\000\000\000\000\
\080\000\081\000\082\000\083\000\084\000\000\000\000\000\000\000\
\085\000\144\000\058\001\000\000\011\000\088\000\063\002\160\000\
\000\000\118\000\119\000\000\000\000\000\000\000\090\000\091\000\
\000\000\000\000\206\001\092\000\093\000\000\000\000\000\000\000\
\000\000\095\000\000\000\000\000\096\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\097\000\098\000\099\000\
\000\000\000\000\000\000\000\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\025\000\026\000\027\000\173\000\029\000\030\000\031\000\032\000\
\033\000\034\000\035\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\112\000\113\000\114\000\000\000\000\000\037\000\000\000\159\000\
\000\000\039\000\040\000\000\000\000\000\000\000\116\000\000\000\
\000\000\080\000\081\000\082\000\083\000\084\000\000\000\000\000\
\000\000\085\000\144\000\058\001\000\000\011\000\088\000\118\002\
\160\000\000\000\118\000\119\000\000\000\000\000\000\000\090\000\
\091\000\000\000\000\000\206\001\092\000\093\000\000\000\000\000\
\000\000\000\000\095\000\000\000\000\000\096\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\097\000\098\000\
\099\000\000\000\000\000\000\000\000\000\013\000\014\000\015\000\
\016\000\017\000\018\000\019\000\020\000\021\000\022\000\023\000\
\024\000\025\000\026\000\027\000\173\000\029\000\030\000\031\000\
\032\000\033\000\034\000\035\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\112\000\113\000\114\000\000\000\000\000\037\000\000\000\
\159\000\000\000\039\000\040\000\000\000\000\000\000\000\116\000\
\000\000\000\000\080\000\081\000\082\000\083\000\084\000\000\000\
\000\000\000\000\085\000\144\000\058\001\000\000\011\000\088\000\
\120\002\160\000\000\000\118\000\119\000\000\000\000\000\000\000\
\090\000\091\000\000\000\000\000\206\001\092\000\093\000\000\000\
\000\000\000\000\000\000\095\000\000\000\000\000\096\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\097\000\
\098\000\099\000\000\000\000\000\000\000\000\000\013\000\014\000\
\015\000\016\000\017\000\018\000\019\000\020\000\021\000\022\000\
\023\000\024\000\025\000\026\000\027\000\173\000\029\000\030\000\
\031\000\032\000\033\000\034\000\035\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\112\000\113\000\114\000\000\000\000\000\037\000\
\000\000\159\000\000\000\039\000\040\000\000\000\000\000\000\000\
\116\000\000\000\000\000\080\000\081\000\082\000\083\000\084\000\
\000\000\000\000\000\000\085\000\144\000\058\001\000\000\011\000\
\088\000\000\000\160\000\000\000\118\000\119\000\000\000\000\000\
\000\000\090\000\091\000\000\000\000\000\206\001\092\000\093\000\
\000\000\000\000\000\000\000\000\095\000\000\000\000\000\096\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\097\000\098\000\099\000\000\000\000\000\000\000\000\000\013\000\
\014\000\015\000\016\000\017\000\018\000\019\000\020\000\021\000\
\022\000\023\000\024\000\025\000\026\000\027\000\173\000\029\000\
\030\000\031\000\032\000\033\000\034\000\035\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\112\000\113\000\114\000\000\000\000\000\
\037\000\000\000\159\000\000\000\039\000\040\000\000\000\000\000\
\000\000\116\000\000\000\000\000\080\000\081\000\082\000\083\000\
\084\000\000\000\000\000\000\000\085\000\144\000\058\001\000\000\
\011\000\088\000\000\000\160\000\000\000\118\000\119\000\000\000\
\000\000\000\000\090\000\091\000\000\000\000\000\099\001\092\000\
\093\000\000\000\000\000\000\000\000\000\095\000\000\000\000\000\
\096\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\097\000\098\000\099\000\000\000\000\000\000\000\000\000\
\013\000\014\000\015\000\016\000\017\000\018\000\019\000\020\000\
\021\000\022\000\023\000\024\000\025\000\026\000\027\000\173\000\
\029\000\030\000\031\000\032\000\033\000\034\000\035\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\112\000\113\000\114\000\000\000\
\000\000\037\000\000\000\159\000\000\000\039\000\040\000\000\000\
\000\000\000\000\116\000\000\000\000\000\000\000\080\000\081\000\
\082\000\083\000\084\000\000\000\000\000\000\000\085\000\086\000\
\000\000\010\000\034\001\088\000\160\000\089\000\118\000\119\000\
\000\000\000\000\000\000\000\000\090\000\091\000\000\000\206\001\
\000\000\092\000\093\000\000\000\000\000\094\000\000\000\095\000\
\000\000\000\000\096\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\097\000\098\000\099\000\000\000\000\000\
\000\000\000\000\013\000\014\000\015\000\016\000\017\000\018\000\
\019\000\020\000\021\000\022\000\023\000\024\000\025\000\026\000\
\027\000\028\000\029\000\030\000\031\000\032\000\033\000\034\000\
\035\000\100\000\101\000\000\000\102\000\103\000\104\000\105\000\
\082\001\107\000\108\000\109\000\110\000\111\000\112\000\113\000\
\114\000\000\000\000\000\037\000\083\001\000\000\000\000\039\000\
\040\000\041\000\000\000\000\000\116\000\084\001\085\001\000\000\
\000\000\000\000\042\000\000\000\043\000\044\000\045\000\046\000\
\047\000\048\000\049\000\050\000\051\000\052\000\086\001\117\000\
\118\000\119\000\053\000\000\000\120\000\080\000\081\000\082\000\
\083\000\084\000\000\000\000\000\000\000\085\000\086\000\000\000\
\010\000\034\001\088\000\000\000\089\000\000\000\000\000\000\000\
\000\000\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\094\000\000\000\095\000\000\000\
\000\000\096\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\097\000\098\000\099\000\000\000\000\000\000\000\
\000\000\013\000\014\000\015\000\016\000\017\000\018\000\019\000\
\020\000\021\000\022\000\023\000\024\000\025\000\026\000\027\000\
\028\000\029\000\030\000\031\000\032\000\033\000\034\000\035\000\
\100\000\101\000\000\000\102\000\103\000\104\000\105\000\082\001\
\107\000\108\000\109\000\110\000\111\000\112\000\113\000\114\000\
\000\000\000\000\037\000\083\001\000\000\000\000\039\000\040\000\
\041\000\000\000\000\000\116\000\000\000\085\001\000\000\000\000\
\000\000\042\000\000\000\043\000\044\000\045\000\046\000\047\000\
\048\000\049\000\050\000\051\000\052\000\086\001\117\000\118\000\
\119\000\053\000\000\000\120\000\134\000\134\000\134\000\134\000\
\134\000\000\000\000\000\000\000\134\000\134\000\000\000\134\000\
\134\000\134\000\000\000\134\000\000\000\000\000\000\000\000\000\
\000\000\000\000\134\000\134\000\000\000\000\000\000\000\134\000\
\134\000\000\000\000\000\134\000\000\000\134\000\000\000\000\000\
\134\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\134\000\134\000\134\000\000\000\000\000\000\000\000\000\
\134\000\134\000\134\000\134\000\134\000\134\000\134\000\134\000\
\134\000\134\000\134\000\134\000\134\000\134\000\134\000\134\000\
\134\000\134\000\134\000\134\000\134\000\134\000\134\000\134\000\
\134\000\000\000\134\000\134\000\134\000\134\000\134\000\134\000\
\134\000\134\000\134\000\134\000\134\000\134\000\134\000\000\000\
\000\000\134\000\134\000\000\000\000\000\134\000\134\000\134\000\
\000\000\000\000\134\000\000\000\000\000\000\000\146\001\000\000\
\134\000\000\000\134\000\134\000\134\000\134\000\134\000\134\000\
\134\000\134\000\134\000\134\000\000\000\134\000\134\000\134\000\
\134\000\000\000\134\000\133\000\133\000\133\000\133\000\133\000\
\000\000\000\000\000\000\133\000\133\000\000\000\133\000\133\000\
\133\000\000\000\133\000\000\000\000\000\000\000\000\000\000\000\
\000\000\133\000\133\000\000\000\000\000\000\000\133\000\133\000\
\000\000\000\000\133\000\000\000\133\000\000\000\000\000\133\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\133\000\133\000\133\000\000\000\000\000\000\000\000\000\133\000\
\133\000\133\000\133\000\133\000\133\000\133\000\133\000\133\000\
\133\000\133\000\133\000\133\000\133\000\133\000\133\000\133\000\
\133\000\133\000\133\000\133\000\133\000\133\000\133\000\133\000\
\000\000\133\000\133\000\133\000\133\000\133\000\133\000\133\000\
\133\000\133\000\133\000\133\000\133\000\133\000\000\000\000\000\
\133\000\133\000\000\000\000\000\133\000\133\000\133\000\000\000\
\000\000\133\000\000\000\000\000\000\000\147\001\000\000\133\000\
\000\000\133\000\133\000\133\000\133\000\133\000\133\000\133\000\
\133\000\133\000\133\000\000\000\133\000\133\000\133\000\133\000\
\000\000\133\000\135\000\135\000\135\000\135\000\135\000\000\000\
\000\000\000\000\135\000\135\000\000\000\135\000\135\000\135\000\
\000\000\135\000\000\000\000\000\000\000\000\000\000\000\000\000\
\135\000\135\000\000\000\000\000\000\000\135\000\135\000\000\000\
\000\000\135\000\000\000\135\000\000\000\000\000\135\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\135\000\
\135\000\135\000\000\000\000\000\000\000\000\000\135\000\135\000\
\135\000\135\000\135\000\135\000\135\000\135\000\135\000\135\000\
\135\000\135\000\135\000\135\000\135\000\135\000\135\000\135\000\
\135\000\135\000\135\000\135\000\135\000\135\000\135\000\000\000\
\135\000\135\000\135\000\135\000\135\000\135\000\135\000\135\000\
\135\000\135\000\135\000\135\000\135\000\000\000\000\000\135\000\
\135\000\000\000\000\000\135\000\135\000\135\000\000\000\000\000\
\135\000\000\000\000\000\000\000\151\001\000\000\135\000\000\000\
\135\000\135\000\135\000\135\000\135\000\135\000\135\000\135\000\
\135\000\135\000\000\000\135\000\135\000\135\000\135\000\000\000\
\135\000\080\000\081\000\082\000\083\000\084\000\000\000\000\000\
\000\000\085\000\086\000\000\000\010\000\034\001\088\000\000\000\
\089\000\000\000\000\000\000\000\000\000\000\000\000\000\090\000\
\091\000\000\000\000\000\000\000\092\000\093\000\000\000\000\000\
\094\000\000\000\095\000\000\000\000\000\096\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\097\000\098\000\
\099\000\000\000\000\000\000\000\000\000\013\000\014\000\015\000\
\016\000\017\000\018\000\019\000\020\000\021\000\022\000\023\000\
\024\000\025\000\026\000\027\000\028\000\029\000\030\000\031\000\
\032\000\033\000\034\000\035\000\100\000\101\000\000\000\102\000\
\035\001\104\000\105\000\106\000\107\000\108\000\109\000\110\000\
\036\001\112\000\113\000\114\000\000\000\000\000\037\000\115\000\
\000\000\000\000\039\000\040\000\041\000\000\000\000\000\116\000\
\000\000\000\000\000\000\000\000\000\000\042\000\000\000\043\000\
\044\000\045\000\046\000\047\000\048\000\049\000\050\000\051\000\
\052\000\000\000\117\000\118\000\119\000\053\000\000\000\120\000\
\080\000\081\000\082\000\083\000\084\000\000\000\000\000\000\000\
\085\000\086\000\000\000\000\000\034\001\088\000\000\000\089\000\
\000\000\000\000\000\000\000\000\000\000\000\000\090\000\091\000\
\000\000\000\000\000\000\092\000\093\000\000\000\000\000\094\000\
\000\000\095\000\000\000\000\000\096\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\097\000\098\000\099\000\
\000\000\000\000\000\000\000\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\025\000\026\000\027\000\028\000\029\000\030\000\031\000\032\000\
\033\000\034\000\035\000\100\000\101\000\000\000\102\000\103\000\
\104\000\105\000\106\000\107\000\108\000\109\000\110\000\111\000\
\112\000\113\000\114\000\000\000\000\000\037\000\115\000\000\000\
\000\000\039\000\040\000\000\000\000\000\000\000\116\000\000\000\
\000\000\080\000\081\000\082\000\083\000\084\000\000\000\000\000\
\240\000\085\000\086\000\241\000\000\000\087\000\088\000\000\000\
\089\000\117\000\118\000\119\000\053\000\000\000\120\000\090\000\
\091\000\000\000\000\000\000\000\092\000\093\000\000\000\000\000\
\094\000\000\000\095\000\000\000\000\000\096\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\097\000\098\000\
\099\000\000\000\000\000\013\000\014\000\015\000\016\000\017\000\
\018\000\019\000\020\000\021\000\022\000\023\000\024\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\032\000\033\000\
\034\000\035\000\000\000\000\000\100\000\101\000\000\000\102\000\
\103\000\104\000\105\000\106\000\107\000\108\000\109\000\110\000\
\111\000\112\000\113\000\114\000\000\000\000\000\000\000\115\000\
\000\000\040\000\080\000\081\000\082\000\083\000\084\000\116\000\
\000\000\000\000\085\000\144\000\000\000\000\000\011\000\088\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\090\000\091\000\117\000\118\000\119\000\092\000\093\000\120\000\
\000\000\094\000\000\000\095\000\000\000\000\000\096\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\097\000\
\098\000\099\000\000\000\000\000\000\000\000\000\013\000\014\000\
\015\000\016\000\017\000\018\000\019\000\020\000\021\000\022\000\
\023\000\024\000\025\000\026\000\027\000\028\000\029\000\030\000\
\031\000\032\000\033\000\034\000\035\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\080\000\081\000\082\000\
\083\000\084\000\112\000\113\000\114\000\085\000\144\000\037\000\
\000\000\011\000\088\000\039\000\040\000\000\000\000\000\000\000\
\116\000\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\000\000\000\000\095\000\000\000\
\000\000\096\000\000\000\000\000\118\000\119\000\053\000\000\000\
\000\000\000\000\097\000\098\000\099\000\000\000\000\000\000\000\
\000\000\013\000\014\000\015\000\016\000\017\000\018\000\019\000\
\020\000\021\000\022\000\023\000\024\000\000\000\000\000\000\000\
\000\000\000\000\030\000\031\000\032\000\033\000\034\000\035\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\112\000\113\000\114\000\
\000\000\000\000\037\000\000\000\000\000\000\000\000\000\040\000\
\000\000\000\000\000\000\116\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\080\000\081\000\082\000\
\083\000\084\000\000\000\000\000\000\000\085\000\049\002\118\000\
\119\000\166\000\088\000\000\000\050\002\176\002\051\002\000\000\
\052\002\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\000\000\000\000\095\000\000\000\
\000\000\096\000\000\000\000\000\000\000\080\000\081\000\082\000\
\083\000\084\000\097\000\098\000\099\000\085\000\049\002\000\000\
\000\000\166\000\088\000\000\000\050\002\228\002\051\002\000\000\
\052\002\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\000\000\000\000\095\000\000\000\
\000\000\096\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\097\000\098\000\099\000\112\000\113\000\114\000\
\080\000\081\000\082\000\083\000\084\000\000\000\000\000\000\000\
\085\000\049\002\000\000\116\000\166\000\088\000\000\000\050\002\
\000\000\051\002\000\000\052\002\000\000\000\000\090\000\091\000\
\000\000\000\000\000\000\092\000\093\000\000\000\000\000\118\000\
\119\000\095\000\000\000\000\000\096\000\112\000\113\000\114\000\
\080\000\081\000\082\000\083\000\084\000\097\000\098\000\099\000\
\085\000\144\000\000\000\116\000\000\000\088\000\000\000\089\000\
\000\000\000\000\000\000\000\000\000\000\000\000\090\000\091\000\
\000\000\000\000\000\000\092\000\093\000\000\000\000\000\118\000\
\119\000\095\000\000\000\000\000\096\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\097\000\098\000\099\000\
\112\000\113\000\114\000\080\000\081\000\082\000\083\000\084\000\
\000\000\000\000\000\000\085\000\144\000\000\000\116\000\000\000\
\088\000\000\000\000\000\000\000\000\000\011\002\000\000\000\000\
\000\000\090\000\091\000\000\000\000\000\000\000\092\000\093\000\
\000\000\000\000\118\000\119\000\095\000\000\000\000\000\096\000\
\112\000\113\000\114\000\080\000\081\000\082\000\083\000\084\000\
\097\000\098\000\099\000\085\000\144\000\000\000\116\000\000\000\
\088\000\000\000\000\000\000\000\000\000\075\002\000\000\000\000\
\000\000\090\000\091\000\000\000\000\000\000\000\092\000\093\000\
\000\000\000\000\118\000\119\000\095\000\000\000\000\000\096\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\097\000\098\000\099\000\112\000\113\000\114\000\080\000\081\000\
\082\000\083\000\084\000\000\000\000\000\000\000\085\000\144\000\
\000\000\116\000\000\000\088\000\000\000\050\002\000\000\000\000\
\000\000\000\000\000\000\000\000\090\000\091\000\000\000\000\000\
\000\000\092\000\093\000\000\000\000\000\118\000\119\000\095\000\
\000\000\000\000\096\000\112\000\113\000\114\000\000\000\000\000\
\000\000\000\000\000\000\097\000\098\000\099\000\000\000\000\000\
\000\000\116\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\118\000\119\000\080\000\
\081\000\082\000\083\000\084\000\000\000\000\000\000\000\085\000\
\144\000\000\000\000\000\000\000\088\000\000\000\112\000\113\000\
\114\000\000\000\000\000\000\000\000\000\090\000\091\000\000\000\
\000\000\000\000\092\000\093\000\116\000\000\000\094\000\000\000\
\095\000\000\000\000\000\096\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\097\000\098\000\099\000\000\000\
\118\000\119\000\080\000\081\000\082\000\083\000\084\000\000\000\
\000\000\000\000\085\000\144\000\000\000\000\000\000\000\088\000\
\000\000\133\002\000\000\000\000\000\000\000\000\000\000\000\000\
\090\000\091\000\000\000\000\000\000\000\092\000\093\000\000\000\
\000\000\000\000\000\000\095\000\000\000\000\000\096\000\112\000\
\113\000\114\000\080\000\081\000\082\000\083\000\084\000\097\000\
\098\000\099\000\085\000\144\000\000\000\116\000\000\000\088\000\
\000\000\000\000\000\000\000\000\141\002\000\000\000\000\000\000\
\090\000\091\000\000\000\000\000\000\000\092\000\093\000\000\000\
\000\000\118\000\119\000\095\000\000\000\000\000\096\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\097\000\
\098\000\099\000\112\000\113\000\114\000\080\000\081\000\082\000\
\083\000\084\000\000\000\000\000\000\000\085\000\144\000\000\000\
\116\000\000\000\088\000\211\002\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\118\000\119\000\095\000\000\000\
\000\000\096\000\112\000\113\000\114\000\080\000\081\000\082\000\
\083\000\084\000\097\000\098\000\099\000\085\000\144\000\000\000\
\116\000\000\000\088\000\213\002\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\090\000\091\000\000\000\000\000\000\000\
\092\000\093\000\000\000\000\000\118\000\119\000\095\000\000\000\
\000\000\096\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\097\000\098\000\099\000\112\000\113\000\114\000\
\080\000\081\000\082\000\083\000\084\000\000\000\000\000\000\000\
\085\000\144\000\000\000\116\000\000\000\088\000\000\000\000\000\
\000\000\000\000\011\000\000\000\000\000\000\000\090\000\091\000\
\000\000\000\000\000\000\092\000\093\000\000\000\000\000\118\000\
\119\000\095\000\000\000\000\000\096\000\112\000\113\000\114\000\
\000\000\000\000\000\000\000\000\000\000\097\000\098\000\099\000\
\000\000\000\000\000\000\116\000\000\000\000\000\000\000\000\000\
\000\000\000\000\013\000\014\000\015\000\016\000\017\000\018\000\
\019\000\020\000\021\000\022\000\023\000\024\000\000\000\118\000\
\119\000\000\000\000\000\030\000\031\000\032\000\033\000\034\000\
\035\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\112\000\113\000\114\000\000\000\228\001\228\001\000\000\228\001\
\228\001\228\001\228\001\037\000\228\001\000\000\116\000\228\001\
\040\000\000\000\000\000\000\000\228\001\000\000\000\000\000\000\
\000\000\228\001\228\001\000\000\000\000\000\000\000\000\228\001\
\000\000\000\000\118\000\119\000\000\000\000\000\000\000\000\000\
\000\000\000\000\228\001\000\000\000\000\000\000\000\000\228\001\
\228\001\228\001\228\001\228\001\228\001\228\001\228\001\228\001\
\228\001\228\001\228\001\228\001\228\001\228\001\228\001\228\001\
\228\001\228\001\228\001\228\001\228\001\228\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\228\001\000\000\
\228\001\000\000\000\000\000\000\228\001\228\001\228\001\000\000\
\057\001\228\001\000\000\057\001\057\001\057\001\000\000\228\001\
\057\001\000\000\000\000\057\001\000\000\000\000\000\000\000\000\
\228\001\228\001\228\001\000\000\000\000\228\001\057\001\228\001\
\000\000\000\000\000\000\057\001\000\000\228\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\057\001\000\000\
\000\000\000\000\000\000\057\001\057\001\057\001\057\001\057\001\
\057\001\057\001\057\001\057\001\057\001\057\001\057\001\057\001\
\057\001\057\001\057\001\057\001\057\001\057\001\057\001\057\001\
\057\001\057\001\000\000\000\000\000\000\000\000\000\000\000\000\
\047\001\000\000\000\000\000\000\047\001\047\001\000\000\000\000\
\047\001\000\000\000\000\047\001\057\001\000\000\057\001\058\001\
\057\001\057\001\058\001\058\001\058\001\057\001\047\001\058\001\
\000\000\057\001\058\001\047\001\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\058\001\047\001\057\001\
\000\000\057\001\058\001\000\000\000\000\000\000\000\000\000\000\
\000\000\057\001\000\000\000\000\000\000\058\001\000\000\000\000\
\000\000\000\000\058\001\058\001\058\001\058\001\058\001\058\001\
\058\001\058\001\058\001\058\001\058\001\058\001\058\001\058\001\
\058\001\058\001\058\001\058\001\058\001\058\001\058\001\058\001\
\058\001\000\000\000\000\000\000\000\000\000\000\047\001\045\001\
\000\000\000\000\000\000\045\001\045\001\047\001\000\000\045\001\
\000\000\047\001\045\001\058\001\000\000\058\001\000\000\058\001\
\058\001\000\000\000\000\000\000\058\001\045\001\000\000\047\001\
\058\001\047\001\045\001\000\000\000\000\000\000\000\000\046\001\
\000\000\047\001\000\000\046\001\046\001\045\001\058\001\046\001\
\058\001\000\000\046\001\000\000\000\000\000\000\044\001\000\000\
\058\001\000\000\044\001\044\001\000\000\046\001\044\001\000\000\
\000\000\044\001\046\001\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\044\001\046\001\000\000\000\000\
\000\000\044\001\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\044\001\045\001\000\000\000\000\
\000\000\000\000\000\000\000\000\045\001\000\000\000\000\000\000\
\045\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\045\001\000\000\
\045\001\000\000\000\000\000\000\000\000\046\001\000\000\000\000\
\045\001\000\000\000\000\000\000\046\001\000\000\000\000\000\000\
\046\001\000\000\000\000\000\000\044\001\000\000\000\000\000\000\
\000\000\000\000\000\000\044\001\000\000\000\000\046\001\044\001\
\046\001\241\000\000\000\241\000\241\000\000\000\000\000\000\000\
\046\001\241\000\000\000\000\000\000\000\044\001\241\000\044\001\
\000\000\000\000\000\000\241\000\241\000\000\000\000\000\044\001\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\241\000\241\000\241\000\241\000\241\000\241\000\241\000\
\241\000\241\000\241\000\241\000\241\000\241\000\241\000\241\000\
\241\000\241\000\241\000\241\000\241\000\241\000\241\000\241\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\241\000\000\000\241\000\241\000\241\000\000\000\241\000\241\000\
\241\000\000\000\000\000\000\000\240\000\000\000\240\000\240\000\
\000\000\241\000\000\000\000\000\240\000\000\000\000\000\000\000\
\000\000\240\000\241\000\241\000\241\000\241\000\240\000\240\000\
\000\000\241\000\000\000\000\000\000\000\000\000\000\000\241\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\240\000\240\000\240\000\240\000\
\240\000\240\000\240\000\240\000\240\000\240\000\240\000\240\000\
\240\000\240\000\240\000\240\000\240\000\240\000\240\000\240\000\
\240\000\240\000\240\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\240\000\000\000\240\000\240\000\240\000\
\000\000\240\000\240\000\240\000\000\000\052\001\000\000\000\000\
\052\001\052\001\000\000\000\000\240\000\052\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\240\000\240\000\240\000\
\240\000\000\000\000\000\052\001\240\000\000\000\000\000\000\000\
\052\001\000\000\240\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\052\001\000\000\000\000\000\000\000\000\
\052\001\052\001\052\001\052\001\052\001\052\001\052\001\052\001\
\052\001\052\001\052\001\052\001\052\001\052\001\052\001\052\001\
\052\001\052\001\052\001\052\001\052\001\052\001\052\001\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\228\000\000\000\000\000\228\000\228\000\000\000\
\000\000\052\001\228\000\052\001\000\000\052\001\052\001\000\000\
\000\000\000\000\052\001\000\000\000\000\000\000\052\001\011\000\
\228\000\000\000\000\000\000\000\000\000\228\000\000\000\000\000\
\000\000\000\000\000\000\000\000\052\001\000\000\052\001\000\000\
\228\000\000\000\000\000\052\001\000\000\228\000\228\000\228\000\
\228\000\228\000\228\000\228\000\228\000\228\000\228\000\228\000\
\228\000\228\000\228\000\228\000\228\000\228\000\228\000\228\000\
\228\000\228\000\228\000\228\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\010\000\011\000\000\000\000\000\000\000\
\159\002\000\000\000\000\000\000\000\000\000\000\228\000\000\000\
\228\000\000\000\228\000\228\000\000\000\000\000\000\000\228\000\
\000\000\000\000\000\000\228\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\228\000\000\000\228\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\025\000\026\000\027\000\028\000\029\000\030\000\031\000\032\000\
\033\000\034\000\035\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\010\000\011\000\000\000\000\000\
\000\000\232\002\000\000\000\000\152\000\037\000\000\000\000\000\
\000\000\039\000\040\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\053\000\013\000\014\000\015\000\
\016\000\017\000\018\000\019\000\020\000\021\000\022\000\023\000\
\024\000\025\000\026\000\027\000\028\000\029\000\030\000\031\000\
\032\000\033\000\034\000\035\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\133\001\
\000\000\000\000\133\001\000\000\000\000\152\000\037\000\066\001\
\000\000\000\000\039\000\040\000\066\001\000\000\000\000\000\000\
\000\000\000\000\066\001\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\053\000\000\000\133\001\
\133\001\133\001\133\001\133\001\133\001\133\001\133\001\133\001\
\133\001\133\001\133\001\133\001\133\001\133\001\133\001\133\001\
\133\001\133\001\133\001\133\001\133\001\133\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\135\001\000\000\000\000\135\001\066\001\000\000\
\133\001\000\000\069\001\000\000\133\001\133\001\133\001\069\001\
\000\000\000\000\000\000\000\000\000\000\069\001\000\000\133\001\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\133\001\133\001\133\001\000\000\000\000\000\000\000\000\133\001\
\000\000\000\000\135\001\135\001\135\001\135\001\135\001\135\001\
\135\001\135\001\135\001\135\001\135\001\135\001\135\001\135\001\
\135\001\135\001\135\001\135\001\135\001\135\001\135\001\135\001\
\135\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\134\001\000\000\000\000\
\134\001\069\001\000\000\135\001\000\000\068\001\000\000\135\001\
\135\001\135\001\068\001\000\000\000\000\000\000\000\000\000\000\
\068\001\000\000\135\001\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\135\001\135\001\135\001\000\000\000\000\
\000\000\000\000\135\001\000\000\000\000\134\001\134\001\134\001\
\134\001\134\001\134\001\134\001\134\001\134\001\134\001\134\001\
\134\001\134\001\134\001\134\001\134\001\134\001\134\001\134\001\
\134\001\134\001\134\001\134\001\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\011\000\000\000\
\000\000\089\000\000\000\000\000\068\001\000\000\134\001\000\000\
\000\000\000\000\134\001\134\001\134\001\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\134\001\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\134\001\134\001\
\134\001\000\000\000\000\000\000\000\000\134\001\013\000\014\000\
\015\000\016\000\017\000\018\000\019\000\020\000\021\000\022\000\
\023\000\024\000\025\000\026\000\027\000\028\000\029\000\030\000\
\031\000\032\000\033\000\034\000\035\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\011\000\
\000\000\000\000\089\000\000\000\000\000\000\000\000\000\037\000\
\000\000\000\000\000\000\039\000\040\000\041\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\042\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\050\000\
\051\000\052\000\000\000\000\000\000\000\000\000\053\000\013\000\
\014\000\015\000\016\000\017\000\018\000\019\000\020\000\021\000\
\022\000\023\000\024\000\025\000\026\000\027\000\028\000\029\000\
\030\000\031\000\032\000\033\000\034\000\035\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\009\000\000\000\000\000\
\011\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\037\000\000\000\000\000\000\000\039\000\040\000\000\000\000\000\
\000\000\000\000\000\000\128\001\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\053\000\
\013\000\014\000\015\000\016\000\017\000\018\000\019\000\020\000\
\021\000\022\000\023\000\024\000\000\000\000\000\000\000\000\000\
\000\000\030\000\031\000\032\000\033\000\034\000\035\000\000\000\
\000\000\000\000\058\001\000\000\011\000\000\000\059\001\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\037\000\000\000\000\000\000\000\000\000\040\000\041\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\042\000\000\000\043\000\044\000\045\000\046\000\047\000\048\000\
\049\000\050\000\051\000\052\000\013\000\014\000\015\000\016\000\
\017\000\018\000\019\000\020\000\021\000\022\000\023\000\024\000\
\025\000\026\000\027\000\173\000\029\000\030\000\031\000\032\000\
\033\000\034\000\035\000\000\000\000\000\000\000\000\000\000\000\
\058\001\000\000\011\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\037\000\000\000\159\000\
\000\000\039\000\040\000\146\002\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\160\000\000\000\013\000\014\000\015\000\016\000\017\000\018\000\
\019\000\020\000\021\000\022\000\023\000\024\000\025\000\026\000\
\027\000\173\000\029\000\030\000\031\000\032\000\033\000\034\000\
\035\000\000\000\000\000\000\000\000\000\058\001\000\000\011\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\037\000\000\000\159\000\000\000\039\000\
\040\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\160\000\013\000\
\014\000\015\000\016\000\017\000\018\000\019\000\020\000\021\000\
\022\000\023\000\024\000\025\000\026\000\027\000\173\000\029\000\
\030\000\031\000\032\000\033\000\034\000\035\000\000\000\000\000\
\000\000\000\000\191\001\000\000\191\001\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\037\000\000\000\159\000\000\000\039\000\040\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\160\000\191\001\191\001\191\001\191\001\
\191\001\191\001\191\001\191\001\191\001\191\001\191\001\191\001\
\191\001\191\001\191\001\191\001\191\001\191\001\191\001\191\001\
\191\001\191\001\191\001\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\191\001\000\000\191\001\
\000\000\191\001\191\001\000\000\000\000\000\000\000\000\000\000\
\008\000\000\000\000\000\000\000\008\000\000\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\000\000\000\000\
\191\001\010\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\009\000\
\000\000\000\000\000\000\009\000\000\000\009\000\009\000\009\000\
\009\000\009\000\009\000\009\000\009\000\058\001\000\000\011\000\
\012\000\009\000\009\000\009\000\009\000\009\000\009\000\009\000\
\009\000\009\000\009\000\009\000\009\000\009\000\009\000\009\000\
\009\000\009\000\009\000\009\000\009\000\009\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\008\000\000\000\013\000\
\014\000\015\000\016\000\017\000\018\000\019\000\020\000\021\000\
\022\000\023\000\024\000\025\000\026\000\027\000\173\000\029\000\
\030\000\031\000\032\000\033\000\034\000\035\000\105\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\009\000\000\000\000\000\000\000\
\037\000\000\000\000\000\000\000\039\000\040\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\105\000\105\000\
\105\000\105\000\105\000\105\000\105\000\105\000\105\000\105\000\
\105\000\105\000\000\000\000\000\000\000\000\000\000\000\105\000\
\105\000\105\000\105\000\105\000\105\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\105\000\
\000\000\000\000\175\000\000\000\105\000\175\000\175\000\175\000\
\175\000\175\000\000\000\000\000\000\000\175\000\000\000\175\000\
\175\000\175\000\175\000\175\000\000\000\175\000\000\000\175\000\
\175\000\175\000\175\000\175\000\175\000\175\000\175\000\175\000\
\175\000\175\000\175\000\175\000\175\000\175\000\175\000\175\000\
\175\000\175\000\175\000\175\000\175\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\171\000\000\000\000\000\171\000\171\000\171\000\
\171\000\171\000\000\000\000\000\000\000\171\000\175\000\171\000\
\171\000\171\000\171\000\171\000\175\000\171\000\000\000\171\000\
\171\000\171\000\171\000\171\000\171\000\171\000\171\000\171\000\
\171\000\171\000\171\000\171\000\171\000\171\000\171\000\171\000\
\171\000\171\000\171\000\171\000\171\000\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\153\001\000\000\000\000\154\001\155\001\156\001\
\157\001\158\001\000\000\000\000\000\000\159\001\171\000\160\001\
\161\001\162\001\163\001\164\001\171\000\165\001\000\000\166\001\
\000\000\167\001\168\001\169\001\170\001\171\001\172\001\173\001\
\174\001\175\001\176\001\177\001\178\001\179\001\180\001\181\001\
\182\001\183\001\184\001\185\001\186\001\000\000\000\000\000\000\
\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\
\000\000\000\000\008\000\000\000\000\000\008\000\008\000\000\000\
\008\000\008\000\008\000\008\000\008\000\000\000\187\001\008\000\
\000\000\000\000\000\000\005\000\188\001\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000\008\000\008\000\008\000\008\000\008\000\008\000\008\000\
\008\000"

let yycheck = "\003\000\
\002\000\034\000\002\000\176\000\003\000\002\000\191\000\125\001\
\008\000\135\000\181\000\008\000\004\000\051\001\032\002\143\000\
\000\000\000\000\008\001\103\000\052\001\014\001\103\000\018\001\
\010\000\253\000\030\001\008\001\014\001\077\001\018\001\017\001\
\103\000\069\002\018\001\014\001\228\000\055\002\017\001\002\000\
\073\000\019\001\062\001\114\000\190\001\000\000\172\000\025\001\
\176\000\068\002\246\000\019\001\019\001\018\001\035\001\021\001\
\000\000\025\001\025\001\002\000\056\002\018\001\133\000\250\000\
\019\001\086\002\032\000\033\000\148\000\149\000\025\001\173\002\
\174\002\052\001\152\001\175\000\076\000\179\002\100\001\076\000\
\180\000\181\000\114\001\018\001\021\001\151\000\170\000\075\001\
\124\002\170\000\086\002\022\001\096\001\021\001\114\001\014\001\
\088\000\110\000\100\000\170\000\039\000\067\000\106\000\125\001\
\005\003\006\003\110\000\106\000\018\001\018\001\075\001\076\000\
\022\001\043\001\107\001\110\001\000\000\109\000\075\001\058\000\
\246\000\107\001\021\001\088\000\183\002\203\001\206\000\066\000\
\107\001\018\001\143\000\070\000\151\002\076\000\127\001\036\003\
\110\001\133\002\128\001\143\000\005\000\127\001\242\000\143\000\
\143\000\111\001\143\000\128\001\127\001\110\001\250\000\251\000\
\067\001\019\001\254\000\255\000\169\000\135\001\014\001\177\002\
\090\001\017\001\032\001\018\001\095\001\169\000\114\001\135\001\
\135\001\035\001\016\003\043\001\176\000\191\002\111\001\234\002\
\176\000\176\000\022\001\176\000\135\001\036\001\018\001\111\001\
\176\000\151\000\001\001\002\001\003\001\004\001\005\001\006\001\
\007\001\008\001\009\001\010\001\011\001\012\001\013\001\014\001\
\015\001\016\001\017\001\018\001\019\001\020\001\192\000\035\001\
\078\001\124\001\035\001\211\000\111\001\019\001\211\000\105\002\
\235\002\020\003\090\001\025\001\035\001\193\001\050\001\067\001\
\190\000\050\001\018\002\131\000\228\000\250\002\151\000\228\000\
\224\000\237\000\255\002\050\001\110\001\237\000\230\000\231\000\
\016\002\023\002\234\000\206\000\210\000\055\001\211\000\212\000\
\113\000\253\000\014\002\095\001\016\002\253\000\025\001\065\001\
\018\001\085\001\194\001\195\001\022\001\067\000\107\001\206\000\
\000\001\036\001\131\000\024\001\025\001\212\000\085\001\175\000\
\193\000\204\001\205\001\215\001\024\001\025\001\132\001\041\001\
\124\001\125\001\092\001\148\000\149\000\113\001\043\001\023\001\
\113\001\005\002\052\001\019\001\019\001\025\001\014\001\043\001\
\099\001\100\001\113\001\043\001\043\001\019\001\043\001\127\001\
\036\001\111\001\010\001\025\001\012\001\023\001\175\000\025\001\
\014\001\137\001\071\001\079\002\018\001\221\000\208\002\185\000\
\019\001\183\002\125\001\071\001\054\001\025\001\025\001\018\001\
\194\000\135\001\030\001\019\001\018\001\090\001\082\001\239\000\
\036\001\025\001\100\001\082\001\025\001\206\000\090\001\025\001\
\210\000\215\001\090\001\090\001\014\001\090\001\023\002\036\001\
\018\001\035\001\036\001\065\001\221\000\025\001\025\001\023\001\
\204\001\205\001\046\002\125\001\192\001\090\000\091\000\192\001\
\036\001\036\001\034\001\030\002\234\002\000\000\239\000\041\001\
\023\001\192\001\025\001\185\000\144\002\111\001\092\001\018\001\
\049\001\191\000\052\001\112\000\194\000\073\002\055\001\019\001\
\019\001\021\001\035\001\023\001\096\001\025\001\025\001\023\001\
\065\001\025\001\018\001\031\001\210\000\107\001\034\001\035\001\
\036\001\037\001\038\001\121\001\111\001\014\001\020\003\018\001\
\017\001\000\000\014\001\022\001\127\001\137\002\132\001\111\001\
\000\000\127\001\018\001\092\001\138\001\088\002\137\001\018\001\
\046\002\034\001\018\001\022\001\135\001\252\001\090\000\091\000\
\127\001\107\001\030\002\015\002\021\001\193\001\015\002\135\001\
\025\001\193\001\137\001\019\001\129\001\130\001\119\001\065\001\
\015\002\025\001\019\001\073\002\112\000\127\001\035\001\035\002\
\025\001\037\002\035\002\000\000\037\002\070\001\029\001\030\001\
\036\001\027\002\035\001\223\001\035\002\213\001\037\002\051\002\
\223\001\069\002\051\002\111\001\056\002\169\002\022\001\014\001\
\024\001\014\001\026\001\018\001\051\002\019\001\210\002\022\001\
\008\001\056\002\018\001\025\001\088\002\025\001\014\001\187\002\
\105\001\018\001\020\001\135\001\129\001\170\002\022\001\121\001\
\004\002\005\002\086\002\065\001\004\002\005\002\127\001\019\001\
\014\001\020\001\132\001\017\001\096\002\025\001\020\001\086\002\
\137\001\139\001\020\001\052\002\033\002\034\001\035\001\035\001\
\124\002\096\002\022\001\013\002\024\001\033\002\092\001\014\001\
\132\002\111\001\030\001\018\001\019\001\039\002\038\002\022\001\
\019\001\038\002\170\002\169\002\019\001\011\001\025\001\014\001\
\018\001\133\002\025\001\018\001\022\001\009\001\014\001\022\001\
\022\002\017\001\041\001\121\001\020\001\187\002\133\002\034\001\
\035\001\020\001\019\001\014\001\107\001\052\001\132\001\041\001\
\025\001\014\001\041\001\019\001\017\001\139\001\104\001\020\001\
\019\001\025\001\052\001\183\002\019\001\052\001\025\001\113\001\
\127\001\173\002\174\002\000\000\089\001\019\001\018\001\179\002\
\122\001\123\001\124\001\025\001\021\002\019\001\173\002\174\002\
\166\001\109\002\027\002\025\001\179\002\018\001\109\002\115\002\
\116\002\018\001\035\001\199\002\115\002\116\002\022\001\000\000\
\112\002\113\002\114\002\014\001\107\001\091\002\017\001\131\002\
\199\002\020\001\019\001\014\001\131\002\137\002\234\002\018\001\
\019\001\137\002\238\002\022\001\107\001\019\001\025\001\035\001\
\127\001\145\002\019\001\025\001\145\002\018\001\019\001\030\001\
\025\001\022\001\021\001\021\002\020\001\036\001\019\001\161\002\
\127\001\027\002\246\002\019\001\025\001\246\002\170\002\019\001\
\019\001\025\001\170\002\170\002\041\001\170\002\025\001\246\002\
\020\003\025\001\170\002\019\001\019\001\018\001\021\001\052\001\
\023\001\025\001\025\001\019\001\016\003\021\001\019\001\023\001\
\031\001\025\001\025\001\034\001\035\001\036\001\037\001\038\001\
\039\001\016\003\034\001\035\001\036\001\030\001\210\002\211\002\
\052\003\213\002\210\002\036\001\211\002\205\002\213\002\021\002\
\014\001\023\002\030\001\019\001\018\001\027\002\019\001\019\001\
\107\001\025\001\092\002\019\001\111\001\025\001\019\001\197\002\
\021\001\025\001\023\001\030\001\025\001\035\001\240\002\000\000\
\019\001\036\001\031\001\041\001\127\001\034\001\035\001\036\001\
\037\001\241\002\019\001\014\001\135\001\111\001\052\001\018\001\
\014\001\041\001\123\002\022\001\018\001\111\001\010\003\110\001\
\012\003\136\001\014\003\010\003\052\001\012\003\019\001\014\003\
\111\001\036\001\019\001\019\001\025\001\019\001\041\001\111\001\
\025\001\025\001\019\001\041\001\018\001\021\001\092\002\019\001\
\025\001\052\001\074\001\075\001\107\001\025\001\052\001\024\001\
\135\001\001\000\002\000\003\000\004\000\005\000\100\001\135\001\
\018\001\036\001\136\001\018\001\035\001\107\001\019\001\022\001\
\019\001\024\001\098\001\026\001\027\001\028\001\023\001\021\001\
\035\001\089\001\111\001\036\001\018\001\035\001\025\001\125\001\
\036\001\127\001\018\001\197\002\023\001\014\001\035\001\000\000\
\020\001\100\001\014\001\035\001\023\001\125\001\100\001\036\001\
\107\001\019\001\135\001\019\001\018\001\107\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\025\001\000\000\018\001\
\021\001\019\001\125\001\019\001\127\001\014\001\019\001\125\001\
\021\001\127\001\023\001\014\001\025\001\052\001\053\001\054\001\
\055\001\056\001\031\001\082\001\025\001\034\001\035\001\036\001\
\037\001\038\001\039\001\040\001\041\001\014\001\036\001\197\002\
\017\001\018\001\019\001\020\001\021\001\022\001\023\001\024\001\
\025\001\026\001\027\001\028\001\029\001\030\001\031\001\023\001\
\033\001\034\001\035\001\036\001\037\001\038\001\039\001\040\001\
\041\001\042\001\043\001\044\001\045\001\046\001\047\001\048\001\
\049\001\050\001\051\001\052\001\053\001\054\001\055\001\056\001\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\019\001\
\111\001\082\001\111\001\025\001\021\001\036\001\019\001\088\001\
\036\001\036\001\021\001\036\001\019\001\008\001\023\001\096\001\
\018\001\098\001\099\001\100\001\036\001\102\001\103\001\104\001\
\000\000\019\001\135\001\009\001\036\001\021\001\111\001\000\000\
\113\001\111\001\021\001\036\001\036\001\035\001\019\001\019\001\
\111\001\122\001\123\001\124\001\125\001\021\001\111\001\111\001\
\129\001\021\001\036\001\035\001\021\001\014\001\135\001\019\001\
\017\001\018\001\019\001\020\001\021\001\022\001\023\001\024\001\
\025\001\026\001\027\001\028\001\029\001\030\001\031\001\021\001\
\033\001\034\001\035\001\036\001\037\001\038\001\039\001\040\001\
\041\001\042\001\043\001\044\001\045\001\046\001\047\001\048\001\
\049\001\050\001\051\001\052\001\053\001\054\001\055\001\056\001\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\021\001\
\111\001\082\001\111\001\111\001\002\000\084\001\111\001\088\001\
\216\000\123\002\135\000\206\001\099\001\240\002\040\002\096\001\
\052\003\098\001\099\001\100\001\203\002\102\001\103\001\104\001\
\000\000\163\000\119\001\203\000\076\002\014\001\111\001\066\001\
\113\001\018\001\019\001\121\001\205\000\022\001\199\002\127\001\
\025\001\122\001\123\001\124\001\125\001\087\002\058\002\137\001\
\129\001\197\002\095\002\168\000\014\001\071\001\135\001\017\001\
\018\001\019\001\153\002\021\001\022\001\023\001\033\002\025\001\
\170\002\255\255\129\002\029\001\030\001\031\001\255\255\255\255\
\034\001\035\001\036\001\037\001\038\001\039\001\040\001\041\001\
\042\001\043\001\044\001\045\001\046\001\047\001\048\001\049\001\
\050\001\051\001\052\001\053\001\054\001\055\001\056\001\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\107\001\255\255\255\255\255\255\111\001\048\001\
\049\001\050\001\051\001\052\001\053\001\054\001\055\001\056\001\
\098\001\255\255\100\001\000\000\102\001\103\001\127\001\255\255\
\255\255\107\001\255\255\255\255\255\255\111\001\135\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\125\001\255\255\127\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\135\001\014\001\255\255\
\255\255\017\001\018\001\019\001\000\000\021\001\022\001\023\001\
\255\255\025\001\255\255\255\255\255\255\029\001\030\001\031\001\
\255\255\255\255\034\001\035\001\036\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\052\001\053\001\054\001\055\001\
\056\001\057\001\058\001\059\001\060\001\061\001\062\001\063\001\
\064\001\065\001\066\001\067\001\068\001\069\001\070\001\071\001\
\072\001\073\001\074\001\075\001\076\001\077\001\078\001\079\001\
\255\255\000\000\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\014\001\014\001\255\255\255\255\018\001\
\018\001\255\255\098\001\255\255\100\001\255\255\102\001\103\001\
\255\255\255\255\255\255\107\001\255\255\255\255\255\255\111\001\
\035\001\036\001\036\001\255\255\255\255\255\255\041\001\041\001\
\255\255\255\255\000\000\255\255\255\255\125\001\255\255\127\001\
\008\001\052\001\052\001\255\255\255\255\255\255\255\255\135\001\
\255\255\255\255\018\001\019\001\255\255\021\001\022\001\023\001\
\024\001\025\001\026\001\027\001\028\001\029\001\030\001\031\001\
\255\255\255\255\034\001\035\001\036\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\052\001\053\001\054\001\055\001\
\056\001\100\001\100\001\255\255\255\255\255\255\255\255\255\255\
\107\001\107\001\044\001\045\001\046\001\047\001\048\001\049\001\
\050\001\051\001\052\001\053\001\054\001\055\001\056\001\255\255\
\000\000\031\001\125\001\125\001\127\001\127\001\255\255\037\001\
\038\001\039\001\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\048\001\049\001\050\001\051\001\052\001\053\001\
\054\001\055\001\056\001\255\255\255\255\255\255\255\255\111\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\000\000\
\255\255\255\255\255\255\008\001\255\255\255\255\255\255\255\255\
\128\001\255\255\255\255\255\255\255\255\018\001\019\001\135\001\
\021\001\022\001\023\001\024\001\025\001\026\001\027\001\028\001\
\029\001\030\001\031\001\255\255\255\255\034\001\035\001\036\001\
\037\001\038\001\039\001\040\001\041\001\042\001\043\001\044\001\
\045\001\046\001\047\001\048\001\049\001\050\001\051\001\052\001\
\053\001\054\001\055\001\056\001\255\255\255\255\018\001\019\001\
\255\255\021\001\022\001\023\001\024\001\025\001\026\001\027\001\
\028\001\029\001\030\001\031\001\255\255\255\255\034\001\035\001\
\036\001\037\001\038\001\039\001\040\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\048\001\049\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\000\000\255\255\255\255\
\255\255\255\255\111\001\255\255\255\255\255\255\255\255\255\255\
\255\255\014\001\255\255\255\255\019\001\018\001\021\001\255\255\
\023\001\022\001\025\001\128\001\255\255\255\255\255\255\255\255\
\031\001\255\255\135\001\034\001\035\001\036\001\037\001\038\001\
\039\001\040\001\255\255\000\000\041\001\255\255\255\255\255\255\
\255\255\255\255\255\255\111\001\255\255\255\255\255\255\052\001\
\255\255\255\255\255\255\255\255\018\001\019\001\255\255\021\001\
\022\001\023\001\024\001\025\001\026\001\027\001\028\001\029\001\
\030\001\031\001\255\255\135\001\034\001\035\001\036\001\037\001\
\038\001\039\001\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\048\001\049\001\050\001\051\001\052\001\053\001\
\054\001\055\001\056\001\255\255\255\255\255\255\255\255\100\001\
\255\255\255\255\255\255\255\255\255\255\255\255\107\001\255\255\
\111\001\042\001\043\001\044\001\045\001\046\001\047\001\048\001\
\049\001\050\001\051\001\052\001\053\001\054\001\055\001\056\001\
\125\001\255\255\127\001\255\255\255\255\255\255\255\255\255\255\
\135\001\255\255\255\255\019\001\255\255\021\001\022\001\023\001\
\255\255\025\001\000\000\255\255\255\255\029\001\030\001\031\001\
\255\255\111\001\034\001\035\001\036\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\052\001\053\001\054\001\055\001\
\056\001\135\001\019\001\255\255\021\001\255\255\023\001\255\255\
\025\001\000\000\255\255\255\255\029\001\030\001\031\001\255\255\
\017\001\034\001\035\001\036\001\037\001\038\001\039\001\040\001\
\041\001\042\001\043\001\044\001\045\001\046\001\047\001\048\001\
\049\001\050\001\051\001\052\001\053\001\054\001\055\001\056\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\000\000\255\255\255\255\255\255\255\255\255\255\255\255\111\001\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\135\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\000\000\
\255\255\255\255\255\255\255\255\255\255\255\255\111\001\255\255\
\255\255\098\001\255\255\255\255\255\255\102\001\103\001\255\255\
\019\001\255\255\021\001\255\255\023\001\255\255\025\001\255\255\
\255\255\255\255\029\001\030\001\031\001\255\255\135\001\034\001\
\035\001\036\001\037\001\038\001\039\001\040\001\041\001\042\001\
\043\001\044\001\045\001\046\001\047\001\048\001\049\001\050\001\
\051\001\052\001\053\001\054\001\055\001\056\001\019\001\255\255\
\021\001\255\255\023\001\255\255\025\001\255\255\255\255\255\255\
\029\001\030\001\031\001\255\255\255\255\034\001\035\001\036\001\
\037\001\038\001\039\001\040\001\041\001\042\001\043\001\044\001\
\045\001\046\001\047\001\048\001\049\001\050\001\051\001\052\001\
\053\001\054\001\055\001\056\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\000\000\255\255\255\255\
\255\255\255\255\255\255\255\255\111\001\001\001\002\001\003\001\
\004\001\005\001\006\001\007\001\008\001\009\001\010\001\011\001\
\012\001\013\001\014\001\015\001\016\001\017\001\018\001\019\001\
\020\001\255\255\255\255\255\255\135\001\000\000\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\111\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\019\001\255\255\021\001\
\255\255\023\001\255\255\025\001\000\000\255\255\255\255\029\001\
\030\001\031\001\135\001\255\255\034\001\035\001\036\001\037\001\
\038\001\039\001\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\048\001\049\001\050\001\051\001\052\001\053\001\
\054\001\055\001\056\001\255\255\019\001\255\255\021\001\255\255\
\023\001\255\255\025\001\255\255\255\255\255\255\255\255\255\255\
\031\001\255\255\255\255\034\001\035\001\036\001\037\001\038\001\
\039\001\040\001\041\001\042\001\043\001\044\001\045\001\046\001\
\047\001\048\001\049\001\050\001\051\001\052\001\053\001\054\001\
\055\001\056\001\255\255\019\001\255\255\021\001\255\255\023\001\
\255\255\025\001\000\000\255\255\255\255\255\255\255\255\031\001\
\255\255\111\001\034\001\035\001\036\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\255\255\255\255\255\255\000\000\
\255\255\135\001\019\001\255\255\021\001\255\255\023\001\255\255\
\025\001\255\255\255\255\255\255\255\255\255\255\031\001\255\255\
\111\001\034\001\035\001\036\001\037\001\038\001\039\001\040\001\
\041\001\042\001\043\001\044\001\045\001\046\001\047\001\048\001\
\049\001\050\001\051\001\255\255\255\255\255\255\255\255\255\255\
\135\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\000\000\255\255\255\255\255\255\255\255\255\255\255\255\111\001\
\038\001\039\001\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\048\001\049\001\050\001\051\001\052\001\053\001\
\054\001\055\001\056\001\255\255\255\255\000\000\255\255\135\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\111\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\000\000\255\255\
\019\001\255\255\021\001\255\255\023\001\255\255\025\001\255\255\
\255\255\255\255\255\255\255\255\031\001\255\255\135\001\034\001\
\035\001\036\001\037\001\038\001\039\001\040\001\041\001\042\001\
\043\001\044\001\045\001\046\001\047\001\048\001\049\001\255\255\
\019\001\255\255\021\001\255\255\023\001\255\255\025\001\255\255\
\255\255\255\255\255\255\255\255\031\001\255\255\255\255\034\001\
\035\001\036\001\037\001\038\001\039\001\040\001\041\001\042\001\
\043\001\044\001\045\001\046\001\047\001\048\001\049\001\019\001\
\255\255\021\001\255\255\023\001\255\255\025\001\255\255\255\255\
\255\255\255\255\255\255\031\001\255\255\255\255\034\001\035\001\
\036\001\037\001\038\001\039\001\040\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\111\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\048\001\049\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\000\000\255\255\255\255\
\255\255\255\255\255\255\255\255\135\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\111\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\019\001\255\255\021\001\
\255\255\023\001\255\255\025\001\135\001\255\255\255\255\255\255\
\255\255\031\001\255\255\111\001\034\001\035\001\036\001\037\001\
\038\001\039\001\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\019\001\255\255\021\001\255\255\023\001\005\000\
\025\001\255\255\255\255\135\001\255\255\255\255\031\001\255\255\
\255\255\034\001\035\001\036\001\037\001\038\001\039\001\040\001\
\041\001\042\001\043\001\044\001\045\001\046\001\047\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\052\001\053\001\054\001\055\001\
\056\001\255\255\255\255\019\001\255\255\021\001\255\255\023\001\
\255\255\025\001\255\255\255\255\255\255\255\255\255\255\031\001\
\255\255\111\001\034\001\035\001\036\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\019\001\255\255\021\001\000\000\023\001\255\255\025\001\255\255\
\255\255\135\001\255\255\255\255\031\001\255\255\111\001\034\001\
\035\001\036\001\037\001\038\001\039\001\040\001\041\001\042\001\
\043\001\019\001\255\255\021\001\255\255\023\001\255\255\025\001\
\255\255\255\255\255\255\255\255\255\255\031\001\135\001\255\255\
\034\001\035\001\036\001\037\001\038\001\039\001\040\001\041\001\
\042\001\043\001\255\255\255\255\255\255\131\000\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\111\001\
\255\255\255\255\255\255\255\255\255\255\255\255\148\000\149\000\
\255\255\255\255\255\255\255\255\000\000\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\135\001\
\255\255\255\255\255\255\255\255\111\001\255\255\255\255\255\255\
\255\255\175\000\040\001\041\001\042\001\043\001\044\001\045\001\
\046\001\047\001\048\001\049\001\050\001\051\001\052\001\053\001\
\054\001\055\001\056\001\193\000\135\001\111\001\255\255\255\255\
\255\255\255\255\005\001\006\001\007\001\008\001\009\001\255\255\
\206\000\255\255\013\001\014\001\255\255\016\001\017\001\018\001\
\255\255\020\001\021\001\255\255\255\255\135\001\255\255\221\000\
\027\001\028\001\000\000\255\255\255\255\032\001\033\001\255\255\
\255\255\036\001\255\255\038\001\255\255\255\255\041\001\255\255\
\255\255\239\000\255\255\255\255\255\255\255\255\255\255\050\001\
\051\001\052\001\255\255\255\255\000\000\255\255\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\069\001\070\001\071\001\072\001\073\001\074\001\
\075\001\076\001\077\001\078\001\079\001\080\001\081\001\255\255\
\083\001\084\001\085\001\086\001\087\001\088\001\089\001\090\001\
\091\001\092\001\093\001\094\001\095\001\255\255\255\255\098\001\
\099\001\156\000\255\255\102\001\103\001\104\001\255\255\255\255\
\107\001\255\255\255\255\255\255\111\001\255\255\113\001\255\255\
\115\001\116\001\117\001\118\001\119\001\120\001\121\001\122\001\
\123\001\124\001\255\255\126\001\127\001\128\001\129\001\255\255\
\131\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\014\001\255\255\016\001\017\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\036\001\
\255\255\119\001\255\255\255\255\255\255\255\255\255\255\242\000\
\255\255\127\001\255\255\255\255\255\255\255\255\255\255\250\000\
\255\255\255\255\255\255\137\001\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\022\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\016\001\017\001\255\255\255\255\
\255\255\255\255\255\255\255\255\097\001\098\001\099\001\255\255\
\255\255\102\001\103\001\104\001\255\255\255\255\255\255\255\255\
\255\255\052\001\255\255\255\255\113\001\255\255\115\001\116\001\
\117\001\118\001\119\001\120\001\121\001\122\001\123\001\124\001\
\255\255\255\255\255\255\255\255\129\001\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\095\001\255\255\255\255\255\255\
\014\001\255\255\255\255\255\255\018\001\019\001\255\255\255\255\
\022\001\255\255\255\255\255\255\255\255\097\001\098\001\114\001\
\255\255\255\255\102\001\103\001\255\255\035\001\036\001\255\255\
\255\255\014\001\014\001\041\001\017\001\018\001\018\001\019\001\
\255\255\255\255\022\001\255\255\255\255\255\255\052\001\255\255\
\255\255\255\255\255\255\255\255\255\255\129\001\255\255\035\001\
\036\001\255\255\255\255\255\255\255\255\041\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\052\001\255\255\255\255\255\255\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\255\255\255\255\255\255\255\255\255\255\255\255\100\001\076\001\
\077\001\078\001\079\001\255\255\255\255\107\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\204\001\205\001\255\255\255\255\255\255\255\255\125\001\
\100\001\127\001\103\001\255\255\255\255\255\255\255\255\107\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\125\001\255\255\127\001\255\255\255\255\005\001\006\001\
\007\001\008\001\009\001\255\255\255\255\255\255\013\001\014\001\
\015\001\255\255\017\001\018\001\019\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\027\001\028\001\255\255\255\255\
\255\255\032\001\033\001\255\255\255\255\016\002\255\255\038\001\
\255\255\020\002\041\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\050\001\051\001\052\001\255\255\255\255\
\255\255\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\069\001\070\001\
\071\001\072\001\073\001\074\001\075\001\076\001\077\001\078\001\
\079\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\093\001\094\001\
\095\001\255\255\255\255\098\001\255\255\100\001\255\255\102\001\
\103\001\255\255\255\255\255\255\107\001\255\255\255\255\005\001\
\006\001\007\001\008\001\009\001\255\255\255\255\255\255\013\001\
\014\001\015\001\255\255\017\001\018\001\019\001\125\001\255\255\
\127\001\128\001\255\255\255\255\255\255\027\001\028\001\255\255\
\255\255\136\001\032\001\033\001\255\255\255\255\255\255\255\255\
\038\001\255\255\255\255\041\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\050\001\051\001\052\001\255\255\
\255\255\255\255\255\255\057\001\058\001\059\001\060\001\061\001\
\062\001\063\001\064\001\065\001\066\001\067\001\068\001\069\001\
\070\001\071\001\072\001\073\001\074\001\075\001\076\001\077\001\
\078\001\079\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\093\001\
\094\001\095\001\255\255\255\255\098\001\255\255\100\001\255\255\
\102\001\103\001\255\255\255\255\255\255\107\001\255\255\255\255\
\005\001\006\001\007\001\008\001\009\001\255\255\255\255\255\255\
\013\001\014\001\015\001\255\255\017\001\018\001\019\001\125\001\
\255\255\127\001\128\001\255\255\255\255\255\255\027\001\028\001\
\255\255\255\255\136\001\032\001\033\001\255\255\255\255\255\255\
\255\255\038\001\255\255\255\255\041\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\050\001\051\001\052\001\
\255\255\255\255\255\255\255\255\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\093\001\094\001\095\001\255\255\255\255\098\001\255\255\100\001\
\255\255\102\001\103\001\255\255\255\255\255\255\107\001\255\255\
\255\255\005\001\006\001\007\001\008\001\009\001\255\255\255\255\
\255\255\013\001\014\001\015\001\255\255\017\001\018\001\019\001\
\125\001\255\255\127\001\128\001\255\255\255\255\255\255\027\001\
\028\001\255\255\255\255\136\001\032\001\033\001\255\255\255\255\
\255\255\255\255\038\001\255\255\255\255\041\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\050\001\051\001\
\052\001\255\255\255\255\255\255\255\255\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\093\001\094\001\095\001\255\255\255\255\098\001\255\255\
\100\001\255\255\102\001\103\001\255\255\255\255\255\255\107\001\
\255\255\255\255\005\001\006\001\007\001\008\001\009\001\255\255\
\255\255\255\255\013\001\014\001\015\001\255\255\017\001\018\001\
\019\001\125\001\255\255\127\001\128\001\255\255\255\255\255\255\
\027\001\028\001\255\255\255\255\136\001\032\001\033\001\255\255\
\255\255\255\255\255\255\038\001\255\255\255\255\041\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\050\001\
\051\001\052\001\255\255\255\255\255\255\255\255\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\069\001\070\001\071\001\072\001\073\001\074\001\
\075\001\076\001\077\001\078\001\079\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\093\001\094\001\095\001\255\255\255\255\098\001\
\255\255\100\001\255\255\102\001\103\001\255\255\255\255\255\255\
\107\001\255\255\255\255\005\001\006\001\007\001\008\001\009\001\
\255\255\255\255\255\255\013\001\014\001\015\001\255\255\017\001\
\018\001\255\255\125\001\255\255\127\001\128\001\255\255\255\255\
\255\255\027\001\028\001\255\255\255\255\136\001\032\001\033\001\
\255\255\255\255\255\255\255\255\038\001\255\255\255\255\041\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\050\001\051\001\052\001\255\255\255\255\255\255\255\255\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\093\001\094\001\095\001\255\255\255\255\
\098\001\255\255\100\001\255\255\102\001\103\001\255\255\255\255\
\255\255\107\001\255\255\255\255\005\001\006\001\007\001\008\001\
\009\001\255\255\255\255\255\255\013\001\014\001\015\001\255\255\
\017\001\018\001\255\255\125\001\255\255\127\001\128\001\255\255\
\255\255\255\255\027\001\028\001\255\255\255\255\136\001\032\001\
\033\001\255\255\255\255\255\255\255\255\038\001\255\255\255\255\
\041\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\050\001\051\001\052\001\255\255\255\255\255\255\255\255\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\093\001\094\001\095\001\255\255\
\255\255\098\001\255\255\100\001\255\255\102\001\103\001\255\255\
\255\255\255\255\107\001\255\255\255\255\255\255\005\001\006\001\
\007\001\008\001\009\001\255\255\255\255\255\255\013\001\014\001\
\255\255\016\001\017\001\018\001\125\001\020\001\127\001\128\001\
\255\255\255\255\255\255\255\255\027\001\028\001\255\255\136\001\
\255\255\032\001\033\001\255\255\255\255\036\001\255\255\038\001\
\255\255\255\255\041\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\050\001\051\001\052\001\255\255\255\255\
\255\255\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\069\001\070\001\
\071\001\072\001\073\001\074\001\075\001\076\001\077\001\078\001\
\079\001\080\001\081\001\255\255\083\001\084\001\085\001\086\001\
\087\001\088\001\089\001\090\001\091\001\092\001\093\001\094\001\
\095\001\255\255\255\255\098\001\099\001\255\255\255\255\102\001\
\103\001\104\001\255\255\255\255\107\001\108\001\109\001\255\255\
\255\255\255\255\113\001\255\255\115\001\116\001\117\001\118\001\
\119\001\120\001\121\001\122\001\123\001\124\001\125\001\126\001\
\127\001\128\001\129\001\255\255\131\001\005\001\006\001\007\001\
\008\001\009\001\255\255\255\255\255\255\013\001\014\001\255\255\
\016\001\017\001\018\001\255\255\020\001\255\255\255\255\255\255\
\255\255\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\036\001\255\255\038\001\255\255\
\255\255\041\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\050\001\051\001\052\001\255\255\255\255\255\255\
\255\255\057\001\058\001\059\001\060\001\061\001\062\001\063\001\
\064\001\065\001\066\001\067\001\068\001\069\001\070\001\071\001\
\072\001\073\001\074\001\075\001\076\001\077\001\078\001\079\001\
\080\001\081\001\255\255\083\001\084\001\085\001\086\001\087\001\
\088\001\089\001\090\001\091\001\092\001\093\001\094\001\095\001\
\255\255\255\255\098\001\099\001\255\255\255\255\102\001\103\001\
\104\001\255\255\255\255\107\001\255\255\109\001\255\255\255\255\
\255\255\113\001\255\255\115\001\116\001\117\001\118\001\119\001\
\120\001\121\001\122\001\123\001\124\001\125\001\126\001\127\001\
\128\001\129\001\255\255\131\001\005\001\006\001\007\001\008\001\
\009\001\255\255\255\255\255\255\013\001\014\001\255\255\016\001\
\017\001\018\001\255\255\020\001\255\255\255\255\255\255\255\255\
\255\255\255\255\027\001\028\001\255\255\255\255\255\255\032\001\
\033\001\255\255\255\255\036\001\255\255\038\001\255\255\255\255\
\041\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\050\001\051\001\052\001\255\255\255\255\255\255\255\255\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\080\001\
\081\001\255\255\083\001\084\001\085\001\086\001\087\001\088\001\
\089\001\090\001\091\001\092\001\093\001\094\001\095\001\255\255\
\255\255\098\001\099\001\255\255\255\255\102\001\103\001\104\001\
\255\255\255\255\107\001\255\255\255\255\255\255\111\001\255\255\
\113\001\255\255\115\001\116\001\117\001\118\001\119\001\120\001\
\121\001\122\001\123\001\124\001\255\255\126\001\127\001\128\001\
\129\001\255\255\131\001\005\001\006\001\007\001\008\001\009\001\
\255\255\255\255\255\255\013\001\014\001\255\255\016\001\017\001\
\018\001\255\255\020\001\255\255\255\255\255\255\255\255\255\255\
\255\255\027\001\028\001\255\255\255\255\255\255\032\001\033\001\
\255\255\255\255\036\001\255\255\038\001\255\255\255\255\041\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\050\001\051\001\052\001\255\255\255\255\255\255\255\255\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\080\001\081\001\
\255\255\083\001\084\001\085\001\086\001\087\001\088\001\089\001\
\090\001\091\001\092\001\093\001\094\001\095\001\255\255\255\255\
\098\001\099\001\255\255\255\255\102\001\103\001\104\001\255\255\
\255\255\107\001\255\255\255\255\255\255\111\001\255\255\113\001\
\255\255\115\001\116\001\117\001\118\001\119\001\120\001\121\001\
\122\001\123\001\124\001\255\255\126\001\127\001\128\001\129\001\
\255\255\131\001\005\001\006\001\007\001\008\001\009\001\255\255\
\255\255\255\255\013\001\014\001\255\255\016\001\017\001\018\001\
\255\255\020\001\255\255\255\255\255\255\255\255\255\255\255\255\
\027\001\028\001\255\255\255\255\255\255\032\001\033\001\255\255\
\255\255\036\001\255\255\038\001\255\255\255\255\041\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\050\001\
\051\001\052\001\255\255\255\255\255\255\255\255\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\069\001\070\001\071\001\072\001\073\001\074\001\
\075\001\076\001\077\001\078\001\079\001\080\001\081\001\255\255\
\083\001\084\001\085\001\086\001\087\001\088\001\089\001\090\001\
\091\001\092\001\093\001\094\001\095\001\255\255\255\255\098\001\
\099\001\255\255\255\255\102\001\103\001\104\001\255\255\255\255\
\107\001\255\255\255\255\255\255\111\001\255\255\113\001\255\255\
\115\001\116\001\117\001\118\001\119\001\120\001\121\001\122\001\
\123\001\124\001\255\255\126\001\127\001\128\001\129\001\255\255\
\131\001\005\001\006\001\007\001\008\001\009\001\255\255\255\255\
\255\255\013\001\014\001\255\255\016\001\017\001\018\001\255\255\
\020\001\255\255\255\255\255\255\255\255\255\255\255\255\027\001\
\028\001\255\255\255\255\255\255\032\001\033\001\255\255\255\255\
\036\001\255\255\038\001\255\255\255\255\041\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\050\001\051\001\
\052\001\255\255\255\255\255\255\255\255\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\080\001\081\001\255\255\083\001\
\084\001\085\001\086\001\087\001\088\001\089\001\090\001\091\001\
\092\001\093\001\094\001\095\001\255\255\255\255\098\001\099\001\
\255\255\255\255\102\001\103\001\104\001\255\255\255\255\107\001\
\255\255\255\255\255\255\255\255\255\255\113\001\255\255\115\001\
\116\001\117\001\118\001\119\001\120\001\121\001\122\001\123\001\
\124\001\255\255\126\001\127\001\128\001\129\001\255\255\131\001\
\005\001\006\001\007\001\008\001\009\001\255\255\255\255\255\255\
\013\001\014\001\255\255\255\255\017\001\018\001\255\255\020\001\
\255\255\255\255\255\255\255\255\255\255\255\255\027\001\028\001\
\255\255\255\255\255\255\032\001\033\001\255\255\255\255\036\001\
\255\255\038\001\255\255\255\255\041\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\050\001\051\001\052\001\
\255\255\255\255\255\255\255\255\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\080\001\081\001\255\255\083\001\084\001\
\085\001\086\001\087\001\088\001\089\001\090\001\091\001\092\001\
\093\001\094\001\095\001\255\255\255\255\098\001\099\001\255\255\
\255\255\102\001\103\001\255\255\255\255\255\255\107\001\255\255\
\255\255\005\001\006\001\007\001\008\001\009\001\255\255\255\255\
\014\001\013\001\014\001\017\001\255\255\017\001\018\001\255\255\
\020\001\126\001\127\001\128\001\129\001\255\255\131\001\027\001\
\028\001\255\255\255\255\255\255\032\001\033\001\255\255\255\255\
\036\001\255\255\038\001\255\255\255\255\041\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\050\001\051\001\
\052\001\255\255\255\255\057\001\058\001\059\001\060\001\061\001\
\062\001\063\001\064\001\065\001\066\001\067\001\068\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\076\001\077\001\
\078\001\079\001\255\255\255\255\080\001\081\001\255\255\083\001\
\084\001\085\001\086\001\087\001\088\001\089\001\090\001\091\001\
\092\001\093\001\094\001\095\001\255\255\255\255\255\255\099\001\
\255\255\103\001\005\001\006\001\007\001\008\001\009\001\107\001\
\255\255\255\255\013\001\014\001\255\255\255\255\017\001\018\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\027\001\028\001\126\001\127\001\128\001\032\001\033\001\131\001\
\255\255\036\001\255\255\038\001\255\255\255\255\041\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\050\001\
\051\001\052\001\255\255\255\255\255\255\255\255\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\069\001\070\001\071\001\072\001\073\001\074\001\
\075\001\076\001\077\001\078\001\079\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\005\001\006\001\007\001\
\008\001\009\001\093\001\094\001\095\001\013\001\014\001\098\001\
\255\255\017\001\018\001\102\001\103\001\255\255\255\255\255\255\
\107\001\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\255\255\255\255\038\001\255\255\
\255\255\041\001\255\255\255\255\127\001\128\001\129\001\255\255\
\255\255\255\255\050\001\051\001\052\001\255\255\255\255\255\255\
\255\255\057\001\058\001\059\001\060\001\061\001\062\001\063\001\
\064\001\065\001\066\001\067\001\068\001\255\255\255\255\255\255\
\255\255\255\255\074\001\075\001\076\001\077\001\078\001\079\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\093\001\094\001\095\001\
\255\255\255\255\098\001\255\255\255\255\255\255\255\255\103\001\
\255\255\255\255\255\255\107\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\005\001\006\001\007\001\
\008\001\009\001\255\255\255\255\255\255\013\001\014\001\127\001\
\128\001\017\001\018\001\255\255\020\001\021\001\022\001\255\255\
\024\001\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\255\255\255\255\038\001\255\255\
\255\255\041\001\255\255\255\255\255\255\005\001\006\001\007\001\
\008\001\009\001\050\001\051\001\052\001\013\001\014\001\255\255\
\255\255\017\001\018\001\255\255\020\001\021\001\022\001\255\255\
\024\001\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\255\255\255\255\038\001\255\255\
\255\255\041\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\050\001\051\001\052\001\093\001\094\001\095\001\
\005\001\006\001\007\001\008\001\009\001\255\255\255\255\255\255\
\013\001\014\001\255\255\107\001\017\001\018\001\255\255\020\001\
\255\255\022\001\255\255\024\001\255\255\255\255\027\001\028\001\
\255\255\255\255\255\255\032\001\033\001\255\255\255\255\127\001\
\128\001\038\001\255\255\255\255\041\001\093\001\094\001\095\001\
\005\001\006\001\007\001\008\001\009\001\050\001\051\001\052\001\
\013\001\014\001\255\255\107\001\255\255\018\001\255\255\020\001\
\255\255\255\255\255\255\255\255\255\255\255\255\027\001\028\001\
\255\255\255\255\255\255\032\001\033\001\255\255\255\255\127\001\
\128\001\038\001\255\255\255\255\041\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\050\001\051\001\052\001\
\093\001\094\001\095\001\005\001\006\001\007\001\008\001\009\001\
\255\255\255\255\255\255\013\001\014\001\255\255\107\001\255\255\
\018\001\255\255\255\255\255\255\255\255\023\001\255\255\255\255\
\255\255\027\001\028\001\255\255\255\255\255\255\032\001\033\001\
\255\255\255\255\127\001\128\001\038\001\255\255\255\255\041\001\
\093\001\094\001\095\001\005\001\006\001\007\001\008\001\009\001\
\050\001\051\001\052\001\013\001\014\001\255\255\107\001\255\255\
\018\001\255\255\255\255\255\255\255\255\023\001\255\255\255\255\
\255\255\027\001\028\001\255\255\255\255\255\255\032\001\033\001\
\255\255\255\255\127\001\128\001\038\001\255\255\255\255\041\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\050\001\051\001\052\001\093\001\094\001\095\001\005\001\006\001\
\007\001\008\001\009\001\255\255\255\255\255\255\013\001\014\001\
\255\255\107\001\255\255\018\001\255\255\020\001\255\255\255\255\
\255\255\255\255\255\255\255\255\027\001\028\001\255\255\255\255\
\255\255\032\001\033\001\255\255\255\255\127\001\128\001\038\001\
\255\255\255\255\041\001\093\001\094\001\095\001\255\255\255\255\
\255\255\255\255\255\255\050\001\051\001\052\001\255\255\255\255\
\255\255\107\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\127\001\128\001\005\001\
\006\001\007\001\008\001\009\001\255\255\255\255\255\255\013\001\
\014\001\255\255\255\255\255\255\018\001\255\255\093\001\094\001\
\095\001\255\255\255\255\255\255\255\255\027\001\028\001\255\255\
\255\255\255\255\032\001\033\001\107\001\255\255\036\001\255\255\
\038\001\255\255\255\255\041\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\050\001\051\001\052\001\255\255\
\127\001\128\001\005\001\006\001\007\001\008\001\009\001\255\255\
\255\255\255\255\013\001\014\001\255\255\255\255\255\255\018\001\
\255\255\020\001\255\255\255\255\255\255\255\255\255\255\255\255\
\027\001\028\001\255\255\255\255\255\255\032\001\033\001\255\255\
\255\255\255\255\255\255\038\001\255\255\255\255\041\001\093\001\
\094\001\095\001\005\001\006\001\007\001\008\001\009\001\050\001\
\051\001\052\001\013\001\014\001\255\255\107\001\255\255\018\001\
\255\255\255\255\255\255\255\255\023\001\255\255\255\255\255\255\
\027\001\028\001\255\255\255\255\255\255\032\001\033\001\255\255\
\255\255\127\001\128\001\038\001\255\255\255\255\041\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\050\001\
\051\001\052\001\093\001\094\001\095\001\005\001\006\001\007\001\
\008\001\009\001\255\255\255\255\255\255\013\001\014\001\255\255\
\107\001\255\255\018\001\019\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\127\001\128\001\038\001\255\255\
\255\255\041\001\093\001\094\001\095\001\005\001\006\001\007\001\
\008\001\009\001\050\001\051\001\052\001\013\001\014\001\255\255\
\107\001\255\255\018\001\019\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\027\001\028\001\255\255\255\255\255\255\
\032\001\033\001\255\255\255\255\127\001\128\001\038\001\255\255\
\255\255\041\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\050\001\051\001\052\001\093\001\094\001\095\001\
\005\001\006\001\007\001\008\001\009\001\255\255\255\255\255\255\
\013\001\014\001\255\255\107\001\255\255\018\001\255\255\255\255\
\255\255\255\255\017\001\255\255\255\255\255\255\027\001\028\001\
\255\255\255\255\255\255\032\001\033\001\255\255\255\255\127\001\
\128\001\038\001\255\255\255\255\041\001\093\001\094\001\095\001\
\255\255\255\255\255\255\255\255\255\255\050\001\051\001\052\001\
\255\255\255\255\255\255\107\001\255\255\255\255\255\255\255\255\
\255\255\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\255\255\127\001\
\128\001\255\255\255\255\074\001\075\001\076\001\077\001\078\001\
\079\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\093\001\094\001\095\001\255\255\014\001\015\001\255\255\017\001\
\018\001\019\001\020\001\098\001\022\001\255\255\107\001\025\001\
\103\001\255\255\255\255\255\255\030\001\255\255\255\255\255\255\
\255\255\035\001\036\001\255\255\255\255\255\255\255\255\041\001\
\255\255\255\255\127\001\128\001\255\255\255\255\255\255\255\255\
\255\255\255\255\052\001\255\255\255\255\255\255\255\255\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\096\001\255\255\
\098\001\255\255\255\255\255\255\102\001\103\001\104\001\255\255\
\014\001\107\001\255\255\017\001\018\001\019\001\255\255\113\001\
\022\001\255\255\255\255\025\001\255\255\255\255\255\255\255\255\
\122\001\123\001\124\001\255\255\255\255\127\001\036\001\129\001\
\255\255\255\255\255\255\041\001\255\255\135\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\052\001\255\255\
\255\255\255\255\255\255\057\001\058\001\059\001\060\001\061\001\
\062\001\063\001\064\001\065\001\066\001\067\001\068\001\069\001\
\070\001\071\001\072\001\073\001\074\001\075\001\076\001\077\001\
\078\001\079\001\255\255\255\255\255\255\255\255\255\255\255\255\
\014\001\255\255\255\255\255\255\018\001\019\001\255\255\255\255\
\022\001\255\255\255\255\025\001\098\001\255\255\100\001\014\001\
\102\001\103\001\017\001\018\001\019\001\107\001\036\001\022\001\
\255\255\111\001\025\001\041\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\036\001\052\001\125\001\
\255\255\127\001\041\001\255\255\255\255\255\255\255\255\255\255\
\255\255\135\001\255\255\255\255\255\255\052\001\255\255\255\255\
\255\255\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\069\001\070\001\
\071\001\072\001\073\001\074\001\075\001\076\001\077\001\078\001\
\079\001\255\255\255\255\255\255\255\255\255\255\100\001\014\001\
\255\255\255\255\255\255\018\001\019\001\107\001\255\255\022\001\
\255\255\111\001\025\001\098\001\255\255\100\001\255\255\102\001\
\103\001\255\255\255\255\255\255\107\001\036\001\255\255\125\001\
\111\001\127\001\041\001\255\255\255\255\255\255\255\255\014\001\
\255\255\135\001\255\255\018\001\019\001\052\001\125\001\022\001\
\127\001\255\255\025\001\255\255\255\255\255\255\014\001\255\255\
\135\001\255\255\018\001\019\001\255\255\036\001\022\001\255\255\
\255\255\025\001\041\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\036\001\052\001\255\255\255\255\
\255\255\041\001\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\052\001\100\001\255\255\255\255\
\255\255\255\255\255\255\255\255\107\001\255\255\255\255\255\255\
\111\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\125\001\255\255\
\127\001\255\255\255\255\255\255\255\255\100\001\255\255\255\255\
\135\001\255\255\255\255\255\255\107\001\255\255\255\255\255\255\
\111\001\255\255\255\255\255\255\100\001\255\255\255\255\255\255\
\255\255\255\255\255\255\107\001\255\255\255\255\125\001\111\001\
\127\001\017\001\255\255\019\001\020\001\255\255\255\255\255\255\
\135\001\025\001\255\255\255\255\255\255\125\001\030\001\127\001\
\255\255\255\255\255\255\035\001\036\001\255\255\255\255\135\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\057\001\058\001\059\001\060\001\061\001\062\001\063\001\
\064\001\065\001\066\001\067\001\068\001\069\001\070\001\071\001\
\072\001\073\001\074\001\075\001\076\001\077\001\078\001\079\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\096\001\255\255\098\001\099\001\100\001\255\255\102\001\103\001\
\104\001\255\255\255\255\255\255\017\001\255\255\019\001\020\001\
\255\255\113\001\255\255\255\255\025\001\255\255\255\255\255\255\
\255\255\030\001\122\001\123\001\124\001\125\001\035\001\036\001\
\255\255\129\001\255\255\255\255\255\255\255\255\255\255\135\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\096\001\255\255\098\001\099\001\100\001\
\255\255\102\001\103\001\104\001\255\255\014\001\255\255\255\255\
\017\001\018\001\255\255\255\255\113\001\022\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\122\001\123\001\124\001\
\125\001\255\255\255\255\036\001\129\001\255\255\255\255\255\255\
\041\001\255\255\135\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\052\001\255\255\255\255\255\255\255\255\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\069\001\070\001\071\001\072\001\
\073\001\074\001\075\001\076\001\077\001\078\001\079\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\014\001\255\255\255\255\017\001\018\001\255\255\
\255\255\098\001\022\001\100\001\255\255\102\001\103\001\255\255\
\255\255\255\255\107\001\255\255\255\255\255\255\111\001\035\001\
\036\001\255\255\255\255\255\255\255\255\041\001\255\255\255\255\
\255\255\255\255\255\255\255\255\125\001\255\255\127\001\255\255\
\052\001\255\255\255\255\132\001\255\255\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\016\001\017\001\255\255\255\255\255\255\
\021\001\255\255\255\255\255\255\255\255\255\255\098\001\255\255\
\100\001\255\255\102\001\103\001\255\255\255\255\255\255\107\001\
\255\255\255\255\255\255\111\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\125\001\255\255\127\001\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\016\001\017\001\255\255\255\255\
\255\255\021\001\255\255\255\255\097\001\098\001\255\255\255\255\
\255\255\102\001\103\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\129\001\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\017\001\
\255\255\255\255\020\001\255\255\255\255\097\001\098\001\025\001\
\255\255\255\255\102\001\103\001\030\001\255\255\255\255\255\255\
\255\255\255\255\036\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\129\001\255\255\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\017\001\255\255\255\255\020\001\096\001\255\255\
\098\001\255\255\025\001\255\255\102\001\103\001\104\001\030\001\
\255\255\255\255\255\255\255\255\255\255\036\001\255\255\113\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\122\001\123\001\124\001\255\255\255\255\255\255\255\255\129\001\
\255\255\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\069\001\070\001\
\071\001\072\001\073\001\074\001\075\001\076\001\077\001\078\001\
\079\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\017\001\255\255\255\255\
\020\001\096\001\255\255\098\001\255\255\025\001\255\255\102\001\
\103\001\104\001\030\001\255\255\255\255\255\255\255\255\255\255\
\036\001\255\255\113\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\122\001\123\001\124\001\255\255\255\255\
\255\255\255\255\129\001\255\255\255\255\057\001\058\001\059\001\
\060\001\061\001\062\001\063\001\064\001\065\001\066\001\067\001\
\068\001\069\001\070\001\071\001\072\001\073\001\074\001\075\001\
\076\001\077\001\078\001\079\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\017\001\255\255\
\255\255\020\001\255\255\255\255\096\001\255\255\098\001\255\255\
\255\255\255\255\102\001\103\001\104\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\113\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\122\001\123\001\
\124\001\255\255\255\255\255\255\255\255\129\001\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\069\001\070\001\071\001\072\001\073\001\074\001\
\075\001\076\001\077\001\078\001\079\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\017\001\
\255\255\255\255\020\001\255\255\255\255\255\255\255\255\098\001\
\255\255\255\255\255\255\102\001\103\001\104\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\113\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\122\001\
\123\001\124\001\255\255\255\255\255\255\255\255\129\001\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\014\001\255\255\255\255\
\017\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\098\001\255\255\255\255\255\255\102\001\103\001\255\255\255\255\
\255\255\255\255\255\255\036\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\129\001\
\057\001\058\001\059\001\060\001\061\001\062\001\063\001\064\001\
\065\001\066\001\067\001\068\001\255\255\255\255\255\255\255\255\
\255\255\074\001\075\001\076\001\077\001\078\001\079\001\255\255\
\255\255\255\255\015\001\255\255\017\001\255\255\019\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\098\001\255\255\255\255\255\255\255\255\103\001\104\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\113\001\255\255\115\001\116\001\117\001\118\001\119\001\120\001\
\121\001\122\001\123\001\124\001\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\255\255\255\255\255\255\255\255\255\255\
\015\001\255\255\017\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\098\001\255\255\100\001\
\255\255\102\001\103\001\034\001\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\125\001\255\255\057\001\058\001\059\001\060\001\061\001\062\001\
\063\001\064\001\065\001\066\001\067\001\068\001\069\001\070\001\
\071\001\072\001\073\001\074\001\075\001\076\001\077\001\078\001\
\079\001\255\255\255\255\255\255\255\255\015\001\255\255\017\001\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\098\001\255\255\100\001\255\255\102\001\
\103\001\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\125\001\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\255\255\255\255\
\255\255\255\255\015\001\255\255\017\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\098\001\255\255\100\001\255\255\102\001\103\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\125\001\057\001\058\001\059\001\060\001\
\061\001\062\001\063\001\064\001\065\001\066\001\067\001\068\001\
\069\001\070\001\071\001\072\001\073\001\074\001\075\001\076\001\
\077\001\078\001\079\001\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\098\001\255\255\100\001\
\255\255\102\001\103\001\255\255\255\255\255\255\255\255\255\255\
\018\001\255\255\255\255\255\255\022\001\255\255\024\001\025\001\
\026\001\027\001\028\001\029\001\030\001\031\001\255\255\255\255\
\125\001\035\001\036\001\037\001\038\001\039\001\040\001\041\001\
\042\001\043\001\044\001\045\001\046\001\047\001\048\001\049\001\
\050\001\051\001\052\001\053\001\054\001\055\001\056\001\018\001\
\255\255\255\255\255\255\022\001\255\255\024\001\025\001\026\001\
\027\001\028\001\029\001\030\001\031\001\015\001\255\255\017\001\
\035\001\036\001\037\001\038\001\039\001\040\001\041\001\042\001\
\043\001\044\001\045\001\046\001\047\001\048\001\049\001\050\001\
\051\001\052\001\053\001\054\001\055\001\056\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\111\001\255\255\057\001\
\058\001\059\001\060\001\061\001\062\001\063\001\064\001\065\001\
\066\001\067\001\068\001\069\001\070\001\071\001\072\001\073\001\
\074\001\075\001\076\001\077\001\078\001\079\001\017\001\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\111\001\255\255\255\255\255\255\
\098\001\255\255\255\255\255\255\102\001\103\001\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\057\001\058\001\
\059\001\060\001\061\001\062\001\063\001\064\001\065\001\066\001\
\067\001\068\001\255\255\255\255\255\255\255\255\255\255\074\001\
\075\001\076\001\077\001\078\001\079\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\098\001\
\255\255\255\255\014\001\255\255\103\001\017\001\018\001\019\001\
\020\001\021\001\255\255\255\255\255\255\025\001\255\255\027\001\
\028\001\029\001\030\001\031\001\255\255\033\001\255\255\035\001\
\036\001\037\001\038\001\039\001\040\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\048\001\049\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\014\001\255\255\255\255\017\001\018\001\019\001\
\020\001\021\001\255\255\255\255\255\255\025\001\082\001\027\001\
\028\001\029\001\030\001\031\001\088\001\033\001\255\255\035\001\
\036\001\037\001\038\001\039\001\040\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\048\001\049\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\014\001\255\255\255\255\017\001\018\001\019\001\
\020\001\021\001\255\255\255\255\255\255\025\001\082\001\027\001\
\028\001\029\001\030\001\031\001\088\001\033\001\255\255\035\001\
\255\255\037\001\038\001\039\001\040\001\041\001\042\001\043\001\
\044\001\045\001\046\001\047\001\048\001\049\001\050\001\051\001\
\052\001\053\001\054\001\055\001\056\001\255\255\255\255\255\255\
\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\255\
\255\255\255\255\018\001\255\255\255\255\021\001\022\001\255\255\
\024\001\025\001\026\001\027\001\028\001\255\255\082\001\031\001\
\255\255\255\255\255\255\035\001\088\001\037\001\038\001\039\001\
\040\001\041\001\042\001\043\001\044\001\045\001\046\001\047\001\
\048\001\049\001\050\001\051\001\052\001\053\001\054\001\055\001\
\056\001"

let yynames_const = "\
  "

let yynames_block = "\
  TUnknown\000\
  TCommentSpace\000\
  TCommentNewline\000\
  TComment\000\
  TInt\000\
  TFloat\000\
  TChar\000\
  TString\000\
  TQuote\000\
  TPct\000\
  TFormat\000\
  TSubString\000\
  TDecimal\000\
  TIdent\000\
  TKRParam\000\
  Tconstructorname\000\
  TypedefIdent\000\
  TOPar\000\
  TCPar\000\
  TOBrace\000\
  TCBrace\000\
  TOCro\000\
  TCCro\000\
  TDot\000\
  TComma\000\
  TPtrOp\000\
  TInc\000\
  TDec\000\
  TAssign\000\
  TEq\000\
  TWhy\000\
  TTilde\000\
  TBang\000\
  TEllipsis\000\
  TDotDot\000\
  TPtVirg\000\
  TOrLog\000\
  TAndLog\000\
  TOr\000\
  TXor\000\
  TAnd\000\
  TEqEq\000\
  TNotEq\000\
  TInf\000\
  TSup\000\
  TInfEq\000\
  TSupEq\000\
  TShl\000\
  TShr\000\
  TPlus\000\
  TMinus\000\
  TMul\000\
  TDiv\000\
  TMod\000\
  TMax\000\
  TMin\000\
  Tchar\000\
  Tshort\000\
  Tint\000\
  Tdouble\000\
  Tfloat\000\
  Tlong\000\
  Tunsigned\000\
  Tsigned\000\
  Tvoid\000\
  Tsize_t\000\
  Tssize_t\000\
  Tptrdiff_t\000\
  Tauto\000\
  Tregister\000\
  Textern\000\
  Tstatic\000\
  Ttypedef\000\
  Tconst\000\
  Tvolatile\000\
  Tstruct\000\
  Tunion\000\
  Tenum\000\
  Tdecimal\000\
  Texec\000\
  Tbreak\000\
  Telse\000\
  Tswitch\000\
  Tcase\000\
  Tcontinue\000\
  Tfor\000\
  Tdo\000\
  Tif\000\
  Twhile\000\
  Treturn\000\
  Tgoto\000\
  Tdefault\000\
  Tsizeof\000\
  Tnew\000\
  Tdelete\000\
  TOParCplusplusInit\000\
  Tnamespace\000\
  Trestrict\000\
  Tasm\000\
  Tattribute\000\
  TattributeNoarg\000\
  Tinline\000\
  Ttypeof\000\
  TDefine\000\
  TDefParamVariadic\000\
  TCppEscapedNewline\000\
  TCppConcatOp\000\
  TOParDefine\000\
  TOBraceDefineInit\000\
  TIdentDefine\000\
  TDefEOL\000\
  TInclude\000\
  TIncludeStart\000\
  TIncludeFilename\000\
  TIfdef\000\
  TIfdefelse\000\
  TIfdefelif\000\
  TEndif\000\
  TIfdefBool\000\
  TIfdefMisc\000\
  TIfdefVersion\000\
  TUndef\000\
  TPragma\000\
  TCppDirectiveOther\000\
  TMacroAttr\000\
  TMacroStmt\000\
  TMacroIdentBuilder\000\
  TMacroString\000\
  TMacroDecl\000\
  TMacroDeclConst\000\
  TMacroIterator\000\
  TMacroAttrStorage\000\
  TCommentSkipTagStart\000\
  TCommentSkipTagEnd\000\
  TCParEOL\000\
  TAction\000\
  TCommentMisc\000\
  TCommentCpp\000\
  EOF\000\
  "

let yyact = [|
  (fun _ -> failwith "parser")
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'translation_unit) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 624 "parser_c.mly"
                          ( _1 )
# 3212 "parser_c.ml"
               : Ast_c.program))
; (fun __caml_parser_env ->
    Obj.repr(
# 628 "parser_c.mly"
     ( [] )
# 3218 "parser_c.ml"
               : 'translation_unit))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'translation_unit) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'external_declaration) in
    Obj.repr(
# 630 "parser_c.mly"
     ( !LP._lexer_hint.context_stack <- [LP.InTopLevel]; _1 ++ [_2] )
# 3226 "parser_c.ml"
               : 'translation_unit))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : 'translation_unit) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : string * Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : 'translation_unit) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 632 "parser_c.mly"
     ( !LP._lexer_hint.context_stack <- [LP.InTopLevel]; 
       _1 ++ [Namespace (_5, [_2; snd _3; _4; _6])] )
# 3239 "parser_c.ml"
               : 'translation_unit))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 645 "parser_c.mly"
                ( _1 )
# 3246 "parser_c.ml"
               : 'ident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 646 "parser_c.mly"
                ( _1 )
# 3253 "parser_c.ml"
               : 'ident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 650 "parser_c.mly"
                ( _1 )
# 3260 "parser_c.ml"
               : 'identifier))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 659 "parser_c.mly"
     ( RegularName (mk_string_wrap _1) )
# 3267 "parser_c.ml"
               : 'identifier_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ident_extra_cpp) in
    Obj.repr(
# 660 "parser_c.mly"
                   ( _1 )
# 3274 "parser_c.ml"
               : 'identifier_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 664 "parser_c.mly"
     ( RegularName (mk_string_wrap _1) )
# 3281 "parser_c.ml"
               : 'ident_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 666 "parser_c.mly"
     ( RegularName (mk_string_wrap _1) )
# 3288 "parser_c.ml"
               : 'ident_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ident_extra_cpp) in
    Obj.repr(
# 667 "parser_c.mly"
                   ( _1 )
# 3295 "parser_c.ml"
               : 'ident_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'identifier_cpp_list) in
    Obj.repr(
# 671 "parser_c.mly"
     (
       CppConcatenatedName (
         match _3 with
         | [] -> raise (Impossible 87)
         | (x,concatnull)::xs ->
             assert(null concatnull);
             (mk_string_wrap _1, [])::(x,[_2])::xs
       )
   )
# 3312 "parser_c.ml"
               : 'ident_extra_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 681 "parser_c.mly"
     ( CppVariadicName (fst _2, [_1; snd _2]) )
# 3320 "parser_c.ml"
               : 'ident_extra_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : (string * Ast_c.info)) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'param_define_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 683 "parser_c.mly"
     ( CppIdentBuilder ((fst _1, [snd _1;_2;_4]), _3) )
# 3330 "parser_c.ml"
               : 'ident_extra_cpp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 686 "parser_c.mly"
          ( [mk_string_wrap _1, []] )
# 3337 "parser_c.ml"
               : 'identifier_cpp_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'identifier_cpp_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 687 "parser_c.mly"
                                           ( _1 ++ [mk_string_wrap _3, [_2]] )
# 3346 "parser_c.ml"
               : 'identifier_cpp_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 694 "parser_c.mly"
                           ( _1 )
# 3353 "parser_c.ml"
               : Ast_c.expression))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 695 "parser_c.mly"
                           ( mk_e (Sequence (_1,_3)) [_2] )
# 3362 "parser_c.ml"
               : Ast_c.expression))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cond_expr) in
    Obj.repr(
# 701 "parser_c.mly"
                                 ( _1 )
# 3369 "parser_c.ml"
               : 'assign_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'cast_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.assignOp * Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 702 "parser_c.mly"
                                 ( mk_e(Assignment (_1,fst _2,_3)) [snd _2])
# 3378 "parser_c.ml"
               : 'assign_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'cast_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 703 "parser_c.mly"
                                 ( mk_e(Assignment (_1,SimpleAssign,_3)) [_2])
# 3387 "parser_c.ml"
               : 'assign_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 711 "parser_c.mly"
     ( _1 )
# 3394 "parser_c.ml"
               : 'cond_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'gcc_opt_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 713 "parser_c.mly"
     ( mk_e (CondExpr (_1,_3,_5)) [_2;_4] )
# 3405 "parser_c.ml"
               : 'cond_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cast_expr) in
    Obj.repr(
# 717 "parser_c.mly"
                                 ( _1 )
# 3412 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 718 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Mul,      _3)) [_2] )
# 3421 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 719 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Div,      _3)) [_2] )
# 3430 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 720 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Min,      _3)) [_2] )
# 3439 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 721 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Max,      _3)) [_2] )
# 3448 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 722 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Mod,      _3)) [_2] )
# 3457 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 723 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Plus,     _3)) [_2] )
# 3466 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 724 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Minus,    _3)) [_2] )
# 3475 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 725 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith DecLeft,  _3)) [_2] )
# 3484 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 726 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith DecRight, _3)) [_2] )
# 3493 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 727 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical Inf,    _3)) [_2] )
# 3502 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 728 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical Sup,    _3)) [_2] )
# 3511 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 729 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical InfEq,  _3)) [_2] )
# 3520 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 730 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical SupEq,  _3)) [_2] )
# 3529 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 731 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical Eq,     _3)) [_2] )
# 3538 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 732 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical NotEq,  _3)) [_2] )
# 3547 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 733 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith And,      _3)) [_2] )
# 3556 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 734 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Or,       _3)) [_2] )
# 3565 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 735 "parser_c.mly"
                                 ( mk_e(Binary (_1, Arith Xor,      _3)) [_2] )
# 3574 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 736 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical AndLog, _3)) [_2] )
# 3583 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'arith_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'arith_expr) in
    Obj.repr(
# 737 "parser_c.mly"
                                 ( mk_e(Binary (_1, Logical OrLog,  _3)) [_2] )
# 3592 "parser_c.ml"
               : 'arith_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'unary_expr) in
    Obj.repr(
# 740 "parser_c.mly"
                                     ( _1 )
# 3599 "parser_c.ml"
               : 'cast_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'topar2) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.fullType) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'tcpar2) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'cast_expr) in
    Obj.repr(
# 741 "parser_c.mly"
                                     ( mk_e(Cast (_2, _4)) [_1;_3] )
# 3609 "parser_c.ml"
               : 'cast_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'postfix_expr) in
    Obj.repr(
# 744 "parser_c.mly"
                                   ( _1 )
# 3616 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'unary_expr) in
    Obj.repr(
# 745 "parser_c.mly"
                                   ( mk_e(Infix (_2, Inc))    [_1] )
# 3624 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'unary_expr) in
    Obj.repr(
# 746 "parser_c.mly"
                                   ( mk_e(Infix (_2, Dec))    [_1] )
# 3632 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'unary_op) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'cast_expr) in
    Obj.repr(
# 747 "parser_c.mly"
                                   ( mk_e(Unary (_2, fst _1)) [snd _1] )
# 3640 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'unary_expr) in
    Obj.repr(
# 748 "parser_c.mly"
                                   ( mk_e(SizeOfExpr (_2))    [_1] )
# 3648 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'topar2) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.fullType) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar2) in
    Obj.repr(
# 749 "parser_c.mly"
                                   ( mk_e(SizeOfType (_3))    [_1;_2;_4] )
# 3658 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'new_argument) in
    Obj.repr(
# 750 "parser_c.mly"
                                   ( mk_e(New (None, _2))     [_1] )
# 3666 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list_ne) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'new_argument) in
    Obj.repr(
# 751 "parser_c.mly"
                                                  ( mk_e(New (Some _3, _5))             [_1; _2; _4] )
# 3677 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'cast_expr) in
    Obj.repr(
# 752 "parser_c.mly"
                                   ( mk_e(Delete _2)          [_1] )
# 3685 "parser_c.ml"
               : 'unary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list_ne) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 756 "parser_c.mly"
     ( let fn = mk_e(Ident (RegularName (mk_string_wrap _1))) [] in
       Left (mk_e(FunCall (fn, _3)) [_2;_4]) )
# 3696 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 759 "parser_c.mly"
     ( let fn = mk_e(Ident (RegularName (mk_string_wrap _1))) [] in
       Left(mk_e(FunCall (fn, [])) [_2;_3]) )
# 3706 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list_ne) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 762 "parser_c.mly"
     ( let fn = mk_e(Ident (RegularName (mk_string_wrap _1))) [] in
       Left (mk_e(FunCall (fn, _3)) [_2;_4]) )
# 3717 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 765 "parser_c.mly"
     ( let fn = mk_e(Ident (RegularName (mk_string_wrap _1))) [] in
       Left (mk_e(FunCall (fn, [])) [_2;_3]) )
# 3727 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_spec) in
    Obj.repr(
# 768 "parser_c.mly"
     ( let ty = addTypeD (_1,nullDecl) in
       let ((returnType,hasreg), iihasreg) = fixDeclSpecForParam ty in
       Right (ArgType { p_namei = None; p_type = returnType;
			p_register = hasreg, iihasreg;
		      } )
     )
# 3739 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'new_argument) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 775 "parser_c.mly"
     (
       match _1 with
	 Left(e) -> Left(mk_e(ArrayAccess (e, _3)) [_2;_4])
       | Right(ArgType(ty)) -> (* lots of hacks to make the right type *)
	   let fty = mk_ty (Array (Some _3, ty.Ast_c.p_type)) [_2;_4] in
	   let pty = { ty with p_type = fty } in
	   Right(ArgType pty)
       | _ -> raise (Impossible 88)
     )
# 3757 "parser_c.ml"
               : 'new_argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 786 "parser_c.mly"
          ( GetRef,     _1 )
# 3764 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 787 "parser_c.mly"
          ( DeRef,      _1 )
# 3771 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 788 "parser_c.mly"
          ( UnPlus,     _1 )
# 3778 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 789 "parser_c.mly"
          ( UnMinus,    _1 )
# 3785 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 790 "parser_c.mly"
          ( Tilde,      _1 )
# 3792 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 791 "parser_c.mly"
          ( Not,        _1 )
# 3799 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 795 "parser_c.mly"
           ( GetRefLabel, _1 )
# 3806 "parser_c.ml"
               : 'unary_op))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'primary_expr) in
    Obj.repr(
# 798 "parser_c.mly"
                              ( _1 )
# 3813 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 800 "parser_c.mly"
     ( mk_e(ArrayAccess (_1, _3)) [_2;_4] )
# 3823 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list_ne) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 802 "parser_c.mly"
     ( mk_e(FunCall (_1, _3)) [_2;_4] )
# 3833 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 803 "parser_c.mly"
                              ( mk_e(FunCall (_1, [])) [_2;_3] )
# 3842 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ident_cpp) in
    Obj.repr(
# 804 "parser_c.mly"
                                 ( mk_e(RecordAccess   (_1,_3)) [_2] )
# 3851 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'ident_cpp) in
    Obj.repr(
# 805 "parser_c.mly"
                                 ( mk_e(RecordPtAccess (_1,_3)) [_2] )
# 3860 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 806 "parser_c.mly"
                              ( mk_e(Postfix (_1, Inc)) [_2] )
# 3868 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'postfix_expr) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 807 "parser_c.mly"
                              ( mk_e(Postfix (_1, Dec)) [_2] )
# 3876 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : 'topar2) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.fullType) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'tcpar2) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 811 "parser_c.mly"
     ( mk_e(Constructor (_2, (InitList [], [_4;_5]))) [_1;_3] )
# 3887 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : 'topar2) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.fullType) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'tcpar2) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'initialize_list) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'gcc_comma_opt) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 813 "parser_c.mly"
     ( mk_e(Constructor (_2, (InitList (List.rev _5),[_4;_7]++_6))) [_1;_3] )
# 3900 "parser_c.ml"
               : 'postfix_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'identifier_cpp) in
    Obj.repr(
# 817 "parser_c.mly"
                   ( mk_e(Ident  (_1)) [] )
# 3907 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * (Ast_c.sign * Ast_c.base)) * Ast_c.info) in
    Obj.repr(
# 819 "parser_c.mly"
    ( let (str,(sign,base)) = fst _1 in
      mk_e(Constant (Int (str,Si(sign,base)))) [snd _1] )
# 3915 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.floatType) * Ast_c.info) in
    Obj.repr(
# 821 "parser_c.mly"
           ( mk_e(Constant (Float  (fst _1))) [snd _1] )
# 3922 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.isWchar) * Ast_c.info) in
    Obj.repr(
# 822 "parser_c.mly"
           ( mk_e(Constant (String (fst _1))) [snd _1] )
# 3929 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : (string * Ast_c.isWchar) * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'string_fragments) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.isWchar) * Ast_c.info) in
    Obj.repr(
# 824 "parser_c.mly"
     ( let ((fullstring,isW),lqinfo) = _1 in
       let (_,rqinfo) = _3 in
       mk_e (Ast_c.StringConstant(_2, fullstring, isW)) [lqinfo;rqinfo] )
# 3940 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.isWchar) * Ast_c.info) in
    Obj.repr(
# 827 "parser_c.mly"
           ( mk_e(Constant (Char   (fst _1))) [snd _1] )
# 3947 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * string (*n*) * string (*p*)) * Ast_c.info) in
    Obj.repr(
# 828 "parser_c.mly"
            ( let (a,b,c) = fst _1 in
              mk_e(Constant (DecimalConst (a,b,c))) [snd _1] )
# 3955 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 830 "parser_c.mly"
                    ( mk_e(ParenExpr (_2)) [_1;_3] )
# 3964 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 833 "parser_c.mly"
                ( mk_e(Constant (MultiString [fst _1])) [snd _1] )
# 3971 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'string_elem) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'string_list) in
    Obj.repr(
# 835 "parser_c.mly"
     ( mk_e(Constant (MultiString ["TODO: MultiString"])) (_1 ++ _2) )
# 3979 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'compound) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 838 "parser_c.mly"
                         ( mk_e(StatementExpr (_2)) [_1;_3] )
# 3988 "parser_c.ml"
               : 'primary_expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 841 "parser_c.mly"
               ( [] )
# 3994 "parser_c.ml"
               : 'string_fragments))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'string_fragment) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'string_fragments) in
    Obj.repr(
# 842 "parser_c.mly"
                                    ( _1 :: _2 )
# 4002 "parser_c.ml"
               : 'string_fragments))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'string_format) in
    Obj.repr(
# 845 "parser_c.mly"
                      ( Ast_c.FormatFragment(_2), [_1] )
# 4010 "parser_c.ml"
               : 'string_fragment))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 846 "parser_c.mly"
              ( Ast_c.ConstantFragment(fst _1), [snd _1] )
# 4017 "parser_c.ml"
               : 'string_fragment))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 849 "parser_c.mly"
           ( Ast_c.ConstantFormat(fst _1), [snd _1] )
# 4024 "parser_c.ml"
               : 'string_format))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 858 "parser_c.mly"
               ( Left _1 )
# 4031 "parser_c.ml"
               : 'argument_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl) in
    Obj.repr(
# 859 "parser_c.mly"
                  ( Right (ArgType _1)  )
# 4038 "parser_c.ml"
               : 'argument_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'action_higherordermacro_ne) in
    Obj.repr(
# 860 "parser_c.mly"
                              ( Right (ArgAction _1) )
# 4045 "parser_c.ml"
               : 'argument_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 864 "parser_c.mly"
               ( Left _1 )
# 4052 "parser_c.ml"
               : 'argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl) in
    Obj.repr(
# 865 "parser_c.mly"
                  ( Right (ArgType _1)  )
# 4059 "parser_c.ml"
               : 'argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'action_higherordermacro) in
    Obj.repr(
# 867 "parser_c.mly"
                           ( Right (ArgAction _1) )
# 4066 "parser_c.ml"
               : 'argument))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'taction_list_ne) in
    Obj.repr(
# 871 "parser_c.mly"
     ( if null _1
       then ActMisc [Ast_c.fakeInfo()]
       else ActMisc _1
     )
# 4076 "parser_c.ml"
               : 'action_higherordermacro_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'taction_list) in
    Obj.repr(
# 879 "parser_c.mly"
     ( if null _1
       then ActMisc [Ast_c.fakeInfo()]
       else ActMisc _1
     )
# 4086 "parser_c.ml"
               : 'action_higherordermacro))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cond_expr) in
    Obj.repr(
# 890 "parser_c.mly"
                      ( _1  )
# 4093 "parser_c.ml"
               : 'const_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 893 "parser_c.mly"
              ( et "topar2" (); _1  )
# 4100 "parser_c.ml"
               : 'topar2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 894 "parser_c.mly"
              ( et "tcpar2" (); _1 (*TODO? et ? sure ? c pas dt plutot ? *) )
# 4107 "parser_c.ml"
               : 'tcpar2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'statement2) in
    Obj.repr(
# 902 "parser_c.mly"
                      ( mk_st (fst _1) (snd _1) )
# 4114 "parser_c.ml"
               : Ast_c.statement))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'labeled) in
    Obj.repr(
# 905 "parser_c.mly"
                   ( Labeled      (fst _1), snd _1 )
# 4121 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'compound) in
    Obj.repr(
# 906 "parser_c.mly"
                   ( Compound     (fst _1), snd _1 )
# 4128 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'expr_statement) in
    Obj.repr(
# 907 "parser_c.mly"
                   ( ExprStatement(fst _1), snd _1 )
# 4135 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'selection) in
    Obj.repr(
# 908 "parser_c.mly"
                   ( Selection    (fst _1), snd _1 ++ [fakeInfo()] )
# 4142 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'iteration) in
    Obj.repr(
# 909 "parser_c.mly"
                   ( Iteration    (fst _1), snd _1 ++ [fakeInfo()] )
# 4149 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'jump) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 910 "parser_c.mly"
                   ( Jump         (fst _1), snd _1 ++ [_2] )
# 4157 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'asmbody) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 913 "parser_c.mly"
                                                ( Asm _3, [_1;_2;_4;_5] )
# 4168 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'asmbody) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 914 "parser_c.mly"
                                                ( Asm _4, [_1;_2;_3;_5;_6] )
# 4180 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 917 "parser_c.mly"
              ( MacroStmt, [snd _1] )
# 4187 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'identifier) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'exec_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 919 "parser_c.mly"
                                      ( Exec(_3), [_1;snd _2;_4] )
# 4197 "parser_c.ml"
               : 'statement2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'ident_cpp) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'sw_stat_or_decl) in
    Obj.repr(
# 926 "parser_c.mly"
                                              ( Label (_1, _3),  [_2] )
# 4206 "parser_c.ml"
               : 'labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'sw_stat_or_decl) in
    Obj.repr(
# 927 "parser_c.mly"
                                              ( Case (_2, _4),       [_1; _3] )
# 4216 "parser_c.ml"
               : 'labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'const_expr) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'sw_stat_or_decl) in
    Obj.repr(
# 929 "parser_c.mly"
     ( CaseRange (_2, _4, _6), [_1;_3;_5] )
# 4228 "parser_c.ml"
               : 'labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'sw_stat_or_decl) in
    Obj.repr(
# 930 "parser_c.mly"
                                         ( Default _3,             [_1; _2] )
# 4237 "parser_c.ml"
               : 'labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 933 "parser_c.mly"
             ( mk_st (Decl (_1 Ast_c.LocalDecl)) Ast_c.noii )
# 4244 "parser_c.ml"
               : 'sw_stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 934 "parser_c.mly"
             ( _1 )
# 4251 "parser_c.ml"
               : 'sw_stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'ident_cpp) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 945 "parser_c.mly"
     ( Label (_1, (mk_st (ExprStatement None) Ast_c.noii)), [_2] )
# 4259 "parser_c.ml"
               : 'end_labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 947 "parser_c.mly"
     ( Case (_2, (mk_st (ExprStatement None) Ast_c.noii)), [_1;_3] )
# 4268 "parser_c.ml"
               : 'end_labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 949 "parser_c.mly"
     ( Default (mk_st (ExprStatement None) Ast_c.noii),    [_1; _2] )
# 4276 "parser_c.ml"
               : 'end_labeled))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'tobrace) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'compound2) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace) in
    Obj.repr(
# 955 "parser_c.mly"
                                    ( _2, [_1; _3]  )
# 4285 "parser_c.ml"
               : 'compound))
; (fun __caml_parser_env ->
    Obj.repr(
# 967 "parser_c.mly"
                     ( ([]) )
# 4291 "parser_c.ml"
               : 'compound2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'stat_or_decl_list) in
    Obj.repr(
# 968 "parser_c.mly"
                     ( _1 )
# 4298 "parser_c.ml"
               : 'compound2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'stat_or_decl) in
    Obj.repr(
# 972 "parser_c.mly"
                                  ( [_1] )
# 4305 "parser_c.ml"
               : 'stat_or_decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'end_labeled) in
    Obj.repr(
# 974 "parser_c.mly"
                ( [StmtElem (mk_st (Labeled  (fst _1)) (snd _1))] )
# 4312 "parser_c.ml"
               : 'stat_or_decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'stat_or_decl) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stat_or_decl_list) in
    Obj.repr(
# 976 "parser_c.mly"
                                  ( _1 :: _2 )
# 4320 "parser_c.ml"
               : 'stat_or_decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 979 "parser_c.mly"
             ( StmtElem (mk_st (Decl (_1 Ast_c.LocalDecl)) Ast_c.noii) )
# 4327 "parser_c.ml"
               : 'stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 980 "parser_c.mly"
             ( StmtElem _1 )
# 4334 "parser_c.ml"
               : 'stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'function_definition) in
    Obj.repr(
# 983 "parser_c.mly"
                       ( StmtElem (mk_st (NestedFunc _1) Ast_c.noii) )
# 4341 "parser_c.ml"
               : 'stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_directive) in
    Obj.repr(
# 987 "parser_c.mly"
     ( CppDirectiveStmt _1 )
# 4348 "parser_c.ml"
               : 'stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_ifdef_directive) in
    Obj.repr(
# 989 "parser_c.mly"
     ( IfdefStmt _1 )
# 4355 "parser_c.ml"
               : 'stat_or_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 993 "parser_c.mly"
                ( None,    [_1] )
# 4362 "parser_c.ml"
               : 'expr_statement))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.expression) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 994 "parser_c.mly"
                ( Some _1, [_2] )
# 4370 "parser_c.ml"
               : 'expr_statement))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 998 "parser_c.mly"
     ( If (_3, _5, (mk_st (ExprStatement None) Ast_c.noii)),   [_1;_2;_4] )
# 4381 "parser_c.ml"
               : 'selection))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.statement) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1000 "parser_c.mly"
     ( If (_3, _5, _7),  [_1;_2;_4;_6] )
# 4394 "parser_c.ml"
               : 'selection))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1002 "parser_c.mly"
     ( Switch (_3,_5),   [_1;_2;_4]  )
# 4405 "parser_c.ml"
               : 'selection))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1006 "parser_c.mly"
     ( While (_3,_5),                [_1;_2;_4] )
# 4416 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.statement) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1008 "parser_c.mly"
     ( DoWhile (_2,_5),              [_1;_3;_4;_6;_7] )
# 4429 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : 'expr_statement) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'expr_statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1010 "parser_c.mly"
     ( For (ForExp _3,_4,(None, []),_6),    [_1;_2;_5])
# 4441 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'expr_statement) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : 'expr_statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1012 "parser_c.mly"
     ( For (ForExp _3,_4,(Some _5, []),_7), [_1;_2;_6] )
# 4454 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : 'decl) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'expr_statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1015 "parser_c.mly"
     ( For (ForDecl (_3 Ast_c.LocalDecl),_4,(None, []),_6),    [_1;_2;_5])
# 4466 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'decl) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : 'expr_statement) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1017 "parser_c.mly"
     ( For (ForDecl (_3 Ast_c.LocalDecl),_4,(Some _5, []),_7), [_1;_2;_6] )
# 4479 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : (string * Ast_c.info)) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list_ne) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1020 "parser_c.mly"
     ( MacroIteration (fst _1, _3, _5), [snd _1;_2;_4] )
# 4490 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : (string * Ast_c.info)) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1022 "parser_c.mly"
     ( MacroIteration (fst _1, [], _4), [snd _1;_2;_3] )
# 4500 "parser_c.ml"
               : 'iteration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ident_cpp) in
    Obj.repr(
# 1026 "parser_c.mly"
                    ( Goto (_2),  [_1] )
# 4508 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1027 "parser_c.mly"
                ( Continue,       [_1] )
# 4515 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1028 "parser_c.mly"
                ( Break,          [_1] )
# 4522 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1029 "parser_c.mly"
                ( Return,         [_1] )
# 4529 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.expression) in
    Obj.repr(
# 1030 "parser_c.mly"
                ( ReturnExpr _2,  [_1] )
# 4537 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.expression) in
    Obj.repr(
# 1031 "parser_c.mly"
                   ( GotoComputed _3, [_1;_2] )
# 4546 "parser_c.ml"
               : 'jump))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.isWchar) * Ast_c.info) in
    Obj.repr(
# 1039 "parser_c.mly"
           ( [snd _1] )
# 4553 "parser_c.ml"
               : 'string_elem))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1041 "parser_c.mly"
                ( [snd _1] )
# 4560 "parser_c.ml"
               : 'string_elem))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'string_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'colon_asm_list) in
    Obj.repr(
# 1045 "parser_c.mly"
                               ( _1, _2 )
# 4568 "parser_c.ml"
               : 'asmbody))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'string_list) in
    Obj.repr(
# 1046 "parser_c.mly"
               ( _1, [] )
# 4575 "parser_c.ml"
               : 'asmbody))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'colon_option_list) in
    Obj.repr(
# 1049 "parser_c.mly"
                                     ( Colon _2, [_1]   )
# 4583 "parser_c.ml"
               : 'colon_asm))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.isWchar) * Ast_c.info) in
    Obj.repr(
# 1052 "parser_c.mly"
                                ( ColonMisc, [snd _1] )
# 4590 "parser_c.ml"
               : 'colon_option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : (string * Ast_c.isWchar) * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'asm_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1053 "parser_c.mly"
                                ( ColonExpr _3, [snd _1; _2;_4] )
# 4600 "parser_c.ml"
               : 'colon_option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : 'identifier) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : (string * Ast_c.isWchar) * Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'asm_expr) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1056 "parser_c.mly"
     ( ColonExpr _6, [_1;snd _2;_3;snd _4; _5; _7 ] )
# 4613 "parser_c.ml"
               : 'colon_option))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'identifier) in
    Obj.repr(
# 1057 "parser_c.mly"
                                    ( ColonMisc, [snd _1] )
# 4620 "parser_c.ml"
               : 'colon_option))
; (fun __caml_parser_env ->
    Obj.repr(
# 1058 "parser_c.mly"
                                    ( ColonMisc, [] )
# 4626 "parser_c.ml"
               : 'colon_option))
; (fun __caml_parser_env ->
    Obj.repr(
# 1062 "parser_c.mly"
                ( [] )
# 4632 "parser_c.ml"
               : 'exec_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'identifier_cpp) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'exec_ident) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'exec_list) in
    Obj.repr(
# 1064 "parser_c.mly"
      ( (ExecEval (_3 (mk_e (Ident _2) [])), [_1]) :: _4 )
# 4642 "parser_c.ml"
               : 'exec_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'exec_ident2) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exec_list) in
    Obj.repr(
# 1066 "parser_c.mly"
      ( (ExecToken, [snd _1]) :: _2 @ _3 )
# 4651 "parser_c.ml"
               : 'exec_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'token) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'exec_list) in
    Obj.repr(
# 1067 "parser_c.mly"
                    ( (ExecToken, [_1]) :: _2 )
# 4659 "parser_c.ml"
               : 'exec_list))
; (fun __caml_parser_env ->
    Obj.repr(
# 1070 "parser_c.mly"
    ( function prev -> prev )
# 4665 "parser_c.ml"
               : 'exec_ident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string * Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exec_ident) in
    Obj.repr(
# 1072 "parser_c.mly"
     ( function prev ->
       let fld = RegularName (mk_string_wrap _2) in
       _3 (mk_e(RecordAccess   (prev,fld)) [_1]) )
# 4676 "parser_c.ml"
               : 'exec_ident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string * Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exec_ident) in
    Obj.repr(
# 1076 "parser_c.mly"
     ( function prev ->
       let fld = RegularName (mk_string_wrap _2) in
       _3 (mk_e(RecordPtAccess   (prev,fld)) [_1]) )
# 4687 "parser_c.ml"
               : 'exec_ident))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.expression) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'exec_ident) in
    Obj.repr(
# 1080 "parser_c.mly"
     ( function prev ->
       _4 (mk_e(ArrayAccess   (prev,_2)) [_1;_3]) )
# 4698 "parser_c.ml"
               : 'exec_ident))
; (fun __caml_parser_env ->
    Obj.repr(
# 1084 "parser_c.mly"
    ( [] )
# 4704 "parser_c.ml"
               : 'exec_ident2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : string * Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'exec_ident2) in
    Obj.repr(
# 1086 "parser_c.mly"
    ( (ExecToken, [_1]) :: (ExecToken, [snd _2]) :: _3 )
# 4713 "parser_c.ml"
               : 'exec_ident2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 1088 "parser_c.mly"
                      ( _1 )
# 4720 "parser_c.ml"
               : 'asm_expr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1091 "parser_c.mly"
            ( _1 )
# 4727 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1092 "parser_c.mly"
            ( _1 )
# 4734 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1093 "parser_c.mly"
            ( _1 )
# 4741 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1094 "parser_c.mly"
            ( _1 )
# 4748 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1095 "parser_c.mly"
            ( _1 )
# 4755 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1096 "parser_c.mly"
            ( _1 )
# 4762 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1097 "parser_c.mly"
            ( _1 )
# 4769 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1098 "parser_c.mly"
            ( _1 )
# 4776 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1099 "parser_c.mly"
            ( _1 )
# 4783 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1100 "parser_c.mly"
            ( _1 )
# 4790 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.assignOp * Ast_c.info) in
    Obj.repr(
# 1101 "parser_c.mly"
            ( snd _1 )
# 4797 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1103 "parser_c.mly"
            ( _1 )
# 4804 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1104 "parser_c.mly"
            ( _1 )
# 4811 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1105 "parser_c.mly"
            ( _1 )
# 4818 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1106 "parser_c.mly"
            ( _1 )
# 4825 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1107 "parser_c.mly"
            ( _1 )
# 4832 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1108 "parser_c.mly"
            ( _1 )
# 4839 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1110 "parser_c.mly"
            ( _1 )
# 4846 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1111 "parser_c.mly"
            ( _1 )
# 4853 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1112 "parser_c.mly"
            ( _1 )
# 4860 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1113 "parser_c.mly"
            ( _1 )
# 4867 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1114 "parser_c.mly"
            ( _1 )
# 4874 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1115 "parser_c.mly"
            ( _1 )
# 4881 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1116 "parser_c.mly"
            ( _1 )
# 4888 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1118 "parser_c.mly"
            ( _1 )
# 4895 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1119 "parser_c.mly"
            ( _1 )
# 4902 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1122 "parser_c.mly"
            ( _1 )
# 4909 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1123 "parser_c.mly"
            ( _1 )
# 4916 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1127 "parser_c.mly"
            ( _1 )
# 4923 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1128 "parser_c.mly"
            ( _1 )
# 4930 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1129 "parser_c.mly"
            ( _1 )
# 4937 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 1131 "parser_c.mly"
                 ( snd _1 )
# 4944 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1133 "parser_c.mly"
            ( _1 )
# 4951 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1134 "parser_c.mly"
            ( _1 )
# 4958 "parser_c.ml"
               : 'token))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1145 "parser_c.mly"
                        ( Right3 (BaseType Void),            [_1] )
# 4965 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1146 "parser_c.mly"
                        ( Right3 (BaseType (IntType CChar)), [_1])
# 4972 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1147 "parser_c.mly"
                        ( Right3 (BaseType (IntType (Si (Signed,CInt)))), [_1])
# 4979 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1148 "parser_c.mly"
                        ( Right3 (BaseType (FloatType CFloat)),  [_1])
# 4986 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1149 "parser_c.mly"
                        ( Right3 (BaseType (FloatType CDouble)), [_1] )
# 4993 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1150 "parser_c.mly"
                        ( Right3 (BaseType SizeType),            [_1] )
# 5000 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1151 "parser_c.mly"
                        ( Right3 (BaseType SSizeType),           [_1] )
# 5007 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1152 "parser_c.mly"
                        ( Right3 (BaseType PtrDiffType),         [_1] )
# 5014 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1153 "parser_c.mly"
                        ( Middle3 Short,  [_1])
# 5021 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1154 "parser_c.mly"
                        ( Middle3 Long,   [_1])
# 5028 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1155 "parser_c.mly"
                        ( Left3 Signed,   [_1])
# 5035 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1156 "parser_c.mly"
                        ( Left3 UnSigned, [_1])
# 5042 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_or_union_spec) in
    Obj.repr(
# 1157 "parser_c.mly"
                        ( Right3 (fst _1), snd _1 )
# 5049 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'enum_spec) in
    Obj.repr(
# 1158 "parser_c.mly"
                        ( Right3 (fst _1), snd _1 )
# 5056 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : 'const_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1160 "parser_c.mly"
     ( Right3 (Decimal(_3,Some _5)), [_1;_2;_4;_6] )
# 5068 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1162 "parser_c.mly"
     ( Right3 (Decimal(_3,None)), [_1;_2;_4] )
# 5078 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 1178 "parser_c.mly"
     ( let name = RegularName (mk_string_wrap _1) in
       Right3 (TypeName (name, Ast_c.noTypedefDef())),[] )
# 5086 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'assign_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1181 "parser_c.mly"
                                   ( Right3 (TypeOfExpr (_3)), [_1;_2;_4] )
# 5096 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.fullType) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1182 "parser_c.mly"
                                   ( Right3 (TypeOfType (_3)), [_1;_2;_4] )
# 5106 "parser_c.ml"
               : 'type_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_spec2) in
    Obj.repr(
# 1188 "parser_c.mly"
                         ( dt "type" (); _1   )
# 5113 "parser_c.ml"
               : 'type_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1195 "parser_c.mly"
             ( {const=true  ; volatile=false}, _1 )
# 5120 "parser_c.ml"
               : 'type_qualif))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1196 "parser_c.mly"
             ( {const=false ; volatile=true},  _1 )
# 5127 "parser_c.ml"
               : 'type_qualif))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1198 "parser_c.mly"
             ( (* TODO *) {const=false ; volatile=false},  _1 )
# 5134 "parser_c.ml"
               : 'type_qualif))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1206 "parser_c.mly"
                                    ( raise Todo )
# 5143 "parser_c.ml"
               : 'attribute))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1208 "parser_c.mly"
              ( Attribute (fst _1), [snd _1] )
# 5150 "parser_c.ml"
               : 'attribute))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1211 "parser_c.mly"
                     ( _1 )
# 5157 "parser_c.ml"
               : 'attribute_storage))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif) in
    Obj.repr(
# 1214 "parser_c.mly"
               ( _1 )
# 5164 "parser_c.ml"
               : 'type_qualif_attr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1216 "parser_c.mly"
              ( {const=true  ; volatile=false}, snd _1   )
# 5171 "parser_c.ml"
               : 'type_qualif_attr))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'pointer) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'direct_d) in
    Obj.repr(
# 1231 "parser_c.mly"
                    ( (fst _2, fun x -> x +> _1 +> (snd _2)  ) )
# 5179 "parser_c.ml"
               : 'declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'direct_d) in
    Obj.repr(
# 1232 "parser_c.mly"
                    ( _1  )
# 5186 "parser_c.ml"
               : 'declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'tmul) in
    Obj.repr(
# 1236 "parser_c.mly"
                          ( fun x -> mk_ty (Pointer x) [_1] )
# 5193 "parser_c.ml"
               : 'pointer))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'tmul) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'pointer) in
    Obj.repr(
# 1237 "parser_c.mly"
                          ( fun x -> mk_ty (Pointer (_2 x)) [_1] )
# 5201 "parser_c.ml"
               : 'pointer))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'tmul) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif_list) in
    Obj.repr(
# 1239 "parser_c.mly"
     ( fun x -> (_2.qualifD, mk_tybis (Pointer x) [_1]))
# 5209 "parser_c.ml"
               : 'pointer))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'tmul) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'type_qualif_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'pointer) in
    Obj.repr(
# 1241 "parser_c.mly"
     ( fun x -> (_2.qualifD, mk_tybis (Pointer (_3 x)) [_1]) )
# 5218 "parser_c.ml"
               : 'pointer))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1244 "parser_c.mly"
        ( _1 )
# 5225 "parser_c.ml"
               : 'tmul))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1246 "parser_c.mly"
     ( if !Flag.c_plus_plus
     then _1
     else
       let i = Ast_c.parse_info_of_info _1 in
       raise (Semantic("& not allowed in C types, try -c++ option", i)) )
# 5236 "parser_c.ml"
               : 'tmul))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'identifier_cpp) in
    Obj.repr(
# 1255 "parser_c.mly"
     ( (_1, fun x -> x) )
# 5243 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1257 "parser_c.mly"
     ( (fst _2, fun x -> mk_ty (ParenType ((snd _2) x)) [_1;_3]) )
# 5252 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'direct_d) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'tocro) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tccro) in
    Obj.repr(
# 1259 "parser_c.mly"
     ( (fst _1,fun x->(snd _1) (mk_ty (Array (None,x)) [_2;_3])) )
# 5261 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'direct_d) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'tocro) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tccro) in
    Obj.repr(
# 1261 "parser_c.mly"
     ( (fst _1,fun x->(snd _1) (mk_ty (Array (Some _3,x)) [_2;_4])) )
# 5271 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'direct_d) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1263 "parser_c.mly"
     ( (fst _1,
       fun x->(snd _1)
         (mk_ty (FunctionType (x,(([],(false, []))))) [_2;_3]))
     )
# 5283 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'direct_d) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'parameter_type_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1268 "parser_c.mly"
     ( (fst _1,fun x->(snd _1)
       (mk_ty (FunctionType (x, _3)) [_2;_4]))
     )
# 5295 "parser_c.ml"
               : 'direct_d))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1277 "parser_c.mly"
             ( et "tocro" ();_1 )
# 5302 "parser_c.ml"
               : 'tocro))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1278 "parser_c.mly"
             ( dt "tccro" ();_1 )
# 5309 "parser_c.ml"
               : 'tccro))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'pointer) in
    Obj.repr(
# 1282 "parser_c.mly"
                                      ( _1 )
# 5316 "parser_c.ml"
               : 'abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'direct_abstract_declarator) in
    Obj.repr(
# 1283 "parser_c.mly"
                                      ( _1 )
# 5323 "parser_c.ml"
               : 'abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'pointer) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'direct_abstract_declarator) in
    Obj.repr(
# 1284 "parser_c.mly"
                                      ( fun x -> x +> _2 +> _1 )
# 5331 "parser_c.ml"
               : 'abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'abstract_declarator) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1288 "parser_c.mly"
     ( fun x -> mk_ty (ParenType (_2 x)) [_1;_3] )
# 5340 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1291 "parser_c.mly"
     ( fun x -> mk_ty (Array (None, x)) [_1;_2] )
# 5348 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1293 "parser_c.mly"
     ( fun x -> mk_ty (Array (Some _2, x)) [_1;_3] )
# 5357 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'direct_abstract_declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1295 "parser_c.mly"
     ( fun x -> _1 (mk_ty (Array (None, x))  [_2;_3]) )
# 5366 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'direct_abstract_declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1297 "parser_c.mly"
     ( fun x -> _1 (mk_ty (Array (Some _3,x))  [_2;_4]) )
# 5376 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1299 "parser_c.mly"
     ( fun x -> mk_ty (FunctionType (x, ([], (false,  [])))) [_1;_2] )
# 5384 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'topar) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'parameter_type_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1301 "parser_c.mly"
     ( fun x -> mk_ty (FunctionType (x, _2))  [_1;_3] )
# 5393 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'direct_abstract_declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1312 "parser_c.mly"
     ( fun x -> _1 (mk_ty (FunctionType (x, (([], (false, []))))) [_2;_3]) )
# 5402 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'direct_abstract_declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'parameter_type_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1314 "parser_c.mly"
     ( fun x -> _1 (mk_ty (FunctionType (x, _3)) [_2;_4]) )
# 5412 "parser_c.ml"
               : 'direct_abstract_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_list) in
    Obj.repr(
# 1320 "parser_c.mly"
                                   ( (_1, (false, [])))
# 5419 "parser_c.ml"
               : 'parameter_type_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'parameter_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1321 "parser_c.mly"
                                   ( (_1, (true,  [_2;_3])) )
# 5428 "parser_c.ml"
               : 'parameter_type_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 1325 "parser_c.mly"
            (
     let name = RegularName (mk_string_wrap _1) in
     LP.add_ident (str_of_name name);
     { p_namei = Some name;
       p_type = mk_ty NoType [];
       p_register = (false, []);
     }
   )
# 5442 "parser_c.ml"
               : 'parameter_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declaratorp) in
    Obj.repr(
# 1334 "parser_c.mly"
     ( let ((returnType,hasreg),iihasreg) = fixDeclSpecForParam _1 in
       let (name, ftyp) = _2 in
       { p_namei = Some (name);
         p_type = ftyp returnType;
         p_register = (hasreg, iihasreg);
       }
     )
# 5456 "parser_c.ml"
               : 'parameter_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declaratorp) in
    Obj.repr(
# 1342 "parser_c.mly"
     ( let ((returnType,hasreg), iihasreg) = fixDeclSpecForParam _1 in
       { p_namei = None;
         p_type = _2 returnType;
         p_register = hasreg, iihasreg;
       }
     )
# 5469 "parser_c.ml"
               : 'parameter_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec) in
    Obj.repr(
# 1349 "parser_c.mly"
     ( let ((returnType,hasreg), iihasreg) = fixDeclSpecForParam _1 in
       { p_namei = None;
         p_type = returnType;
         p_register = hasreg, iihasreg;
       }
     )
# 5481 "parser_c.ml"
               : 'parameter_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl2) in
    Obj.repr(
# 1361 "parser_c.mly"
                                ( et "param" ();  _1 )
# 5488 "parser_c.ml"
               : 'parameter_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl2) in
    Obj.repr(
# 1362 "parser_c.mly"
                              ( et "param" (); _2 )
# 5496 "parser_c.ml"
               : 'parameter_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1365 "parser_c.mly"
               ( LP.add_ident (str_of_name (fst _1)); _1 )
# 5503 "parser_c.ml"
               : 'declaratorp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1367 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _2)); _2 )
# 5511 "parser_c.ml"
               : 'declaratorp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1368 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _1)); _1 )
# 5519 "parser_c.ml"
               : 'declaratorp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declarator) in
    Obj.repr(
# 1371 "parser_c.mly"
                       ( _1 )
# 5526 "parser_c.ml"
               : 'abstract_declaratorp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declarator) in
    Obj.repr(
# 1373 "parser_c.mly"
                                  ( _2 )
# 5534 "parser_c.ml"
               : 'abstract_declaratorp))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_spec) in
    Obj.repr(
# 1382 "parser_c.mly"
                                ( addTypeD (_1, nullDecl) )
# 5541 "parser_c.ml"
               : 'spec_qualif_list2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif) in
    Obj.repr(
# 1383 "parser_c.mly"
                                ( {nullDecl with qualifD = (fst _1,[snd _1])})
# 5548 "parser_c.ml"
               : 'spec_qualif_list2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'type_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'spec_qualif_list) in
    Obj.repr(
# 1384 "parser_c.mly"
                                ( addTypeD (_1,_2)   )
# 5556 "parser_c.ml"
               : 'spec_qualif_list2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'type_qualif) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'spec_qualif_list) in
    Obj.repr(
# 1385 "parser_c.mly"
                                ( addQualifD (_1,_2) )
# 5564 "parser_c.ml"
               : 'spec_qualif_list2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'spec_qualif_list2) in
    Obj.repr(
# 1387 "parser_c.mly"
                                               (  dt "spec_qualif" (); _1 )
# 5571 "parser_c.ml"
               : 'spec_qualif_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif_attr) in
    Obj.repr(
# 1392 "parser_c.mly"
                                     ( {nullDecl with qualifD = (fst _1,[snd _1])} )
# 5578 "parser_c.ml"
               : 'type_qualif_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'type_qualif_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif_attr) in
    Obj.repr(
# 1393 "parser_c.mly"
                                     ( addQualifD (_2,_1) )
# 5586 "parser_c.ml"
               : 'type_qualif_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'spec_qualif_list) in
    Obj.repr(
# 1406 "parser_c.mly"
     ( let (returnType, _) = fixDeclSpecForDecl _1 in  returnType )
# 5593 "parser_c.ml"
               : Ast_c.fullType))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'spec_qualif_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declaratort) in
    Obj.repr(
# 1408 "parser_c.mly"
     ( let (returnType, _) = fixDeclSpecForDecl _1 in _2 returnType )
# 5601 "parser_c.ml"
               : Ast_c.fullType))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declarator) in
    Obj.repr(
# 1413 "parser_c.mly"
                       ( _1 )
# 5608 "parser_c.ml"
               : 'abstract_declaratort))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declarator) in
    Obj.repr(
# 1415 "parser_c.mly"
                                  ( _2 )
# 5616 "parser_c.ml"
               : 'abstract_declaratort))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1424 "parser_c.mly"
     ( function local ->
       let (returnType,storage) = fixDeclSpecForDecl _1 in
       let iistart = Ast_c.fakeInfo () in
       DeclList ([{v_namei = None; v_type = returnType;
                   v_storage = unwrap storage; v_local = local;
                   v_attr = Ast_c.noattr;
                   v_type_bis = ref None;
                },[]],
                (_2::iistart::snd storage))
     )
# 5633 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'init_declarator_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1435 "parser_c.mly"
     ( function local ->
       let (returnType,storage) = fixDeclSpecForDecl _1 in
       let iistart = Ast_c.fakeInfo () in
       DeclList (
         (_2 +> List.map (fun ((((name,f),attrs), ini), iivirg) ->
           let s = str_of_name name in
	   if fst (unwrap storage) =*= StoTypedef
	   then LP.add_typedef s;
           {v_namei = Some (name, ini);
            v_type = f returnType;
            v_storage = unwrap storage;
            v_local = local;
            v_attr = attrs;
            v_type_bis = ref None;
           },
           iivirg
         )
         ),  (_3::iistart::snd storage))
     )
# 5660 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : (string * Ast_c.info)) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1457 "parser_c.mly"
     ( function _ ->
       MacroDecl ((fst _1, _3, true), [snd _1;_2;_4;_5;fakeInfo()]) )
# 5672 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1460 "parser_c.mly"
     ( function _ ->
       MacroDecl ((fst _2, _4, true), [snd _2;_3;_5;_6;fakeInfo();_1]) )
# 5685 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : (string * Ast_c.info)) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1463 "parser_c.mly"
     ( function _ ->
       MacroDecl ((fst _3, _5, true), [snd _3;_4;_6;_7;fakeInfo();_1;_2]))
# 5699 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : (string * Ast_c.info)) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : 'teq) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'initialize) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1468 "parser_c.mly"
     ( function _ ->
       MacroDeclInit ((fst _1, _3, _6), [snd _1;_2;_4;_5;_7;fakeInfo()]) )
# 5713 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 7 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 6 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 4 : 'argument_list) in
    let _5 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 2 : 'teq) in
    let _7 = (Parsing.peek_val __caml_parser_env 1 : 'initialize) in
    let _8 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1471 "parser_c.mly"
     ( function _ ->
       MacroDeclInit ((fst _2, _4, _7),[snd _2;_3;_5;_6;_8;fakeInfo();_1]) )
# 5728 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 8 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 7 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 6 : (string * Ast_c.info)) in
    let _4 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 4 : 'argument_list) in
    let _6 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _7 = (Parsing.peek_val __caml_parser_env 2 : 'teq) in
    let _8 = (Parsing.peek_val __caml_parser_env 1 : 'initialize) in
    let _9 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1475 "parser_c.mly"
     ( function _ ->
       MacroDeclInit
	 ((fst _3, _5, _8), [snd _3;_4;_6;_7;_9;fakeInfo();_1;_2]))
# 5745 "parser_c.ml"
               : 'decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'storage_class_spec) in
    Obj.repr(
# 1482 "parser_c.mly"
                           ( {nullDecl with storageD = (fst _1, [snd _1]) } )
# 5752 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_spec) in
    Obj.repr(
# 1483 "parser_c.mly"
                           ( addTypeD (_1,nullDecl) )
# 5759 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'type_qualif) in
    Obj.repr(
# 1484 "parser_c.mly"
                           ( {nullDecl with qualifD  = (fst _1, [snd _1]) } )
# 5766 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1485 "parser_c.mly"
                           ( {nullDecl with inlineD = (true, [_1]) } )
# 5773 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'storage_class_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec2) in
    Obj.repr(
# 1486 "parser_c.mly"
                                 ( addStorageD (_1, _2) )
# 5781 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'type_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec2) in
    Obj.repr(
# 1487 "parser_c.mly"
                                 ( addTypeD    (_1, _2) )
# 5789 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'type_qualif) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec2) in
    Obj.repr(
# 1488 "parser_c.mly"
                                 ( addQualifD  (_1, _2) )
# 5797 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec2) in
    Obj.repr(
# 1489 "parser_c.mly"
                                 ( addInlineD ((true, _1), _2) )
# 5805 "parser_c.ml"
               : 'decl_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1497 "parser_c.mly"
                ( Sto Static,  _1 )
# 5812 "parser_c.ml"
               : 'storage_class_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1498 "parser_c.mly"
                ( Sto Extern,  _1 )
# 5819 "parser_c.ml"
               : 'storage_class_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1499 "parser_c.mly"
                ( Sto Auto,    _1 )
# 5826 "parser_c.ml"
               : 'storage_class_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1500 "parser_c.mly"
                ( Sto Register,_1 )
# 5833 "parser_c.ml"
               : 'storage_class_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1501 "parser_c.mly"
                ( StoTypedef,  _1 )
# 5840 "parser_c.ml"
               : 'storage_class_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'storage_class_spec2) in
    Obj.repr(
# 1505 "parser_c.mly"
                       ( _1 )
# 5847 "parser_c.ml"
               : 'storage_class_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'storage_class_spec2) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attribute_storage_list) in
    Obj.repr(
# 1506 "parser_c.mly"
                                              ( _1 (* TODO *) )
# 5855 "parser_c.ml"
               : 'storage_class_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl2) in
    Obj.repr(
# 1514 "parser_c.mly"
                         ( et "decl" (); _1 )
# 5862 "parser_c.ml"
               : 'decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec2) in
    Obj.repr(
# 1515 "parser_c.mly"
                         ( dt "declspec" (); _1  )
# 5869 "parser_c.ml"
               : 'decl_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declaratori) in
    Obj.repr(
# 1521 "parser_c.mly"
                                ( (_1, NoInit) )
# 5876 "parser_c.ml"
               : 'init_declarator2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'declaratori) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'teq) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'initialize) in
    Obj.repr(
# 1522 "parser_c.mly"
                                ( (_1, ValInit(_2, _3)) )
# 5885 "parser_c.ml"
               : 'init_declarator2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'declaratori) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1525 "parser_c.mly"
     ( (_1, ConstrInit(_3,[_2;_4])) )
# 5895 "parser_c.ml"
               : 'init_declarator2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1531 "parser_c.mly"
          ( et "teq" (); _1 )
# 5902 "parser_c.ml"
               : 'teq))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'init_declarator2) in
    Obj.repr(
# 1533 "parser_c.mly"
                                   ( dt "init" (); _1 )
# 5909 "parser_c.ml"
               : 'init_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1541 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _1)); _1, Ast_c.noattr )
# 5916 "parser_c.ml"
               : 'declaratori))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'gcc_asm_decl) in
    Obj.repr(
# 1543 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _1)); _1, Ast_c.noattr )
# 5924 "parser_c.ml"
               : 'declaratori))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1545 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _2)); _2, _1 )
# 5932 "parser_c.ml"
               : 'declaratori))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1546 "parser_c.mly"
                           ( LP.add_ident (str_of_name (fst _1)); _1, Ast_c.noattr (* TODO *) )
# 5940 "parser_c.ml"
               : 'declaratori))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'asmbody) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1551 "parser_c.mly"
                                         (  )
# 5950 "parser_c.ml"
               : 'gcc_asm_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'asmbody) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1552 "parser_c.mly"
                                        (  )
# 5961 "parser_c.ml"
               : 'gcc_asm_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'assign_expr) in
    Obj.repr(
# 1558 "parser_c.mly"
     ( InitExpr _1,                [] )
# 5968 "parser_c.ml"
               : 'initialize))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'tobrace_ini) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'initialize_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'gcc_comma_opt_struct) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_ini) in
    Obj.repr(
# 1560 "parser_c.mly"
     ( InitList (List.rev _2),     [_1;_4]++_3 )
# 5978 "parser_c.ml"
               : 'initialize))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'tobrace_ini) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_ini) in
    Obj.repr(
# 1562 "parser_c.mly"
     ( InitList [],       [_1;_2] )
# 5986 "parser_c.ml"
               : 'initialize))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'initialize2) in
    Obj.repr(
# 1573 "parser_c.mly"
                                      ( [_1,   []] )
# 5993 "parser_c.ml"
               : 'initialize_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'initialize_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'initialize2) in
    Obj.repr(
# 1574 "parser_c.mly"
                                      ( (_3,  [_2])::_1 )
# 6002 "parser_c.ml"
               : 'initialize_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cond_expr) in
    Obj.repr(
# 1580 "parser_c.mly"
     ( InitExpr _1,   [] )
# 6009 "parser_c.ml"
               : 'initialize2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'tobrace_ini) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'initialize_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'gcc_comma_opt_struct) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_ini) in
    Obj.repr(
# 1582 "parser_c.mly"
     ( InitList (List.rev _2),   [_1;_4]++_3 )
# 6019 "parser_c.ml"
               : 'initialize2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'tobrace_ini) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_ini) in
    Obj.repr(
# 1584 "parser_c.mly"
     ( InitList [],  [_1;_2]  )
# 6027 "parser_c.ml"
               : 'initialize2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'designator_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'initialize2) in
    Obj.repr(
# 1588 "parser_c.mly"
     ( InitDesignators (_1, _3), [_2] )
# 6036 "parser_c.ml"
               : 'initialize2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'ident) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'initialize2) in
    Obj.repr(
# 1592 "parser_c.mly"
     ( InitFieldOld (fst _1, _3),     [snd _1; _2] )
# 6045 "parser_c.ml"
               : 'initialize2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ident) in
    Obj.repr(
# 1603 "parser_c.mly"
     ( DesignatorField (fst _2), [_1;snd _2] )
# 6053 "parser_c.ml"
               : 'designator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1605 "parser_c.mly"
     ( DesignatorIndex (_2),  [_1;_3] )
# 6062 "parser_c.ml"
               : 'designator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'const_expr) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'const_expr) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1607 "parser_c.mly"
     ( DesignatorRange (_2, _4),  [_1;_3;_5] )
# 6073 "parser_c.ml"
               : 'designator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1615 "parser_c.mly"
          (  [_1] )
# 6080 "parser_c.ml"
               : 'gcc_comma_opt_struct))
; (fun __caml_parser_env ->
    Obj.repr(
# 1616 "parser_c.mly"
                    (  [Ast_c.fakeInfo() +> Ast_c.rewrap_str ","]  )
# 6086 "parser_c.ml"
               : 'gcc_comma_opt_struct))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : 'struct_or_union) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'ident) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'tobrace_struct) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'struct_decl_list_gcc) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_struct) in
    Obj.repr(
# 1631 "parser_c.mly"
     ( StructUnion (fst _1, Some (fst _2), _4),  [snd _1;snd _2;_3;_5]  )
# 6097 "parser_c.ml"
               : 's_or_u_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'struct_or_union) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'tobrace_struct) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'struct_decl_list_gcc) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_struct) in
    Obj.repr(
# 1633 "parser_c.mly"
     ( StructUnion (fst _1, None, _3), [snd _1;_2;_4] )
# 6107 "parser_c.ml"
               : 's_or_u_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'struct_or_union) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ident) in
    Obj.repr(
# 1635 "parser_c.mly"
     ( StructUnionName (fst _1, fst _2), [snd _1;snd _2] )
# 6115 "parser_c.ml"
               : 's_or_u_spec2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1638 "parser_c.mly"
             ( Struct, _1 )
# 6122 "parser_c.ml"
               : 'struct_or_union2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1639 "parser_c.mly"
             ( Union, _1 )
# 6129 "parser_c.ml"
               : 'struct_or_union2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1641 "parser_c.mly"
                        ( Struct, _1 (* TODO *) )
# 6137 "parser_c.ml"
               : 'struct_or_union2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1642 "parser_c.mly"
                        ( Union, _1  (* TODO *) )
# 6145 "parser_c.ml"
               : 'struct_or_union2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'field_declaration) in
    Obj.repr(
# 1647 "parser_c.mly"
                     ( DeclarationField _1 )
# 6152 "parser_c.ml"
               : 'struct_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1648 "parser_c.mly"
           ( EmptyField _1  )
# 6159 "parser_c.ml"
               : 'struct_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : 'identifier) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1654 "parser_c.mly"
     ( MacroDeclField ((fst _1, _3), [snd _1;_2;_4;_5;fakeInfo()]) )
# 6170 "parser_c.ml"
               : 'struct_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_directive) in
    Obj.repr(
# 1658 "parser_c.mly"
     ( CppDirectiveStruct _1 )
# 6177 "parser_c.ml"
               : 'struct_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_ifdef_directive) in
    Obj.repr(
# 1660 "parser_c.mly"
     ( IfdefStruct _1 )
# 6184 "parser_c.ml"
               : 'struct_decl2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'spec_qualif_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'struct_declarator_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1665 "parser_c.mly"
     (
       let (returnType,storage) = fixDeclSpecForDecl _1 in
       if fst (unwrap storage) <> NoSto
       then internal_error "parsing dont allow this";

       FieldDeclList (_2 +> (List.map (fun (f, iivirg) ->
         f returnType, iivirg))
                         ,[_3])
         (* dont need to check if typedef or func initialised cos
          * grammar dont allow typedef nor initialiser in struct
          *)
     )
# 6204 "parser_c.ml"
               : 'field_declaration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'spec_qualif_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1679 "parser_c.mly"
     (
       (* gccext: allow empty elements if it is a structdef or enumdef *)
       let (returnType,storage) = fixDeclSpecForDecl _1 in
       if fst (unwrap storage) <> NoSto
       then internal_error "parsing dont allow this";

       FieldDeclList ([(Simple (None, returnType)) , []], [_2])
     )
# 6219 "parser_c.ml"
               : 'field_declaration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declaratorsd) in
    Obj.repr(
# 1694 "parser_c.mly"
     ( (fun x -> Simple   (Some (fst _1), (snd _1) x)) )
# 6226 "parser_c.ml"
               : 'struct_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'dotdot) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'const_expr2) in
    Obj.repr(
# 1696 "parser_c.mly"
     ( (fun x -> BitField (None, x, _1, _2)) )
# 6234 "parser_c.ml"
               : 'struct_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'declaratorsd) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'dotdot) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'const_expr2) in
    Obj.repr(
# 1698 "parser_c.mly"
     ( (fun x -> BitField (Some (fst _1), ((snd _1) x), _2, _3)) )
# 6243 "parser_c.ml"
               : 'struct_declarator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1705 "parser_c.mly"
              ( (*also ? LP.add_ident (fst (fst $1)); *) _1 )
# 6250 "parser_c.ml"
               : 'declaratorsd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1707 "parser_c.mly"
                           ( _2 )
# 6258 "parser_c.ml"
               : 'declaratorsd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1708 "parser_c.mly"
                           ( _1 )
# 6266 "parser_c.ml"
               : 'declaratorsd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 's_or_u_spec2) in
    Obj.repr(
# 1713 "parser_c.mly"
                                   ( dt "su" (); _1 )
# 6273 "parser_c.ml"
               : 'struct_or_union_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_or_union2) in
    Obj.repr(
# 1714 "parser_c.mly"
                                  ( et "su" (); _1 )
# 6280 "parser_c.ml"
               : 'struct_or_union))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_decl2) in
    Obj.repr(
# 1715 "parser_c.mly"
                           ( et "struct" (); _1 )
# 6287 "parser_c.ml"
               : 'struct_decl))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1717 "parser_c.mly"
                 ( et "dotdot" (); _1 )
# 6294 "parser_c.ml"
               : 'dotdot))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'const_expr) in
    Obj.repr(
# 1718 "parser_c.mly"
                        ( dt "const_expr2" (); _1 )
# 6301 "parser_c.ml"
               : 'const_expr2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_decl_list) in
    Obj.repr(
# 1721 "parser_c.mly"
                     ( _1 )
# 6308 "parser_c.ml"
               : 'struct_decl_list_gcc))
; (fun __caml_parser_env ->
    Obj.repr(
# 1722 "parser_c.mly"
                         ( [] )
# 6314 "parser_c.ml"
               : 'struct_decl_list_gcc))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'tobrace_enum) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'enumerator_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'gcc_comma_opt_struct) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_enum) in
    Obj.repr(
# 1730 "parser_c.mly"
     ( Enum (None,    _3),           [_1;_2;_5] ++ _4 )
# 6325 "parser_c.ml"
               : 'enum_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : 'ident) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : 'tobrace_enum) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : 'enumerator_list) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : 'gcc_comma_opt_struct) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : 'tcbrace_enum) in
    Obj.repr(
# 1732 "parser_c.mly"
     ( Enum (Some (fst _2), _4),     [_1; snd _2; _3;_6] ++ _5 )
# 6337 "parser_c.ml"
               : 'enum_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'ident) in
    Obj.repr(
# 1734 "parser_c.mly"
     ( EnumName (fst _2),       [_1; snd _2] )
# 6345 "parser_c.ml"
               : 'enum_spec))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'idente) in
    Obj.repr(
# 1737 "parser_c.mly"
                          ( _1, None     )
# 6352 "parser_c.ml"
               : 'enumerator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'idente) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'const_expr) in
    Obj.repr(
# 1738 "parser_c.mly"
                          ( _1, Some (_2, _3) )
# 6361 "parser_c.ml"
               : 'enumerator))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ident_cpp) in
    Obj.repr(
# 1745 "parser_c.mly"
                  ( LP.add_ident (str_of_name _1); _1 )
# 6368 "parser_c.ml"
               : 'idente))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'function_def) in
    Obj.repr(
# 1752 "parser_c.mly"
                                     ( fixFunc _1 )
# 6375 "parser_c.ml"
               : 'function_definition))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 1755 "parser_c.mly"
                  ( [_1 Ast_c.LocalDecl]   )
# 6382 "parser_c.ml"
               : 'decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 1756 "parser_c.mly"
                  ( _1 ++ [_2 Ast_c.LocalDecl] )
# 6390 "parser_c.ml"
               : 'decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_directive) in
    Obj.repr(
# 1760 "parser_c.mly"
                                    ( )
# 6397 "parser_c.ml"
               : 'cpp_directive_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'cpp_directive_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_directive) in
    Obj.repr(
# 1761 "parser_c.mly"
                                    ( )
# 6405 "parser_c.ml"
               : 'cpp_directive_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'start_fun) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'compound) in
    Obj.repr(
# 1764 "parser_c.mly"
                           ( LP.del_scope(); (_1, _2, None) )
# 6413 "parser_c.ml"
               : 'function_def))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'start_fun) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'cpp_directive_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'compound) in
    Obj.repr(
# 1765 "parser_c.mly"
                                         ( LP.del_scope(); (_1, _3, None) )
# 6422 "parser_c.ml"
               : 'function_def))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'start_fun) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'decl_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'compound) in
    Obj.repr(
# 1766 "parser_c.mly"
                                     (
     (* TODO: undo the typedef added ? *)
     LP.del_scope();
     (_1, _3, Some _2)
   )
# 6435 "parser_c.ml"
               : 'function_def))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'start_fun2) in
    Obj.repr(
# 1773 "parser_c.mly"
  ( LP.new_scope();
    fix_add_params_ident _1;
    (* toreput? !LP._lexer_hint.toplevel <- false;  *)
    _1
  )
# 6446 "parser_c.ml"
               : 'start_fun))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declaratorfd) in
    Obj.repr(
# 1780 "parser_c.mly"
     ( let (returnType,storage) = fixDeclSpecForFuncDef _1 in
       let (id, attrs) = _2 in
       (fst id, fixOldCDecl ((snd id) returnType) , storage, attrs)
     )
# 6457 "parser_c.ml"
               : 'start_fun2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ctor_dtor) in
    Obj.repr(
# 1784 "parser_c.mly"
               ( _1 )
# 6464 "parser_c.ml"
               : 'start_fun2))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1787 "parser_c.mly"
                                (
     let id = RegularName (mk_string_wrap _1) in
     let ret = mk_ty NoType [] in
     let ty = mk_ty (FunctionType (ret, (([], (false, []))))) [_2;_3] in
     let storage = ((NoSto,false),[]) in
     let attrs = [] in
     (id, ty, storage, attrs) )
# 6479 "parser_c.ml"
               : 'ctor_dtor))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : string * Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : 'topar) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'parameter_type_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : 'tcpar) in
    Obj.repr(
# 1794 "parser_c.mly"
                                                    (
     let id = RegularName (mk_string_wrap _1) in
     let ret = mk_ty NoType [] in
     let ty = mk_ty (FunctionType (ret, _3)) [_2;_4] in
     let storage = ((NoSto,false),[]) in
     let attrs = [] in
     (id, ty, storage, attrs) )
# 6495 "parser_c.ml"
               : 'ctor_dtor))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1815 "parser_c.mly"
              ( et "declaratorfd" (); _1, Ast_c.noattr )
# 6502 "parser_c.ml"
               : 'declaratorfd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attributes) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'declarator) in
    Obj.repr(
# 1817 "parser_c.mly"
                           ( et "declaratorfd" (); _2, _1 )
# 6510 "parser_c.ml"
               : 'declaratorfd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'declarator) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attributes) in
    Obj.repr(
# 1818 "parser_c.mly"
                           ( et "declaratorfd" (); _1, Ast_c.noattr )
# 6518 "parser_c.ml"
               : 'declaratorfd))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : (Ast_c.info * bool ref)) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1828 "parser_c.mly"
     (
       let (i1, in_ifdef) = _1 in
       let (s, i2) = _2 in

       (* redo some lexing work :( *)
       let inc_file =
         match () with
         | _ when s =~ "^\"\\(.*\\)\"$" ->
             Local (Common.split "/" (matched1 s))
         | _ when s =~ "^\\<\\(.*\\)\\>$" ->
             NonLocal (Common.split "/" (matched1 s))
         | _ ->
             Weird s
       in
       Include { i_include = (inc_file, [i1;i2]);
                 i_rel_pos = Ast_c.noRelPos();
                 i_is_in_ifdef = !in_ifdef;
                 i_content = Ast_c.noi_content;
       }
     )
# 6545 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'define_val) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1850 "parser_c.mly"
     ( Define ((fst _2, [_1; snd _2;_4]), (DefineVar, _3)) )
# 6555 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 6 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 5 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 3 : 'param_define_list) in
    let _5 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _6 = (Parsing.peek_val __caml_parser_env 1 : 'define_val) in
    let _7 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1857 "parser_c.mly"
     ( Define
         ((fst _2, [_1; snd _2; _7]),
           (DefineFunc (_4, [_3;_5]), _6))
     )
# 6571 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1863 "parser_c.mly"
     ( Define((fst _2, [_1; snd _2; _3]), (Undef,DefineEmpty)) )
# 6580 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : (string * Ast_c.info)) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'pragmainfo) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1866 "parser_c.mly"
     ( Pragma((fst _2, [_1; snd _2; _4]), _3) )
# 6590 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1868 "parser_c.mly"
                      ( OtherDirective ([_1]) )
# 6597 "parser_c.ml"
               : 'cpp_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list_ne) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1871 "parser_c.mly"
                                ( (PragmaTuple (_2, [_1;_3])) )
# 6606 "parser_c.ml"
               : 'pragmainfo))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1872 "parser_c.mly"
               ( PragmaTuple ([], [_1;_2]) )
# 6614 "parser_c.ml"
               : 'pragmainfo))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'ident_define_list_ne) in
    Obj.repr(
# 1873 "parser_c.mly"
                        ( PragmaIdList _1 )
# 6621 "parser_c.ml"
               : 'pragmainfo))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.expression) in
    Obj.repr(
# 1879 "parser_c.mly"
             ( DefineExpr _1 )
# 6628 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.statement) in
    Obj.repr(
# 1880 "parser_c.mly"
             ( DefineStmt _1 )
# 6635 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 1881 "parser_c.mly"
             ( DefineStmt (mk_st (Decl (_1 Ast_c.NotLocalDecl)) Ast_c.noii) )
# 6642 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl_spec) in
    Obj.repr(
# 1891 "parser_c.mly"
     ( let returnType = fixDeclSpecForMacro _1 in
       DefineType returnType
     )
# 6651 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'decl_spec) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'abstract_declarator) in
    Obj.repr(
# 1895 "parser_c.mly"
     ( let returnType = fixDeclSpecForMacro _1 in
       let typ = _2 returnType in
       DefineType typ
     )
# 6662 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'stat_or_decl) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'stat_or_decl_list) in
    Obj.repr(
# 1907 "parser_c.mly"
     ( DefineMulti
	 (List.map
	    (function
		StmtElem e -> e
	      | _ -> failwith "unexpected statement for DefineMulti")
	    (_1 :: _2)) )
# 6675 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'function_definition) in
    Obj.repr(
# 1921 "parser_c.mly"
                       ( DefineFunction _1 )
# 6682 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : 'initialize_list) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'gcc_comma_opt_struct) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : 'comma_opt) in
    Obj.repr(
# 1924 "parser_c.mly"
    ( DefineInit (InitList (List.rev _2), [_1;_4]++_3++_5)  )
# 6693 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 5 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.statement) in
    let _3 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.expression) in
    let _6 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1928 "parser_c.mly"
     (
       (* TOREPUT
       if fst $5 <> "0"
       then pr2 "WEIRD: in macro and have not a while(0)";
       *)
       DefineDoWhileZero ((_2,_5),   [_1;_3;_4;_6])
     )
# 6711 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'asmbody) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1936 "parser_c.mly"
                                         ( DefineTodo )
# 6721 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'asmbody) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1937 "parser_c.mly"
                                         ( DefineTodo )
# 6732 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1940 "parser_c.mly"
              ( DefineTodo )
# 6739 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    Obj.repr(
# 1942 "parser_c.mly"
                   ( DefineEmpty )
# 6745 "parser_c.ml"
               : 'define_val))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 1948 "parser_c.mly"
                        ( mk_string_wrap _1 )
# 6752 "parser_c.ml"
               : 'param_define))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : string * Ast_c.info) in
    Obj.repr(
# 1949 "parser_c.mly"
                        ( mk_string_wrap _1 )
# 6759 "parser_c.ml"
               : 'param_define))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 1950 "parser_c.mly"
                        ( mk_string_wrap _1 )
# 6766 "parser_c.ml"
               : 'param_define))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1951 "parser_c.mly"
                        ( "...", [_1] )
# 6773 "parser_c.ml"
               : 'param_define))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1953 "parser_c.mly"
                        ( "register", [_1] )
# 6780 "parser_c.ml"
               : 'param_define))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : ((int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1960 "parser_c.mly"
     ( let (tag,ii) = _1 in
       IfdefDirective ((Ifdef, IfdefTag (Common.some !tag)),  [ii]) )
# 6788 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : ((int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1963 "parser_c.mly"
     ( let (tag,ii) = _1 in
       IfdefDirective ((IfdefElse, IfdefTag (Common.some !tag)), [ii]) )
# 6796 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : ((int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1966 "parser_c.mly"
     ( let (tag,ii) = _1 in
       IfdefDirective ((IfdefElseif, IfdefTag (Common.some !tag)), [ii]) )
# 6804 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : ((int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1969 "parser_c.mly"
     ( let (tag,ii) = _1 in
       IfdefDirective ((IfdefEndif, IfdefTag (Common.some !tag)), [ii]) )
# 6812 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (bool * (int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1973 "parser_c.mly"
     ( let (_b, tag,ii) = _1 in
       IfdefDirective ((Ifdef, IfdefTag (Common.some !tag)), [ii]) )
# 6820 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (bool * (int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1976 "parser_c.mly"
     ( let (_b, tag,ii) = _1 in
       IfdefDirective ((Ifdef, IfdefTag (Common.some !tag)), [ii]) )
# 6828 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (bool * (int * int) option ref * Ast_c.info)) in
    Obj.repr(
# 1979 "parser_c.mly"
     ( let (_b, tag,ii) = _1 in
       IfdefDirective ((Ifdef, IfdefTag (Common.some !tag)), [ii]) )
# 6836 "parser_c.ml"
               : 'cpp_ifdef_directive))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : 'identifier) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1990 "parser_c.mly"
     (
       Declaration(MacroDecl((fst _1, _3, true), [snd _1;_2;_4;_5;fakeInfo()]))
       (* old: MacroTop (fst $1, $3,    [snd $1;$2;$4;$5])  *)
     )
# 6850 "parser_c.ml"
               : 'cpp_other))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 3 : 'identifier) in
    let _2 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 1 : 'argument_list) in
    let _4 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 1997 "parser_c.mly"
     ( Declaration (MacroDecl ((fst _1, _3, false), [snd _1;_2;_4;fakeInfo()])) )
# 6860 "parser_c.ml"
               : 'cpp_other))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'identifier) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2000 "parser_c.mly"
                      ( EmptyDef [snd _1;_2] )
# 6868 "parser_c.ml"
               : 'cpp_other))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'function_definition) in
    Obj.repr(
# 2009 "parser_c.mly"
                                     ( Definition _1 )
# 6875 "parser_c.ml"
               : 'external_declaration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'decl) in
    Obj.repr(
# 2010 "parser_c.mly"
                                     ( Declaration (_1 Ast_c.NotLocalDecl) )
# 6882 "parser_c.ml"
               : 'external_declaration))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : string * Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : Ast_c.info) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : 'translation_unit) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2015 "parser_c.mly"
     ( !LP._lexer_hint.context_stack <- [LP.InTopLevel]; 
       Namespace (_4, [_1; snd _2; _3; _5]) )
# 6894 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'external_declaration) in
    Obj.repr(
# 2018 "parser_c.mly"
                                                ( _1 )
# 6901 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_directive) in
    Obj.repr(
# 2022 "parser_c.mly"
     ( CppTop _1 )
# 6908 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_other) in
    Obj.repr(
# 2024 "parser_c.mly"
     ( _1 )
# 6915 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'cpp_ifdef_directive) in
    Obj.repr(
# 2026 "parser_c.mly"
     ( IfdefTop _1 )
# 6922 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 4 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 3 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 2 : 'asmbody) in
    let _4 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _5 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2029 "parser_c.mly"
                                                ( EmptyDef [_1;_2;_4;_5] )
# 6933 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2036 "parser_c.mly"
              ( EmptyDef [_1] )
# 6940 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2039 "parser_c.mly"
              ( FinalDef _1 )
# 6947 "parser_c.ml"
               : Ast_c.toplevel))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2048 "parser_c.mly"
                  ( LP.push_context LP.InFunction; LP.new_scope (); _1 )
# 6954 "parser_c.ml"
               : 'tobrace))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2049 "parser_c.mly"
                  ( LP.pop_context();              LP.del_scope (); _1 )
# 6961 "parser_c.ml"
               : 'tcbrace))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2051 "parser_c.mly"
                      ( LP.push_context LP.InEnum; _1 )
# 6968 "parser_c.ml"
               : 'tobrace_enum))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2052 "parser_c.mly"
                      ( LP.pop_context (); _1 )
# 6975 "parser_c.ml"
               : 'tcbrace_enum))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2054 "parser_c.mly"
                     ( LP.push_context LP.InInitializer; _1 )
# 6982 "parser_c.ml"
               : 'tobrace_ini))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2055 "parser_c.mly"
                     ( LP.pop_context (); _1 )
# 6989 "parser_c.ml"
               : 'tcbrace_ini))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2057 "parser_c.mly"
                        ( LP.push_context LP.InStruct; _1)
# 6996 "parser_c.ml"
               : 'tobrace_struct))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2058 "parser_c.mly"
                        ( LP.pop_context (); _1 )
# 7003 "parser_c.ml"
               : 'tcbrace_struct))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2064 "parser_c.mly"
     ( LP.new_scope ();et "topar" ();
       LP.push_context LP.InParameter;
       _1
     )
# 7013 "parser_c.ml"
               : 'topar))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2069 "parser_c.mly"
     ( LP.del_scope ();dt "tcpar" ();
       LP.pop_context ();
       _1
     )
# 7023 "parser_c.ml"
               : 'tcpar))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'string_elem) in
    Obj.repr(
# 2108 "parser_c.mly"
               ( _1 )
# 7030 "parser_c.ml"
               : 'string_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'string_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'string_elem) in
    Obj.repr(
# 2109 "parser_c.mly"
                           ( _1 ++ _2 )
# 7038 "parser_c.ml"
               : 'string_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'colon_asm) in
    Obj.repr(
# 2112 "parser_c.mly"
             ( [_1] )
# 7045 "parser_c.ml"
               : 'colon_asm_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'colon_asm_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'colon_asm) in
    Obj.repr(
# 2113 "parser_c.mly"
                             ( _1 ++ [_2] )
# 7053 "parser_c.ml"
               : 'colon_asm_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'colon_option) in
    Obj.repr(
# 2116 "parser_c.mly"
                ( [_1, []] )
# 7060 "parser_c.ml"
               : 'colon_option_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'colon_option_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'colon_option) in
    Obj.repr(
# 2117 "parser_c.mly"
                                         ( _1 ++ [_3, [_2]] )
# 7069 "parser_c.ml"
               : 'colon_option_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'argument_ne) in
    Obj.repr(
# 2121 "parser_c.mly"
                                         ( [_1, []] )
# 7076 "parser_c.ml"
               : 'argument_list_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list_ne) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'argument) in
    Obj.repr(
# 2122 "parser_c.mly"
                                    ( _1 ++ [_3,    [_2]] )
# 7085 "parser_c.ml"
               : 'argument_list_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'argument) in
    Obj.repr(
# 2125 "parser_c.mly"
                                      ( [_1, []] )
# 7092 "parser_c.ml"
               : 'argument_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'argument_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'argument) in
    Obj.repr(
# 2126 "parser_c.mly"
                                 ( _1 ++ [_3,    [_2]] )
# 7101 "parser_c.ml"
               : 'argument_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 2136 "parser_c.mly"
                             ( [RegularName (mk_string_wrap _1), []] )
# 7108 "parser_c.ml"
               : 'ident_define_list_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'ident_define_list_ne) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : (string * Ast_c.info)) in
    Obj.repr(
# 2138 "parser_c.mly"
     ( _1 ++ [RegularName (mk_string_wrap _2), []] )
# 7116 "parser_c.ml"
               : 'ident_define_list_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_decl) in
    Obj.repr(
# 2142 "parser_c.mly"
                                 ( [_1] )
# 7123 "parser_c.ml"
               : 'struct_decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'struct_decl_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'struct_decl) in
    Obj.repr(
# 2143 "parser_c.mly"
                                 ( _1 ++ [_2] )
# 7131 "parser_c.ml"
               : 'struct_decl_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'struct_declarator) in
    Obj.repr(
# 2147 "parser_c.mly"
                                                   ( [_1,           []] )
# 7138 "parser_c.ml"
               : 'struct_declarator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'struct_declarator_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'struct_declarator) in
    Obj.repr(
# 2148 "parser_c.mly"
                                                   ( _1 ++ [_3,     [_2]] )
# 7147 "parser_c.ml"
               : 'struct_declarator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'enumerator) in
    Obj.repr(
# 2152 "parser_c.mly"
                                     ( [_1,          []]   )
# 7154 "parser_c.ml"
               : 'enumerator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'enumerator_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'enumerator) in
    Obj.repr(
# 2153 "parser_c.mly"
                                     ( _1 ++ [_3,    [_2]] )
# 7163 "parser_c.ml"
               : 'enumerator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'init_declarator) in
    Obj.repr(
# 2157 "parser_c.mly"
                                               ( [_1,   []] )
# 7170 "parser_c.ml"
               : 'init_declarator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'init_declarator_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'init_declarator) in
    Obj.repr(
# 2158 "parser_c.mly"
                                               ( _1 ++ [_3,     [_2]] )
# 7179 "parser_c.ml"
               : 'init_declarator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl) in
    Obj.repr(
# 2162 "parser_c.mly"
                                        ( [_1, []] )
# 7186 "parser_c.ml"
               : 'parameter_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'parameter_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'parameter_decl) in
    Obj.repr(
# 2163 "parser_c.mly"
                                        ( _1 ++ [_3,  [_2]] )
# 7195 "parser_c.ml"
               : 'parameter_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2166 "parser_c.mly"
                           ( [_1] )
# 7202 "parser_c.ml"
               : 'taction_list_ne))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'taction_list_ne) in
    Obj.repr(
# 2167 "parser_c.mly"
                           ( _1 :: _2 )
# 7210 "parser_c.ml"
               : 'taction_list_ne))
; (fun __caml_parser_env ->
    Obj.repr(
# 2175 "parser_c.mly"
                        ( [] )
# 7216 "parser_c.ml"
               : 'taction_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'taction_list) in
    Obj.repr(
# 2176 "parser_c.mly"
                        ( _1 :: _2 )
# 7224 "parser_c.ml"
               : 'taction_list))
; (fun __caml_parser_env ->
    Obj.repr(
# 2179 "parser_c.mly"
                   ( [] )
# 7230 "parser_c.ml"
               : 'param_define_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'param_define) in
    Obj.repr(
# 2180 "parser_c.mly"
                                          ( [_1, []] )
# 7237 "parser_c.ml"
               : 'param_define_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 2 : 'param_define_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 1 : Ast_c.info) in
    let _3 = (Parsing.peek_val __caml_parser_env 0 : 'param_define) in
    Obj.repr(
# 2181 "parser_c.mly"
                                          ( _1 ++ [_3, [_2]] )
# 7246 "parser_c.ml"
               : 'param_define_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'designator) in
    Obj.repr(
# 2184 "parser_c.mly"
              ( [_1] )
# 7253 "parser_c.ml"
               : 'designator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'designator_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'designator) in
    Obj.repr(
# 2185 "parser_c.mly"
                              ( _1 ++ [_2] )
# 7261 "parser_c.ml"
               : 'designator_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'attribute) in
    Obj.repr(
# 2188 "parser_c.mly"
             ( [_1] )
# 7268 "parser_c.ml"
               : 'attribute_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attribute_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attribute) in
    Obj.repr(
# 2189 "parser_c.mly"
                            ( _1 ++ [_2] )
# 7276 "parser_c.ml"
               : 'attribute_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'attribute_storage) in
    Obj.repr(
# 2192 "parser_c.mly"
                     ( [_1] )
# 7283 "parser_c.ml"
               : 'attribute_storage_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 1 : 'attribute_storage_list) in
    let _2 = (Parsing.peek_val __caml_parser_env 0 : 'attribute_storage) in
    Obj.repr(
# 2193 "parser_c.mly"
                                            ( _1 ++ [_2] )
# 7291 "parser_c.ml"
               : 'attribute_storage_list))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : 'attribute_list) in
    Obj.repr(
# 2196 "parser_c.mly"
                           ( _1 )
# 7298 "parser_c.ml"
               : 'attributes))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2202 "parser_c.mly"
          (  [_1] )
# 7305 "parser_c.ml"
               : 'gcc_comma_opt))
; (fun __caml_parser_env ->
    Obj.repr(
# 2203 "parser_c.mly"
                    (  []  )
# 7311 "parser_c.ml"
               : 'gcc_comma_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.info) in
    Obj.repr(
# 2206 "parser_c.mly"
          (  [_1] )
# 7318 "parser_c.ml"
               : 'comma_opt))
; (fun __caml_parser_env ->
    Obj.repr(
# 2207 "parser_c.mly"
                    (  []  )
# 7324 "parser_c.ml"
               : 'comma_opt))
; (fun __caml_parser_env ->
    let _1 = (Parsing.peek_val __caml_parser_env 0 : Ast_c.expression) in
    Obj.repr(
# 2216 "parser_c.mly"
               ( Some _1 )
# 7331 "parser_c.ml"
               : 'gcc_opt_expr))
; (fun __caml_parser_env ->
    Obj.repr(
# 2217 "parser_c.mly"
                   ( None  )
# 7337 "parser_c.ml"
               : 'gcc_opt_expr))
(* Entry main *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
(* Entry celem *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
(* Entry statement *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
(* Entry expr *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
(* Entry type_name *)
; (fun __caml_parser_env -> raise (Parsing.YYexit (Parsing.peek_val __caml_parser_env 0)))
|]
let yytables =
  { Parsing.actions=yyact;
    Parsing.transl_const=yytransl_const;
    Parsing.transl_block=yytransl_block;
    Parsing.lhs=yylhs;
    Parsing.len=yylen;
    Parsing.defred=yydefred;
    Parsing.dgoto=yydgoto;
    Parsing.sindex=yysindex;
    Parsing.rindex=yyrindex;
    Parsing.gindex=yygindex;
    Parsing.tablesize=yytablesize;
    Parsing.table=yytable;
    Parsing.check=yycheck;
    Parsing.error_function=parse_error;
    Parsing.names_const=yynames_const;
    Parsing.names_block=yynames_block }
let main (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 1 lexfun lexbuf : Ast_c.program)
let celem (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 2 lexfun lexbuf : Ast_c.toplevel)
let statement (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 3 lexfun lexbuf : Ast_c.statement)
let expr (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 4 lexfun lexbuf : Ast_c.expression)
let type_name (lexfun : Lexing.lexbuf -> token) (lexbuf : Lexing.lexbuf) =
   (Parsing.yyparse yytables 5 lexfun lexbuf : Ast_c.fullType)
