type ('state, 'semantic_value) stack = {
  state : 'state;
  semv : 'semantic_value;
  startp : Lexing.position;
  endp : Lexing.position;
  next : ('state, 'semantic_value) stack;
}
type ('state, 'semantic_value, 'token) env = {
  lexer : Lexing.lexbuf -> 'token;
  lexbuf : Lexing.lexbuf;
  mutable token : 'token;
  mutable shifted : int;
  mutable previouserror : int;
  mutable stack : ('state, 'semantic_value) stack;
  mutable current : 'state;
}
module type TABLE =
  sig
    type state
    type token
    type terminal
    type semantic_value
    val token2terminal : token -> terminal
    val token2value : token -> semantic_value
    val error_terminal : terminal
    val error_value : semantic_value
    type production
    val default_reduction :
      state ->
      ('env -> production -> 'answer) -> ('env -> 'answer) -> 'env -> 'answer
    val action :
      state ->
      terminal ->
      semantic_value ->
      ('env -> bool -> terminal -> semantic_value -> state -> 'answer) ->
      ('env -> production -> 'answer) -> ('env -> 'answer) -> 'env -> 'answer
    val goto : state -> production -> state
    exception Accept of semantic_value
    exception Error
    type semantic_action = (state, semantic_value, token) env -> unit
    val semantic_action : production -> semantic_action
    val recovery : bool
    module Log :
      sig
        val state : state -> unit
        val shift : terminal -> state -> unit
        val reduce_or_accept : production -> unit
        val lookahead_token : Lexing.lexbuf -> terminal -> unit
        val initiating_error_handling : unit -> unit
        val resuming_error_handling : unit -> unit
        val handling_error : state -> unit
        val discarding_last_token : terminal -> unit
      end
  end
module type ENGINE =
  sig
    type state
    type token
    type semantic_value
    exception Error
    val entry :
      state -> (Lexing.lexbuf -> token) -> Lexing.lexbuf -> semantic_value
  end
